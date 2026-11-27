import random, string
WORDS = """circuit voltage current resistor capacitor inductor transistor diode rectifier signal oscillator breadboard sensor battery memory router binary firmware pointer register variable function network 
garden bridge motorway tunnel window harbor lighthouse windmill 
jester wizard alchemist sorcerer privateer inquisitor executioner 
island volcano prairie jungle desert glacier forest mountain valley riverbed canyon meadow orchard 
cloud thunderbolt lightning rainbow blizzard fog 
lantern compass campfire anchor guillotine shadow puzzle journey mystery riddle voyage 
trousers shirt button cape parka bracelet hat kilt 
planet galaxy comet rocket orbit satellite meteor shuttle astronaut extraterrestrial glider telescope syzygy equinox eclipse solstice azimuth 
gravity photon quantum magnet ultrasonic 
crystal diamond emerald copper silver bronze platinum quicksilver 
bagpipe theremin guitar piano cello violin trumpet trombone melody rhythm harmony chorus 
opera theater circus painter sculpture poetry 
tractor lorry diesel bicycle yellow submarine zeppelin 
pickle lemon waffle cake pancake chocolate cinnamon pumpkin blueberry sandwich cheese lemonade coffee sausage peanut 
birdwatching fishing beekeeping hunting whittling crocheting 
penguin giraffe elephant dolphin octopus butterfly hedgehog squirrel kangaroo flamingo gerbil""".split()
MAX = 6
s = discord["storage"]["channel"]
a = discord["variables"]["__argsString"].lower().split()
N = chr(10)
def art(m):
    h = "O" if m > 0 else " "
    t = "|" if m > 1 else " "
    l = "/" if m > 2 else " "
    r = chr(92) if m > 3 else " "
    x = "/" if m > 4 else " "
    y = chr(92) if m > 5 else " "
    return N.join(("  +---+", "  |   |", "  " + h + "   |", " " + l + t + r + "  |", " " + x + " " + y + "  |", "      |", "======="))
def wrong(w, t):
    return [x for x in t if len(x) > 1 or x not in w]
def show(w, t, msg):
    wr = wrong(w, t)
    word = " ".join(c if c in t else "_" for c in w)
    print(msg + N + "```" + N + art(len(wr)) + N + N + word + N + N + "Wrong (" + str(len(wr)) + "/" + str(MAX) + "): " + " ".join(wr) + N + "```")
def finish(w, t, msg):
    s.pop("hw", None)
    s.pop("hg", None)
    show(w, t + list(w), msg)
def new(w, pre):
    nw = random.choice([x for x in WORDS if x != w])
    s["hw"] = nw
    s.pop("hg", None)
    show(nw, [], pre + "New game! The word has " + str(len(nw)) + " letters.")
w = s.get("hw", "")
if not (w.isalpha() and w.islower()):
    w = ""
t = s.get("hg", "").split()
if a == ["new"]:
    new(w, "The word was " + w + "." + N if w else "")
elif not a:
    if w:
        show(w, t, "Game in progress.")
    else:
        new(w, "")
elif len(a) == 1 and set(a[0]) <= set(string.ascii_lowercase):
    g = a[0]
    if not w:
        print("No game running. Use the tag without arguments to start one.")
    elif g in t:
        show(w, t, "You already tried " + g + ".")
    elif g == w:
        finish(w, t, "YOU WIN! The word was " + w + ".")
    else:
        t = t + [g]
        if len(g) == 1 and g in w:
            if all(c in t for c in w):
                finish(w, t, "YOU WIN! The word was " + w + ".")
            else:
                s["hg"] = " ".join(t)
                show(w, t, "Yes, " + g + " is in the word!")
        elif len(wrong(w, t)) >= MAX:
            finish(w, t, "YOU LOSE! The word was " + w + ".")
        else:
            s["hg"] = " ".join(t)
            show(w, t, ("No " + g + " in the word." if len(g) == 1 else g + " is not the word."))
else:
    print("Invalid input! Guess one letter or a whole word, or use new")
