#include <iostream>
#include <fstream>
using namespace std;
struct rood
{
    int data;
    rood* left;
    rood* right;
};
//35
void add(rood*& top, int x)
{
    if (!top)
    {
        top = new rood;
        top->data = x;
        top->left = NULL;
        top->right = NULL;
    }
    else
        if (top->data >= x)
            add(top->left, x);
        else
            add(top->right, x);
}
void Create(ifstream& f, rood*& top)
{
    int x;
    while (f.peek() != EOF)
    {
        f >> x;
        add(top, x);
    }
}
// 27
int count_x(rood* top, int x)
{
    if (!top)
        return 0;
    if (top->data == x)
        return 1 + count_x(top->left, x) + count_x(top->right, x);
    return count_x(top->left, x) + count_x(top->right, x);
}
// 28
int Sum(rood* top)
{
    if (!top)
        return 0;
    return top->data + Sum(top->left) + Sum(top->right);
}
// 29
int Hight(rood* top)
{
    if (!top)
        return 0;
    return 1 + max(Hight(top->left), Hight(top->right));
}
// 30
int count_ver(rood* top, int n, int i)
{
    if (n == i)
        return 1;
    return count_ver(top->left, n, i + 1) + count_ver(top->right, n, i + 1);
}
//31
void print_leaves(ofstream& f, rood* top)
{
    if (!top)
        return;
    if (!top->left && !top->right)
    {
        f << top->data << " ";
        return;
    }
    print_leaves(f, top->left);
    print_leaves(f, top->right);
}
//32
void delete_rood(rood*& top)
{
    if (!top)
        return;
    delete_rood(top->left);
    delete_rood(top->right);
    delete top;
    top = NULL;
}
//33
rood* Copy(rood* top)
{
    if (!top)
        return NULL;
    rood* p = new rood;
    p->data = top->data;
    p->left = Copy(top->left);
    p->right = Copy(top->right);
    return p;
}
//34
bool Equal(rood* top1, rood* top2)
{
    if (!top1 && !top2)
        return true;
    if (!top1 && top2 || top1 && !top2)
        return false;
    if (top1->data == top2->data)
        return Equal(top1->left, top2->left) && Equal(top1->right, top2->right);
    return false;
}
//36
rood* find_x(rood* top, int x)
{
    if (!top)
        return NULL;
    if (top->data == x)
        return top;
    if (top->data > x)
        return find_x(top->left, x);
    return find_x(top->right, x);
}
int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    rood* top = NULL;
    Create(fin, top);
    int x;

    //27
    cout << "x = ";
    cin >> x;
    fout << "x = " << x << "\ncount_x = " << count_x(top, x) << endl;

    //28
    fout << "sum = " << Sum(top) << endl;

    //29
    fout << "hight = " << Hight(top) << endl;

    //30
    int n;
    cout << "n = ";
    cin >> n;
    fout << "count_ver = " << count_ver(top, n, 1) << endl;

    //31
    fout << "rood's leaves: ";
    print_leaves(fout, top);
    fout << endl;

    //33
    rood* top2 = Copy(top);

    //32
    delete_rood(top2);

    //34
    top2 = Copy(top);
    fout << "is_equal: " << Equal(top, top2);

    delete_rood(top2);
    delete_rood(top);
    fin.close();
    fout.close();
    return 0;
}