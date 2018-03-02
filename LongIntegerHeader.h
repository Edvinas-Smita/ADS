//Autoriai: Šmita Edvinas ir Šaulys Teodoras - VU MIF PS 1k. 2gr. 2pogr. 2017-2018m.m.
typedef struct muchlong
{
	char *num;
	unsigned long long len;
	unsigned char isNegativeBool;
} verylong;

void freeStruct(verylong *a);/*
Atlaisvina šiuo formatu laikomo skaičiaus naudojamą atmintį.
Ši funkcija turėtų būti kviečiama kai šio formato kintamasis nebebus naudojamas arba kai tame kintamajame yra norima laikyti kita reikšmė.
Prieš naudojant šią funkciją reikėtų įsitikinti, jog jai paduodamas kintamasis yra tinkamai inicijuotas (t.y. kintamasis yra gautas panaudojus šiame faile pateiktomis funkcijomis).
*/
int readToStruct(FILE *input, verylong *a);/*
Nuskaito skaičių iš duoto failo (pateikus stdin į input parametrą galima nuskaityti ir iš terminalo) ir nuskaitytus duomenis talpina į verylong tipo kintamąjį.
Skaičiaus nuskaitymas procesas:
>	Visi 'white space' simboliai, esantys prieš bent vieną skaitmenį (net jei jau buvo parašytas - arba +) bus ignoruojami.
>	- ir + simboliai turi būti griežtai prieš skaičių. Šių simbolių gali atsirasti daugiau nei 1 (pvz: įvedus "--1" minusai susiprastins). + simbolis reikšmės visiškai neįtakoja.
>	Atpažystami simboliai yra -, +, [0-9] ir 'white space'.
>	Skaičiaus pabaiga laikomas pirmas 'white space' simbolis po skaitmenų sekos.

Galimos gryžimo reikšmės (return code):
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
1 : Aptiktas neatpažintas simbolis
*/


int verylongA_EQUALS_verylongB_Bool(verylong a, verylong b);/* (a == b)
Grąžina reikšmę 1, jei abiejų verylong tipo kintamųjų (a ir b) laikomos reikšmės yra lygios (atsižvelgiant į ženklą).
Grąžina reikšmę 0 visais kitais atvejais.
*/
int verylongA_IS_GREATER_THAN_verylongB_Bool(verylong a, verylong b);/* (a > b)
Grąžina reikšmę 1, jei pirmojo verylong tipo kintamojo (a) laikomos reikšmė yra didesnė, nei antrojo (b) (atsižvelgiant į ženklą).
Grąžina reikšmę 0 visais kitais atvejais.
*/
int verylongA_IS_LESS_THAN_verylongB_Bool(verylong a, verylong b);/* (a < b)
Grąžina reikšmę 1, jei pirmojo verylong tipo kintamojo (a) laikomos reikšmė yra mažesnė, nei antrojo (b) (atsižvelgiant į ženklą).
Grąžina reikšmę 0 visais kitais atvejais.
*/

int verylongA_EQUALS_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);/* (a == b)
Grąžina reikšmę 1, jei reikšmė, esanti pirmame (verylong tipo) kintamajame (a), yra lygi reikšmei, esančiai antrame (long long tipo) kintamajame (b). (Atsižvelgiama į ženklą, jei į trečiajį parametrą yra paduodama nenulinė reikšmė).
Grąžina reikšmę 0 visais kitais atvejais.
*/
int verylongA_IS_GREATER_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);/* (a > b)
Grąžina reikšmę 1, jei reikšmė, esanti pirmame (verylong tipo) kintamajame (a), yra didesnė nei reikšmė, esanti antrame (long long tipo) kintamajame (b). (Atsižvelgiama į ženklą, jei į trečiajį parametrą yra paduodama nenulinė reikšmė).
Grąžina reikšmę 0 visais kitais atvejais.
*/
int verylongA_IS_LESS_THAN_longlongB_Bool(verylong a, long long b, int treatAsSignedBool);/* (a < b)
Grąžina reikšmę 1, jei reikšmė, esanti pirmame (verylong tipo) kintamajame (a), yra mažesnė nei reikšmė, esanti antrame (long long tipo) kintamajame (b). (Atsižvelgiama į ženklą, jei į trečiajį parametrą yra paduodama nenulinė reikšmė).
Grąžina reikšmę 0 visais kitais atvejais.
*/

