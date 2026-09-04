#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using std::string;
using std::vector;

struct studentas{
    string vardas, pavarde;
    vector<int> paz;
    int exam;
};

void printas( studentas &A);

int main(){
    int k;
    std::vector<studentas> grupe;
    studentas A;
    std::cout<<"Kiek studentu yra sarase: ";
    int n;
    std::cin>>n;
    for (int j=0;j<n;j++){
        std::cout<<"Įveskite per tarpa studento varda ir pavarde: ";
        std::cin>>A.vardas>>A.pavarde;
        std::cout<<"Įveskite semestro paz. kieki: ";std::cin>>k;
        for (int i=0;i<k;i++){
            //cin>>A.paz[i];
            std::cout<<"Įveskite "<<i+1<<" paz: ";
            int a;
            std::cin>>a;
            A.paz.push_back(a);
        }
        std::cout<<"Įveskite semestro Egzamino paz.: ";std::cin>>A.exam;
        grupe.push_back(A);
        A.pavarde.clear();
        A.vardas.clear();
        A.paz.clear();
    }

    std::cout<<"Studentu duom.: \n";
    for (studentas &B:grupe) printas(B);
}

void printas( studentas &A){
    std::cout<<"|"<<std::left<<std::setw(10)<<A.vardas<<"|"<<std::left<<std::setw(10)<<A.pavarde<<"|";
    for (int p: A.paz) std::cout<<std::right<<std::setw(3)<<p<<"|";
    std::cout<<std::right<<std::setw(5)<<A.exam<<"|\n";
}