/*
** File description:
** Snake
*/

#pragma once

#include "BinaryPacket.hpp"
#include <sys/types.h>
#include <vector>

enum orient : uint8_t { NORTH = 0, SOUTH = 1, WEST = 2, EAST = 3 };

struct Body {
        uint s_pos_x{0};
        uint s_pos_y{0};
        orient s_orient{orient::NORTH};
};

class Snake
{
    public:
        Snake() = delete;
        Snake(uint head_x, uint head_y, orient head_orient, short id);
        Snake(Snake const &to_copy) = default;
        Snake(Snake &&to_move) = default;
        ~Snake() = default;
        Snake &operator=(Snake const &to_copy) = default;
        Snake &operator=(Snake &&to_move) = default;

        void eat_apple();
        void move();
        void edit_packet(BinaryPacket &packet);
        [[nodiscard]] bool is_colliding_it(Body head) const;
        [[nodiscard]] bool is_colliding_wall(uint max_height, uint max_width) const;
        [[nodiscard]] orient get_orient() const;
        void set_orient(orient orient);
        [[nodiscard]] bool is_it_dead() const;
        void set_death();
        [[nodiscard]] Body get_head_pos() const;

    private:
        bool m_is_dead{false};
        short m_id{0};
        uint m_head_x{0};
        uint m_head_y{0};
        orient m_head_orient{0};
        std::vector<Body> m_body_pos;
};
