import urllib.request, json
print("asdf")

i="d7a446f0-ab85-4bcb-afca-51333dd2da09";targetStationId = "d7a446f0-ab85-4bcb-afca-51333dd2da09"
u="https://creativecommons.tankerkoenig.de/json/detail.php?id="+i+"&apikey=84c7c365-1767-4614-a8d1-10ee0c3e37d8"
s=json.loads(urllib.request.urlopen(u,timeout=5).read())["station"]
f=lambda x: "%.3f" % x if x else "n/a"
print("**%s** (%s) - %s" % (s["name"],s["brand"],"OPEN" if s["isOpen"] else "CLOSED"))
print("E5 %s | E10 %s | Diesel %s" % (f(s["e5"]),f(s["e10"]),f(s["diesel"])))
