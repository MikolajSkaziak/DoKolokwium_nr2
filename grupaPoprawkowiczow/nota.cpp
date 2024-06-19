#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cmath> // For std::abs

using namespace std;

// Klasa Wlasciciel
class Wlasciciel {
private:
    char nazwisko[50];

public:
    Wlasciciel(const char* nazwisko) {
        strncpy(this->nazwisko, nazwisko, sizeof(this->nazwisko) - 1);
        this->nazwisko[sizeof(this->nazwisko) - 1] = '\0'; // Ensure null-termination
    }

    const char* getNazwisko() const {
        return nazwisko;
    }
};

// Enum class dla stanu dopuszczenia do jazdy
enum class StanDopuszczenia { Dopuszczony, Niedopuszczony };

// Klasa Samochod
class Samochod {
private:
    char numerRejestracyjny[11]; // 3 litery, '-', 5 cyfr i '\0'
    int stanLicznika;
    StanDopuszczenia stanDopuszczenia;
    Wlasciciel* wlasciciel;
    static int ostatniNumerRejestracyjny;

protected:
    // Walidacja i generacja numeru rejestracyjnego
    void generujNumerRejestracyjny(const char* czescLiczbowa, bool incrementNumer = true) {
        if (strlen(czescLiczbowa) != 3) {
            throw invalid_argument("Czesc numeru rejestracyjnego musi zawierać dokładnie 3 litery.");
        }

        for (int i = 0; i < 3; i++) {
            if (czescLiczbowa[i] < 'A' || czescLiczbowa[i] > 'Z') {
                throw invalid_argument("Czesc numeru rejestracyjnego musi zawierać tylko duże litery.");
            }
        }

        char czescNumeru[6];
        int numer;
        if (incrementNumer) {
            ostatniNumerRejestracyjny++;
            numer = ostatniNumerRejestracyjny;
        } else {
            strncpy(czescNumeru, numerRejestracyjny + 4, 5);
            czescNumeru[5] = '\0';
            numer = 0;
            for (int i = 0; i < 5; i++) {
                if (czescNumeru[i] < '0' || czescNumeru[i] > '9') {
                    throw invalid_argument("Czesc numeru rejestracyjnego musi zawierać tylko cyfry.");
                }
                numer = numer * 10 + (czescNumeru[i] - '0');
            }
        }

        // Tworzenie numeru jako 5-cyfrowy string
        for (int i = 4; i >= 0; i--) {
            czescNumeru[i] = '0' + (numer % 10);
            numer /= 10;
        }
        czescNumeru[5] = '\0';

        strcpy(numerRejestracyjny, czescLiczbowa);
        strcat(numerRejestracyjny, "-");
        strcat(numerRejestracyjny, czescNumeru);
    }

public:
    // Konstruktor argumentowy ustawiający wszystkie pola na zadane wartości
    Samochod(const char* czescLiczbowa, int stanLicznika, StanDopuszczenia stanDopuszczenia, Wlasciciel* wlasciciel) {
        setStanLicznika(stanLicznika);
        setStanDopuszczenia(stanDopuszczenia);
        setWlasciciel(wlasciciel);
        generujNumerRejestracyjny(czescLiczbowa);
    }

    // Setery i getery
    void setNumerRejestracyjny(const char* czescLiczbowa) {
        char czescNumeru[6];
        strncpy(czescNumeru, numerRejestracyjny + 4, 5); // Kopiuje część numerową z obecnego numeru rejestracyjnego
        czescNumeru[5] = '\0'; // Ensure null-termination
        generujNumerRejestracyjny(czescLiczbowa, false); // Generate with the new letter part, retaining the number
        strcat(numerRejestracyjny, czescNumeru); // Append the retained number part
    }

    const char* getNumerRejestracyjny() const {
        return numerRejestracyjny;
    }

    void setStanLicznika(int nowyStanLicznika) {
        if (nowyStanLicznika < 0) {
            throw invalid_argument("Stan licznika nie może być ujemny.");
        }
        stanLicznika = nowyStanLicznika;
    }

    int getStanLicznika() const {
        return stanLicznika;
    }

    void setStanDopuszczenia(StanDopuszczenia nowyStanDopuszczenia) {
        stanDopuszczenia = nowyStanDopuszczenia;
    }

    StanDopuszczenia getStanDopuszczenia() const {
        return stanDopuszczenia;
    }

    void setWlasciciel(Wlasciciel* nowyWlasciciel) {
        if (nowyWlasciciel == nullptr || strlen(nowyWlasciciel->getNazwisko()) == 0) {
            throw invalid_argument("Właściciel nie może być pusty.");
        }
        wlasciciel = new Wlasciciel(nowyWlasciciel->getNazwisko());
    }

    Wlasciciel* getWlasciciel() const {
        return wlasciciel;
    }

    virtual double obliczZasieg() const {
        return 800.0; // Stały zasięg dla zwykłego samochodu
    }

    static int getOstatniNumerRejestracyjny() {
        return ostatniNumerRejestracyjny;
    }

    virtual ~Samochod() {
        delete wlasciciel;
    }

    // Operator równości
    bool operator==(const Samochod& other) const {
        return strncmp(this->numerRejestracyjny, other.numerRejestracyjny, 3) == 0 &&
               std::abs(this->stanLicznika - other.stanLicznika) <= 10;
    }
};

// Inicjalizacja statycznego pola
int Samochod::ostatniNumerRejestracyjny = 0;

int main() {
    // Tworzenie obiektu Wlasciciel
    Wlasciciel wlasciciel("Kowalski");

    try {
        // Tworzenie obiektów Samochod
        Samochod car1("XYZ", 50000, StanDopuszczenia::Dopuszczony, &wlasciciel);
        Samochod car2("XYZ", 50010, StanDopuszczenia::Dopuszczony, &wlasciciel);

        // Operator porównania
        if (car1 == car2) {
            cout << "car1 i car2 są identyczne." << endl;
        } else {
            cout << "car1 i car2 nie są identyczne." << endl;
        }
    } catch (const exception& e) {
        cerr << "Błąd: " << e.what() << endl;
    }

    return 0;
}
