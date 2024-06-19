// KolosGr1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cassert>
using namespace std;
enum class Dostepnosc
{
    dostepne,
    niedostepne
};

class Autor
{
    char nazwisko[50];

public:
    Autor(const char *tab)
    {
        assert(tab != nullptr);
        strcpy(nazwisko, tab);
    }
    char *getNazwaAutora() { return nazwisko; }
};

class Ksiazka
{
    char Tytul[100] = {};
    int liczbaStron;
    Dostepnosc dostepnosc;
    Autor *autor;
    static Ksiazka *wzorzec;
    void assertAutor(Autor *aut)
    {
        assert(aut != nullptr);
    }
    void assertTytul(const char *tyt)
    {
        assert(tyt != nullptr);
    }
    static void assertWzorzec(Ksiazka *wz)
    {
        assert(wz != nullptr);
    }

public:
    Ksiazka()
    {
        assert(wzorzec != nullptr);

        strcpy(Tytul, wzorzec->Tytul);
        liczbaStron = wzorzec->liczbaStron;
        dostepnosc = wzorzec->dostepnosc;
        autor = wzorzec->autor;
    }
    ~Ksiazka() {}

    const char* opis() const
    {
        char *opis = new char[256];
        sprintf(opis, "Tytuł: %s, Strony: %d, Dostępność: %s, Autor: %s",
                Tytul,
                liczbaStron,
                (dostepnosc == Dostepnosc::dostepne ? "Dostępne" : "Niedostępne"),
                autor->getNazwaAutora());
        return opis;
    }

    Ksiazka(const char *tyt, int liczba, Dostepnosc dost, Autor *aut)
    {
        setTytul(tyt);
        setLiczbaStron(liczba);
        setDostepnosc(dost);
        setAutor(aut);
    }
    static void setWzorzec(Ksiazka *wz)
    {
        assertWzorzec(wz);
        wzorzec = wz;
    }

    void setTytul(const char *tyt)
    {
        assertTytul(tyt);
        strcpy(Tytul, tyt);
    }

    void setLiczbaStron(int liczba)
    {

        liczbaStron = (liczba < 0 ? 0 : liczba);
    }

    void setDostepnosc(Dostepnosc dost) { dostepnosc = dost; }

    void setAutor(Autor *aut)
    {
        assertAutor(aut);
        autor = aut;
    }

    char *getTytul() { return Tytul; }

    int getLiczbaStron() const { return liczbaStron; }

    Dostepnosc getDostepnosc() const { return dostepnosc; }

    Autor *getAutor() const { return autor; }
    double virtual cenaKsiazki()
    {
        return 1.0 * getLiczbaStron();
    }
   bool operator==(const Ksiazka &other) const
{
    if (this == &other) return true;
    
    if (this->liczbaStron != other.liczbaStron) return false;

    if (this->dostepnosc != other.dostepnosc) return false;

    if (strcmp(this->autor->getNazwaAutora(), other.autor->getNazwaAutora()) != 0) return false;

    return true;
}

};

Ksiazka *Ksiazka::wzorzec = nullptr;

class Ebook : public Ksiazka
{
    int rozmiar;

public:
    Ebook(int roz, Ksiazka &k) : Ksiazka(k)
    {
        setRozmiar(roz);
    }
    void setRozmiar(int roz)
    {
        rozmiar = (roz < 0 ? 0 : roz);
    }
    int getRozmiar() { return rozmiar; }
    double cenaKsiazki() override
    {
        return Ksiazka::cenaKsiazki() * 0.75;
    }
};

int main()
{
    Autor Autor1("Cezariusz");

    Ksiazka Wpustyni("W Pustyni", 2137, Dostepnosc::dostepne, &Autor1);
    Ebook Wpustyni1(250, Wpustyni);
    Ksiazka::setWzorzec(&Wpustyni);
    Ksiazka luz;
    cout << "cena: " << Wpustyni.cenaKsiazki() << endl;
    cout << "cena: " << Wpustyni1.cenaKsiazki() << endl;
     

    cout << Wpustyni.opis();
}