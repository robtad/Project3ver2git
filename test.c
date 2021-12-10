#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
const int MAX = 24;
typedef struct plane
{
    int priorityId;
    int planeNo;
    int landingTime;
    int delay;
} plane;
//typedef struct plane plane;
plane planeL[24]; //landing plane
plane planeT[24];
plane temp;
int head = -1;
int tail = -1;
int i;
//int temp;//replaced by plane temp;
int node, left, right, father;
plane NODE, LEFT, RIGHT, FATHER;
void getFamily(int i)
{
    node = planeT[i].landingTime;
    father = planeT[(i - 1) / 2].landingTime;
    left = planeT[2 * i + 1].landingTime;
    right = planeT[2 * i + 2].landingTime;
}
void getMember(int i)
{
    NODE = planeT[i];
    FATHER = planeT[(i - 1) / 2];
    LEFT = planeT[2 * i + 1];
    RIGHT = planeT[2 * i + 2];
}
void setFamilyNF()
{
    planeT[i] = NODE;
    planeT[(i - 1) / 2] = FATHER;
}
void setFamilyNL()
{
    planeT[i] = NODE;
    planeT[2 * i + 1] = LEFT;
}
void setFamilyNR()
{
    planeT[i] = NODE;
    planeT[2 * i + 2] = RIGHT;
}

void swapNF()
{
    temp = NODE;
    NODE = FATHER;
    FATHER = temp;
}

void swapNL()
{
    temp = NODE;
    NODE = LEFT;
    LEFT = temp;
}
void swapNR()
{
    temp = NODE;
    NODE = RIGHT;
    RIGHT = temp;
}
bool isEmpty()
{
    if (head == -1 && tail == -1)
        return true;
    else
        return false;
}
bool isFull()
{
    if (tail == MAX - 1)
        return true;
    else
        return false;
}

void addToPQ(plane x) //takes planeT[i] elements.
{
    if (isEmpty())
    {
        head = tail = 0;
        planeT[tail] = x;
        printf("\n\n%*d%*d%*d%*d added\n", 7, planeT[tail].priorityId, 11, planeT[tail].planeNo, 13, planeT[tail].landingTime, 12, planeT[tail].delay);
        //printf("element %d is added to PQ successfully!\n", planeT[tail].landingTime);
    }
    else if (isFull())
    {
        printf("\nkalkis pisti kullanimsirasi dolmustur.\n");
        return;
    }
    else //if there is atleast one element in the PQ
    {
        tail += 1;
        planeT[tail] = x;
        //printf("element %d is added to PQ successfully!\n", planeT[tail].landingTime);
        printf("\n\n%*d%*d%*d%*d added\n", 7, planeT[tail].priorityId, 11, planeT[tail].planeNo, 13, planeT[tail].landingTime, 12, planeT[tail].delay);

        i = tail;

        while (i > head)
        {
            getFamily(i);
            getMember(i);
            if (node < father)
            {
                swapNF(); //swap current node with its father
            }
            setFamilyNF(); //to put the swaped element in array;
            i = (i - 1) / 2;
        }
    }
}

void removeFromPQ()
{
    if (isEmpty())
    {
        printf("\nkalkis pisti kullanim sirasinda olan ucak bulunmamaktadir.\n");
        return;
    }
    else if (head == tail) //if there is only one element in pq(i,e only root)
    {
        //printf("element %d is dequeued/removed from PQ\n", planeT[head].landingTime);
        printf("\n\n%*d%*d%*d%*d took off\n", 7, planeT[head].priorityId, 11, planeT[head].planeNo, 13, planeT[head].landingTime, 12, planeT[head].delay);

        head = -1; //dequeueing when head == tail makes the queue empty.
        tail = -1;
        return;
    }
    else //if there are more than one elements
    {
        //printf("%d is dequeued/removed from PQ\n", planeT[head].landingTime);
        printf("\n\n%*d%*d%*d%*d took off\n", 7, planeT[head].priorityId, 11, planeT[head].planeNo, 13, planeT[head].landingTime, 12, planeT[head].delay);
        planeT[head] = planeT[tail]; //putting the last element in the root(since root is removed)
        tail -= 1;                   //since the tail element goes to the root tail points to the next tail element (which is tail-1)
        int i = head;
        //int depth = log2(tail);
        getFamily(i);
        getMember(i);
        while (i < tail)
        {
            if (((2 * i) + 1) > tail) //if the left kid is not there the node planeT[i].landingTime has no kids at all in a heap.
                break;                //to prevent accessing non existent kids
            if (((2 * i) + 2) > tail) //if the right kid is not there check the left and swap if it is smaller than planeT[i].landingTime.
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

int main()
{
    int num;
    srand(time(NULL));
    for (int i = 0; i < 9; i++)
    {
        planeL[i].priorityId = rand() % 5;
        planeL[i].planeNo = 24 - i;
        planeL[i].landingTime = 24 - i;
        planeL[i].delay = rand() % 4;
    }
    for (int i = 0; i < 9; i++)
    {
        printf("\n\n%*d%*d%*d%*d \n", 7, planeL[i].priorityId, 11, planeL[i].planeNo, 13, planeL[i].landingTime, 12, planeL[i].delay);
        addToPQ(planeL[i]);
    }
    printf("\n-----------------------------------------------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        printf("\n\n%*d%*d%*d%*d \n", 7, planeT[i].priorityId, 11, planeT[i].planeNo, 13, planeT[i].landingTime, 12, planeT[i].delay);
    }
    printf("\n-----------------------------------------------------------------------\n");

    for (int j = 0; j < 9; j++)
    {
        removeFromPQ();
    }
    return 0;
}