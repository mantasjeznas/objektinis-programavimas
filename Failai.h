#ifndef FAILAI_H
#define FAILAI_H

#include <iostream>
#include <string>
#include <vector>
#include "Studentas.h"

void failo_generavimas(int stud_sk, const std::string &failo_pav);
void rezultatu_isvedimas(std::ostream &out, std::vector<studentas> &grupe, int pasirinkimas, int rikiavimas);
bool nuskaityti_faila(const std::string &pav, std::vector<studentas> &grupe);
void greicio_analize(const std::string &pav);

#endif
