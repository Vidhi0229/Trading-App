#include "functions.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

void ProfitLoss(float open, float close, std::string name) {
    float percentage_change = ((close - open) / open) * 100;

    if (percentage_change > 0) {
        cout << "\nThe " + name + " stocks is in profit of " << percentage_change << "%\n";
    } else if (percentage_change < 0) {
        cout << "\nThe " + name + " stocks is in loss of " << percentage_change << "%\n";
    } else {
        cout << "\nThe " + name + " stocks is in a neutral state of " << percentage_change << "%\n";
    }
}

void wantTransact(std::string ans, int amount, float price) {
    transform(ans.begin(), ans.end(), ans.begin(), ::toupper);
    if (ans == "Y") {
        cout << "Enter the amount of stock to know the cost of stock: ";
        cin >> amount;
        cout << "\nThe stock cost: " << amount * price << "\n";
    } else if (ans == "N") {
        cout << "\nHappy Trading!!!\n\n";
    } else {
        cout << "\nInvalid Choice\n";
    }
}

void print_data(std::string name, std::string exchange, std::string currency, float open, float high, float low, float close, float volume, float change, float price) {
    cout << "\nGenerating Data....\n\n";
    cout <<
        "name: " << name << "\n" <<
        "exchange: " << exchange << "\n" <<
        "currency:" << currency << "\n" <<
        "Open price: " << open << "\n" <<
        "High price: " << high << "\n" <<
        "Low price: " << low << "\n" <<
        "Close price: " << close << "\n" <<
        "Volume:" << volume << "\n" <<
        "Change: " << change << "\n" <<
        "Current Price: " << price << "\n";
}
