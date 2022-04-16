#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;

int transfer(int byte, int radix) {
    int res = 0, k = 1;
    for (int i = 0; byte != 0; ++i) {
        res += (byte % radix) * k;
        k <<= 1;
        byte /= radix;
    }
    return res;
}

void Decompress(vector<string>& dec, int arg) {
    for (int i = dec.size() - 1; i >= 0; --i) {
        arg %= 2;
        int cnt = stoi(dec[i]);
        dec[i].clear();
        for (int j = 0; j < cnt; ++j)  dec[i].push_back(static_cast<char>(arg + 48));
        ++arg;
    }
}

void DeleteNull(string& str) {
    int cnt = 0;
    for (int i = 0; i < str.size() && str[i] != '\0'; ++i) {
        if (str[i] == '0') {
            ++cnt;
            str.erase(i--, 1);
        }
        else if (cnt) {
            i = i + cnt + 1;
            str.insert(i, " ");
            cnt = 0;
        }
        else str.insert(++i, " ");
    }
}

vector<string> InDEC(const string& str) {
    vector<string> res;
    int combo, p;
    for (int i = str.size() - 1; i >= 0; --i) {
        if (str[i] == ' ') {
            combo = 0;
            p = 0;
            for (int j = i - 1; j >= 0 && str[j] != ' ' ; --j)
                combo = combo + (static_cast<int>(str[j]) - 48) * static_cast<int>(1 << p++);
            res.push_back(to_string(combo));
        }
    }
    return res;
}

void Decode_and_Otput(const vector<string>& dec) {
    string res, symb;
    for (int i = 0; i < dec.size(); ++i) res += dec[i];
    int isfull = (res.size()) % 8;
    if (isfull) {
        int cntnon = isfull;
        for (int j = res.size() - 1; --cntnon >= 0; --j)  symb += res[j];
        unsigned char symbol = transfer(stoi(symb), 10);
        symb.clear();
        cout << symbol;
    }
    for (int j = res.size() - isfull - 1; j >= 0; --j) {
        symb += res[j];
        if (symb.size() == 8) {
            unsigned char symbol = static_cast<unsigned char>(transfer(stoi(symb), 10));
            symb.clear();
            cout << symbol;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    string str;
    getline(cin, str);

    str.erase(0, 1);
    for (int i = 0; i < str.size(); ++i) if (str[i] == ' ') str.erase(i, 1);

    DeleteNull(str);
    vector <string> dec = InDEC(str);

    Decompress(dec, str[0] % 48);
    Decode_and_Otput(dec);
    
    system("pause");
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
