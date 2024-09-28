# University of Antwerp Project

Tested on Ubuntu

Read additional [design choice](https://github.com/AP-Lab-Sessions/2023-project-Z3roC0d3/blob/master/PacManV2%20Doc.pdf)

## Game Overview

- **Menu**:
  - Map Selection: Choose a map for gameplay.
  - Play: Start the game.
  - Credit: View contributors.
  - Exit: Close the game.

- **High Scores**:
  - Top 5 highest scores are displayed.
  - Scores are updated unless the game is exited prematurely.

- **Levels**:
  - Multiple levels with increasing difficulty.
  - Ghosts become faster and more aggressive with each level.

- **Movement**:
  - PacMan and Ghosts have predefined movement based on the map.
  - Player controls PacMan with arrow keys or WASD.
  - Entities reappear on the opposite side when moving out of bounds.
  - Collisions with walls restrict movement.

- **Collectibles**:
  - Coins and Fruits are scattered across the map.
  - Banana Sleep temporarily disables ghosts.

- **Lives**:
  - Players start with 3 lives.
  - Losing all lives results in game-over.

- **Map Progression**:
  - Game automatically switches to the next map after completing a level.
  - Difficulty increases as new maps are introduced.

- **Ghost AI**:
  - Ghosts switch between different modes:
    - Setup: Target a special coin.
    - Chase: Pursue PacMan based on Manhattan distance.
    - Fear: Triggered when PacMan collects a fruit, causing ghosts to flee.

- **Scoring**:
  - Different values for Coins, Fruits, and Ghosts.
  - Scores are saved if they rank in the top 5.
  - Game ends when all 3 lives are lost.

- **Animations**:
  - Sprites for PacMan, Ghosts, and other entities.
  - Directional changes are reflected in sprite orientation.

## Additional Features

- **Audio**:
  - Background music changes depending on the state (menu or level).
  - Sound effects play in parallel to enhance immersion.

- **Design Patterns**:
  - State pattern and template classes for ghost behavior.
  - Singleton pattern for map manager and stopwatch.

## Known Issues

- **Collision Detection**:
  - In low FPS environments, collision detection may fail due to large `deltaTime` values.
  - A 1-second delay is added at the start to help reduce these issues, though problems may still arise in extreme cases.
