from sys import argv, exit
import csv
import re


def main():
    with open(argv[1]) as data:
        readerdata = csv.DictReader(data)
        patterns = readerdata.fieldnames[1:]
        # seq is the string of data
        # readerseq is the sequances per person
        consecCounter = []
        for p in range(len(patterns)):
            consecCounter.append(1)
        with open(argv[2]) as sequance:
            readerseq = list(csv.reader(sequance))
            seq = readerseq[0][0]
            # for number of elements in patterns
            for i in range(len(patterns)):
                # regex through to get a a number of grouped STR and record heighest amount
                currentHeighest = 0
                regex = re.compile(f'({patterns[i]})+')
                search = regex.finditer(seq)
                for match in search:
                    consec = match.span()[1]-match.span()[0]
                    if consec > len(patterns[i]):
                        if consec > currentHeighest:
                            currentHeighest = consec
                # put current heighest into a list
                consecCounter[i] = currentHeighest/len(patterns[i]) 
            # create a counter to record how many matches
            matches = 0
            # for each name in the csv file and number of STRs to check
            for line in readerdata:
                for r in range(len(patterns)):
                    # check that the value in consecCounter matches line[patterns] if so add 1 to match
                    if consecCounter[r] == int(line[patterns[r]]):
                        matches += 1
                        # if matches == the number of patterns to search for print line["name"] and exit
                        if matches == len(patterns):
                            print(line["name"])   
                            exit()
                    else:
                        # reset matches to 0 on next name 
                        matches = 0
            # if no matches, return no match            
            if matches != len(patterns):
                print("No Match")    

main()
