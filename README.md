
![Master](https://github.com/user-attachments/assets/56bc8e81-dc0d-466d-9b75-fc4e58baaba6)

Welcome to "Shadows Call" a 2D Action RPG Game.
Embark on a perilous journey into the abyss to confront a shadowy cult and unravel the secrets of their unholy power.

### -Game is still under development-

## Key Features

### Core Architecture
- **Entity-Component-System (ECS):** Decoupled data and behavior for scalability and reusability.
- **Scene Management:** Dynamic handling of multiple game scenes with lifecycle management.

### Graphics and Rendering
- **High-Performance Rendering:** Optimized rendering pipeline for smooth graphics.
- **Texture Management:** Efficient loading and management of sprites and textures.

### Input and Interaction
- **Input Handling:** Comprehensive support for keyboard and mouse input.
- **Event System:** Decoupled event-driven architecture for inter-component communication.

### Extensibility
- **Plugin Support:** Modular design to easily extend engine capabilities.
- **Scripting:** Integration-ready for scripting to accelerate game logic development.


---


# 2D Game Engine Using Qt Framework

This project is a modular and object-oriented 2D game engine designed using the Qt framework.

## 🛠️ Key Features

- **Dynamic Graphics Rendering**:
  - Built with `QGraphicsScene` and `QGraphicsView` for a scalable and efficient rendering pipeline.
  - Customizable tile-based maps using a 2D character array.

- **Interactive Player and NPCs**:
  - Controllable player character, with seamless integration into the game world.
  - NPCs (e.g., Enemy, Frog) demonstrate AI extensibility and interaction design.

- **High-Performance Game Loop**:
  - Smooth updates using `QTimer` with a 16ms interval for 60 FPS gameplay.
  - Modular `gameUpdate()` logic for scene-wide refreshes.

- **Extensible Design**:
  - Modular components for scene management, player, and NPCs.
  - Clearly defined class responsibilities ensure maintainability and scalability.

### Additional Features
- **Physics Integration:** Support for collision detection and basic physics.
- **Audio:** Expandable audio playback capabilities.

---

# Using the Engine

## Define a Scene

Scenes act as containers for game objects, logic, and rendering. To create custom scene logic, you can extend the `Scene` class and implement the necessary methods.

### Example:

```cpp
#include "Scene.h"

class GameScene : public Scene {
public:
    void onEnter() override {
        // Initialize scene objects
    }

    void update(float deltaTime) override {
        // Game logic
    }

    void onExit() override {
        // Cleanup resources
    }
};
```

### Explanation:
- **onEnter()**: This method is called when the scene is entered. You can initialize any resources or objects here.
- **update(float deltaTime)**: This method is called every frame. Use this method for the game logic and updates to your entities.
- **onExit()**: This method is called when the scene is exited. You should clean up any resources here.

## Create Entities and Add Components

The **Entity-Component-System (ECS)** design pattern allows you to assemble game objects dynamically by adding components to entities. Here's how you can create entities and add components in the engine.

### Example:

```cpp
void onEnter() override {
    Entity player = createEntity("Player");
    player.addComponent<TransformComponent>(/* initial position */);
    player.addComponent<SpriteComponent>("player_texture.png");
}
```

### Explanation:
- **createEntity("Player")**: Creates a new entity named "Player".
- **addComponent<TransformComponent>**: Adds a `TransformComponent` to the player entity, which might store position, rotation, and scale data.
- **addComponent<SpriteComponent>**: Adds a `SpriteComponent` to render the player's sprite using the specified texture.

This approach allows for dynamic and flexible game object creation where each entity can have different combinations of components to define its behavior.



## 🛠️  How to Build & Run

### Prerequisites
- **Qt Development Tools**: Qt Creator, Qt 5+ with `qmake`.
- **C++ Compiler**: Compatible with Qt requirements (e.g., GCC, MSVC).


### 🚀 Build Instructions
Clone the repository:

- git clone <repository_url>
- cd <repository_name>
- Open the project in Qt Creator:

- Locate the .pro file and open it using Qt Creator.
- Build and run
