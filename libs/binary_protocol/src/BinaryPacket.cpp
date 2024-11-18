#include "BinaryPacket.hpp"
#include <stdexcept>

BinaryPacket::BinaryPacket(PacketType type) : type_(type) {}

std::vector<uint8_t> BinaryPacket::serialize() const {
    std::vector<uint8_t> data;

    uint8_t header = (static_cast<uint8_t>(type_) & 0x0F) << 4 | (payload_.size() & 0x0F);
    data.push_back(header);

    data.insert(data.end(), payload_.begin(), payload_.end());

    return data;
}

BinaryPacket BinaryPacket::deserialize(const std::vector<uint8_t>& data) {
    if (data.empty()) throw std::invalid_argument("Data cannot be empty");

    uint8_t header = data[0];
    PacketType type = static_cast<PacketType>((header >> 4) & 0x0F);
    size_t length = header & 0x0F;

    // Validate payload length
    if (data.size() - 1 != length) throw std::invalid_argument("Incorrect payload length");

    BinaryPacket packet(type);
    packet.payload_.assign(data.begin() + 1, data.end());

    return packet;
}

// Add a single byte to the payload
void BinaryPacket::addByte(uint8_t byte) {
    payload_.push_back(byte);
}

// Add a 16-bit unsigned integer to the payload (big-endian format)
void BinaryPacket::addUint16(uint16_t value) {
    payload_.push_back((value >> 8) & 0xFF);  // High byte
    payload_.push_back(value & 0xFF);         // Low byte
}

// Add a string to the payload (fixed-length, terminated by null byte, or length-prefixed)
void BinaryPacket::addString(const std::string& str) {
    payload_.insert(payload_.end(), str.begin(), str.end());
    payload_.push_back(0);  // Null-terminate string
}

// Get a single byte from the payload
uint8_t BinaryPacket::getByte(size_t index) const {
    checkIndex(index, 1);
    return payload_[index];
}

// Get a 16-bit unsigned integer from the payload (big-endian format)
uint16_t BinaryPacket::getUint16(size_t index) const {
    checkIndex(index, 2);
    return (payload_[index] << 8) | payload_[index + 1];
}

// Get a string from the payload
std::string BinaryPacket::getString(size_t index, size_t length) const {
    checkIndex(index, length);
    return std::string(payload_.begin() + index, payload_.begin() + index + length);
}

// Helper function to check bounds for payload access
void BinaryPacket::checkIndex(size_t index, size_t size) const {
    if (index + size > payload_.size()) {
        throw std::out_of_range("Index out of range in payload");
    }
}
