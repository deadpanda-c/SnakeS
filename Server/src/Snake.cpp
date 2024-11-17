/*
** File description:
** Snake
*/

#include <Snake.hh>
#include <algorithm>

Snake::Snake(uint head_x, uint head_y, orient head_orient, short id)
    : m_head_x{head_x}, m_head_y{head_y}, m_head_orient{head_orient}, m_id{id}
{
    if (head_orient == orient::NORTH)
        m_body_pos.emplace_back(Body{m_head_x, m_head_y + 1});
    if (head_orient == orient::SOUTH)
        m_body_pos.emplace_back(Body{m_head_x, m_head_y - 1});
    if (head_orient == orient::EAST)
        m_body_pos.emplace_back(Body{m_head_x + 1, m_head_y});
    if (head_orient == orient::WEST)
        m_body_pos.emplace_back(Body{m_head_x - 1, m_head_y});
}

void Snake::eat_apple()
{
    orient last_body_orient{m_body_pos[m_body_pos.size() - 1].s_orient};
    uint last_body_x{m_body_pos[m_body_pos.size() - 1].s_pos_x};
    uint last_body_y{m_body_pos[m_body_pos.size() - 1].s_pos_y};

    if (last_body_orient == orient::NORTH)
        m_body_pos.emplace_back(Body{last_body_x, last_body_y + 1, orient::NORTH});
    if (last_body_orient == orient::SOUTH)
        m_body_pos.emplace_back(Body{last_body_x, last_body_y - 1, orient::SOUTH});
    if (last_body_orient == orient::EAST)
        m_body_pos.emplace_back(Body{last_body_x + 1, last_body_y, orient::EAST});
    if (last_body_orient == orient::WEST)
        m_body_pos.emplace_back(Body{last_body_x - 1, last_body_y, orient::WEST});
}

void Snake::move()
{
    int x_value{0};
    int y_value{0};

    if (m_head_orient == orient::NORTH)
        y_value = 1;
    if (m_head_orient == orient::SOUTH)
        y_value = -1;
    if (m_head_orient == orient::EAST)
        x_value = 1;
    if (m_head_orient == orient::WEST)
        x_value = -1;
    for (ulong i{m_body_pos.size() - 1}; i >= 0; i--) {
        if (i == 0) {
            m_body_pos[i].s_orient = m_head_orient;
            m_body_pos[i].s_pos_x = m_head_x;
            m_body_pos[i].s_pos_y = m_head_y;
        } else {
            m_body_pos[i].s_orient = m_body_pos[i - 1].s_orient;
            m_body_pos[i].s_pos_x = m_body_pos[i - 1].s_pos_x;
            m_body_pos[i].s_orient = m_body_pos[i - 1].s_orient;
        }
    }
    m_head_x += x_value;
    m_head_y += y_value;
}

[[nodiscard]] bool Snake::is_colliding_it(Body head) const
{
    if (head.s_pos_x == m_head_x && head.s_pos_y == m_head_y)
        return true;
    auto lambda = [=](const Body &body_part) -> bool {
        return body_part.s_pos_x == head.s_pos_x && body_part.s_pos_y == head.s_pos_y;
    };
    return std::find_if(m_body_pos.begin(), m_body_pos.end(), lambda) == m_body_pos.end();
}

[[nodiscard]] bool Snake::is_colliding_wall(uint max_height, uint max_width) const
{
    return m_head_x == 0 || m_head_y == 0 || m_head_x == max_width || m_head_y == max_height;
}

[[nodiscard]] orient Snake::get_orient() const
{
    return m_head_orient;
}

void Snake::set_orient(orient orient)
{
    m_head_orient = orient;
}

void Snake::edit_packet(BinaryPacket &packet)
{
    packet.addUint16(m_id);
    packet.addUint16(m_head_x);
    packet.addUint16(m_head_y);
    char tmp{static_cast<char>(m_body_pos.size())};
    char tmp2{static_cast<char>(m_head_orient)};
    tmp2 <<= 6;
    packet.addByte(tmp & tmp2);
}

void Snake::set_death()
{
    m_is_dead = true;
}

[[nodiscard]] bool Snake::is_it_dead() const
{
    return m_is_dead;
}

[[nodiscard]] Body Snake::get_head_pos() const
{
    return Body{m_head_x, m_head_y};
}
