#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

enum class Aktywnosc
{
    aktywne,
    nieaktywne
};

class Klient
{
    private:
     char imieKlienta[100]={};
     char nazwiskoKlienta[100]={};
    public:
        void setImie(const char* imie)
        {
            strncpy(imieKlienta,imie,sizeof(imieKlienta));
        }
        void setNazwisko(const char* nazwisko)
        {
            strncpy(nazwiskoKlienta,nazwisko,sizeof(nazwiskoKlienta));
        }
        void setIMiNZ(char* imie,char* nazwisko)
        {
            setImie(imie);
            setNazwisko(nazwisko);
        }
        char* getImie(char*imie)
        {
            return imie;
        }
        char* getNazwisko(char*nazwisko)
        {
            return nazwisko;
        }
        
};
static const int Rozmiar=26;

class kontoBankowe
{  
    protected:
        int numer_konta[Rozmiar]={};
        double stan_konta=0;
        Aktywnosc aktywnosc=Aktywnosc::aktywne;
        Klient* klient;
    private:
        static int licznikAktywnychKont;
        void sprStan(double kasa)
        {
            if(kasa<0)
                throw invalid_argument("Stan konta nie moze byc mniejszy od 0!");
        }   
       
    public:

        kontoBankowe(int* numer,double stan,Aktywnosc akt,Klient* klient_)
        {
            setNumerKonta(numer);
            setStanKonta(stan);
            setAktywnosc(akt);
            setKlient(klient_);
        }
        ~kontoBankowe()
        {
            if(aktywnosc==Aktywnosc::aktywne)
                {
                    licznikAktywnychKont--;
                }
        }
        void setNumerKonta(int* numer)
        {   
            if(numer==nullptr)
                throw invalid_argument("Wskaznik jest pusty! ");
        
            for (size_t i = 0; i < Rozmiar; i++)
            {
                numer[i]=rand()%10;
            }
            for(size_t i=0; i<Rozmiar;i++)
            {
               numer_konta[i]=numer[i];
            }
        }
        
        void setStanKonta(double pieniozki)
        {   
            sprStan(pieniozki);
            stan_konta=pieniozki;
        }

        void setAktywnosc(Aktywnosc akt)
        {
            if(aktywnosc!=akt)
            {
                if(akt==Aktywnosc::aktywne)
                    licznikAktywnychKont++;
                else if(aktywnosc==Aktywnosc::aktywne)
                    licznikAktywnychKont--;
                    
                aktywnosc=akt;
            }
            
        }
        
        void setKlient(Klient* klient_)
        {  
            klient=klient_;
        }

        int* getNumerKonta()
        {
            return numer_konta;
        }

        double getStanKonta()   
        {
            return stan_konta;
        }

        Aktywnosc getaktywnosc()
        {
            return aktywnosc;
        }

        Klient* getKlient()
        {
            return klient;
        }
        double virtual Oprocentowanie()
        {  
            return stan_konta;
        }

};

int kontoBankowe::licznikAktywnychKont=0;

class konto_oszczednosciowe : public kontoBankowe
{
    protected:
    int stopa_oprocentowania=0;
    private:
   
    void sprStopy(int stopa)
    {
        if(stopa<0)
        {
            throw invalid_argument("Błąd stopa oprocentowania nie moe być mniejsza od 0! ");
        }
    }
    public:  

    konto_oszczednosciowe(kontoBankowe konto,int opr=0):kontoBankowe(konto){setUstawOprocentowanie(opr);}
    
    double Oprocentowanie() override
    {
        return stan_konta*pow((1+stopa_oprocentowania),1);
    }

    void setUstawOprocentowanie(int stopa)
    {
        sprStopy(stopa);
        stopa_oprocentowania=stopa;
    }

    int getUstawOprocentowanie()
    {
        return stopa_oprocentowania;
    }
};

int main()
{   setlocale(LC_ALL,"");
    srand(time(NULL));


    int tab[Rozmiar]={};
    Klient k1,k2,k3;
    k1.setIMiNZ("Janusz","Brzeczyszczykiewicz");
    k2.setIMiNZ("Bogdan","Stasic");
    k3.setIMiNZ("Robert","Kubica");
    kontoBankowe konto1(tab,2098.21,Aktywnosc::aktywne,&k1);
    kontoBankowe konto2(tab,12.21,Aktywnosc::aktywne,&k2);
    kontoBankowe konto3(tab,762.80,Aktywnosc::aktywne,&k3);
    
    return 0;
}
