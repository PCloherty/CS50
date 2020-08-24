import os


from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    items = db.execute("SELECT symbol, shares FROM transactions WHERE user_id=:id ",id=session["user_id"])
    total_amount=0
    portfolio=[]
    
    for row in items:
        symbol=row["symbol"]
        shares=row["shares"]
        info=lookup(symbol)
        total= float(info["price"]) * float(shares)
        total_amount += total
        portfolio.append(list((symbol, info["name"], shares, usd(info["price"]),usd(total))))
    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    total_amount += cash[0]["cash"]
    return render_template("index.html", portfolio=portfolio, cash=usd(cash[0]["cash"]),total_amount=usd(total_amount))

    #return apology("TODO index")
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    if request.method == "POST":
        shares= int(request.form.get("shares"))
        symbol = lookup(request.form.get("symbol").upper())
        if not symbol:
            return apology("must provide a comapany symbol", 403)
        if not shares:
            return apology("must provide amount of shares being bought",403)
        if shares < 1:
            return apology("require a positive number",403)
        cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
      
        updated_cash = cash[0]["cash"] - shares * symbol['price']
        if updated_cash == 0:
            return apology("cant afford it", 403)
        
               
        
        check=db.execute("SELECT * FROM transactions WHERE user_id=:id and symbol=:symbol", id=session["user_id"], symbol=symbol["symbol"])
        date = datetime.utcnow()
        db.execute("INSERT INTO history (symbol, shares_involved, price_at_transaction, transaction_type, user_history,date) VALUES(:symbol, :shares_involved,:price_at_transaction ,:transaction_type, :user_history, :date)",
            symbol=symbol["symbol"],shares_involved=shares,price_at_transaction=symbol["price"],transaction_type="buy",user_history=session["user_id"], date=date)

        
        for check_row in check:
            if symbol["symbol"]:
                update_share= check_row["shares"]+ shares
                db.execute("UPDATE transactions SET shares=:shares WHERE user_id=:id and symbol=:symbol ",
                    id=session["user_id"], symbol=symbol["symbol"], shares=update_share)
                db.execute("UPDATE users SET cash= :cash WHERE id=:id", cash=updated_cash , id=session["user_id"])
                return redirect("/")
            
        
        db.execute("INSERT INTO transactions (user_id, symbol, shares) VALUES(:user_id, :symbol, :shares)",
            user_id=session["user_id"], symbol=symbol["symbol"], shares=shares)
        db.execute("UPDATE users SET cash= :cash WHERE id=:id", cash=updated_cash , id=session["user_id"])
        return redirect("/")
        
    else:
        return render_template("buy.html")
    #return apology("TODO buy")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_history=:id ORDER BY date DESC",id=session["user_id"])
    return render_template("history.html", history=history,)
    #return apology("TODO history")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    #if the request is get, load the quote page
    if request.method == "GET":
        return render_template("quote.html")
    else:
        #look up the symbol provided
        search = lookup(request.form.get("symbol"))
        #if no symbol was provided give error
        if not search:
           return apology("Must provide search criteria",403)
        #need a wrong symbol provided 
        
        #then load quoted with symbol information
        return render_template("quoted.html",api=search)
    
@app.route("/password_update", methods=["GET", "POST"])
def password_update():      
    if  request.method == "GET" :
        return render_template("password_update.html")
    else:
        
        password =request.form.get("password")
        confirm=request.form.get("confirmation")
        #pass both requirements
        if not password or not confirm:
            return apology("must provide Password and confirmation password",403)
        elif password != confirm:
            return apology("passwords did not match",403)
        #hash password    
        hash = generate_password_hash(password)
        #update database with new password
        db.execute("UPDATE users SET hash=:hash WHERE id=:id", hash=hash,id=session["user_id"])
        return redirect("/")
       
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    #if the request method is get, return template register.html(aka register component)
    if  request.method == "GET" :
        return render_template("register.html")
    #else cover issue where people dont input on input wrong username and password
    else:
        name = request.form.get("name")
        password =request.form.get("password")
        if not name:
            return apology("must provide username", 403)
        elif not password or not request.form.get("confirmation"):
            return apology("must provide Password and confirmation password",403)
        elif password != request.form.get("confirmation"):
            return apology("passwords did not match",403)
        #hash password
        hash = generate_password_hash(password)
        #send password to database and load main page
        db.execute("INSERT INTO users(username, hash) VALUES (:name, :hash)", name=name, hash=hash)
        return redirect("/")
    


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    portfolio = db.execute("SELECT symbol FROM transactions WHERE user_id= :id",id=session["user_id"])
    
    if request.method == "GET":
        return render_template("sell.html", stocks=portfolio)
    else:
        
        info=lookup(request.form.get("symbol"))
        price=info["price"]
        quantity= request.form.get("quantity")
        symbol=request.form.get("symbol")
        holding = db.execute("SELECT shares FROM transactions WHERE user_id=:id and symbol=:symbol", id=session["user_id"], symbol=symbol)
        if not symbol or not quantity:
            return apology("please provide symbol and quantity")
        if int(quantity) > int(holding[0]["shares"]):
            return apology("you do not have that many shares to sell",403)
        current_cash=db.execute("SELECT cash FROM users WHERE id=:id",id=session["user_id"])
        print(holding)
        updated_cash=current_cash[0]["cash"]+(float(quantity) * price)
        print(holding)
        
        updated_shares= holding[0]["shares"]-int(quantity)
        
        if updated_shares == 0:
            db.execute("DELETE FROM transactions WHERE user_id=:id and symbol=:symbol", id=session["user_id"], symbol=symbol)    
        
        db.execute("UPDATE transactions SET shares=:shares WHERE user_id=:id AND symbol=:symbol",shares=updated_shares, id=session["user_id"],symbol=symbol)
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=updated_cash , id=session["user_id"])
        
        date=datetime.utcnow()
        db.execute("INSERT INTO history (symbol, shares_involved, price_at_transaction, transaction_type, user_history,date) VALUES(:symbol, :shares_involved,:price_at_transaction ,:transaction_type, :user_history, :date)",
            symbol=symbol, shares_involved=quantity, price_at_transaction=price, transaction_type="sell", user_history=session["user_id"], date=date)
        
        return redirect("/")
        
        
        
        
        
    
        #cash=usd(cash[0]["cash"]),total=usd(total_amount))
    #return apology("TODO sell")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
