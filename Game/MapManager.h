//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_MAPMANAGER_H
#define PACMANV2_MAPMANAGER_H
#include <vector>
#include <string>
#include <fstream>
#include "../json.hpp"
#include "../Global.h"

namespace Game {
class MapManager {
private:
    std::vector<Map> maps;
    int index;

    MapManager()
        : index(0) {
    } // Private constructor

public:
    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    static MapManager& GetInstance();

    void LoadMaps(const std::string& file_path);
    void NextMap(); // Move to the next map
    inline void SetMap(const int index) { this->index = index % maps.size(); }
    unsigned long GetTotalMaps() const { return maps.size(); }
    const Map& GetCurrentMap() const; // Get the current map
};
}
#endif //PACMANV2_MAPMANAGER_H
