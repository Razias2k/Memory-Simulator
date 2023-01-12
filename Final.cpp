#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream> 

using namespace std;

int memsizePrompt() {
    int mainmemSize; 
    cout << "Enter the size of main memory in bytes: ";
    cin >> mainmemSize;
    return  mainmemSize;
}

int cachesizePrompt() {
    int cacheSize;
    cout << "Enter the size of the cache in bytes: ";
    cin >> cacheSize;
    return cacheSize;
}

int cacheblocksizePrompt() {
    int cacheblockSize;
    cout << "Enter the cache block/line size: ";
    cin >> cacheblockSize;
    return cacheblockSize;
}

int setassociativityPrompt() {
    int setassociativity;
    cout << "Enter the degree of set-associativity (input n for an n-way set-associative mapping): ";
    cin >> setassociativity;
    return setassociativity;
}

char replacementpolicyPrompt() {
    char replacementpolicy;
    cout << "Enter the replacement policy (L = LRU, F = FIFO): ";
    cin >> replacementpolicy;
    return replacementpolicy;
}

string inputfilePrompt() {
    string inputfile;
    cout << "Enter the name of the input file containing the list of memory references generated by the CPU: ";
    cin >> inputfile;
    return inputfile;
}

int addresslinesCalc(int ALC_input) {
    int tempCalc = log2(ALC_input);
    return tempCalc;
}

int offsetbitCalc(int OBC_input) {
    int tempCalc2 = log2(OBC_input);
    return tempCalc2;
}

int indexbitCalc(int cacheSize, int blockSize, int nwaysetassociativity) {
    int cacheblockSize = cacheSize / blockSize;
    int tempCalc3 = cacheblockSize / nwaysetassociativity;
    int indexBits = log2(tempCalc3);
    return indexBits;
}

int tagbitCalc(int addressLines, int index, int offset) {
    int tagBits = addressLines - index - offset;
    return tagBits;
}

int numofcacheblocksCalc(int cacheSize, int blockSize) {
    int temp = cacheSize / blockSize;
    return temp;
}

int totalcachesizeCalc(int originalcacheSize, int numofBlocks, int tagBits) {
    int temp1 = (1 + 1 + tagBits);
    int temp2 = temp1 * (numofBlocks);
    int temp3 = (temp2 / 8);
    int temp4 = originalcacheSize + temp3;
    return temp4;

}

vector<string> getfileContent(string input_file) {
    vector<string> vecOfStrs;
    ifstream in(input_file.c_str());
    in.ignore(1, '\n');
    string str;
    while (std::getline(in, str)) {
    
    // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }

    //Close The File
    in.close();
    return vecOfStrs;
}



int main() {
    vector<string> vecOfStr;
    char user_exit;
    bool exit_loop = false;

    while(exit_loop == false) {
        int MM_input = memsizePrompt();
    //  cout << input << endl;          debugging
        int CM_input = cachesizePrompt();
    //  cout << CM_input << endl;       debugging
        int CMBS_input = cacheblocksizePrompt();
    //  cout << CMBS_input << endl;     debugging
        int SA_input = setassociativityPrompt();
    //  cout << SA_input << endl;       debugging
        char RP_input = replacementpolicyPrompt();
    //  cout << RP_input << endl;       debugging     
        string IF_input = inputfilePrompt();
        cout << endl;
    //  cout << IF_input << endl;       debugging

        cout << "Simulator Output: " << endl;
        int totalAddressLines = addresslinesCalc(MM_input);
        cout << "Total address lines required: " << totalAddressLines << endl;
        int offsetBits = offsetbitCalc(CMBS_input);
        cout << "Number of bits for offset = " << offsetBits << endl;
        int indexBits = indexbitCalc(CM_input, CMBS_input, SA_input);
        cout << "Number of bits for index = " << indexBits << endl;
        int tagBits = tagbitCalc(totalAddressLines, offsetBits, indexBits);
        cout << "Number of bits for tag = " << tagBits << endl;
        int numofcacheBlocks = numofcacheblocksCalc(CM_input, CMBS_input);
        int totalcacheSize = totalcachesizeCalc(CM_input, numofcacheBlocks, tagBits);
        cout << "Total cache size required = " << totalcacheSize << " bytes" << endl;
        vecOfStr = getfileContent(IF_input);
        
 /*      debugging file read
        for(string & line : vecOfStr) {
            cout<<line<<endl;
    }
*/
        string RorW; 
        int address;
        for (int i = 0; i < vecOfStr.size(); i++) {
    
            RorW = vecOfStr.at(i)[0];
            address = stoi(vecOfStr.at(i).substr(2));
            cout << RorW << " " << address << endl;
        }

        cout << "\nContinue? (y = yes, n = no): ";
        cin >> user_exit;
        if (user_exit == 'n') {
            exit_loop = true;
            break;
    }

}
}
