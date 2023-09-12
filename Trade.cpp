#include<bits/stdc++.h>
using namespace std;

int main() {
    int i = 0;
    //double data;
    map<string, string> company_Data;
    vector <string> Key = {"Stock_Name", "Exchange", "Currency", "Open_Price", "High_Price", "Low_Price", "Close_Price", "Volume", "change", "Current_Price"};
    
    cout << "\nEnter the stock symbol (ticker): ";
    string ticker;
    cin >> ticker;
    
    cout << "\nFetch Market data....\n\n";

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

    }
    
    file.close();

    // int commaPos = line.find(',', i);
    // while (commaPos != string::npos){
    //     string value = line.substr(i, commaPos - i);
    //     company_Data.insert(make_pair(Key[i], value));
    //     cout << value <<"\n";
    //     i++;
    // }
    
    
    // //cout << stold(current_Price) << "\n";

    return 0;
}
