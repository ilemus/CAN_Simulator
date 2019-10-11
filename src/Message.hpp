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
        byte[] serialize();
    };
}

using namespace can;

namespace can {
    /*
    class: Message
    purpose: CAN Message container
    description: A container object which contains information about the message itself
        (arbitration ID, message name, sender ECU, and message length).
        Also contains the message values itself.
        
        Signals are stored in a hash map by signal name. The user should be able to make a script to update signal values or get signal values.
        Ex Script:
            when signal Application:Increase_Speed
                var value = get signal CLU11:CF_Clu_Vanz
                update signal CLU11:CF_Clu_Vanz (value + 1)
    */
    class Message {
    private:
        unordered_map<string, Signal> signals;
        int can_id;
        string sender_name;
        string message_name;
        unsigned char* can_message;
        int message_length;
    public:
        Message(int id, string message_name ,unsigned int length, string sender_name);
        ~Message();
        // Add signal to message. messages should not be overlapping. Signal considers start bit and length.
        void add_signal(string name, Signal signal) {
            signals[name] = signal;
        }
        // lower half (long msb 00 00 00 00 lsb). Set the signal (previously defined for the message) to the value provided.
        void update_signal(string name, unsigned long long int value);
        // Get the signal value based on previously defined signal in message.
        unsigned long long int get_signal(string name);
        // Update the values of the whole message with a char array.
        void update_message(vector<unsigned char> message);
        string get_message_name() { return message_name; }
        // Format the string to printable value (ID\tlength\tmessage array)
        string to_string();
        /*
        Serialization format will be short int type, int length, {content}
        */
        byte[] serialize();
    };
}
#endif