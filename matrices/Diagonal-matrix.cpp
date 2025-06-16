#include <iostream>
#include <cstdlib>
using namespace std;

class Diagonal
{
    private:
        int* arr;
        unsigned int n;

    public:
        Diagonal()
        {
            n = 5;
            arr = new int[n];
        }


        Diagonal(unsigned int n)
        {
            if(n == 0)
            {
                cout<<"(NULL BYTE ERROR): Can't Allocate Null byte"<<endl;
                exit(EXIT_FAILURE);
            }

            this->n = n;
            arr = new int[n];
        }

        ~Diagonal()
        {
            free(arr);
        }

        void Set(unsigned int row, unsigned int col, int element);
        int Get(unsigned int row, unsigned int col);
        void Display();
};

void Diagonal::Set(unsigned int row, unsigned int col, int element)
{
    if(row == col &&  row >= 1 && row <= n)
        *(arr + row - 1) = element;
}

int Diagonal::Get(unsigned int row, unsigned int col)
{
    return (row == col && row >= 1 && row <= n)? *(arr + row - 1): 0;
}

void Diagonal::Display()
{
    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {
            if(row == col)
                cout<<*(arr + row)<<" ";
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}

int main()
{
    Diagonal d(4);
    d.Set(1,1,5);
    d.Set(2,2,8);
    d.Set(3,3,9);
    d.Set(4,4,12);
    d.Display();
    cout<<"Matrix(2,2):"<<d.Get(2,2)<<endl;
    return EXIT_SUCCESS;
}