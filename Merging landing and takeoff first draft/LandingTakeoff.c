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
//plane tempo;

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
//the updateOutput function writes the updated takeoff information to the output.txt file and it
//reads the updated version of
//the fields that should appear in the output file are: 1.priorityId 2.planeNo
//3. requested landing timr(landingTime-delay) 4.landingTime 5.delay
//6.takeOffTime(landingTime+1).
void updateOutput() {}

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

////////////////////////////////
/*
void addToPQ(int x)
{
    if (isEmpty())
    {
        front = rear = 0;
        planeL[rear].landingTime = x;
        printf("element %d is added to PQ successfully!\n", planeL[rear].landingTime);
    }
    else if (isFull())
    {
        printf("Sorry! The PQ is full.");
        return;
    }
    else //if there is atleast one element in the PQ
    {
        rear += 1;
        planeL[rear].landingTime = x;
        printf("element %d is added to PQ successfully!\n", planeL[rear].landingTime);
        i = rear;

        while (i > front)
        {
            getFamily(i);
            if (node < father)
            {
                swapNF(); //swap current node with its father
            }
            setFamilyNF(); //to put the swaped element in array;
            i = (i - 1) / 2;
        }
    }
}*/
////////////////////////////////
/*
void removeFromPQ()
{
    if (isEmpty())
    {
        //printf("can't remove, the PQ is empty\n");
        printf("\nBeklemekte olan ucak bulunmamaktadir.\n");
        return;
    }
    else if (front == rear) //if there is only one element in pq(i,e only root)
    {
        printf("element %d is dequeued/removed from PQ\n", planeL[front].landingTime);
        front = -1; //dequeueing when front == rear makes the queue empty.
        rear = -1;
        return;
    }
    else //if there are more than one elements
    {
        printf("%d is dequeued/removed from PQ\n", planeL[front].landingTime);
        planeL[front].landingTime = planeL[rear].landingTime; //putting the last element in the root(since root is removed)
        rear -= 1;                                            //since the rear element goes to the root rear points to the next rear element (which is rear-1)
        int i = front;
        //int depth = log2(rear);
        getFamily(i);
        while (i < rear)

        {
            if (((2 * i) + 1) > rear) //if the left kid is not there the node planeL[i].landingTime has no kids at all in a heap.
                break;                //to prevent accessing non existent kids
            if (((2 * i) + 2) > rear) //if the right kid is not there check the left and swap if it is smaller than planeL[i].landingTime.
            {                         //to prevent accessing non existent kids
                if (left < node)
                {
                    swapNL(); //swap node and its left child
                    setFamilyNL();
                    break;
                }
            }

            if (left < right)
            {
                if (left > node)
                    break; ////no swap needed if the parent is smaller than the smaller kid(i.e, everyone is inplace)
                else
                {
                    swapNL(); //swap node and its left child
                    setFamilyNL();
                }
                i = (2 * i) + 1;
            }
            else
            {
                if (right > node)
                    break; //no swap needed if the parent is less than the smaller kid(i.e, everyone is inplace)
                else
                {
                    swapNR();
                    setFamilyNR();
                }
                i = (2 * i) + 2;
            }

            /*NB if the left and right kids have the same landingTime (i.e,  (A[(2 * i) + 1] == A[(2 * i) + 2]))
             swap according to their priorityId(swap with the smallest priotityId) if they have the same priorityId,
             swap with the smaller planeNo. and add 1 hour to the landingTime of the 
             plane which is not swapped.
            */
/*  }

        return;
    }
}

*/
////////////////////////////////

void readInput()
{

    FILE *file;
    file = fopen("input.txt", "r");
    if (file == NULL)
        printf("\n  Error! Couldnt open file \n");
    else
    {

        // printf("\n Priority ID\tPlane No\tLanding Time \n");
        fseek(file, 24, SEEK_SET); //to skip the first line in the input.txt file
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
