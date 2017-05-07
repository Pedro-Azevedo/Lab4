#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

/* Double linked list: has the content, a pointer to the next node and a pointer to the previous node*/
typedef struct listnums{
    int num;
    struct listnums *next;
    struct listnums *prev;

}listnums;

void GetN(int*);
void Aleat(int, listnums**);
void CountElem(listnums*);
listnums* NewNode(int);
void InsertHead(listnums**, int);
listnums* InsertTail(listnums*, int);


int main(void)
{
    int N;
    listnums* lista=NULL;
    listnums* freelist=NULL; /*pointer to help free memory*/
    GetN(&N);
    Aleat(N, &lista);
    CountElem(lista);

    /*Free memory*/
    while(lista!=NULL)
    {
        freelist=lista;
        lista=lista->next;
        free(freelist);
    }

    return EXIT_SUCCESS;
}


/** GetN: function that passes by reference the number of numbers to generate */

void GetN(int* _N)
{
    int test=0;
    char buffer[MAX]={'\0'};
    do
    {
        printf("Enter how many number between 0 and 1 to generate\n");
        fgets(buffer, MAX, stdin);
        test=sscanf(buffer, "%d", _N);
        if(test==1 && _N<=0)
        {
            printf("Error: Please enter a non negative number\n");
            test=0;
        }

    }while(test!=1);

}

/** Aleat: function that receives how many numbers to generate(_N)
                                  our list (passed by reference from main)

 */

void Aleat(int _N, listnums** _lista)
{

    srand((unsigned)time(NULL));
    int aleat=0;

    while(_N>0) /*To generate _N numbers*/
    {
        aleat=rand()%2;
        /* Because we want to assign the numbers to the list in order (we chose crescent order)
           When the generated number is 0 we insert it in the beginning of the list (Head).
           When the generated number is 0 we insert it in the beginning of the list (Head).
        */

        if(aleat==0)
            InsertHead(_lista, aleat);
        else
            (*_lista)=InsertTail(*_lista, aleat);
        _N--;
    }
}

/** NewNode: function to create a new node to the list
            It receives the content of the node and returns the node;

 */

listnums* NewNode(int _x)
{
    listnums* newnode; /* our new node*/
    newnode=(listnums*)malloc(sizeof(listnums)); /*allocate memory to the new node*/
    if(newnode==NULL)
    {
        printf("Memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    newnode->num=_x;/* assign the content to the node */
    newnode->next=NULL; /* assign both next and prev pointers to NULL */
    newnode->prev=NULL;
    return newnode;
}

/** InsertHead: function to add a new node at the beginning of the list
            It passes by reference the list to Aleat function and the content to assign to the list;

 */

void InsertHead(listnums**_head, int _x)
{
    listnums *newhead; /* the new head of the list*/
    newhead=NewNode(_x); /* create the node */
    /*If the list is empty*/
    if(*_head==NULL)
    {
        (*_head)=newhead; /* We simply create the list with our new element*/
        return;
    }

    /*If the list already has elements*/
    newhead->next=*_head; /* We put the new node pointing to our current first element*/
    *_head=newhead; /* We put the list (the head) pointing to the new node created */

}

/** InsertTail: function to add a new node at the end of the list
            It passes the list and the content to assign to the list; it returns the list

 */

listnums* InsertTail(listnums *_head, int _x)
{
    listnums *newtail=NULL; /* our new tail */
    newtail=NewNode(_x); /* create the tail node*/
    listnums *aux=NULL; /* create an auxiliary pointer to the list */

    /*If the list is empty*/
    if(_head==NULL)
    {
        /*We create a new list with this new element simply by returning it*/
        return newtail;
    }

    /* If the list is not empty*/

    aux=_head;/* We use our auxiliary pointer (to save us from altering the head)*/

    /* We go all the way down the list */
    while (aux->next!=NULL)
    {
        aux=aux->next;
    }


    aux->next=newtail; /*we put the current tail pointing to the new element*/
    newtail->prev=aux; /* we put the prev pointer of our new element pointing to our current tail*/


    return _head; /*return the list (with first element - head - not changed)*/

}

/** CountElem: function to count the number of zeros and ones in our list
            It passes the list

 */

void CountElem(listnums* _lista)
{
    int one=0, zero=0;

    /* We go all the way down the list, verifying if the content is 0 or 1 and, according to that
        increment the respective variable that counts zeros or ones*/
    while (_lista!=NULL)
    {
        if(_lista->num==0)
            zero++;

        else
            one++;

        _lista=_lista->next;
    }

    printf("\nThere are %d zero(s) and %d one(s) in the list\n", zero, one);
}
