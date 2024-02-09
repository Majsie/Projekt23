#ifndef MAP_HPP
#define MAP_HPP

// Struktura reprezentujaca pozycje na planszy
struct Position {
    int x;
    int y;
};

// Struktura przechowujaca mapy
struct MapCollection {
    std::vector<std::vector<std::vector<char>>> maps;

    // Inicjalizacja map
    MapCollection() {
        loadMapsFromFile("map1.txt");
        loadMapsFromFile("map2.txt");
        loadMapsFromFile("map3.txt");
        loadMapsFromFile("map4.txt");
        loadMapsFromFile("map5.txt");
    }

    // Zwolnienie zasobow
    ~MapCollection() {
        for (auto& map : maps) {
            for (auto& row : map) {
                row.clear();
            }
            map.clear();
        }
        maps.clear();
    }

    // Metoda do wczytywania mapy z pliku tekstowego
    void loadMapsFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        std::vector<std::vector<char>> map;
        std::string line;
        while (std::getline(file, line)) {
            std::vector<char> row;
            for (char c : line) {
                if (c != '\n') {
                    row.push_back(c);
                }
            }
            map.push_back(row);
        }
        maps.push_back(map);

        file.close();
    }

    // Metoda zwracajaca najwieksza szerokosc mapy w kolekcji
    int getMaxWidth() const {
        int maxWidth = 0;
        for (const auto& map : maps) {
            maxWidth = (((maxWidth) > (static_cast<int>(map[0].size()))) ? (maxWidth) : (static_cast<int>(map[0].size())));
        }
        return maxWidth;
    }

    // Metoda zwracajaca najwieksza wysokosc mapy w kolekcji
    int getMaxHeight() const {
        int maxHeight = 0;
        for (const auto& map : maps) {
            maxHeight = (((maxHeight) > (static_cast<int>(map.size()))) ? (maxHeight) : (static_cast<int>(map.size())));
        }
        return maxHeight;
    }
};

#endif