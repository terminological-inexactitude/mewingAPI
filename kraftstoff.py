import urllib.request, json
i="YOUR-STATION-UUID"
u="https://creativecommons.tankerkoenig.de/json/prices.php?ids="+i+"&apikey=YOUR-KEY"
p=json.loads(urllib.request.urlopen(u,timeout=5).read())["prices"][i]
if p["status"]!="open":
    print("Station is closed")
else:
    print("E5 %.3f | E10 %.3f | Diesel %.3f" % (p["e5"],p["e10"],p["diesel"]))
