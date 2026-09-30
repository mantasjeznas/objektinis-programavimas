#include "Pagalbiniai.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using std::cin;
using std::cout;

int skaicius_input(){
    int sk;
    while (!(cin >> sk)) {
        cout << "Netinkama ivestis. Iveskite skaiciu: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return sk;
}

int pazymio_apribojimas(){
    while (true) {
        int x = skaicius_input();
        if (x >= 0 && x <= 10) return x;
        cout << "Pazymys turi buti nuo 0 iki 10: ";
    }
}

void ignoruoti_eilute(){
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int random_pazymys(){
    return rand() % 11;
}
