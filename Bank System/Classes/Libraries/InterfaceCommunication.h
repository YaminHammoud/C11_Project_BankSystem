#pragma once 
#include <iostream>
#include <string> 

using namespace std; 

class InterfaceCommunication 
{
public:
    virtual void SendEmail(string Title, string Body) = 0;
    virtual void SendFax(string Title, string body) = 0;
    virtual void SendSMS(string Title, string body) = 0;

    /* this is an interface for communication
        any class Implement it should override this methods at the same signature (same name and parameters).
    */
};
