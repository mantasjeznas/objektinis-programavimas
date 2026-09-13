#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::cin;

struct studentas{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

void printas(const studentas &A, int pasirinkimas);
double vidurkis(const studentas &A);
double mediana(const studentas &A);
double galutinis(const studentas &A, bool ar_mediana);

int main(){
    int k;
    vector<studentas> grupe;
    studentas A;

    cout<<"Kiek studentu yra sarase: "; int n; cin>>n;

    for (int j=0;j<n;j++){
        cout<<"Įveskite per tarpa studento varda ir pavarde: ";
        cin>>A.vardas>>A.pavarde;
        cout<<"Įveskite semestro paz. kieki: ";cin>>k;
        for (int i=0;i<k;i++){
            cout<<"Įveskite "<<i+1<<" paz: ";
            int a;
            cin>>a;
            A.paz.push_back(a);
        }
        cout<<"Įveskite semestro Egzamino paz.: ";cin>>A.exam;

        grupe.push_back(A);
        A.pavarde.clear();
        A.vardas.clear();
        A.paz.clear();
    }

    cout << "\nKaip skaiciuoti galutini bala?\n"
    <<"1 - pagal vidurki\n"
    <<"2 - pagal mediana\n"
    <<"3 - abu\n";
    int pasirinkimas = 0;
    while (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3) {
        cout << "Pasirinkimas: \n";
        cin >> pasirinkimas;
        if (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3){
            cout << "neteisinga ivestis\n";
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

    return 0;
}

double vidurkis(const studentas &A) {
    if (A.paz.empty()) return 0;
    double suma = 0;
    for (int p : A.paz){
        suma += p;
    }
    return suma / A.paz.size();
}

double mediana(const studentas &A) {
    if (A.paz.empty()) return 0;
    vector<int> laikinas = A.paz;
    std::sort(laikinas.begin(), laikinas.end());
    int n = laikinas.size();
    if (n % 2 == 1) return laikinas[n / 2]; // grazina vidurine reiksme, nes sveikoji dalyba
    return (laikinas[n / 2 - 1] + laikinas[n / 2]) / 2.0;
}

double galutinis(const studentas &A, bool ar_mediana) {
    if (ar_mediana == true){
    return 0.4 * mediana(A) + 0.6 * A.exam;
    }
    return 0.4 * vidurkis(A) + 0.6 * A.exam;
}

void printas(const studentas &A, int pasirinkimas){
    cout << std::left << std::setw(15) << A.pavarde
    << std::left << std::setw(15) << A.vardas
    << std::fixed << std::setprecision(2);

    if (pasirinkimas == 1) {
        cout << galutinis(A, false) << "\n";
    } else if (pasirinkimas == 2) {
        cout << galutinis(A, true) << "\n";
    } else {
        cout << std::left << std::setw(18) << galutinis(A, false) << galutinis(A, true) << "\n";
    }
}