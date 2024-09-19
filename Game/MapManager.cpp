//
// Created by R1perXNX on 7/1/2024.
//

#include "MapManager.h"

using json = nlohmann::json;
using namespace Game;

MapManager& MapManager::GetInstance() {
    static MapManager instance; // Static instance of MapManager
    return instance;
}

// Load maps from a JSON file
void MapManager::LoadMaps(const std::string& file_path) {
    try {
        // Open the specified file
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::ios_base::failure("Unable to open file: " + file_path);
        }

        // Parse the JSON content of the file
        json j;
        file >> j;

        // Clear any previously loaded maps
        maps.clear();

        // Load each map from the JSON array
        for (json& mapJson : j["maps"]) {
            maps.push_back(mapJson.get<Map>()); // Deserialize JSON to Map object and store it in the maps vector
        }

        // Reset the map index to start from the first map
        index = 0;

    } catch (const std::exception& e) {
        // Print an error message if there's an issue with loading the maps
        std::cerr << "Error loading maps from file: " << e.what() << std::endl;
    }
}

// Advance to the next map in the list
void MapManager::NextMap() {
    // Increment the index, wrapping around if it exceeds the number of maps
    index = (index + 1) % maps.size();
}

const Map& MapManager::GetCurrentMap() const {
    return maps[index];
}
