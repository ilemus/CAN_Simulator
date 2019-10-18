#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <unordered_map>
#include "Message.hpp"

using namespace std;
using namespace can;

class Configuration {
private:
    unordered_map<int, Message*> messages;
public:
    static Configuration load_configuration(string filepath);
    void save_configuration(string filepath);
    void read_vector_database(string filepath);
    
    void print_messages();
};
#endif