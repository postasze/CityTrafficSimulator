# Realistic city traffic simulator 2D, with the ability to construct your own city, written in Qt C++

Symulator ruchu miejskiego

Instrukcja instalacji i uruchamiania aplikacji

1.1 Aplikacja zosta�a stworzona z u�yciem bibliotek Qt, wi�c trzeba pobra� biblioteki Qt z internetu
np. poprzez instalacj� �rodowisk� Qt st�d https://www.qt.io/download

1.2 Nast�pnie trzeba rozpakowa� plik zip zawieraj�cy kod �r�d�owy aplikacji

1.3 Potem trzeba przej�� w konsoli bash lub cmd do folderu CityTrafficSimulator, w kt�rym jest zawarty plik CityTrafficSimulator.pro

1.4 Nast�pnie trzeba wywo�a� polecenie qmake, kt�re generuje automatycznie plik Makefile
(w windowsie je�li nie zosta�a ustawiona zmienna �rodowiskowa QMAKE konieczne jest wpisanie ca�ej �cie�ki do programu qmake,
typu C:\Qt\5.10.0\mingw53_32\bin\qmake.exe)

1.5 Potem trzeba wywo�a� polecenie make, kt�re generuje automatycznie dzia�aj�c� aplikacj�
(w windowsie je�li nie zosta�a ustawiona zmienna �rodowiskowa MAKE konieczne jest wpisanie ca�ej �cie�ki do programu make,
typu C:\Qt\Tools\mingw530_32\bin\mingw32-make.exe)

1.6 Nast�pnie mo�na ju� uruchomi� aplikacj� z pliku CityTrafficSimulator.exe
(w windowsie mo�e by� konieczne ustawienie �cie�ki do bibliotek Qt w zmiennych �rodowiskowych
lub przekopiowanie bibliotek Qt do folderu w kt�rym znajduje si� plik exe,
biblioteki Qt znajduj� si� w �cie�ce typu C:\Qt\Tools\QtCreator\bin)

Kompilacja aplikacji w systemie Linux Ubuntu 16.04 powinna przebiega� o wiele sprawniej i pro�ciek ni� w systemie Windows. Alternatywnie mo�na te� uruchomi� aplikacj� wewn�trz �rodowiska Qt

2. Opis aplikacji

2.1 Interfejs graficzny

Plik screen.png obrazuje graficzny interfejs i spos�b u�ycia aplikacji

Klikni�cie prawym przyciskiem myszy na element miasta w lewym panelu zawieraj�cym elementy
powoduje obr�t danego elementu o 90 stopni
Klikni�cie i przytrzymanie lewego przycisku myszy na elemencie miasta w lewym panelu zawieraj�cym elementy
umo�liwia przeci�ganie elementu z panelu po lewej i upuszczanie tego elementu na plansz�
Klikni�cie prawym przyciskiem na elementy planszy
powoduje skasowanie elementu b�d�cego najbardziej na wierzchu pod kursorem myszy
Klikni�cie przycisku Czyszczenie edytora na g�rze interfejsu
powoduje ca�kowite skasowanie wszystkich element�w znajduj�cych si� obecnie na planszy
Klikni�cie przycisku Stw�rz domy�lne miasto na g�rze interfejsu
powoduje ca�kowite skasowanie wszystkich element�w znajduj�cych si� obecnie na planszy
i stworzenie nowego, poprawnego miasta ze wszystkimi potrzebnymi elementami
Klikni�cie przycisku Start na po prawej stronie interfejsu
powoduje uruchomienie symulacji (aby symulacja dzia�a�a poprawnie miasto musi by� poprawnie zbudowane)
Klikni�cie przycisku Stop na po prawej stronie interfejsu
powoduje zatrzymanie symulacji
Pr�dko�� symulacji mo�na zmienia� w okienku po prawej stronie interfejsu

Pasy dla pieszych mog� by� umieszczane tylko na drogach prostych
�wiat�a drogowe mog� by� umieszczane tylko na skrzy�owaniach
Kamery mog� by� umieszczane wsz�dzie, nawet w polach, w kt�rych s� �wiat�a drogowe
Nie da si� umieszcza� element�w w polach w kt�rych ju� znajduje si� element tej samej warstwy Z
Punkty dla pieszych mo�na umieszcza� tylko na chodniku
Punkty dla samochod�w mo�na umieszcza� tylko na drodze prostej
(samoch�d zawsze powinien startowa� z prawej dolnej cz�ci drogi prostej)

2.2 Logika aplikacji

Jest 6 warstw element�w na planszy (elementy o wi�kszej wsp�rz�dnej Z s� widziane nad elementami o ni�szych wsp�rz�dnych Z)
Z = 0 - wszystkie podstawowe elementy opr�cz �wiate� i kamer
Z = 1 - pasy dla pieszych
Z = 2 - samochody i piesi
Z = 3 - �wiat�a drogowe
Z = 4 - kamery
Z = 5 - punkty pocz�tkowe i ko�cowe dla samochod�w i pieszych

Jest 8 r�nych klas obiekt�w na planszy (s� one umieszczane w streetArray)
Mo�na je wybra� z panelu obiekt�w po lewej stronie interfejsu, obraca� i upuszcza� na plansz�
Obiekty te s� u�ywane przez samochody i pieszych w trakcie symulacji

Pavement - chodnik 1x1
StraightStreet - prosta droga 2x2 (mo�na stawia� na niej pasy dla pieszych)
TurnStreet - zakr�t 2x2
DivisionStreet - rozga��zienie ulicy na dwie nowe ulice 2x2
CrossingStreet - fragment drogi reprezentuj�cy skrzy�owanie 2x2
(nie mo�na na nim stawia� pas�w dla pieszych, mo�na stawia� �wiat�a drogowe)
PedestrianCrossing - fragment drogi zawieraj�cy pasy dla pieszych 1x2
TrafficLight - �wiat�o drogowe 1x1
Camera - kamera 1x1























