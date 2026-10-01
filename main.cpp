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
    studentas A;

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
                ar_suskirstyta = false;
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
                pasirinkimas = skaicius_input();
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
            int veiksmas = 0;
            while (veiksmas != 1 && veiksmas != 2){
                cout << "Pasirinkimas: ";
                veiksmas = skaicius_input();
                if (veiksmas != 1 && veiksmas != 2) cout << "Tokio pasirinkimo nera\n";
            }

            if (veiksmas == 1){
                if (grupe.empty()) {
                    cout << "\nNera studentu.\n";
                    continue;
                }

                cout << "\nPagal ka skaiciuoti galutini bala?\n"
                << "1 - vidurkis\n"
                << "2 - mediana\n";
                int pagal = 0;
                while (pagal != 1 && pagal != 2){
                    cout << "Pasirinkimas: ";
                    pagal = skaicius_input();
                    if (pagal != 1 && pagal != 2) cout << "Tokio pasirinkimo nera\n";
                }

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

                cout << "\nPagal ka rikiuoti?\n" << "1 - varda\n" << "2 - pavarde\n";
                int rikiavimas = 0;
                while (rikiavimas != 1 && rikiavimas != 2){
                    cout << "Pasirinkimas: ";
                    rikiavimas = skaicius_input();
                    if (rikiavimas != 1 && rikiavimas != 2) cout << "\nTokio pasirinkimo nera\n";
                }

                std::ofstream varg("vargsiukai.txt");
                std::ofstream kiet("kietiakai.txt");
                if (!varg || !kiet) {
                    cout << "\nNepavyko sukurti/redaguoti failo.\n";
                    continue;
                }
                int pasirinkimas = skirstymo_mediana ? 2 : 1;
                rezultatu_isvedimas(varg, vargsiukai, pasirinkimas, rikiavimas);
                rezultatu_isvedimas(kiet, kietiakai, pasirinkimas, rikiavimas);
                cout << "\nIrasyta i vargsiukai.txt (" << vargsiukai.size() << " studentu)\n";
                cout << "Irasyta i kietiakai.txt (" << kietiakai.size() << " studentu)\n";
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
        } else if (meniu_veiksmas == 6){
            const char *vardai[5] = {
                "studentai1000.txt",
                "studentai10000.txt",
                "studentai100000.txt",
                "studentai1000000.txt",
                "studentai10000000.txt"
            };
            int esami[5];
            int n = 0;
            for (int i = 0; i < 5; i++) {
                std::ifstream fd(vardai[i]);
                if (fd) esami[n++] = i;
            }
            if (n == 0) {
                cout << "\nNera sugeneruotu failu. Sugeneruokite meniu 5 punktu.\n";
                continue;
            }

            cout << "\nKuri faila testuoti?\n";
            for (int i = 0; i < n; i++) {
                cout << i + 1 << " - " << vardai[esami[i]] << "\n";
            }
            if (n > 1) cout << n + 1 << " - visus esamus\n";

            int max_pasirinkimas = (n > 1) ? n + 1 : n;
            int kiekis = 0;
            while (kiekis < 1 || kiekis > max_pasirinkimas) {
                cout << "Pasirinkimas: ";
                kiekis = skaicius_input();
                if (kiekis < 1 || kiekis > max_pasirinkimas) cout << "Tokio pasirinkimo nera\n";
            }
            ignoruoti_eilute();

            if (n > 1 && kiekis == n + 1) {
                for (int i = 0; i < n; i++) greicio_analize(vardai[esami[i]]);
            } else {
                greicio_analize(vardai[esami[kiekis - 1]]);
            }
        }
        else if (meniu_veiksmas != 0){
            cout << "\nTokio pasirinkimo nera!\n";
        }
    }
    return 0;
}
