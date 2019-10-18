#include <iostream>
#include "Message.hpp"
#include "configuration.hpp"

using namespace std;
using namespace can;

int main() {
    cout << "Started application." << endl;
    Configuration config;
    config.read_vector_database("../20190122_DN8_2019_멀티_19-01-02.dbc");
    config.print_messages();
    
    cout << "==========================================" << endl;
    
    config.save_configuration("Configuration.cfg");
    Configuration other;
    other.load_configuration("Configuration.cfg");
    other.print_messages();
}