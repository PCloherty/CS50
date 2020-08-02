from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters = lettercount(text)
    words= wordcount(text)
    sentences= sentencescount(text)
    #print(f"letters {letters}")
    #print(f"words {words}")
    #print(f"sentences {sentences}")
    grade = calcindex(letters,words,sentences)
    if grade < 1:
        print("Before grade 1")
    elif grade > 16:
        print("Grade 16+")
    else :
        print(f'Grade {grade}')
    
    
def lettercount(text):
    count = 0
    for letters in text:
        if letters.isalpha():
            count+=1
    return count    
    
def wordcount(text):
    count=1
    for words in text:
        if words.isspace():
            count+=1
    return count
    
def sentencescount(text):
    breakers= {"?", ".", "!"}
    count=0
    for sentences in text:
        for icons in breakers:
            if sentences == icons:
                count+=1
    return count
    
def calcindex(letters,words,sentences):
    L = (letters/ words) *100
    S = (sentences/words )*100
    indexraw = 0.0588* L - 0.296 * S - 15.8;    
    index = round(indexraw)
    return index
main()