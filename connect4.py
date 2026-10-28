import random
s = discord["storage"]["user"]
a = discord["variables"]["__argsString"].split()
N = chr(10)
W = 7
H = 6
DEPTH = 4
L = []
for r in range(H):
    for c in range(W):
        for dr, dc in ((0, 1), (1, 0), (1, 1), (1, -1)):
            q = [(r + k * dr, c + k * dc) for k in range(4)]
            if all(0 <= y < H and 0 <= x < W for y, x in q):
                L.append([y * W + x for y, x in q])
def win(b, p):
    return any(all(b[i] == p for i in l) for l in L)
def drop(b, c, p):
    for r in range(H - 1, -1, -1):
        if b[r * W + c] == " ":
            n = b[:]
            n[r * W + c] = p
            return n
    return None
def score(b):
    t = 0
    for l in L:
        v = [b[i] for i in l]
        o = v.count("O")
        x = v.count("X")
        if not (o and x):
            t += (0, 1, 4, 20)[o] - (0, 1, 4, 20)[x]
    return t + 3 * sum(1 for r in range(H) if b[r * W + 3] == "O")
def mm(b, d, al, be, turn):
    if win(b, "O"):
        return 1000 + d
    if win(b, "X"):
        return -1000 - d
    moves = [c for c in (3, 2, 4, 1, 5, 0, 6) if b[c] == " "]
    if not moves:
        return 0
    if d == 0:
        return score(b)
    if turn == "O":
        v = -9999
        for c in moves:
            v = max(v, mm(drop(b, c, "O"), d - 1, al, be, "X"))
            al = max(al, v)
            if al >= be:
                break
        return v
    v = 9999
    for c in moves:
        v = min(v, mm(drop(b, c, "X"), d - 1, al, be, "O"))
        be = min(be, v)
        if al >= be:
            break
    return v
def bot(b):
    cs = [c for c in range(W) if b[c] == " "]
    sc = [mm(drop(b, c, "O"), DEPTH - 1, -9999, 9999, "X") for c in cs]
    return drop(b, random.choice([c for c, v in zip(cs, sc) if v == max(sc)]), "O")
def show(b):
    k = chr(65039) + chr(8419)
    sym = (chr(9898), chr(128308), chr(128993))
    rows = ["".join(sym[" XO".index(b[r * W + c])] for c in range(W)) for r in range(H)]
    print("```" + N + "".join(str(i) + k for i in range(1, W + 1)) + N + N.join(rows) + N + "```")
def end(msg):
    s["c4"] = "E" * (W * H)
    print(msg)
v = s.get("c4", "")
if len(v) != W * H or set(v) - set("EXO"):
    v = "E" * (W * H)
b = [" " if ch == "E" else ch for ch in v]
if a == ["clear"]:
    end("Board cleared!")
elif len(a) == 1 and a[0] in ("1", "2", "3", "4", "5", "6", "7"):
    n = drop(b, int(a[0]) - 1, "X")
    if n is None:
        print("That column is full!")
        show(b)
    else:
        b = n
        if win(b, "X"):
            show(b)
            end("YOU WIN!")
        elif " " not in b:
            show(b)
            end("It's a tie!")
        else:
            b = bot(b)
            show(b)
            if win(b, "O"):
                end("YOU LOSE!")
            elif " " not in b:
                end("It's a tie!")
            else:
                s["c4"] = "".join("E" if ch == " " else ch for ch in b)
else:
    print("Invalid input! Use a column number from 1 to 7, or clear")
