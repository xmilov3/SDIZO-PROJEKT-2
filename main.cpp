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
    // Otwarcie pliku "liczby.txt" do zapisu
    std::ofstream plik("liczby.txt");

    // Zmienne przechowujące dane wprowadzone przez użytkownika
    int zakresMin, zakresMax;

    // Wczytanie danych od użytkownika
    std::cout << "Podaj ilosc liczb:\n";
    std::cin >> rozmiar;
    std::cout << "Podaj zakres minimalny:\n";
    std::cin >> zakresMin;
    std::cout << "Podaj zakres maksymalny:\n";
    std::cin >> zakresMax;

    // Sprawdzenie poprawności zakresu
    if (zakresMin > zakresMax) {
        std::cout << "Zakres minimalny nie moze byc wiekszy od zakresu maksymalnego.\n";
        return;
    }

    // Sprawdzenie możliwości wygenerowania unikalnych liczb
    if (rozmiar > (zakresMax - zakresMin + 1)) {
        std::cout << "Nie mozna wygenerowac " << rozmiar << " unikalnych liczb w podanym zakresie.\n";
        return;
    }

    // Wektor przechowujący wygenerowane liczby
    std::vector<int> wygenerowaneLiczby;

    // Inicjalizacja generatora liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());

    // Dystrybucja liczb losowych w podanym zakresie
    std::uniform_int_distribution<int> distrib(zakresMin, zakresMax);

    // Zbiór przechowujący unikalne liczby
    std::set<int> unikalneLiczby;

    // Generowanie unikalnych liczb w ilości rozmiar
    while (unikalneLiczby.size() < rozmiar) {
        int liczba = distrib(gen);
        unikalneLiczby.insert(liczba);
    }

    // Kopiowanie unikalnych liczb do wektora
    std::copy(unikalneLiczby.begin(), unikalneLiczby.end(), std::back_inserter(wygenerowaneLiczby));

    // Przetasowanie kolejności liczb w wektorze
    std::shuffle(wygenerowaneLiczby.begin(), wygenerowaneLiczby.end(), gen);

    // Zapisanie rozmiaru do pliku
    plik << rozmiar << std::endl;

    // Zapisanie wygenerowanych liczb do pliku
    for (int liczba : wygenerowaneLiczby) {
        plik << liczba << std::endl;
    }

    // Zamknięcie pliku
    plik.close();

    // Wyświetlenie komunikatu o wygenerowaniu pliku
    std::cout << "Wygenerowano plik z unikalnymi liczbami: " << liczby << std::endl;
}

void wyswietl_zawartosc_pliku() {
    // Otwarcie pliku "liczby.txt" do odczytu
    std::ifstream plik("liczby.txt");

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zmienna przechowująca aktualnie wczytaną linię z pliku
    std::string linia;

    // Odczyt linii z pliku i wyświetlanie na ekranie
    while (std::getline(plik, linia)) {
        std::cout << linia << std::endl;
    }

    // Zamknięcie pliku
    plik.close();
}

