import json
import os
import sys

print("testing")

api_key = str(API_TOKEN).strip()
station_id = "d7d11f7c-7833-4f9c-b17b-03c0049ff8d7"

url = "https://tankerkoenig.de" + station_id + "&apikey=" + api_key

command = 'curl -s -A "Mozilla/5.0" "' + url + '" > price.json'
os.system(command)

try:
    with open("price.json", "r", encoding="utf-8") as file:
        raw_data = file.read()
        
    d = json.loads(raw_data)
    if d.get("ok") and d.get("station"):
        s = d["station"]
        print("⛽ **STATION STATUS** ⛽\n")
        
        e5 = "€" + str(round(s['e5'], 3)) if isinstance(s.get('e5'), (int, float)) else "N/A"
        e10 = "€" + str(round(s['e10'], 3)) if isinstance(s.get('e10'), (int, float)) else "N/A"
        di = "€" + str(round(s['diesel'], 3)) if isinstance(s.get('diesel'), (int, float)) else "N/A"
        
        status = "🟢 OPEN" if s.get('isOpen') else "🔴 CLOSED"
        brand = str(s.get('brand', '-')).upper()
        name = str(s.get('name'))
        
        print("**" + brand + "** (" + name + ") | " + status)
        print("├─ E5:     `" + e5 + "`")
        print("├─ E10:    `" + e10 + "`")
        print("└─ Diesel: `" + di + "`")
    else:
        print("❌ API Error: Invalid data packet layout.")
except Exception as err:
    print("❌ Render Execution Error: " + str(err))
