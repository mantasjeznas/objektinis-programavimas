#include "Studentas.h"
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include "Pagalbiniai.h"
using std::vector;
using std::ostream;
using std::string;
using std::cout;
using std::cin;

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

bool pagal_vidurki_mazejant(const studentas &a, const studentas &b){
    if (galutinis(a, false) == galutinis(b, false)) return pagal_pavarde(a, b);
    return galutinis(a, false) > galutinis(b, false);
}

bool pagal_vidurki_didejant(const studentas &a, const studentas &b){
    if (galutinis(a, false) == galutinis(b, false)) return pagal_pavarde(a, b);
    return galutinis(a, false) < galutinis(b, false);
}

bool pagal_mediana_mazejant(const studentas &a, const studentas &b){
    if (galutinis(a, true) == galutinis(b, true)) return pagal_pavarde(a, b);
    return galutinis(a, true) > galutinis(b, true);
}

bool pagal_mediana_didejant(const studentas &a, const studentas &b){
    if (galutinis(a, true) == galutinis(b, true)) return pagal_pavarde(a, b);
    return galutinis(a, true) < galutinis(b, true);
}

void skirstymas(const vector<studentas> &grupe, vector<studentas> &kietiakai, vector<studentas> &vargsiukai, bool ar_mediana){
    vargsiukai.clear();
    kietiakai.clear();
    for (const studentas &S : grupe){
        if (galutinis(S, ar_mediana) < 5.0) vargsiukai.push_back(S);
        else kietiakai.push_back(S);
    }
}

studentas ivesti_studenta(){
    studentas A;
        cout<<"Iveskite per tarpa studento varda ir pavarde: ";
        cin>>A.vardas>>A.pavarde;
        ignoruoti_eilute();

        cout << "1 - pazymius vesti ranka, 2 - generuoti atsitiktinai: ";
        int rezimas = skaicius_input();
        while (rezimas != 1 && rezimas != 2) {
            cout << "Klaida. Iveskite 1 arba 2: ";
            rezimas = skaicius_input();
        }
        ignoruoti_eilute();

        cout<<"Iveskite semestro paz. kieki: ";

        if (rezimas == 2){
            int k = skaicius_input();
            while (k < 0){
                cout << "Pazymiu kiekis negali buti neigiamas!\n";
                cout<<"Iveskite semestro paz. kieki: ";
                k = skaicius_input();
            }
            for (int i = 0; i < k; i++){
                A.paz.push_back(random_pazymys());
            }
            A.exam = random_pazymys();
            ignoruoti_eilute();
        } else{
            string ivedimas;
            getline(cin, ivedimas);

            if (ivedimas.empty()){
            int i = 0;
            while(true){
                cout << "Iveskite " << i + 1 << " paz: ";
                getline(cin, ivedimas);
                if (ivedimas.empty()) break;
                try{
                    int paz = std::stoi(ivedimas);
                    if (paz < 0 || paz > 10){
                        cout << "Pazymys turi buti nuo 0 iki 10\n";
                        continue;
                    }
                    A.paz.push_back(paz);
                    i++;
                } catch(const std::exception&){
                    cout << "Klaida. Iveskite skaiciu\n";
                }
            }
            } else{
                int k;
                try{
                    k = std::stoi(ivedimas);
                } catch (const std::exception&){
                k = -1;
                }
                while (k < 0){
                    cout << "Bloga ivestis. Iveskite semestro paz. kieki: \n";
                    k = skaicius_input();
                }
                for (int i = 0; i < k; i++){
                    cout << "Iveskite " << i + 1 << " paz: ";
                    int a = pazymio_apribojimas();
                    A.paz.push_back(a);
                }
                ignoruoti_eilute();
            }

        cout<<"Iveskite semestro Egzamino paz.: "; A.exam = pazymio_apribojimas();
        ignoruoti_eilute();

        }
    return A;
}
