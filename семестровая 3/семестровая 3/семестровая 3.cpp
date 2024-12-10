#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int Indent = 7;
const int Lenght = 97;
struct Road
{
    int len = 0;
    char color = 'g';// green/yellow/red
};
struct node
{
    int data;
    node* next;
};
Road** Make(int);
void Create_tabl(ifstream&, Road**&);
void Create_mass(int*, int);
void push(node*&, int);
int Find_Color_Road(Road**&, int, int, char);
void Change_color(Road**&, int, int, char);
void FindRoad(Road**&, node*&, int*, int, int, int);
void pop(node*&, int&);
bool empty_list(node*);
int Distance(node*&, Road**);
void star(ofstream&);
void star1(ofstream&);
void Show(ofstream&, Road**, int, int, int);
void Show(ofstream&, node*);
void Show(ofstream&, int);
int main()
{
    setlocale(LC_ALL, "Ru");
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int x, y, n; // n - кол-во вершин
    fin >> n >> x >> y;
    Road** road = Make(n);
    Create_tabl(fin, road);
    Show(fout, road, n, x, y);
    int* age = new int[n]; // 1- новый, 0 - старый
    Create_mass(age, n);
    age[x - 1] = 0;
    node* top = NULL;
    FindRoad(road, top, age, n, x - 1, y - 1);
    Show(fout, top);
    int Lenght = Distance(top, road);
    Show(fout, Lenght);
    system("pause");
    return 0;
}
Road** Make(int n)
{
    Road** x = new Road * [n];
    for (int i = 0; i < n; i++)
        x[i] = new Road[n];
    return x;
}
void Create_tabl(ifstream& f, Road**& x)
{
    int i, j, l;
    while(!f.eof())
    {
        f >> i >> j >> l;
        x[i - 1][j - 1].len = l;
        x[j - 1][i - 1].len = l;
    }
}
void Create_mass(int* x, int n)
{
    for (int i = 0; i < n; i++)
        x[i] = 1;
}
void push(node*& top, int data)
{
    node* p;
    p = new node;
    p->data = data;
    p->next = top;
    top = p;
}
int Find_Color_Road(Road**& road, int n, int x, char a)
{
    int x1 = -1;
    bool b = false;
    for (int i = 0; i < n && !b; i++)
        if (road[i][x].len != 0 && road[i][x].color == a)
        {
            x1 = i;
            b = true;
        }
    return x1;
}
void Change_color(Road**& road, int i, int j, char a)
{
    road[i][j].color = a;
    road[j][i].color = a;
}
void FindRoad(Road**& road, node*& top, int* age, int n, int x, int y)
{
    int x1 = x;
    bool find = false;
    while (!find)
    {
        push(top, x1);
        x = x1;
        x1 = Find_Color_Road(road, n, x, 'g');
        if (x1 == -1)
        {
            x1 = top->next->data;
            if (road[x1][x].color == 'r')
                x1 = Find_Color_Road(road, n, x, 'y');
            Change_color(road, x, x1, 'r');
        }
        else if (x1 == y)
        {
            push(top, x1);
            find = true;
        }
        else if (age[x1] && road[x][x1].color == 'g')
        {
            Change_color(road, x, x1, 'y');
            age[x1] = 0;
        }
        else if (!age[x1] && road[x][x1].color == 'g')
        {
            Change_color(road, x, x1, 'r');
            push(top, x1);
            x1 = x;
        }
    }
}
void pop(node*& top, int& data)
{
    node* p;
    data = top->data;
    p = top->next;
    delete top;
    top = p;
}
bool empty_list(node* top)
{
    return top == NULL;
}
int Distance(node*& top, Road** road)
{
    node* p;
    int data1, data2, len = 0;
    pop(top, data1);
    while (!empty_list(top))
    {
        data2 = data1;
        pop(top, data1);
        len += road[data1][data2].len;
    }
    return len;
}
void star(ofstream& f)
{
    f.width(Indent + 1);
    for (int i = 0; i < Lenght; i++)
        f << "*";
    f << endl;
}
void star1(ofstream& f)
{
    f.width(Indent + 1);
    f << "*";
    for (int i = 0; i < 16; i++)
    {
        f.width(6);
        f << "*";
    }
    f << endl;
}
void Show(ofstream& f, Road** a, int n, int x, int y)
{
    f << "Поиск путей в схеме дорог" << endl;
    f << "Входные данные:" << endl;
    f << "n = " << n << endl;
    f << "x = " << x << endl;
    f << "y = " << y << endl;
    f << "Матрица смежности:" << endl;
    f.width(Indent + 4);
    for (int i = 0; i < n; i++)
    {
        f << i + 1;
        f.width(6);
    }
    f << endl;
    star(f);
    for (int i = 0; i < n; i++)
    {
        star1(f);
        f.width(Indent - 1);
        f << i + 1 << " ";
        f << "*";
        for (int j = 0; j < n; j++)
        {
            f.width(3);
            f << a[i][j].len;
            f.width(3);
            f << "*";
        }
        f << endl;
        star1(f);
        star(f);
    }
}
void Show(ofstream& f, node* top)
{
    f << "Пройденный путь:" << endl;
    f.width(Indent + 1);
    node* p = top;
    while (p)
    {
        f << p->data + 1 << " ";
        p = p->next;
    }
    f << endl;
}
void Show(ofstream& f, int lenght)
{
    f << "Пройденное расстояние: " << lenght << endl;
}