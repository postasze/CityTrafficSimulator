# Realistic city traffic simulator 2D, with the ability to construct your own city, written in Qt C++

Symulator ruchu miejskiego

Instrukcja instalacji i uruchamiania aplikacji

1.1 Aplikacja zosta³a stworzona z u¿yciem bibliotek Qt, wiêc trzeba pobraæ biblioteki Qt z internetu
np. poprzez instalacjê œrodowisk¹ Qt st¹d https://www.qt.io/download

1.2 Nastêpnie trzeba rozpakowaæ plik zip zawieraj¹cy kod Ÿród³owy aplikacji

1.3 Potem trzeba przejœæ w konsoli bash lub cmd do folderu CityTrafficSimulator, w którym jest zawarty plik CityTrafficSimulator.pro

1.4 Nastêpnie trzeba wywo³aæ polecenie qmake, które generuje automatycznie plik Makefile
(w windowsie jeœli nie zosta³a ustawiona zmienna œrodowiskowa QMAKE konieczne jest wpisanie ca³ej œcie¿ki do programu qmake,
typu C:\Qt\5.10.0\mingw53_32\bin\qmake.exe)

1.5 Potem trzeba wywo³aæ polecenie make, które generuje automatycznie dzia³aj¹c¹ aplikacjê
(w windowsie jeœli nie zosta³a ustawiona zmienna œrodowiskowa MAKE konieczne jest wpisanie ca³ej œcie¿ki do programu make,
typu C:\Qt\Tools\mingw530_32\bin\mingw32-make.exe)

1.6 Nastêpnie mo¿na ju¿ uruchomiæ aplikacjê z pliku CityTrafficSimulator.exe
(w windowsie mo¿e byæ konieczne ustawienie œcie¿ki do bibliotek Qt w zmiennych œrodowiskowych
lub przekopiowanie bibliotek Qt do folderu w którym znajduje siê plik exe,
biblioteki Qt znajduj¹ siê w œcie¿ce typu C:\Qt\Tools\QtCreator\bin)

Kompilacja aplikacji w systemie Linux Ubuntu 16.04 powinna przebiegaæ o wiele sprawniej i proœciek ni¿ w systemie Windows. Alternatywnie mo¿na te¿ uruchomiæ aplikacjê wewn¹trz œrodowiska Qt

2. Opis aplikacji

2.1 Interfejs graficzny

Plik screen.png obrazuje graficzny interfejs i sposób u¿ycia aplikacji

Klikniêcie prawym przyciskiem myszy na element miasta w lewym panelu zawieraj¹cym elementy
powoduje obrót danego elementu o 90 stopni
Klikniêcie i przytrzymanie lewego przycisku myszy na elemencie miasta w lewym panelu zawieraj¹cym elementy
umo¿liwia przeci¹ganie elementu z panelu po lewej i upuszczanie tego elementu na planszê
Klikniêcie prawym przyciskiem na elementy planszy
powoduje skasowanie elementu bêd¹cego najbardziej na wierzchu pod kursorem myszy
Klikniêcie przycisku Czyszczenie edytora na górze interfejsu
powoduje ca³kowite skasowanie wszystkich elementów znajduj¹cych siê obecnie na planszy
Klikniêcie przycisku Stwórz domyœlne miasto na górze interfejsu
powoduje ca³kowite skasowanie wszystkich elementów znajduj¹cych siê obecnie na planszy
i stworzenie nowego, poprawnego miasta ze wszystkimi potrzebnymi elementami
Klikniêcie przycisku Start na po prawej stronie interfejsu
powoduje uruchomienie symulacji (aby symulacja dzia³a³a poprawnie miasto musi byæ poprawnie zbudowane)
Klikniêcie przycisku Stop na po prawej stronie interfejsu
powoduje zatrzymanie symulacji
Prêdkoœæ symulacji mo¿na zmieniaæ w okienku po prawej stronie interfejsu

Pasy dla pieszych mog¹ byæ umieszczane tylko na drogach prostych
Œwiat³a drogowe mog¹ byæ umieszczane tylko na skrzy¿owaniach
Kamery mog¹ byæ umieszczane wszêdzie, nawet w polach, w których s¹ œwiat³a drogowe
Nie da siê umieszczaæ elementów w polach w których ju¿ znajduje siê element tej samej warstwy Z
Punkty dla pieszych mo¿na umieszczaæ tylko na chodniku
Punkty dla samochodów mo¿na umieszczaæ tylko na drodze prostej
(samochód zawsze powinien startowaæ z prawej dolnej czêœci drogi prostej)

2.2 Logika aplikacji

Jest 6 warstw elementów na planszy (elementy o wiêkszej wspó³rzêdnej Z s¹ widziane nad elementami o ni¿szych wspó³rzêdnych Z)
Z = 0 - wszystkie podstawowe elementy oprócz œwiate³ i kamer
Z = 1 - pasy dla pieszych
Z = 2 - samochody i piesi
Z = 3 - œwiat³a drogowe
Z = 4 - kamery
Z = 5 - punkty pocz¹tkowe i koñcowe dla samochodów i pieszych

Jest 8 ró¿nych klas obiektów na planszy (s¹ one umieszczane w streetArray)
Mo¿na je wybraæ z panelu obiektów po lewej stronie interfejsu, obracaæ i upuszczaæ na planszê
Obiekty te s¹ u¿ywane przez samochody i pieszych w trakcie symulacji

Pavement - chodnik 1x1
StraightStreet - prosta droga 2x2 (mo¿na stawiaæ na niej pasy dla pieszych)
TurnStreet - zakrêt 2x2
DivisionStreet - rozga³êzienie ulicy na dwie nowe ulice 2x2
CrossingStreet - fragment drogi reprezentuj¹cy skrzy¿owanie 2x2
(nie mo¿na na nim stawiaæ pasów dla pieszych, mo¿na stawiaæ œwiat³a drogowe)
PedestrianCrossing - fragment drogi zawieraj¹cy pasy dla pieszych 1x2
TrafficLight - œwiat³o drogowe 1x1
Camera - kamera 1x1























