TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:\sfml\SFML-2.5.1\include"
SOURCES += \
        assetsmanager.cpp \
        bat.cpp \
        endgame.cpp \
        enemy.cpp \
        explosion.cpp \
        fireball.cpp \
        fuel.cpp \
        game.cpp \
        gameplay.cpp \
        heart.cpp \
        helicopter.cpp \
        main.cpp \
        menu.cpp \
        player.cpp \
        reinforcements.cpp \
        state.cpp \
        statemanager.cpp
        LIBS += -L"C:\sfml\SFML-2.5.1\lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }

HEADERS += \
    AssetsManager.h \
    Bat.h \
    EndGame.h \
    Enemy.h \
    Explosion.h \
    Fireball.h \
    Fuel.h \
    Game.h \
    Gameplay.h \
    Heart.h \
    Helicopter.h \
    Menu.h \
    Player.h \
    Reinforcements.h \
    State.h \
    StateManager.h