int verylongA_CAN_BE_STORED_IN_ULongLong(verylong a);/*
Grąžina reikšmę 1, jei verylong tipo kintamajame (a) esanti reikšmė telpa į unsigned long long tipo ribas.
Grąžina reikšmę 0 visais kitais atvejais.
*/
int verylongA_IS_A_POWER_OF_10_Bool(verylong a);/*
Grąžina reikšmę 1, jei verylong tipo kintamajame (a) esanti reikšmė yra 10 laipsnis (1, 10, 100 ir t.t.).
Grąžina reikšmę 0 visais kitais atvejais.
*/



void invertVerylongSign(verylong *a);/* (a = -a)
Apkeičia verylong tipo kintamojo (a) reikšmės ženklą (neigiamą skaičių padaro teigiamu ir atvirkščiai).
*/
int longSum(verylong a, verylong b, verylong *sum);/* (sum = a + b)
Apskaičiuoja dviejų verylong tipo kintamųjų (a ir b) reikšmių sumą ir atsakymą talpina į trečiajį verylong tipo kintamajį (sum).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
1 : Gauta reikšmė netilptų (net) į verylong formatą
*/
int longDiff(verylong a, verylong b, verylong *diff);/* (diff = a + b)
Apskaičiuoja dviejų verylong tipo kintamųjų (a ir b) reikšmių skirtumą ir atsakymą talpina į trečiajį verylong tipo kintamajį (diff).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
1 : Gauta reikšmė netilptų (net) į verylong formatą
*/
int longMul(verylong a, verylong b, verylong *mul);/* (mul = a * b)
Apskaičiuoja dviejų verylong tipo kintamųjų (a ir b) reikšmių sandaugą ir atsakymą talpina į trečiajį verylong tipo kintamajį (mul).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
1 : Gauta reikšmė netilptų (net) į verylong formatą
*/
int longDiv(verylong a, verylong b, verylong *quot, verylong *rem);/* (mul = a / b; quot = a % b)
Apskaičiuoja dviejų verylong tipo kintamųjų (a ir b) reikšmių dalmenį bei liekaną. Dalmenį talpina į trečiajį verylong tipo kintamajį (quot), o liekaną į ketvirtąjį (rem).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
1 : Dalyba iš nulio
2 : Įvyko klaida bandant naudoti kitas funkcijas
*/
int longExp(verylong a, verylong b, verylong *exp);/* (exp = a ^ b (čia ^ - kėlimo laipniu operacija))
Pirmojo verylong tipo kintamojo (a) reikšmę pakelia antrojo verylong tipo kintamojo (b) reikšmės laipsniu ir atsakymą talpina į trečiajį verylong tipo kintamajį (exp).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
0 : Viskas įvykdyta sėkmingai
1 : Pateiktas laipsnis yra neigiamas
2 : Gauta reikšmė netilptų (net) į verylong formatą
3 : Įvyko klaida bandant naudoti kitas funkcijas
*/

int print_bcdh(FILE *output, verylong a);/*
Išveda verylong tipo kintamojo (a) reikšmę į nurodytą failą (pateikus stdout į output parametrą galima išvesti ir į terminalą).

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
0 : Viskas įvykdyta sėkmingai
1 : Įvyko klaida įrašinėjant
*/
int castVerylongToULongLong(verylong a, unsigned long long *regular);/* (regular = (unsigned long long) a)
Jei įmanoma, verylong tipo kintamojo (a) reikšmę patalpiną į unsigned long long tipo kintamąjį (regular)

Galimos gryžimo reikšmės (return code):
-2 : Gauti blogi parametrai
0 : Viskas įvykdyta sėkmingai
1 : A reikšmės negalima sutalpinti į unsigned long long formatą
*/
int castULongLongToVerylong(unsigned long long regular, verylong *a);/* (a = (verylong) regular)
Unsigned long long tipo kintamąjo (regular) reikšmę patalpiną į verylong tipo kintamojį (a)

Galimos gryžimo reikšmės (return code):
-1 : Įvyko klaida su dinaminiu atminties paskirimu
0 : Viskas įvykdyta sėkmingai
*/
