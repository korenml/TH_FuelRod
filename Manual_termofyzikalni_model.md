# Manuál pro termofyzikální model palivového proutku pro OpenFOAM

## Úvod

## Licence
Tento software je pod licencí GNU General Public License. Zněni licence

Obecná veřejná licence GNU (v angličtině GNU General Public License, dále jen jako “GNU GPL” nebo “GPL”) je svobodná, “copyleft” (část autorských práv ponechává a části se zříká) licence pro software a jiná díla.

Většina licencí pro software a jiná díla jsou navrženy tak, aby omezovaly svobodu jeho sdílení a úprav. Naproti tomu, Obecná veřejná licence GNU zaručuje svobodu sdílení a úprav všech verzí programu – aby byl software svobodný pro všechny jeho uživatele. My, ze Free Software Foundation, používáme Obecnou veřejnou licenci GNU pro většinu našich programů, ale licence se vztahuje i na díla jiných autorů, kteří se je rozhodli zveřejnit právě tímto způsobem. Můžete ji rovněž použít pro své programy.

Pokud mluvíme o svobodném softwaru, myslíme tím svobodu používání, nikoliv cenu. Naše Obecné veřejné licence jsou navrženy tak, abyste mohli volně šířit kopie svobodného softwaru (a pokud chcete, nechat si za to i zaplatit), abyste obdrželi zdrojový kód, nebo ho měli možnost získat, abyste mohli tento software měnit nebo jeho části použít v nových programech a abyste věděli, že tyto věci smíte dělat.

Abychom mohli chránit vaše práva, musíme zabránit tomu, aby vám kdokoliv tato práva odepíral, nebo vás žádal, abyste se těchto práv vzdali. Proto i vy máte určité povinnosti, které musíte dodržet, pokud šíříte nebo upravujete takový software, a to povinnost respektovat svobodu ostatních.

Například, šíříte-li kopie programu, ať již zdarma nebo za poplatek, příjemci musíte poskytnout stejná práva, jaké jste sami obdrželi. Musíte zaručit, že příjemci rovněž dostanou, anebo mohou získat zdrojový kód. A aby i oni znali svá práva, musíte je upozornit na tyto podmínky.

Vývojáři, kteří používají GNU GPL, chrání vaše práva ve dvou krocích: (1) zabezpečením autorských práv k softwaru, a (2) nabídkou této Licence, která vám dává právoplatné svolení k jeho kopírování, šíření a/nebo jeho úpravě.

Kvůli ochraně každého vývojáře a autora, GPL dává jasně najevo, že pro svobodný software neexistuje žádná záruka. V zájmu obou stran, uživatelů i autorů, GPL požaduje, aby upravené verze programu byly příslušně označeny, a to kvůli tomu, aby za původce případných chyb programu nebyli nesprávně označeni autoři původních verzí.

Některá zařízení uživatelům zakazují instalaci nebo spuštění upravených verzí softwaru, i když výrobce si takovou možnost ponechal. Toto je z principu neslučitelné s cílem ochrany uživatelské svobody – svobody jakkoli software měnit. Takové porušování se systematicky vyskytuje tam, kde je program určen pro jednotlivce, tedy tam, kde je to nejméně přijatelné. Abychom takovým počinem předešli, vytvořili jsme tuto verzi GPL. Jestliže problémy tohoto druhu budou nadále vznikat, jsme připraveni je podle potřeby ošetřit v následujících verzích GPL.

Závěrem, každý program je neustále ohrožen softwarovými patenty. Státy by neměly povolovat patenty pro zamezení vývoje a použití softwaru, který je určen pro všeobecné použití. Ale u těch, které tak činí, bychom rádi zamezili nebezpečí, že by distributoři svobodného programu obdrželi samostatná patentová osvědčení a tím by učinili takový program vázaným. Abychom tomu zamezili, GPL zaručuje, že patenty nemohou činit program nesvobodným.

## Kompilace
Kompilaci lze provést jednoše pomocí příkazu

```
Allwmake
```

ten se postaré o vše potřebné.

Alternativně lze zkompilovat jednotlivé knihnovny. Pro správný proces kompilace je nejprve potřeba odstranit veškeré předchozí verze a s tím souvijící zkompilované knihovny. Vyčištění předchozích verzí se proveden příkazem

```
wclean
```

Pro samotnou kompilaci se použije příkaz:

```
wmake libso
```

Po zdařilé kompilaci by se měla zobrazit cesta ke zkompilované knihovně.


## Materiálové vlastnosti
Hlavní součástí softwaru je soubor termofyzikálních vlastností pro palivo, pokrytí a mezeru na rozhraní palivo-pokrytí.

### UO2
Termofyzikální vlastnosti paliva jsou vypočty z níže uvedených vztahů, kde T_ se vypočte T_=T/1000

Tepelná kapacita

```
c=3.69*(52.1743+87.951*T_-84.2411*T_^2+31.542*T_^3-2.6334*T_^4+0.7139/T_^2)
```

Závislost tepelné kapaciy na teplotě je zobrazena na grafu níže

![Tepelná kapacita UO2](Graph_heat_cap.png)

Tepelná vodivost

```
k=0.001/(7.5408+17.692*T_+3.6142*T_^2)+64*(T_^-2.5)*e^(-16.35/T_)

```

Závislost tepelné vodivosti na teplotě je zobrazena na grafu níže

![Tepelná vodivost UO2](Graph_thermal_cond.png)

Hustota

```
rho=10970
```

### Zirkoniové slitiny
#### E110

Tepelná kapacita

T>=300 a T <=1100

```
c_p=238+0.159*T
```

T>1100 a T <=2000

```
c_p=281+0.0663*T
```

Tepelná vodivost

T>=300 a T<=1100

```
k=23.5-0.0192*T + 1.68e-5*T^2
```

T>1100 a T<=1600

```
k=1.5+0.02*T
```

#### E125
Tepelná kapacita

T>=300 a T<=1100

```
c_p=221+0.172*T-5.87e-5*T^2
```

T>1100 a T<=2000

```
c_p=380
```

Tepelná vodivost

T>=300 a T<=1100

```
k=14.0+0.0115*T
```

### Mezera palivo-pokrytí
Přestup tepla mezi palivem a pokrytím byl modelován pomocí algebraického modelu [GAPHTC].
Tepelná vodivost v mezeře

```

T_mean = 0.5*(T_fuel + T_cladding)
h_gap = (1.149e-2 + (3.9963e-4 - 7.2674e-8*T_mean)*T_mean)/h_gap_cold
```

## Ukázka použití

## Závěr

## Reference

[GAPHTC] N.P.Kolev, I.Spasov (INRNE), "VVER MSLB Benchmark Specification Report: Transient boundary conditions, solvers", NURISP D3.1.3.1 rev 1 Issued on 29/09/2009