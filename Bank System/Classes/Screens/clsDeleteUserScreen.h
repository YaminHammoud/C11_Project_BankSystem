#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsUser.h"
#include "../Libraries/clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
    
    private :
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

    public :

   static void ShowDeleteUserScreen()
   {
        _DrawScreenHeader("\t Delete User Screen"); 
        string username = "";

        cout << "\nPlease Enter UserName: ";
        username = clsInputValidate::ReadString(); 

        while (!clsUser::IsUserExist(username))
        {
            cout << "\nUser Name is already exist, please enter another one: ";
            username = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(username); 
        _PrintUser(User1);

        cout << "\nAre You Sure You Want Delete this User y/n? ";
        char answer = 'n'; 
        cin >> answer; 


        if (toupper(answer) == 'Y')
        {
            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else 
            {
                cout << "\nError, User was not deleted.\n"; 
            }
        }

        else 
        {
            cout << "\nDelete User was Canceled :-)\n"; 
        }
   }
};