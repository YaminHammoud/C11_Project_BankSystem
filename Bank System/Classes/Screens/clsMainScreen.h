#pragma once 

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Global.h"
#include "../Libraries/clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsDepositScreen.h"
#include "clsLoginScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"


using namespace std; 

class clsMainScreen : protected clsScreen 
{

private:

    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange= 9,
        eExit = 10
    };

    static short _ReadMainMenuOption()
    {

        cout << setw(33) << left << "" << "Choose what do you want to do ? [1 to 10]? ";

        short choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter a number between 1 and 10: ");
        return choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(33) << left << "" << "\nPress any key to go back to Main Menu...";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        cin.get(); // Wait for user input

        ShowMainMenu();
    }

    static void _ShowListClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenuScreen()
    {
        clsTransactonsScreen::ShowTransactionMenu();
    }

    static void _ShowManageUsersMenu()
    {
        // cout << "\nManage Users Screen Will be here...........\n";
        clsManageUsersScreen::ShowManageUsersMenu();
    }

    static void _ShowCurrencyExchangeMenuScreen()
    {
        // cout << "Currency Exchange Menu Screen Will be here...........\n";

        clsCurrencyExchangeMainScreen::ShowCurrenciesMenu(); 
    }

   /*  static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here.....................\n";
    } */

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", ""); 
        // this will make the current user empty.
        // here it will back to main function.

        // clsLoginScreen::ShowLoginScreen(); 
        // if we use this it will lead to Stack Overflow & Circular Reference because it will call the login screen again and again.
        // so we use while (true) in main to show login screen again .
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
    {
        switch (MainMenuOption)
        {
        case enMainMenuOptions::eListClients:
        {
            clsUtil::ClearScreen();
            _ShowListClientsScreen();
            _GoBackToMainMenu();
            break;
        }

        case enMainMenuOptions::eAddNewClient:
        {
            clsUtil::ClearScreen();
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;
        }

        case enMainMenuOptions::eDeleteClient:
        {
            clsUtil::ClearScreen();
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;
        }

        case enMainMenuOptions::eUpdateClient:
        {
            clsUtil::ClearScreen();
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break; 
        }

        case enMainMenuOptions::eFindClient:
        {
            clsUtil::ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        }

        case enMainMenuOptions::eShowTransactionsMenu:
        {
            clsUtil::ClearScreen();
            _ShowTransactionsMenuScreen();
            _GoBackToMainMenu();

            break;
        }

        case enMainMenuOptions::eManageUsers:
        {
            clsUtil::ClearScreen();
            _ShowManageUsersMenu();
            _GoBackToMainMenu();

            break;
        }

        case enMainMenuOptions::eLoginRegister:
        {
            clsUtil::ClearScreen();
            _ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break; 
        }

        case enMainMenuOptions::eCurrencyExchange:
        {
            clsUtil::ClearScreen(); 
            _ShowCurrencyExchangeMenuScreen(); 
            _GoBackToMainMenu();
            break;
        }

        case enMainMenuOptions::eExit:
        {
            clsUtil::ClearScreen();
            // _ShowEndScreen();
            _Logout();
            break; 
        }
    }
}

public:
static void ShowMainMenu()
{

    clsUtil::ClearScreen();
    _DrawScreenHeader("\t\tMain Screen");

    cout << "\n\n";

    cout << setw(33) << left << "" << string(39, '=') << "\n\n";
    cout << setw(33) << left << "" << "\t\tMain Menu\n\n";
    cout << setw(33) << left << "" << string(39, '=') << "\n\n";
    cout << setw(33) << left << "" << "\t[1] Show Client List\n";
    cout << setw(33) << left << "" << "\t[2] Add New Client\n";
    cout << setw(33) << left << "" << "\t[3] Delete Client\n";
    cout << setw(33) << left << "" << "\t[4] Update Client Info\n";
    cout << setw(33) << left << "" << "\t[5] Find Client\n";
    cout << setw(33) << left << "" << "\t[6] Transactions Menu\n";
    cout << setw(33) << left << "" << "\t[7] Manage Users\n";
    cout << setw(33) << left << "" << "\t[8] Login Register\n";
    cout << setw(33) << left << "" << "\t[9] Currency Exchange\n";
    cout << setw(33) << left << "" << "\t[10] Logout\n";
    cout << setw(33) << left << "" << string(39, '=') << "\n\n";

    _PerformMainMenuOption(enMainMenuOptions(_ReadMainMenuOption()));
}
};