

#include <iostream>

using namespace std;

class rekord
{
public:

    int klucz;
    int bazowy_id;
    string tekst;

    rekord()
    {
        klucz = -1;
        bazowy_id = -1;
        tekst = "";
    }

    rekord(int k,int size, string t)
    {
        klucz = k;
        bazowy_id=k%size;
        tekst = t;
    }
    ~rekord() {};

    void set_rekord(int k, int size, string t)
    {
        klucz = k;
        if(size==-1)
        {
            bazowy_id = -1;
        }
        else
        {
            bazowy_id = k % size;
        }
        tekst = t;
    }

    void delete_rekord()
    {
        klucz = -1;
        bazowy_id = -1;
        tekst = "";
    }

    void show()
    {
        cout << klucz << " " << tekst << " " << endl; //cout<<bazowy_id << endl;
    }

};

int index(int key, int size); //wyznacza index

rekord* get_array(int size); //tworzy tabele rekordow o danym rozmiarze

void add(rekord* arr, int size, int klucz, int id, string tekst); //dodaje rekord

void print(rekord* arr, int size); //drukuje niepuste rekordy tabeli

void del(rekord* arr, int size, int klucz); //usuwa rekord o podanym kluczu

void popraw(rekord* arr, int size); //poprawia miejsca rekordów które nie są na swoich miejscach docelowych

int main()//interefejs umieszczony w mainie
{
    int l_przyp; //liczba przypadków (ile tablic po kolei zostanie stworzonych)
    cin >> l_przyp;
    int licznik = 1;
    while (licznik <= l_przyp)
    {
        string wejscie;
        string arg1;
        string arg2;
        int size;
        cin >> wejscie;
        cin >> size;
        //cout << size << endl;
        rekord* arr = new rekord[size];

        while (wejscie != "stop")
        {
            cin >> wejscie;
            
            if (wejscie == "add")
            {
                int klucz;
                string tekst;
                cin >> klucz;
                cin >> tekst;
                //cout << klucz << " " << tekst<<endl;
                add(arr, size, klucz, index(klucz, size), tekst);


            }
            else if (wejscie == "delete")
            {
                int klucz;
                cin >> klucz;
                //cout << arg1 << endl;
                del(arr, size, klucz);
            }
            else if (wejscie == "print")
            {
                print(arr, size);
                cout << endl;
            }
            popraw(arr, size);
        }
        licznik++;
        delete[] arr;
    }
}


int index(int key, int size)
{
    return key % size;
}

rekord* get_array(int size)
{
    rekord* arr = new rekord[size];
    return arr;
}

void add(rekord* arr, int size, int klucz, int id, string tekst)
{
    if (arr[id].klucz == -1)
    {
        arr[id].set_rekord(klucz, size, tekst);
    }
    else
    {
        if (id != size)
        {
            id++;
        }
        else
        {
            id = 0;
        }
        return add(arr, size, klucz, id, tekst);
    }
}

void print(rekord* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].klucz != -1)
        {
            cout << i << " ";
            arr[i].show();
        }
    }
}

void del(rekord* arr, int size, int klucz)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].klucz == klucz)
        {
            arr[i].delete_rekord();
        }
    }
}

void popraw(rekord* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if ((arr[i].bazowy_id != i) && (arr[i].bazowy_id != -1)) //nie jest pusty i nie jest na swoim miejscu
        {
            {
                int pom = 1;
                for (int j = arr[i].bazowy_id; pom != 0; ++j)// szukanie dla rekordu nie na swoim miejscu miejsca bliżej docelowego
                {
                    if (j == size)
                    {
                        j = 0;
                    }
                    if (arr[j].bazowy_id == -1)
                    {
                        arr[j].set_rekord(arr[i].klucz, size, arr[i].tekst);
                        arr[i].delete_rekord();
                        i = j;
                    }
                    //cout << "i=" << i << endl;
                    //cout << "j=" << j << endl;
                    pom = i - j;
                }
            }
        }
    }
}