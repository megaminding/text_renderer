#include <iostream>
#include <fstream>
#include <cstring>


 #include <sstream>
 #include <streambuf>

 #include <cassert>
 using namespace std;

bool doBreak = false;
void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue);

void newLine(ostream& outf, int& count, bool& validSpace, bool& validBreak) {
    outf << '\n';
    count = 0;
    validSpace = false;
}
void printWord(const char* word, int wordLength, int& count, ostream& outf, bool& validSpace,  bool& validBreak) {
//    int wordCounter = 0;
//    for (int i = 0; word[i] != '\0'; i++) {
//        outf << word[wordCounter];
//        wordCounter += 1;
//    }
    outf << word;
    count += strlen(word);
    validSpace = true;
}

void cutDownWordAndPrint(char* tempPortion, int& tempPortionLength, int& count, ostream& outf, int lineLength, bool& validSpace, int& returnValue, bool& validBreak) {

    char first[181];
    char second[181];
    int firstLength = 0;
    int secondLength = 0;
    first[0] = '\0';
    second[0] = '\0';

    if (tempPortionLength + count > lineLength && tempPortionLength > 0) {
        if (tempPortionLength > lineLength) {
            returnValue = 1;
            while (tempPortionLength > lineLength) {
                firstLength = 0;
                first[0] = '\0';
                for (int i = 0; i < lineLength; ++i) {
                    first[firstLength] = tempPortion[i];
                    firstLength += 1;
                    first[firstLength] = '\0';
                }
                if (firstLength + count > lineLength) {
                    newLine(outf, count,validSpace, validBreak);
                    printWord(first, firstLength, count, outf,validSpace, validBreak);
                    for (int i = 0; tempPortion[i + lineLength] != '\0'; ++i) {
                        second[secondLength] = tempPortion[i + lineLength];
                        secondLength += 1;
                        second[secondLength] = '\0';
                    }
                  
                        tempPortionLength = 0;
                        tempPortion[tempPortionLength] = '\0';

              
                    for (int i = 0; second[i] != '\0'; ++i) {
                        tempPortion[tempPortionLength] = second[i];
                        tempPortionLength += 1;
                        tempPortion[tempPortionLength] = '\0';
                    }
                } else {
                    printWord(first, firstLength, count, outf,validSpace, validBreak);
                    newLine(outf, count,validSpace, validBreak);
                    for (int i = 0; tempPortion[i + lineLength] != '\0'; ++i) {
                        second[secondLength] = tempPortion[i + lineLength];
                        secondLength += 1;
                        second[secondLength] = '\0';
                    }
                    tempPortionLength = 0;
                    tempPortion[tempPortionLength] = '\0';
               
                    for (int i = 0; second[i] != '\0'; ++i) {
                        tempPortion[tempPortionLength] = second[i];
                        tempPortionLength += 1;
                        tempPortion[tempPortionLength] = '\0';
                    }

                }
            }
        } else {
            newLine(outf, count,validSpace, validBreak);
        }

    }
    if (tempPortionLength + count > lineLength) {
        newLine(outf, count,validSpace, validBreak);
        printWord(tempPortion, tempPortionLength, count, outf,validSpace, validBreak);
        tempPortion[0] = '\0';
        tempPortionLength = 0;
    } else if (tempPortionLength > 0) {
        printWord(tempPortion, tempPortionLength, count, outf,validSpace, validBreak);
        tempPortion[0] = '\0';
        tempPortionLength = 0;
    }
}
void getWordPortions(char* tempString, int& tempStringLength, ostream& outf, int& count, int& lineLength, char* tempPortion, int& tempPortionLength, bool& validSpace, int& returnValue, bool& validBreak) {
    int i = 0;

    bool firstSpace = true;
    

    
        for (i = 0; i < tempStringLength; ++i) {
            if (tempString[i] != '-') {
                tempPortion[tempPortionLength] = tempString[i];
                tempPortionLength += 1;
                tempPortion[tempPortionLength] = '\0';
            } else { // hyphen
                if (!validSpace || !firstSpace) {
                    cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength, validSpace, returnValue, validBreak);
                    firstSpace = false;
                }
                if (validSpace && tempPortionLength + count + 2 <= lineLength && tempPortionLength > 0 && firstSpace) {
                    outf << ' ';
                    count += 1; // for the space
                    validSpace = false;
                    firstSpace = false;
                    
                    cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
                    outf << '-';
                    validSpace = false;
                    firstSpace = false;
                } else {
                    count += 2; // for the hyphen
                    cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
                    outf << '-';
                    firstSpace = false;
                    validSpace = false;
                }
            }
        }
    }




