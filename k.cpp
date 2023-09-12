#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>  // Include the chrono library for timing
#include <thread>  // Include the thread library for sleep
using namespace std;

int main() {

    cout << "Enter the stock symbol (ticker): ";
        string ticker;
        cin >> ticker;
    while (true) {  // Continuously fetch data
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
        cout << "\n";
        // Sleep for a certain interval before fetching data again (e.g., 60 seconds)
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Adjust the interval as needed
    }

    return 0;
}
