#include <iostream>
#include "Message.hpp"

using namespace std;
using namespace can;

int main() {
    cout << "Started application." << endl;
    Message msg(1, 740, 8);
    msg.add_signal("CF_Vanz", Signal(8, 15));
    for (int i = 0; i < 100000; i++) {
        msg.update_signal("CF_Vanz", (unsigned long int) i % 0x7FFF);
        cout << msg.to_string() << endl;
    }
}