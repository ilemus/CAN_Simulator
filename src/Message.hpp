#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace can {
    class Signal {
    public:
        unsigned int start_bit;
        unsigned int length;
        Signal(unsigned int s, unsigned int l) {
            start_bit = s;
            length = l;
        }
        Signal() : Signal(0, 0) {}
    };
}

using namespace can;

namespace can {
    class Message {
    private:
        unordered_map<string, Signal> signals;
        unsigned char can_line;
        int can_id;
        unsigned char* can_message;
        int message_length;
    public:
        Message(unsigned char line, int id, unsigned int length);
        ~Message();
        void add_signal(string name, Signal signal) {
            signals[name] = signal;
        }
        // lower half (long msb 00 00 00 00 lsb)
        void update_signal(string name, unsigned long long int value);
        unsigned long long int get_signal(string name);
        void update_message(vector<unsigned char> message);
        string to_string();
        vector<unsigned char> to_bytes();
    };
}
#endif