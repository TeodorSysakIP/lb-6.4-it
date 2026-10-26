// Лабораторна робота № 6, завдання № 6.4, варіант 13 (ітераційний спосіб)


#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;


double* CreateArray(const int size);
void    FillRandom(double* a, const int size, const double low, const double high);
void    PrintArray(const double* a, const int size);
void    DestroyArray(double*& a);

int CountInRange(const double* a, const int size, const double A, const double B);

int IndexOfMax(const double* a, const int size);

double SumAfterIndex(const double* a, const int size, const int index);


void SortEvenByModulusDesc(double* a, const int size);


int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    srand(static_cast<unsigned int>(time(nullptr)));

    int n;
    double A, B;

    cout << "Введіть n: ";
    cin >> n;
    cout << "Введіть A: ";
    cin >> A;
    cout << "Введіть B: ";
    cin >> B;

    if (n <= 0)
    {
        cout << "Помилка: n має бути додатним." << endl;
        return 1;
    }

    double* a = CreateArray(n);
    FillRandom(a, n, -10.0, 10.0);

    cout << "\nПочатковий масив:" << endl;
    PrintArray(a, n);

   
    int count = CountInRange(a, n, A, B);
    cout << "\n1.1. Кількість елементів в діапазоні [" << A << "; " << B
        << "] = " << count << endl;

 
    int imax = IndexOfMax(a, n);
    double sum = SumAfterIndex(a, n, imax);
    cout << "1.2. Максимальний елемент a[" << imax << "] = " << a[imax]
        << ", сума елементів після нього = " << fixed << setprecision(2) << sum << endl;

  
    SortEvenByModulusDesc(a, n);
    cout << "\n2. Масив після впорядкування парних елементів за спаданням модулів:" << endl;
    PrintArray(a, n);

    DestroyArray(a);
    return 0;
}


double* CreateArray(const int size)
{
    return new double[size];
}

void FillRandom(double* a, const int size, const double low, const double high)
{
    for (int i = 0; i < size; i++)
        a[i] = low + (high - low) * rand() / RAND_MAX;
}

void PrintArray(const double* a, const int size)
{
    for (int i = 0; i < size; i++)
        cout << setw(8) << fixed << setprecision(2) << a[i];
    cout << endl;
}

void DestroyArray(double*& a)
{
    delete[] a;
    a = nullptr;
}

int CountInRange(const double* a, const int size, const double A, const double B)
{
    int count = 0;
    for (int i = 0; i < size; i++)
        if (a[i] >= A && a[i] <= B)
            count++;
    return count;
}

int IndexOfMax(const double* a, const int size)
{
    int imax = 0;
    for (int i = 1; i < size; i++)
        if (a[i] > a[imax])        
            imax = i;
    return imax;
}

double SumAfterIndex(const double* a, const int size, const int index)
{
    double s = 0;
    for (int i = index + 1; i < size; i++)
        s += a[i];
    return s;
}

void SortEvenByModulusDesc(double* a, const int size)
{
    
    for (int i = 0; i < size; i += 2)
    {
        int imax = i;                          
        for (int j = i + 2; j < size; j += 2)
            if (fabs(a[j]) > fabs(a[imax]))
                imax = j;

        double tmp = a[i];
        a[i] = a[imax];
        a[imax] = tmp;
    }
}