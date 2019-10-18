#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class String {
public:
    int length;
    const char* c_str = NULL;
    
    String() : String("") {}
    String(string str) {
        length = str.length();
        c_str = str.c_str();
    }
    
    string to_string() {
        return string(c_str);
    }
    
    friend istream& operator>> (istream& is, String& str) {
        char* c_str;
        is >> str.length;
        c_str = new char[str.length];
        int temp;
        for (int i = 0; i < str.length; i++) {
            is >> temp;
            c_str[i] = (char) temp;
        }
        str.c_str = c_str;
        return is;
    }
    friend ostream& operator<< (ostream& os, const String& str) {
        os << str.length;
        for (int i = 0; i < str.length; i++) {
            os << " " << (int) str.c_str[i];
        }
        return os;
    }
};

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
        friend istream& operator>> (istream& is, Signal& sig) {
            is >> sig.start_bit >> sig.length;
            return is;
        }
        friend ostream& operator<< (ostream& os, const Signal& sig) {
            os << sig.start_bit << " " << sig.length;
            return os;
        }
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
        int can_id;
        string sender_name;
        string message_name;
        int message_length;
        unsigned char* can_message;
        void init_message();
    public:
        unordered_map<string, Signal*> signals;
        Message() : Message(0, "", 0, "") {}
        Message(int id, string message_name, unsigned int length, string sender_name);
        ~Message();
        // Add signal to message. messages should not be overlapping. Signal considers start bit and length.
        void add_signal(string name, Signal* signal) {
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
        
        int get_can_id() { return can_id; }
        
        friend istream& operator>> (istream& is, Message& msg) {
            String sender_name, message_name;
            is >> msg.can_id >> sender_name >> message_name >> msg.message_length;
            msg.sender_name = sender_name.to_string();
            msg.message_name = message_name.to_string();
            
            int count;
            is >> count;
            for (int i = 0; i < count; i++) {
                String name;
                int start_bit;
                int length;
                is >> name >> start_bit >> length;
                msg.signals[name.to_string()] = new Signal(start_bit, length);
            }
            
            return is;
        }
        friend ostream& operator<< (ostream& os, const Message& msg) {
            os << msg.can_id << " " << String(msg.sender_name) << " " << String(msg.message_name) << " " << msg.message_length;
            os << " " << msg.signals.size();
            for (auto s = msg.signals.begin(); s != msg.signals.end(); ++s) {
                // Strings might need to be converted to bytes
                cout << " " << String(s->first) << " " << s->second->start_bit << " " << s->second->length;
            }
            return os;
        }
    };
}
#endif