void getWords(char c, ostream& outf, char* tempString, int& tempStringLength, int& count, int& lineLength, char* tempPortion, int& tempPortionLength, bool& validSpace, int& returnValue, bool& validBreak) {
    
    
//    if (strcmp(tempString, "@P@") == 0){
//        doBreak = true;
//    }
 //   else {
//
//        if (doBreak){
//            if (tempPortionLength > 0){
//                outf << '\n';
//                validBreak = false;
//            } else {
//                cout << "BADATTEMPT";
//                doBreak = false;
//            }
//        }
//    }
    if (strcmp(tempString, "@P@") == 0){
        outf << '\n';
        validBreak = false;
        tempStringLength = 0; // Reset the length of tempString
        tempString[tempStringLength] = '\0';
    }
    
    if (count <= lineLength) {
        getWordPortions(tempString, tempStringLength, outf, count, lineLength, tempPortion, tempPortionLength,validSpace, returnValue, validBreak);
        if (!validSpace) {
            cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
        }
        
        else if (tempPortionLength + count + 1 <= lineLength && tempPortionLength > 0) {
            outf << '+';
            validSpace = false;
            count += 1;
            cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
        }
        else {
            count += 1;
            cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
        }
        if ((c == '!' or c == '.' or c == '?' or c == ':')){
            if ( tempPortionLength + count + 3 <= lineLength and validSpace){
                outf << c;
                outf << "  ";
                count += 3;
                cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
                validSpace = false;
            } else {
                cutDownWordAndPrint(tempPortion, tempPortionLength, count, outf, lineLength,validSpace, returnValue, validBreak);
                outf << c;
                count += 1;
                validSpace = false;
            }
        }
        tempStringLength = 0; // Reset the length of tempString
        tempString[tempStringLength] = '\0';
    } else {
        cout << "new line";
    }
}


int render(int lineLength, istream& inf, ostream& outf) {
    char c;
    char tempString[181];
    char tempPortion[181];
    int tempStringLength = 0;
    int tempPortionLength = 0;
    int count = 0;
    bool validSpace = false;
    int returnValue = 0;
    bool validBreak = false;
    bool skip = false;
    
    if (lineLength < 1){
        return 2;
    }// 2 if the desired maximum line length is less than 1)

    while (inf.get(c)) {
        if (c == '\n'){
        getWords(c, outf, tempString, tempStringLength, count, lineLength, tempPortion, tempPortionLength, validSpace, returnValue, validBreak);
        }
        else if (c == ' ') {
            if (tempStringLength > 0){
                getWords(c, outf, tempString, tempStringLength, count, lineLength, tempPortion, tempPortionLength, validSpace, returnValue, validBreak);
            }
        }
        else if (c == '!' or c == '.' or c == '?' or c == ':'){
         
             getWords(c, outf, tempString, tempStringLength, count, lineLength, tempPortion, tempPortionLength, validSpace, returnValue, validBreak);
            
        }
        else {
            if (tempStringLength < 181) {
                tempString[tempStringLength] = c;
                tempStringLength += 1;
                tempString[tempStringLength] = '\0';
            } 
        }
    }
//    cout << "c:" << c << "ts" << tempString;
 
    if ((c != '!' and c != '.' and c != '?' and c != ':')){
        getWords(c, outf, tempString, tempStringLength, count, lineLength, tempPortion, tempPortionLength, validSpace, returnValue, validBreak);
    }

    outf << '\n';
    return returnValue;
}

void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}
int main() {
    testRender(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
           testRender(8, "  This is a test  \n", "This is\na test\n", 0);
    testRender(6, "Testing it", "Testin\ng it\n", 1);

           cerr << "Tests complete" << endl;
//               for (;;)
//           {
//               string filename = "/Users/megantieu/downloads/results.txt";
//
//               ifstream infile(filename);
//               if (!infile)
//               {
//                   cerr << "Cannot open " << filename << "!" << endl;
//                   continue;
//               }
//               cout << "Enter maximum line length: ";
//               int len;
//               cin >> len;
//               cin.ignore(10000, '\n');
//               int returnCode = render(len, infile, cout);
//               cout << "Return code is " << returnCode << endl;
//           }
    return 0;
}

