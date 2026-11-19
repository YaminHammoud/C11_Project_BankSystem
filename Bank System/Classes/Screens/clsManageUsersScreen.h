#pragma once 

#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include <iomanip> 
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOptions { 
        eListUsers = 1 , eAddNewUser=2 , eDeleteUser = 3 , eUpdateUser= 4 , eFindUser = 5, eMainMenu = 6
    };

    static void _GoBackToManageUsersMenu()
    {
        cout << setw(33) << left << "" << "\nPress any key to go back to Manage Users Menu...";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();                                                     // Wait for user input
        ShowManageUsersMenu();
    }

    static short _ReadManageUsersMenuOption ()
    {
        cout << setw(33) << left << "" << "Choos What Do You Want To Do ? [1 TO 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 6, "\nPlease Enter A Number Between 1 And 6 ");

        return choice;
    }

    static void _ShowListUsersScreen ()
    {
        // cout << "\nList Users Screen Will Be Here........\n";
        clsListUsersScreen::ShowUsersList();

    }

    static void _ShowAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here................\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will Be Here................\n"; 
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here...............\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen ()
    {
        // cout << "\nFind User Screen Will Be Here.....................\n"; 
        clsFindUserScreen::ShowFindUserScreen(); 
    }

    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions Option)
    {
        switch (Option)
        {
            case enManageUsersMenuOptions::eListUsers : 
            {
                clsUtil::ClearScreen();
                _ShowListUsersScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenuOptions::eAddNewUser: 
            {
                clsUtil::ClearScreen();
                _ShowAddNewUserScreen();
                _GoBackToManageUsersMenu();
                break; 
            }

            case enManageUsersMenuOptions::eDeleteUser: 
            {
                clsUtil::ClearScreen();
                _ShowDeleteUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenuOptions::eUpdateUser: 
            {
                clsUtil::ClearScreen();
                _ShowUpdateUserScreen();
                _GoBackToManageUsersMenu();
                break; 
            }

            case enManageUsersMenuOptions::eFindUser: 
            {
                clsUtil::ClearScreen();
                _ShowFindUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }

            case enManageUsersMenuOptions::eMainMenu:
            {
                
            }

                }
    }

public:
    static void ShowManageUsersMenu()
    {
        if (!CheckRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }
        clsUtil::ClearScreen();

        _DrawScreenHeader("\tManage Users Screen");

        cout << "\n";

        cout << setw(33) << left << "" << "===================================\n\n";
        cout << setw(33) << left << "" << "\t Manage Users Menu\n\n";
        cout << setw(33) << left << "" << "===================================\n\n";

        cout << setw(33) << left << "" << "\t[1] List Users.\n";
        cout << setw(33) << left << "" << "\t[2] Add New User\n";
        cout << setw(33) << left << "" << "\t[3] Delete User.\n";
        cout << setw(33) << left << "" << "\t[4] Update User.\n";
        cout << setw(33) << left << "" << "\t[5] Find User.\n";
        cout << setw(33) << left << "" << "\t[6] Main Menu.\n\n";
        cout << setw(33) << left << "" << "===================================\n";

        _PerformManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
    }
    
};