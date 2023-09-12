import sys
import requests

if len(sys.argv) != 2:
    print("Usage: python fetch_stock_data.py <ticker>")
    sys.exit(1)

ticker = sys.argv[1]
api_key = "4cac4af5f73a405c9632e98cca7ef7f8"

def get_price(ticker_symbol, api):
    url = f"https://api.twelvedata.com/price?symbol={ticker_symbol}&apikey={api}"
    response = requests.get(url).json()
    price = response['price']
    return price

def get_stock_quote(ticker_symbol, api):
    url = f"https://api.twelvedata.com/quote?symbol={ticker_symbol}&apikey={api}"
    response = requests.get(url).json()
    return response

stock_data = get_stock_quote(ticker, api_key)
stock_price = get_price(ticker, api_key)

exchange = stock_data['exchange']
currency = stock_data['currency']
open_price = stock_data['open']
high_price = stock_data['high']
low_price = stock_data['low']
close_price = stock_data['close']
volume = stock_data['volume']
name = stock_data['name']
change = stock_data['change']
close = float(close_price)
opened = float(open_price)
priceValue = float(stock_price)

print(f"Stock Name: {name}\nExchange: {exchange}\nCurrency: {currency}\nOpen Price: {opened}\nHigh Price: {high_price}\nLow Price: {low_price}\nClose Price: {opened}\nVolume: {volume}\nchange: {change}\nCurrent Price: {priceValue}\n")

with open(f"{ticker}_data.txt", "w") as file:
    file.write(f"{priceValue}")
