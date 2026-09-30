#include "Studentas.h"
#include <algorithm>
#include <iomanip>
#include <vector>
using std::vector;
using std::ostream;

double vidurkis(const studentas &A){
    if (A.paz.empty()) return 0;
    double suma = 0;
    for (int p : A.paz){
        suma += p;
    }
    return suma / A.paz.size();
}

double mediana(const studentas &A){
    if (A.paz.empty()) return 0;
    vector<int> laikinas = A.paz;
    std::sort(laikinas.begin(), laikinas.end());
    int n = laikinas.size();
    if (n % 2 == 1) return laikinas[n / 2];
    return (laikinas[n / 2 - 1] + laikinas[n / 2]) / 2.0;
}

double galutinis(const studentas &A, bool ar_mediana){
    if (ar_mediana == true){
        return 0.4 * mediana(A) + 0.6 * A.exam;
    }
    return 0.4 * vidurkis(A) + 0.6 * A.exam;
}

void printas(ostream &out, const studentas &A, int pasirinkimas, int pavardes_ilgis, int vardo_ilgis){
    // out gali buti cout arba jau atidarytas failas.
    out << std::left << std::setw(pavardes_ilgis) << A.pavarde
        << std::left << std::setw(vardo_ilgis) << A.vardas
        << std::fixed << std::setprecision(2);

    if (pasirinkimas == 1){
        out << galutinis(A, false) << "\n";
    } else if (pasirinkimas == 2){
        out << galutinis(A, true) << "\n";
    } else{
        out << std::left << std::setw(18) << galutinis(A, false) << galutinis(A, true) << "\n";
    }
}

bool pagal_pavarde(const studentas &a, const studentas &b){
    if (a.pavarde == b.pavarde) return a.vardas < b.vardas;
    return a.pavarde < b.pavarde;
}

bool pagal_varda(const studentas &a, const studentas &b){
    if (a.vardas == b.vardas) return a.pavarde < b.pavarde;
    return a.vardas < b.vardas;
}

void skirstymas(const vector<studentas> &grupe, vector<studentas> &kietiakai, vector<studentas> &vargsiukai, bool ar_mediana){
    vargsiukai.clear();
    kietiakai.clear();
    for (const studentas &S : grupe){
        if (galutinis(S, ar_mediana) < 5.0) vargsiukai.push_back(S);
        else kietiakai.push_back(S);
    }
}
