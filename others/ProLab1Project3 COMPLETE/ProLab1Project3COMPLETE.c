#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const int MAX = 25;
const int CAPACITY = 26;
typedef struct plane
{
    int priorityId;
    int planeNo;
    int landingTime;
    int delay;
} plane;
plane planeL[25];
plane planeP[28];
plane planeT[26];
int flagM = 1;
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
                           "olmadigi icin,inis izni verilememektedir.\n\n");
                    flagM = 0;
                }
                else
                {
                    printf("\nUcak id'si %d olan ucagin ucak id onceligi daha once ayni"
                           "saatte inis talep eden %d \nucak id'li ucaktan yuksek oldugu icin"
                           "%d ucak id'li ucagin inis \nizni iptal edilmistir, inis icin Sabiha Gokcen"
                           "Havalimani\'na yonlendiriliyor...\n\n",
                           planeL[rear + 1].planeNo, planeL[j].planeNo, planeL[j].planeNo);
                    planeL[j] = planeL[rear + 1];
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir.\n\n", planeL[j].planeNo);
                    flagM = 0;
                }
            }
            else if (planeL[j].priorityId > planeL[rear + 1].priorityId)
            {
                printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                       "saatte inis talep eden %d oncelik id'li ucagin inis izni iptal edilmistir,\n inis icin Sabiha Gokcen"
                       "Havalimani\'na yonlendiriliyor...\n\n",
                       planeL[rear + 1].priorityId, planeL[j].priorityId);
                planeL[j] = planeL[rear + 1];
                printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir.\n\n", planeL[j].planeNo);
                flagM = 0;
            }
            else //if priority id of the existing plane is smaller than the new plane
            {
                printf("\nDaha once ayni saatte inis talep eden ucaktan daha yuksek\n onceliginiz"
                       "olmadigi icin,inis izni verilememektedir.\n\n");
                flagM = 0;
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

                if (planeL[i].planeNo > p.planeNo)
                {
                    if (planeL[i].delay < 3)
                    {
                        tempo = planeL[i];
                        planeL[i] = p;
                        planeL[rear] = tempo;
                        planeL[rear].landingTime += 1;
                        planeL[rear].delay += 1;
                        delayHandler(planeL[rear]);
                    }
                    else if (planeL[i].delay == 3)
                    {
                        if (p.delay < 3)
                        {
                            planeL[rear].landingTime += 1;
                            planeL[rear].delay += 1;
                            delayHandler(planeL[rear]);
                        }
                        else if (p.delay == 3)
                        {
                            //printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                            printf("\n%d id'li ucak 3 kez ertelenmistir ve inis pisti kullanim sirasinda\n"
                                   "   uygun yer bulunamadi, inis icin Sabiha Gokcen Havalimani\'na yonlendiriliyor.\n\n",
                                   p.planeNo);
                            rear -= 1;
                            flagM = 0;
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
                    }
                    else if (p.delay == 3) //if-else if
                    {
                        //printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                        printf("\n%d id'li ucak 3 kez ertelenmistir ve inis pisti kullanim sirasinda\n"
                               "   uygun yer bulunamadi, inis icin Sabiha Gokcen Havalimani\'na yonlendiriliyor.\n\n",
                               p.planeNo);
                        rear -= 1;
                        flagM = 0;
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
                }
                else if (p.delay == 3) //if-else if
                {
                    // printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                    printf("\n%d id'li ucak 3 kez ertelenmistir ve inis pisti kullanim sirasinda\n"
                           "   uygun yer bulunamadi, inis icin Sabiha Gokcen Havalimani\'na yonlendiriliyor.\n\n",
                           p.planeNo);
                    rear -= 1;
                    flagM = 0;
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
                }
                else if (planeL[i].delay == 3) //if-else if
                {
                    if (p.delay < 3)
                    {
                        planeL[rear].landingTime += 1;
                        planeL[rear].delay += 1;

                        delayHandler(planeL[rear]);
                    }
                    else if (p.delay == 3) //if-else if
                    {
                        // printf("\ndelay:%d -->go to Sabiha Airport\n", p.delay);
                        printf("\n%d id'li ucak 3 kez ertelenmistir ve inis pisti kullanim sirasinda\n"
                               "   uygun yer bulunamadi, inis icin Sabiha Gokcen Havalimani\'na yonlendiriliyor.\n\n",
                               p.planeNo);
                        rear -= 1;
                        flagM = 0;
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
    // printf("\nInis izin talebiniz onaylanmistir.\n");
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
        // printf("\n%d    %d      %d      %d  \ninis izin talebi onaylanmistir!\n", planeL[rear].priorityId, planeL[rear].planeNo, planeL[rear].landingTime, planeL[rear].delay);
        // push(planeL[rear]); //adding to takeoff runway.

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

//////////////////////////////

int count = 0;

int getParentIndex(int index)
{
    return index / 2;
}
int getLeftIndex(int index)
{
    return index * 2;
}
int getRightIndex(int index)
{
    return index * 2 + 1;
}

void upMinHeap(int index)
{
    if (index <= 1)
        return;
    int parentIndex = getParentIndex(index);
    if (planeT[index].landingTime < planeT[parentIndex].landingTime)
    {
        plane temp = planeT[index];
        planeT[index] = planeT[parentIndex];
        planeT[parentIndex] = temp;
        upMinHeap(parentIndex);
    }
}

void push(plane value)
{
    if (count == CAPACITY - 1)
    {
        printf("\nthe runway is full\n");
        return;
    }
    count++;
    planeT[count] = value;
    //  printf("\n\n%*d%*d%*d%*d added\n", 7, planeT[count].priorityId, 11, planeT[count].planeNo, 13, planeT[count].landingTime, 12, planeT[count].delay);
    upMinHeap(count);
}

void view()
{
    int i;
    for (i = 1; i <= count; i++)
    {
        printf("\n\n%*d%*d%*d%*d \n", 7, planeT[i].priorityId, 11, planeT[i].planeNo, 13, planeT[i].landingTime, 12, planeT[i].delay);
    }
}

void downMinHeap(int index)
{
    if (index * 2 > count)
        return;

    int left = getLeftIndex(index);
    int right = getRightIndex(index);

    int smallest = index;
    if (left <= count && planeT[left].landingTime < planeT[smallest].landingTime)
    {
        smallest = left;
    }
    if (right <= count && planeT[right].landingTime < planeT[smallest].landingTime)
    {
        smallest = right;
    }
    if (smallest == index)
        return;

    plane temp = planeT[index];
    planeT[index] = planeT[smallest];
    planeT[smallest] = temp;

    downMinHeap(smallest);
}

int flag = 0, flag2 = 0, flag3 = 0;
void writeToOutputFile(plane p)
{

    FILE *file;
    if (flag2 == 0)
    {
        file = fopen("output.txt", "w"); //this line is for test purpose
        flag2 = 1;
    }
    file = fopen("output.txt", "a");

    if (flag == 0)
    {
        fprintf(file, "PriorityID   PlaneNo   ReqLandingTime   LandingTime     Delay   TakeOffTime\n");
        flag = 1;
    }
    fprintf(file, "%*d%*d%*d%*d%*d%*d\n", 7, p.priorityId, 11, p.planeNo, 13, p.landingTime - p.delay, 15, p.landingTime, 13, p.delay, 12, p.landingTime + 1);
    fclose(file);
}

void pop()
{
    if (count == 0)
    {
        printf("\nthe runway is empty\n");
        return;
    }
    if (flag3 == 0)
    {
        printf("\n------------------Guncel kalkis pisti kullanim sirasi------------------------\n");
        printf("\nPriorityID   PlaneNo   ReqLandingTime   LandingTime     Delay   TakeOffTime\n");
        flag3 = 1;
    }
    printf("\n\n%*d%*d%*d%*d%*d%*d\n", 7, planeT[1].priorityId, 11, planeT[1].planeNo, 13, planeT[1].landingTime - planeT[1].delay, 15, planeT[1].landingTime, 13, planeT[1].delay, 12, planeT[1].landingTime + 1);

    writeToOutputFile(planeT[1]);
    planeT[1] = planeT[count];
    count--;
    downMinHeap(1);
}

void pushAndPop(int index)
{
    count = 0;
    int x = 0, y = 0;
    while (x <= rear)
    {
        push(planeL[x]);
        x++;
    }
    while (y < x)
    {
        pop();
        y++;
    }

    flag3 = 0;
    flag2 = 0;
    flag = 0;
    return;
}

///////////////////////////////

void readInput()
{

    FILE *file;
    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("\n  Error! Couldnt open file \n");
        return;
    }

    fseek(file, 24, SEEK_SET); //to skip the first line in the input.txt file
    for (int i = 0; i < 28; i++)
    {
        fscanf(file, "%d %d %d", &planeP[i].priorityId, &planeP[i].planeNo, &planeP[i].landingTime);
        planeP[i].delay = 0;
        printf("\n\nPriority ID   Plane No   Landing Time   Delay\n");
        printf("\n%*d%*d%*d%*d \n", 7, planeP[i].priorityId, 11, planeP[i].planeNo, 13, planeP[i].landingTime, 12, planeP[i].delay);
        addToLandingList(planeP[i]);
        if (flagM)
        {
            printf("Inis izin talebiniz onaylanmistir.\n\n\n");
        }
        pushAndPop(i);
        printf("\n----------------------------------------------------------------------------\n\n");
        flagM = 1;
        // Sleep(1000);
    }

    fclose(file);
}

int main()
{
    readInput();
    return 0;
}
