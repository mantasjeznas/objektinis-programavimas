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

void rezultatu_isvedimas(ostream &out, vector<studentas> &grupe, int pasirinkimas, int rikiavimas){
    if (rikiavimas == 1) std::sort(grupe.begin(), grupe.end(), pagal_varda);
    else if (rikiavimas == 3 && pasirinkimas == 2) std::sort(grupe.begin(), grupe.end(), pagal_mediana_mazejant);
    else if (rikiavimas == 3) std::sort(grupe.begin(), grupe.end(), pagal_vidurki_mazejant);
    else if (rikiavimas == 4 && pasirinkimas == 2) std::sort(grupe.begin(), grupe.end(), pagal_mediana_didejant);
    else if (rikiavimas == 4) std::sort(grupe.begin(), grupe.end(), pagal_vidurki_didejant);
    else std::sort(grupe.begin(), grupe.end(), pagal_pavarde);

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
    buf << string(linijos_ilgis, '-') << "\n";

    for (const studentas &S : grupe) printas(buf, S, pasirinkimas, pavardes_ilgis, vardo_ilgis);
    out << buf.str();
}

double greicio_analize(const string &pav){
    const int kartai = 3;
    vector<studentas> grupe;
    vector<studentas> kietiakai;
    vector<studentas> vargsiukai;

    if (!nuskaityti_faila(pav, grupe)){
        cout << "\nnerasta " << pav << ". sugeneruokite meniu 5 punktu.\n";
        return 0;
    }

    double t_skaitymas = 0;
    double t_skirstymas = 0;
    double t_rasymas = 0;

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        if (!nuskaityti_faila(pav, grupe)){
            cout << "\nNepavyko skaityti " << pav << "\n";
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
    }

    for (int i = 0; i < kartai; i++){
        auto start = std::chrono::steady_clock::now();
        std::ofstream varg("vargsiukai.txt");
        std::ofstream kiet("kietiakai.txt");
        if (!varg || !kiet){
            cout << "\nNepavyko irasyti rezultatu failu.\n";
            return 0;
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
     << std::setw(15) << "Studentu sk" << "| " << grupe.size() << "\n"
     << std::setw(15) << "Skaitymas" << "| " << t_skaitymas / kartai << " s\n"
     << std::setw(15) << "Skirstymas" << "| " << t_skirstymas / kartai << " s\n"
     << std::setw(15) << "Rasymas" << "| " << t_rasymas / kartai << " s\n";

    double bendras = (t_skaitymas + t_skirstymas + t_rasymas) / kartai;
    cout << std::setw(15) << "Bendras laikas" << "| " << bendras << " s\n";
    return bendras;
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

void irasyti_kategorijas(vector<studentas> &vargsiukai, vector<studentas> &kietiakai, int pasirinkimas, int rikiavimas){
    std::ofstream varg("vargsiukai.txt");
    std::ofstream kiet("kietiakai.txt");
    if (!varg || !kiet) {
        cout << "\nNepavyko sukurti/redaguoti failo.\n";
        return;
    }
    rezultatu_isvedimas(varg, vargsiukai, pasirinkimas, rikiavimas);
    rezultatu_isvedimas(kiet, kietiakai, pasirinkimas, rikiavimas);
    cout << "\nIrasyta i vargsiukai.txt (" << vargsiukai.size() << " studentu)\n";
    cout << "Irasyta i kietiakai.txt (" << kietiakai.size() << " studentu)\n";
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

void greicio_analizes_meniu(){
    int esami[5];
    int n = 0;
    for (int i = 0; i < 5; i++) {
        std::ifstream fd(failu_vardai[i]);
        if (fd) esami[n++] = i;
    }
    if (n == 0) {
        cout << "\nNera sugeneruotu failu. Sugeneruokite meniu 5 punktu.\n";
        return;
    }

    cout << "\nKuri faila testuoti?\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " - " << failu_vardai[esami[i]] << "\n";
    }
    if (n > 1) cout << n + 1 << " - visus esamus\n";

    int max_pasirinkimas = (n > 1) ? n + 1 : n;
    int kiekis = pasirinkimas_tarp(1, max_pasirinkimas);
    ignoruoti_eilute();

    if (n > 1 && kiekis == n + 1) {
        double bendras = 0;
        for (int i = 0; i < n; i++) bendras += greicio_analize(failu_vardai[esami[i]]);
        cout << "\nBendras visu failu laikas: " << bendras << " s\n";
    } else {
        greicio_analize(failu_vardai[esami[kiekis - 1]]);
    }
}
