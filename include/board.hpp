#ifndef BOARD_HPP
#define BOARD_HPP

const char EMPTY = ' ';
const char WALL = '#';
const char BOX = '$';
const char TARGET = '.';
const char PLAYER = '@';
const char PLAYER_ON_TARGET = '+';
const char BOX_ON_TARGET = '*';
static Position playerPosition;
static MapCollection collection;

// Klasa reprezentujaca plansze
class Board {
private:
    std::vector<std::vector<char>> grid;
    int width;
    int height;

public:
    Board(int w, int h) : width(w), height(h) {
        // Inicjalizacja planszy jako pusta
        grid.resize(height, std::vector<char>(width, EMPTY));
    }

    ~Board() {grid.clear();}

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    // Metoda do ustawiania zawartosci planszy na danej pozycji
    void setCell(int x, int y, char value) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = value;
        }
    }

    // Metoda do pobierania zawartosci planszy z danej pozycji
    char getCell(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return grid[y][x];
        }
        return ' ';
    }

    // Metoda do sprawdzania czy pozycja jest sciana
    bool isWall(int x, int y) const {
        return getCell(x, y) == WALL;
    }

    // Metoda do sprawdzania czy pozycja jest celem
    bool isTarget(int x, int y) const {
        return getCell(x, y) == TARGET || getCell(x, y) == PLAYER_ON_TARGET || getCell(x, y) == BOX_ON_TARGET;
    }

    // Metoda do wczytywania mapy
    void loadMap(const std::vector<std::vector<char>>& map) {
        int newWidth = map[0].size();
        int newHeight = map.size();

        // Dostosowanie rozmiaru planszy do rozmiaru wczytywanej mapy
        if (newWidth > width || newHeight > height) {
            width = (((width) > (newWidth)) ? (width) : (newWidth));
            height = (((height) > (newHeight)) ? (height) : (newHeight));
            grid.resize(height, std::vector<char>(width, EMPTY));
        }

        // Wczytanie mapy do planszy
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                if (map[y][x] == PLAYER || map[y][x] == PLAYER_ON_TARGET) {
                    playerPosition = {x, y};
                }
                setCell(x, y, map[y][x]);
            }
        }
    }

    // Metoda do wczytywania mapy z kolekcji
    void loadMapFromCollection(const MapCollection& collection, int index) {
        if (index >= 0 && index < collection.maps.size()) {
            loadMap(collection.maps[index]);
        }
    }

    // Metoda do wypisywania planszy
    void print() const {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << getCell(x, y);
            }
            std::cout << std::endl;
        }
    }

    bool hasBoxesLeft() const {
        for (int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                if (getCell(x, y) == BOX)
                return 1;
            }
        }
        return 0;
    }

    void clear_screen(char fill = ' ') { 
        COORD tl = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
    }
};

#endif