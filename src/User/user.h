
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include "../Flow/flow.h"
using namespace std;

class User {
    private :
    string name;
    public:

    void greeting();
    void authentif();
    void login();
    void startBuildingflows();

};


#endif