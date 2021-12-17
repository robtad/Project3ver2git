#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
const int MAX = 24;
typedef struct plane
{
    int PI;
    int pNo;
    int LTR;
    int LT;
    int DLY;
    int TOT;
} plane;

plane planeL[24];

void writeToFile()
{

    FILE *file;
    file = fopen("output.txt", "w");
    fprintf(file, "PriorityID   PlaneNo   ReqLandingTime   LandingTime     Delay   TakeOffTime\n");

    for (int i = 0; i < 10; i++)
    {
        i *= 13;
        planeL[i].PI = i;
        planeL[i].pNo = i;
        planeL[i].LTR = i;
        planeL[i].LT = i;
        planeL[i].DLY = i;
        planeL[i].TOT = i;
        //   fwrite(&planeL[i], sizeof(planeL[i]), 1, file);
        //fprintf(file, "%d\t%d\t%d\t%d\t%d\t%d\n", planeL[i].PI, planeL[i].pNo, planeL[i].pNo, planeL[i].LTR, planeL[i].LT, planeL[i].DLY);
        fprintf(file, "%*d%*d%*d%*d%*d%*d\n", 7, planeL[i].PI, 11, planeL[i].pNo, 13, planeL[i].pNo, 15, planeL[i].LTR, 13, planeL[i].LT, 12, planeL[i].DLY);

        i /= 13;
    }
    fclose(file);
}

void readFromFile()
{
    FILE *file;
    file = fopen("output.txt", "r");
    int a, b, c, d, e, f;
    int i = 0;
    printf("\nPriorityID   PlaneNo   ReqLandingTime   LandingTime     Delay   TakeOffTime\n");
    fseek(file, 80, SEEK_SET); //to skip the first line which is a title line in the output.txt file

    while (i < 10)
    {
        // printf("\nPriorityID   PlaneNo   ReqLandingTime   LandingTime     Delay   TakeOffTime\n");

        fscanf(file, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
        printf("\n\n%*d%*d%*d%*d%*d%*d\n", 7, a, 11, b, 13, c, 15, d, 13, e, 12, f);
        i++;
    }
    fclose(file);
}
int main()
{

    writeToFile();
    readFromFile();

    return 0;
}