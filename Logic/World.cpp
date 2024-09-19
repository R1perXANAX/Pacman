//
// Created by R1perXNX on 7/3/2024.
//

#include "World.h"
#include "../Game/ScoreManager.h"
#include "../Logic/Entities/DynamicEntities/States/SetupState.h"

#include "Random.h"

using namespace Logic;

std::array<std::array<std::shared_ptr<EntityModel>, MAP_ROW_SIZE>, MAP_COLUM_SIZE> World::staticEntities;
std::shared_ptr<PacmanEntity> World::pacman;
std::weak_ptr<EntityModel> World::ghostEscapePoint;

void World::LoadMap() {
    if (!entityFactory)
        return;

    int totalCoin = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); ++j) {
            const int entityType = map[i][j];
            Vector2i startingPosition(j, i);

            switch (entityType) {
            case Pacman:
                try {
                    auto entity = entityFactory->CreatePacman(startingPosition, 2.5f);
                    if (entity) {
                        pacman = entity;
                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            case Coin:
                try {

                    auto entity = entityFactory->CreateCoin(startingPosition);
                    if (entity) {
                        staticEntities[j][i] = entity;
                        totalCoin++;
                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            case Ghost:
                try {
                    static short spawnCooldown = 1;
                    auto entity = entityFactory->CreateGhost(startingPosition,
                                                             2.0f + static_cast<float>(gScoreManager->GetCurrentLevel())
                                                             * 0.1f);

                    if (entity) {
                        entity->SetSpawnCooldown(spawnCooldown);
                        ghosts.push_back(entity);
                        spawnCooldown++;
                        if (spawnCooldown == 5)
                            spawnCooldown = 1;
                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            case Fruit:
                try {
                    auto entity = entityFactory->CreateFruit(startingPosition);
                    if (entity) {
                        staticEntities[j][i] = entity;
                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            case Wall:
                try {
                    auto entity = entityFactory->CreateWall(startingPosition);
                    if (entity) {
                        staticEntities[j][i] = entity;

                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            case GhostSetup:
                try {

                    auto entity = entityFactory->CreateCoin(startingPosition);
                    if (entity) {
                        staticEntities[j][i] = entity;
                        ghostEscapePoint = entity;
                        totalCoin++;
                    }
                } catch (const std::bad_alloc& e) {
                    break;
                }
                break;
            default:
                std::cerr << "Unknown entity type at position (" << i << ", " << j << ")." << std::endl;
                break;
            }

        }

    }

    if (gScoreManager)
        gScoreManager->SetMaxCoins(totalCoin);

    for (const auto& ghost : ghosts) {
        ghost->PushState(std::make_unique<SetupState>(ghost));
    }
    pacman->Spawn();
}

std::shared_ptr<EntityModel> World::GetEntityAt(const int x, const int y) {
    if (x < MAP_COLUM_SIZE && y < MAP_ROW_SIZE && staticEntities[x][y])
        return staticEntities[x][y];
    return nullptr;
}

bool World::CheckWallCollision(const std::shared_ptr<DynamicEntityModel>& entity, Direction direction,
                               float predictionOffset) {
    bool collided = false;

    if (!entity)
        return collided;

    std::shared_ptr<EntityModel> collider;
    auto origin = entity->GetOrigin();

    switch (direction) {
    case Up:
        collider = GetEntityAt(origin.x, origin.y - predictionOffset);
        break;
    case Down:
        collider = GetEntityAt(origin.x, origin.y + predictionOffset);
        break;
    case Left:
        collider = GetEntityAt(origin.x - predictionOffset, origin.y);
        break;
    case Right:
        collider = GetEntityAt(origin.x + predictionOffset, origin.y);
        break;
    default:
        break;
    }

    if (collider && collider->GetType() == Wall)
        collided = true;

    return collided;
}

void World::CheckGhostCollision(const std::shared_ptr<GhostEntity>& ghost) {
    if (pacman && ghost && pacman->IsAlive() && ghost->IsAlive()) {
        const auto pacmanPos = pacman->GetOrigin();
        const auto ghostPos = ghost->GetOrigin();

        if (pacmanPos.DistanceTo(ghostPos) < 0.3) {
            if (ghost->GetStateType() == PlayerStateType::GhostFearing) {
                ghost->Kill();
                pacman->Notify(SubjectEvent::GhostEaten);
            } else {
                pacman->Kill();
                pacman->Notify(SubjectEvent::PacmanDead);
                playerDeathTime = std::chrono::steady_clock::now();
            }

        }
    }
}

bool World::CheckCollectableCollision(const std::shared_ptr<EntityModel>& entity) {
    if (!entity)
        return false;

    const auto position = entity->GetOrigin();

    if (pacman && pacman->IsAlive()) {
        if (pacman->GetOrigin().DistanceTo(position) < 0.4)
            return true;
    }
    return false;
}

void World::HandleCollision() {
    if (!pacman || !pacman->IsAlive())
        return;

    const auto pacmanPosition = pacman->GetPosition();
    const auto staticEntity = GetEntityAt(roundf(pacmanPosition.x), roundf(pacmanPosition.y));

    if (staticEntity) {
        const auto entityType = staticEntity->GetType();
        if (entityType == Fruit || entityType == Coin || entityType == Banana) {
            if (staticEntity->IsAvailable() && CheckCollectableCollision(staticEntity)) {

                switch (entityType) {
                case Banana:
                    pacman->Sleep();
                    staticEntity->SetAvailable(false);

                    break;
                case Fruit: {
                    staticEntity->SetAvailable(false);
                    for (auto& ghost : ghosts) {
                        if (ghost)
                            ghost->ToggleFearing();
                    }
                    pacman->Eat(staticEntity);
                    break;
                }
                case Coin:
                    pacman->Take(staticEntity);

                default:
                    break;

                }
                avaiableSpawnPos.push_back(staticEntity->GetPosition());
            }
        }
    }

    for (const auto& ghost : ghosts) {
        CheckGhostCollision(ghost);
    }
}

World::World(std::unique_ptr<IAbstractFactory> factory)
    : entityFactory(std::move(factory)) {
    ghosts.reserve(4);
}

void World::SetMap(const Map& map) {
    this->map = map;
    LoadMap();
    bananaSpawnTime = std::chrono::steady_clock::now();
}

void World::Update() {

    auto current_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - bananaSpawnTime);

    if (!avaiableSpawnPos.empty() && elapsed_time.count() > SPAWN_BANANA_COOLDOWN) {
        const auto randomIndex = Random::GetInstance().GetRandomInRange<int>(0, avaiableSpawnPos.size() - 1);
        const auto bananaSpawn = avaiableSpawnPos[randomIndex];
        const auto banana = entityFactory->CreateBanana(bananaSpawn);
        avaiableSpawnPos.erase(avaiableSpawnPos.begin() + randomIndex);
        staticEntities[static_cast<int>(bananaSpawn.x)][static_cast<int>(bananaSpawn.y)] = banana;
        bananaSpawnTime = std::chrono::steady_clock::now();
    }

    if (pacman && !pacman->IsAlive()) {
        if (gScoreManager->GetLifeLeft() != 0) {
            current_time = std::chrono::steady_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - playerDeathTime);
            if (elapsed_time.count() < PLAY_AGAIN_COOLDOWN)
                return;

            for (const auto& ghost : ghosts)
                ghost->Kill(); //FORCE RESPAWN

            pacman->Spawn();

        }

    }

    for (const auto& ghost : ghosts) {
        if (ghost) {
            ghost->Update();
        }
    }

    pacman->Update();

    return HandleCollision();
}

World::~World() {
    for (auto& row : staticEntities) {
        for (auto& entity : row) {
            entity.reset();
        }
    }
    pacman.reset();
}
