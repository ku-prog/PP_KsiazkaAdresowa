#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Adresat
{
    int idAdresata, idUzytkownika;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik
{
    int id;
    string login = "", haslo = "";
};

string wczytajLinie()
{
    cin.sync();
    string wejscie;
    getline(cin, wejscie);
    return wejscie;
}

int wczytajLiczbe()
{
    string wejscie = "";
    int liczba = 0;

    while(true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if(myStream >> liczba)
            break;

        cout << "To nie jest liczba. Wpisz ponownie";

    }
    return liczba;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while(true)
    {
        getline(cin,wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;

    }
    return znak;

}

vector <Adresat> wczytajPlikAdresatow(int zalogowanyUzytkownik)
{
    vector <Adresat> adresaci;
    Adresat nowyAdresat;
    string liniaOdczytu = "", odczytIdAdresata = "", odczytIdUzytkownika = "";
    ifstream plik("Adresaci.txt", ios::in);

    if (!plik.good())
    {
        cout << "Brak adresatow w bazie danych." << endl;
        system("pause");
        return adresaci;
    }

    while(getline(plik, liniaOdczytu))
    {
        istringstream iss(liniaOdczytu);

        getline(iss, odczytIdAdresata, '|');
        nowyAdresat.idAdresata = stoi(odczytIdAdresata);
        getline(iss, odczytIdUzytkownika, '|');
        nowyAdresat.idUzytkownika = stoi(odczytIdUzytkownika);
        getline(iss, nowyAdresat.imie, '|');
        getline(iss, nowyAdresat.nazwisko, '|');
        getline(iss, nowyAdresat.numerTelefonu, '|');
        getline(iss, nowyAdresat.email, '|');
        getline(iss, nowyAdresat.adres, '|');

        if(nowyAdresat.idUzytkownika == zalogowanyUzytkownik)
        adresaci.push_back(nowyAdresat);
    }
    plik.close();

    return adresaci;
}

vector <Uzytkownik> wczytajPlikUzytkownikow()
{
    vector <Uzytkownik> uzytkownicy;
    Uzytkownik nowyUzytkownik;
    string liniaOdczytu = "", odczytId = "";
    ifstream plikUzytkownicy("Uzytkownicy.txt", ios::in);

    if (!plikUzytkownicy.good())
    {
        cout << "Brak Uzytkownikow w bazie danych" << endl;
        system("pause");
        return uzytkownicy;
    }

    while(getline(plikUzytkownicy, liniaOdczytu))
    {
        istringstream iss(liniaOdczytu);

        getline(iss, odczytId, '|');
        nowyUzytkownik.id = stoi(odczytId);
        getline(iss, nowyUzytkownik.login, '|');
        getline(iss, nowyUzytkownik.haslo, '|');

        uzytkownicy.push_back(nowyUzytkownik);
    }
    plikUzytkownicy.close();

    return uzytkownicy;
}

vector<Uzytkownik> rejestracjaUzytkownika(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    string nowyUzytkownikID, liniaZapisu = "";

    fstream plikUzytkownicy;
    plikUzytkownicy.open("Uzytkownicy.txt", ios::out|ios::app);

    cout << "Wprowadz login: ";
    nowyUzytkownik.login = wczytajLinie();
    cout << "Wprowadz haslo: ";
    nowyUzytkownik.haslo = wczytajLinie();

    nowyUzytkownik.id = uzytkownicy.empty() ? 1 : uzytkownicy.back().id + 1;
    nowyUzytkownikID = to_string(nowyUzytkownik.id);

    liniaZapisu = nowyUzytkownikID + "|" + nowyUzytkownik.login + "|" + nowyUzytkownik.haslo + "|";
    plikUzytkownicy << liniaZapisu + "\n";


    plikUzytkownicy.close();
    uzytkownicy.push_back(nowyUzytkownik);

    return uzytkownicy;
}

void logowanieUzytkownika(vector<Uzytkownik> &uzytkownicy, Uzytkownik &zalogowanyUzytkownik)
{
    cout << "Podaj login: ";
    zalogowanyUzytkownik.login = wczytajLinie();


    for (auto testowyUzytkownik : uzytkownicy)
    {
        if (testowyUzytkownik.login == zalogowanyUzytkownik.login)
        {
            cout << "Podaj haslo: ";
            zalogowanyUzytkownik.haslo = wczytajLinie();

            if(testowyUzytkownik.haslo == zalogowanyUzytkownik.haslo)
            {
                zalogowanyUzytkownik.id = testowyUzytkownik.id;
                return;
            }

            else
            {
                cout << "Login lub haslo niepoprawne." << endl;
                system("pause");
                return;
            }
        }
    }
    cout << "Login lub haslo niepoprawne." << endl;
    system("pause");
    return;
}

void zapiszZmianyWPlikuUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    string liniaZapisu = "";
    fstream plikUzytkownicy;
    plikUzytkownicy.open("Uzytkownicy.txt", ios::out|ios::trunc);
    plikUzytkownicy.close();

    plikUzytkownicy.open("Uzytkownicy.txt", ios::out|ios::app);

    for(auto uzytkownik : uzytkownicy)
    {
        liniaZapisu = to_string(uzytkownik.id) + "|" + uzytkownik.login + "|" + uzytkownik.haslo + "|";
        plikUzytkownicy << liniaZapisu + "\n";
    }
    plikUzytkownicy.close();
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, Uzytkownik &zalogowanyUzytkownik)
{
    for (size_t i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].id == zalogowanyUzytkownik.id)
        {
            cout << "Podaj nowe haslo: ";
            uzytkownicy[i].haslo = wczytajLinie();
            zalogowanyUzytkownik.haslo = uzytkownicy[i].haslo;
        }
    }
    zapiszZmianyWPlikuUzytkownikow(uzytkownicy);
}

