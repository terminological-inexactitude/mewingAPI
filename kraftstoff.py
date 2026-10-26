import urllib.request, json
i="YOUR-STATION-UUID"
u="https://creativecommons.tankerkoenig.de/json/detail.php?id="+i+"&apikey=YOUR-KEY"
s=json.loads(urllib.request.urlopen(u,timeout=5).read())["station"]
f=lambda x: "%.3f" % x if x else "n/a"
print("**%s** (%s) - %s" % (s["name"],s["brand"],"OPEN" if s["isOpen"] else "CLOSED"))
print("E5 %s | E10 %s | Diesel %s" % (f(s["e5"]),f(s["e10"]),f(s["diesel"])))
