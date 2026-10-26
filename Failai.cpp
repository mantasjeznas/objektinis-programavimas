#include "Failai.h"
#include "Pagalbiniai.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
using std::string;
using std::cout;

void failo_generavimas(int stud_sk, const string &failo_pav){
    auto start = std::chrono::steady_clock::now();

    std::ofstream fd(failo_pav);
    if (!fd) {
        cout << "Nepavyko sukurti " << failo_pav << "\n";
        return;
    }

    std::stringstream buf;
    buf << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    for (int i = 1; i <= stud_sk; i++) {
        buf << "Pavarde" << i << " Vardas" << i;
        for (int j = 0; j < 5; j++) buf << ' ' << random_pazymys();
        buf << ' ' << random_pazymys() << '\n';
    }
    fd << buf.str();
    fd.close();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> trukme = end - start;
    cout << "\nsukurtas " << failo_pav << " su " << stud_sk << " irasu\n";
    cout << "trukme: " << trukme.count() << " s\n";
}

int rikiavimo_pasirinkimas(){
    cout << "\nPagal ka rikiuoti?\n" << "1 - varda\n" << "2 - pavarde\n" << "3 - galutini bala\n";
    int rikiavimas = pasirinkimas_tarp(1, 3);
    if (rikiavimas == 3){
        cout << "\n1 - mazejancia\n" << "2 - didejancia\n";
        int tvarka = pasirinkimas_tarp(1, 2);
        if (tvarka == 2) rikiavimas = 4;
    }
    return rikiavimas;
}

void failu_generavimo_meniu(){
    cout << "\nKuri faila generuoti?\n"
    << "1 - 1,000 studentu | studentai1000.txt\n"
    << "2 - 10,000 studentu | studentai10000.txt\n"
    << "3 - 100,000 studentu | studentai100000.txt\n"
    << "4 - 1,000,000 studentu | studentai1000000.txt\n"
    << "5 - 10,000,000 studentu | studentai10000000.txt\n"
    << "6 - visus penkis\n";
    int kiekis = pasirinkimas_tarp(1, 6);
    ignoruoti_eilute();

    if (kiekis == 6) {
        for (int i = 0; i < 5; i++) failo_generavimas(failu_kiekiai[i], failu_vardai[i]);
    } else {
        failo_generavimas(failu_kiekiai[kiekis - 1], failu_vardai[kiekis - 1]);
    }
}