void przepiszDanePlikow(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string liniaOdczytu = "";
    fstream plikAdresaciOryginalny, plikAdresaciTymczasowy;

    plikAdresaciOryginalny.open("Adresaci.txt", ios::in);
    plikAdresaciTymczasowy.open("Adresaci_tymczasowy.txt", ios::out|ios::app);

//    while(getlinie(plikAdresaciOryginalny, liniaOdczytu))
//    {
//        getline(pli)
//
//
//    }

    plikAdresaciOryginalny.close();
    plikAdresaciTymczasowy.close();
}

void dodajAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{

    string liniaZapisu = "", numerIdAdresata, ostatniaLinia = "", liniaOdczytu = "", odczytIdAdresata = "", buforOdczytu = "";
    int idOstatniegoAdresata = 0;
    Adresat nowyAdresat;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);


    while(getline(plik, liniaOdczytu))
    {
        istringstream iss(liniaOdczytu);

        getline(iss, odczytIdAdresata, '|');
        idOstatniegoAdresata = stoi(odczytIdAdresata);
        getline(iss, buforOdczytu, '|');
        getline(iss, buforOdczytu, '|');
        getline(iss, buforOdczytu, '|');
        getline(iss, buforOdczytu, '|');
        getline(iss, buforOdczytu, '|');
        getline(iss, buforOdczytu, '|');

    }

    plik.close();

    nowyAdresat.idAdresata= !idOstatniegoAdresata ? 1 : idOstatniegoAdresata + 1;
    numerIdAdresata= to_string(nowyAdresat.idAdresata);



    cout << "Podaj imie: ";
    nowyAdresat.imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    nowyAdresat.nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    nowyAdresat.numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    nowyAdresat.email = wczytajLinie();

    cout << "Podaj adres: ";
    nowyAdresat.adres = wczytajLinie();

    liniaZapisu = numerIdAdresata + "|" + to_string(idZalogowanegoUzytkownika) + "|" + nowyAdresat.imie + "|" + nowyAdresat.nazwisko + "|" + nowyAdresat.numerTelefonu + "|" + nowyAdresat.email + "|" + nowyAdresat.adres + "|";

    plik.open("Adresaci.txt", ios::out|ios::app);
    plik << liniaZapisu + "\n";
    plik.close();

    adresaci.push_back(nowyAdresat);

    cout << "Dodano nowy wpis: " << liniaZapisu << endl;
    system("pause");

    //przepiszDanePlikow(adresaci, idZalogowanegoUzytkownika);
}

