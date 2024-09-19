University of Antwerp Project
Tested on Ubuntu

Read additional [design choice](https://github.com/AP-Lab-Sessions/2023-project-Z3roC0d3/blob/master/PacManV2%20Doc.pdf)

# Game Features

### Menu

The game menu serves as the main hub where players can start the game, view credits, or exit the game. It includes the
following options:

- **Map Selection Button**: Allows players to choose the map on which they want to play.
- **Play Button**: Starts the game with the selected map and settings.
- **Credit Button**: Displays the game credits, acknowledging the contributors.
- **Exit Button**: Closes the game application.

### Top 5 High Scores

- The game tracks and displays the top 5 highest scores achieved by players.
- Scores are preserved and updated as players achieve higher scores during the game.
- Score are not saved if the game is exited before winning or losing(e.g. going back from pause to menu)

### Levels

- The game consists of multiple levels. Players advance to the next map when a level ends.
- Difficulty increases with each level as ghosts become faster and more aggressive.

### Ghosts and PacMan Movement

- **Ghosts** and **PacMan** have predefined movement patterns based on the map layout.
- An extra feature ensures that entities attempting to move out of bounds reappear on the opposite side of the map.
- **Player Movement**: Players control PacMan using either the arrow keys or WASD keys.
- **Collisions with Walls**: Movement is restricted by walls, preventing PacMan and ghosts from moving through them.

### Coins, Fruits, and Banana Sleep Feature

- **Coins** and **Fruits** are collectible items scattered across the map.
- **Banana Sleep Feature**: A special item that temporarily disables ghosts, allowing PacMan to move freely without
  being chased.

### Remaining Lives

- Players start with 3 lives.
- Lives are preserved throughout the game session. Losing all lives results in a game-over state.
- The player loses a life when colliding with a ghost that is not in fear mode.

### Switching Maps

- The game automatically switches to the next map when the current level is completed.
- This transition increases the game’s difficulty, enhancing the challenge for the player.

### Ghost AI

- **Ghost Mode State Pattern**: Ghost behavior is managed using a state pattern, allowing them to switch between
  different modes (setup, chase, fear).
- **Ghost Setup**: During setup, ghosts target a special coin named `ghostsetupcheckpoint`.
- **Chase Mode**: Once setup is complete, ghosts enter chase mode, selecting directions based on the Manhattan distance
  to PacMan.
- **Fear Mode**: Triggered when PacMan collects a fruit, causing ghosts to flee in randomized directions. This mode is
  temporary.
- **Decision-Making**: Ghosts choose new directions whenever they encounter a wall or intersection during chase and fear
  modes.

### Scoring System

- **Score Value**: Different entities have different score values (Coins < Fruits < Ghosts).
- **Score Persistence**: Scores are preserved as long as PacMan's lives
- **Top 5 Scores**: If a player's score ranks in the top 5, it is saved.
- **Game Over**: The game ends when all 3 lives are lost.
- **Increasing Difficulty**: As players progress to higher levels, the difficulty increases, primarily through faster
  ghost movements.
- **Pause and Resume**: Players can safely pause the game and resume later without losing progress.

### Sprites and Animations

- **Sprites**: All entities except intersections have sprites to visually represent them.
- **Dynamic Animations**: Dynamic entities like PacMan and ghosts feature looping animations, handled by an animation
  class.
- **Directional Changes**: The sprites of PacMan and ghosts change depending on their direction of movement.

### Extra Feature: Audio

- **Sound Types**: The game includes various sounds that play in parallel, enhancing the immersive experience.
- **Background Music**: Background music is implemented and changes based on whether the player is in the main menu or
  an active level.

### Extra Features: Design using Templates and Patterns

- **State Manager:** : state pattern implemented as template class
- **Entity View:** entityview implemented as template class
- **Random Class:** implemented using templates
- **Map Manager and Stopwatch:** designed using singleton pattern

## Known Issues

- **Collision Detection:** Collision detection may fail in low FPS environments because `deltaTime` is used to calculate
  the next position of entities. Large `deltaTime` values can cause significant movement steps, potentially allowing
  entities to skip over walls and exit the map. To mitigate this, a 1-second delay is added at the start of the game to
  ensure proper loading of all components and accurate `deltaTime` calculation. However, collisions may still fail in
  very low FPS scenarios.



