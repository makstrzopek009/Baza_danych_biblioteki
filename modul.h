#ifndef MODUL_H
#define MODUL_H

#include <string>

struct Ksiazka {
    std::string tytul;
    std::string imie_autora;
    std::string nazwisko_autora;
    std::string wydawnictwo;
    int data_wydania;
    bool czy_wypozyczona;
    std::string numer;
    Ksiazka* nast;
};

// Funkcje interfejsu
void UstawKolor(int k);
void RysujNaglowek(std::string tekst);

// Funkcje bazy danych
void Dodaj(Ksiazka*& glowa, std::string tytul, std::string imie_autora, std::string nazwisko_autora, std::string wydawnictwo, int data_wydania, bool czy_wypozyczona, std::string numer);
void Dodawanie_ksiazki(Ksiazka*& glowa);
void Wczytaj_z_pliku(Ksiazka*& glowa, const std::string& nazwa_pliku);
void Wypisz(Ksiazka* glowa);
void Zapisz_do_pliku(Ksiazka* glowa, std::string& nazwa_pliku);
void Usun(Ksiazka*& glowa);
void Sortowanie(Ksiazka*& glowa);
void Wypozycz_ksiazke(Ksiazka* glowa, std::string& numer_do_wypozyczenia);
void Zwroc_ksiazke(Ksiazka* glowa, std::string& numer_do_wypozyczenia);
void Usun_pamiec(Ksiazka*& glowa);

#endif