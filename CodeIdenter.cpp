#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

void processLine(const string& line, int indentLevel, ofstream& outFile) {
    string indent(indentLevel * 4, ' '); 
    string trimmedLine = line;
    
    while (!trimmedLine.empty() && isspace(trimmedLine.back())) {
        trimmedLine.pop_back();
    }

    if (trimmedLine.empty()) {
        outFile << indent << endl;
        return;
    }
    
    if (trimmedLine.back() == '}') {
        if (indentLevel > 0) {
            --indentLevel;
        }
        outFile << indent << trimmedLine << endl;
        if (trimmedLine.find("{") != string::npos) {
            ++indentLevel;
        }
    } else if (trimmedLine.find("{") != string::npos) {
        outFile << indent << trimmedLine << endl;
        ++indentLevel;
    } else {
        outFile << indent << trimmedLine << endl;
    }
}

void indentCode(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile) {
        cerr << "Error opening input file." << endl;
        return;
    }
    if (!outFile) {
        cerr << "Error opening output file." << endl;
        return;
    }

    stack<int> braces;
    int indentLevel = 0;
    string line;

    while (getline(inFile, line)) {
        processLine(line, indentLevel, outFile);
    }

    inFile.close();
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }

    indentCode(argv[1], argv[2]);

    return 0;
}
