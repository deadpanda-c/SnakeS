#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace Constants
{
    constexpr int SPRITE_SIZE = 16;
    constexpr const char* SNAKE_MIDDLE = "assets/snake_middle.png";
    constexpr const char* SNAKE_HEAD = "assets/snake_head.png";
    constexpr const char* SNAKE_TAIL = "assets/snake_tail.png";
    constexpr const char* SNAKE_ANGLE = "assets/snake_angle.png";
    constexpr const char* APPLE = "assets/apple.png";
    constexpr const char* FONT = "assets/Minecraft.ttf";
    constexpr const char* MAIN_BACKGROUND = "assets/menus/main_background.png";
    constexpr const char* CURSOR = "assets/cursor.png";
}

enum InputEnum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum LobbyStateEnum {
    MAIN,
    CONNECTING,
    CONNECTED,
    READY,
};

#endif // CONSTANTS_HPP
