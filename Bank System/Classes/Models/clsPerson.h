#pragma once

#include <iostream>
#include <string>
#include "../Libraries/InterfaceCommunication.h"

using namespace std; 

class clsPerson : public InterfaceCommunication
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone; 

    public:

    clsPerson (string FirstName, string LastName , string Email,string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone; 
    }


    void SetFirstName (string FirstName)
    {
       _FirstName = FirstName;
    }

    void SetLastName (string LastName)
    {
        _LastName = LastName;
    }

    void SetEmail (string Email)
    {
        _Email = Email;
    }

    void SetPhone (string Phone)
    {
        _Phone = Phone; 
    }



    string GetFirstName ()
    {
        return _FirstName;
    }

    string GetLastName  ()
    {
        return _LastName;
    }

    string GetEmail ()
    {
        return _Email;
    }

    string GetPhone()
    {
        return _Phone; 
    }

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void SendEmail (string Title, string body)
    {
        // if you don't overrid this 3 method -> there will be a compiler error.
    }

    void SendFax (string Title, string body)
    {

    }

    void SendSMS (string Title, string body)
    {
        
    }
};