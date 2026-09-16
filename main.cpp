#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using std::string;
using std::vector;
using std::cout;
using std::cin;

struct studentas{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

int skaicius_input();
int pazymio_apribojimas();
void ignoruoti_eilute(); // yra skaicius_input() viduje;
int random_pazymys();
void printas(const studentas &A, int pasirinkimas);
double vidurkis(const studentas &A);
double mediana(const studentas &A);
double galutinis(const studentas &A, bool ar_mediana);

int main(){
    srand(time(nullptr));
    vector<studentas> grupe;
    studentas A;

    int meniu_veiksmas = -1;
    while (meniu_veiksmas != 0) {
        cout << "\n=== Studentu DB ===\n"
        << "1. Pazymiu ivedimas\n"
        << "2. Rodyti rezultatus\n"
        << "3. Nuskaityti duomenis is failo\n"
        << "0. Iseiti\n"
        << "Pasirinkimas: ";
        meniu_veiksmas = skaicius_input();
        ignoruoti_eilute();

        if (meniu_veiksmas == 1){
            cout<<"Kiek studentu yra sarase: ";
            int n = skaicius_input();
            while (n < 0) {
                cout << "Studentu sk. negali buti neigiamas: ";
                n = skaicius_input();
            }

            ignoruoti_eilute();
            for (int j=0;j<n;j++){
                cout<<"Įveskite per tarpa studento varda ir pavarde: ";
                cin>>A.vardas>>A.pavarde;
                ignoruoti_eilute();

                cout << "1 - pazymius vesti ranka, 2 - generuoti atsitiktinai: ";
                int rezimas = skaicius_input();
                while (rezimas != 1 && rezimas != 2) {
                    cout << "Klaida. Iveskite 1 arba 2: ";
                    rezimas = skaicius_input();
                }
                ignoruoti_eilute();

                cout<<"Įveskite semestro paz. kieki: ";

                if (rezimas == 2){
                    int k = skaicius_input();
                    while (k < 0){
                        cout << "Pazymiu kiekis negali buti neigiamas!\n";
                        cout<<"Įveskite semestro paz. kieki: ";
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

                cout<<"Įveskite semestro Egzamino paz.: "; A.exam = pazymio_apribojimas();
                ignoruoti_eilute();

                }
                grupe.push_back(A);
                A.pavarde.clear();
                A.vardas.clear();
                A.paz.clear();
            }
        }
        else if (meniu_veiksmas == 2) {
            if (grupe.empty()) {
                cout << "\nNera studentu.\n";
                continue;
            }

            cout << "\nKaip skaiciuoti galutini bala?\n"
            <<"1 - pagal vidurki\n"
            <<"2 - pagal mediana\n"
            <<"3 - abu\n";
            int pasirinkimas = 0;
            while (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3) {
                cout << "Pasirinkimas: ";
                pasirinkimas = skaicius_input(); //
                if (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3){
                    cout << "Tokio pasirinkimo nera\n";
                }
            }

            cout << std::left << std::setw(15) <<"Pavarde"<< std::left << std::setw(15) <<"Vardas";
            if (pasirinkimas == 1) cout << "Galutinis (Vid.)\n";
            else if (pasirinkimas == 2) cout << "Galutinis (Med.)\n";
            else cout << std::left << std::setw(18) << "Galutinis (Vid.)" << "Galutinis (Med.)\n";

            int linijos_ilgis = 47;
            if (pasirinkimas == 3) linijos_ilgis = 65;
            cout << string(linijos_ilgis, '-') << "\n";

            for (studentas &B:grupe) printas(B, pasirinkimas);
        }
        else if (meniu_veiksmas == 3){
            string pav = "kursiokai.txt";
            std::ifstream fd(pav);
            if (!fd){
                cout << "\nFailas nerastas.\n";
                continue;
            }

            string eilute;
            getline(fd, eilute);

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
            cout << "\nDuomenys nuskaityti is " << pav << ". Studentu sk: " <<grupe.size() << "\n";
        }
        else if (meniu_veiksmas != 0){
            cout << "\nTokio pasirinkimo nera!\n";
        }
    }
    return 0;
}

int skaicius_input(){
    int sk;
    while (!(cin >> sk)) {
        cout << "Netinkama ivestis. Iveskite skaiciu: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return sk;
}

int pazymio_apribojimas(){
    while (true) {
        int x = skaicius_input();
        if (x >= 0 && x <= 10) return x;
        cout << "Pazymys turi buti nuo 0 iki 10: ";
    }
}

void ignoruoti_eilute(){
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int random_pazymys(){
    return rand() % 11;
}

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
    if (n % 2 == 1) return laikinas[n / 2]; // grazina vidurine reiksme, nes sveikoji dalyba
    return (laikinas[n / 2 - 1] + laikinas[n / 2]) / 2.0;
}

double galutinis(const studentas &A, bool ar_mediana){
    if (ar_mediana == true){
    return 0.4 * mediana(A) + 0.6 * A.exam;
    }
    return 0.4 * vidurkis(A) + 0.6 * A.exam;
}

void printas(const studentas &A, int pasirinkimas){
    cout << std::left << std::setw(15) << A.pavarde
    << std::left << std::setw(15) << A.vardas
    << std::fixed << std::setprecision(2);

    if (pasirinkimas == 1){
        cout << galutinis(A, false) << "\n";
    } else if (pasirinkimas == 2){
        cout << galutinis(A, true) << "\n";
    } else{
        cout << std::left << std::setw(18) << galutinis(A, false) << galutinis(A, true) << "\n";
    }
}