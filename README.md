# objektinis-programavimas
VU objektinio programavimo projektas

## v0.3 greičio (spartos) rezultatai

Testavimas atliktas su jau sugeneruotais failais studentai1000.txt - studentai10000000.txt.
Kiekvienas procesas kartotas po 3 kartus. Failų generavimas į skaičiavimą neįtrauktas. Lentelėje pateiktas kiekvieno proceso vidurkis.

Eiga:
Skaitymas: failas nuskaitomas į konteinerį (`vector` arba `list`);
Skirstymas: kopijuojama į konteinerius “vargsiukai” ir “kietiakai”;
Rašymas: surikiuotos grupės surašomos į vargsiukai.txt ir kietiakai.txt;
Rūšiavimas: abi grupės surikiuojamos pagal galutinį balą (mažėjančiai).

Kompiliuota su `clang++ -std=c++17 -O2 -o programa *.cpp`

## \<vector\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | rūšiavimas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.0013154 | 0.0000867 | 0.000795 | 0.0003528 | 0.0025498 |
| studentai10000.txt | 10000 | 0.0081312 | 0.0004164 | 0.0022497 | 0.003034 | 0.0138313 |
| studentai100000.txt | 100000 | 0.0566773 | 0.0036074 | 0.0210392 | 0.0342742 | 0.115598 |
| studentai1000000.txt | 1000000 | 0.582248 | 0.0517744 | 0.260544 | 0.424 | 1.31857 |
| studentai10000000.txt | 10000000 | 6.24886 | 0.664551 | 2.92715 | 5.82745 | 15.668 |

Bendras visų failų laikas 17,1186 s

<img src="images/vector_laikai.png" width="400">
<br><br>

**Išvada**. Kuo didesnis failas, tuo ilgiau trunka visi etapai. Nuo 1 000 iki 10 000 000 studentų bendras laikas išauga maždaug 6000 kartų, o duomenų yra 10 000 kartų daugiau. Nuo 1 000 000 iki 10 000 000 studentų jis išauga apie 12 kartų. Mažuose failuose ilgiausiai trunka skaitymas. Faile su 10 000 000 studentų skaitymas (6,25 s) ir rūšiavimas (5,83 s) užima daugiausiai laiko, rašymas trunka 2,93 s, o trumpiausiai trunka skirstymas (0,66 s).

## \<list\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | rūšiavimas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.0016536 | 0.0001498 | 0.0010184 | 0.0004099 | 0.0032317 |
| studentai10000.txt | 10000 | 0.0088176 | 0.0004691 | 0.0020218 | 0.0022588 | 0.0135673 |
| studentai100000.txt | 100000 | 0.0581188 | 0.005309 | 0.0244732 | 0.0278873 | 0.115788 |
| studentai1000000.txt | 1000000 | 0.602292 | 0.134513 | 0.43024 | 0.715659 | 1.8827 |
| studentai10000000.txt | 10000000 | 6.60467 | 1.52681 | 4.31249 | 10.862 | 23.306 |

Bendras visų failų laikas 25,3213 s

<img src="images/list_laikai.png" width="400">
<br><br>


**Išvada**. Su `std::list` didžiausiame faile bendras laikas yra 23,3 s, o su `vector` 15,7 s, todėl `list` apie 1,5 karto lėtesnis. Skaitymas panašus (6,60 s ir 6,25 s), skirstymas su `list` lėtesnis apie 2,3 karto (1,53 s ir 0,66 s), rašymas apie 1,5 karto (4,31 s ir 2,93 s). Rūšiavimas su `list` trunka 10,9 s ir yra ilgiausias etapas, o su `vector` 5,83 s. Su 10 000 ir 100 000 studentų `list` rūšiavimas buvo šiek tiek greitesnis, o bendri laikai panašūs, tačiau nuo 1 000 000 studentų `vector` greitesnis visuose etapuose. Tikėtina, kad taip yra todėl, kad `list` laiko kiekvieną studentą atskiroje atminties vietoje, o `vector` iš eilės, todėl kompiuteriui juos greičiau pasiekti.


## Bendra išvada
`std::vector` yra tinkamesnis pasirinkimas didelėms studentų grupėms, nes visi etapai su juo trunka trumpiau, kai failai didesni nei 1 000 000 įrašų. Su mažesniais failais skirtumas nedidelis. Greitis didėjant failui auga maždaug proporcingai duomenų kiekiui abiem konteineriams.

<sub>laikai matuoti sekundėmis</sub>

## Testavimo sistemos parametrai

- **CPU:** Apple M1 Pro
- **RAM:** 16 GB
- **Disk:** SSD
