import random, string
WORDS = """python discord keyboard circuit voltage resistor capacitor firmware compiler pointer register
interrupt bootloader oscillator transistor microchip solder breadboard antenna sensor battery current signal
memory kernel thread socket packet router binary syntax variable function library network backup cursor
button window monitor laptop server cloud pixel cookie banner castle dragon wizard knight goblin treasure
pirate island volcano jungle desert glacier harbor lantern compass anchor voyage journey mystery puzzle
riddle shadow thunder lightning rainbow blizzard meadow orchard garden bridge tunnel mountain valley river
forest canyon planet galaxy comet rocket orbit meteor eclipse astronaut telescope gravity photon quantum
magnet crystal diamond emerald copper silver bronze guitar piano violin trumpet melody rhythm harmony
chorus circus theater painter sculpture bicycle tractor submarine lighthouse windmill campfire pancake
chocolate cinnamon pumpkin blueberry sandwich cheese lemonade penguin giraffe elephant dolphin octopus
butterfly hedgehog squirrel kangaroo flamingo""".split()
MAX = 6
s = discord["storage"]["user"]
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
