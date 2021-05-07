#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;
int idZalogowanegoUzytkownika = 0;
int idOstatniegoAdresata = 0;
int liczbaWszystkichAdresatowWKsiazceAdresowej = 0;
struct Uzytkownik {
    int idUzytkownika;
    string login, haslo;
};
void wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy) {
    fstream plik;
    plik.open("uzytkownicy.txt",ios::in);
    if(plik.good()==false) {
        cout << "Brak zapisanych u¾ytkownik¢w." << endl;
    }
    string linia;
    int nrLini = 1;
    int i = 0;
    while(getline(plik,linia,'|')) {
        switch(nrLini) {
        case 1:
            uzytkownicy.push_back(Uzytkownik());
            uzytkownicy[i].idUzytkownika = atoi(linia.c_str());
            break;
        case 2:
            uzytkownicy[i].login = linia;
            break;
        case 3:
            uzytkownicy[i].haslo = linia;
            i++;
            nrLini = 0;
            break;
        }
        nrLini++;
    }
    plik.close();
}
int rejestracja(vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow) {
    string login, haslo;
    int idUzytkownika;
    cout << "Podaj login: ";
    cin >> login;
    for(int i = 0; i <iloscUzytkownikow; i++) {
        if(uzytkownicy[i].login == login) {
            cout << "Taka nazwa u¾ytkownika ju¾ istnieje. Podaj inn¥ nazw© u¾ytkownika: ";
            cin >> login;
            i = 0;
        }
    }
    cout << "Podaj hasˆo: ";
    cin >> haslo;
    if(iloscUzytkownikow == 0) {
        idUzytkownika = 1;
    } else if(iloscUzytkownikow > 0) {
        idUzytkownika = uzytkownicy[uzytkownicy.size() - 1].idUzytkownika + 1;
    }
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[iloscUzytkownikow].login = login;
    uzytkownicy[iloscUzytkownikow].haslo = haslo;
    uzytkownicy[iloscUzytkownikow].idUzytkownika = idUzytkownika;
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out|ios::app);
    if(iloscUzytkownikow == 0) {
        plik << idUzytkownika << '|' << login << '|' << haslo << '|';
    } else {
        plik << endl << idUzytkownika << '|' << login << '|' << haslo << '|';
    }
    plik.close();
    cout << "Konto zaˆo¾one" << endl;
    Sleep(1000);
    return iloscUzytkownikow + 1;
}
int logowanie(vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow) {
    string login, haslo;
    cout << "Wprowad« login: ";
    cin >> login;
    for(int i = 0; i < iloscUzytkownikow; i++) {
        if(uzytkownicy[i].login == login) {
            for(int j = 0; j < 3; j++) {
                cout << "Wprowad« hasˆo: ";
                     cin >> haslo;
                if(uzytkownicy[i].haslo == haslo) {
                    cout << "Jeste˜ zalogowany.";
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podaˆe˜ 3 razy niepoprawne hasˆo. Odczekaj 3 sekundy do kolejnej pr¢by.";
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma u¾ytkownika o takim loginie!";
    Sleep(1500);
    return 0;
}
void zmianaHasla(vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow) {
    string haslo;
    cout << "Podaj nowe hasˆo: ";
    cin >> haslo;
    for(int i = 0; i<iloscUzytkownikow; i++) {
        if(uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Hasˆo zostaˆo zmienione." << endl;
            Sleep(1500);
        }
    }
    fstream plik;
    plik.open("uzytkownicy.txt",ios::out|ios::trunc);
    plik.clear();
    plik.close();
    plik.open("uzytkownicy.txt",ios::out|ios::app);
    for(int i = 0; i < uzytkownicy.size(); i++) {
        if(i == 0) {
            plik << uzytkownicy[i].idUzytkownika << '|' << uzytkownicy[i].login << '|' << uzytkownicy[i].haslo << '|';
        } else {
            plik << endl << uzytkownicy[i].idUzytkownika << '|' << uzytkownicy[i].login << '|' << uzytkownicy[i].haslo << '|';
        }
    }
    plik.close();
}
struct Osoba {
    int id, idUzytkownika;
    string imie, nazwisko,numerTelefonu,email,adres;
};
Osoba wczytajAdresata(string daneAdresata) {
    Osoba adresat;
    string pojedynczaDanaAdresata;
    int numerDanejAdresata = 1;
    for(int nrZnaku = 0; nrZnaku < daneAdresata.length(); nrZnaku++) {
        if(daneAdresata[nrZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresata[nrZnaku];
        } else {
            switch(numerDanejAdresata) {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            numerDanejAdresata++;
            pojedynczaDanaAdresata = "";
        }
    }
    return adresat;
}
void wczytajKsiazkeAdresowa(vector <Osoba> &ksiazkaAdresowa) {
    Osoba adresat;
    string daneAdresata;
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::in);
    if(plik.good() == true) {
        while(getline(plik,daneAdresata)) {
            adresat = wczytajAdresata(daneAdresata);
            if(adresat.idUzytkownika == idZalogowanegoUzytkownika) {
                ksiazkaAdresowa.push_back(adresat);
            }
            idOstatniegoAdresata = adresat.id;
            liczbaWszystkichAdresatowWKsiazceAdresowej++;
        }
    } else if(plik.good()==false) {
        cout << "Brak zapisanych os¢b w ksi¥¾ce adresowej." << endl;
    }
    plik.close();
}
int zapiszOsobeDoKsiazki(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string imie, nazwisko, numer, email, adres;
    int id;
    cout << "Podaj imi©: " << endl;
    cin >> imie;
    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    for(int i = 0; i < iloscOsob; i++) {
        if (imie == ksiazkaAdresowa[i].imie && nazwisko == ksiazkaAdresowa[i].nazwisko && idZalogowanegoUzytkownika == ksiazkaAdresowa[i].idUzytkownika) {
            cout << "Osoba o podanym imieniu i nazwisku znajduje si© w Twojej Ksi¥¾ce Adresowej" << endl;
            cout << "Wybierz 1. aby poda† inne dane osobowe" << endl;
            cout << "Wybierz 2. aby wyj˜† z funkcji zapisu" << endl;
            int wybor;
            cin >> wybor;
            if (wybor == 1) {
                cout << "Podaj imi©: " << endl;
                cin >> imie;
                cout << "Podaj nazwisko: " << endl;
                cin >> nazwisko;
            } else if(wybor == 2) {
                return iloscOsob;
            }
            i = -1;
        }
    }
    cout << "Podaj numer telefonu: " << endl;
    cin >> numer;
    cout << "Podaj email: " << endl;
    cin >> email;
    cout << "Podaj adres: " << endl;
    cin.ignore();
    getline(cin,adres);
    ksiazkaAdresowa.clear();
    wczytajKsiazkeAdresowa(ksiazkaAdresowa);
    if(liczbaWszystkichAdresatowWKsiazceAdresowej == 0) {
        id = 1;
    } else if(liczbaWszystkichAdresatowWKsiazceAdresowej != 0) {
        id = idOstatniegoAdresata + 1;
    }
    ksiazkaAdresowa.push_back(Osoba());
    ksiazkaAdresowa.shrink_to_fit();
    ksiazkaAdresowa[iloscOsob].imie = imie;
    ksiazkaAdresowa[iloscOsob].nazwisko = nazwisko;
    ksiazkaAdresowa[iloscOsob].numerTelefonu = numer;
    ksiazkaAdresowa[iloscOsob].email = email;
    ksiazkaAdresowa[iloscOsob].adres = adres;
    ksiazkaAdresowa[iloscOsob].idUzytkownika = idZalogowanegoUzytkownika;
    ksiazkaAdresowa[iloscOsob].id = id;
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out|ios::app);
    if(liczbaWszystkichAdresatowWKsiazceAdresowej == 0 && iloscOsob == 0) {
        plik << id << '|' << idZalogowanegoUzytkownika << '|' << imie << '|' << nazwisko << '|' <<  numer << '|' << email << '|' << adres << '|';
    } else {
        plik << endl << id << '|' << idZalogowanegoUzytkownika << '|' << imie << '|' << nazwisko << '|' <<  numer << '|' << email << '|' << adres << '|';
    }
    plik.close();
    cout << "Osoba zostaˆa zapisana do Ksi¥¾ki adresowej." << endl;
    Sleep(1000);
    return iloscOsob + 1;
}
void wyszukajPrzezImie(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string imie;
    cout << "Wyszukaj za pomoc¥ imienia: " << endl;
    cin >> imie;
    int czyIstnieje = 0;
    for(int i = 0; i <= iloscOsob; i++) {
        if(ksiazkaAdresowa[i].imie == imie && idZalogowanegoUzytkownika == ksiazkaAdresowa[i].idUzytkownika) {
            cout << "*************************" << endl;
            cout << "Imi©: " << ksiazkaAdresowa[i].imie << endl;
            cout << "Nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
            cout << "Numer telefonu: " << ksiazkaAdresowa[i].numerTelefonu << endl;
            cout << "Adres email: " << ksiazkaAdresowa[i].email << endl;
            cout << "Adres zamieszkania: " << ksiazkaAdresowa[i].adres << endl;
            cout << "Id osoby: " << ksiazkaAdresowa[i].id << endl;
            cout << endl;
            czyIstnieje++;
        }
    }
    if(czyIstnieje == 0) { //Zwiekszona wartosc zmiennej czyIstnieje oznacza znalezienie osoby o podanym imieniu.
        cout << "Osoba o podanym imieniu nie jest zapisana." << endl;
    }
    system("pause");
}
void wyszukajPrzezNazwisko(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string nazwisko;
    cout << "Wyszukaj za pomoc¥ nazwiska: "<< endl;
    cin >> nazwisko;
    int czyIstnieje = 0;
    for(int i=0; i<=iloscOsob; i++) {
        if(ksiazkaAdresowa[i].nazwisko == nazwisko && idZalogowanegoUzytkownika == ksiazkaAdresowa[i].idUzytkownika) {
            cout << "*************************" << endl;
            cout << "Imi©: " << ksiazkaAdresowa[i].imie << endl;
            cout << "Nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
            cout << "Numer telefonu: " << ksiazkaAdresowa[i].numerTelefonu << endl;
            cout << "Adres email: " << ksiazkaAdresowa[i].email << endl;
            cout << "Adres zamieszkania: " << ksiazkaAdresowa[i].adres << endl;
            cout << "Id osoby: " << ksiazkaAdresowa[i].id << endl;
            cout << endl;
            czyIstnieje++;
        }
    }
    if(czyIstnieje == 0) { //Zwiekszona wartosc zmiennej czyIstnieje oznacza znalezienie osoby o podanym imieniu.
        cout << "Osoba o podanym nazwisku nie jest zapisana." << endl;
    }
    system("pause");
}
void wypiszWszystkieZapisaneOsoby(vector <Osoba> &ksiazkaAdresowa) {
    ksiazkaAdresowa.shrink_to_fit();
    for(int i = 0; i<ksiazkaAdresowa.size(); i++) {
        if (idZalogowanegoUzytkownika == ksiazkaAdresowa[i].idUzytkownika) {
            cout << "*************************" << endl;
            cout << "Imi©: " << ksiazkaAdresowa[i].imie << endl;
            cout << "Nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
            cout << "Numer telefonu: " << ksiazkaAdresowa[i].numerTelefonu << endl;
            cout << "Adres email: " << ksiazkaAdresowa[i].email << endl;
            cout << "Adres zamieszkania: " << ksiazkaAdresowa[i].adres << endl;
            cout << "Id osoby: " << ksiazkaAdresowa[i].id << endl;
            cout << endl;
        }
    }
    system("pause");
}
void przepiszDaneDoNowegoPlikuTekstowegoPoUsunieciuAdresata(int idUsunietegoAdresata) {
    Osoba adresat;
    string daneAdresataOryginalnyPlik;
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::in);
    if(plik.good()==false) {
        cout << "Brak zapisanych os¢b w ksi¥¾ce adresowej." << endl;
    }
    while(getline(plik,daneAdresataOryginalnyPlik)) {
        adresat = wczytajAdresata(daneAdresataOryginalnyPlik);
        if(adresat.id != idUsunietegoAdresata) {
            fstream plik;
            plik.open("ksiazka_adresowa_tymczasowa.txt",ios::out|ios::app);
            if(ifstream("ksiazka_adresowa_tymczasowa.txt", ios::ate).tellg()) {
                plik << endl << daneAdresataOryginalnyPlik;
            } else {
                plik << daneAdresataOryginalnyPlik;
            }
            plik.close();
        }
    }
    plik.close();
    if(remove("ksiazka_adresowa.txt") == 0) {
        rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt");
    } else {
        cout << "Przepisywanie pliku nie powiodˆo si©." << endl;
    }
}
void przepiszDaneDoNowegoPlikuTekstowegoPoEdycjiAdresata(Osoba edytowanyAdresat) {
    Osoba adresat;
    string daneAdresataOryginalnyPlik;
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::in);
    if(plik.good()==false) {
        cout << "Brak zapisanych os¢b w ksi¥¾ce adresowej." << endl;
    }
    while(getline(plik,daneAdresataOryginalnyPlik)) {
        adresat = wczytajAdresata(daneAdresataOryginalnyPlik);
        if(adresat.id != edytowanyAdresat.id) {
            fstream plik;
            plik.open("ksiazka_adresowa_tymczasowa.txt",ios::out|ios::app);
            if(ifstream("ksiazka_adresowa_tymczasowa.txt", ios::ate).tellg()) {
                plik << endl << daneAdresataOryginalnyPlik;
            } else {
                plik << daneAdresataOryginalnyPlik;
            }
            plik.close();
        } else if(adresat.id == edytowanyAdresat.id) {
            fstream plik;
            plik.open("ksiazka_adresowa_tymczasowa.txt",ios::out|ios::app);
            if(ifstream("ksiazka_adresowa_tymczasowa.txt", ios::ate).tellg()) {
                plik << endl << edytowanyAdresat.id << '|' << edytowanyAdresat.idUzytkownika << '|' << edytowanyAdresat.imie << '|' << edytowanyAdresat.nazwisko << '|' <<  edytowanyAdresat.numerTelefonu << '|' << edytowanyAdresat.email << '|' << edytowanyAdresat.adres << '|';
            } else {
                plik << edytowanyAdresat.id << '|' << edytowanyAdresat.idUzytkownika << '|' << edytowanyAdresat.imie << '|' << edytowanyAdresat.nazwisko << '|' <<  edytowanyAdresat.numerTelefonu << '|' << edytowanyAdresat.email << '|' << edytowanyAdresat.adres << '|';
            }
            plik.close();
        }
    }
    plik.close();
    if(remove("ksiazka_adresowa.txt") == 0) {
        rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt");
    } else {
        cout << "Przepisywanie pliku nie powiodˆo si©." << endl;
    }
}
void edytujInformacjeOsobowe(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string imie, nazwisko,numerTelefonu,email,adres;
    Osoba edytowanyAdresat;
    int id;
    cout << "Podaj id osoby do edycji: " << endl;
    cin >> id;
    int czyIstnieje = 0;
    char wybor;
    for(int i = 0; i < iloscOsob; i++) {
        if(ksiazkaAdresowa[i].id == id && ksiazkaAdresowa[i].idUzytkownika == idZalogowanegoUzytkownika) {
            while(1) {
                system("cls");
                cout << "Witaj w edytorze." << endl;
                cout << "1 - imie" << endl;
                cout << "2 - nazwisko" << endl;
                cout << "3 - numer telefonu" << endl;
                cout << "4 - email" << endl;
                cout << "5 - adres" << endl;
                cout << "6 - powr¢t do menu" << endl;
                cin >> wybor;
                if (wybor == '1') {
                    cout << "Wprowad« nowe imi©:" << endl;
                    cin >> imie;
                    ksiazkaAdresowa[i].imie = imie;
                    cout << "Zmieniono imi© na " << imie << endl;
                } else if(wybor == '2') {
                    cout << "Wprowad« nowe nazwisko:" << endl;
                    cin >> nazwisko;
                    ksiazkaAdresowa[i].nazwisko = nazwisko;
                    cout << "Zmieniono nazwisko na " << nazwisko << endl;
                } else if(wybor == '3') {
                    cout << "Wprowad« nowy numer telefonu:" << endl;
                    cin >> numerTelefonu;
                    ksiazkaAdresowa[i].numerTelefonu = numerTelefonu;
                    cout << "Zmieniono numer telefonu na " << numerTelefonu << endl;
                } else if(wybor == '4') {
                    cout << "Wprowad« nowy email:" << endl;
                    cin >> email;
                    ksiazkaAdresowa[i].email = email;
                    cout << "Zmieniono email na " << email << endl;
                } else if(wybor == '5') {
                    cout << "Wprowad« nowy adres:" << endl;
                    cin.ignore();
                    getline(cin,adres);
                    ksiazkaAdresowa[i].adres = adres;
                    cout << "Zmieniono adres na " << email << endl;
                } else if(wybor == '6') {
                    edytowanyAdresat.id = ksiazkaAdresowa[i].id;
                    edytowanyAdresat.idUzytkownika = ksiazkaAdresowa[i].idUzytkownika;
                    edytowanyAdresat.imie = ksiazkaAdresowa[i].imie;
                    edytowanyAdresat.nazwisko = ksiazkaAdresowa[i].nazwisko;
                    edytowanyAdresat.numerTelefonu = ksiazkaAdresowa[i].numerTelefonu;
                    edytowanyAdresat.email = ksiazkaAdresowa[i].email;
                    edytowanyAdresat.adres = ksiazkaAdresowa[i].adres;
                    break;
                } else {
                    cout << "Wybierz poprawny numer!" << endl;
                    Sleep(1000);
                }
            }
            czyIstnieje++;
        }
    }
    if(czyIstnieje == 0) { //Zwiekszona wartosc zmiennej czyIstnieje oznacza znalezienie osoby o podanym imieniu.
        cout << "Osoba o podanym imieniu i nazwisku nie jest zapisana w Twojej ksi¥¾ce adresowej." << endl;
    } else {
        przepiszDaneDoNowegoPlikuTekstowegoPoEdycjiAdresata(edytowanyAdresat);
    }
    system("pause");
}
int usunAdresata(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    int id;
    cout << "Podaj id osoby do usuni©cia: " << endl;
    cin >> id;
    int czyIstnieje = 0;
    char wybor;
    for(int i = 0; i < iloscOsob; i++) {
        if(ksiazkaAdresowa[i].id == id && ksiazkaAdresowa[i].idUzytkownika == idZalogowanegoUzytkownika) {
            cout << "Je¾eli chcesz usun¥† adresata wci˜nij t" << endl;
            char czyUsunac;
            cin >> czyUsunac;
            if(czyUsunac == 't') {
                ksiazkaAdresowa.erase(ksiazkaAdresowa.begin() + i);
                ksiazkaAdresowa.shrink_to_fit();
                cout << "Usuni©to osob©." << endl;
                Sleep(1000);
            } else {
                cout << "Osoba nie zostaˆa usuni©ta." << endl;
                Sleep(1000);
            }
        }
        czyIstnieje++;
    }
    if(czyIstnieje == 0) { //Zwiekszona wartosc zmiennej czyIstnieje oznacza znalezienie osoby o podanym imieniu.
        cout << "Osoba o podanym id nie jest zapisana w ksi¥¾ce adresowej." << endl;
    } else {
        przepiszDaneDoNowegoPlikuTekstowegoPoUsunieciuAdresata(id);
    }
    ksiazkaAdresowa.shrink_to_fit();

    iloscOsob = ksiazkaAdresowa.size();
    return iloscOsob;
    system("pause");
}
int wczytajMenuKsiazkiAdresowej(vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow) {
    vector <Osoba> ksiazkaAdresowa;
    wczytajKsiazkeAdresowa(ksiazkaAdresowa);
    int iloscOsob = ksiazkaAdresowa.size();
    for(int i = 0; i < iloscOsob; i++) {
        cout << ksiazkaAdresowa[i].imie << endl;
    }
    char wybor;
    while(1) {
        system("cls");
        cout << iloscOsob << endl;
        cout << "KSI¤½KA ADRESOWA"<< endl;
        cout << "1. Dodaj adresata"<< endl;
        cout << "2. Wyszukaj po imieniu."<< endl;
        cout << "3. Wyszukaj po nazwisku"<< endl;
        cout << "4. Wy˜wietl wszystkich adresat¢w"<< endl;
        cout << "5. Usuä adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmieä hasˆo" << endl;
        cout << "8. Wyloguj" << endl;
        cout << "Tw¢j wyb¢r: ";
        cin >> wybor;
        if (wybor == '1') {
            iloscOsob = zapiszOsobeDoKsiazki(ksiazkaAdresowa,iloscOsob);
        } else if(wybor == '2') {
            wyszukajPrzezImie(ksiazkaAdresowa,iloscOsob);
        } else if(wybor == '3') {
            wyszukajPrzezNazwisko(ksiazkaAdresowa,iloscOsob);
        } else if(wybor == '4') {
            wypiszWszystkieZapisaneOsoby(ksiazkaAdresowa);
        } else if(wybor == '5') {
            iloscOsob = usunAdresata(ksiazkaAdresowa,iloscOsob);
        } else if(wybor == '6') {
            edytujInformacjeOsobowe(ksiazkaAdresowa,iloscOsob);
        } else if(wybor == '7') {
            zmianaHasla(uzytkownicy,iloscUzytkownikow);
        } else if(wybor == '8') {
            return 0;
        } else {
            cout << "Wybierz poprawny numer!" << endl;
            Sleep(1000);
        }
    }
}
int main() {
    vector <Uzytkownik> uzytkownicy;
    wczytajUzytkownikow(uzytkownicy);
    int iloscUzytkownikow = uzytkownicy.size();
    char wybor;
    while(1) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            setlocale( LC_ALL, "" );
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoäcz program" << endl;
            cin >> wybor;
            if(wybor == '1') {
                iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
            } else if(wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,iloscUzytkownikow);
            } else if(wybor == '9') {
                exit(0);
            }
        } else {
            idZalogowanegoUzytkownika = wczytajMenuKsiazkiAdresowej(uzytkownicy,iloscUzytkownikow);
        }
    }
    return 0;
}
