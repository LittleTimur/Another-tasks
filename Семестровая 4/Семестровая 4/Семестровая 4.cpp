#include <iostream>
#include <fstream>
using namespace std;
void Show(ifstream& fin, ofstream& fout)
{
    fout << "Входные данные:" << endl;
    char x;
    while (fin >> x)
    {
        fout << x;
    }
    fout << endl << endl;
}
void ShowMistake(ofstream& f, int k)
{
    if (k == 0 || k == 18)
        f << "Ошибка. Ожидался символ: 'A'...'Z'";
    else if (k == 1)
        f << "Ошибка. Ожидался символ: 'A'...'Z' или '0'...'9'";
    else if (k == 2 || k == 14)
        f << "Ошибка. Ожидался символ: ':'";
    else if (k == 3 || k == 15)
        f << "Ошибка. Ожидался символ: '='";
    else if (k == 16)
        f << "Ошибка. Ожидался символ: '!', или '%', или '^'";
    else if (k >= 4 && k <= 11)
        f << "Ошибка. Ожидался символ: '0' или '1'";
    else if (k == 17)
        f << "Ошибка. Ожидался символ: 'A'...'Z', или '0', или '1'";
    else if (k == 12)
        f << "Ошибка. Ожидался символ: ';'";
    else if (k == 13)
        f << "Ошибка. Ожидался символ: 'A'...'Z' или ' '";

}
int main()
{
    setlocale(LC_ALL, "Ru");
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    Show(fin, fout);
    fin.clear();
    fin.seekg(0);
    char x;
    int q = 0, k = 0;
    fout << "Выходные данные:" << endl;
    while (fin.peek() != EOF && q != 20)
    {
        fin.get(x);
        switch (q)
        {
        case 0:
            if (x >= 'A' && x <= 'Z')
            {
                fout << x;
                q = 1;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 1:
            if (x >= 'A' && x <= 'Z')
            {
                fout << x;
                q = 2;
            }
            else if (x >= '0' && x <= '9')
            {
                fout << x;
                q = 14;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 2:
            if (x == ':')
            {
                fout << x;
                q = 3;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 3:
            if (x == '=')
            {
                fout << x;
                q = 4;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 4:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 5;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 5:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 6;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 6:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 7;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 7:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 8;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 8:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 9;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 9:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 10;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 10:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 11;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 11:
            if (x == '1' || x == '0')
            {
                fout << x;
                q = 12;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 12:
            if (x == ';')
            {
                fout << x;
                q = 13;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 13:
            if (x >= 'A' && x <= 'Z')
            {
                fout << x;
                q = 1;
            }
            else if (x == ' ')
                q = 19;
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 14:
            if (x == ':')
            {
                fout << x;
                q = 15;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 15:
            if (x == '=')
            {
                fout << x;
                q = 16;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 16:
            if (x == '!' || x == '%' || x == '^')
            {
                fout << x;
                q = 17;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 17:
            if (x >= 'A' && x <= 'Z')
            {
                fout << x;
                q = 18;
            }
            else if (x == '1' || x == '0')
                q = 5;
            else
            {
                k = q;
                q = 20;
            }
            break;
        case 18:
            if (x >= 'A' && x <= 'Z')
            {
                fout << x;
                q = 12;
            }
            else
            {
                k = q;
                q = 20;
            }
            break;
        }
    }
    fout << endl;
    if (q == 19)
        fout << "Ошибок не выявлено";
    else
        ShowMistake(fout, k);
    return 0;
}