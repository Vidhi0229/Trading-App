
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
using namespace std;
int main() {
    
    cout << "Enter the stock symbol (ticker): ";
    string ticker;
    cin >> ticker;
    double close = 0.0, opened = 0.0, percent;

    
    string pythonCommand = "python3 Data.py " + ticker;
    int exitCode = system(pythonCommand.c_str());

    if (exitCode != 0) {
        cerr << "Failed to fetch stock data." << endl;
        return 1;
    }

    
    ifstream file(ticker + "_data.txt");

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;

    
    while (getline(file, line)) {
        cout << line << std::endl;
    }
    
    file.close();

    return 0;
}
