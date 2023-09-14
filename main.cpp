#include <bits/stdc++.h>
#include "functions.h"
#include "curl_function.h"
using namespace std;
const string api_key = "4cac4af5f73a405c9632e98cca7ef7f8";

int main() {
    string name, exchange, currency, ans;
    float open, high, low, close, volume, change, price;
    int amount;
    string ticker;
    cout << "\nEnter Ticker symbol of a company: ";
    cin >> ticker;

    string stock_price = get_price(ticker, api_key);
    if (!stock_price.empty()) {
        price = stof(stock_price);
        // cout << "Price: " << price << "\n";
        // cout << "Stock Price for " << ticker << ": " << stock_price << std::endl;
    } else {
        cerr << "Failed to fetch stock price." << endl;
        return 1;
    }

    Json::Value stock_data = get_stock_quote(ticker, api_key);
    if (!stock_data.empty()) {
        // std::cout << "Stock Quote for " << ticker << ": " << stock_quote.toStyledString() << std::endl;
        name = stock_data["name"].asString();
        exchange = stock_data["exchange"].asString();
        currency = stock_data["currency"].asString();
        open = stof(stock_data["open"].asString());
        high = stof(stock_data["high"].asString());
        low = stof(stock_data["low"].asString());
        close = stof(stock_data["close"].asString());
        volume = stof(stock_data["volume"].asString());
        change = stof(stock_data["change"].asString());
    } else {
        cerr << "Failed to fetch stock quote." << endl;
        return 1;
    }
    print_data(name, exchange, currency, open, high, low, close, volume, change, price);
    ProfitLoss(open, close, name);
    cout << "\nWant to know the cost of buying or selling stock? Enter Y for yes and N for no\n";
    cout << "Your Response: ";
    cin >> ans;
    wantTransact(ans, amount, price);
    return 0;
}