void wstaw_do_tablicy_na_poczatek(int element) {
    // Otwarcie pliku "tablica.txt" do odczytu
    std::ifstream plik("tablica.txt");

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zmienna przechowująca czas rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    // Odczyt rozmiaru tablicy z pliku
    plik >> rozmiar;

    // Tworzenie dynamicznej tablicy i odczytanie danych z pliku do tablicy
    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    // Tworzenie nowej dynamicznej tablicy o rozmiarze większym o 1 od pierwotnej
    int* nowa_tablica = new int[rozmiar + 1];

    // Przeniesienie danych z pierwotnej tablicy do nowej tablicy, z przesunięciem o 1 indeks w prawo
    for (int i = 0; i < rozmiar; i++) {
        nowa_tablica[i + 1] = tablica[i];
    }

    // Wstawienie nowego elementu na początek nowej tablicy
    nowa_tablica[0] = element;

    // Zwiększenie rozmiaru tablicy
    rozmiar++;

    // Otwarcie pliku "tablica.txt" do zapisu
    std::ofstream plik_wyjsciowy("tablica.txt");

    // Zapis nowego rozmiaru do pliku
    plik_wyjsciowy << rozmiar << std::endl;

    // Zapis zawartości nowej tablicy do pliku
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zajmowanej przez tablice
    delete[] tablica;
    delete[] nowa_tablica;

    // Obliczenie czasu trwania operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o sukcesie operacji i czasie trwania
    std::cout << "Element zostal wstawiony na poczatek tablicy.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void wstaw_do_tablicy_na_koniec(int element) {
    // Otwarcie pliku "tablica.txt" do odczytu
    std::ifstream plik("tablica.txt");

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zmienna przechowująca czas rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    // Odczyt rozmiaru tablicy z pliku
    plik >> rozmiar;

    // Tworzenie dynamicznej tablicy i odczytanie danych z pliku do tablicy
    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    // Tworzenie nowej dynamicznej tablicy o rozmiarze większym o 1 od pierwotnej
    int* nowa_tablica = new int[rozmiar + 1];

    // Przeniesienie danych z pierwotnej tablicy do nowej tablicy
    for (int i = 0; i < rozmiar; i++) {
        nowa_tablica[i] = tablica[i];
    }

    // Wstawienie nowego elementu na koniec nowej tablicy
    nowa_tablica[rozmiar] = element;

    // Zwiększenie rozmiaru tablicy
    rozmiar++;

    // Otwarcie pliku "tablica.txt" do zapisu
    std::ofstream plik_wyjsciowy("tablica.txt");

    // Zapis nowego rozmiaru do pliku
    plik_wyjsciowy << rozmiar << std::endl;

    // Zapis zawartości nowej tablicy do pliku
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zajmowanej przez tablice
    delete[] tablica;
    delete[] nowa_tablica;

    // Obliczenie czasu trwania operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o sukcesie operacji i czasie trwania
    std::cout << "Element zostal wstawiony pomyslnie na koniec.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void wstaw_do_tablicy_losowo(int element) {
    // Otwarcie pliku "tablica.txt" do odczytu
    std::ifstream plik("tablica.txt");

    // Sprawdzenie, czy plik został poprawnie otwarty
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zmienna przechowująca czas rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    // Odczyt rozmiaru tablicy z pliku
    plik >> rozmiar;

    // Tworzenie dynamicznej tablicy i odczytanie danych z pliku do tablicy
    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    // Wygenerowanie losowego indeksu w zakresie od 0 do rozmiar+1
    int indeks = rand() % (rozmiar + 1);

    // Tworzenie nowej dynamicznej tablicy o rozmiarze większym o 1 od pierwotnej
    int* nowa_tablica = new int[rozmiar + 1];

    // Przeniesienie danych z pierwotnej tablicy do nowej tablicy do indeksu
    for (int i = 0; i < indeks; i++) {
        nowa_tablica[i] = tablica[i];
    }

    // Wstawienie nowego elementu na wylosowanym indeksie w nowej tablicy
    nowa_tablica[indeks] = element;

    // Przeniesienie pozostałych danych z pierwotnej tablicy do nowej tablicy
    for (int i = indeks + 1; i < rozmiar + 1; i++) {
        nowa_tablica[i] = tablica[i - 1];
    }

    // Zwiększenie rozmiaru tablicy
    rozmiar++;

    // Otwarcie pliku "tablica.txt" do zapisu
    std::ofstream plik_wyjsciowy("tablica.txt");

    // Zapis nowego rozmiaru do pliku
    plik_wyjsciowy << rozmiar << std::endl;

    // Zapis zawartości nowej tablicy do pliku
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zajmowanej przez tablice
    delete[] tablica;
    delete[] nowa_tablica;

    // Obliczenie czasu trwania operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o sukcesie operacji i czasie trwania
    std::cout << "Element zostal wstawiony pomyslnie w losowe miejsce w pliku tablica.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";

}

struct WpisListy {
    // Pole przechowujące wartość elementu listy (typ: int)
    int wartosc;
    // Wskaźnik na następny element listy (typ: WpisListy*)
    WpisListy* nastepny;
};

