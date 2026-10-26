import urllib.request, json, sys

try:
    url = f"https://tankerkoenig.de{K}"
    req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
    with urllib.request.urlopen(req) as r:
        data = json.loads(r.read().decode())
    
    if not data.get("ok"):
        print(f"❌ API Error. Response: {data}")
    else:
        print("⛽ **Rütenbrock Border Fuel Prices** 🇩🇪\n```\nBrand      | Status | E5    | E10\n-----------------------------------")
        for s in data.get("stations", []):
            brand = (s.get("brand", "Unknown")[:10]).ljust(10)
            status = "OPEN  " if s.get("isOpen") else "CLOSED"
            print(f"{brand} | {status} | €{s.get('e5'):.3f} | €{s.get('e10'):.3f}")
        print("```")
except Exception as e:
    print(f"❌ Python Exception: {type(e).__name__} - {str(e)}")
