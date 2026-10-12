# objektinis-programavimas
VU objektinio programavimo projektas

## v0.2 greičio (spartos) rezultatai

Testavimas atliktas su jau sugeneruotais failais studentai1000.txt - studentai10000000.txt.
Kiekvienas procesas kartotas po 3 kartus. Failų generavimas į skaičiavimą neįtrauktas. Lentelėje pateiktas kiekvieno proceso vidurkis.

Eiga:
Skaitymas: failas nuskaitomas į vektorių;
Skirstymas: kopijuojama į vektorius “vargsiukai” ir “kietiakai”;
Rašymas: abi grupės surikiuojamos(pagal pavardę) ir surašomos į vargsiukai.txt ir kietiakai.txt.

| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s | bendras laikas s |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.000716403 | 0.000144167 | 0.00144107 | 0.00230164 |
| studentai10000.txt | 10000 | 0.00884856 | 0.000463722 | 0.003222183 | 0.0125341 |
| studentai100000.txt | 100000 | 0.0585941 | 0.00375571 | 0.0264452 | 0.088795 |
| studentai1000000.txt | 1000000 | 0.591244 | 0.0372668 | 0.262962 | 0.891473 |
| studentai10000000.txt | 10000000 | 6.20625 | 0.499676 | 2.67394 | 9.37987 |

<sub>laikas matuotas sekundėmis</sub>

**Išvada**. Kuo didesnis failas, tuo ilgiau trunka visi trys etapai. Nuo 1 000 iki 10 000 000 studentų laikas išauga maždaug tiek pat kartų, kiek ir duomenų kiekis. Ilgiausiai trunka skaitymas, trumpiausiai skirstymas. Rašymas yra tarp jų, nes be įrašymo į diską dar yra rikiuojami studentai ir suformuojama lentelė. Dideliame faile daugiausia laiko užima duomenų skaitymas ir rašymas į failą, ne galutinio balo skaičiavimas.
