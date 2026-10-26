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
        S=d["stations"][:8]
        f=lambda x: "%.3f" % x if x else "-"
        m=[]
        for n in ("e5","e10","diesel"):
            v=[s[n] for s in S if s["isOpen"] and s[n]]
            m.append(min(v) if len(v)>1 else None)
        k=lambda s,i,n: f(s[n]).rjust(6)+("*" if s["isOpen"] and s[n] and s[n]==m[i] else " ")
        o=["%-16s %7s %7s %7s %s" % ("Station","E5 ","E10 ","Diesel ","Status")]
        for s in S:
            o.append("%-16s %s %s %s %s" % (s["name"][:16],k(s,0,"e5"),k(s,1,"e10"),k(s,2,"diesel"),"open" if s["isOpen"] else "closed"))
        if any(x is not None for x in m):
            o.append("* = cheapest open")
        print("**Fuel near %s**" % c["name"])
        print(chr(96)*3+"\n".join(o)+chr(96)*3)
