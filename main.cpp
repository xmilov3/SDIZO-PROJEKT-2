#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>




int rozmiar;

void generowanie_pliku(const std::string& liczby) {
    std::ofstream plik("liczby.txt");
    int zakresMin, zakresMax;
    std::cout << "Podaj ilosc liczb\n";
    std::cin >> rozmiar;
    std::cout << "Podaj zakres minimalny\n";
    std::cin >> zakresMin;
    std::cout << "Podaj zakres maksymalny\n";
    std::cin >> zakresMax;




    // Inicjalizacja generatora liczb losowych na podstawie czasu
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    plik << rozmiar-1 << std::endl;

    for (int i = 0; i < rozmiar-1; i++) {
        int liczba = zakresMin + std::rand() % (zakresMax - zakresMin + 1);
        plik << liczba << std::endl;
        std::string nazwaPliku = "liczby.txt";
    }

    plik.close();
    std::cout << "Wygenerowano plik z liczbami: " << liczby << std::endl;

}

void wyswietl_zawartosc_pliku(const std::string& liczby){
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie można otworzyć pliku.\n";
        return;
    }

    std::string linia;
    while (std::getline(plik, linia)) {
        std::cout << linia << std::endl;
    }

    plik.close();
}
void wstaw_do_tablicy_na_poczatek(int element) {
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie można otworzyć pliku.\n";
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

    std::ofstream plik_wyjsciowy("liczby.txt");
    plik_wyjsciowy << rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        plik_wyjsciowy << nowa_tablica[i] << std::endl;
    }
    plik_wyjsciowy.close();

    delete[] tablica;
    delete[] nowa_tablica;

    auto czas_koniec = std::chrono::high_resolution_clock::now();
    auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

    std::cout << "Element został wstawiony pomyślnie do pliku liczby.txt.\n";
    std::cout << "Operacja trwała " << czas_trwania << " mikrosekund \n";
    return;
}
void wstaw_do_tablicy_na_koniec(int element){
        std::ifstream plik("liczby.txt");

        if (!plik.is_open()) {
            std::cout << "Nie można otworzyć pliku.\n";
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

        std::ofstream plik_wyjsciowy("liczby.txt");
        plik_wyjsciowy << rozmiar << std::endl;
        for (int i = 0; i < rozmiar; i++) {
            plik_wyjsciowy << nowa_tablica[i] << std::endl;
        }
        plik_wyjsciowy.close();

        delete[] tablica;
        delete[] nowa_tablica;

        auto czas_koniec = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

        std::cout << "Element został wstawiony pomyślnie na koniec pliku liczby.txt.\n";
    std::cout << "Operacja trwała " << czas_trwania << " mikrosekund \n";
        return;
    }
    void wstaw_do_tablicy_losowo(int element){
        std::ifstream plik("liczby.txt");

        if (!plik.is_open()) {
            std::cout << "Nie można otworzyć pliku.\n";
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

        std::ofstream plik_wyjsciowy("liczby.txt");
        plik_wyjsciowy << rozmiar << std::endl;
        for (int i = 0; i < rozmiar; i++) {
            plik_wyjsciowy << nowa_tablica[i] << std::endl;
        }
        plik_wyjsciowy.close();

        delete[] tablica;
        delete[] nowa_tablica;

        auto czas_koniec = std::chrono::high_resolution_clock::now();
        auto czas_trwania = std::chrono::duration_cast<std::chrono::microseconds>(czas_koniec - czas_start).count();

        std::cout << "Element został wstawiony pomyślnie w losowe miejsce w pliku liczby.txt.\n";
        std::cout << "Operacja trwała " << czas_trwania << " mikrosekund \n";
        return;
}

void wstaw_do_tablicy(){
    int element;
    int choice;
    std::cout<<"Wpisz element jaki chcesz dodać do tablicy\n";
    std::cin>>element;

    while(true) {
        std::cout << "Gdzie chcesz dodać element?\n";
        std::cout << "1. Na początek\n";
        std::cout << "2. Na koniec\n";
        std::cout << "3. W losowe miejsce\n";
        std::cout << "4. Powrót\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano na początek\n";
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
    std::ifstream plik("liczby.txt");

    if (!plik.is_open()) {
        std::cout << "Nie można otworzyć pliku.\n";
        return;
    }

}
void wstaw_do_drzewa(){

}
void wstaw_element() {

    int choice;

    while (true) {
        std::cout << "==== MENU WSTAWIANIA ELEMENTU ====\n";
        std::cout << "Gdzie chcesz wstawić element?\n";
        std::cout << "1. Wstaw element do tablicy\n";
        std::cout << "2. Wstaw element do listy\n";
        std::cout << "3. Wstaw element do drzewa\n";
        std::cout << "4. Wróć do menu głównego\n";
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
                wstaw_do_drzewa();
                break;
            case 4:
                std::cout << "Powrót do menu głównego";
                return;
        }
    }
}

void usun_element(){

}
void szukanie_elementu(){

}
void usuniecie_pliku(){
    std::cout << "Czy na pewno chcesz zakończyć usunąć plik? (1 - Tak, 2 - Nie)\n";
    int wybor_usuniecie;
    std::cin >> wybor_usuniecie;
    if (wybor_usuniecie == 1) {
        std::cout << "Wybrano usunięcie. Plik zostanie usunięty\n";
        if (std::remove("liczby.txt") == 0) {
            std::cout << "Plik został usunięty\n";
        } else {
            std::cout << "Nie udało się usunąć pliku\n";
        }
    }
    else if (wybor_usuniecie == 2){
        std::cout << "Anulowano usunięcie. Plik nie zostanie usunięty\n";
    }
    else {
        std::cout << "Niepoprawny wybór. Plik nie zostanie usunięty\n";
    }
}
void wyjscie_z_programu(){
    std::cout << "Czy na pewno chcesz zakończyć program? (1 - Tak, 2 - Nie)\n";
    int wybor_wyjscie;
    std::cin >> wybor_wyjscie;
    if (wybor_wyjscie == 1) {
        std::cout << "Wybrano wyjście. Program zostanie zakończony\n";
        exit(0);
    }
    else if (wybor_wyjscie == 2){
        std::cout << "Anulowano wyjście. Program nie zostanie zakończony\n";
    }
    else {
        std::cout << "Niepoprawny wybór. Program nie zostanie zakończony\n";
    }
}
void menu() {
    int choice;

    while (true) {
        std::cout << "=========== MENU ===========\n";
        std::cout << "1. Wygeneruj plik z liczbami\n";
        std::cout << "2. Wyświetl\n";
        std::cout << "3. Wstaw element\n";
        std::cout << "4. Usuń element\n";
        std::cout << "5. Szukaj elementu\n";
        std::cout << "6. Usuń plik z liczbami\n";
        std::cout << "7. Zakończ program\n";
        std::cout << "============================\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Wybrano generowanie pliku z liczbami\n";
                generowanie_pliku("liczby.txt");
                break;
            case 2:
                std::cout << "Wybrano wyświetlenie.\n";
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
                std::cout<< "Wybrano usunięcie pliku z liczbami\n";
                usuniecie_pliku();
                break;
            case 7:
                std::cout<< "Wybrano zakończenie programu\n";
                wyjscie_z_programu();
                break;
        }

    }

}

int main() {
    menu();
    return 0;
}
