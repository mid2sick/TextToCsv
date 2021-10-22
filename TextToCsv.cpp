#include <fstream>   
#include <string>  
#include <iostream>  
#include <sstream>  
#include <string.h> 
using namespace std;   

bool prefix(const std::string& a, const std::string& b) {
  if (a.size() > b.size()) {
    return a.substr(0,b.size()) == b;
  }
  else {
    return b.substr(0,a.size()) == a;
  }
}


// change: the current sheet
const int current = 1;

// change the files
const char *inputCSV = "1.csv";
const char *inputText = "text.txt";
const char *outputCSV = "A1.csv";
const string nextParagraph = "A2 ";

// DONT CHANGE
//                 X    A1   A2   A3   A4    B    C    D    E
//                 0     1    2    3    4    5    6    7    8
const int AID[] = {  0,   0,  167, 171, 178, 193, 199, 210, 217};
const int NUM[] = {  0, 167,    4,   7,  15,   6,  11,   7,  11};

const int idStart = AID[current];
const int N = NUM[current];



int main() {
    string strT, strE, searchS, searchS2;
    string name[N + 10], context, keywords, references;
    
    ifstream infE, infT;
    fstream ofE;
    infE.open(inputCSV, ifstream::in);
    infT.open(inputText, ifstream::in);
    ofE.open(outputCSV, ofstream::out);
    
    int commaCnt = 0;
    int linecnt = 1;
    size_t comma[10];

    // 跳過最一開始的欄位
    getline(infE, strE);

    // store all the names
    for(int i = 1; i <= N; i ++) {
        getline(infE,strE);

        // search all the commas' location
        comma[0] = strE.find(',',0);
        comma[1] = strE.find(',', comma[0] + 1);
        
        // get the current lastname
        // (not the full name since there might be different number of spaces in 2-words names)
        name[i] = strE.substr(comma[1] + 1, 3);
    }
    name[N + 1] = "It's END";

    infE.seekg(0L, ios::beg);

    // 把最一開始的欄位複製到新的檔案
    getline(infE, strE);
    ofE << strE << endl;

    // start geting data
    for(int i = 1; i <= N; i ++) {
        context.clear();
        keywords.clear();
        references.clear();

        // find the name in text, they might be [num].[space][name] or [num].[tab][name]
        searchS = to_string((i + idStart)) + ". " + name[i];
        searchS2 = to_string((i + idStart)) + ".	" + name[i];

        while(strT.find(searchS) == -1 && strT.find(searchS2) == -1 ) {
            getline(infT, strT);
        }

        // skip empty line
        getline(infT, strT);
        getline(infT, strT);

        // adding context until reaching keywords
        do {
            context = context + strT + "\n";
            getline(infT, strT);
        }while(strT.find("關鍵詞") == -1);

        // get the keywords (name[i] is the first keyword after "關鍵字：")
        int loc = strT.find(name[i]);
        
        keywords = strT.substr(loc);

        // find the references
        while(strT.find("參考資料") == -1) {
            getline(infT, strT);
        }

        // skip the line of "參考資料："
        cout << strT << endl;
        getline(infT, strT);

        // get all the references until reaching the next person
        searchS = to_string((i + idStart + 1)) + ". " + name[i + 1];
        searchS2 = to_string((i + idStart + 1)) + ".	" + name[i + 1];

        while(!prefix(searchS, strT) && !prefix(searchS2, strT) && !prefix(nextParagraph, strT)) {
            references = references + strT + "\n";   
            getline(infT, strT);
        }

        // writing data to the new file
        getline(infE, strE);
        comma[0] = strE.find(',',0);
        commaCnt = 1;
        for(; commaCnt < 5; commaCnt ++) {
            comma[commaCnt] = strE.find(',', comma[commaCnt - 1] + 1);
        }

        // copy part of the original csv file
        string temp = strE.substr(0, comma[4] + 1);

        // output data to the new csv file
        ofE << temp << "\"" << context << "\",\"" <<  keywords << "\",\"" << references << "\"" << endl;
    }

    infE.close();
    ofE.close();
    return 0;  
}
