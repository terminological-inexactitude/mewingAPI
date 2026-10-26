import urllib.request, json
i="d7a446f0-ab85-4bcb-afca-51333dd2da09";targetStationId = "d7a446f0-ab85-4bcb-afca-51333dd2da09"
u="https://creativecommons.tankerkoenig.de/json/prices.php?ids="+i+"&apikey=84c7c365-1767-4614-a8d1-10ee0c3e37d8"
p=json.loads(urllib.request.urlopen(u,timeout=5).read())["prices"][i]
if p["status"]!="open":
    print("Station is closed")
else:
    print("E5 %.3f | E10 %.3f | Diesel %.3f" % (p["e5"],p["e10"],p["diesel"]))
