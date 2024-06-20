#include "klasy.h"

int Telefon::licznikZablokowannych=0;




int main()
{
    Operator op("Orange");
    Telefon t("123-456-789","1234",100,czyOdblokowany::wlaczony,&op);
    SystemOperacyjny sys("Android");
    Smartfon s(&sys,t);
    cout<<t.getNumer()<<endl;
    Smartfon s2= TelefontoSmartfon(&sys,t);
    sys.setKosztObliczeniowy(0.5);
    /*cout<<sys.getKosztObliczeniowy()<<endl;
    cout<<t.czasDzialania()<<endl;
    cout<<s.czasDzialania()<<endl;*/
    cout<<s2.getSystem()->getNazwa()<<endl;
    
    t+=-20;
    cout<<t.getStanBaterii()<<endl;
    cout<<(int)t.getStan()<<endl;
    return 0;
}
