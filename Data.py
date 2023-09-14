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
data = stock_data['name']

with open(f"{ticker}_data.txt", "w") as file:
    file.write(f"{stock_data['name']},")
    file.write(f"{stock_data['exchange']},")
    file.write(f"{stock_data['currency']},")
    file.write(f"{stock_data['open']},")
    file.write(f"{stock_data['high']},")
    file.write(f"{stock_data['low']},")
    file.write(f"{stock_data['close']},")
    file.write(f"{stock_data['volume']},")
    file.write(f"{stock_data['change']},")
    file.write(f"{stock_price}")
