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
        } else if (tokens.size() > 0 && tokens[0].compare("SG_") == 0) {
            // New signal
            if (!(tokens.size() == 8)) continue;
            // SG_ CR_Solar_Right_Sens : 0|8@1+ (4.72441,0) [0|1200] "W/m2"  DATC
            
        }
    }
    
    for (auto it = messages.begin(); it != messages.end(); ++it) cout << it->second->get_message_name() << "\t\t\t\t: " << it->second->to_string() << endl;
}
