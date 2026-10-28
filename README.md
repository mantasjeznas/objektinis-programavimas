# objektinis-programavimas
VU objektinio programavimo projektas

## v0.3 greičio (spartos) rezultatai

Testavimas atliktas su jau sugeneruotais failais stud1000.txt - stud10000000.txt.
Kiekvienas procesas kartotas po 3 kartus. Failų generavimas į skaičiavimą neįtrauktas. Lentelėje pateiktas kiekvieno proceso vidurkis.

Eiga:
Skaitymas: failas nuskaitomas į konteinerį (`vector` arba `list`);
Skirstymas: kopijuojama į konteinerius “vargsiukai” ir “kietiakai”;
Rūšiavimas: abi grupės surikiuojamos pagal galutinį balą (mažėjančiai);
Rašymas: surikiuotos grupės surašomos į vargsiukai.txt ir kietiakai.txt.

Kompiliuota su `clang++ -std=c++17 -O2 -o programa *.cpp`

## \<vector\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | rūšiavimas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|---:|
| stud1000.txt | 1000 | 0.0019629 | 0.0001115 | 0.0012659 | 0.0005125 | 0.0038528 |
| stud10000.txt | 10000 | 0.0100717 | 0.0005161 | 0.0023294 | 0.0037051 | 0.0166223 |
| stud100000.txt | 100000 | 0.058124 | 0.0037096 | 0.0204477 | 0.034671 | 0.116952 |
| stud1000000.txt | 1000000 | 0.592253 | 0.0546006 | 0.279484 | 0.440726 | 1.36706 |
| stud10000000.txt | 10000000 | 6.49013 | 0.629851 | 2.99189 | 5.94023 | 16.0521 |

Bendras visų failų laikas 17,5566 s

<img src="images/vector_laikai.png" width="400">
<br>

**Išvada**. Kuo didesnis failas, tuo ilgiau trunka visi etapai. Nuo 1 000 000 iki 10 000 000 studentų kiekvienas etapas išauga maždaug 11–14 kartų. Mažuose failuose ilgiausiai trunka skaitymas. Faile su 10 000 000 studentų skaitymas (6,49 s) ir rūšiavimas (5,94 s) užima daugiausiai laiko, rašymas trunka 2,99 s, o trumpiausiai trunka skirstymas (0,63 s).
<br>

## \<list\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | rūšiavimas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|---:|
| stud1000.txt | 1000 | 0.0019173 | 0.0001745 | 0.0035289 | 0.0002285 | 0.005849 |
| stud10000.txt | 10000 | 0.0106939 | 0.0013119 | 0.0026378 | 0.0032017 | 0.0178453 |
| stud100000.txt | 100000 | 0.0724235 | 0.0182655 | 0.041369 | 0.0445372 | 0.176595 |
| stud1000000.txt | 1000000 | 0.744151 | 0.230315 | 0.540531 | 0.991579 | 2.50658 |
| stud10000000.txt | 10000000 | 8.38451 | 2.81153 | 8.12095 | 16.0895 | 35.4065 |

Bendras visų failų laikas 38,1134 s

<img src="images/list_laikai.png" width="400">
<br>


**Išvada**. Su `std::list` didžiausiame faile bendras laikas yra 35,41 s, o su `vector` 16,05 s, todėl `list` apie 2,2 karto lėtesnis. Skaitymas lėtesnis apie 1,3 karto (8,38 s ir 6,49 s), skirstymas apie 4,5 karto (2,81 s ir 0,63 s), rašymas apie 2,7 karto (8,12 s ir 2,99 s). Rūšiavimas su `list` trunka 16,09 s ir yra ilgiausias etapas, o su `vector` 5,94 s (apie 2,7 karto). Su 1 000 ir 10 000 studentų `list` rūšiavimas buvo šiek tiek greitesnis, tačiau nuo 100 000 studentų `vector` greitesnis visuose etapuose. Tikėtina, kad taip yra todėl, kad `list` laiko kiekvieną studentą atskiroje atminties vietoje, o `vector` iš eilės, todėl kompiuteriui juos greičiau pasiekti.

## Bendra išvada
`std::vector` yra tinkamesnis pasirinkimas didelėms studentų grupėms, nes visi etapai su juo trunka trumpiau, kai failuose yra 100 000 ir daugiau įrašų. Su mažesniais failais skirtumas nedidelis. Greitis didėjant failui auga maždaug proporcingai duomenų kiekiui abiem konteineriams.

<sub>laikai matuoti sekundėmis</sub>

## Testavimo sistemos parametrai

- **CPU:** Apple M1 Pro
- **RAM:** 16 GB
- **Disk:** SSD
