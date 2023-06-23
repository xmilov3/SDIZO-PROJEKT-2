#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include <sstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>

int rozmiar;

void generowanie_pliku(const std::string& liczby) {
    std::ofstream plik("liczby.txt");
    int rozmiar, zakresMin, zakresMax;
    std::cout << "Podaj ilosc liczb:\n";
    std::cin >> rozmiar;
    std::cout << "Podaj zakres minimalny:\n";
    std::cin >> zakresMin;
    std::cout << "Podaj zakres maksymalny:\n";
    std::cin >> zakresMax;

    if (zakresMin > zakresMax) {
        std::cout << "Zakres minimalny nie moze byc wiekszy od zakresu maksymalnego.\n";
        return;
    }

    if (rozmiar > (zakresMax - zakresMin + 1)) {
        std::cout << "Nie mozna wygenerowac " << rozmiar << " unikalnych liczb w podanym zakresie.\n";
        return;
    }

    std::vector<int> wygenerowaneLiczby;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(zakresMin, zakresMax);

    std::set<int> unikalneLiczby;
    while (unikalneLiczby.size() < rozmiar) {
        int liczba = distrib(gen);
        unikalneLiczby.insert(liczba);
    }

    std::copy(unikalneLiczby.begin(), unikalneLiczby.end(), std::back_inserter(wygenerowaneLiczby));

    std::shuffle(wygenerowaneLiczby.begin(), wygenerowaneLiczby.end(), gen);

    plik << rozmiar << std::endl;

    for (int liczba : wygenerowaneLiczby) {
        plik << liczba << std::endl;
    }

    plik.close();
    std::cout << "Wygenerowano plik z unikalnymi liczbami: " << liczby << std::endl;
} // zrobione, liczby sa unikalne

void wyswietl_zawartosc_pliku(const std::string& liczby){
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    std::string linia;
    while (std::getline(plik, linia)) {
        std::cout << linia << std::endl;
    }

    plik.close();
} //zrobione

void wstaw_do_tablicy_na_poczatek(int element) {
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    plik >> rozmiar;

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    int* nowa_tablica = new int[rozmiar + 1];
    for (int i = 0; i < rozmiar; i++) {
        nowa_tablica[i + 1] = tablica[i];
    }
    nowa_tablica[0] = element;
    rozmiar=rozmiar+1;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;
    delete[] nowa_tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal wstawiony pomyslnie do pliku tablica.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
    return;
} // zrobione z liczeniem czasu i z plikiem tablica.txt
void wstaw_do_tablicy_na_koniec(int element){
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    plik >> rozmiar;

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    int* nowa_tablica = new int[rozmiar + 1];
    for (int i = 0; i < rozmiar; i++) {
        nowa_tablica[i] = tablica[i];
    }
    nowa_tablica[rozmiar] = element;
    rozmiar++;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;
    delete[] nowa_tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal wstawiony pomyslnie na koniec pliku tablica.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
    return;
} // zrobione z liczeniem czasu i z plikiem tablica.txt
void wstaw_do_tablicy_losowo(int element){
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    plik >> rozmiar;

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    int indeks = rand() % (rozmiar + 1);  // Losowy indeks w zakresie od 0 do rozmiar+1

    int* nowa_tablica = new int[rozmiar + 1];
    for (int i = 0; i < indeks; i++) {
        nowa_tablica[i] = tablica[i];
    }
    nowa_tablica[indeks] = element;
    for (int i = indeks + 1; i < rozmiar + 1; i++) {
        nowa_tablica[i] = tablica[i - 1];
    }
    rozmiar++;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;
    delete[] nowa_tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal wstawiony pomyslnie w losowe miejsce w pliku tablica.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
    return;
} // zrobione z liczeniem czasu i z plikiem tablica.txt

struct WpisListy {
    int wartosc;
    WpisListy* nastepny;
};

