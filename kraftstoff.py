import json
import sys

# NotSoBot passes arguments via sys.argv. 
# arg1 = Raw API Response payload string text
raw_data = sys.argv[1] if len(sys.argv) > 1 else "{}"

try:
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
        print("❌ API Error response payload check.")
except Exception as err:
    print("❌ Render Parse Error: " + str(err))
