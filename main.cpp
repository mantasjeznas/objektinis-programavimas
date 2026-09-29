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
void ignoruoti_eilute();
int random_pazymys();
void printas(std::ostream &out, const studentas &A, int pasirinkimas, int pavardes_ilgis, int vardo_ilgis);
double vidurkis(const studentas &A);
double mediana(const studentas &A);
double galutinis(const studentas &A, bool ar_mediana);
bool pagal_pavarde(const studentas &a, const studentas &b);
bool pagal_varda(const studentas &a, const studentas &b);
void failo_generavimas(int stud_sk, const string &failo_pav);

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
        << "4. Failu generavimas\n"
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

            cout << "\nKur isvesti rezultatus?\n"
            << "1 - i ekrana\n"
            << "2 - i faila\n";
            int kur = 0;
            while (kur != 1 && kur != 2) {
                cout << "Pasirinkimas: ";
                kur = skaicius_input();
                if (kur != 1 && kur != 2){
                    cout << "Tokio pasirinkimo nera\n";
                }
            }
            ignoruoti_eilute();

            string pav;
            if (kur == 2) {
                cout << "Iveskite failo pav.: ";
                cin >> pav;
                ignoruoti_eilute();
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

            cout << "\nPagal ka rikiuoti?\n" << "1 - varda\n" << "2 - pavarde\n";
            int rikiavimas = 0;
            while (rikiavimas != 1 && rikiavimas != 2){
                cout << "Pasirinkimas: ";
                rikiavimas = skaicius_input();
                if (rikiavimas != 1 && rikiavimas != 2){
                    cout << "\nTokio pasirinkimo nera\n";
                }
            }

            if (rikiavimas == 1) std::sort(grupe.begin(), grupe.end(), pagal_varda);
            else std::sort(grupe.begin(), grupe.end(), pagal_pavarde);

            int pavardes_ilgis = 12;
            int vardo_ilgis = 12;
            for (const studentas &S : grupe){
                if ((int)S.pavarde.size() + 2 > pavardes_ilgis) pavardes_ilgis = (int)S.pavarde.size() + 2;
                if ((int)S.vardas.size() + 2 > vardo_ilgis) vardo_ilgis = (int)S.vardas.size() + 2;
            }

            std::ofstream fd;
            std::ostream *out = &cout;
            if (kur == 2) {
                fd.open(pav);
                if (!fd) {
                    cout << "\nNepavyko sukurti failo.\n";
                    continue;
                }
                out = &fd;
            }

            *out << std::left << std::setw(pavardes_ilgis) << "Pavarde" << std::left << std::setw(vardo_ilgis) << "Vardas";
            if (pasirinkimas == 1) *out << "Galutinis (Vid.)\n";
            else if (pasirinkimas == 2) *out << "Galutinis (Med.)\n";
            else *out << std::left << std::setw(18) << "Galutinis (Vid.)" << "Galutinis (Med.)\n";

            int linijos_ilgis = pavardes_ilgis + vardo_ilgis + 16;
            if (pasirinkimas == 3) linijos_ilgis = pavardes_ilgis + vardo_ilgis + 34;
            *out << string(linijos_ilgis, '-') << "\n";

            for (studentas &B:grupe) printas(*out, B, pasirinkimas, pavardes_ilgis, vardo_ilgis);

            if (kur == 2) {
                fd.close();
                cout << "\nRezultatai irasyti i " << pav << "\n";
            }
        }
        else if (meniu_veiksmas == 3){
            string pav;
            cout << "Iveskite failo pav.: ";
            cin >> pav;
            std::ifstream fd(pav);
            if (!fd){
                cout << "\nFailas nerastas.\n";
                continue;
            }

            grupe.clear();

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
        else if (meniu_veiksmas == 4){
            cout << "\nKuri faila generuoti?\n"
            << "1 - 1,000 studentu | studentai1000.txt\n"
            << "2 - 10,000 studentu | studentai10000.txt\n"
            << "3 - 100,000 studentu | studentai100000.txt\n"
            << "4 - 1,000,000 studentu | studentai1000000.txt\n"
            << "5 - 10,000,000 studentu | studentai10000000.txt\n"
            << "6 - visus penkis\n";
            int kiekis = 0;
            while (kiekis < 1 || kiekis > 6) {
                cout << "Pasirinkimas: ";
                kiekis = skaicius_input();
                if (kiekis < 1 || kiekis > 6) cout << "Tokio pasirinkimo nera\n";
            }
            ignoruoti_eilute();

            const int kiekiai[5] = {1000, 10000, 100000, 1000000, 10000000};
            const char *vardai[5] = {
                "studentai1000.txt",
                "studentai10000.txt",
                "studentai100000.txt",
                "studentai1000000.txt",
                "studentai10000000.txt"
            };
            if (kiekis == 6) {
                for (int i = 0; i < 5; i++) failo_generavimas(kiekiai[i], vardai[i]);
            } else {
                failo_generavimas(kiekiai[kiekis - 1], vardai[kiekis - 1]);
            }
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

void printas(std::ostream &out, const studentas &A, int pasirinkimas, int pavardes_ilgis, int vardo_ilgis){
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

void failo_generavimas(int stud_sk, const string &failo_pav){
    std::ofstream fd(failo_pav);
    if (!fd) {
        cout << "Nepavyko sukurti " << failo_pav << "\n";
        return;
    }

    fd << "Pavarde Vardas ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    for (int i = 1; i <= stud_sk; i++) {
        fd << "Pavarde" << i << " Vardas" << i;
        for (int j = 0; j < 5; j++) fd << ' ' << random_pazymys();
        fd << ' ' << random_pazymys() << '\n';
    }
    fd.close();
    cout << "\nsukurtas " << failo_pav << " su " << stud_sk << " irasu\n";
}
