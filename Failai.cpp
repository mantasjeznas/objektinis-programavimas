#include "Failai.h"
#include "Pagalbiniai.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <chrono>
using std::string;
using std::vector;
using std::cout;
using std::ostream;

void failo_generavimas(int stud_sk, const string &failo_pav){
    auto start = std::chrono::steady_clock::now();

    std::ofstream fd(failo_pav);
    if (!fd) {
        cout << "Nepavyko sukurti " << failo_pav << "\n";
        return;
    }

    fd << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    for (int i = 1; i <= stud_sk; i++) {
        fd << "Pavarde" << i << " Vardas" << i;
        for (int j = 0; j < 5; j++) fd << ' ' << random_pazymys();
        fd << ' ' << random_pazymys() << '\n';
    }
    fd.close();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> trukme = end - start;
    cout << "\nsukurtas " << failo_pav << " su " << stud_sk << " irasu\n";
    cout << "trukme: " << trukme.count() << " s\n";
}

void rezultatu_isvedimas(ostream &out, vector<studentas> &grupe, int pasirinkimas, int rikiavimas){
    if (rikiavimas == 1) std::sort(grupe.begin(), grupe.end(), pagal_varda);
    else std::sort(grupe.begin(), grupe.end(), pagal_pavarde);

    int pavardes_ilgis = 12;
    int vardo_ilgis = 12;
    for (const studentas &S : grupe){
        if ((int)S.pavarde.size() + 2 > pavardes_ilgis) pavardes_ilgis = (int)S.pavarde.size() + 2;
        if ((int)S.vardas.size() + 2 > vardo_ilgis) vardo_ilgis = (int)S.vardas.size() + 2;
    }

    out << std::left << std::setw(pavardes_ilgis) << "Pavarde" << std::left << std::setw(vardo_ilgis) << "Vardas";
    if (pasirinkimas == 1) out << "Galutinis (Vid.)\n";
    else if (pasirinkimas == 2) out << "Galutinis (Med.)\n";
    else out << std::left << std::setw(18) << "Galutinis (Vid.)" << "Galutinis (Med.)\n";

    int linijos_ilgis = pavardes_ilgis + vardo_ilgis + 16;
    if (pasirinkimas == 3) linijos_ilgis = pavardes_ilgis + vardo_ilgis + 34;
    out << string(linijos_ilgis, '-') << "\n";

    for (const studentas &S : grupe) printas(out, S, pasirinkimas, pavardes_ilgis, vardo_ilgis);
}
