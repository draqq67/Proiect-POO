
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
    void login(bool &logged);
    void startFlows();
    // void buildFlow();
    void createNewFlow();
    void accessExistingFlows(std::string username, std::string flowname );
    void deleteFlows();

};


#endif