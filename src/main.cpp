#include <windows.h>
#include <iostream>
#include "../include/Math.h"
#include "../include/Tile.h"
#include "../include/Player.h"
#include "../include/GameState.h"

void showConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void setupEntities(GameState &gameState) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribX(0, gameState.worldWidth - 1);
    std::uniform_int_distribution<int> distribY(0, gameState.worldHeight - 1);

    for (int x = 0; x < gameState.worldWidth / 8; x++) {
        for (int y = 0; y < gameState.worldHeight / 8; y++) {
            int posX = distribX(gen);
            int posY = distribY(gen);

            while (gameState.world.find({posX, posY}) != gameState.world.end()) {
                posX = distribX(gen);
                posY = distribY(gen);
            }

            Math::Vector::Vector2D position(posX, posY);
            Entity entity{ "0" };
            gameState.world.insert({position, Tile(entity)});
        }
    }

    int posX = distribX(gen);
    int posY = distribY(gen);

    while (gameState.world.find({posX, posY}) != gameState.world.end()) {
        posX = distribX(gen);
        posY = distribY(gen);
    }

    gameState.player.setPosition({ posX, posY });
    gameState.world.insert({{ posX, posY }, Tile(gameState.player)});
}

void setup(GameState &gameState) {
    showConsoleCursor(false);
    gameState.worldWidth = 58;
    gameState.worldHeight = 25;
    setupEntities(gameState);
    gameState.isRunning = true;
}

void updatePlayerPositon(GameState &gameState, Math::Vector::Vector2D oldPosition) {
    auto newPosition = gameState.player.getPosition();

    if (newPosition.x != oldPosition.x || newPosition.y != oldPosition.y) {
        auto it = gameState.world.find(oldPosition);
        if (it != gameState.world.end()) {
            gameState.world.erase(it->first);
        }

        auto secondIt = gameState.world.find(newPosition);
        if (secondIt != gameState.world.end()) {
            if (secondIt->second.getEntity().getAppearance() == "0") {
                gameState.score += 1;

                int maxScore = (gameState.worldWidth / 8) * (gameState.worldHeight / 8);
                if (gameState.score == maxScore) {
                    gameState.isRunning = false;
                }
            }
        }

        gameState.player.setAppearance("1");
        gameState.world.insert({ newPosition, Tile(gameState.player) });
    }
}

bool update(GameState &gameState) {
    if (GetAsyncKeyState(VK_ESCAPE)) {
        gameState.isRunning = false;
        return true;
    }

    auto oldPosition = gameState.player.getPosition();

    if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
        gameState.player.movePlayer(Player::UP);
        updatePlayerPositon(gameState, oldPosition);
        return true;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
        gameState.player.movePlayer(Player::DOWN);
        updatePlayerPositon(gameState, oldPosition);
        return true;
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
        gameState.player.movePlayer(Player::LEFT);
        updatePlayerPositon(gameState, oldPosition);
        return true;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
        gameState.player.movePlayer(Player::RIGHT);
        updatePlayerPositon(gameState, oldPosition);
        return true;
    }

    return false;
}

void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, cursorPos);
}

void draw(GameState &gameState) {
    clearConsole();

    std::cout << " - ";
    for (int i = 0; i < gameState.worldWidth; ++i) {
        std::cout << "- ";
    }
    std::cout << "-" << std::endl;

    for (int y = 0; y < gameState.worldHeight; ++y) {
        std::cout << " | ";
        for (int x = 0; x < gameState.worldWidth; ++x) {
            auto it = gameState.world.find({ x, y });
            if (it != gameState.world.end()) {
                const Entity& entity = it->second.getEntity();
                std::string appearance = entity.getAppearance();
                if (!appearance.empty()) {
                    std::cout << appearance << " ";
                } else {
                    std::cout << "  ";
                }
                continue;
            }
            std::cout << "  ";
        }
        std::cout << "|" << std::endl;
    }

    std::cout << " - ";
    for (int i = 0; i < gameState.worldWidth; ++i) {
        std::cout << "- ";
    }
    std::cout << "-" << std::endl << std::endl;

    int maxScore = (gameState.worldWidth / 8) * (gameState.worldHeight / 8);
    std::cout << " Score: " << gameState.score << "/" << maxScore;
}

void loop(GameState &gameState) {
    draw(gameState);
    while (gameState.isRunning) {
        bool isUpdated = update(gameState);
        if (isUpdated) {
            draw(gameState);
        }
        Sleep(10);
    }
}

int main() {
    GameState gameState{};
    setup(gameState);
    loop(gameState);
}
