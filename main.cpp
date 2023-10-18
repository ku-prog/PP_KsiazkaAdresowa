#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Adresat
{
    int id;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
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

vector <Adresat> wczytajPlik()
{
    vector <Adresat> adresaci;
    Adresat nowyAdresat;
    string liniaOdczytu = "";
    fstream plik;

    plik.open("plik.txt", ios::in);
    if (!plik.good())
        cout << "Nie mozna otworzyc pliku!" << endl;

    int itr = 0;
    string dane = "";

    while(getline(plik, liniaOdczytu))
    {


        while(liniaOdczytu[itr] != '|')
        {
            dane = liniaOdczytu.substr(0, itr + 1);
            itr++;
        }
        liniaOdczytu.erase(itr - dane.length(), dane.length() + 1);
        nowyAdresat.id = stoi(dane);

        itr = 0;
        int flaga = 0;

        while(liniaOdczytu.length() != 0)
        {
            flaga++;
            while(liniaOdczytu[itr] != '|')
            {
                dane = liniaOdczytu.substr(0, itr + 1);

                if (liniaOdczytu[itr+1] == '|')
                {
                    switch (flaga)
                    {
                    case 1:
                    {
                        nowyAdresat.imie = dane;
                        break;
                    }
                    case 2:
                    {
                        nowyAdresat.nazwisko = dane;
                        break;
                    }
                    case 3:
                    {
                        nowyAdresat.numerTelefonu = dane;
                        break;
                    }
                    case 4:
                    {
                        nowyAdresat.email = dane;
                        break;
                    }
                    case 5:
                    {
                        nowyAdresat.adres = dane;
                        break;
                    }
                    }
                }
                itr++;
            }
            liniaOdczytu.erase(itr - dane.length(), dane.length() + 1);
            itr = 0;
        }
        adresaci.push_back(nowyAdresat);
    }
    plik.close();

    return adresaci;
}

int pobierzIloscAdresatow(vector <Adresat> &adresaci)
{
    fstream plik;
    string linia;
    int nrLinii = 0;

    plik.open("plik.txt", ios::in);
    while(getline(plik, linia))
    {
        nrLinii++;
    }
    plik.close();
    return nrLinii;
}

void dodajAdresata(vector <Adresat> &adresaci)
{
    string numerID, liniaZapisu = "";
    Adresat nowyAdresat;

    fstream plik;
    plik.open("plik.txt", ios::out|ios::app);

    if(pobierzIloscAdresatow(adresaci) <= 0)
        nowyAdresat.id = 1;
    else
        nowyAdresat.id = adresaci[pobierzIloscAdresatow(adresaci) - 1].id + 1;

    numerID = to_string(nowyAdresat.id);

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

    liniaZapisu = numerID + "|" + nowyAdresat.imie + "|" + nowyAdresat.nazwisko + "|" + nowyAdresat.numerTelefonu + "|" + nowyAdresat.email + "|" + nowyAdresat.adres + "|";

    plik << liniaZapisu + "\n";

    plik.close();

    adresaci.push_back(nowyAdresat);
}

void wyszukajPoImieniu(vector <Adresat> adresaci)
{
    cout << "Wprowadz szukane imie: ";
    string szukaneImie = wczytajLinie();

    for(auto x : adresaci)
    {
        if(x.imie == szukaneImie)
        {
            cout << "ID:             " << x.id << endl;
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
    cout << "Wprowadz szukane nazwisko: ";
    string szukaneNazwisko = wczytajLinie();

    for(auto x : adresaci)
    {
        if(x.nazwisko == szukaneNazwisko)
        {
            cout << "ID:             " << x.id << endl;
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

    for(auto x : adresaci)
    {
        cout << "ID:             " << x.id << endl;
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
    plik.open("plik.txt", ios::out|ios::trunc);
    plik.close();

    plik.open("plik.txt", ios::out|ios::app);

    for(auto x : adresaci)
    {
        liniaZapisu = to_string(x.id) + "|" + x.imie + "|" + x.nazwisko + "|" + x.numerTelefonu + "|" + x.email + "|" + x.adres + "|" + "\n";
        plik << liniaZapisu;
    }
    plik.close();
}

void usunAdresata(vector <Adresat> &adresaci)
{
    cout << "Podaj numer ID uzytkownika do usuniecia: ";
    int usunID = wczytajLiczbe(), pozycjaAdresata = 0;


    for(auto x : adresaci)
    {
        if(x.id == usunID)
        {
            cout << "Usuwasz adresata o id: " << x.id << endl;
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

    cout << "Podaj ID adresata do edycji: ";
    idDoEdycji = wczytajLiczbe();

    for (size_t itr = 0; itr < adresaci.size(); itr++)
    {
        if (adresaci[itr].id == idDoEdycji)
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
                {
                    cout << "Zmien imie dla adresata o ID " << adresaci[itr].id <<": ";
                    adresaci[itr].imie = wczytajLinie();
                    break;
                }

                case '2':
                {
                    cout << "Zmien nazwisko dla adresata o ID: " << adresaci[itr].id <<": ";
                    adresaci[itr].nazwisko = wczytajLinie();
                    break;
                }

                case '3':
                {
                    cout << "Zmien numer telefonu dla adresata o ID: " << adresaci[itr].id <<": ";
                    adresaci[itr].numerTelefonu = wczytajLinie();
                    break;
                }

                case '4':
                {
                    cout << "Zmien email dla adresata o ID: " << adresaci[itr].id <<": ";
                    adresaci[itr].email = wczytajLinie();
                    break;
                }

                case '5':
                {
                    cout << "Zmien adres dla adresata o ID: " << adresaci[itr].id <<": ";
                    adresaci[itr].adres = wczytajLinie();
                    break;
                }

                case '6':
                {
                    cout << "Powrot do Menu glownego." << endl;
                    break;
                }
                }

            }
        }


        if (wybor == '6')
        {
            zapiszZmianyWPliku(adresaci);
            break;
        }

    }

}



int main()
{

    vector <Adresat> adresaci = wczytajPlik();
    char wybor = '0';

    //int iloscAdresatow = pobierzIloscAdresatow(adresaci);

    while (true)
    {
        system("cls");
        cout << "---------------MENU--------------" << endl;
        cout << "1. Dodaj adresata." << endl;
        cout << "2. Wyszukaj po imieniu. " << endl;
        cout << "3. Wyszukaj po nazwisku. " << endl;
        cout << "4. Wyswietl wszytkich adresatow. " << endl;
        cout << "5. Usun adresata. " << endl;
        cout << "6. Edytuj adresata. " << endl;
        cout << "9. Zakoncz porgram. " << endl;
        cout << "---------------------------------" << endl;
        cout << "Wybierz opcje: " << endl;

        wybor = wczytajZnak();
        switch (wybor)
        {

        case '1':
        {
            dodajAdresata(adresaci);
            break;
        }
        case '2':
        {
            wyszukajPoImieniu(adresaci);
            break;
        }

        case '3':
        {
            wyszukajPoNazwisku(adresaci);
            break;
        }

        case '4':
        {
            wyswietlWszystkich(adresaci);
            break;
        }

        case '5':
        {
            usunAdresata(adresaci);
            break;
        }

        case '6':
        {
            edytujAdresata(adresaci);
            break;
        }

        case '9':
        {
            cout << "Konczenie pracy programu..." << endl;
            exit(0);
            break;
        }

        }

    }


    return 0;
}

