#include "Failai.h"
#include "Pagalbiniai.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <sstream>
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

bool nuskaityti_faila(const string &pav, vector<studentas> &grupe){
    std::ifstream fd(pav);
    if (!fd) return false;

    grupe.clear();
    string eilute;
    getline(fd, eilute);

    studentas A;
    while (getline(fd, eilute)){
        std::stringstream ss(eilute);
        ss >> A.pavarde >> A.vardas;

        A.paz.clear();
        int x;
        while (ss >> x) A.paz.push_back(x);

        if (A.paz.empty()) continue;
        A.exam = A.paz.back();
        A.paz.pop_back();
        grupe.push_back(A);
        A.paz.clear();
    }
    return true;
}

void greicio_analize(const string &pav){
    const int kartai = 3;
    vector<studentas> grupe;
    vector<studentas> kietiakai;
    vector<studentas> vargsiukai;

    if (!nuskaityti_faila(pav, grupe)){
        cout << "\nnerasta " << pav << ". sugeneruokite meniu 5 punktu.\n";
        return;
    }

    double t_skaitymas = 0;
    double t_skirstymas = 0;
    double t_rasymas = 0;

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        if (!nuskaityti_faila(pav, grupe)){
            cout << "\nNepavyko skaityti " << pav << "\n";
            return;
        }
        auto end = std::chrono::steady_clock::now();
        t_skaitymas += std::chrono::duration<double>(end - start).count();
    }

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        skirstymas(grupe, kietiakai, vargsiukai, false);
        auto end = std::chrono::steady_clock::now();
        t_skirstymas += std::chrono::duration<double>(end - start).count();
    }

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        std::ofstream varg("vargsiukai.txt");
        std::ofstream kiet("kietiakai.txt");
        if (!varg || !kiet){
            cout << "\nNepavyko irasyti rezultatu failu.\n";
            return;
        }
        rezultatu_isvedimas(varg, vargsiukai, 1, 2);
        rezultatu_isvedimas(kiet, kietiakai, 1, 2);
        varg.close();
        kiet.close();
        auto end = std::chrono::steady_clock::now();
        t_rasymas += std::chrono::duration<double>(end - start).count();
    }

    cout << "\n--- " << pav << " (" << kartai << " kartu vidurkiai) ---\n";
    cout << std::defaultfloat << std::setprecision(6);
    cout << std::left
     << std::setw(14) << "Studentu sk" << "| " << grupe.size() << "\n"
     << std::setw(14) << "Skaitymas" << "| " << t_skaitymas / kartai << " s\n"
     << std::setw(14) << "Skirstymas" << "| " << t_skirstymas / kartai << " s\n"
     << std::setw(14) << "Rasymas" << "| " << t_rasymas / kartai << " s\n";
}
