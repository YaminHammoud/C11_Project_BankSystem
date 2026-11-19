#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdatCurrencyRateScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen
{

    private : 

    enum enCurrencyExchangeMenuOptions
    {
        eListCurrencies = 1, 
        eFindCurrency = 2, 
        eUpdateRate=3 , 
        eCurrencyCalculator=4,
        eMainMenu = 5
    };

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << setw(33) << left << "" << "\nPress any key to go back to Currency Exchange Menu...";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();                                                     // Wait for user input

        ShowCurrenciesMenu();
    }

    static short _ReadCurrencyExchangeMenuOption()
    {

        cout << setw(33) << left << "" << "Choose what do you want to do ? [1 to 5]? ";

        short choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter a number between 1 and 5: ");
        return choice;
    }

    static void _ShowListCurrenciesScreen()
    {
        // cout << "\nList Currencies Screen Will be here..............\n"; 
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        // cout << "\nFind Currrency Screen Will be here....................\n"; 
        clsFindCurrencyScreen::ShowFindCurrencyScreen(); 
    }

    static void _ShowUpdateRateScreen()
    {
        // cout << "\nUpate Rate Screen Will Be here................\n";
        clsUpdatCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCureencyCalculatorScreen()
    {
        // cout << "\nCurrency Calculator Screen Will be here......................\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen(); 
    }

    static void _PerformCurrencyExchangeMainScreenOption(enCurrencyExchangeMenuOptions Choice)
    {
        switch (Choice)
        {
        case enCurrencyExchangeMenuOptions::eListCurrencies:
        {
            clsUtil::ClearScreen();
            _ShowListCurrenciesScreen(); 
            _GoBackToCurrencyExchangeMenu();
            break;
        }

        case enCurrencyExchangeMenuOptions::eFindCurrency:
        {
            clsUtil::ClearScreen();
            _ShowFindCurrencyScreen(); 
            _GoBackToCurrencyExchangeMenu();
            break;
        }

        case enCurrencyExchangeMenuOptions::eUpdateRate:
        {
            clsUtil::ClearScreen();
            _ShowUpdateRateScreen(); 
            _GoBackToCurrencyExchangeMenu();
            break;
        }

        case enCurrencyExchangeMenuOptions::eCurrencyCalculator:
        {
            clsUtil::ClearScreen();
            _ShowCureencyCalculatorScreen(); 
            _GoBackToCurrencyExchangeMenu();
            break;
        }

        case enCurrencyExchangeMenuOptions::eMainMenu:
        {
            
        }
        

            
    }
}

    public :

    static void ShowCurrenciesMenu()
    {
        clsUtil::ClearScreen();
        _DrawScreenHeader("   Currency Exchange Main Screen");

        cout << "\n\n"; 
        cout << setw(33) << left << "" << "========================================\n";
        cout << setw(33) << left << "" << "\t Currency Exchange Menu\n";
        cout << setw(33) << left << "" << "========================================\n";
        cout << setw(32) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(32) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(32) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(32) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(32) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(33) << left << "" << "========================================\n";

        _PerformCurrencyExchangeMainScreenOption(enCurrencyExchangeMenuOptions(_ReadCurrencyExchangeMenuOption()));
    }
};