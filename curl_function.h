#ifndef CURL_FUNCTIONS_H
#define CURL_FUNCTIONS_H

#include <string>
#include <jsoncpp/json/json.h>

std::string get_price(const std::string& ticker_symbol, const std::string& api);
Json::Value get_stock_quote(const std::string& ticker_symbol, const std::string& api);

#endif // CURL_FUNCTIONS_H