void wstaw_do_listy_na_poczatek(int element) {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwieksz wartosc pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiekszona wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = element;
    nowyWpis->nastepny = glowa->nastepny;
    glowa->nastepny = nowyWpis;

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();


    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na poczatek listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem lista.txt
void wstaw_do_listy_na_koniec(int element) {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwieksz wartosc pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiekszona wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = element;
    nowyWpis->nastepny = nullptr;

    if (glowa == nullptr) {
        glowa = nowyWpis;
        ogon = nowyWpis;
    } else {
        ogon->nastepny = nowyWpis;
        ogon = nowyWpis;
    }

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();


    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na koniec listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem lista.txt
void wstaw_do_listy_losowo(int element) {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwieksz wartosc pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiekszona wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    // Znajdowanie losowego indeksu do wstawienia elementu
    int iloscElementow = 0;
    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        iloscElementow++;
        obecny = obecny->nastepny;
    }

    int indeks = rand() % (iloscElementow + 1);

    // Dodawanie elementu na losowe miejsce w liscie
    obecny = glowa;
    WpisListy* poprzedni = nullptr;
    int aktualnyIndeks = 0;

    while (obecny != nullptr && aktualnyIndeks < indeks) {
        poprzedni = obecny;
        obecny = obecny->nastepny;
        aktualnyIndeks++;
    }

    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = element;
    nowyWpis->nastepny = obecny;

    if (poprzedni == nullptr) {
        glowa = nowyWpis;
    } else {
        poprzedni->nastepny = nowyWpis;
    }

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();



    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na losowe miejsce w liscie w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem lista.txt

struct Wezel {
    int wartosc;
    Wezel* lewy;
    Wezel* prawy;

    Wezel(int val) : wartosc(val), lewy(nullptr), prawy(nullptr) {}
};

Wezel* wstaw(Wezel* korzen, int wartosc) {
    if (korzen == nullptr) {
        return new Wezel(wartosc);
    }

    if (wartosc < korzen->wartosc) {
        korzen->lewy = wstaw(korzen->lewy, wartosc);
    } else {
        korzen->prawy = wstaw(korzen->prawy, wartosc);
    }

    return korzen;
}

void zapisz_drzewo_do_pliku(Wezel* korzen, std::ofstream& plik) {
    if (korzen == nullptr) {
        return;
    }

    zapisz_drzewo_do_pliku(korzen->lewy, plik);
    plik << korzen->wartosc << std::endl;
    zapisz_drzewo_do_pliku(korzen->prawy, plik);
}

void utworz_tablice(){
    std::ifstream plikWejsciowy("liczby.txt");
    if (!plikWejsciowy) {
        std::cout << "Błąd podczas otwierania pliku." << std::endl;
        return;
    }

    std::vector<int> liczby;
    int liczba;
    std::string linia;

    // Wczytaj liczby z pliku i zapisz je w wektorze
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> liczba) {
            liczby.push_back(liczba);
        }
    }

    plikWejsciowy.close();

    // Sprawdź, czy udało się wczytać jakiekolwiek liczby
    if (liczby.empty()) {
        std::cout << "Brak liczb do utworzenia tablicy." << std::endl;
        return;
    }

    // Tworzenie dynamicznej tablicy o rozmiarze wczytanych liczb
    int rozmiar = liczby.size();
    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; ++i) {
        tablica[i] = liczby[i];
    }

    // Zapisz tablicę do pliku "tablica.txt"
    std::ofstream plikWyjsciowy("tablica.txt");
    if (!plikWyjsciowy) {
        std::cout << "Błąd podczas tworzenia pliku z tablicą." << std::endl;
        delete[] tablica; // Zwolnienie zaalokowanej pamięci
        return;
    }

    for (int i = 0; i < rozmiar; ++i) {
        plikWyjsciowy << tablica[i] << std::endl;
    }

    plikWyjsciowy.close();

    std::cout << "Tablica została zapisana do pliku: tablica.txt" << std::endl;

    // Zwolnienie zaalokowanej pamięci
    delete[] tablica;
} // zrobione
void dodaj_do_pliku_lista(WpisListy*& glowa, int wartosc) {
    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = wartosc;
    nowyWpis->nastepny = nullptr;

    if (glowa == nullptr) {
        glowa = nowyWpis;
    } else {
        WpisListy* aktualny = glowa;
        while (aktualny->nastepny != nullptr) {
            aktualny = aktualny->nastepny;
        }
        aktualny->nastepny = nowyWpis;
    }
}
void utworz_liste(){
    std::ifstream plikWejsciowy("liczby.txt");
    if (!plikWejsciowy) {
        std::cout << "Błąd podczas otwierania pliku." << std::endl;
        return;
    }

    WpisListy* glowa = nullptr;
    int liczba;
    std::string linia;

    // Wczytaj liczby z pliku i dodaj je do listy
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> liczba) {
            dodaj_do_pliku_lista(glowa, liczba);
        }
    }

    plikWejsciowy.close();

    // Sprawdź, czy udało się wczytać jakiekolwiek liczby
    if (glowa == nullptr) {
        std::cout << "Brak liczb do utworzenia listy." << std::endl;
        return;
    }

    // Zapisz listę do pliku "lista.txt"
    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy) {
        std::cout << "Błąd podczas tworzenia pliku z listą." << std::endl;
        // Zwolnienie pamięci dla wszystkich elementów listy
        WpisListy* aktualny = glowa;
        while (aktualny != nullptr) {
            WpisListy* nastepny = aktualny->nastepny;
            delete aktualny;
            aktualny = nastepny;
        }
        return;
    }

    WpisListy* aktualny = glowa;
    while (aktualny != nullptr) {
        plikWyjsciowy << aktualny->wartosc << std::endl;
        aktualny = aktualny->nastepny;
    }

    plikWyjsciowy.close();

    std::cout << "Lista została zapisana do pliku: lista.txt" << std::endl;

    // Zwolnienie pamięci dla wszystkich elementów listy
    aktualny = glowa;
    while (aktualny != nullptr) {
        WpisListy* nastepny = aktualny->nastepny;
        delete aktualny;
        aktualny = nastepny;
    }
} // zrobione
void utworz_drzewo_binarne() {
    std::ifstream plikWejsciowy("liczby.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku." << std::endl;
        return;
    }
    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr;
    int liczba;
    std::string linia;

    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> liczba) {
            korzen = wstaw(korzen, liczba);
        }
    }

    plikWejsciowy.close();

    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas tworzenia pliku z drzewem." << std::endl;
        return;
    }

    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    plikWyjsciowy.close();

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Drzewo binarne zostalo utworzone i zapisane do pliku: drzewo.txt" << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu

