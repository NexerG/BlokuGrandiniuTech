# BlokuGrandiniuTech
 bloku grandiniu technologiju uzduotys

## Analizė
Kodas priima bet kokio ilgio "stringą"  
Visą laiką gražina 64 simbolių šešioliktainį kodą  
Tas pats "stringas" duos tą patį rezultatą  
Apskaičiuoja Šešioliktainį labai greitai (su visom operacijom), tai yra, per <0.1s  
Pradinio "stringo" neįmanoma atgaminti nežinant unikalaus "stringo" kodo, kuris gaunamas iš "stringo" (kitaip sakant neįmanoma atgaminti)  
Bandyta 2 kartus su 100'000 skritingų 1000 simbolių ilgio "stringų". Nė vienos kolizijos  
Žodžio unikalus kodas padaro, kad menkas skirtumas tarp dviejų "stringų" duoda visiškai kitą rezultatą.  
  
Konstitucijos punktą padaro taip:   
![asd](https://user-images.githubusercontent.com/68482683/202278874-2be832b7-ff43-4371-94b5-578f9cea8de0.png)
  
  
6as punktas parodė, jog "hash'ų" skirtingumas kai hašai mažai skiriasi yra: Min: 6.455% Avg: 6.4906% Max: 6.551%  
6as punktas parodė, jog "hash'ų" skirtingumas kai hašai daug skiriasi yra: Min: 6.473% Avg: 6.4992% Max: 6.548 %  
Be to, kai lyginamas dvejetainis, tai: Min: 49.985% Avg: 49.9992% Max: 51.0012%

## Išvados
Striprybės:  
Skaičiuojant šešioliktainį naudojama ne keista dvejetainė matematika, bet unikalus žodžio kodas.  

Silpnybės:  
Matematiškai labai sunku padaryti, kad kolizijų nebūtų (su 64 šešioliktainio išvesties kodo limitu).  

## Pseudo kodas:
{  
pasirinkimas ar rašyti ranka ar skaičiuoti iš failų  
jeigu ranka  
--{  
----rašymas ranka  
--}  
jeigu iš failų  
--{  
----pasirinkti koks nuskaitymo tipas  
--{  
-----jeigu pirmas, tai tikrina du sugeneruotus 1000 simbolių ilgio stringus  
-----jeigu antras, tai tikrina du sugeneruotus 1000 simbolių ilgio stringus (skiriasi vienu simboliu)  
-----jeigu trečias, tai tikrina "a" su "b" stringus  
-----jeigu ketvirtas, tai tikrina X skritingų (sugeneruotų) 1000 simbolių ilgio stringus  
--}  
}  
   
 Hashinimo algoritmas  
{  
---skaičiuojamas stringo unikalus kodas.  
---stringas sutrumpinamas arba prailginamas iki 32 simbolių  
---stringas paverčiamas dvejetainiu kodu  
---dvejetainis kodas rotuojamas naudojant unikalų žodžio kodą  
---dvejetainis kodas paverčiamas šešioliktainiu kodu  
---šešioliktainis kodas rotuojamas naudojant unikalų hash'o kodą  
}  
