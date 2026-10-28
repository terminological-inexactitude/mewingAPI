import random
s = discord["storage"]["user"]
a = discord["variables"]["__argsString"].split()
N = chr(10)
L = [(0,1,2),(3,4,5),(6,7,8),(0,3,6),(1,4,7),(2,5,8),(0,4,8),(2,4,6)]
def w(b, p):
    return any(all(b[i] == p for i in l) for l in L)
def show(b):
    n = [k + chr(65039) + chr(8419) for k in "123"]
    t = chr(8201)
    rows = [n[i] + " " + " | ".join(b[3*i:3*i+3]) for i in range(3)]
    print("```" + N + "   " + n[0] + " " + t + n[1] + " " + t + n[2] + N + (N + "  ---+---+---" + N).join(rows) + N + "```")
def end(msg):
    s["myvar2"] = "E" * 9
    print(msg)
def bot(b):
    e = [i for i in range(9) if b[i] == " "]
    if not e:
        return
    for p in "OX":
        for i in e:
            b[i] = p
            hit = w(b, p)
            b[i] = " "
            if hit:
                b[i] = "O"
                return
    b[4 if b[4] == " " else random.choice(e)] = "O"
v = s.get("myvar2", "")
if len(v) != 9 or set(v) - set("EXO"):
    v = "E" * 9
b = [" " if c == "E" else c for c in v]
if a == ["clear"]:
    end("Board cleared!")
elif len(a) == 2 and all(x in ("1", "2", "3") for x in a):
    i = 3 * (int(a[0]) - 1) + int(a[1]) - 1
    if b[i] != " ":
        print("That spot is already occupied by a " + b[i] + "!")
        show(b)
    else:
        b[i] = "X"
        if w(b, "X"):
            show(b)
            end("YOU WIN!")
        else:
            bot(b)
            show(b)
            if w(b, "O"):
                end("YOU LOSE!")
            elif " " not in b:
                end("It's a tie!")
            else:
                s["myvar2"] = "".join("E" if c == " " else c for c in b)
else:
    print("Invalid input format! Use 'row' 'column'")
