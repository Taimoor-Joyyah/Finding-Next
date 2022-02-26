#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long fact(long long z);
long long newfunc(long long n, long long m);
long long ratio(long long num, long long den, long long tf, long long *numo, long long *deno);
int main(int argc, char *argv[])
{
    long long a, b, c, d, dx, e, f, x, y, tn, td;
    long long arr[100][100], cn[100], cd[100];
    printf("Next Value Limit = ");
    long long nextl, factd;
    scanf("%lld", &nextl);
    char end;
    b = c = 1;
    while(end != 'e')
    {
        a = 1;
        if(c == 1)
        {
            printf("Enter First Value = ");
            scanf("%lld", &arr[a][c]);
            c++;
        }
        printf("Enter Next  Value = ");
        scanf("%lld", &arr[a][c]);
        a = 2, b = 1;
        for(a = 2; a <= c; ++a)
        for(b = 1; b <= c - a + 1; ++b)
                arr[a][b] = arr[a-1][b+1] - arr[a-1][b];
        for(y = b; y <= c + nextl; ++y)
        {
            for(x = a - 1; x >= 1; --x)
            {
                arr[x][y] = arr[x+1][y-1] + arr[x][y-1];
                ++y;
            }
            x += c;
            y -= c;
        }
        a = 1, b = 1;
        for(a = 1; a <= c + nextl; a++)
        {
            for(b = 1; b <= c + nextl - a + 1; b++)
                printf("%lld\t", arr[a][b]);
            printf("\n");
        }
        f = c - 1;
        for(d = f; d >= 0; d--)
        {
            if(d == f)
            {
                cn[f] = arr[f+1][1];
                cd[f] = fact(f);
                continue;
            }
            if(d == 0)
            {
                cn[0] = arr[1][1];
                cd[0] = 1;
                continue;
            }
            cd[d] = fact(d) * cd[d+1];
            cn[d] = arr[d+1][1] * cd[d+1];
            for(e = 1; e <= f - d; e++)
            {
                dx = f - e + 1;
                cn[d] -= ((cd[d+1] / cd[dx]) * cn[dx] * newfunc(d, dx));
            }
        }
        printf("\n");
        for(d = f; d >= 0; d--)
        {
            if(cn[d] < 0)
            {
                ratio(-cn[d], cd[d], f, &tn, &td);
                tn = -tn;
            }
            else
            {
                ratio(cn[d], cd[d], f, &tn, &td);
            }
            cn[d] = tn;
            cd[d] = td;
            if(tn == 0)
            {
                continue;
            }
            if(tn < 0 || d == f)
            {
                printf("%lld", tn);
            }
            else
            {
                printf("+%lld", tn);
            }
            if(d == 1)
            {
                printf("x");
            }
            else if(d > 0)
            {
                printf("x^%lld", d);
            }
            if(td > 1)
            {
                printf("/%lld", td);
            }
        }
        printf("\n");
        c++;
        /*printf("Enter e to End = ");
        end = getche();*/
        printf("\n");
    }
    return 0;
}
long long newfunc(long long n, long long m)
{
    long long fx = 0, k, sg;
    for(k = 0; k <= n - 1; ++k)
    {
        if(k == 0)
        {
            sg = 1;
        }
        else
        {
            sg *= -1;
        }
        fx += (sg * pow(n - k, m) * (fact(n) / (fact(k) * fact(n - k))));
    }
    return(fx);
}
long long fact(long long z)
{
    if(z == 0)
    {
        return(1);
    }
    long long f = 1, j;
    for (j = 1; j <= z; j++)
    {
        f *= j;
    }
    return(f);
}
long long ratio(long long num, long long den, long long tf, long long *numo, long long *deno)
{
    long long i;
    long long n = num,d = den;
    if(d == n)
    {
        *numo = 1;
        *deno = 1;
        return 1;
    }
    for(i = 2; i <= tf; ++i)
        if(n % i == 0 && d % i == 0)
        {
            n /= i;
            d /= i;
            --i;
        }
    *numo = n;
    *deno = d;
    return 1;
}
