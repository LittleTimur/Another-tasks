#include <iostream>
#include <fstream>
using namespace std;
template <class T>
class Priority_Queue
{
private:
    int capacity;
    int size;
    T* mas;
    void heapify_up(int);
    void heapify_down(int);
public:
    Priority_Queue();
    Priority_Queue(const Priority_Queue&);
    Priority_Queue(T*, int);
    ~Priority_Queue();
    void New_capacity(int);
    void insert(T);
    T get_min();
    T extract_min();
    void Show();
};
template <class T>
void Priority_Queue<T>::heapify_up(int i)
{
    bool t = true;
    while (t && i > 0)
        if (mas[i] < mas[(i + 1) / 2 - 1])
        {
            swap(mas[(i + 1) / 2 - 1], mas[i]);
            i = (i + 1) / 2 - 1;
        }
        else
            t = false;
}
template <class T>
void Priority_Queue<T>:: heapify_down(int i)
{
    bool t = true;
    while (t && 2 * (i + 1) - 1 < size)
        if (mas[i] > mas[2 * (i + 1) - 1] || (2 * (i + 1)< size && mas[i] > mas[2 * (i + 1)]))
        {
            int j = 2 * (i + 1) - 1;
            if (mas[j] > mas[2 * (i + 1)])
                j = 2 * (i + 1);
            swap(mas[i], mas[j]);
            i = j;
        }
        else
            t = false;
}
template <class T>
Priority_Queue<T>::Priority_Queue()
{
    size = 0;
    capacity = 0;
}
template <class T>
Priority_Queue<T>::Priority_Queue(const Priority_Queue<T>& orig )
{
    capacity = orig.capacity;
    size = orig.size;
    mas = new T[capacity];
    for (int i = 0; i < size; i++)
        mas[i] = orig.mas[i];
}
template <class T>
void Priority_Queue<T>::New_capacity(int delt)
{
    capacity += delt;
    T* mas1 = new T[capacity];
    for (int i = 0; i < size; i++)
        mas1[i] = mas[i];
    delete[] mas;
    mas = mas1;
}
template <class T>
void Priority_Queue<T>::insert(T x)
{
    if (size == capacity)
        New_capacity(10);
    mas[size] = x;
    size++;
}
template <class T>
Priority_Queue<T>::Priority_Queue(T* x, int n)
{
    capacity = n;
    size = 0;
    mas = new T[capacity];
    for (int i = 0; i < n; i++)
    {
        insert(x[i]);
        heapify_up(i);
    }
}
template <class T>
Priority_Queue<T>::~Priority_Queue()
{
    delete[] mas;
}
template <class T>
T Priority_Queue<T>::get_min()
{
    return mas[0];
}
template <class T>
T Priority_Queue<T>::extract_min()
{
    T x;
    x = mas[0];
    mas[0] = mas[size - 1];
    size--;
    heapify_down(0);
    return x;
}
template <class T>
void Priority_Queue<T>::Show()
{
    for (int i = 0; i < size; i++)
        cout << mas[i] << " ";
    cout << endl;
}
int main()
{
    ifstream fin("input.txt");
    int n;
    fin >> n;
    int* mas = new int[n];
    for(int i = 0; i < n; i++)
        fin >> mas[i];
    Priority_Queue<int> q(mas, n);
    cout << "min = " << q.get_min() << endl;
    q.Show();
    cout << "min = " << q.extract_min() << endl;
    q.Show();
    cout << "min = " << q.get_min() << endl;
    return 0;
}