import json
import sys

print("asdf")

raw_input = sys.argv[1] if len(sys.argv) > 1 else "{}"

try:
    d = json.loads(raw_input)
    if d.get("ok") and d.get("stations"):
        print("⛽ **LOCAL STATION PACKET** ⛽\n")
        
        for s in d["stations"]:
            if s.get("id") == "d7d11f7c-7833-4f9c-b17b-03c0049ff8d7" or s.get("brand", "").upper() == "AVIA":
                
                v_e5 = "€" + str(round(s['e5'], 3)) if isinstance(s.get('e5'), (int, float)) else "N/A"
                v_e10 = "€" + str(round(s['e10'], 3)) if isinstance(s.get('e10'), (int, float)) else "N/A"
                v_di = "€" + str(round(s['diesel'], 3)) if isinstance(s.get('diesel'), (int, float)) else "N/A"
                
                status = "🟢 OPEN" if s.get('isOpen') else "🔴 CLOSED"
                brand = str(s.get('brand', '-')).upper()
                name = str(s.get('name'))
                
                print("**" + brand + "** (" + name + ") | " + status)
                print("├─ E5:     `" + v_e5 + "`")
                print("├─ E10:    `" + v_e10 + "`")
                print("└─ Diesel: `" + v_di + "`\n")
                break
        else:
            print("⚠️ Target station not found within the local coordinate radius.")
    else:
        print("❌ API Error response payload validation check failed.")
except Exception as err:
    print("❌ Render Parse Error: " + str(err))
