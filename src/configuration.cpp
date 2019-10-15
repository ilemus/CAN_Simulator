#include "configuration.hpp"

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void Configuration::read_vector_database(string filepath) {
    fstream infile(filepath);
    
    string line;
    Message* current_msg = NULL;
    while (getline(infile, line)) {
        vector<string> tokens = split(line, ' ');
        
        if (tokens.size() > 0 && tokens[0].compare("BO_") == 0) {
            // New message
            if (!(tokens.size() == 5)) continue;
            // BO_ 1279 RLSH11: 8 CGW
            int id = stoi(tokens[1]);
            unsigned int length = stoi(tokens[3]);
            current_msg = new Message(id, tokens[2].substr(0, tokens[2].length() - 1), length, tokens[4]);
            messages[id] = current_msg;
        } else if (tokens.size() > 1 && tokens[1].compare("SG_") == 0 && tokens[0].compare("") == 0) {
            // New signal

            if (tokens.size() != 10) continue;
            // SG_ CR_Solar_Right_Sens : 0|8@1+ (4.72441,0) [0|1200] "W/m2"  DATC
            int start_bit, length;
            vector<string> bits = split(tokens[4], '|');
            cout << "bits size: " << bits.size() << endl;
            if (bits.size() != 2) continue;
            start_bit = stoi(bits[0]);
            length = stoi(bits[1].substr(0, bits[1].find("@")));
            current_msg->add_signal(tokens[2], new Signal(start_bit, length));
            current_msg->update_signal(tokens[2], 0xffffffffffffffff);
        }
    }
    
    // Just printing out the messages
    for (auto it = messages.begin(); it != messages.end(); ++it) {
        Message* msg = it->second;
        cout << msg->get_message_name() << ":\t" << msg->to_string() << endl;
        
        for (auto s = msg->signals.begin(); s != msg->signals.end(); ++s) {
            cout << "\t" << s->first << ": " << s->second->start_bit << "|" << s->second->length << endl;
        }
    }
}
