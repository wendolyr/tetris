# 🎮 Tetris in C (console version)

A classic Tetris implementation in C using ASCII graphics in the terminal.

## 🌟 Features
- Classic tetris rules  
- Keyboard controls  
- Score system  
- Progressive difficulty (speed increases)  
- Next piece preview  
- Display where the current piece will drop
- ASCII interface  

## 📋 Requirements
- C compiler (GCC)  
- Linux/macOS Terminal  
- Installed `ncurses` library  

## 📥 Installation & Running
1. Clone the repository  
2. Compile the program using `make install`  
3. Start the game using `make play`  

## 🕹️ Controls
| --- | ----------------- |
| ← → | Move horizontally |  
|  ↓  | Hard drop         |  
|Space| Rotate piece      |
|  P  | Pause             |
| ESC | Quit              |

## 🛠️ Technical features
- Game realized using FSM (finite state machine)  
![img](./images/fsm_scheme.png)  
- 7 types of tetromino:  
![img](./images/tetris-pieces.png)  
- The progect includes unit tests covering all backend functions:  
![img](./images/gcov_report.png)  
To run tests and coverage report use `make test` and `make gcov_report`.  
- Documentation done using Doxyfile. For creation use `make dvi`.  

## 📷 Screenshots
![img](./images/main_menu.png)  
![img](./images/playing.png)  
![img](./images/pause_menu.png)  
![img](./images/game_over.png)
