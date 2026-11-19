#pragma once 
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Models/clsUser.h"
#include "../Libraries/clsInputValidate.h"
#include "clsMainScreen.h"

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 0;

        string UserName, Password;

        do
        {
            if (LoginFaild)
            {
                FaildLoginCount++;
                cout << "\nInvalid UserName/Password, Try Again: \n";
                printf("You have %i Trial(s) to login.\n\n", 3 - FaildLoginCount);
            }

            if (FaildLoginCount == 3)
            {
                cout << "\n\nYou are locked after 3 faild trials :-(\n";
                return false;
            }

            cout << "\nPlease Enter UserName? ";
            UserName = clsInputValidate::ReadString();
            cout << "\nPlease Enter Password? ";
            Password = clsInputValidate::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn(); 
        clsMainScreen::ShowMainMenu();
        return true;
    }

  
public:

    static bool ShowLoginScreen()
    {
        clsUtil::ClearScreen();
        _DrawScreenHeader("\t   Login Screen");
        return _Login(); 
    }
};