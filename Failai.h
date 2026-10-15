#ifndef FAILAI_H
#define FAILAI_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Studentas.h"
#include "Pagalbiniai.h"

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
void rezultatu_isvedimas(std::ostream &out, Konteineris &grupe, int pasirinkimas, int rikiavimas, bool ar_rikiuoti = true){
    if (ar_rikiuoti) rikiuoti_grupe(grupe, pasirinkimas, rikiavimas);

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

template <class Konteineris>
double greicio_analize(const std::string &pav){
    const int kartai = 3;
    Konteineris grupe;
    Konteineris kietiakai;
    Konteineris vargsiukai;

    if (!nuskaityti_faila(pav, grupe)){
        std::cout << "\nnerasta " << pav << ". sugeneruokite meniu 5 punktu.\n";
        return 0;
    }

    double t_skaitymas = 0;
    double t_skirstymas = 0;
    double t_rasymas = 0;
    double t_rusiavimas = 0;

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        if (!nuskaityti_faila(pav, grupe)){
            std::cout << "\nNepavyko skaityti " << pav << "\n";
            return 0;
        }
        auto end = std::chrono::steady_clock::now();
        t_skaitymas += std::chrono::duration<double>(end - start).count();
    }

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        skirstymas(grupe, kietiakai, vargsiukai, false);
        auto end = std::chrono::steady_clock::now();
        t_skirstymas += std::chrono::duration<double>(end - start).count();

        start = std::chrono::steady_clock::now();
        rikiuoti_grupe(vargsiukai, 1, 3);
        rikiuoti_grupe(kietiakai, 1, 3);
        end = std::chrono::steady_clock::now();
        t_rusiavimas += std::chrono::duration<double>(end - start).count();
    }

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        std::ofstream varg("vargsiukai.txt");
        std::ofstream kiet("kietiakai.txt");
        if (!varg || !kiet){
            std::cout << "\nNepavyko irasyti rezultatu failu.\n";
            return 0;
        }
        rezultatu_isvedimas(varg, vargsiukai, 1, 3, false);
        rezultatu_isvedimas(kiet, kietiakai, 1, 3, false);
        varg.close();
        kiet.close();
        auto end = std::chrono::steady_clock::now();
        t_rasymas += std::chrono::duration<double>(end - start).count();
    }

    std::cout << "\n--- " << pav << " (" << kartai << " kartu vidurkiai) ---\n";
    std::cout << std::defaultfloat << std::setprecision(6);
    std::cout << std::left
     << std::setw(15) << "Studentu sk" << "| " << grupe.size() << "\n"
     << std::setw(15) << "Skaitymas" << "| " << t_skaitymas / kartai << " s\n"
     << std::setw(15) << "Skirstymas" << "| " << t_skirstymas / kartai << " s\n"
     << std::setw(15) << "Rasymas" << "| " << t_rasymas / kartai << " s\n"
     << std::setw(15) << "Rusiavimas" << "| " << t_rusiavimas / kartai << " s\n";

    double bendras = (t_skaitymas + t_skirstymas + t_rasymas + t_rusiavimas) / kartai;
    std::cout << std::setw(15) << "Bendras laikas" << "| " << bendras << " s\n";
    return bendras;
}

template <class Konteineris>
void greicio_analize_meniu(){
    int esami[5];
    int n = 0;
    for (int i = 0; i < 5; i++) {
        std::ifstream fd(failu_vardai[i]);
        if (fd) esami[n++] = i;
    }
    if (n == 0) {
        std::cout << "\nNera sugeneruotu failu. Sugeneruokite meniu 5 punktu.\n";
        return;
    }

    std::cout << "\nKuri faila testuoti?\n";
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << " - " << failu_vardai[esami[i]] << "\n";
    }
    if (n > 1) std::cout << n + 1 << " - visus esamus\n";

    int max_pasirinkimas = (n > 1) ? n + 1 : n;
    int kiekis = pasirinkimas_tarp(1, max_pasirinkimas);
    ignoruoti_eilute();

    if (n > 1 && kiekis == n + 1) {
        double bendras = 0;
        for (int i = 0; i < n; i++) bendras += greicio_analize<Konteineris>(failu_vardai[esami[i]]);
        std::cout << "\nBendras visu failu laikas: " << bendras << " s\n";
    } else {
        greicio_analize<Konteineris>(failu_vardai[esami[kiekis - 1]]);
    }
}

#endif
