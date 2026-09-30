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
void skirstymas(const std::vector<studentas> &grupe, std::vector<studentas> &kietiakai, std::vector<studentas> &vargsiukai, bool ar_mediana);

#endif