void wyszukajPoImieniu(vector <Adresat> adresaci)
{
    if(adresaci.size() < 1)
    {
        cout << "Brak danych w bazie." << endl;
        system("pause");
        return;

    }

    cout << "Wprowadz szukane imie: ";
    string szukaneImie = wczytajLinie();

    for(auto x : adresaci)
    {
        if(x.imie == szukaneImie)
        {
            cout << "ID:             " << x.idAdresata<< endl;
            cout << "Imie:           " << x.imie << endl;
            cout << "Naziwsko:       " << x.nazwisko << endl;
            cout << "Numer telefonu: " << x.numerTelefonu << endl;
            cout << "Email:          " << x.email << endl;
            cout << "Adres:          " << x.adres << endl;
        }
    }
    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> adresaci)
{
    if(adresaci.size() < 1)
    {
        cout << "Brak danych w bazie." << endl;
        system("pause");
        return;

    }

    cout << "Wprowadz szukane nazwisko: ";
    string szukaneNazwisko = wczytajLinie();

    for(auto x : adresaci)
    {
        if(x.nazwisko == szukaneNazwisko)
        {
            cout << "ID:             " << x.idAdresata<< endl;
            cout << "Imie:           " << x.imie << endl;
            cout << "Naziwsko:       " << x.nazwisko << endl;
            cout << "Numer telefonu: " << x.numerTelefonu << endl;
            cout << "Email:          " << x.email << endl;
            cout << "Adres:          " << x.adres << endl;
        }
    }
    system("pause");
}

void wyswietlWszystkich(vector <Adresat> adresaci)
{

    if(adresaci.size() < 1)
    {
        cout << "Brak danych w bazie." << endl;
        system("pause");
        return;

    }

    for(auto x : adresaci)
    {
        cout << "ID:             " << x.idAdresata<< endl;
        cout << "Imie:           " << x.imie << endl;
        cout << "Naziwsko:       " << x.nazwisko << endl;
        cout << "Numer telefonu: " << x.numerTelefonu << endl;
        cout << "Email:          " << x.email << endl;
        cout << "Adres:          " << x.adres << endl;
    }
    system("pause");
}

void zapiszZmianyWPliku(vector <Adresat> &adresaci)
{
    string liniaZapisu = "";
    fstream plik;
    plik.open("Adresaci.txt", ios::out|ios::trunc);
    plik.close();

    plik.open("Adresaci.txt", ios::out|ios::app);

    for(auto x : adresaci)
    {
        liniaZapisu = to_string(x.idAdresata) + "|" + x.imie + "|" + x.nazwisko + "|" + x.numerTelefonu + "|" + x.email + "|" + x.adres + "|" + "\n";
        plik << liniaZapisu;
    }
    plik.close();
}

void usunAdresata(vector <Adresat> &adresaci)
{
    if(adresaci.empty())
    {
        cout << "Brak danych w bazie." << endl;
        system("pause");
        return;

    }

    cout << "Podaj numer ID uzytkownika do usuniecia: ";
    int usunID = wczytajLiczbe(), pozycjaAdresata = 0;


    for(auto x : adresaci) //lepiej iteracyjnie, nie indeksowo
    {
        if(x.idAdresata== usunID)
        {
            cout << "Usuwasz adresata o id: " << x.idAdresata<< endl;
            adresaci.erase(adresaci.begin() + pozycjaAdresata);
        }
        pozycjaAdresata++;
    }
    zapiszZmianyWPliku(adresaci);

    system("pause");
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    int idDoEdycji;
    char wybor = '0';

    if(adresaci.size() < 1)
    {
        cout << "Brak danych w bazie." << endl;
        system("pause");
        return;

    }

    cout << "Podaj ID adresata do edycji: ";
    idDoEdycji = wczytajLiczbe();



    for (size_t i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].idAdresata== idDoEdycji)
        {
            while (wybor != '6')
            {
                system("cls");
                cout << "---------MENU EDYCYJNE-------" << endl;
                cout << "1. Imie." << endl;
                cout << "2. Nazwisko. " << endl;
                cout << "3. Numer telefonu. " << endl;
                cout << "4. Email. " << endl;
                cout << "5. Adres. " << endl;
                cout << "6. Powrot do Menu. " << endl;
                cout << "-----------------------------" << endl;
                cout << "Wybierz opcje: ";

                wybor = wczytajZnak();
                switch (wybor)
                {

                case '1':
                    cout << "Zmien imie dla adresata o ID " << adresaci[i].idAdresata<<": ";
                    adresaci[i].imie = wczytajLinie();
                    break;

                case '2':
                    cout << "Zmien nazwisko dla adresata o ID: " << adresaci[i].idAdresata<<": ";
                    adresaci[i].nazwisko = wczytajLinie();
                    break;

                case '3':
                    cout << "Zmien numer telefonu dla adresata o ID: " << adresaci[i].idAdresata<<": ";
                    adresaci[i].numerTelefonu = wczytajLinie();
                    break;

                case '4':
                    cout << "Zmien email dla adresata o ID: " << adresaci[i].idAdresata<<": ";
                    adresaci[i].email = wczytajLinie();
                    break;

                case '5':
                    cout << "Zmien adres dla adresata o ID: " << adresaci[i].idAdresata<<": ";
                    adresaci[i].adres = wczytajLinie();
                    break;

                case '6':
                    cout << "Powrot do Menu glownego." << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Brak kontaktu o podanym numerze ID." << endl;
            system("pause");
            break;
        }

        if (wybor == '6')
        {
            zapiszZmianyWPliku(adresaci);
            break;
        }
    }
}

