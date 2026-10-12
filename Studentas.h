#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>

struct studentas {
    std::string vardas, pavarde;
    std::vector<int> paz;
    int exam;
};

double vidurkis(const studentas &A);
double mediana(const studentas &A);
double galutinis(const studentas &A, bool ar_mediana);
void printas(std::ostream &out, const studentas &A, int pasirinkimas, int pavardes_ilgis, int vardo_ilgis);
bool pagal_pavarde(const studentas &a, const studentas &b);
bool pagal_varda(const studentas &a, const studentas &b);
bool pagal_vidurki_mazejant(const studentas &a, const studentas &b);
bool pagal_vidurki_didejant(const studentas &a, const studentas &b);
bool pagal_mediana_mazejant(const studentas &a, const studentas &b);
bool pagal_mediana_didejant(const studentas &a, const studentas &b);
studentas ivesti_studenta();

template <class Konteineris>
void skirstymas(const Konteineris &grupe, Konteineris &kietiakai, Konteineris &vargsiukai, bool ar_mediana){
    vargsiukai.clear();
    kietiakai.clear();
    for (const studentas &S : grupe){
        if (galutinis(S, ar_mediana) < 5.0) vargsiukai.push_back(S);
        else kietiakai.push_back(S);
    }
}

#endif
