from collections import deque

dxy = ((0, 1), (0, -1), (1, 0), (-1, 0))

K, M = 0, 0
ground = [[0] * 5 for _ in range(5)]
wall = [0]

def debug():
    for g in ground:
        print(*g)
    print("===========")

def init():
    global K, M, ground, wall
    K, M = map(int, input().split())
    ground = [list(map(int, input().split())) for _ in range(5)]
    wall = deque(map(int, input().split()))

def search():
    minx, miny, minr, maxscore = 5, 5, 4, 0

    for x in range(1, 4):
        for y in range(1, 4):
            for r in range(1, 4):
                rotate90(x, y)
                score = calculate()
                if score > maxscore:
                    minx, miny, minr, maxscore = x, y, r, score
                    continue
                elif score < maxscore:
                    continue
                
                if r < minr:
                    minx, miny, minr, maxscore = x, y, r, score
                    continue
                elif r > minr:
                    continue

                if y < miny:
                    minx, miny, minr, maxscore = x, y, r, score
                    continue
                elif y > miny:
                    continue

                if x < minx:
                    minx, miny, minr, maxscore = x, y, r, score
                    continue
                elif x > minx:
                    continue
            rotate90(x, y)

    for _ in range(minr):
        rotate90(minx, miny)

def rotate90(x, y):
    global ground
    tmp = [[0] * 3 for _ in range(3)]

    for dx in range(-1, 2):
        for dy in range(-1, 2):
            tmp[1 + dx][1 + dy] = ground[x - dy][y + dx]
    
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            ground[x + dx][y + dy] = tmp[1 + dx][1 + dy]

def calculate(d = False) -> int:
    global ground
    visited = [[0] * 5 for _ in range(5)]
    score = 0
    
    for sx in range(5):
        for sy in range(5):
            if visited[sx][sy]:
                continue
            value = ground[sx][sy]

            queue = deque()
            queue.append((sx, sy))
            visited[sx][sy] = 1

            tmpscore = 1
            tmpcombo = [(sx, sy)]
            while queue:
                x, y = queue.popleft()

                for dx, dy in dxy:
                    nx, ny = x + dx, y + dy
                    if not 0 <= nx < 5 or not 0 <= ny < 5:
                        continue
                    if visited[nx][ny]:
                        continue
                    if ground[nx][ny] != value:
                        continue

                    visited[nx][ny] = 1
                    queue.append((nx, ny))
                    tmpscore += 1
                    if d:
                        tmpcombo.append((nx, ny))

            if tmpscore < 3:
                continue
            
            score += tmpscore
            if d:
                for x, y in tmpcombo:
                    ground[x][y] = 0

    return score

def getscore() -> int:
    result = 0
    tmpscore = calculate(True)

    while tmpscore:
        result += tmpscore

        fillfromwall()
        tmpscore = calculate(True)

    return result

def fillfromwall():
    for y in range(5):
        for x in range(4, -1, -1):
            if ground[x][y] > 0:
                continue
            ground[x][y] = wall.popleft()
            

if __name__ == "__main__":
    init()

    for _ in range(K):
        search()
        res = getscore()
        if res:
            print(res, end=' ')
        else:
            exit()