void przejdzDoMenuZalogowanegoUzytkownika(vector<Uzytkownik> &uzytkownicy, Uzytkownik &zalogowanyUzytkownik)
{
    vector <Adresat> adresaci = wczytajPlikAdresatow(zalogowanyUzytkownik.id);
    char wybor;
    while (true)
    {
        system("cls");
        cout << "---------->MENU GLOWNE<----------" << endl;
        cout << "1. Dodaj adresata." << endl;
        cout << "2. Wyszukaj po imieniu. " << endl;
        cout << "3. Wyszukaj po nazwisku. " << endl;
        cout << "4. Wyswietl wszytkich adresatow. " << endl;
        cout << "5. Usun adresata. " << endl;
        cout << "6. Edytuj adresata. " << endl;
        cout << "---------------------------------" << endl;
        cout << "7. Zmien haslo. " << endl;
        cout << "9. Wyloguj sie. " << endl;
        cout << "---------------------------------" << endl;
        cout << "Wybierz opcje: " << endl;

        wybor = wczytajZnak();
        switch (wybor)
        {

        case '1':
            dodajAdresata(adresaci, zalogowanyUzytkownik.id);
            break;

        case '2':
            wyszukajPoImieniu(adresaci);
            break;

        case '3':
            wyszukajPoNazwisku(adresaci);
            break;

        case '4':
            wyswietlWszystkich(adresaci);
            break;

        case '5':
            usunAdresata(adresaci);
            break;

        case '6':
            edytujAdresata(adresaci);
            break;

        case '7':
            zmienHaslo(uzytkownicy, zalogowanyUzytkownik);
            break;

        case '9':
            //wylogowanieUzytkownika();
            //break;
            return;
        }


    }
}


int main()
{
    vector<Uzytkownik> uzytkownicy = wczytajPlikUzytkownikow();
    Uzytkownik zalogowanyUzytkownik;
    char wybor;


    while (true)
    {
        system("cls");
        cout << "---------PANEL LOGOWANIA---------" << endl;
        cout << "1. Rejestracja." << endl;
        cout << "2. Logowanie. " << endl;
        cout << "9. Zakoncz porgram. " << endl;
        cout << "---------------------------------" << endl;
        cout << "Wybierz opcje: " << endl;

        wybor = wczytajZnak();
        zalogowanyUzytkownik.id = 0;

        switch (wybor)
        {
        case '1':
            rejestracjaUzytkownika(uzytkownicy);
            break;

        case '2':
            logowanieUzytkownika(uzytkownicy, zalogowanyUzytkownik);
            break;

        case '9':
            cout << "Konczenie pracy programu..." << endl;
            exit(0);
            break;

        default:
            cout << "Nie ma takiej opcji. Wybierz ponownie" << endl;
            system("pause");
            break;
        }
        if(zalogowanyUzytkownik.id != 0)
        {
            cout << "Witaj " << zalogowanyUzytkownik.login << "!" << endl;
            system("pause");
            przejdzDoMenuZalogowanegoUzytkownika(uzytkownicy, zalogowanyUzytkownik);
        }

    }


    return 0;
}
