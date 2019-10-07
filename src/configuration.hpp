#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

using namespace std;

class Configuration {
    public:
    static Configuration load_configuration(string filepath);
    void save_configuration();
};
#endif