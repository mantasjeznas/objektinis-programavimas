#ifndef FAILAI_H
#define FAILAI_H

#include <iostream>
#include <string>
#include <vector>
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
void rezultatu_isvedimas(std::ostream &out, std::vector<studentas> &grupe, int pasirinkimas, int rikiavimas);
bool nuskaityti_faila(const std::string &pav, std::vector<studentas> &grupe);
double greicio_analize(const std::string &pav);

int rikiavimo_pasirinkimas();
void irasyti_kategorijas(std::vector<studentas> &vargsiukai, std::vector<studentas> &kietiakai, int pasirinkimas, int rikiavimas);
void failu_generavimo_meniu();
void greicio_analizes_meniu();

#endif
