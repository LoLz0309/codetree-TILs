#include <stdio.h>

#define MAX_M 300

const int cdx[4] = { 0, 0, 1, -1 };
const int cdy[4] = { -1, 1, 0, 0 };

int k, m;
int map[5][5];
int wall[MAX_M];
int walln;

void debug(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("===============\n");
}

void init(){
    scanf("%d %d", &k, &m);
    for (int i = 0; i < 5; i++){
        scanf("%d %d %d %d %d\n", 
        &map[i][0], &map[i][1], &map[i][2], &map[i][3], &map[i][4]);
    }
    for (int i = 0; i < m; i++){
        scanf("%d ", &wall[i]);
    }
    walln = 0;
}

int getscore(){
    int visited[5][5] = { 0, };
    int queue[25][2] = { 0, };
    int qs, qf;
    int res = 0;

    for (int sx = 0; sx < 5; sx++){
        for (int sy = 0; sy < 5; sy++){
            if (visited[sx][sy]) continue;
            int ss = map[sx][sy];
            qs = 0; qf = 1;
            queue[0][0] = sx;
            queue[0][1] = sy;
            visited[sx][sy] = 1;

            while (qf > qs){
                int x = queue[qs][0];
                int y = queue[qs][1];
                ++qs;

                for (int d = 0; d < 4; d++){
                    int nx = x + cdx[d];
                    int ny = y + cdy[d];
                    if (nx < 0 || nx >= 5) continue;
                    if (ny < 0 || ny >= 5) continue;
                    if (visited[nx][ny])   continue;
                    if (map[nx][ny] != ss) continue;

                    queue[qf][0] = nx;
                    queue[qf][1] = ny;
                    ++qf;
                    visited[nx][ny] = 1;
                }
            }
            if (qf < 3) continue;
            res += qf;
        }
    }
    return res;
}

int rotate90(int x, int y){
    int tmpmap[3][3];
    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            tmpmap[1 + dx][1 + dy] = map[x + dx][y + dy];
        }
    }

    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            map[x + dx][y + dy] = tmpmap[1 - dy][1 + dx];
        }
    }
    return getscore();
}

void rotate(){
    int resx, resy, resr;
    int ress = -1;

    for (int x = 1; x < 4; x++){
        for (int y = 1; y < 4; y++){
            for (int r = 1; r < 4; r++){
                int s = rotate90(x, y);
                // printf("%d, %d, %3d : %d\n", x, y, r * 90, s);
                // debug();
                if (s > ress){
                    ress = s; 
                    resr = r; 
                    resx = x; 
                    resy = y; 
                    continue;
                }
                if (s < ress) continue;

                if (r < resr){
                    ress = s; 
                    resr = r; 
                    resx = x; 
                    resy = y; 
                    continue;
                }
                if (r > resr) continue;
                
                if (x < resx){
                    ress = s; 
                    resr = r; 
                    resx = x; 
                    resy = y; 
                    continue;
                }
                if (x > resx) continue;
                
                if (y < resy){
                    ress = s; 
                    resr = r; 
                    resx = x; 
                    resy = y; 
                    continue;
                }
                if (y > resy) continue;
            }
            rotate90(x, y);
        }
    }
    // printf("res: (%d, %d) - %d : %d\n", resx, resy, resr, ress);
    for (int r = 0; r < resr; r++){
        rotate90(resx, resy);
    }
    // debug();
}

int remconn(){
    int queue[25][2] = { 0, };
    int qs, qf;
    int res = 0;

    for (int sx = 0; sx < 5; sx++){
        for (int sy = 0; sy < 5; sy++){
            if (!map[sx][sy]) continue;
            int ss = map[sx][sy];
            qs = 0; qf = 1;
            queue[0][0] = sx;
            queue[0][1] = sy;
            map[sx][sy] = 0;

            while (qf > qs){
                int x = queue[qs][0];
                int y = queue[qs][1];
                ++qs;

                for (int d = 0; d < 4; d++){
                    int nx = x + cdx[d];
                    int ny = y + cdy[d];
                    if (nx < 0 || nx >= 5) continue;
                    if (ny < 0 || ny >= 5) continue;
                    if (map[nx][ny] != ss) continue;

                    queue[qf][0] = nx;
                    queue[qf][1] = ny;
                    ++qf;
                    map[nx][ny] = 0;
                }
            }
            if (qf < 3) {
                for (int q = 0; q < qf; q++){
                    map[queue[q][0]][queue[q][1]] = ss;
                }
                continue;
            }
            res += qf;
        }
    }
    // debug();
    return res;
}

void restore(){
    for (int y = 0; y < 5; y++){
        for (int x = 4; x >= 0; x--){
            if (map[x][y]) continue;
            map[x][y] = wall[walln++];
        }
    }
    // debug();
}

int getcontscore(){
    int prevwalln = walln;

    while (1){
        if (!remconn()) break;
        restore();
    }
    return walln - prevwalln;
}

int main() {
    int score;
    init();

    for (int t = 0; t < k; t++){
        rotate();
        score = getcontscore();
        if (score) 
            printf("%d ", score);
    }
    return 0;
}