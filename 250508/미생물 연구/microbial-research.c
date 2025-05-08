#include <stdio.h>

#define MAX_N 15
#define MAX_Q 51
#define MAX_QUEUE 400

int dxy[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

typedef struct{
    int r;
    int c;
}rc;

int N;
int Q;
int G;

int Box[MAX_N][MAX_N];
int Temp_Box[MAX_N][MAX_N];

int GermSize[MAX_Q];
int checkQ[MAX_Q];

rc Queue[MAX_QUEUE];
int ql, qr;

void printGerm()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            printf("%2d ", Box[r][c]);
        }
        printf("\n");
    }
    printf("=============================\n");
}

void init()
{
    scanf("%d %d", &N, &Q);
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            Box[r][c] = 0;
        }
    }
    for (int i = 0; i <= Q; i++)
    {
        GermSize[i] = 0;
    }
}

void cleanTempBox()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            Temp_Box[r][c] = 0;
        }
    }
}

void inputGerm()
{
    int r1, c1, r2, c2;
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
    for (int r = r1; r < r2; r++)
    {
        for (int c = c1; c < c2; c++)
        {
            Box[r][c] = G;
        }
    }
}

void scanSize()
{
    for (int i = 0; i <= Q; i++)
    {
        GermSize[i] = 0;
    }
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Box[r][c] == 0)
                continue;
            GermSize[Box[r][c]]++;
        }
    }
}

int getConnSize(int gr, int gc)
{
    int size = 0;
    int germ = Box[gr][gc];
    int r, c, nr, nc;

    cleanTempBox();
    ql = qr = 0;

    Queue[qr].r = gr;
    Queue[qr].c = gc;
    qr++;
    Temp_Box[gr][gc] = 1;
    size++;

    while (qr > ql)
    {
        r = Queue[ql].r;
        c = Queue[ql].c;
        ql++;

        for (int d = 0; d < 4; d++)
        {
            nr = r + dxy[d][0];
            nc = c + dxy[d][1];

            if (nr < 0 || nr >= N)
                continue;
            if (nc < 0 || nc >= N)
                continue;

            if (Box[nr][nc] != germ)
                continue;
            if (Temp_Box[nr][nc])
                continue;

            Queue[qr].r = nr;
            Queue[qr].c = nc;
            qr++;
            Temp_Box[nr][nc] = 1;
            size++;
        }
    }
    return size;
}

void removeGerm(int germ)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Box[r][c] == germ)
                Box[r][c] = 0;
        }
    }
    GermSize[germ] = 0;
}

void checkConnect()
{
    int size = 0;

    for (int i = 0; i < MAX_Q; i++)
    {
        checkQ[i] = 0;
    }

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Box[r][c] == 0)
                continue;

            if (checkQ[Box[r][c]])
                continue;

            checkQ[Box[r][c]] = 1;

            size = getConnSize(r, c);
            if (size != GermSize[Box[r][c]])
                removeGerm(Box[r][c]);
        }
    }
}

int getTarget()
{
    int result = 0;

    for (int i = 1; i <= G; i++)
    {
        if (GermSize[i] > GermSize[result])
            result = i;
    }
    return result;
}

int validateAdjust(
    int targetG, 
    int r1, int c1, int r2, int c2, 
    int ar, int ac
)
{
    for (int r = 0; r < (r2 - r1 + 1); r++)
    {
        for (int c = 0; c < (c2 - c1 + 1); c++)
        {
            if (Box[r1 + r][c1 + c] != targetG)
                continue;
            if (Temp_Box[ar + r][ac + c])
                return 0;
        }
    }
    return 1;
}

void procAdjust(
    int targetG, 
    int r1, int c1, int r2, int c2, 
    int ar, int ac
)
{
    for (int r = 0; r < (r2 - r1 + 1); r++)
    {
        for (int c = 0; c < (c2 - c1 + 1); c++)
        {
            if (Box[r1 + r][c1 + c] != targetG)
                continue;
            
            Temp_Box[ar + r][ac + c] = targetG;
            Box[r1 + r][c1 + c] = 0;
        }
    }
}
void moveGerm(int targetG)
{
    int r1, c1, r2, c2;
    int ar, ac;

    // Phase1: get Size of Target Germ
    r1 = c1 = N;
    r2 = c2 = 0;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Box[r][c] == targetG)
            {
                if (r1 > r)
                    r1 = r;
                if (c1 > c)
                    c1 = c;
                if (r2 < r)
                    r2 = r;
                if (c2 < c)
                    c2 = c;
            }
        }
    }

    // Phase2: Get Adjust Movement of new box
    ar = ac = N;
    for (int r = 0; r < N; r++)
    {
        if (ar < N)
            break;
        if (r + (r2 - r1 + 1) > N)
            break;
        for (int c = 0; c < N; c++)
        {
            if (ac < N)
                break;
            if (c + (c2 - c1 + 1) > N)
                break;
                
            if (validateAdjust(targetG, r1, c1, r2, c2, r, c))
            {
                ar = r;
                ac = c;
                break;
            }
        }
    }
    if (ar >= N || ac >= N)
        return;
    
    // Phase3: Process Adjust
    procAdjust(targetG, r1, c1, r2, c2, ar, ac);
    GermSize[targetG] = 0;
}

void replaceBox()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            Box[r][c] = Temp_Box[r][c];
        }
    }
}

void adjustGerm()
{
    int targetG;
    cleanTempBox();

    while (targetG = getTarget())
    {
        moveGerm(targetG);
    }
    replaceBox();
}

int checkNearby(int gi, int gj)
{
    int r, c, nr, nc;
    int ir, ic;

    // Phase1: Get gi's location
    ir = ic = N;
    for (r = 0; r < N; r++)
    {
        if (ir < N)
            break;
        for (c = 0; c < N; c++)
        {
            if (ic < N)
                break;
            
            if (Box[r][c] == gi)
            {
                ir = r;
                ic = c;
                break;
            }
        }
    }

    // Phase2: Check Nearby
    cleanTempBox();
    ql = qr = 0;

    Queue[qr].r = ir;
    Queue[qr].c = ic;
    qr++;
    Temp_Box[ir][ic] = 1;

    while (qr > ql)
    {
        r = Queue[ql].r;
        c = Queue[ql].c;
        ql++;

        for (int d = 0; d < 4; d++)
        {
            nr = r + dxy[d][0];
            nc = c + dxy[d][1];

            if (nr < 0 || nr >= N)
                continue;
            if (nc < 0 || nc >= N)
                continue;

            if (Box[nr][nc] == gj)
                return 1;
            if (Box[nr][nc] != gi)
                continue;
            if (Temp_Box[nr][nc])
                continue;

            Queue[qr].r = nr;
            Queue[qr].c = nc;
            qr++;
            Temp_Box[nr][nc] = 1;
        }
    }
    return 0;
}

void reportGerm()
{
    int score = 0;

    for (int i = 1; i <= G; i++)
    {
        for (int j = i + 1; j <=G; j++)
        {
            if (checkNearby(i, j))
                score += GermSize[i] * GermSize[j];
        }
    }
    printf("%d\n", score);
}

int main() {
    init();
    for (G = 1; G <= Q; G++)
    {
        // Phase1
        inputGerm();
        scanSize();
        checkConnect();
        // Phase2
        adjustGerm();
        scanSize();
        // Phase3
        reportGerm();
        //printGerm();
    }
    return 0;
}