void wstaw_do_listy_na_poczatek(int element) {
    WpisListy* glowa = nullptr;  // Inicjalizacja wskaźnika na głowę listy jako nullptr (pusta lista)
    WpisListy* ogon = nullptr;   // Inicjalizacja wskaźnika na ogon listy jako nullptr (pusta lista)

    std::ifstream plik("lista.txt");  // Otwarcie pliku "lista.txt" w trybie odczytu
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwiększ wartość pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiększoną wartość jako pierwszy element listy
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

    plik.close();  // Zamknięcie pliku

    // Tworzenie nowego elementu na początku listy
    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = element;
    nowyWpis->nastepny = glowa->nastepny;
    glowa->nastepny = nowyWpis;

    std::ofstream plikWyjsciowy("lista.txt");  // Otwarcie pliku "lista.txt" w trybie zapisu
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;  // Zapisywanie wartości elementów do pliku
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();  // Zamknięcie pliku

    // Zwolnienie pamięci zaalokowanej dla elementów listy
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na poczatek listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void wstaw_do_listy_na_koniec(int element) {
    WpisListy* glowa = nullptr;  // Inicjalizacja wskaźnika na głowę listy jako nullptr (pusta lista)
    WpisListy* ogon = nullptr;   // Inicjalizacja wskaźnika na ogon listy jako nullptr (pusta lista)

    std::ifstream plik("lista.txt");  // Otwarcie pliku "lista.txt" w trybie odczytu
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwiększ wartość pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiększoną wartość jako pierwszy element listy
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

    plik.close();  // Zamknięcie pliku

    // Tworzenie nowego elementu na końcu listy
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

    std::ofstream plikWyjsciowy("lista.txt");  // Otwarcie pliku "lista.txt" w trybie zapisu
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;  // Zapisywanie wartości elementów do pliku
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();  // Zamknięcie pliku

    // Zwolnienie pamięci zaalokowanej dla elementów listy
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na koniec listy w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void wstaw_do_listy_losowo(int element) {
    WpisListy* glowa = nullptr;  // Inicjalizacja wskaźnika na głowę listy jako nullptr (pusta lista)
    WpisListy* ogon = nullptr;   // Inicjalizacja wskaźnika na ogon listy jako nullptr (pusta lista)

    std::ifstream plik("lista.txt");  // Otwarcie pliku "lista.txt" w trybie odczytu
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zwiększ wartość pierwszej liczby o 1
        liczba += 1;

        // Dodaj zwiększoną wartość jako pierwszy element listy
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

    plik.close();  // Zamknięcie pliku

    // Znajdowanie losowego indeksu do wstawienia elementu
    int iloscElementow = 0;
    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        iloscElementow++;
        obecny = obecny->nastepny;
    }

    int indeks = rand() % (iloscElementow + 1);

    // Dodawanie elementu na losowe miejsce w liście
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

    std::ofstream plikWyjsciowy("lista.txt");  // Otwarcie pliku "lista.txt" w trybie zapisu
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;  // Zapis wartości elementów do pliku
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();  // Zamknięcie pliku

    // Zwolnienie pamięci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element zostal dodany na losowe miejsce w liscie w pliku lista.txt.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}

struct Wezel {
    int wartosc;        // Wartość przechowywana w węźle
    Wezel* lewy;        // Wskaźnik na lewego potomka
    Wezel* prawy;       // Wskaźnik na prawego potomka

    Wezel(int val) : wartosc(val), lewy(nullptr), prawy(nullptr) {}
}; // skomentowany

Wezel* wstaw(Wezel* korzen, int wartosc) {
    // Sprawdzenie, czy drzewo jest puste (czy korzeń jest pusty)
    if (korzen == nullptr) {
        // Jeśli tak, utwórz nowy węzeł i zwróć go jako korzeń drzewa
        return new Wezel(wartosc);
    }

    // Sprawdzenie, czy wartość do wstawienia jest mniejsza od wartości w korzeniu
    if (wartosc < korzen->wartosc) {
        // Jeśli tak, rekurencyjnie wywołaj funkcję wstawiając nową wartość do lewego poddrzewa
        korzen->lewy = wstaw(korzen->lewy, wartosc);
    } else {
        // Jeśli wartość jest większa lub równa, rekurencyjnie wywołaj funkcję wstawiając nową wartość do prawego poddrzewa
        korzen->prawy = wstaw(korzen->prawy, wartosc);
    }

    // Zwróć wskaźnik na korzeń drzewa
    return korzen;
}

void zapisz_drzewo_do_pliku(Wezel* korzen, std::ofstream& plik) {
    // Sprawdzenie, czy korzeń jest pusty (czy drzewo jest puste)
    if (korzen == nullptr) {
        // Jeśli tak, zakończ funkcję
        return;
    }

    // Rekurencyjnie zapisz lewe poddrzewo do pliku
    zapisz_drzewo_do_pliku(korzen->lewy, plik);

    // Zapisz wartość korzenia do pliku
    plik << korzen->wartosc << std::endl;

    // Rekurencyjnie zapisz prawe poddrzewo do pliku
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
}
void dodaj_do_pliku_lista(WpisListy*& glowa, int wartosc) {
    // Tworzenie nowego wpisu listy
    WpisListy* nowyWpis = new WpisListy;
    nowyWpis->wartosc = wartosc;
    nowyWpis->nastepny = nullptr;

    // Sprawdzenie, czy lista jest pusta
    if (glowa == nullptr) {
        // Jeśli lista jest pusta, nowy wpis staje się głową listy
        glowa = nowyWpis;
    } else {
        // Jeśli lista nie jest pusta, należy znaleźć ostatni element
        WpisListy* aktualny = glowa;
        while (aktualny->nastepny != nullptr) {
            aktualny = aktualny->nastepny;
        }
        // Po znalezieniu ostatniego elementu, nowy wpis zostaje dodany na koniec listy
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
}

void utworz_drzewo_binarne() {
    // Otwarcie pliku wejściowego
    std::ifstream plikWejsciowy("liczby.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku." << std::endl;
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr; // Inicjalizacja korzenia drzewa jako nullptr
    int liczba;
    std::string linia;

    // Odczyt linii po linii z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> liczba) {
            korzen = wstaw(korzen, liczba); // Wstawienie liczby do drzewa przy użyciu funkcji wstaw()
        }
    }

    // Zamknięcie pliku wejściowego
    plikWejsciowy.close();

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas tworzenia pliku z drzewem." << std::endl;
        return;
    }

    // Zapis drzewa do pliku wyjściowego przy użyciu funkcji zapisz_drzewo_do_pliku()
    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    // Zamknięcie pliku wyjściowego
    plikWyjsciowy.close();

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Drzewo binarne zostalo utworzone i zapisane do pliku: drzewo.txt" << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void wstaw_do_drzewa(const std::string& liczby, int liczba) {
    // Otwarcie pliku z drzewem do odczytu
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr; // Inicjalizacja korzenia drzewa jako nullptr
    int wartosc;
    std::string linia;

    // Odczyt linii po linii z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc); // Wstawienie wartości do drzewa przy użyciu funkcji wstaw()
        }
    }

    // Zamknięcie pliku wejściowego
    plikWejsciowy.close();

    // Wstawienie nowej liczby do drzewa
    korzen = wstaw(korzen, liczba);

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    // Zapis drzewa do pliku wyjściowego przy użyciu funkcji zapisz_drzewo_do_pliku()
    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    // Zamknięcie pliku wyjściowego
    plikWyjsciowy.close();

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Liczba " << liczba << " zostala dodana do drzewa." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void usun_z_poczatku_drzewa() {
    // Otwarcie pliku z drzewem do odczytu
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr; // Inicjalizacja korzenia drzewa jako nullptr
    int wartosc;
    std::string linia;

    // Wczytanie drzewa z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc); // Wstawienie wartości do drzewa przy użyciu funkcji wstaw()
        }
    }

    // Zamknięcie pliku wejściowego
    plikWejsciowy.close();

    // Usunięcie pierwszego elementu z drzewa
    if (korzen != nullptr) {
        Wezel* temp = korzen;
        korzen = korzen->prawy;
        delete temp;
    }

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    // Zapis zmodyfikowanego drzewa do pliku wyjściowego przy użyciu funkcji zapisz_drzewo_do_pliku()
    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    // Zamknięcie pliku wyjściowego
    plikWyjsciowy.close();

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Pierwszy element z drzewa zostal usuniety." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
void usun_z_konca_drzewa() {
    // Otwarcie pliku z drzewem do odczytu
    std::ifstream plikWejsciowy("drzewo.txt");
    if (!plikWejsciowy) {
        std::cout << "Blad podczas otwierania pliku z drzewem." << std::endl;
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    Wezel* korzen = nullptr; // Inicjalizacja korzenia drzewa jako nullptr
    int wartosc;
    std::string linia;

    // Wczytanie drzewa z pliku
    while (std::getline(plikWejsciowy, linia)) {
        std::istringstream iss(linia);
        if (iss >> wartosc) {
            korzen = wstaw(korzen, wartosc); // Wstawienie wartości do drzewa przy użyciu funkcji wstaw()
        }
    }

    // Zamknięcie pliku wejściowego
    plikWejsciowy.close();

    // Usunięcie ostatniego elementu z drzewa
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

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("drzewo.txt");
    if (!plikWyjsciowy) {
        std::cout << "Blad podczas zapisu drzewa do pliku." << std::endl;
        return;
    }

    // Zapis zmodyfikowanego drzewa do pliku wyjściowego przy użyciu funkcji zapisz_drzewo_do_pliku()
    zapisz_drzewo_do_pliku(korzen, plikWyjsciowy);

    // Zamknięcie pliku wyjściowego
    plikWyjsciowy.close();

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Ostatni element z drzewa zostal usuniety." << std::endl;
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund \n";
}
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
}


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

}
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
}
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
}
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
}


