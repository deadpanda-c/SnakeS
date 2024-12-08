
#include <SFML/Network/Packet.hpp>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

class BinaryPacket
{
    public:
        enum PacketType : uint8_t {
            PLAYER_ACTION = 0x01,
            GAME_STATE = 0x02,
            PLAYER_JOIN = 0x03,
            PLAYER_LEAVE = 0x04,
            GAME_OVER = 0x05,
            KEEP_ALIVE = 0x06,
            FRUIT_STATUS = 0X07,
            DEATH = 0X08,
            EAT_FRUIT = 0X09,
            CLIENT_ID = 0X10
        };

        BinaryPacket(PacketType type);

        std::vector<uint8_t> serialize() const;

        static BinaryPacket deserialize(const std::vector<uint8_t> &data);

        void addByte(uint8_t byte);
        void addUint16(uint16_t value);
        void addString(const std::string &str);

        uint8_t getByte(size_t index) const;
        uint16_t getUint16(size_t index) const;
        std::string getString(size_t index, size_t length) const;

        PacketType getType() const { return type_; }
        size_t getLength() const { return payload_.size(); }

    private:
        PacketType type_;              // Packet type (4 bits)
        std::vector<uint8_t> payload_; // Packet payload

        // Helper to check if payload access is in bounds
        void checkIndex(size_t index, size_t size) const;
};

inline sf::Packet &operator<<(sf::Packet &packet, const std::vector<uint8_t> &serialize_data)
{
    for (unsigned char i : serialize_data)
        packet << i;
    return packet;
}

inline sf::Packet &operator>>(sf::Packet &packet, std::vector<uint8_t> &serialize_data)
{
    uint8_t x;

    for (int i{0}; i < packet.getDataSize(); i++) {
        packet >> x;
        serialize_data.emplace_back(x);
    }
    return packet;
}
