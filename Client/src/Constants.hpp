#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define SPRITE_SIZE 16
#define SNAKE_MIDDLE "assets/snake_middle.png"
#define SNAKE_HEAD "assets/snake_head.png"
#define SNAKE_TAIL "assets/snake_tail.png"
#define SNAKE_ANGLE "assets/snake_angle.png"
#define APPLE "assets/apple.png"
#define FONT "assets/Minecraft.ttf"

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
