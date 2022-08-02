#include <iostream>
#include <vector>

using namespace std;

class vertice
{
public:
    int id;
    string klucz;
    int parent;
    int rank = 1;
public:
    vertice()
    {
        id = -1;
        klucz = "";
        parent = -1;

    }

    vertice(int n, string k)
    {
        id = n;
        klucz = k;
        parent = -1;
    }
    void set_vertice(int n, string k)
    {
        id = n;
        klucz = k;
    }

    void show_vertice()
    {
        cout << id << " " << klucz << endl;
    }
    void operator=(const vertice& v)
    {
        id = v.id;
        klucz = v.klucz;
        parent = v.parent;
        rank = v.rank;
    }
};

class edge
{
public:
    int v1;
    int v2;
    int waga;
public:
    edge()
    {
        v1 = -1;
        v2 = -1;
        waga = -1;
    }
    edge(int a, int b, int w)
    {
        v1 = a;
        v2 = b;
        waga = w;
    }

    void set_edge(int a, int b, int w)
    {
        v1 = a;
        v2 = b;
        waga = w;
    }

    int get_waga()
    {
        return waga;
    }

    void show_edge()
    {
        cout << v1 << " " << v2 << " " << waga << endl;
    }

    void operator=(const edge& e)
    {
        v1 = e.v1;
        v2 = e.v2;
        waga = e.waga;
    }
};

int find(int id, vertice tab[], int size)
{
    vertice v = tab[id - 1];
    if (v.parent == -1)
        return v.id;


    return v.parent = find(v.parent, tab, size);
}

void unite(int x, int y, vertice tab[], int size)
{
    int v1 = find(x, tab, size);
    int v2 = find(y, tab, size);

    if (v1 != v2) {
        if (tab[v1 - 1].rank < tab[v2 - 1].rank) {
            tab[v1 - 1].parent = tab[v2 - 1].id;
            tab[v2 - 1].rank += tab[v1 - 1].rank;
        }
        else {
            tab[v2 - 1].parent = tab[v1 - 1].id;
            tab[v1 - 1].rank += tab[v2 - 1].rank;
        }
    }
};

vertice* get_vertices(int size)
{
    vertice* arr = new vertice[size];
    return arr;
}

edge* get_edges(int size)
{
    edge* arr = new edge[size];
    return arr;
}

void swap(int* a, int* b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void swapEdge(edge* a, edge* b) {
    edge t;
    t = *a;
    *a = *b;
    *b = t;
}

int partition(edge array[], int low, int high) {

    int pivot = array[high].waga;

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j].waga <= pivot) {

            i++;

            swapEdge(&array[i], &array[j]);
        }
    }
    swapEdge(&array[i + 1], &array[high]);

    return (i + 1);
}

void quickSort(edge array[], int low, int high) {
    if (low < high) {

        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);

        quickSort(array, pi + 1, high);
    }
}


int main()
{
    int l_w; //liczba wierzcho³ków
    cin >> l_w;

    vertice* v_arr = get_vertices(l_w); //tablica wierzcho³ków

    int nr_w; //numer wierzcholka
    string klucz;

    for (int i = 0; i < l_w; i++)
    {
        cin >> nr_w;
        cin >> klucz;
        v_arr[nr_w - 1].set_vertice(nr_w, klucz);
    }
    /*for (int i = 0; i < l_w; i++)
    {

        v_arr[i].show_vertice();
    }*/

    int l_k; //liczba krawedzi
    cin >> l_k;

    edge* e_arr = get_edges(l_k); // tablica krawêdzi

    int nr_wierz1;
    int nr_wierz2;
    int waga;

    for (int i = 0; i < l_k; i++)
    {
        cin >> nr_wierz1;
        cin >> nr_wierz2;
        cin >> waga;
        e_arr[i].set_edge(nr_wierz1, nr_wierz2, waga);
    }
    quickSort(e_arr, 0, l_k - 1);// sortowanie krawedzi wg wag

    edge* e_sol = get_edges(l_k); // tablica rozwiazañ krawêdzi

    int e_pom = 0;


    for (int i = 0; i < l_k; i++)
    {

        int v1 = find(e_arr[i].v1, v_arr, l_w);
        int v2 = find(e_arr[i].v2, v_arr, l_w);

        if (v1 != v2)
        {
            unite(v1, v2, v_arr, l_w);
            e_sol[e_pom] = e_arr[i];
            e_pom++;
        }


    }

    //cout << endl << "wynik:" << endl;

    for (int i = 0; i < l_k; i++)
    {
        if (e_sol[i].waga != -1)
        {
            cout << v_arr[e_sol[i].v1 - 1].klucz << " " << v_arr[e_sol[i].v2 - 1].klucz << " " << e_sol[i].waga << endl;
        }
    }

    delete[] v_arr;
    delete[] e_arr;
}
