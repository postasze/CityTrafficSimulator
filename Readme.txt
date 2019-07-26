
1. Instrukcja instalacji i uruchamiania aplikacji

1.1 Aplikacja została stworzona z użyciem bibliotek Qt, więc trzeba pobrać biblioteki Qt z internetu
np. poprzez instalację środowiską Qt stąd https://www.qt.io/download

1.2 Następnie trzeba rozpakować plik zip zawierający kod źródłowy aplikacji

1.3 Potem trzeba przejść w konsoli bash lub cmd do folderu CityTrafficSimulator, w którym jest zawarty plik CityTrafficSimulator.pro

1.4 Następnie trzeba wywołać polecenie qmake, które generuje automatycznie plik Makefile
(w windowsie jeśli nie została ustawiona zmienna środowiskowa QMAKE konieczne jest wpisanie całej ścieżki do programu qmake,
typu C:\Qt\5.10.0\mingw53_32\bin\qmake.exe)

1.5 Potem trzeba wywołać polecenie make, które generuje automatycznie działającą aplikację
(w windowsie jeśli nie została ustawiona zmienna środowiskowa MAKE konieczne jest wpisanie całej ścieżki do programu make,
typu C:\Qt\Tools\mingw530_32\bin\mingw32-make.exe)

1.6 Następnie można już uruchomić aplikację z pliku CityTrafficSimulator.exe
(w windowsie może być konieczne ustawienie ścieżki do bibliotek Qt w zmiennych środowiskowych
lub przekopiowanie bibliotek Qt do folderu w którym znajduje się plik exe,
biblioteki Qt znajdują się w ścieżce typu C:\Qt\Tools\QtCreator\bin)

Kompilacja aplikacji w systemie Linux Ubuntu 16.04 powinna przebiegać o wiele sprawniej i prościek niż w systemie Windows. Alternatywnie można też uruchomić aplikację wewnątrz środowiska Qt

2. Opis aplikacji

2.1 Interfejs graficzny

Plik screen.png obrazuje graficzny interfejs i sposób użycia aplikacji

Kliknięcie prawym przyciskiem myszy na element miasta w lewym panelu zawierającym elementy
powoduje obrót danego elementu o 90 stopni
Kliknięcie i przytrzymanie lewego przycisku myszy na elemencie miasta w lewym panelu zawierającym elementy
umożliwia przeciąganie elementu z panelu po lewej i upuszczanie tego elementu na planszę
Kliknięcie prawym przyciskiem na elementy planszy
powoduje skasowanie elementu będącego najbardziej na wierzchu pod kursorem myszy
Kliknięcie przycisku Czyszczenie edytora na górze interfejsu
powoduje całkowite skasowanie wszystkich elementów znajdujących się obecnie na planszy
Kliknięcie przycisku Stwórz domyślne miasto na górze interfejsu
powoduje całkowite skasowanie wszystkich elementów znajdujących się obecnie na planszy
i stworzenie nowego, poprawnego miasta ze wszystkimi potrzebnymi elementami
Kliknięcie przycisku Start na po prawej stronie interfejsu
powoduje uruchomienie symulacji (aby symulacja działała poprawnie miasto musi być poprawnie zbudowane)
Kliknięcie przycisku Stop na po prawej stronie interfejsu
powoduje zatrzymanie symulacji
Prędkość symulacji można zmieniać w okienku po prawej stronie interfejsu

Pasy dla pieszych mogą być umieszczane tylko na drogach prostych
Światła drogowe mogą być umieszczane tylko na skrzyżowaniach
Kamery mogą być umieszczane wszędzie, nawet w polach, w których są światła drogowe
Nie da się umieszczać elementów w polach w których już znajduje się element tej samej warstwy Z
Punkty dla pieszych można umieszczać tylko na chodniku
Punkty dla samochodów można umieszczać tylko na drodze prostej
(samochód zawsze powinien startować z prawej dolnej części drogi prostej)

2.2 Logika aplikacji

Jest 6 warstw elementów na planszy (elementy o większej współrzędnej Z są widziane nad elementami o niższych współrzędnych Z)
Z = 0 - wszystkie podstawowe elementy oprócz świateł i kamer
Z = 1 - pasy dla pieszych
Z = 2 - samochody i piesi
Z = 3 - światła drogowe
Z = 4 - kamery
Z = 5 - punkty początkowe i końcowe dla samochodów i pieszych

Jest 8 różnych klas obiektów na planszy (są one umieszczane w streetArray)
Można je wybrać z panelu obiektów po lewej stronie interfejsu, obracać i upuszczać na planszę
Obiekty te są używane przez samochody i pieszych w trakcie symulacji

Pavement - chodnik 1x1
StraightStreet - prosta droga 2x2 (można stawiać na niej pasy dla pieszych)
TurnStreet - zakręt 2x2
DivisionStreet - rozgałęzienie ulicy na dwie nowe ulice 2x2
CrossingStreet - fragment drogi reprezentujący skrzyżowanie 2x2
(nie można na nim stawiać pasów dla pieszych, można stawiać światła drogowe)
PedestrianCrossing - fragment drogi zawierający pasy dla pieszych 1x2
TrafficLight - światło drogowe 1x1
Camera - kamera 1x1












