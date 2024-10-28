#include "BinaryPacket.hpp"

#include <iostream>
#include <bitset>
#include <iomanip>

void printBits(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << "Byte " << std::setw(2) << i << ": "
                  << std::bitset<8>(data[i]) << std::endl;
}

int main(void)
{

  BinaryPacket packet(BinaryPacket::PLAYER_ACTION);
  packet.addByte(5);  // Player ID
  packet.addByte(0x00); // Direction: Up

  // Serialize packet to send
  std::vector<uint8_t> data = packet.serialize();

  // Deserialize packet upon receiving
  BinaryPacket receivedPacket = BinaryPacket::deserialize(data);
  uint8_t playerId = receivedPacket.getByte(0);
  uint8_t direction = receivedPacket.getByte(1);

  printBits(data);
  std::cout << "Player ID: " << (int)playerId << std::endl;
  std::cout << "Direction: " << (int)direction << std::endl;

  return 0;
}
