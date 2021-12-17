#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

const int CAPACITY = 24;
typedef struct plane
{
    int priorityId;
    int planeNo;
    int landingTime;
    int delay;
} plane;

plane planeL[24];
plane planeT[24];

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
    printf("\n\n%*d%*d%*d%*d added\n", 7, planeT[count].priorityId, 11, planeT[count].planeNo, 13, planeT[count].landingTime, 12, planeT[count].delay);
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

void pop()
{
    if (count == 0)
    {
        printf("\nthe runway is empty\n");
        return;
    }
    printf("\n\n%*d%*d%*d%*d took off\n", 7, planeT[1].priorityId, 11, planeT[1].planeNo, 13, planeT[1].landingTime, 12, planeT[1].delay);

    planeT[1] = planeT[count];
    count--;
    downMinHeap(1);
}

int main()
{
    /*
    push(24);
    push(23);
    push(22);
    push(21);
    push(20);
    push(19);
    push(18);
    push(17);
    push(16);
    view();
    printf("\n------------------------\n");
    for (int i = 0; i < 12; i++)
    {
        pop();
        // view();
    }*/

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
        push(planeL[i]);
    }
    printf("\n-----------------------------------------------------------------------\n");
    //analyse the initial index of planeL and planeT (0 or 1?)
    for (int i = 1; i <= count; i++)
    {
        printf("\n\n%*d%*d%*d%*d \n", 7, planeT[i].priorityId, 11, planeT[i].planeNo, 13, planeT[i].landingTime, 12, planeT[i].delay);
    }
    printf("\n-----------------------------------------------------------------------\n");

    for (int j = 0; j <= 9; j++)
    {
        pop();
    }

    return 0;
}