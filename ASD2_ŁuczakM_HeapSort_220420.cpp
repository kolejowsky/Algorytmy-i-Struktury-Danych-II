#include <iostream>

using namespace std;

void insert(int* tab, int size); // wpisanie elementów do tablicy

void print_tab(int* tab, int size); //wypisywanie elementów 

void sort(int* tab, int size);

void buildHeap(int* tab, int size);

void heapify(int* tab, int index, int size);

int main()
{
   
    int l_przyp; //liczba przypadków (ile tablic po kolei zostanie stworzonych)
    cin >> l_przyp;
    int licznik = 1;
    while (licznik <= l_przyp)
    {
        int size;
        cin >> size;
        //cout << size << endl;
        int* arr = new int[size]; //utworzenie tablicy dynamicznej

        insert(arr, size);
        //print_tab(arr, size);
        sort(arr, size);
        print_tab(arr, size);
        

        
        licznik++;
        cout << endl;


        
        delete[] arr;
    }
}

void insert(int* tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        cin >> tab[i];
    }
}

void print_tab(int* tab, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;
}

void sort(int* tab, int size)
{
    buildHeap(tab, size);
    for (int i = size - 1; i > 0; i--)
    {
        print_tab(tab, i+1); //i+1 maleje wiec wypisuje siê coraz mniej elementów 
        swap(tab[0], tab[i]);
        heapify(tab, 0 ,i);
    }
}

void buildHeap(int* tab, int size)
{
    for (int idx = size / 2 - 1 ; idx >= 0; idx--)
    {
        heapify(tab, idx, size);
    }
}

void heapify(int* tab, int index, int size)
{
    int max = size;
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < max && tab[left] > tab[largest])
    {
        largest = left;
    }
    else
    {
        largest = index;
    }

    if (right < max && tab[right] > tab[largest])
    {
        largest = right;
    }
    
    if (largest != index)
    {
        swap(tab[index], tab[largest]);
        heapify(tab, largest, max);
    }
}
