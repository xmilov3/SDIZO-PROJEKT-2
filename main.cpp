#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio> // Do usuwania pliku





void generowanie_pliku(const std::string& liczby) {
    std::ofstream plik("liczby.txt");
    int iloscLiczb, zakresMin, zakresMax;
    std::cout << "Podaj ilosc liczb\n";
    std::cin >> iloscLiczb;
    std::cout << "Podaj zakres minimalny\n";
    std::cin >> zakresMin;
    std::cout << "Podaj zakres maksymalny\n";
    std::cin >> zakresMax;


    // Inicjalizacja generatora liczb losowych na podstawie czasu
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    plik << iloscLiczb << std::endl;

    for (int i = 0; i < iloscLiczb; i++) {
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

void wstaw_do_tablicy(){

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
                break;
            case 3:
                std::cout << "Wybrano wstawianie elementu do drzewa\n";
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
