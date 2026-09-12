#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using std::string;
using std::vector;
using std::cout;
using std::cin;

struct studentas{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

void printas(const studentas &A);
double vidurkis(const studentas &A);
double galutinis(const studentas &A);

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

    cout << std::left << std::setw(15) <<"Pavarde"<< std::left << std::setw(15) <<"Vardas"
    <<"Galutinis (Vid.)\n"<< "-----------------------------------------------\n";

    for (studentas &B:grupe) printas(B);

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

double galutinis(const studentas &A) {
    return 0.4 * vidurkis(A) + 0.6 * A.exam;
}

void printas(const studentas &A){
    cout << std::left << std::setw(15) << A.pavarde
    << std::left << std::setw(15) << A.vardas
    << std::fixed << std::setprecision(2) << galutinis(A) << "\n";
}