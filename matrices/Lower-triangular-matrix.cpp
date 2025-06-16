#include <iostream>
#include <cstdlib>
using namespace std;

class Lower_Triangular
{
    private:
        int* arr;
        unsigned int n;

    public:
        Lower_Triangular()
        {
            n = 5;
            int non_zero_elements = n * (n + 1)/ 2;
            arr = new int[non_zero_elements];
        }


        Lower_Triangular(unsigned int n)
        {
            if(n == 0)
            {
                cout<<"(NULL BYTE ERROR): Can't Allocate Null byte"<<endl;
                exit(EXIT_FAILURE);
            }

            this->n = n;
            int non_zero_elements = n * (n + 1)/ 2;
            arr = new int[non_zero_elements];
        }

        ~Lower_Triangular()
        {
            free(arr);
        }


        // Row major mapping
        void Set_r(unsigned int row, unsigned int col, int element);
        int Get_r(unsigned int row, unsigned int col);
        void Display_r();
        void Input_r();

        // Column major mapping
        void Set_c(unsigned int row, unsigned int col, int element);
        int Get_c(unsigned int row, unsigned int col);
        void Display_c();
        void Input_c();
};

// Row major mapping
void Lower_Triangular::Set_r(unsigned int row, unsigned int col, int element)
{
    if (row >= col && row >= 1 && row <= n && col >= 1)
    {
        int index = (row * (row - 1)) / 2 + (col - 1);
        arr[index] = element;
    }
}

int Lower_Triangular::Get_r(unsigned int row, unsigned int col)
{
    if (row >= col && row >= 1 && row <= n && col >= 1)
    {
        int index = (row * (row - 1)) / 2 + (col - 1);
        return arr[index];
    }
    else
        return 0; 
}

void Lower_Triangular::Display_r()
{
    for (unsigned int row = 1; row <= n; row++)
    {
        for (unsigned int col = 1; col <= n; col++)
        {
            if (row >= col)
            {
                int index = (row * (row - 1)) / 2 + (col - 1);
                cout<<arr[index]<<" ";
            }
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}

void Lower_Triangular::Input_r()
{
    printf("Enter all elements (row-wise):\n");
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= n; j++)
        {
            int x;
            if (i >= j)
            {
                cout << "Element [" << i << "][" << j << "]: ";
                cin>>x;
                Set_r(i, j, x);
            }
        }
    }
}

// Column major mapping
void Lower_Triangular::Set_c(unsigned int row, unsigned int col, int element)
{
    if (row >= col && row >= 1 && row <= n && col >= 1)
    {
        int index = n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
        arr[index] = element;
    }
}


int Lower_Triangular::Get_c( unsigned int row, unsigned int col)
{
    if (row >= col && row >= 1 && row <= n && col >= 1)
    {
        int index = n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
        return arr[index];
    }
    else
        return 0;  
}

void Lower_Triangular::Display_c()
{
    for (unsigned int row = 1; row <= n; row++)
    {
        for (unsigned int col = 1; col <= n; col++)
        {
            if (row >= col)
            {
                int index = n*(col - 1) - ((col-2)*(col-1)/2) + row - col;
                cout<<arr[index]<<" ";
            }
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}


void Lower_Triangular::Input_c()
{
    printf("Enter all elements (col-wise):\n");
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= n; j++)
        {
            int x;
            if (j >= i)
            {
                cout << "Element [" << j << "][" << i << "]: ";
                cin>>x;
                Set_c(j, i, x);
            }
        }
    }
}


int main()
{
    unsigned int size;
    cout<<"Enter Dimension: ";
    cin>>size;
    Lower_Triangular lm(size);

    lm.Input_c();
    lm.Display_c();

    cout<<"Matrix(3,2):"<<lm.Get_c(3,2)<<endl;
    return EXIT_SUCCESS;
}