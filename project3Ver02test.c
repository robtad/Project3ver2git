#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //to use Sleep function
#include <string.h>
#include <math.h>
#include <stdbool.h>
//const int MAX = 30;
//array of struct to store all planes read from input file.
typedef struct planesInFile
{
    int priorityId;
    int planeNo;
    int landingTime;
} pendingPlane;
pendingPlane planeP[30]; //pending plane
//array of struct to store request approved planes
const int MAX = 24;
typedef struct plane
{
    int priorityId;
    int planeNo;
    int landingTime;
    int delay; //keeps track of how many times a plane's landing time delayed due to another higher priority planes.
} plane;
//typedef struct plane plane;
plane planeL[25]; //landing plane. One extra space for plane requesting landing when the landing queue is full.
plane tempo;

// const int MAX = 10;
// int A[10];
int front = -1;
int rear = -1;
int i, temp;
int node, left, right, father;

void getFamily(int i)
{
    node = planeL[i].landingTime;
    father = planeL[(i - 1) / 2].landingTime;
    left = planeL[2 * i + 1].landingTime;
    right = planeL[2 * i + 2].landingTime;
}
void setFamilyNF()
{
    planeL[i].landingTime = node;
    planeL[(i - 1) / 2].landingTime = father;
}
void setFamilyNL()
{
    planeL[i].landingTime = node;
    planeL[2 * i + 1].landingTime = left;
}
void setFamilyNR()
{
    planeL[i].landingTime = node;
    planeL[2 * i + 2].landingTime = right;
}
void swapNF()
{
    temp = node;
    node = father;
    father = temp;
}
void swapNL()
{
    temp = node;
    node = left;
    left = temp;
}
void swapNR()
{
    temp = node;
    node = right;
    right = temp;
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
void delayHandler(plane p)
{
    int flag = 0;
    for (int i = front; i < rear; i++)
    {
        if (planeL[i].landingTime == p.landingTime)
        {
            flag = 1;
            //if ((planeL[i].priorityId > p.priorityId) || ((planeL[i].priorityId == p.priorityId) && (planeL[i].planeNo > p.planeNo)))
            if (planeL[i].priorityId == p.priorityId)
            {
                /////
                printf("\nequal     incoming prID:%d     existing prID:%d\n", p.priorityId, planeL[i].priorityId);
                printf("\ncompared with %d    %d     %d\n", planeL[i].priorityId, planeL[i].planeNo, planeL[i].landingTime);
                /////
                if (planeL[i].planeNo <= p.planeNo)
                {
                    if (p.delay < 3)
                    {
                        p.delay += 1;
                        p.landingTime += 1;
                        planeL[rear] = p;
                        printf("\nDDDaha once ayni saat icin inis izin talebi onaylanan ucak bulunmaktadir.\n"
                               "ondan daha yuksek onceliginiz olmadigi icin,inis saatiniz bir saat ertelenmistir.");
                        printf("\n\nlandingTime of %d id plane:%d\n", p.planeNo, p.landingTime);
                        printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                        delayHandler(p);
                    }
                }
                else //if plane no of existing plane is greater than new plane
                {
                    if (planeL[i].delay < 3)
                    {
                        printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                               "saatte inis talep eden %d ucak id'li ucagin inis saati bir saat ertelenmistir.",
                               p.priorityId, planeL[i].planeNo);
                        printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                        tempo = planeL[i];
                        planeL[i] = p;
                        p = tempo;
                        p.delay += 1;
                        p.landingTime += 1;
                        planeL[rear] = p;
                        delayHandler(p);
                    }
                    else //if planeL[i] is delayed 3 times already. delay the high priority plane.
                    {
                        printf("%d ucak id'li ucagin inisi daha once 3 kere ertendigi icin, %d ucak id'li\n"
                               "ucagin inis bir saat ertelenmistir.",
                               planeL[i].planeNo, p.planeNo);
                        printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!\n", p.planeNo);
                        p.delay += 1;
                        p.landingTime += 1;
                        planeL[rear] = p;
                        delayHandler(p); //check for other planes with the same time and handle the delay.
                    }
                }
            }
            else if (planeL[i].priorityId > p.priorityId)
            {
                /////
                printf("\nincoming smaller      incoming prID:%d     existing prID:%d\n", p.priorityId, planeL[i].priorityId);
                printf("\ncompared with %d    %d     %d\n", planeL[i].priorityId, planeL[i].planeNo, planeL[i].landingTime);
                /////
                if (planeL[i].delay < 3)
                {
                    printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                           "saatte inis talep eden %d ucak id'li ucagin inis saati bir saat ertelenmistir.",
                           p.priorityId, planeL[i].planeNo);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                    tempo = planeL[i];
                    planeL[i] = p;
                    p = tempo;
                    printf("\nswapped incoming: %d  %d  %d  %d\n", tempo.priorityId, tempo.planeNo, tempo.landingTime, tempo.delay);
                    p.delay += 1;
                    p.landingTime += 1;
                    printf("\ncheck swapp: %d  %d  %d  %d\n", p.priorityId, p.planeNo, p.landingTime, p.delay);
                    planeL[rear] = p;
                    delayHandler(p);
                }
                else //if planeL[i] is delayed 3 times already. delay the high priority plane.
                {
                    printf("%d ucak id'li ucagin inisi daha once 3 kere ertendigi icin, %d ucak id'li\n"
                           "ucagin inis bir saat ertelenmistir.",
                           planeL[i].planeNo, p.planeNo);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!\n", p.planeNo);
                    p.delay += 1;
                    p.landingTime += 1;
                    planeL[rear] = p;
                    delayHandler(p); //check for other planes with the same time and handle the delay.
                }
            }
            else //if priority id of the existing plane is smaller than the new plane
            {
                /////
                printf("\nexisting smaller      incoming prID:%d     existing prID:%d\n", p.priorityId, planeL[i].priorityId);
                printf("\ncompared with %d    %d     %d\n", planeL[i].priorityId, planeL[i].planeNo, planeL[i].landingTime);
                /////
                if (p.delay < 3)
                {
                    p.delay += 1;
                    p.landingTime += 1;
                    planeL[rear] = p;
                    printf("\nDDDaha once ayni saat icin inis izin talebi onaylanan ucak bulunmaktadir.\n"
                           "ondan daha yuksek onceliginiz olmadigi icin,inis saatiniz bir saat ertelenmistir.");
                    printf("\n\nlandingTime of %d id plane:%d\n", p.planeNo, p.landingTime);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                    delayHandler(p);
                }
            }
        }
    }
    if (flag == 0)
    { //checks if the incoming plane has no any landing time overlap with others.
        printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
    }
    return;
}

