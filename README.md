# objektinis-programavimas
VU objektinio programavimo projektas

## v0.2 greičio (spartos) rezultatai

Testavimas atliktas su jau sugeneruotais failais studentai1000.txt - studentai10000000.txt.
Kiekvienas procesas kartotas po 3 kartus. Failų generavimas į skaičiavimą neįtrauktas. Lentelėje pateiktas kiekvieno proceso vidurkis.

Eiga:
Skaitymas: failas nuskaitomas į vektorių;
Skirstymas: kopijuojama į vektorius “vargsiukai” ir “kietiakai”;
Rašymas: abi grupės surikiuojamos(pagal pavardę) ir surašomos į vargsiukai.txt ir kietiakai.txt.

## \<vector\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.000716403 | 0.000144167 | 0.00144107 | 0.00230164 |
| studentai10000.txt | 10000 | 0.00884856 | 0.000463722 | 0.003222183 | 0.0125341 |
| studentai100000.txt | 100000 | 0.0585941 | 0.00375571 | 0.0264452 | 0.088795 |
| studentai1000000.txt | 1000000 | 0.591244 | 0.0372668 | 0.262962 | 0.891473 |
| studentai10000000.txt | 10000000 | 6.20625 | 0.499676 | 2.67394 | 9.37987 |

**Išvada**. Kuo didesnis failas, tuo ilgiau trunka visi trys etapai. Nuo 1 000 iki 10 000 000 studentų laikas išauga maždaug tiek pat kartų, kiek ir duomenų kiekis. Ilgiausiai trunka skaitymas, trumpiausiai skirstymas. Rašymas yra tarp jų, nes be įrašymo į diską dar yra rikiuojami studentai ir suformuojama lentelė. Dideliame faile daugiausia laiko užima duomenų skaitymas ir rašymas į failą, ne galutinio balo skaičiavimas.

## \<list\>
| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.00169442 | 0.000155403 | 0.00142608 | 0.0032759 |
| studentai10000.txt | 10000 | 0.00830774 | 0.0005765 | 0.00386558 | 0.0127498 |
| studentai100000.txt | 100000 | 0.0592591 | 0.00497779 | 0.0276213 | 0.0918582 |
| studentai1000000.txt | 1000000 | 0.693618 | 0.0445039 | 0.281836 | 1.01996 |
| studentai10000000.txt | 10000000 | 6.52029 | 0.568762 | 3.1152 | 10.2043 |

**Išvada**. Su `std::list` visi etapai trunka šiek tiek ilgiau nei su `std::vector`. Didžiausiame faile bendras laikas yra 10.2 s, o su `vector` buvo 9.4 s. Skirtumas atsiranda todėl, kad `list` kiekvieną studentą laiko atskiroje atminties vietoje, o `vector` visus laiko iš eilės, todėl kompiuteriui juos greičiau pasiekti. Kaip ir su `vector`, ilgiausiai trunka skaitymas, trumpiausiai skirstymas, o laikas auga maždaug tiek pat kartų, kiek ir duomenų kiekis.

<sub>laikai matuoti sekundėmis</sub>