#ifndef FAILAI_H
#define FAILAI_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Studentas.h"

const int failu_kiekiai[5] = {1000, 10000, 100000, 1000000, 10000000};
const char *const failu_vardai[5] = {
    "studentai1000.txt",
    "studentai10000.txt",
    "studentai100000.txt",
    "studentai1000000.txt",
    "studentai10000000.txt"
};

void failo_generavimas(int stud_sk, const std::string &failo_pav);
void rikiuoti_grupe(std::vector<studentas> &grupe, int pasirinkimas, int rikiavimas);
void rikiuoti_grupe(std::list<studentas> &grupe, int pasirinkimas, int rikiavimas);

template <class Konteineris>
void rezultatu_isvedimas(std::ostream &out, Konteineris &grupe, int pasirinkimas, int rikiavimas){
    rikiuoti_grupe(grupe, pasirinkimas, rikiavimas);

    int pavardes_ilgis = 12;
    int vardo_ilgis = 12;
    for (const studentas &S : grupe){
        if ((int)S.pavarde.size() + 2 > pavardes_ilgis) pavardes_ilgis = (int)S.pavarde.size() + 2;
        if ((int)S.vardas.size() + 2 > vardo_ilgis) vardo_ilgis = (int)S.vardas.size() + 2;
    }

    std::stringstream buf;
    buf << std::left << std::setw(pavardes_ilgis) << "Pavarde" << std::left << std::setw(vardo_ilgis) << "Vardas";
    if (pasirinkimas == 1) buf << "Galutinis (Vid.)\n";
    else if (pasirinkimas == 2) buf << "Galutinis (Med.)\n";
    else buf << std::left << std::setw(18) << "Galutinis (Vid.)" << "Galutinis (Med.)\n";

    int linijos_ilgis = pavardes_ilgis + vardo_ilgis + 16;
    if (pasirinkimas == 3) linijos_ilgis = pavardes_ilgis + vardo_ilgis + 34;
    buf << std::string(linijos_ilgis, '-') << "\n";

    for (const studentas &S : grupe) printas(buf, S, pasirinkimas, pavardes_ilgis, vardo_ilgis);
    out << buf.str();
}

double greicio_analize(const std::string &pav);

template <class Konteineris>
bool nuskaityti_faila(const std::string &pav, Konteineris &grupe){
    std::ifstream fd(pav);
    if (!fd) return false;

    grupe.clear();
    std::string eilute;
    std::stringstream buf;
    buf << fd.rdbuf();
    fd.close();
    getline(buf, eilute);

    studentas A;
    std::stringstream ss;
    while (getline(buf, eilute)){
        ss.clear();
        ss.str(eilute);
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

int rikiavimo_pasirinkimas();

template <class Konteineris>
void irasyti_kategorijas(Konteineris &vargsiukai, Konteineris &kietiakai, int pasirinkimas, int rikiavimas){
    std::ofstream varg("vargsiukai.txt");
    std::ofstream kiet("kietiakai.txt");
    if (!varg || !kiet) {
        std::cout << "\nNepavyko sukurti/redaguoti failo.\n";
        return;
    }
    rezultatu_isvedimas(varg, vargsiukai, pasirinkimas, rikiavimas);
    rezultatu_isvedimas(kiet, kietiakai, pasirinkimas, rikiavimas);
    std::cout << "\nIrasyta i vargsiukai.txt (" << vargsiukai.size() << " studentu)\n";
    std::cout << "Irasyta i kietiakai.txt (" << kietiakai.size() << " studentu)\n";
}

void failu_generavimo_meniu();
void greicio_analizes_meniu();

#endif
