#include "modul.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>

void UstawKolor(int k) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

void RysujNaglowek(std::string tekst) {
    UstawKolor(11); // Jasnoniebieski
    std::cout << "\n================================================================================\n";
    std::cout << "  " << tekst << "\n";
    std::cout << "================================================================================\n";
    UstawKolor(7);
}

void Dodaj(Ksiazka*& glowa, std::string tytul, std::string imie_autora, std::string nazwisko_autora, std::string wydawnictwo, int data_wydania, bool czy_wypozyczona, std::string numer) {
    Ksiazka* tmp = new Ksiazka;
    tmp->tytul = tytul;
    tmp->imie_autora = imie_autora;
    tmp->nazwisko_autora = nazwisko_autora;
    tmp->wydawnictwo = wydawnictwo;
    tmp->data_wydania = data_wydania;
    tmp->czy_wypozyczona = czy_wypozyczona;
    tmp->numer = numer;
    tmp->nast = nullptr;

    if (glowa == nullptr) {
        glowa = tmp;
    }
    else {
        Ksiazka* w = glowa;
        while (w->nast != nullptr) w = w->nast;
        w->nast = tmp;
    }
}

void Dodawanie_ksiazki(Ksiazka*& glowa) {
    RysujNaglowek("DODAWANIE NOWEJ KSIAZKI");
    std::string tytul, imie, nazwisko, wydawnictwo, numer;
    int data;
    bool status;

    std::cin.ignore(1000, '\n');
    std::cout << " Tytul: "; std::getline(std::cin, tytul);
    std::cout << " Imie autora: "; std::getline(std::cin, imie);
    std::cout << " Nazwisko autora: "; std::getline(std::cin, nazwisko);
    std::cout << " Wydawnictwo: "; std::getline(std::cin, wydawnictwo);
    std::cout << " Rok wydania: "; std::cin >> data;
    std::cout << " Czy wypozyczona (1-Tak / 0-Nie): "; std::cin >> status;
    std::cout << " Numer ID: "; std::cin >> numer;

    Dodaj(glowa, tytul, imie, nazwisko, wydawnictwo, data, status, numer);
    UstawKolor(10); std::cout << "\n [+] Ksiazka zostala dodana do listy.\n"; UstawKolor(7);
    system("pause");
}

void Wczytaj_z_pliku(Ksiazka*& glowa, const std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);
    if (!plik.is_open()) {
        UstawKolor(12); std::cout << " [X] Blad: Nie mozna otworzyc pliku: " << nazwa_pliku << std::endl; UstawKolor(7);
        return;
    }

    std::string linia;
    int licznik = 0;
    while (std::getline(plik, linia)) {
        std::istringstream iss(linia);
        std::string tytul, imie, nazwisko, wydawnictwo, numer;
        int data_wydania;
        bool czy_wypozyczona;

        if (std::getline(iss, numer, ';') && std::getline(iss, tytul, ';') &&
            std::getline(iss, imie, ';') && std::getline(iss, nazwisko, ';') &&
            std::getline(iss, wydawnictwo, ';') && (iss >> data_wydania) &&
            (iss.ignore(1, ';') && (iss >> czy_wypozyczona))) {
            Dodaj(glowa, tytul, imie, nazwisko, wydawnictwo, data_wydania, czy_wypozyczona, numer);
            licznik++;
        }
    }
    UstawKolor(10); std::cout << " [+] Pomyslnie wczytano " << licznik << " rekordow.\n"; UstawKolor(7);
    plik.close();
}

void Wypisz(Ksiazka* glowa) {
    RysujNaglowek("AKTUALNY STAN BAZY DANYCH");
    if (glowa == nullptr) {
        UstawKolor(14); std::cout << " [!] Baza danych jest pusta.\n"; UstawKolor(7);
        return;
    }

    UstawKolor(14);
    std::cout << std::left << std::setw(4) << "LP" << std::setw(12) << "ID" << std::setw(25) << "TYTUL"
        << std::setw(20) << "AUTOR" << std::setw(8) << "ROK" << "STATUS" << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n";
    UstawKolor(7);

    int i = 1;
    Ksiazka* w = glowa;
    while (w != nullptr) {
        std::cout << std::left << std::setw(4) << i << std::setw(12) << w->numer
            << std::setw(25) << (w->tytul.length() > 22 ? w->tytul.substr(0, 20) + ".." : w->tytul)
            << std::setw(20) << w->nazwisko_autora << std::setw(8) << w->data_wydania;

        if (w->czy_wypozyczona) {
            UstawKolor(12); std::cout << "WYPOZYCZONA";
        }
        else {
            UstawKolor(10); std::cout << "DOSTEPNA";
        }
        UstawKolor(7);
        std::cout << std::endl;
        w = w->nast;
        i++;
    }
    std::cout << "--------------------------------------------------------------------------------\n";
}

