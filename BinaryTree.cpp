#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>

#include <cmath>

using namespace std;

struct wezel
{
    int value;
    wezel *right;
    wezel *left;
};

void BST_insert(wezel *&r, int x) //funkcja do tworzenia drzewa binarnego
{
    if(r == NULL)
    {
        wezel *nowy = new wezel;
        nowy->value = x;
        nowy->right = NULL;
        nowy->left = NULL;
        r = nowy;
    }
    else if(x >= r->value)
        BST_insert(r->right, x);
    else
        BST_insert(r->left, x);
}

wezel* BST_search(wezel *r, int x) //funkcja do szukania zadanego elementu
{
    if((r==NULL) or (r->value == x))
        return r;
    else
        if(x < r->value)
            return BST_search(r->left, x);
        else
            return BST_search(r->right, x);
}

void BT_remove(wezel *nowy) //funkcja do usuwania drzewa
{
    if(nowy)
    {
        BT_remove(nowy->left);
        BT_remove(nowy->right);
        delete nowy;
    }
}

void print_BT(wezel *wezel, int level) // funkcja do rysowania drzewa w konsoli`
{
    if(wezel)
    {
        print_BT(wezel->right, level+1);
        for(int i = level; i > 0; i--)
            cout << "    ";
        cout << wezel->value << endl;
        print_BT(wezel->left, level+1);
    }
}

int* BT_fullRandom(int n, int valOff)
{
    if(n == 0)
    {
        int* ret = new int[1];
        ret[0] = valOff + 1;
        return ret;
    }

    int c = pow(2, n);
    int* L = BT_fullRandom(n - 1, 0);
    int* R = BT_fullRandom(n - 1, c);
    int* ret = new int[2*c-1];
    ret[0] = valOff + c;
    int i = 1;
    for(;i < c;i++)
        ret[i] = valOff + L[i - 1];
    for(;i < 2*c-1;i++)
        ret[i] = valOff + R[i - c];
    return ret;
}

int main()
{
    bool runFlag = true;
    wezel *root = NULL;
    srand( time( NULL ) );
    int choice;
    int wstawiany;

    while(runFlag)
    {
        system("cls"); // œrednik na koñcu dodany
        cout << " Menu do obslugi programu do drzewa binarnego. " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "        Wybor zadania do zrealizowania:        " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "[1] - Losowanie  drzewa                        " << endl;
        cout << "[2] - Dodanie wartosci do drzewa               " << endl;
        cout << "[3] - Rysowanie drzewa                              " << endl;
        cout << "[4]                                            " << endl;
        cout << "[5] - Wyjœcie z programu                       " << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Twoj wybor to:                                 " << endl;
        /*cin >> choice << endl;*/
        cin >> choice;
        system("cls"); // œrednik na koñcu dodany

        switch(choice)
        {
        case 1 :
            {
                cout << "Podaj maksymalna wartosc w drzewie: ";
                int maxVal;
                cin >> maxVal;

                cout << "Podaj liczbe poziomow drzewa: ";
                int n;
                cin >> n;

                int step = maxVal / static_cast<int>(pow(2, n+1));
                int* vals = BT_fullRandom(n, 0);

                int c = pow(2, n+1)-1;
                for(int i = 0; i < c; i++)
                {
                    BST_insert(root, (vals[i]-1) * step + rand() % step);
                }
                break;
            }
        case 2 :
                cout << "Podaj wartosc do wstawienia: ";
                cin >> wstawiany;
                BST_insert(root, wstawiany);
                break;
        case 3 :
                print_BT(root, 0);
                system("pause");
                break; break;
        case 4 :

        case 5 :
            cout << "Opuszczanie programu." << endl;
            runFlag = false;
            break;
        }
    }
    BT_remove(root);
    return 0;
}
