#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct node
{
    int data;
    node* next;
};
void DFS(ofstream& f, node** g, int u, int pred, vector<char>& color, bool& t)
{
    f << "Перекрашиваем вершину " << u << " в серый цвет" << endl;
    color[u] = 'g';
    node* v = g[u];
    f << "Ищем вершины, смежные с " << u << endl;
    while (v != NULL)
    {
        if (v->data != pred)
        {
            f << "Вершина " << v->data << " соединена с вершиной " << u << " ребром" << endl << "Её цвет - ";
            if (color[v->data] == 'w')
            {
                f << "белый, поэтому запускаем DFS обход с вершины: " << v->data << endl;
                DFS(f, g, v->data, u, color, t);
            }
            else if (color[v->data] == 'b')
                f << "чёрный, поэтому ищем следующую смежную с " << u << " вершину" << endl;
            else
            {
                f << "серый, поэтому ищем следующую смежную с " << u << " вершину" << endl;
                t = true;
            }
        }
        v = v->next;
    }
    f << "Больше нет смежных с " << u <<" вершин" << endl << "Закончился DFS обход вершины " << u << ", поэтому перекрашиваем её в чёрный" <<endl;
    color[u] = 'b';
}
void Road_n(ofstream& f, node** g, int n, bool t)
{
    vector<char> color(n);
    for (int i = 0; i < n; i++)
        color[i] = 'w';
    f << "Начинаем DFS обход с вершины: 0" << endl;
    bool cycle = false;
    DFS(f, g, 0, 0, color, cycle);
    bool all_b = true;
    for (int i = 0; i < n && all_b; i++)
        if (color[i] == 'w')
            all_b = false;
    if (all_b)
        f << "Все вершины чёрного цвета, поэтому граф связный" << endl;
    else
        f << "Не все вершины чёрного цвета, поэтому граф несвязный" << endl;
    if (cycle)
        f << "Граф цикличный" << endl;
    else
        f << "Граф ацикличный" << endl;
}
void Road_o(ofstream& f, node** g, int n, bool t)
{
    vector<char> color(n);
    bool all_b = true;
    bool cycle = false;
    for (int i = 0; i < n && all_b; i++)
    {
        for (int i = 0; i < n; i++)
            color[i] = 'w';
        f << "Начинаем DFS обход с вершины: " << i << endl;
        DFS(f, g, i, i, color, cycle);
        for (int i = 0; i < n && all_b; i++)
            if (color[i] == 'w')
                all_b = false;
        if(!all_b)
            f << "Если начинать DFS обход с вершины " << i <<", то не все вершины будут чёрного цвета, поэтому граф несвязный" << endl;
    }
    if (all_b)
        f << "Все вершины чёрного цвета при любом начале DFS обхода, поэтому граф связный" << endl;
    if (cycle)
        f << "Граф цикличный" << endl;
    else
        f << "Граф ацикличный" << endl;

}
void push_back(node*& top, int x)
{
    if (!top)
    {
        top = new node;
        top->data = x;
        top->next = NULL;
        return;
    }
    node* temp1 = top, *temp2 = top->next;
    while (temp2 != NULL)
    {
        temp1 = temp2;
        temp2 = temp2->next;
    }
    temp2 = new node;
    temp2->data = x;
    temp2->next = NULL;
    temp1->next = temp2;
}
void Create_Graf_n(ifstream& f, node** g, int n, int v)
{
    for (int i = 0; i < n; i++)
        g[i] = NULL;
    for (int i = 0; i < v; i++)
    {
        int x, y;
        f >> x >> y;
        push_back(g[x], y);
        push_back(g[y], x);
    }
}
void Create_Graf_o(ifstream& f, node** g, int n, int v)
{
    for (int i = 0; i < n; i++)
        g[i] = NULL;
    for (int i = 0; i < v; i++)
    {
        int x, y;
        f >> x >> y;
        push_back(g[x], y);
    }
}
void Show_Graf(ofstream& f, node** g, int n)
{
    for (int i = 0; i < n; i++)
    {
        f << "Вершина " << i << " соеденена рёбрами с вершинами: ";
        node* temp = g[i];
        while (temp != NULL)
        {
            f << temp->data;
            if (temp->next)
                f << ", ";
            temp = temp->next;
        }
        f << ";" << endl;
    }
}
int main()
{
    setlocale(LC_ALL, "Ru");
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, v;
    char type;
    bool t = false;
    fin >> type;
    if (type == 'n')
        t = true;
    fin >> n >> v;
    if (t)
        fout << "Граф неориентированный" << endl;
    else
        fout << "Граф ориентированный" << endl;
    fout << "Количесво вершин графа: " << n << endl <<"Количество рёбер графа: " << v << endl;
    node** g = new node*[n];
    if (t)
        Create_Graf_n(fin, g, n, v);
    else
        Create_Graf_o(fin, g, n, v);
    fout << "Граф:" << endl;
    Show_Graf(fout, g, n);
    if (t)
        Road_n(fout, g, n, t);
    else
        Road_o(fout, g, n, t);
    fin.close();
    fout.close();
    return 0;
}