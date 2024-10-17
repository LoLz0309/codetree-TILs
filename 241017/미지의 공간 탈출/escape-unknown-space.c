#include <stdio.h>

#define MAX_N 20
#define MAX_M 10
#define MAX_F 10
#define MAX_TURN 400

const dx[4] = { 1, -1, 0, 0 };
const dy[4] = { 0, 0, 1, -1 };

typedef struct dxy {
    int d;
    int x;
    int y;
} DXY;

typedef struct xy {
    int x;
    int y;
} XY;

typedef struct virus {
    int r;
    int c;
    int d;
    int v;
} VIRUS;

int N, M, F;
int gSpace[MAX_N][MAX_N];
int gWall[5][MAX_M][MAX_M];
VIRUS gVirus[MAX_F];

DXY gStartWall;
DXY gExitWall;
XY gStartSpace;
XY gExitSpace;

int gTurns;

void init() {
    scanf("%d %d %d", &N, &M, &F);
    
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            scanf("%d ", &gSpace[y][x]);
        }
    }

    for (int d = 0; d < 5; d++) {
        for (int y = 0; y < M; y++) {
            for (int x = 0; x < M; x++) {
                scanf("%d ", &gWall[d][y][x]);
            }
        }
    }

    for (int i = 0; i < F; i++) {
        scanf("%d %d %d %d", &gVirus[i].r, &gVirus[i].c, &gVirus[i].d, &gVirus[i].v);
    }

    gTurns = 0;
#if 0
    printf("%d %d %d\n", N, M, F);
    
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            printf("%d ", gSpace[y][x]);
        }
        printf("\n");
    }
    printf("\n");

    for (int d = 0; d < 5; d++) {
        for (int y = 0; y < M; y++) {
            for (int x = 0; x < M; x++) {
                printf("%d ", gWall[d][y][x]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < F; i++) {
        printf("%d %d %d %d\n", gVirus[i].r, gVirus[i].c, gVirus[i].d, gVirus[i].v);
    }
#endif
}

void searchStartExit() {
    /*
    DXY gStartWall;
    DXY gExitWall;
    */
    int d;
    XY wall[2];

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (gSpace[y][x] == 4) {
                gExitSpace.y = y;
                gExitSpace.x = x;
                continue;
            }

            if (gSpace[y][x] == 0) {
                for (d = 0; d < 4; d++) {
                    int ny = y + dy[d];
                    int nx = x + dx[d];

                    if (ny < 0 || ny >= N) continue;
                    if (nx < 0 || nx >= N) continue;

                    if (gSpace[ny][nx] == 3) {
                        gStartSpace.y = y;
                        gStartSpace.x = x;
                    }
                }
            }
        }
    }

    d = 4;
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < M; x++) {
            if (gWall[d][y][x] == 2) {
                gStartWall.d = 4;
                gStartWall.y = y;
                gStartWall.x = x;
            }
        }
    }




#if 1
    printf("%d %d\n", gStartSpace.y, gStartSpace.x);
    printf("%d %d\n", gExitSpace.y, gExitSpace.x);
    printf("%d %d %d\n", gStartWall.d, gStartWall.y, gStartWall.x);
    printf("%d %d %d\n", gExitWall.d, gExitWall.y, gExitWall.x);
#endif
}

void calcWall() {

}

void applyVirus() {

}

int calcSpace() {
    return -1;
}

int main() {
    int result = -1;
    init();
    searchStartExit();
    calcWall();
    applyVirus();
    result = calcSpace();
    printf("%d", result);
    return 0;
}