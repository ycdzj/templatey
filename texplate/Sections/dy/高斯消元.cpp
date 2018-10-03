//高斯消元
const int maxn=1e2+10;
int n,m,k,t;
int lcm(int x,int y){return x/__gcd(x,y)*y;}
int a[maxn][maxn];
int x[maxn];
bool free_x[maxn];
int free_num;
int Gauss(int equ,int var)
{
    int i, j, k;
    int max_r;
    int col;
    int ta, tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;
    for (col=0,k = 0; k < equ && col < var; k++, col++)
    {
        max_r = k;
        for (i = k + 1; i < equ; i++)
        {
            if (abs(a[i][col]) > abs(a[max_r][col])) max_r = i;
        }
        if (max_r != k)
        {
            for (j = k; j < var + 1; j++) swap(a[k][j], a[max_r][j]);
        }
        if (a[k][col] == 0)
        {
            k--; continue;
        }
        for (i = k + 1; i < equ; i++)
        {
            if (a[i][col] != 0)
            {
                LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                ta = LCM / abs(a[i][col]), tb = LCM / abs(a[k][col]);
                if (a[i][col] * a[k][col] < 0) tb = -tb;
                for (j = col; j < var + 1; j++)
                {
                    a[i][j] = a[i][j] * ta - a[k][j] * tb;
                }
            }
        }
    }
    for (i = k; i < equ; i++)
    {
        if (a[i][col] != 0) return -1;
    }
    if (k < var)
    {
        for (i = k - 1; i >= 0; i--)
        {
            free_x_num = 0;
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue;
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index];
            free_x[free_index] = 0;
        }
        return var - k;
    }
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2;
        x[i] = temp / a[i][i];
    }
    return 0;
}