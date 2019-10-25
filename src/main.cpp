#include <iostream>
#include "Message.hpp"
#include "configuration.hpp"

using namespace std;
using namespace can;

int main() {
    cout << "Started application." << endl;
    
    
    // Configuration config;
    // config.read_vector_database("../20190122_DN8_2019_멀티_19-01-02.dbc");
    
    /*
    cout << *config.messages[0xf5] << endl;
    cout << config.messages[0xf5]->get_sender_name() << " " << config.messages[0xf5]->get_message_name() << ":\t" << config.messages[0xf5]->to_string() << endl;

    for (auto s = config.messages[0xf5]->signals.begin(); s != config.messages[0xf5]->signals.end(); ++s) {
        cout << "\t" << s->first << ": " << s->second->start_bit << "|" << s->second->length << endl;
    }
    
    Message msg;
    cin >> msg;
    cout << msg << endl;
    cout << msg.get_sender_name() << " " << msg.get_message_name() << ":\t" << msg.to_string() << endl;

    for (auto s = msg.signals.begin(); s != msg.signals.end(); ++s) {
        cout << "\t" << s->first << ": " << s->second->start_bit << "|" << s->second->length << endl;
    }
    */
    
    /*
    String s("EDT_AMP_DEV_BEEP_USE_E_1");
    cout << s << endl;
    cout << s.to_string() << endl;
    String a;
    cin >> a;
    cout << a << endl;
    cout << s.to_string() << endl;
    */
    
    
    // config.print_messages();
    
    // cout << "==========================================" << endl;
    
    // config.save_configuration("Configuration.cfg");
    Configuration other;
    other.load_configuration("Configuration.cfg");
    other.print_messages();
    
}