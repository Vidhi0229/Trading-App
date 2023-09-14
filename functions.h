#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <jsoncpp/json/json.h>

void ProfitLoss(float open, float close, std::string name);
void wantTransact(std::string ans, int amount, float price);
void print_data(std::string name, std::string exchange, std::string currency, float open, float high, float low, float close, float volume, float change, float price);

#endif // FUNCTIONS_H