void Zapisz_do_pliku(Ksiazka* glowa, std::string& nazwa_pliku) {
    std::ofstream plik(nazwa_pliku);
    if (!plik.is_open()) {
        UstawKolor(12); std::cout << " [X] Blad zapisu.\n"; UstawKolor(7);
        return;
    }
    Ksiazka* w = glowa;
    while (w != nullptr) {
        plik << w->numer << ";" << w->tytul << ";" << w->imie_autora << ";" << w->nazwisko_autora << ";"
            << w->wydawnictwo << ";" << w->data_wydania << ";" << w->czy_wypozyczona << std::endl;
        w = w->nast;
    }
    UstawKolor(10); std::cout << " [+] Baza zostala zapisana do: " << nazwa_pliku << std::endl; UstawKolor(7);
    plik.close();
}

void Usun(Ksiazka*& glowa) {
    if (glowa == nullptr) return;
    int pozycja;
    std::cout << " Podaj numer LP do usuniecia: "; std::cin >> pozycja;

    if (pozycja == 1) {
        Ksiazka* tmp = glowa;
        glowa = glowa->nast;
        delete tmp;
    }
    else {
        Ksiazka* w = glowa;
        for (int i = 1; w != nullptr && i < pozycja - 1; i++) w = w->nast;
        if (w == nullptr || w->nast == nullptr) return;
        Ksiazka* tmp = w->nast;
        w->nast = tmp->nast;
        delete tmp;
    }
    UstawKolor(13); std::cout << " [-] Usunieto pozycje nr " << pozycja << std::endl; UstawKolor(7);
    system("pause");
}

void Sortowanie(Ksiazka*& glowa) {
    if (glowa == nullptr) return;
    RysujNaglowek("SORTOWANIE BAZY");
    std::cout << " [1] Tytul  [2] Imie  [3] Nazwisko  [4] Wydawnictwo  [5] Rok  [6] ID\n Wybor: ";
    int wybor; std::cin >> wybor;

    for (Ksiazka* i = glowa; i != nullptr; i = i->nast) {
        for (Ksiazka* j = i->nast; j != nullptr; j = j->nast) {
            bool zamien = false;
            if (wybor == 1 && j->tytul < i->tytul) zamien = true;
            if (wybor == 3 && j->nazwisko_autora < i->nazwisko_autora) zamien = true;
            if (wybor == 5 && j->data_wydania < i->data_wydania) zamien = true;
            if (wybor == 6 && j->numer < i->numer) zamien = true;

            if (zamien) {
                std::swap(i->tytul, j->tytul);
                std::swap(i->imie_autora, j->imie_autora);
                std::swap(i->nazwisko_autora, j->nazwisko_autora);
                std::swap(i->wydawnictwo, j->wydawnictwo);
                std::swap(i->data_wydania, j->data_wydania);
                std::swap(i->czy_wypozyczona, j->czy_wypozyczona);
                std::swap(i->numer, j->numer);
            }
        }
    }
    UstawKolor(10); std::cout << " [+] Sortowanie zakonczone.\n"; UstawKolor(7);
    system("pause");
}

void Wypozycz_ksiazke(Ksiazka* glowa, std::string& numer) {
    Ksiazka* w = glowa;
    while (w != nullptr) {
        if (w->numer == numer) {
            if (w->czy_wypozyczona) std::cout << " [!] Ta ksiazka jest juz wypozyczona.\n";
            else { w->czy_wypozyczona = true; std::cout << " [+] Wypozyczono: " << w->tytul << std::endl; }
            return;
        }
        w = w->nast;
    }
    std::cout << " [X] Nie znaleziono ID.\n";
}

void Zwroc_ksiazke(Ksiazka* glowa, std::string& numer) {
    Ksiazka* w = glowa;
    while (w != nullptr) {
        if (w->numer == numer) {
            if (!w->czy_wypozyczona) std::cout << " [!] Ta ksiazka nie byla wypozyczona.\n";
            else { w->czy_wypozyczona = false; std::cout << " [+] Zwrocono: " << w->tytul << std::endl; }
            return;
        }
        w = w->nast;
    }
}

void Usun_pamiec(Ksiazka*& glowa) {
    while (glowa) {
        Ksiazka* tmp = glowa;
        glowa = glowa->nast;
        delete tmp;
    }
}