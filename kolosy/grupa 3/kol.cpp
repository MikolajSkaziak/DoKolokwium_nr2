#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

enum class Rodzaj
{
    mieszkalny,
    publiczny,
    komercyjny
};
class Miejscowosc
{
    char nazwaMiejscowosci[30];

public:
    Miejscowosc(const char *nazwa)
    {
        strncpy(nazwaMiejscowosci, nazwa, sizeof(nazwaMiejscowosci));
        nazwaMiejscowosci[sizeof(nazwaMiejscowosci) - 1] = '\0';
    }
    char *getNazwa()
    {
        return nazwaMiejscowosci;
    }
};

class Budynek
{

    static int licznikBudynkow;
    char ulica[30];
    char numer[2];
    char kodpocztowy[6];
    double metraz;
    Rodzaj rodzaj;
    Miejscowosc *miejscowos;

public:
    Budynek(const char *uli, const char *num, const char *kod, double metr, Rodzaj rodz, Miejscowosc *miejsc) : rodzaj(rodz)
    {
        setUlica(uli);
        setNumer(num);
        setKod(kod);
        setMetraz(metr);
        if (rodz != Rodzaj::publiczny)
        {
            licznikBudynkow++;
        }
        setMiejscowosc(miejsc);
    };
    ~Budynek()
    {
        if (rodzaj != Rodzaj::publiczny)
            licznikBudynkow--;
    }

    void setUlica(const char *uli)
    {
        assert(uli != nullptr && strlen(uli) > 0);
        strncpy(ulica, uli, sizeof(ulica));
        ulica[sizeof(ulica) - 1] = '\0';
    };

    void setNumer(const char *num)
    {
        assert(num != nullptr && strlen(num) > 0);
        strncpy(numer, num, sizeof(numer));
        numer[sizeof(numer) - 1] = '\0';
    };

    void setKod(const char *kod)
    {
        assert(kod != nullptr && strlen(kod) == 5);
        strncpy(kodpocztowy, kod, sizeof(kodpocztowy));
        kodpocztowy[sizeof(kodpocztowy) - 1] = '\0';
    };

    void setMetraz(double metr)
    {
        assert(metr > 0);
        metraz = metr;
    };

    void setRodzaj(Rodzaj rodz)
    {
        if (rodz != rodzaj)
        {
            if (rodz != Rodzaj::publiczny)
            {
                licznikBudynkow++;
            }
            else
            {
                licznikBudynkow--;
            }
        }
        rodzaj = rodz;
    };

    void setMiejscowosc(Miejscowosc *miejsc)
    {
        assert(miejsc != nullptr);
        miejscowos = miejsc;
    };

    char *getUlica()
    {
        return ulica;
    };

    char *getNumer()
    {
        return numer;
    };

    char *getKod()
    {
        return kodpocztowy;
    };

    double getMetraz()
    {
        return metraz;
    };

    Rodzaj getRodzaj()
    {
        return rodzaj;
    };

    Miejscowosc *getMiejscowosc()
    {
        return miejscowos;
    };
    static int getLicznik()
    {
        return licznikBudynkow;
    };
    virtual double ObliczPodatek()
    {
        return 10 * metraz;
    }
    operator double()
    {
        return getMetraz() * sqrt(2);
    }
};

class Posiadlosc : public Budynek
{
    double powierzchniaDzialki;

public:
    Posiadlosc(double powierzchnia, Budynek &b) : Budynek(b)
    {
        setPowierzchnia(powierzchnia);
    };

    void setPowierzchnia(double pow)
    {
        assert(pow > 0);
        powierzchniaDzialki = pow;
    };
    double getPowierzchnia()
    {
        return powierzchniaDzialki;
    };
    double ObliczPodatek() override
    {
        return 10 * getMetraz() + 5 * powierzchniaDzialki;
    }
    bool operator==(Posiadlosc &p)
    {
       return memcmp(this->getMiejscowosc(), p.getMiejscowosc(),sizeof(p)) == 0 && this->getMetraz() == p.getMetraz() && this->getPowierzchnia() == p.getPowierzchnia();
    }
    bool operator!=(Posiadlosc &p)
    {
        return !(*this == p);
    }
};

int Budynek::licznikBudynkow = 0;

int main()
{
    Miejscowosc m1("Warszawa");
    Budynek b1("ul. Polna", "12", "12345", 100, Rodzaj::mieszkalny, &m1);
    Budynek b2("ul. Polna", "12", "12345", 100, Rodzaj::publiczny, &m1);
    Budynek b3("ul. Polna", "12", "12345", 100, Rodzaj::komercyjny, &m1);
    Posiadlosc p1(1000, b1);
    Posiadlosc p2(1000, b2);
    cout << Budynek::getLicznik() << endl;
    b1.setRodzaj(Rodzaj::publiczny);
    cout << Budynek::getLicznik() << endl;

    cout << static_cast<double>(b1) << endl;
    if(p1==p2)
    {
        cout<<"Rowne"<<endl;
    }
    else
    {
        cout<<"Rozne"<<endl;
    }

    return 0;
}