////
/*  if (planeL[i].delay < 3)
                {
                    printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                           "saatte inis talep eden %d ucak id'li ucagin inis saati bir saat ertelenmistir.",
                           p.priorityId, planeL[i].planeNo);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                    tempo = planeL[i];
                    planeL[i] = p;
                    p = tempo;
                    p.delay += 1;
                    p.landingTime += 1;
                    delayHandler(p);
                }
                else //if planeL[i] is delayed 3 times already. delay the high priority plane.
                {
                    printf("%d ucak id'li ucagin inisi daha once 3 kere ertendigi icin, %d ucak id'li\n"
                           "ucagin inis bir saat ertelenmistir.",
                           planeL[i].planeNo, p.planeNo);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!\n", p.planeNo);
                    p.delay += 1;
                    p.landingTime += 1;
                    delayHandler(p); //check for other planes with the same time and handle the delay.
                }
            }
            else
            {
                if (p.delay < 3)
                {
                    p.delay += 1;
                    p.landingTime += 1;
                    printf("\nDDDaha once ayni saat icin inis izin talebi onaylanan ucak bulunmaktadir.\n"
                           "ondan daha yuksek onceliginiz olmadigi icin,inis saatiniz bir saat ertelenmistir.");
                    printf("\n\nlandingTime of %d id plane:%d\n", p.planeNo, p.landingTime);
                    printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", p.planeNo);
                    delayHandler(p);
                }
            }
        }
    }
    return;
}*/
void addToPQ(pendingPlane planeP)
{
    printf("\n");
    if (isEmpty())
    {
        front = rear = 0;
        // planeL[rear].landingTime = x;
        planeL[rear].priorityId = planeP.priorityId;
        planeL[rear].planeNo = planeP.planeNo;
        planeL[rear].landingTime = planeP.landingTime;
        //printf("element %d is added to PQ successfully!\n", planeL[rear].landingTime);
        printf("\n%d ucak id'li ucagin inis izin talebi onaylanmistir!", planeL[rear].planeNo);
    }
    else if (isFull())
    {
        printf("\nThe PQ is full!\nChecking conditions for emergency landing...please wait...");
        // planeL[rear + 1].landingTime = x;
        planeL[rear + 1].priorityId = planeP.priorityId;
        planeL[rear + 1].planeNo = planeP.planeNo;
        planeL[rear + 1].landingTime = planeP.landingTime;
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
                               "Havalimani’na yonlendiriliyor...",
                               planeL[rear + 1].planeNo, planeL[j].planeNo, planeL[j].planeNo);
                        planeL[j] = planeL[rear + 1];
                        printf("\n\n%d Ucak id'li ucagin inis izin talebi onaylanmistir!", planeL[j].planeNo);
                    }
                }
                else if (planeL[j].priorityId > planeL[rear + 1].priorityId)
                {
                    printf("\nAcil inis yapmasi gereken %d oncelik id'li ucagi nedeniyle daha once ayni\n"
                           "saatte inis talep eden %d oncelik id'li ucagin inis izni iptal edilmistir,\n inis icin Sabiha Gokcen"
                           "Havalimani’na yonlendiriliyor...",
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

        //return;
    }
    else //if there is atleast one element in the PQ
    {
        rear += 1;
        //planeL[rear].landingTime = x;
        planeL[rear].priorityId = planeP.priorityId;
        planeL[rear].planeNo = planeP.planeNo;
        planeL[rear].landingTime = planeP.landingTime;
        //////////////////////////////
        delayHandler(planeL[rear]);

        ///////////////////////////////
        //printf("element %d is added to PQ successfully!\n", planeL[rear].landingTime);
        i = rear;

        /*  while (i > front) //this while loop arranges planes in a heap. it is in else block check later. commented for debugging uncomment later
        {
            getFamily(i);
            if (node < father)
            {
                swapNF(); //swap current node with its father
            }
            setFamilyNF(); //to put the swaped element in array;
            i = (i - 1) / 2;
        }*/
    }
}
void removeFromPQ()
{
    if (isEmpty())
    {
        printf("can't remove, the PQ is empty\n");
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
        }

        return;
    }
}