void wstaw_do_drzewa(const std::string& liczby, int liczba) {
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr;
    int wartosc;
    std::string linia;

    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc);
        }
    }

    plikWejsciowy.close();

    korzen = wstaw(korzen, liczba);

    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    plikWyjsciowy.close();


    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Liczba " << liczba << " zostala dodana do drzewa." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem drzewo.txt

void usun_z_poczatku_drzewa() {
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr;
    int wartosc;
    std::string linia;

    // Wczytaj drzewo z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc);
        }
    }

    plikWejsciowy.close();

    // Usun pierwszy element z drzewa
    if (korzen != nullptr) {
        Wezel* temp = korzen;
        korzen = korzen->prawy;
        delete temp;
    }

    // Zapisz zmodyfikowane drzewo do pliku
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    plikWyjsciowy.close();


    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Pierwszy element z drzewa zostal usuniety." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu
void usun_z_konca_drzewa() {
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr;
    int wartosc;
    std::string linia;

    // Wczytaj drzewo z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc);
        }
    }

    plikWejsciowy.close();

    // Usun ostatni element z drzewa
    if (korzen != nullptr) {
        Wezel* temp = korzen;
        Wezel* parent = nullptr;

        while (temp->prawy != nullptr) {
            parent = temp;
            temp = temp->prawy;
        }

        if (parent != nullptr) {
            parent->prawy = temp->lewy;
        } else {
            korzen = temp->lewy;
        }

        delete temp;
    }

    // Zapisz zmodyfikowane drzewo do pliku
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    plikWyjsciowy.close();


    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Ostatni element z drzewa zostal usuniety." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem drzewo.txt
