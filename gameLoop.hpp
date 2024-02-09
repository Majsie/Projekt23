#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

void gameLoop()
{
    char direction;
    int mapChoice;

    // Pobranie maksymalnych rozmiarow planszy na podstawie map w kolekcji
    int maxWidth = collection.getMaxWidth();
    int maxHeight = collection.getMaxHeight();
    
    while (true) {
        // Utworzenie planszy o odpowiednich rozmiarach
        Board board(maxWidth, maxHeight);

        // Wybor mapy przez uzytkownika
        mapChoice = displayMenu(collection, board);

        // Sprawdzenie czy uzytkownik chce zakonczyc program
        if (mapChoice == collection.maps.size()) {
            break;
        }
        
        // Wczytanie wybranej mapy z kolekcji do planszy
        board.loadMapFromCollection(collection, mapChoice);
        std::cout << std::endl;

        while (true) {
            board.clear_screen();
            board.print();

            if (!board.hasBoxesLeft()) {
                std::cout << "Gratulacje! Ukonczyles poziom " << mapChoice + 1 << "!" << std::endl;
                _getch();
                break;
            }
            
            std::cout << "Podaj kierunek (w/a/s/d) lub Esc aby wrocic do menu gry: " << std::endl;
            direction = _getch();

            // Sprawdzenie czy nacisnieto klawisz Escape
            if (direction == 27) {
                break;
            }

            // Wykonanie ruchu gracza na podstawie kierunku
            movePlayer(direction, board, playerPosition);
            std::cout << std::endl;
        }
    }
}

#endif