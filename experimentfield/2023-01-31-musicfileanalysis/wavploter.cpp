#include <stdio.h>
#include "complexnumber.h"
short data[100000000];
short datainverse[100000000];
int main()
{
    int c;
    int pose = 4;
    int len = 0;

    FILE *wavnptfile;
    wavnptfile = fopen("test.wav", "r");
    fseek(wavnptfile, 4, SEEK_SET);
    fread(&len, 4, 1, wavnptfile);
    printf("%d\n", len);

    fseek(wavnptfile, 8, SEEK_SET);
    fread(data, 1, len, wavnptfile);
    /*
    for (int i = len / 4 - 3; i < len / 4; i++)
    {
        printf("%x\n", data[i]);
    }
    */
    fclose(wavnptfile);

    FILE *f;
    f = fopen("comnum900-2", "w");
    fprintf(f, "%d 0.005 %lf\n", 400, 1.0 / 255);
    for (int i = 0; i < len; i++)
    {
        datainverse[i] = data[len - 1 - i];
        complexnumber cda(i - 90200, data[i], 0);
        if (i >= 90001 && i <= 90400)
        {
            cda.fprint(f, 0);
            fprintf(f, "\n");
        }
    }
    fclose(f);

    FILE *wavopt;
    wavopt = fopen("tt.wav", "ab");
    fwrite(datainverse, 4, len / 4, wavopt);
    fclose(wavopt);

    return 0;
}
