//
// Created by R1perXNX on 7/3/2024.
//

#ifndef PACMANV2_WORLD_H
#define PACMANV2_WORLD_H

#include "Entities/IAbstractFactory.h"
#include "../Game/MapManager.h"


namespace Logic {
class World {
private:
    static constexpr short PLAY_AGAIN_COOLDOWN = 2;
    static constexpr short SPAWN_BANANA_COOLDOWN = 10;
    Map map;
    static std::shared_ptr<PacmanEntity> pacman;
    std::vector<std::shared_ptr<GhostEntity>> ghosts;
    //std::shared_ptr<PacmanController> pacmanController;
    static std::array<std::array<std::shared_ptr<EntityModel>, MAP_ROW_SIZE>, MAP_COLUM_SIZE> staticEntities;
    static std::weak_ptr<EntityModel> ghostEscapePoint;
    std::vector<Vector2f> avaiableSpawnPos;
    std::unique_ptr<IAbstractFactory> entityFactory;
    std::chrono::steady_clock::time_point bananaSpawnTime;
    std::chrono::steady_clock::time_point playerDeathTime;

private:
    void LoadMap();
    static std::shared_ptr<EntityModel> GetEntityAt(int x, int y);

public:
    World(std::unique_ptr<IAbstractFactory> factory);
    void SetMap(const Map& map);
    static bool CheckWallCollision(const std::shared_ptr<DynamicEntityModel>& entity, Direction direction,
                                   float predictionOffset);
    void CheckGhostCollision(const std::shared_ptr<GhostEntity>& ghost);
    static bool CheckCollectableCollision(const std::shared_ptr<EntityModel>& entity);
    void HandleCollision(); // This could be threaded
    void Update();
    const static std::shared_ptr<PacmanEntity>& GetLocalPlayer() { return pacman; }

    static const std::array<std::array<std::shared_ptr<EntityModel>, MAP_ROW_SIZE>, MAP_COLUM_SIZE>&
    GetStaticEntities() { return staticEntities; }

    const std::vector<std::shared_ptr<GhostEntity>>& GetGhosts() { return ghosts; }
    static std::weak_ptr<EntityModel> GetGhostEscapePoint() { return ghostEscapePoint; }
    ~World();
};
}

#endif //PACMANV2_WORLD_H
