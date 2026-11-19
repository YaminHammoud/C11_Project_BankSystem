#pragma once
#include <iostream>
#include "../Models/clsUser.h"
#include "../Libraries/clsInputValidate.h"
#include "clsScreen.h"

class clsFindUserScreen : protected clsScreen
{
private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

    public: 

    static void ShowFindUserScreen ()
    {
        _DrawScreenHeader("\t Find User Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser user1 = clsUser::Find(UserName);

        if (!user1.IsEmpty())
        {
            cout << "\nUser Found :-) \n\n";
        }
        else
        {
            cout << "\nUser was not found :-(\n";
        }
        
        _PrintUser(user1);
    }
};