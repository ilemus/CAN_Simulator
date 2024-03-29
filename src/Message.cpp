#include "Message.hpp"

Message::Message(int id, string msg ,unsigned int length, string sndr) {
    can_id = id;
    message_name = msg;
    message_length = length;
    init_message();
    if (!sndr.empty() && sndr[sndr.size() - 1] == '\r') sndr.erase(sndr.size() - 1);
    sender_name = sndr;
}

void Message::init_message() {
    can_message = new unsigned char[message_length];
    // Originally values are garbage.
    for (int i = 0; i < message_length; i++) {
        can_message[i] = 0;
    }
}

Message::~Message() {
    // We created this so we need to delete it too
    delete(can_message);
}

void Message::update_signal(string str, unsigned long long int value) {
    Signal* s = signals[str];
    int start_byte = s->start_bit / 8;
    int grab = s->start_bit % 8;
    int remaining = s->length;
    int mask = 0x0FF;
    int byte_count = 0;
    while (remaining > 0) {
        if (remaining < 8) {
            mask = mask >> 8 - remaining;
            remaining = 0;
        }
        // Clear the signal value (0x32) &= [(0xF0) -> (0x0F)] -> (0x02)
        can_message[start_byte + byte_count] &= ~(mask << grab);
        // Write the signal value (0x02) |= [(0x0F) & (0x89) -> (0x09) -> (0x90)] -> (0x92)
        can_message[start_byte + byte_count] |= (value & mask) << grab;
        // Now that we wrote part of the signal remove that part  (0x9289) -> (0x0928)
        value = value >> 8 - grab;
        // Remaining bits to write
        remaining -= 8 - grab;
        // First case there is a grab value, other cases dont need this
        grab = 0;
        // Next byte
        byte_count++;
    }
}

unsigned long long int Message::get_signal(string name) {
    unsigned long long int result = 0L;
    Signal* s = signals[name];
    int mask = 0x0FF;
    int start_byte = s->start_bit / 8;
    int grab = s->start_bit % 8;
    int byte_count = 0;
    int remaining = s->length;
    while (remaining > 0) {
        if (remaining < 8) {
            mask = mask >> 8 - remaining;
            remaining = 0;
        }
        // Write the signal value (0x02) |= [(0x0F) & (0x89) -> (0x09) -> (0x90)] -> (0x92)
        result |= (can_message[start_byte + byte_count] & mask >> grab) << (byte_count * 8);
        // Now that we wrote part of the signal remove that part  (0x9289) -> (0x0928)
        // Remaining bits to write
        remaining -= 8 - grab;
        // First case there is a grab value, other cases dont need this
        grab = 0;
        // Next byte
        byte_count++;
    }
    return result;
}

string Message::to_string() {
    stringstream result;
    result << std::hex << can_id << "\t";
    for (int i = 0; i < message_length - 1; i++) {
        result << std::setfill('0') << std::setw(2) << std::hex << (int) can_message[i] << " ";
    }
    result << std::setfill('0') << std::setw(2) << std::hex << (int) can_message[message_length - 1];
    return result.str();
}
