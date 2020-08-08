//reset scrores
function RPSCapsule(){
    //clear the outputs
    document.getElementById('yourScore').innerHTML = 0;
    document.getElementById('botScore').innerHTML = 0;
    document.getElementById('machine').innerHTML = '';
    document.getElementById('yourChoice').innerHTML = '';
    document.getElementById('result').innerHTML = '';
    } 

function maxScore() {
    let clearUScore = document.getElementById('yourScore');
    let clearBScore = document.getElementById('botScore');
    if (clearUScore.innerHTML > 5 || 
        clearBScore.innerHTML > 5) {
            RPSCapsule();
    }
    
}

function rock() {
    RPS(0);
}
function paper() {
    RPS(1);
}
function scissors() {
    //
    RPS(2);
}




//game
function RPS(vote) {
    let choices = ['Rock', 'Paper', 'Scissors'];
    let userChoice = choices[vote]
    let terminator = '';
    
 
    //bot functions
    //random number generator for the bot
    let randomN = Math.random();
    let range = Math.floor(randomN * 3);
    
    //allocating the index number to the array
    terminator = choices[range];
    
    //printing the option of the bot to the screen
    document.getElementById('machine').innerHTML = terminator;
    document.getElementById('yourChoice').innerHTML = userChoice;

    //outcomes of the choice combinations
    let result = document.getElementById('result');
    if ((range+1)%3 === vote ){
        result.innerHTML = "You Win!"
        win()
    } else if( range === vote){
        result.innerHTML= "Draw"
    } else {
        result.innerHTML = "You Lost!"
        lose()
    }
    
    
    
    
}

//additional functions
function win() {
    let i = Number(document.getElementById('yourScore').innerHTML);
    i++;
    document.getElementById('yourScore').innerHTML = i;
    maxScore();
    
    }
function lose(){
    let i = Number(document.getElementById('botScore').innerHTML);
    i++;
    document.getElementById('botScore').innerHTML = i;
    maxScore();
}