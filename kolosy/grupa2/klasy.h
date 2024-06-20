#pragma once
#include <iostream>
#include <cstring>
#include <cassert>
#include <iomanip>
using namespace std;

enum class czyOdblokowany
{
    
    wylaczony,
    wlaczony,
    zablokowany
};

class Operator
{
  char nazwa[50];
  public:

  Operator(const char* tab){setOperator(tab);}
  ~Operator(){}
  void setOperator(const char* tab)
    {   assert(tab!=nullptr);
        strncpy(nazwa, tab,sizeof(nazwa));
        nazwa[sizeof(nazwa)-1]='\0';
    }
    char* getOperator()
    {
        return nazwa;
    }
    
};

class SystemOperacyjny
{
    char nazwa[50];
    double kosztObliczeniowy=0;
    public:
    SystemOperacyjny(const char* tab){setNazwa(tab);}
    ~SystemOperacyjny(){}
    void setNazwa(const char* tab)
    {
        assert(tab!=nullptr);
        strncpy(nazwa, tab,sizeof(nazwa));
        nazwa[sizeof(nazwa)-1]='\0';
    }
    char* getNazwa()
    {
        return nazwa;
    }
    void setKosztObliczeniowy(double koszt)
    {
        assert(koszt>=0&&koszt<=1);
        kosztObliczeniowy=koszt;
    }
    double getKosztObliczeniowy()
    {
        return kosztObliczeniowy;
    }
};


class Telefon
{   static int licznikZablokowannych;
    char numer[12];
    int stanBaterii;
    czyOdblokowany stan;
    char pin[4];
    Operator* operatorTelefonu;

    void sprawdzenie(czyOdblokowany odb)
    {
         if(odb==czyOdblokowany::zablokowany)
                licznikZablokowannych++;
            stan=odb;
         
    }
    public:
    Telefon();
    ~Telefon(){if(stan==czyOdblokowany::zablokowany)licznikZablokowannych--;}
    Telefon(const char* numer_,const char*pin_,int stan, czyOdblokowany odb,Operator* op)
    {
        assert(odb!=czyOdblokowany::zablokowany);
        strncpy(pin,pin_,sizeof(pin));
        setNumer(numer_);
        setstanBaterii(stan);
        setStan(odb);
        setOperator(op);
    }
    void setNumer(const char* numer_)
{
    assert(numer_!=nullptr);
    if (strlen(numer_) != 11 || numer_[3] != '-' || numer_[7] != '-') {
        throw invalid_argument("Numer powinien być w formacie xxx-xxx-xxx");
    }

    strncpy(numer, numer_, sizeof(numer));
    numer[sizeof(numer)-1] = '\0';
}
    void setstanBaterii(int stan)
    {
        assert(stan>=0 && stan<=100);
        stanBaterii=stan;
    }
    void setStan(czyOdblokowany odb)
    {  if(stan!=czyOdblokowany::zablokowany)
            sprawdzenie(odb);
       
    }
    void setStan(const char* pin_,czyOdblokowany odb)
    {   
        
        
        if(stan==czyOdblokowany::zablokowany)
        {
        if(strncmp(pin,pin_,4)==0)
        {   
            stan=odb;
            licznikZablokowannych--;
        }
        }
        else
        sprawdzenie(odb);
    }
    static int getLicznikZablokowannych()
    {
        return licznikZablokowannych;
    }
    void setOperator(Operator* op)
    {
        operatorTelefonu=op;
    }
    char* getNumer()
    {
        return numer;
    }
    int getStanBaterii()
    {
        return stanBaterii;
    }
    czyOdblokowany getStan()
    {
        return stan;
    }
    Operator* getOperator()
    {
        return operatorTelefonu;
    }
    virtual double czasDzialania()
    {
        return 20*stanBaterii;
    }
    Telefon& operator +=(int x)
    {   
        this->stanBaterii+=x;

        if(stanBaterii<=0)
        {
            stanBaterii=0;
            stan=czyOdblokowany::wylaczony; 
        }
        else if(stanBaterii>=100)
            stanBaterii=100;

        
        return *this;
    }

};

class Smartfon:public Telefon
{
    SystemOperacyjny* system;
    public:
    Smartfon(){}
    Smartfon(SystemOperacyjny*sys,Telefon& t):Telefon(t)
    {
        setSystem(sys);
    }
    ~Smartfon(){}
    Smartfon(const Smartfon& s):Telefon(s)
    {
        setSystem(s.system);
    }
    void setSystem(SystemOperacyjny* sys)
    {
        system=sys;
    }

    SystemOperacyjny* getSystem()
    {
        return system;
    }
    double czasDzialania() override
    {
        return (20-(10*system->getKosztObliczeniowy()))*getStanBaterii();
    }
};

Smartfon TelefontoSmartfon(SystemOperacyjny* s_,Telefon& t)
{
    Smartfon s(s_,t);
    return s;
}