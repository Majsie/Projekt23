#ifndef UI_HPP
#define UI_HPP

// Funkcja wyswietlajaca menu i zwracajaca wybrany przez uzytkownika numer mapy
int displayMenu(const MapCollection& collection, Board& board) {
    int choice = 0;
    do {
        board.clear_screen();
        std::cout << "Wybierz mape:" << std::endl;
        for (size_t i = 0; i < collection.maps.size(); ++i) {
            std::cout << i + 1 << ". Mapa " << i + 1 << std::endl;
        }
        std::cout << collection.maps.size() + 1 << ". Wyjscie" << std::endl;
        std::cout << "Wybor: ";
        std::cin >> choice;

        // Sprawdzenie czy dane zostaly poprawnie wprowadzone
        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(collection.maps.size()) + 1) {
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl;
            _getch();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    } while (choice < 1 || choice > static_cast<int>(collection.maps.size()) + 1);
    return choice - 1;
}

#endif