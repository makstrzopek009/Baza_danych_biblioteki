System Zarządzania Biblioteką

Prosty, konsolowy system do zarządzania bazą danych książek napisany w języku C++. Projekt wykorzystuje **dynamiczne struktury danych** (listę jednokierunkową) oraz zapewnia trwałość danych poprzez zapis do plików tekstowych.

Funkcje systemu
* **Zarządzanie zasobami:** Dodawanie i usuwanie książek z bazy.
* **Dynamiczna lista:** Implementacja oparta na wskaźnikach (linked list).
* **Obsługa wypożyczeń:** Zmiana statusu dostępności pozycji na podstawie ID.
* **Sortowanie:** Możliwość sortowania bazy według tytułu, autora, roku wydania lub ID.
* **Persystencja danych:** Zapis i odczyt bazy z plików `.txt` (format CSV/średnikowy).
* **Interfejs UI:** Kolorowa konsola Windows (WinAPI) dla lepszej czytelności.

Technologie
* **Język:** C++ (standard C++11 lub nowszy)
* **Biblioteki:** `iostream`, `fstream`, `string`, `windows.h` (UI)
* **Struktura danych:** Lista jednokierunkowa (Singly Linked List)

Struktura plików
* `main.cpp` - Logika menu i główna pętla programu.
* `modul.cpp` - Implementacja funkcji logicznych i operacji na liście.
* `modul.h` - Definicja struktury `Ksiazka` i nagłówki funkcji.

Instrukcja obsługi
1. Skompiluj program (np. używając g++ lub Visual Studio).
2. Po uruchomieniu wybierz opcję z menu głównego wpisując odpowiednią cyfrę.
3. Przy wczytywaniu/zapisie podawaj nazwę pliku z rozszerzeniem, np. `przyklad.txt`.
