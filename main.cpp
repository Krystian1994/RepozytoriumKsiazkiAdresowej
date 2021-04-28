#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;
struct Osoba {
    int id;
    string imie, nazwisko,numerTelefonu,email,adres;
};
void wczytajKsiazkeAdresowa(vector <Osoba> &ksiazkaAdresowa) {
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::in);

    if(plik.good()==false) {
        cout << "Brak zapisanych osób w ksi¹¿ce adresowej." << endl;
    }
    string linia;
    int nrLini = 1;
    int i = 0;
    while(getline(plik,linia,'|')) {
        switch(nrLini) {
        case 1:
            ksiazkaAdresowa.push_back(Osoba());
            ksiazkaAdresowa[i].id = atoi(linia.c_str());
            break;
        case 2:
            ksiazkaAdresowa[i].imie = linia;
            break;
        case 3:
            ksiazkaAdresowa[i].nazwisko = linia;
            break;
        case 4:
            ksiazkaAdresowa[i].numerTelefonu = linia;
            break;
        case 5:
            ksiazkaAdresowa[i].email = linia;
            break;
        case 6:
            ksiazkaAdresowa[i].adres = linia;
            i++;
            nrLini = 0;
            break;
        }
        nrLini++;
    }
    plik.close();
}
int zapiszOsobeDoKsiazki(vector <Osoba> &ksiazkaAdresowa,int liczbaZapisow) {
    string imie, nazwisko, numer, email, adres;
    int id;
    cout << "Podaj imiê: " << endl;
    cin >> imie;
    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    for(int i = 0; i < liczbaZapisow; i++) {
        if ((imie == ksiazkaAdresowa[i].imie) && (nazwisko == ksiazkaAdresowa[i].nazwisko)) {
            cout << "Osoba o podanym imieniu i nazwisku znajduje siê w Ksi¹¿ce Adresowej" << endl;
            cout << "Wybierz 1. aby podaæ inne dane osobowe" << endl;
            cout << "Wybierz 2. aby wyjœæ z funkcji zapisu" << endl;
            int wybor;
            cin >> wybor;
            if (wybor == 1) {
                cout << "Podaj imiê: " << endl;
                cin >> imie;
                cout << "Podaj nazwisko: " << endl;
                cin >> nazwisko;
            } else if(wybor == 2) {
                return liczbaZapisow;
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
    if(liczbaZapisow == 0) {
        id = 1;
    } else if(liczbaZapisow > 0) {
        id = ksiazkaAdresowa[ksiazkaAdresowa.size() - 1].id + 1;
    }
    ksiazkaAdresowa.push_back(Osoba());
    ksiazkaAdresowa.shrink_to_fit();
    ksiazkaAdresowa[liczbaZapisow].imie = imie;
    ksiazkaAdresowa[liczbaZapisow].nazwisko = nazwisko;
    ksiazkaAdresowa[liczbaZapisow].numerTelefonu = numer;
    ksiazkaAdresowa[liczbaZapisow].email = email;
    ksiazkaAdresowa[liczbaZapisow].adres = adres;
    ksiazkaAdresowa[liczbaZapisow].id = id;
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out|ios::app);
    if(liczbaZapisow == 0) {
        plik << id << '|' << imie << '|' << nazwisko << '|' <<  numer << '|' << email << '|' << adres << '|';
    } else {
        plik << endl << id << '|' << imie << '|' << nazwisko << '|' <<  numer << '|' << email << '|' << adres << '|';
    }
    plik.close();
    cout << "Osoba zostala zapisana do Ksi¹¿ki adresowej."<< endl;
    Sleep(1000);
    return liczbaZapisow + 1;
}
void wyszukajPrzezImie(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string imie;
    cout << "Wyszukaj za pomoc¹ imienia: "<< endl;
    cin >> imie;
    int czyIstnieje = 0;
    for(int i = 0; i <= iloscOsob; i++) {
        if(ksiazkaAdresowa[i].imie == imie) {
            cout << "*************************" << endl;
            cout << "Imiê: " << ksiazkaAdresowa[i].imie << endl;
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
    cout << "Wyszukaj za pomoc¹ nazwiska: "<< endl;
    cin >> nazwisko;
    int czyIstnieje = 0;
    for(int i=0; i<=iloscOsob; i++) {
        if(ksiazkaAdresowa[i].nazwisko == nazwisko) {
            cout << "*************************" << endl;
            cout << "Imiê: " << ksiazkaAdresowa[i].imie << endl;
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
        cout << "*************************" << endl;
        cout << "Imie: " << ksiazkaAdresowa[i].imie << endl;
        cout << "Nazwisko: " << ksiazkaAdresowa[i].nazwisko << endl;
        cout << "Numer telefonu: " << ksiazkaAdresowa[i].numerTelefonu << endl;
        cout << "Adres email: " << ksiazkaAdresowa[i].email << endl;
        cout << "Adres zamieszkania: " << ksiazkaAdresowa[i].adres << endl;
        cout << "Id osoby: " << ksiazkaAdresowa[i].id << endl;
        cout << endl;
    }
    system("pause");
}
void edytujInformacjeOsobowe(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    string imie, nazwisko,numerTelefonu,email,adres;
    int id;
    cout << "Podaj id osoby do edycji: " << endl;
    cin >> id;
    int czyIstnieje = 0;
    char wybor;
    for(int i = 0; i < iloscOsob; i++) {
        if(ksiazkaAdresowa[i].id == id) {
            while(1) {
                system("cls");
                cout << "Witaj w edytorze." << endl;
                cout << "1 – imiê" << endl;
                cout << "2 – nazwisko" << endl;
                cout << "3 – numer telefonu" << endl;
                cout << "4 – email" << endl;
                cout << "5 – adres" << endl;
                cout << "6 – powrót do menu" << endl;
                cin >> wybor;
                if (wybor == '1') {
                    cout << "WprowadŸ nowe imiê:" << endl;
                    cin >> imie;
                    ksiazkaAdresowa[i].imie = imie;
                    cout << "Zmieniono imiê na " << imie << endl;
                } else if(wybor == '2') {
                    cout << "WprowadŸ nowe nazwisko:" << endl;
                    cin >> nazwisko;
                    ksiazkaAdresowa[i].nazwisko = nazwisko;
                    cout << "Zmieniono nazwisko na " << nazwisko << endl;
                } else if(wybor == '3') {
                    cout << "WprowadŸ nowy numer telefonu:" << endl;
                    cin >> numerTelefonu;
                    ksiazkaAdresowa[i].numerTelefonu = numerTelefonu;
                    cout << "Zmieniono numer telefonu na " << numerTelefonu << endl;
                } else if(wybor == '4') {
                    cout << "WprowadŸ nowy email:" << endl;
                    cin >> email;
                    ksiazkaAdresowa[i].email = email;
                    cout << "Zmieniono email na " << email << endl;
                } else if(wybor == '5') {
                    cout << "WprowadŸ nowy adres:" << endl;
                    cin.ignore();
                    getline(cin,adres);
                    ksiazkaAdresowa[i].adres = adres;
                    cout << "Zmieniono adres na " << email << endl;
                } else if(wybor == '6') {
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
        cout << "Osoba o podanym imieniu i nazwisku nie jest zapisana w ksi¹¿ce adresowej." << endl;
    }
    ksiazkaAdresowa.shrink_to_fit();
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out|ios::trunc);
    plik.clear();
    plik.close();
    plik.open("ksiazka_adresowa.txt",ios::out|ios::app);
    for(int i = 0; i < ksiazkaAdresowa.size(); i++) {
        if(i == 0) {
            plik << ksiazkaAdresowa[i].id << '|' << ksiazkaAdresowa[i].imie << '|' << ksiazkaAdresowa[i].nazwisko << '|' <<  ksiazkaAdresowa[i].numerTelefonu << '|' << ksiazkaAdresowa[i].email << '|' << ksiazkaAdresowa[i].adres << '|';
        } else {
            plik << endl << ksiazkaAdresowa[i].id << '|' << ksiazkaAdresowa[i].imie << '|' << ksiazkaAdresowa[i].nazwisko << '|' <<  ksiazkaAdresowa[i].numerTelefonu << '|' << ksiazkaAdresowa[i].email << '|' << ksiazkaAdresowa[i].adres << '|';
        }
    }
    plik.close();
    system("pause");
}
int usunAdresata(vector <Osoba> &ksiazkaAdresowa,int iloscOsob) {
    int id;
    cout << "Podaj id osoby do usunięcia: " << endl;
    cin >> id;
    int czyIstnieje = 0;
    char wybor;
    for(int i = 0; i < iloscOsob; i++) {
        if(ksiazkaAdresowa[i].id == id) {
            cout << "Je¿eli chcesz usun¹æ adresata wciœnij t" << endl;
            char czyUsunac;
            cin >> czyUsunac;
            if(czyUsunac == 't') {
                ksiazkaAdresowa.erase(ksiazkaAdresowa.begin() + i);
                ksiazkaAdresowa.shrink_to_fit();
                cout << "Usuniêto osobê." << endl;
                Sleep(1000);
            } else {
                cout << "Osoba nie zosta³a usuniêta." << endl;
                Sleep(1000);
            }
        }
        czyIstnieje++;
    }

    if(czyIstnieje == 0) { //Zwiekszona wartosc zmiennej czyIstnieje oznacza znalezienie osoby o podanym imieniu.
        cout << "Osoba o podanym imieniu i nazwisku nie jest zapisana w ksi¹¿ce adresowej." << endl;
    }
    ksiazkaAdresowa.shrink_to_fit();
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out|ios::trunc);
    plik.clear();
    plik.close();
    plik.open("ksiazka_adresowa.txt",ios::out|ios::app);
    for(int i = 0; i < ksiazkaAdresowa.size(); i++) {
        if(i == 0) {
            plik << ksiazkaAdresowa[i].id << '|' << ksiazkaAdresowa[i].imie << '|' << ksiazkaAdresowa[i].nazwisko << '|' <<  ksiazkaAdresowa[i].numerTelefonu << '|' << ksiazkaAdresowa[i].email << '|' << ksiazkaAdresowa[i].adres << '|';
        } else {
            plik << endl << ksiazkaAdresowa[i].id << '|' << ksiazkaAdresowa[i].imie << '|' << ksiazkaAdresowa[i].nazwisko << '|' <<  ksiazkaAdresowa[i].numerTelefonu << '|' << ksiazkaAdresowa[i].email << '|' << ksiazkaAdresowa[i].adres << '|';
        }
    }
    plik.close();
    iloscOsob = ksiazkaAdresowa.size();
    return iloscOsob;
    system("pause");
}
int main() {
    setlocale( LC_ALL, "" );
    vector <Osoba> ksiazkaAdresowa;
    wczytajKsiazkeAdresowa(ksiazkaAdresowa);
    int iloscOsob = ksiazkaAdresowa.size();
    for(int i = 0; i < iloscOsob; i++) {
        cout << ksiazkaAdresowa[i].imie << endl;
    }
    char wybor;
    while(1) {
        system("cls");
        cout << "KSIĄŻKA ADRESOWA"<< endl;
        cout << "1. Dodaj adresata"<< endl;
        cout << "2. Wyszukaj po imieniu."<< endl;
        cout << "3. Wyszukaj po nazwisku"<< endl;
        cout << "4. Wyœwietl wszystkich adresatów"<< endl;
        cout << "5. Usuñ adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoñcz program"<< endl;
        cout << "Twój wybór: ";
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
        } else if(wybor == '9') {
            exit(0);
        } else {
            cout << "Wybierz poprawny numer!" << endl;
            Sleep(1000);
        }
    }
    return 0;
}

