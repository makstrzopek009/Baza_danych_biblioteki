#include <iostream>
#include "modul.h"
#include <windows.h>

int main() {
    setlocale(LC_ALL, "Polish");
    system("title SYSTEM ZARZADZANIA BIBLIOTEKA v1.0");

    Ksiazka* glowa = nullptr;
    int wybor = 0;

    while (wybor != 9) {
        system("cls");
        RysujNaglowek("GLOWNE MENU SYSTEMU");
        UstawKolor(7);
        std::cout << " [1] Dodaj nowa ksiazke          [5] Wypozycz ksiazke\n";
        std::cout << " [2] Sortuj baze danych          [8] Zwroc ksiazke\n";
        std::cout << " [3] Wyswietl zasoby (TABELA)    [4] Usun ksiazke\n";
        std::cout << "------------------------------------------------------\n";
        std::cout << " [6] Zapisz do pliku             [7] Wczytaj z pliku\n";
        std::cout << "------------------------------------------------------\n";
        UstawKolor(12); std::cout << " [9] ZAMKNIJ PROGRAM\n"; UstawKolor(7);

        std::cout << "\n Wybor > ";
        if (!(std::cin >> wybor)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (wybor) {
        case 1: Dodawanie_ksiazki(glowa); break;
        case 2: Sortowanie(glowa); break;
        case 3: Wypisz(glowa); system("pause"); break;
        case 4: Usun(glowa); break;
        case 5: {
            std::string n; std::cout << " Podaj nr ID: "; std::cin >> n;
            Wypozycz_ksiazke(glowa, n); system("pause"); break;
        }
        case 6: {
            std::string np; std::cout << " Nazwa pliku: "; std::cin >> np;
            Zapisz_do_pliku(glowa, np); system("pause"); break;
        }
        case 7: {
            std::string n; std::cout << " Nazwa pliku: "; std::cin >> n;
            Wczytaj_z_pliku(glowa, n); system("pause"); break;
        }
        case 8: {
            std::string n; std::cout << " Podaj nr ID: "; std::cin >> n;
            Zwroc_ksiazke(glowa, n); system("pause"); break;
        }
        }
    }
    Usun_pamiec(glowa);
    return 0;
}