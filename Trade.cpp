#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
using namespace std;
void ProfitLoss(float open , float close, string name);

const string api_key = "4cac4af5f73a405c9632e98cca7ef7f8";

// Callback function for cURL to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

string get_price(const string& ticker_symbol, const string& api) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << endl;
        return "";
    }

    // Set up the URL
    string url = "https://api.twelvedata.com/price?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
        return "";
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        cerr << "Failed to parse JSON: " << errors << endl;
        delete reader;
        return "";
    }
    delete reader;

    // Extract and return the price
    string price = root["price"].asString();
    return price;
}

Json::Value get_stock_quote(const string& ticker_symbol, const string& api) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize cURL." << endl;
        return Json::Value(); // Return an empty JSON value on error
    }

    // Set up the URL
    string url = "https://api.twelvedata.com/quote?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
        return Json::Value(); // Return an empty JSON value on error
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        cerr << "Failed to parse JSON: " << errors << endl;
        delete reader;
        return Json::Value(); // Return an empty JSON value on error
    }
    delete reader;

    return root;
}

int main() {

    string ticker;
    cout << "Enter Ticker symbol of a company: ";
    cin >> ticker;

    string stock_price = get_price(ticker, api_key);
    if (!stock_price.empty()) {
        string price = stock_price;
        //cout << "Stock Price for " << ticker << ": " << stock_price << std::endl;
    } else {
        cerr << "Failed to fetch stock price." << std::endl;
        return 1;
    }

    Json::Value stock_data = get_stock_quote(ticker, api_key);
    if (!stock_data.empty()) {
        //std::cout << "Stock Quote for " << ticker << ": " << stock_quote.toStyledString() << std::endl;
        string name = stock_data["name"].asString();
        string exchange = stock_data["exchange"].asString();
        string currency = stock_data["currency"].asString();
        float open = stof(stock_data["open"].asString());
        float high = stof(stock_data["high"].asString());
        float low = stof(stock_data["low"].asString());
        float close = stof(stock_data["close"].asString());
        float volume = stof(stock_data["volume"].asString());
        float change = stof(stock_data["change"].asString());
        ProfitLoss(open , close, name);
    } else {
        cerr << "Failed to fetch stock quote." << endl;
        return 1;
    }
    
    return 0;
}


void ProfitLoss(float open , float close, string name){

    float percentage_change = ((close - open) / open) * 100;

    if(percentage_change > 0){
        cout << "The "+name+" stocks is in profit of "<< percentage_change <<"%\n";
    }
    else if(percentage_change < 0){
        cout << "The "+name+" stocks is in loss of "<< percentage_change <<"%\n";
    }
    else{
        cout << "The "+name+" stocks is in neutral state of "<< percentage_change <<"%\n";
    }
}

void BuySell(){
    while (true) {
        cout << "Options:" << std::endl;
        cout << "1. Buy stock" << std::endl;
        cout << "2. Sell stock" << std::endl;
        cout << "3. Quit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                
            case 2:
                
            case 3:
                
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}