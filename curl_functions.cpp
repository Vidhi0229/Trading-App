#include "curl_function.h"
#include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;


// Callback function for cURL to handle the response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string get_price(const std::string& ticker_symbol, const std::string& api) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return "";
    }

    // Set up the URL
    std::string url = "https://api.twelvedata.com/price?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    std::string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        return "";
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        std::cerr << "Failed to parse JSON: " << errors << std::endl;
        delete reader;
        return "";
    }
    delete reader;

    // Extract and return the price
    std::string price = root["price"].asString();
    return price;
}

Json::Value get_stock_quote(const std::string& ticker_symbol, const std::string& api) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL." << std::endl;
        return Json::Value(); // Return an empty JSON value on error
    }

    // Set up the URL
    std::string url = "https://api.twelvedata.com/quote?symbol=" + ticker_symbol + "&apikey=" + api;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Create a string to store the JSON response
    std::string jsonResponse;

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        return Json::Value(); // Return an empty JSON value on error
    }

    // Clean up cURL
    curl_easy_cleanup(curl);

    // Parse the JSON data using JsonCpp
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errors;
    if (!reader->parse(jsonResponse.c_str(), jsonResponse.c_str() + jsonResponse.size(), &root, &errors)) {
        std::cerr << "Failed to parse JSON: " << errors << std::endl;
        delete reader;
        return Json::Value(); // Return an empty JSON value on error
    }
    delete reader;

    return root;
}
