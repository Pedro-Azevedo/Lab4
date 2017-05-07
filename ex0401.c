#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 100


struct ISTPerson{
    int ist_id;
    char nome[MAX];
    char dominio[MAX];
    int ano_nascimento;
};


void load_istpeople(struct ISTPerson**, FILE*);
void find_youngest(struct ISTPerson*);
void find_oldest(struct ISTPerson*);
void print(struct ISTPerson*, int);


int main(void)
{
    FILE *fp=NULL;
    struct ISTPerson *istpeople=NULL;

    fp=fopen("contacts.txt", "r");
    if(fp==NULL)
    {
        printf("Error: File could not be opened\n");
        exit(EXIT_FAILURE);
    }

    load_istpeople(&istpeople, fp);
    find_youngest(istpeople);
    find_oldest(istpeople);

    free(istpeople);//free memory
    fclose(fp);//close file

    return EXIT_SUCCESS;
}

/**
    load_istpeople: function to read the file into a vector of structures
                    it passes by reference the vector of structures and the file
*/

void load_istpeople(struct ISTPerson** _istpeople, FILE* _fp)
{
    struct ISTPerson* aux=NULL; /* auxiliar pointer(vector)*/
    char separator[]="#@#"; /* separator characters to apply the strtok function */
    char *help=NULL; /* help pointer to apply the strtol function */
    char buffer[MAX]={'\0'}; /* buffer to read from the file */
    long int ist_ID; /* auxiliar variable to apply the strtol function (it returns a long int)*/
    long int ano; /*same*/
    char *token=NULL; /* auxiliar pointer (string) to get the various tokens (strings) when applying strtok*/
    int i=1, j=0;

    /* cycle that hold until we reach the end of the file*/
    while(fgets(buffer, MAX, _fp)!=NULL)
    {
        aux=(struct ISTPerson*)realloc(aux, i*sizeof(struct ISTPerson));/* we reallocate memory fro each iteration*/
        if (aux==NULL)
        {
            printf("Error: Memory not correctly allocated\n");
            exit(EXIT_FAILURE);
        }

        token=strtok(buffer, separator); /*To get "ist(numbers) */

        /* cycle to convert "ist(numbers) to just "(numbers)"*/
        for(j=0; j<strlen(token)-2; j++)
        {
            token[j]=token[j+3];
        }
        token[j]='\0';

        ist_ID=strtol(token, &help, 10); /*convert the string to a long int number */
        aux[i-1].ist_id=(int)ist_ID; /* cast the long int to an int and attribute it to the respective structure*/

        token=strtok(NULL, separator); /* to get name*/
        strcpy(aux[i-1].nome, token);

        token=strtok(NULL, separator);/* to get domain */
        strcpy(aux[i-1].dominio, token);

        token=strtok(NULL, separator); /* to get year of birth */
        ano=strtol(token, &help, 10); /* convert string to a long int*/
        aux[i-1].ano_nascimento=(int)ano; /* cast the long int to an int and attribute it to the respective structure*/
        i++;
    }

    aux[i-1].ano_nascimento=-1; /*we add a very last structure to our vector so that we have an invalid parameter
                                    (in this case, a negative year of birth). This way, we'll be able to iterate
                                    through the vector in other functions without knowing its length */

    *_istpeople=aux; /* we finally get rid of the auxiliary vector*/
}

/**
    find_oldest: function to find the oldest members listed in the file
                    it has the vector of structures as entry
*/

void find_oldest(struct ISTPerson* _istpeople)
{

    int old=_istpeople->ano_nascimento; /*we start by assuming the oldest is the year in the first structure*/
    int i=1;

    while((_istpeople+i)->ano_nascimento>0)/*we iterate using our invalid parameter*/
    {
        if(((_istpeople+i)->ano_nascimento)<old)/* if the year in other function is lower than the year currently in the
                                                    variable old, than old is the new year found */
        {
            old=(_istpeople+i)->ano_nascimento;
        }
        i++;
    }

    printf("\nFuncionario(s) mais velho(s)\n");
    print(_istpeople, old);/* to print the oldest employees*/
}

/**
    find_youngest: function to find the youngest members listed in the file
                    it has the vector of structures as entry
*/
void find_youngest(struct ISTPerson* _istpeople)
{

    /* SImilar login to the previous function*/
    int youn=_istpeople->ano_nascimento;
    int i=1;

    while((_istpeople+i)->ano_nascimento>0)
    {
        if(((_istpeople+i)->ano_nascimento)>youn)
        {
            youn=(_istpeople+i)->ano_nascimento;
        }
        i++;
    }

    printf("\nFuncionario(s) mais novo(s)\n");
    print(_istpeople, youn);
}


/**
    print : function to print some elements of the strutures that verify some parameter related to the year of born
                    it has the vector of structures and the parameter as entries
*/

void print(struct ISTPerson* _istpeople, int _parameter)
{
    int i=0;

    while((_istpeople+i)->ano_nascimento>0) /* we iterate using our invalid parameter*/
    {
        if(((_istpeople+i)->ano_nascimento)==_parameter) /* if the parameter is satisfies we print*/
        {
            printf("ISTID:ist%d\n", (_istpeople+i)->ist_id);
            printf("Email:%s@%s\n", (_istpeople+i)->nome, (_istpeople+i)->dominio);
        }
        i++;
    }

}
