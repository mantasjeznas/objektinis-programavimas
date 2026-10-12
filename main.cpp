#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Studentas.h"
#include "Pagalbiniai.h"
#include "Failai.h"
using std::string;
using std::vector;
using std::cout;
using std::cin;

int main(){
    srand(time(nullptr));
    vector<studentas> grupe;
    vector<studentas> kietiakai;
    vector<studentas> vargsiukai;
    bool ar_suskirstyta = false;
    bool skirstymo_mediana = false;

    int meniu_veiksmas = -1;
    while (meniu_veiksmas != 0) {
        cout << "\n=== Studentu DB ===\n"
        << "1. Pazymiu ivedimas\n"
        << "2. Rodyti rezultatus\n"
        << "3. Skirstymas pagal bala\n"
        << "4. Nuskaityti duomenis is failo\n"
        << "5. Failu generavimas\n"
        << "6. Greicio analize\n"
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
                grupe.push_back(ivesti_studenta());
                ar_suskirstyta = false;
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
            int kur = pasirinkimas_tarp(1, 2);
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
            int pasirinkimas = pasirinkimas_tarp(1, 3);
            int rikiavimas = rikiavimo_pasirinkimas();

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

            rezultatu_isvedimas(*out, grupe, pasirinkimas, rikiavimas);

            if (kur == 2) {
                fd.close();
                cout << "\nRezultatai irasyti i " << pav << "\n";
            }
        }
        else if (meniu_veiksmas == 3){
            cout << "\n1 - skirstyti i kategorijas\n"
            << "2 - irasyti i failus (tik jei jau suskirstyta)\n";
            int veiksmas = pasirinkimas_tarp(1, 2);

            if (veiksmas == 1){
                if (grupe.empty()) {
                    cout << "\nNera studentu.\n";
                    continue;
                }

                cout << "\nPagal ka skaiciuoti galutini bala?\n"
                << "1 - vidurkis\n"
                << "2 - mediana\n";
                int pagal = pasirinkimas_tarp(1, 2);

                skirstymo_mediana = (pagal == 2);
                skirstymas(grupe, kietiakai, vargsiukai, skirstymo_mediana);
                ar_suskirstyta = true;
                cout << "\nVargsiukai (galutinis < 5): " << vargsiukai.size() << "\n";
                cout << "Kietiakai (galutinis >= 5): " << kietiakai.size() << "\n";
            } else {
                if (!ar_suskirstyta){
                    cout << "\nPirmiausia suskirstykite.\n";
                    continue;
                }

                int rikiavimas = rikiavimo_pasirinkimas();
                int pasirinkimas = skirstymo_mediana ? 2 : 1;
                irasyti_kategorijas(vargsiukai, kietiakai, pasirinkimas, rikiavimas);
            }
        }
        else if (meniu_veiksmas == 4){
            string pav;
            cout << "Iveskite failo pav.: ";
            cin >> pav;
            if (!nuskaityti_faila(pav, grupe)){
                cout << "\nFailas nerastas.\n";
                continue;
            }
            ar_suskirstyta = false;
            cout << "\nDuomenys nuskaityti is " << pav << ". Studentu sk: " <<grupe.size() << "\n";
        }
        else if (meniu_veiksmas == 5){
            failu_generavimo_meniu();
        } else if (meniu_veiksmas == 6){
            greicio_analizes_meniu();
        }
        else if (meniu_veiksmas != 0){
            cout << "\nTokio pasirinkimo nera!\n";
        }
    }
    return 0;
}
