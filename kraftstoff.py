import urllib.request, urllib.parse, json
g=lambda u: json.loads(urllib.request.urlopen(u,timeout=5).read())
q="".join(c for c in """{args}""" if c.isalnum() or c in " -").strip()
if not q:
    print("Usage: .t fuel <city>")
else:
    r=g("https://geocoding-api.open-meteo.com/v1/search?count=1&countryCode=DE&name="+urllib.parse.quote(q)).get("results")
    if not r:
        print("City not found (Germany only)")
    else:
        c=r[0]
        d=g("https://creativecommons.tankerkoenig.de/json/list.php?lat=%s&lng=%s&rad=5&type=all&apikey=84c7c365-1767-4614-a8d1-10ee0c3e37d8" % (c["latitude"],c["longitude"]))
        f=lambda x: "%.3f" % x if x else "n/a"
        print("**Fuel near %s**" % c["name"])
        for s in d["stations"][:8]:
            print("%s **%s** (%.1f km) E5 %s | E10 %s | D %s" % ("🟢" if s["isOpen"] else "🔴",s["name"],s["dist"],f(s["e5"]),f(s["e10"]),f(s["diesel"])))
