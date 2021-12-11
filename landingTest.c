#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const int MAX = 25;
typedef struct plane
{
    int priorityId;
    int planeNo;
    int landingTime;
    int delay;
} plane;
plane planeL[25];
plane planeP[28];

int front = -1;
int rear = -1;

void delayHandler4Full(plane p)
{
    for (int j = front; j <= rear; j++)
    {
        if (planeL[j].landingTime == planeL[rear + 1].landingTime)
        {
            if (planeL[j].priorityId == planeL[rear + 1].priorityId)
            {
                if (planeL[j].planeNo <= planeL[rear + 1].planeNo)
                {
                    printf("\nDaha once ayni saatte inis talep eden ucaktan daha\nyuksek onceliginiz"
                           "olmadigi icin,inis izni verilememektedir.");
                }
                else
                {
                    printf("\nUcak id'si %d olan ucagin ucak id onceligi daha once ayni"
                           "saatte inis talep eden %d \nucak id'li ucaktan yuksek oldugu icin"
                           "%d ucak id'li ucagin inis \nizni iptal edilmistir, inis icin Sabiha Gokcen"
                           "Havalimani\'na yonlendiriliyor...",
                           planeL[rear + 1].planeNo, planeL[j].planeNo, planeL[j].planeNo);
                    planeL[j] = planeL[rear + 1];
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", planeL[j].planeNo);
                }
            }
            else if (planeL[j].priorityId > planeL[rear + 1].priorityId)
            {
                printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                       "saatte inis talep eden %d oncelik id'li ucagin inis izni iptal edilmistir,\n inis icin Sabiha Gokcen"
                       "Havalimani\'na yonlendiriliyor...",
                       planeL[rear + 1].priorityId, planeL[j].priorityId);
                planeL[j] = planeL[rear + 1];
                printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", planeL[j].planeNo);
            }
            else //if priority id of the existing plane is smaller than the new plane
            {
                printf("\nDaha once ayni saatte inis talep eden ucaktan daha yuksek\n onceliginiz"
                       "olmadigi icin,inis izni verilememektedir.");
            }
        }
    }
    return;
}
void delayHandler(plane p)
{
    plane tempo;
    for (int i = front; i < rear; i++)
    {
        if (planeL[i].landingTime == p.landingTime)
        {
            if (planeL[i].priorityId == p.priorityId)
            {

                if (planeL[i].planeNo > p.planeNo) //if-else if
                {
                    if (planeL[i].delay < 3)
                    {
                        tempo = planeL[i];
                        planeL[i] = p;
                        planeL[rear] = tempo;
                        planeL[rear].landingTime += 1;
                        planeL[rear].delay += 1;
                        delayHandler(planeL[rear]);
                        //planeL[rear] = p;
                        //return;
                    }
                    else if (planeL[i].delay == 3) //if-else if
                    {
                        if (p.delay < 3)
                        {
                            planeL[rear].landingTime += 1;
                            planeL[rear].delay += 1;

                            delayHandler(planeL[rear]);
                            // planeL[rear] = p;
                            //return;
                        }
                        else if (p.delay == 3) //if-else if
                        {
                            printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                            rear -= 1;
                            return;
                        }
                        else
                        {
                            printf("\nError2.1: ");
                            printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                        }
                    }
                    else
                    {
                        printf("\nError2: ");
                        printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                    }
                }
                else // (planeL[i].planeNo < p.planeNo)//if -> else
                {
                    if (p.delay < 3)
                    {
                        planeL[rear].landingTime += 1;
                        planeL[rear].delay += 1;

                        delayHandler(planeL[rear]);
                        // planeL[rear] = p;
                        //return;
                    }
                    else if (p.delay == 3) //if-else if
                    {
                        printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                        rear -= 1;
                        return;
                    }
                    else
                    {
                        printf("\nError3.1: ");
                        printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                    }
                }
            }

            else if (planeL[i].priorityId < p.priorityId)
            {
                if (p.delay < 3)
                {
                    planeL[rear].landingTime += 1;
                    planeL[rear].delay += 1;

                    delayHandler(planeL[rear]);
                    //planeL[rear] = p;
                    // return;
                }
                else if (p.delay == 3) //if-else if
                {
                    printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                    rear -= 1;
                    return;
                }
                else
                {
                    printf("\nError4: ");
                    printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                }
            }

            else //if(planeL[i].priorityId>p.priorityId)
            {
                if (planeL[i].delay < 3)
                {
                    tempo = planeL[i];
                    planeL[i] = p;
                    planeL[rear] = tempo;
                    planeL[rear].landingTime += 1;
                    planeL[rear].delay += 1;

                    delayHandler(planeL[rear]);
                    //planeL[rear] = p;
                    //return;
                }
                else if (planeL[i].delay == 3) //if-else if
                {
                    if (p.delay < 3)
                    {
                        planeL[rear].landingTime += 1;
                        planeL[rear].delay += 1;

                        delayHandler(planeL[rear]);
                        //planeL[rear] = p;
                        // return;
                    }
                    else if (p.delay == 3) //if-else if
                    {
                        printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                        rear -= 1;
                        return;
                    }
                    else
                    {
                        printf("\nError5.1: ");
                        printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                    }
                }
                else
                {
                    printf("\nError5: ");
                    printf("%d    %d      %d      %d \n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                }
            }
        }
    }
    //printf("\n%d    %d      %d      %d \n ....inis izin talebi onaylanmistir! \n", p.priorityId, p.planeNo, p.landingTime, p.delay);

    //printf("\nrear=%d\n", rear);
    return;
}

bool isEmpty()
{
    if (front == -1 && rear == -1)
        return true;
    else
        return false;
}
bool isFull()
{
    if (rear == MAX - 1)
        return true;
    else
        return false;
}

void addToLandingList(plane pp)
{
    printf("\n");
    if (isEmpty())
    {
        front = rear = 0;
        planeL[rear] = pp;
        printf("\n%d    %d      %d      %d  \ninis izin talebi onaylanmistir!\n", planeL[rear].priorityId, planeL[rear].planeNo, planeL[rear].landingTime, planeL[rear].delay);
        return;
    }
    else if (isFull())
    {
        printf("\nThe PQ is full!\nChecking conditions for emergency landing...\nPlease wait...\n");
        planeL[rear + 1] = pp;
        delayHandler4Full(planeL[rear + 1]);
        return;
    }
    else
    {
        rear += 1;
        planeL[rear] = pp;
        delayHandler(planeL[rear]);
        return;
    }
    return;
}

void readInput()
{

    FILE *file;
    file = fopen("planes.txt", "r");
    if (file == NULL)
        printf("\n  Error! Couldnt open file \n");
    else
    {

        // printf("\n Priority ID\tPlane No\tLanding Time \n");
        fseek(file, 24, SEEK_SET); //to skip the first line in the planes.txt file
        for (int i = 0; i < 28; i++)
        {
            fscanf(file, "%d %d %d", &planeP[i].priorityId, &planeP[i].planeNo, &planeP[i].landingTime);
            planeP[i].delay = 0;
            printf("\nPriority ID   Plane No   Landing Time   Delay\n");
            printf("\n\n%*d%*d%*d%*d \n", 7, planeP[i].priorityId, 11, planeP[i].planeNo, 13, planeP[i].landingTime, 12, planeP[i].delay);
            addToLandingList(planeP[i]);

            // Sleep(1000);
        }
    }
    fclose(file);
}

int main()
{
    readInput();
    printf("\n\n\n------------------------------------------------------\n");
    int i = 0;
    printf("\nPriority ID   Plane No   Landing Time   Delay\n");
    while (i < MAX)
    {
        printf("\n\n%d%*d%*d%*d%*d \n", i, 7, planeL[i].priorityId, 11, planeL[i].planeNo, 13, planeL[i].landingTime, 12, planeL[i].delay);
        // printf("\nrear = %d\n", rear);
        i++;
    }

    return 0;
}
