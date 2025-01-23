
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

---


## 📦 How to Build & Run

### Prerequisites
- **Qt Development Tools**: Qt Creator, Qt 5+ with `qmake`.
- **C++ Compiler**: Compatible with Qt requirements (e.g., GCC, MSVC).

### Build Instructions
1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <repository_directory>

🚀 Setup and Usage
Prerequisites
Qt Development Tools: Qt Creator, Qt 5+ with qmake.
C++ Compiler: GCC, MSVC, or equivalent (compatible with Qt).
Build Instructions
Clone the repository:

git clone <repository_url>
cd <repository_name>
Open the project in Qt Creator:

Locate the .pro file and open it using Qt Creator.
Build and run:

Configure the build environment.
Click "Run" to compile and launch the application.
