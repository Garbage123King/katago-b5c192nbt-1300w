def letter_to_index(letter, reverse=False):
    letters = "abcdefghijklmnopqrs"
    if reverse:
        letters = letters[::-1]
    return letters.index(letter)

def parse_moves(input_str):
    moves = []
    entries = input_str.strip().split(";")
    for entry in entries:
        if not entry.strip():
            continue
        color, coord = entry.strip()[0].lower(), entry.strip()[2:-1]
        x = letter_to_index(coord[0])  # 横坐标正常
        y = letter_to_index(coord[1], reverse=True)  # 纵坐标反过来
        moves.append((color, (y, x)))
    return moves

# 你的输入（略长，仅部分展示）
# 用vs code打开sgf，用正则表达式[WB]\[..\]匹配，然后按Alt_Enter复制
input_str = """B[qc];W[pp];B[cc];W[dp];B[dq];W[eq];B[cp];W[dr];B[cq];W[do];B[co];W[pn];B[dn];W[en];B[ep];W[eo];B[fp];W[er];B[em];W[dm];B[cn];W[fm];B[el];W[gn];B[go];W[fn];B[ho];W[gl];B[gr];W[hn];B[io];W[in];B[jo];W[kn];B[jn];W[jm];B[km];W[qe];B[jl];W[im];B[kl];W[ln];B[lp];W[nq];B[oc];W[oe];B[mq];W[ce];B[ec];W[dl];B[ek];W[dk];B[ej];W[dj];B[di];W[ci];B[ch];W[dh];B[ei];W[cj];B[dg];W[cg];B[eh];W[bh];B[hk]"""

moves = parse_moves(input_str)

# 输出前 10 个进行验证
for move in moves[:]:
    print(str(move) + ', ')
