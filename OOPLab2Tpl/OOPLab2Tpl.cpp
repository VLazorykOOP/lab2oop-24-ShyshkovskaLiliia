
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

void Shifruvanna(char S[64], unsigned short Rez[64]) {
    unsigned char c;
    unsigned short r,i,b,t;
    short j;

    for (i = 0; i < 64; i++) {
        r = 0;
        c = S[i]; 
        t = 1; 
        // Позиція символу в рядку (6 бітів, біти 0-5)
        r |= (i & 0x3F); // 0x3F = 00111111 (6 бітів)
        // Старша частина ASCII - коду (4 біти, біти 6-9)
        r |= ((c >> 4) & 0xF) << 6;
        // Обчислення біта парності для перших двох полів (біти 0-9)
        b = 0;
        for (j = 0; j < 10; j++) {
            if (r & t) {
                if (b == 0) b = 1; else b = 0; 
            }
            t <<= 1; 
        }
        r |= b << 10; 
        // Молодша частина ASCII - коду (4 біти, біти 11-14)
        r |= (c & 0xF) << 11;
        // Обчислення біта парності для попереднього поля (біти 11-14)
        b = 0;
        for (j = 11; j < 15; j++) {
            if (r & (1 << j)) {
                if (b == 0) b = 1; else b = 0;
            }
        }
        r |= b << 15; 
        Rez[i] = r; 
    }
}

int main() {
    char S[64] = {0}; 
    unsigned short Rez[64];
    unsigned short i;
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Помилка відкриття файлу!" << endl;
        return 1;
    }
    inputFile.get(S, 64);
    inputFile.close();

    for (i = 0; i < 64; i++) {
        if (S[i] == '\0') {
            S[i] = ' ';
        }
    }

    Shifruvanna(S, Rez);
    cout << "Зашифрований результат у шістнадцятковому форматі:" << endl;
    for (i = 0; i < 64; i++) {
        cout << hex << Rez[i] << endl;
    }

    ofstream outputFile("encrypted.bin", ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return 1;
    }
    outputFile.write(reinterpret_cast<char*>(Rez), sizeof(Rez));
    outputFile.close();

    cout << "Результат записано у файл 'encrypted.bin'." << endl;

    return 0;
}
