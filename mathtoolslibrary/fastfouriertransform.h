#ifndef FASTFOURIERTRANSFORM_H
#define FASTFOURIERTRANSFORM_H
#include "complexmatrix.h"
#include "complexnumber.h"
#include <math.h>
#define PI acos(-1)
complexmatrix fastfouriertransform_of_power_two(complexmatrix P, int opt)
{
    long long N = P.r;
    if (N == 1)
    {
        return P;
    }
    complexnumber zeta(1, opt * 2.0 * PI / N, 1);
    complexmatrix Pe(N / 2, 1), Po(N / 2, 1);
    for (int i = 1; i <= N / 2; i++)
    {
        Pe.dt[i][1] = P.dt[2 * i - 1][1];
        Po.dt[i][1] = P.dt[2 * i][1];
    }
    complexmatrix ye = fastfouriertransform_of_power_two(Pe, opt);
    complexmatrix yo = fastfouriertransform_of_power_two(Po, opt);
    complexmatrix y(N, 1);
    for (int i = 1; i <= N / 2; i++)
    {
        complexnumber power_i(i - 1, 0, 0);
        y.dt[i][1] = ye.dt[i][1] + (zeta ^ power_i) * yo.dt[i][1];
        y.dt[i + N / 2][1] = ye.dt[i][1] - (zeta ^ power_i) * yo.dt[i][1];
    }
    return y;
}
complexmatrix fastfouriertransform(complexmatrix P, int opt)
{
    if (P.r == 0)
    {
        printf("fastfouriertransformERROR:you have input a null matrix\n");
        return P;
    }
    long long N = exp2(ceil(log2(P.r)));
    complexmatrix PP(N, 1);
    for (int i = 1; i <= P.r; i++)
    {
        PP.dt[i][1] = P.dt[i][1];
    }
    printf("we are deal with:\n");
    PP.print(0);
    return fastfouriertransform_of_power_two(PP, opt);
}
#endif