void usun_z_poczatku_tablicy() {
    // Otwarcie pliku z tablicą do odczytu
    std::ifstream plik("tablica.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    int rozmiar;
    plik >> rozmiar;

    int* tablica = new int[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        plik >> tablica[i];
    }
    plik.close();

    // Zmiana wartości pierwszego elementu
    int pierwsza_liczba = tablica[0];
    tablica[0] = pierwsza_liczba - 1;

    // Przesunięcie pozostałych elementów w tablicy
    for (int i = 1; i < rozmiar - 1; i++) {
        tablica[i] = tablica[i + 1];
    }

    rozmiar -= 1;

    // Otwarcie pliku wyjściowego
    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zaalokowanej dla tablicy
    delete[] tablica;

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Pierwszy element z tablicy zostal usuniety\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}
void usun_z_konca_tablicy() {
    // Otwarcie pliku z tablicą do odczytu
    std::ifstream plik("tablica.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
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

    // Otwarcie pliku wyjściowego
    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zaalokowanej dla tablicy
    delete[] tablica;

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Ostatni element tablicy zostal usuniety.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}
void usun_z_losowo_z_tablicy() {
    // Otwarcie pliku z tablicą do odczytu
    std::ifstream plik("tablica.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
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

    // Znajdowanie losowego indeksu elementu do usunięcia
    int indeks = rand() % rozmiar;

    // Usuwanie elementu z losowego miejsca
    for (int i = indeks; i < rozmiar - 1; i++) {
        tablica[i] = tablica[i + 1];
    }

    rozmiar -= 1;

    // Otwarcie pliku wyjściowego
    std::ofstream plik_wyjsciowy("tablica.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    // Zwolnienie pamięci zaalokowanej dla tablicy
    delete[] tablica;

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Element z losowego miejsca tablicy zostal usuniety.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}

void usun_z_poczatku_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    // Otwarcie pliku z listą do odczytu
    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;

    if (plik >> liczba) {
        // Zmniejsz wartość pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zaktualizowaną wartość jako pierwszy element listy
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

    // Usunięcie pierwszego elementu z listy
    WpisListy* drugiWpis = glowa->nastepny;
    glowa->nastepny = drugiWpis->nastepny;
    delete drugiWpis;

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";

        // Zwolnienie pamięci
        while (glowa != nullptr) {
            WpisListy* temp = glowa;
            glowa = glowa->nastepny;
            delete temp;
        }
        return;
    }

    // Zapisanie listy do pliku
    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();

    // Zwolnienie pamięci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    // Wyświetlenie informacji o zakończonej operacji
    std::cout << "Pierwszy element zostal usuniety z listy.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}
void usun_z_konca_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    // Otwarcie pliku z listą do odczytu
    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;
    if (plik >> liczba) {
        // Zwiększ wartość pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zwiększoną wartość jako pierwszy element listy
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

    // Sprawdzenie czy lista jest pusta
    if (glowa == nullptr) {
        std::cout << "Lista jest pusta.\n";
        return;
    }

    // Sprawdzenie czy lista zawiera tylko jeden element
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

    // Usunięcie ostatniego elementu
    delete przedostatni->nastepny;
    przedostatni->nastepny = nullptr;

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zapisanie listy do pliku
    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();

    // Zwolnienie pamięci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Ostatni element zostal usuniety z listy.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}
void usun_losowo_z_listy() {
    WpisListy* glowa = nullptr;
    WpisListy* ogon = nullptr;

    // Otwarcie pliku z listą do odczytu
    std::ifstream plik("lista.txt");
    if (!plik.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Pomiar czasu rozpoczęcia operacji
    auto czas_start = std::chrono::high_resolution_clock::now();

    int liczba;
    if (plik >> liczba) {
        // Zwiększ wartość pierwszej liczby o 1
        liczba -= 1;

        // Dodaj zwiększoną wartość jako pierwszy element listy
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

    // Sprawdzenie czy lista jest pusta
    if (glowa == nullptr) {
        std::cout << "Lista jest pusta.\n";
        return;
    }

    // Sprawdzenie czy lista zawiera tylko jeden element
    if (glowa->nastepny == nullptr) {
        std::cout << "Lista zawiera tylko jeden element.\n";
        delete glowa;
        return;
    }

    // Obliczenie rozmiaru listy
    WpisListy* obecny = glowa;
    while (obecny != nullptr) {
        rozmiar++;
        obecny = obecny->nastepny;
    }

    // Znalezienie losowego indeksu elementu do usunięcia
    srand(time(nullptr));
    int indeks = rand() % (rozmiar - 1) + 1;

    // Znalezienie elementu przed elementem do usunięcia
    WpisListy* przedUsunieciem = glowa;
    for (int i = 0; i < indeks - 1; i++) {
        przedUsunieciem = przedUsunieciem->nastepny;
    }

    // Usunięcie elementu
    WpisListy* temp = przedUsunieciem->nastepny;
    przedUsunieciem->nastepny = temp->nastepny;
    delete temp;

    // Otwarcie pliku wyjściowego
    std::ofstream plikWyjsciowy("lista.txt");
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Nie mozna otworzyc pliku.\n";
        return;
    }

    // Zapisanie listy do pliku
    obecny = glowa;
    while (obecny != nullptr) {
        plikWyjsciowy << obecny->wartosc << std::endl;
        obecny = obecny->nastepny;
    }

    plikWyjsciowy.close();

    // Zwolnienie pamięci
    while (glowa != nullptr) {
        WpisListy* temp = glowa;
        glowa = glowa->nastepny;
        delete temp;
    }

    // Pomiar czasu zakończenia operacji
    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Losowy element zostal usuniety z listy.\n";
    std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
}



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
}
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
}
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
}

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
}

void szukaj_w_tablicy(){
    {
        std::ifstream plik("tablica.txt");

        // Sprawdzenie czy plik można otworzyć
        if (!plik.is_open()) {
            std::cout << "Nie mozna otworzyc pliku.\n";
            return;
        }


        int element, szukany_element;
        std::cout << "Wpisz element, ktorego szukasz: \n";
        std::cin >> szukany_element;

        // Pomiar czasu rozpoczęcia operacji
        auto czas_start = std::chrono::high_resolution_clock::now();

        bool czy_znaleziono = false;

        while (plik >> element) {
            if (element == szukany_element) {
                czy_znaleziono = true;
                break;
            }
        }

        plik.close();

        if (czy_znaleziono) {
            std::cout << "Element " << szukany_element << " znajduje sie w tablicy.\n";
        } else {
            std::cout << "Element " << szukany_element << " nie wystepuje w tablicy.\n";
        }

        // Pomiar czasu zakończenia operacji
        auto czas_koniec = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();
        std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
    }
}
void szukaj_w_liscie(){
    {
        std::ifstream plik("lista.txt");

        // Sprawdzenie czy plik można otworzyć
        if (!plik.is_open()) {
            std::cout << "Nie mozna otworzyc pliku.\n";
            return;
        }


        int element, szukany_element;
        std::cout << "Wpisz element, ktorego szukasz: \n";
        std::cin >> szukany_element;

        // Pomiar czasu rozpoczęcia operacji
        auto czas_start = std::chrono::high_resolution_clock::now();

        bool czy_znaleziono = false;

        while (plik >> element) {
            if (element == szukany_element) {
                czy_znaleziono = true;
                break;
            }
        }

        plik.close();

        if (czy_znaleziono) {
            std::cout << "Element " << szukany_element << " znajduje sie w liscie.\n";
        } else {
            std::cout << "Element " << szukany_element << " nie wystepuje w liscie.\n";
        }

        // Pomiar czasu zakończenia operacji
        auto czas_koniec = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();
        std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
    }
}
void szukaj_w_drzewie(){
    {
        std::ifstream plik("drzewo.txt");

        // Sprawdzenie czy plik można otworzyć
        if (!plik.is_open()) {
            std::cout << "Nie mozna otworzyc pliku.\n";
            return;
        }


        int element, szukany_element;
        std::cout << "Wpisz element, ktorego szukasz: \n";
        std::cin >> szukany_element;

        // Pomiar czasu rozpoczęcia operacji
        auto czas_start = std::chrono::high_resolution_clock::now();

        bool czy_znaleziono = false;

        while (plik >> element) {
            if (element == szukany_element) {
                czy_znaleziono = true;
                break;
            }
        }

        plik.close();

        if (czy_znaleziono) {
            std::cout << "Element " << szukany_element << " znajduje sie w drzewie.\n";
        } else {
            std::cout << "Element " << szukany_element << " nie wystepuje w drzewie.\n";
        }

        // Pomiar czasu zakończenia operacji
        auto czas_koniec = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();
        std::cout << "Operacja trwala " << czas_trwania << " mikrosekund.\n";
    }
}
void szukanie_elementu(){

    int choice;

    while (true) {
        std::cout << "==== MENU SZUKANIA ELEMENTU ====\n";
        std::cout << "W jakiej strukturze chcesz szukac elementu?\n";
        std::cout << "1. Szukaj elementu w tablicy\n";
        std::cout << "2. Szukaj elementu w liscie\n";
        std::cout << "3. Szukaj elementu w drzewie\n";
        std::cout << "4. Wroc do menu glownego\n";
        std::cout << "==================================\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano szukanie elementu w tablicy\n";
                szukaj_w_tablicy();
                break;
            case 2:
                std::cout << "Wybrano szukanie elementu w liscie\n";
                szukaj_w_liscie();
                break;
            case 3:
                std::cout << "Wybrano szukanie elementu w drzewie\n";
                szukaj_w_drzewie();
                break;
            case 4:
                std::cout << "Wybrano usuniecie z menu glownego\n";
                return;
        }
    }
}


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
}
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
}
void menu() {
    int choice;

    while (true) {
        std::cout << "=========== MENU ===========\n";
        std::cout << "1. Wygeneruj plik z liczbami\n";
        std::cout << "2. Wyswietl plik z liczbami\n";
        std::cout << "3. Wstaw element\n";
        std::cout << "4. Usun element\n";
        std::cout << "5. Szukaj elementu\n";
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
                wyswietl_zawartosc_pliku();
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

}

int main() {
    menu();
    return 0;
}
