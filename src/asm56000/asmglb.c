/* Expression-language math wrappers from the original asmglb module. */
#include <math.h>

#include "asm56000.h"

double mth_atan(double x)
{
    return atan(x);
}

double mth_abs(double x)
{
    return fabs(x);
}

double mth_acos(double x)
{
    return acos(x);
}

double mth_asin(double x)
{
    return asin(x);
}

double mth_ceil(double x)
{
    return ceil(x);
}

double mth_cosh(double x)
{
    return cosh(x);
}

double mth_cos(double x)
{
    return cos(x);
}

double mth_floor(double x)
{
    return floor(x);
}

double mth_log10(double x)
{
    return log10(x);
}

double mth_log(double x)
{
    return log(x);
}

double mth_sin(double x)
{
    return sin(x);
}

double mth_sinh(double x)
{
    return sinh(x);
}

double mth_sqrt(double x)
{
    return sqrt(x);
}

double mth_tan(double x)
{
    return tan(x);
}

double mth_tanh(double x)
{
    return tanh(x);
}

double mth_exp(double x)
{
    return exp(x);
}

double mth_pow(double x, double y)
{
    return pow(x, y);
}

double mth_atan2(double y, double x)
{
    return atan2(y, x);
}
