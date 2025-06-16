#include <iostream>
#include <cstdlib>
using namespace std;

class Upper_Triangular
{
    private:
        int* arr;
        unsigned int n;

    public:
        Upper_Triangular()
        {
            n = 5;
            int non_zero_elements = n * (n + 1)/ 2;
            arr = new int[non_zero_elements];
        }


        Upper_Triangular(unsigned int n)
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

        ~Upper_Triangular()
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
void Upper_Triangular::Set_r(unsigned int row, unsigned int col, int element)
{
    if (col >= row && col >= 1 && col <= n && row >= 1)
    {
        int index = n*(row - 1) - ((row - 2)* (row - 1)/ 2) + (col - row);
        arr[index] = element;
    }
}

int Upper_Triangular::Get_r(unsigned int row, unsigned int col)
{
    if (col >= row && col >= 1 && col <= n && row >= 1)
    {
        int index = n*(row - 1) - ((row - 2)* (row - 1)/ 2) + (col - row);
        return arr[index];
    }
    else
        return 0; 
}

void Upper_Triangular::Display_r()
{
    for (unsigned int row = 1; row <= n; row++)
    {
        for (unsigned int col = 1; col <= n; col++)
        {
            if (col >= row)
            {
                int index = n*(row - 1) - ((row - 2)* (row - 1)/ 2) + (col - row);
                cout<<arr[index]<<" ";
            }
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}

void Upper_Triangular::Input_r()
{
    printf("Enter all elements (row-wise):\n");
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= n; j++)
        {
            int x;
            if (j >= i)
            {
                cout << "Element [" << i << "][" << j << "]: ";
                cin>>x;
                Set_r(i, j, x);
            }
        }
    }
}

// Column major mapping
void Upper_Triangular::Set_c(unsigned int row, unsigned int col, int element)
{
    if (col >= row && col >= 1 && col <= n && row >= 1)
    {
        int index =col * (col - 1) / 2 + (row - 1);
        arr[index] = element;
    }
}


int Upper_Triangular::Get_c( unsigned int row, unsigned int col)
{
    if (col >= row && col >= 1 && col <= n && row >= 1)
    {
        int index =col * (col - 1) / 2 + (row - 1);
        return arr[index];
    }
    else
        return 0;  
}

void Upper_Triangular::Display_c()
{
    for (unsigned int row = 1; row <= n; row++)
    {
        for (unsigned int col = 1; col <= n; col++)
        {
            if (col >= row)
            {
                int index =col * (col - 1) / 2 + (row - 1);
                cout<<arr[index]<<" ";
            }
            else
                cout<<"0 ";
        }
        cout<<endl;
    }
}


void Upper_Triangular::Input_c()
{
    printf("Enter all elements (col-wise):\n");
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= n; j++)
        {
            int x;
            if (i >= j)
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
    Upper_Triangular um(size);

    um.Input_r();
    um.Display_r();

    cout<<"Matrix(3,4):"<<um.Get_r(3,4)<<endl;
    return EXIT_SUCCESS;
}