void usun_losowo_z_drzewa() {
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr;
    int wartosc;
    std::string linia;
    std::vector<int> wartosci;

    // Wczytaj drzewo z pliku i zapisz wartosci w wektorze
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc);
            wartosci.push_back(wartosc);
        }
    }

    plikWejsciowy.close();

    // Sprawdz, czy drzewo jest puste
    if (korzen == nullptr || wartosci.empty()) {
        std::cout << "Drzewo jest puste." << std::endl;
        return;
    }

    // Wygeneruj losowy indeks elementu do usuniecia
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int indeks = std::rand() % wartosci.size();
    int element = wartosci[indeks];

    // Usun ostatni element z drzewa
    if (korzen != nullptr) {
        Wezel* temp = korzen;
        Wezel* parent = nullptr;

        while (temp->prawy != nullptr) {
            parent = temp;
            temp = temp->prawy;
        }

        if (parent != nullptr) {
            parent->prawy = temp->lewy;
        } else {
            korzen = temp->lewy;
        }

        delete temp;
    }

    // Zapisz zmodyfikowane drzewo do pliku
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    plikWyjsciowy.close();


    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element " << element << " zostal usuniety z drzewa." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
} // zrobione z liczeniem czasu i z plikiem drzewo.txt

void wstaw_do_tablicy(){
    int element;
    int choice;
    std::cout<<"Wpisz element jaki chcesz dodac do tablicy\n";
    std::cin>>element;

    while(true) {
        std::cout << "Gdzie chcesz dodac element?\n";
        std::cout << "1. Na poczatek\n";
        std::cout << "2. Na koniec\n";
        std::cout << "3. W losowe miejsce\n";
        std::cout << "4. Powrot\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano na poczatek\n";
                wstaw_do_tablicy_na_poczatek(element);
                break;
            case 2:
                std::cout << "Wybrano na koniec\n";
                wstaw_do_tablicy_na_koniec(element);
                break;
            case 3:
                std::cout << "Wybrano losowe miejsce\n";
                wstaw_do_tablicy_losowo(element);
                break;
            case 4:
                return;
        }
    }

} // zrobione (tu sie nie liczy czasu)
void wstaw_do_listy(){
    int element;
    int choice;
    std::cout<<"Wpisz element jaki chcesz dodac do listy\n";
    std::cin>>element;
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    while(true) {
        std::cout << "Gdzie chcesz dodac element?\n";
        std::cout << "1. Na poczatek\n";
        std::cout << "2. Na koniec\n";
        std::cout << "3. W losowe miejsce\n";
        std::cout << "4. Powrot\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano na poczatek\n";
                wstaw_do_listy_na_poczatek(element);
                break;
            case 2:
                std::cout << "Wybrano na koniec\n";
                wstaw_do_listy_na_koniec(element);
                break;
            case 3:
                std::cout << "Wybrano losowe miejsce\n";
                wstaw_do_listy_losowo(element);
                break;
            case 4:
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)
void wstaw_do_drzewa_menu(){
    int liczba;
    int choice;

    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    while(true) {
        std::cout << "Jaki element chcesz dodac do drzewa?\n";
        std::cout << "1. Wpisz samodzielnie\n";
        std::cout << "2. Losowy\n";
        std::cout << "3. Powrot\n";
        std::cin >> choice;


        switch (choice) {
            case 1:
                std::cout << "Wybrano samodzielne wpisanie\n";
                std::cout << "Wpisz lelement jaki chcesz dodac do drzewa\n";
                std::cin >> liczba;
                wstaw_do_drzewa("liczby.txt",liczba);
                break;
            case 2:
                std::cout << "Wybrano losowa wartosc\n";
                liczba = rand() % 999 + 1;
                wstaw_do_drzewa("liczby.txt",liczba);
                break;
            case 3:
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)
void wstaw_element() {

    int choice;

    while (true) {
        std::cout << "==== MENU WSTAWIANIA ELEMENTU ====\n";
        std::cout << "Gdzie chcesz wstawic element?\n";
        std::cout << "1. Wstaw element do tablicy\n";
        std::cout << "2. Wstaw element do listy\n";
        std::cout << "3. Wstaw element do drzewa\n";
        std::cout << "4. Wroc do menu glownego\n";
        std::cout << "==================================\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano wstawianie elementu do tablicy\n";
                wstaw_do_tablicy();
                break;
            case 2:
                std::cout << "Wybrano wstawianie elementu do listy\n";
                wstaw_do_listy();
                break;
            case 3:
                std::cout << "Wybrano wstawianie elementu do drzewa\n";
                wstaw_do_drzewa_menu();
                break;
            case 4:
                std::cout << "Wybrano powrot do menu glownego\n";
                return;
        }
    }
} //  zrobione (tu sie nie liczy czasu)

void usun_z_poczatku_tablicy() {
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int rozmiar;
    plik >> rozmiar;

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();


    int pierwsza_liczba = tablica[0];
    tablica[0] = pierwsza_liczba - 1;

    for (int i = 1; i < rozmiar - 1; i++) {
        tablica[i] = tablica[i + 1];
    }

    rozmiar -= 1;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Pierwszy element z tablicy zostal usuniety\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu i z plikiem tablica.txt
void usun_z_konca_tablicy() {
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int rozmiar;
    plik >> rozmiar;

    if (rozmiar == 0) {
        std::cout << "Tablica jest pusta.\n";
        return;
    }

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    rozmiar -= 1;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Ostatni element tablicy zostal usuniety.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu i z plikiem tablica.txt
void usun_z_losowo_z_tablicy() {
    std::ifstream plik("tablica.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int rozmiar;
    plik >> rozmiar;

    if (rozmiar == 0) {
        std::cout << "Tablica jest pusta.\n";
        return;
    }

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    // Znajdowanie losowego indeksu elementu do usuniecia
    int indeks = rand() % rozmiar;

    // Usuwanie elementu z losowego miejsca
    for (int i = indeks; i < rozmiar - 1; i++) {
        tablica[i] = tablica[i + 1];
    }

    rozmiar -= 1;

    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element z losowego miejsca tablicy zostal usuniety.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu i z plikiem tablica.txt

void usun_z_poczatku_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zmniejsz wartosc pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zaktualizowana wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    // Usuniecie pierwszego elementu z listy
    WpisListy* drugiWpis = glowa->nastepny;
    glowa->nastepny = drugiWpis->nastepny;
    delete drugiWpis;

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        // Zwolnienie pamieci
        while (glowa != nullptr) {
            WpisListy* temp = glowa;
            glowa = glowa->nastepny;
            delete temp;
        }
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();

    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Pierwszy element zostal usuniety z listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu i z plikiem lista.txt
void usun_z_konca_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;
    if (plik >> liczba) {
        // Zwieksz wartosc pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zwiekszona wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    if (glowa == nullptr) {
        std::cout << "Lista jest pusta.\n";
        return;
    }

    if (glowa->nastepny == nullptr) {
        std::cout << "Lista zawiera tylko jeden element.\n";
        delete glowa;
        return;
    }

    // Znalezienie przedostatniego elementu
    WpisListy* przedostatni = glowa;
    while (przedostatni->nastepny->nastepny != nullptr) {
        przedostatni = przedostatni->nastepny;
    }

    // Usuniecie ostatniego elementu
    delete przedostatni->nastepny;
    przedostatni->nastepny = nullptr;

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();


    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Ostatni element zostal usuniety z listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu i z plikiem lista.txt
void usun_losowo_z_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }
    auto czas_start = std::chrono::high_resolution_clock::now();
    int liczba;
    if (plik >> liczba) {
        // Zwieksz wartosc pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zwiekszona wartosc jako pierwszy element listy
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;
        glowa = nowyWpis;
        ogon = nowyWpis;
    }

    while (plik >> liczba) {
        WpisListy* nowyWpis = new WpisListy;
        nowyWpis->wartosc = liczba;
        nowyWpis->nastepny = nullptr;

        if (glowa == nullptr) {
            glowa = nowyWpis;
            ogon = nowyWpis;
        } else {
            ogon->nastepny = nowyWpis;
            ogon = nowyWpis;
        }
    }

    plik.close();

    if (glowa == nullptr) {
        std::cout << "Lista jest pusta.\n";
        return;
    }

    if (glowa->nastepny == nullptr) {
        std::cout << "Lista zawiera tylko jeden element.\n";
        delete glowa;
        return;
    }

    // Znajdowanie losowego indeksu elementu do usuniecia
    srand(time(nullptr));
    int indeks = rand() % (rozmiar - 1) + 1;

    // Znalezienie elementu przed elementem do usuniecia
    WpisListy* przedUsunieciem = glowa;
    for (int i = 0; i < indeks - 1; i++) {
        przedUsunieciem = przedUsunieciem->nastepny;
    }

    // Usuniecie elementu
    WpisListy* temp = przedUsunieciem->nastepny;
    przedUsunieciem->nastepny = temp->nastepny;
    delete temp;

    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();

    // Zwolnienie pamieci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Losowy element zostal usuniety z listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";


} // zrobione z liczeniem czasu i z plikiem lista.txt

void usun_z_tablicy(){
    int choice;

    while(true) {
        std::cout << "Ktory element chcesz usunac z tablicy?\n";
        std::cout << "1. Z poczatku\n";
        std::cout << "2. Z konca\n";
        std::cout << "3. Z losowego miejsca\n";
        std::cout << "4. Powrot\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano usuniecie z poczatku\n";
                usun_z_poczatku_tablicy();
                break;
            case 2:
                std::cout << "Wybrano usuniecie z konca\n";
                usun_z_konca_tablicy();
                break;
            case 3:
                std::cout << "Wybrano usuniecie z losowego miejsca\n";
                usun_z_losowo_z_tablicy();
                break;
            case 4:
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)
void usun_z_listy() {
    int choice;

    while(true) {
        std::cout << "Ktory element chcesz usunac z listy?\n";
        std::cout << "1. Z poczatku\n";
        std::cout << "2. Z konca\n";
        std::cout << "3. Z losowego miejsca\n";
        std::cout << "4. Powrot\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano usuniecie z poczatku\n";
                usun_z_poczatku_listy();
                break;
            case 2:
                std::cout << "Wybrano usuniecie z konca\n";
                usun_z_konca_listy();
                break;
            case 3:
                std::cout << "Wybrano usuniecie z losowego miejsca\n";
                usun_losowo_z_listy();
                break;
            case 4:
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)
void usun_z_drzewa_menu(){
    int choice;

    while(true) {
        std::cout << "Ktory element chcesz usunac z drzewa?\n";
        std::cout << "1. Z poczatku\n";
        std::cout << "2. Z konca\n";
        std::cout << "3. Z losowego miejsca\n";
        std::cout << "4. Powrot\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano usuniecie z poczatku\n";
                usun_z_poczatku_drzewa();
                break;
            case 2:
                std::cout << "Wybrano usuniecie z konca\n";
                usun_z_konca_drzewa();
                break;
            case 3:
                std::cout << "Wybrano usuniecie z losowego miejsca\n";
                usun_losowo_z_drzewa();
                break;
            case 4:
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)

void usun_element(){

    int choice;

    while (true) {
        std::cout << "==== MENU USUWANIA ELEMENTU ====\n";
        std::cout << "Skad chcesz usunac element?\n";
        std::cout << "1. Usun element z tablicy\n";
        std::cout << "2. Usun element z listy\n";
        std::cout << "3. Usun element z drzewa\n";
        std::cout << "4. Wroc do menu glownego\n";
        std::cout << "==================================\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano usuniecie elementu z tablicy\n";
                usun_z_tablicy();
                break;
            case 2:
                std::cout << "Wybrano usuniecie elementu z listy\n";
                usun_z_listy();
                break;
            case 3:
                std::cout << "Wybrano usuniecie elementu z drzewa\n";
                usun_z_drzewa_menu();
                break;
            case 4:
                std::cout << "Wybrano usuniecie z menu glownego\n";
                return;
        }
    }
} // zrobione (tu sie nie liczy czasu)

void szukanie_elementu(){
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int element, szukany_element;
    std::cout << "Wpisz element ktorego szukasz\n";
    std::cin >> szukany_element;

    bool czy_znaleziono = false;

    while (plik >> element) {
        if (element == szukany_element) {
            czy_znaleziono = true;
            break;
        }
    }

    plik.close();

    if (czy_znaleziono) {
        std::cout << "Element " << szukany_element << " znajduje sie w pliku\n";
    } else {
        std::cout << "Element " << szukany_element << " nie wystepuje w pliku\n";
    }
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
} // zrobione z liczeniem czasu
void usuniecie_pliku(){
    std::cout << "Czy na pewno chcesz zakonczyc usunac plik? (1 - Tak, 2 - Nie)\n";
    int wybor_usuniecie;
    std::cin >> wybor_usuniecie;
    if (wybor_usuniecie == 1) {
        std::cout << "Wybrano usuniecie. Plik zostanie usuniety\n";
        if (std::remove("liczby.txt") == 0) {
            std::cout << "Plik zostal usuniety\n";
        } else {
            std::cout << "Nie udalo sie usunac pliku\n";
        }
    }
    else if (wybor_usuniecie == 2){
        std::cout << "Anulowano usuniecie. Plik nie zostanie usuniety\n";
    }
    else {
        std::cout << "Niepoprawny wybor. Plik nie zostanie usuniety\n";
    }
} // // zrobione (tu sie nie liczy czasu)
void wyjscie_z_programu(){
    std::cout << "Czy na pewno chcesz zakonczyc program? (1 - Tak, 2 - Nie)\n";
    int wybor_wyjscie;
    std::cin >> wybor_wyjscie;
    if (wybor_wyjscie == 1) {
        std::cout << "Wybrano wyjscie. Program zostanie zakonczony\n";
        exit(0);
    }
    else if (wybor_wyjscie == 2){
        std::cout << "Anulowano wyjscie. Program nie zostanie zakonczony\n";
    }
    else {
        std::cout << "Niepoprawny wybor. Program nie zostanie zakonczony\n";
    }
} // zrobione (tu sie nie liczy czasu)
void menu() {
    int choice;

    while (true) {
        std::cout << "=========== MENU ===========\n";
        std::cout << "1. Wygeneruj plik z liczbami\n";
        std::cout << "2. Wyswietl plik z liczbami\n";
        std::cout << "3. Wstaw element\n";
        std::cout << "4. Usun element\n";
        std::cout << "5. Szukaj elementu w pliku liczby.txt\n";
        std::cout << "6. Usun plik z liczbami\n";
        std::cout << "7. Stworz tablice\n";
        std::cout << "8. Stworz liste\n";
        std::cout << "9. Stworz drzewo binarne\n";
        std::cout << "10. Zakoncz program\n";
        std::cout << "============================\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano generowanie pliku z liczbami\n";
                generowanie_pliku("liczby.txt");
                break;
            case 2:
                std::cout << "Wybrano wyswietlenie.\n";
                wyswietl_zawartosc_pliku("liczby.txt");
                break;
            case 3:
                std::cout << "Wybrano wstawianie elementu\n";
                wstaw_element();
                break;
            case 4:
                std::cout << "Wybrano usuwanie elementu\n";
                usun_element();
                break;
            case 5:
                std::cout << "Wybrano szukanie elementu\n";
                szukanie_elementu();
                break;
            case 6:
                std::cout << "Wybrano usuniecie pliku z liczbami\n";
                usuniecie_pliku();
                break;
            case 7:
                std::cout << "Wybrano stworzenie tablicy\n";
                utworz_tablice();
                break;
            case 8:
                std::cout << "Wybrano stworzenie listy\n";
                utworz_liste();
                break;
            case 9:
                std::cout << "Wybrano stworzenie drzewa binarnego\n";
                utworz_drzewo_binarne();
                break;
            case 10:
                std::cout << "Wybrano zakonczenie programu\n";
                wyjscie_z_programu();
                break;
        }

    }

} // zrobione (tu sie nie liczy czasu)

int main() {
    menu();
    return 0;
} // zrobione
