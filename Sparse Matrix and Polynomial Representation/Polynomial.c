#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Term
{
    int coeff;
    int exp;
} Term;

typedef struct Polynomial
{
    unsigned int n;
    Term* terms;
} Polynomial;

Polynomial* __init__()
{
    Polynomial* poly = (Polynomial *)malloc(sizeof(Polynomial));

    if(!poly)
    {
        printf("Couldn't alloacte the memory!\n");
        exit(EXIT_FAILURE);
    }


    printf("Enter the no.of terms: ");
    scanf("%u",&(poly->n));

    poly->terms = (Term *)malloc(sizeof(Term) * poly->n);

    if(!(poly->terms))
    {
        printf("Couldn't alloacte the memory!\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter the terms \n");
    for(unsigned int i = 0; i < poly->n; i++)
    {
        printf("Enter the Term-%u (coeffecient): ",i+1);
        scanf("%d",&((*(poly->terms + i)).coeff));
        printf("Enter the Term-%u (exponent): ",i+1);
        scanf("%d",&((*(poly->terms + i)).exp));
    }

    return poly;
}

void __del__(Polynomial* poly)
{
    free(poly->terms);
    free(poly);
}

void display(Polynomial* poly)
{
    printf("P(X) := ");
    for(unsigned int i = 0; i < poly->n; i++)
    {
        printf("%dX^%d ",(*(poly->terms + i)).coeff,(*(poly->terms + i)).exp);
        if(i != (poly->n - 1))
            printf("+ ");
    }
    printf("\n");
}

Polynomial* add(Polynomial* p1, Polynomial* p2)
{

    if(!p1 || !p2)
    {
        printf("Null object can't be used to perform polynomial addition!\n");
        exit(EXIT_FAILURE);
    }

    Polynomial* result = (Polynomial *)malloc(sizeof(Polynomial));

    if(!result)
    {
        printf("Couldn't alloacte the memory!\n");
        exit(EXIT_FAILURE);
    }

    result->terms = (Term *)malloc(sizeof(Term) * (p1->n + p2->n));

    if(!(result->terms))
    {
        printf("Couldn't alloacte the memory!\n");
        free(result);
        exit(EXIT_FAILURE);
    }

    unsigned int  i,j,k;
    i=j=k=0;

    while(i < p1->n && j < p2->n)
    {
        if((*(p1->terms + i)).exp > (*(p2->terms + j)).exp)
        {
            *(result->terms + k) =  *(p1->terms + i);
            i++;
        }
        else if((*(p1->terms + i)).exp < (*(p2->terms + j)).exp)
        {
            *(result->terms + k) =  *(p2->terms + j);
            j++;
        }
        else
        {
            (*(result->terms + k)).exp = (*(p1->terms + i)).exp;
            (*(result->terms + k)).coeff = (*(p1->terms + i)).coeff + (*(p2->terms + j)).coeff;
            i++;
            j++;
        }
        k++;
    }

    for(; i < p1->n; i++)
    {
        *(result->terms + k) = *(p1-> terms + i);
        k++;
    }

    for(; j < p2->n; j++)
    {
        *(result->terms + k) = *(p2-> terms + j);
        k++;
    }

    result->n = k;

    result->terms = (Term *)realloc(result->terms,sizeof(Term) * result->n);

    if(!(result->terms))
    {
        printf("Couldn't alloacte the memory!\n");
        free(result);
        exit(EXIT_FAILURE);
    }

    return result;
}

double evaluate(Polynomial* poly, double x)
{
    double sum = 0.0;
    for (unsigned int i = 0; i < poly->n; i++)
    {
        double coeff = (double)(*(poly->terms + i)).coeff;
        int exp = (*(poly->terms + i)).exp;
        sum += coeff * pow(x, exp);
    }
    return sum;
}


int main()
{
    Polynomial* poly1 = __init__();
    display(poly1);
    Polynomial* poly2 = __init__();
    display(poly2);
    Polynomial* result = add(poly1,poly2);
    display(result);

    __del__(poly1);
    __del__(poly2);
    __del__(result);
    return EXIT_SUCCESS;
}