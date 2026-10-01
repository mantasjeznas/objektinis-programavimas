# objektinis-programavimas
VU objektinio programavimo projektas

## v0.2 greičio (spartos) rezultatai

Testavimas atliktas su jau sugeneruotais failais studentai1000.txt - studentai10000000.txt.
Kiekvienas procesas kartotas po 3 kartus. Failų generavimas į skaičiavimą neįtrauktas. Lentelėje pateiktas kiekvieno proceso vidurkis.

Eiga:
Skaitymas: failas nuskaitomas į vektorių;
Skirstymas: kopijuojama į vektorius “vargsiukai” ir “kietiakai”;
Rašymas: abi grupės surikiuojamos(pagal pavardę) ir surašomos į vargsiukai.txt ir kietiakai.txt.

| failas | studentų | skaitymas, s | skirstymas, s | rašymas, s |
|---|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.00259957 | 0.000396514 | 0.00125843 |
| studentai10000.txt | 10000 | 0.0229616 | 0.00399596 | 0.0114728 |
| studentai100000.txt | 100000 | 0.227453 | 0.0376774 | 0.124706 |
| studentai1000000.txt | 1000000 | 2.30009 | 0.372941 | 1.36898 |
| studentai10000000.txt | 10000000 | 23.7857 | 4.11928 | 15.2353 |

<sub>laikas matuotas sekundėmis</sub>

**Išvada**. Kuo didesnis failas, tuo ilgiau trunka visi trys etapai. Nuo 1 000 iki 10 000 000 studentų laikas išauga maždaug tiek pat kartų, kiek ir duomenų kiekis. Ilgiausiai trunka skaitymas, trumpiausiai skirstymas. Rašymas yra tarp jų, nes be įrašymo į diską dar yra rikiuojami studentai ir suformuojama lentelė. Dideliame faile daugiausia laiko užima duomenų skaitymas ir rašymas į failą, ne galutinio balo skaičiavimas.
