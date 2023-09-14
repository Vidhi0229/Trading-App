#include<bits/stdc++.h>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
using namespace std;
void ProfitLoss(float open , float close, string name);
void wantTransact(string ans, int amount, float price);
void print_data(string name, string exchange, string currency, float open, float high, float low, float close, float volume, float change, float price);
    

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
    string name, exchange, currency, ans;
    float open, high, low, close, volume, change, price;
    int amount;
    string ticker;
    cout << "Enter Ticker symbol of a company: ";
    cin >> ticker;


    string stock_price = get_price(ticker, api_key);
    if (!stock_price.empty()) {
        price = stof(stock_price);
        cout << "Price: " << price << "\n";
        //cout << "Stock Price for " << ticker << ": " << stock_price << std::endl;
    } else {
        cerr << "Failed to fetch stock price." << std::endl;
        return 1;
    }

    Json::Value stock_data = get_stock_quote(ticker, api_key);
    if (!stock_data.empty()) {
        //std::cout << "Stock Quote for " << ticker << ": " << stock_quote.toStyledString() << std::endl;
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
    ProfitLoss(open , close, name);
    cout << "Want to know the cost of buying or selling stock? Enter Y for yes and N for no\n";
    cout << "Your Response: ";
    cin >> ans;
    wantTransact(ans, amount, price);
    return 0;
}


void ProfitLoss(float open , float close, string name){

    float percentage_change = ((close - open) / open) * 100;

    if(percentage_change > 0){
        cout << "\nThe "+name+" stocks is in profit of "<< percentage_change <<"%\n";
    }
    else if(percentage_change < 0){
        cout << "\nThe "+name+" stocks is in loss of "<< percentage_change <<"%\n";
    }
    else{
        cout << "\nThe "+name+" stocks is in neutral state of "<< percentage_change <<"%\n";
    }

}


void wantTransact(string ans, int amount, float price){
    transform(ans.begin(), ans.end(), ans.begin(), ::toupper);
    if(ans == "YES" || "Y"){
        cout << "Enter the amount of stock to know cost of stock: ";
        cin >> amount;
        cout << "The stock cost: "<< amount * price << "\n";
    }
    else if(ans == "NO" || "N"){
        cout << "Happy Trading\n";
    }
    else{
        cout << "Invalid Choice\n";
    }
}

void print_data(string name, string exchange, string currency, float open, float high, float low, float close, float volume, float change, float price){
    cout << "Generating Data....\n\n";
    cout << 
    "name: " << name << "\n" <<
    "exchange: " << exchange << "\n" <<
    "currency:" <<currency<<"\n"<<
    "Open price: " << open <<"\n" << 
    "High price: " << high<<"\n" <<
    "Low price: " << low <<"\n" <<
    "Close price: " << close << "\n" <<
    "Volume:" << volume << "\n" << 
    "Change: " << change << "\n" <<
    "Current:" << price <<"\n";  
}
