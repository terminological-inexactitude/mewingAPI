import json
import urllib.request
import sys

# Static parameters for your primary station
station_id = "d7d11f7c-7833-4f9c-b17b-03c0049ff8d7"

# We pass your API key as an argument via the Discord prompt command string
api_key = sys.argv[1] if len(sys.argv) > 1 else "MISSING_KEY"

url = "https://tankerkoenig.de" + station_id + "&apikey=" + api_key

try:
    # Explicitly forge a standard browser User-Agent header to pass the security firewall
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    
    with urllib.request.urlopen(req) as response:
        raw_data = response.read().decode('utf-8')
        d = json.loads(raw_data)
        
        if d.get("ok") and d.get("station"):
            s = d["station"]
            print("⛽ **STATION STATUS** ⛽\n")
            
            # Safe extraction without f-string collisions with Euler's constant {e}
            v_e5 = "€" + str(round(s['e5'], 3)) if isinstance(s.get('e5'), (int, float)) else "N/A"
            v_e10 = "€" + str(round(s['e10'], 3)) if isinstance(s.get('e10'), (int, float)) else "N/A"
            v_di = "€" + str(round(s['diesel'], 3)) if isinstance(s.get('diesel'), (int, float)) else "N/A"
            
            status = "🟢 OPEN" if s.get('isOpen') else "🔴 CLOSED"
            brand = str(s.get('brand', '-')).upper()
            name = str(s.get('name'))
            
            print("**" + brand + "** (" + name + ") | " + status)
            print("├─ E5:     `" + v_e5 + "`")
            print("├─ E10:    `" + v_e10 + "`")
            print("└─ Diesel: `" + v_di + "`")
        else:
            print("❌ Tankerkönig API Error. Response was invalid.")
except Exception as err:
    print("❌ Runtime Connection Error: " + str(err))
