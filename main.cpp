#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Meniu.h"
using std::vector;
using std::cout;

int main(){
    srand(time(nullptr));
    cout << "\n=== Studentu DB ===\n";
    cout << "Kuri konteineri naudoti?\n"
    << "1 - vector\n"
    << "2 - list\n";
    int konteineris = pasirinkimas_tarp(1, 2);
    ignoruoti_eilute();

    if (konteineris == 1) programa<vector<studentas<vector<int>>>, vector<int>>();
    else programa<std::list<studentas<std::list<int>>>, std::list<int>>();
    return 0;
}
