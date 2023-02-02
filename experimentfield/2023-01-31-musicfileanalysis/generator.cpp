#include <stdio.h>
#include <math.h>
#define PI acos(-1)
short chr;
double phase, amplitude, c_frequency, e_frequency, g_frequency;
int lasttime;
int filelen;
double samplingrate;
double sharpcos(double x)
{
    return asin(cos(x)) / (PI / 2);
}
double fcos(double x)
{
    if (cos(x) > 0)
    {
        return 1;
    }
    if (cos(x) < 0)
    {
        return -1;
    }
    return 0;
}
int main()
{
    FILE *f;
    f = fopen("genfcosggg.wav", "ab");
    printf("%d\n", sizeof(chr));
    fprintf(f, "data");

    phase = 0; // phase between -PI~PI
    amplitude = 16000 / 3;
    c_frequency = 261.63;
    e_frequency = 329.63;
    g_frequency = 392.00;
    lasttime = 5;
    samplingrate = 47880;

    filelen = samplingrate * 2 * lasttime;

    printf("%x\n", filelen);
    fwrite(&filelen, 4, 1, f);
    // printf("%lf\n", fcos());

    for (int t = 0 * lasttime / 4; t < 4 * lasttime / 4; t++)
    {
        for (int s = 0; s < samplingrate; s++)
        {
            double tt = t + s / samplingrate;
            chr = amplitude * fcos(2 * PI * g_frequency * tt + phase) + amplitude * fcos(2 * PI * g_frequency * tt + phase) + amplitude * fcos(2 * PI * g_frequency * tt + phase);
            fwrite(&chr, 2, 1, f);
        }
    }
    for (int t = 1 * lasttime / 4; t < 0 * lasttime / 4; t++)
    {
        for (int s = 0; s < samplingrate; s++)
        {
            double tt = t + s / samplingrate;
            chr = amplitude * sharpcos(2 * PI * c_frequency * tt + phase) + amplitude * sharpcos(2 * PI * e_frequency * tt + phase) + amplitude * sharpcos(2 * PI * g_frequency * tt + phase);
            fwrite(&chr, 2, 1, f);
        }
    }
    for (int t = 2 * lasttime / 4; t < 0 * lasttime / 4; t++)
    {
        for (int s = 0; s < samplingrate; s++)
        {
            double tt = t + s / samplingrate;
            chr = amplitude * sharpcos(2 * PI * e_frequency * tt + phase) + amplitude * sharpcos(2 * PI * e_frequency * tt + phase) + amplitude * sharpcos(2 * PI * g_frequency * tt + phase);
            fwrite(&chr, 2, 1, f);
        }
    }
    for (int t = 3 * lasttime / 4; t < 0 * lasttime / 4; t++)
    {
        for (int s = 0; s < samplingrate; s++)
        {
            double tt = t + s / samplingrate;
            chr = amplitude * cos(2 * PI * g_frequency * tt + phase) + amplitude * cos(2 * PI * g_frequency * tt + phase) + amplitude * cos(2 * PI * g_frequency * tt + phase);
            fwrite(&chr, 2, 1, f);
        }
    }
    fclose(f);
    return 0;
}
