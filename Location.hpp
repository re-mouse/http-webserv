//
// Created by Harren Leilani on 5/1/21.
//

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Server.hpp"
#include <map>
#include <string>

using namespace std;

class Location
{
public:
    string path;
    map<string, string> metaVariables;
    Server *server;
    Location(string path);
    Location &operator=(Location const& rhs);
    ~Location();
};

#endif