void readInput()
{

    FILE *file;
    file = fopen("planes.txt", "r");
    if (file == NULL)
        printf("\n  Error! Couldnt open file \n");
    else
    {

        printf("\n Priority ID\tPlane No\tLanding Time \n");
        fseek(file, 24, SEEK_SET); //to skip the first line in the planes.txt file
        for (int i = 0; i < 28; i++)
        {
            fscanf(file, "%d %d %d", &planeP[i].priorityId, &planeP[i].planeNo, &planeP[i].landingTime);
            printf("\n\n%*d%*d%*d   \n", 7, planeP[i].priorityId, 11, planeP[i].planeNo, 19, planeP[i].landingTime);
            planeL[i].delay = 0;
            addToPQ(planeP[i]);

            // Sleep(1000);
        }
    }
    fclose(file);
}

int main()
{
    /*for (int i = 0; i < 25; i++)
    {
        planeL[i].delay = 0;
    }*/
    readInput();

    printf("\n\n\n------------------------------------------------------\n");
    int i = 0;
    while (i < 25)
    {
        printf(" \n%d|  %*d%*d%*d%*d   \n", i, 7, planeL[i].priorityId, 11, planeL[i].planeNo, 19, planeL[i].landingTime, 15, planeL[i].delay);
        i++;
    }

    return 0;
}
