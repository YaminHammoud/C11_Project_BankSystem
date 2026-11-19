#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsCurrency.h"
#include "../Libraries/clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
    private : 
    enum enFindCurrencyMenuOptions
    {
        eFindByCode = 1, 
        eFindByCountry =2
        
    };

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________________________\n\n"; 
        cout << "Country        : " << Currency.GetCountry() << endl;
        cout << "Currency Code  : " << Currency.GetCurrencyCode() << endl;
        cout << "Currency Name  : " << Currency.GetCurrencyName() << endl;
        cout << "Rate           : " << Currency.GetRate() << endl;
        cout << "_____________________________________________\n";
    }

    static short _ReadCurrencyScreenChoice()
    {
        short choice = 0 ; 

        cout << "\nFind By: [1] Code or [2] Country? "; 
        choice = clsInputValidate::ReadShortNumberBetween(1,2);

        return choice; 
    }

    static string _ReadCurrencyCode ()
    {
        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        return CurrencyCode ; 
    }

    static string _ReadCountry()
    {
        string Country = "";

        cout << "\nPlease Enter Country: ";
        Country = clsInputValidate::ReadString();

        return Country;
    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (Currency.IsEmpty())
        {
            cout << "\nCurrency Is Not Found!\n";
        }
        else
        {
            cout << "\nCurrency Found Successfully :-)\n";
            _PrintCurrencyCard(Currency);
        }
    }

    static void _PerfromFindCurrencyScreenOpiton(enFindCurrencyMenuOptions choice)
    {
        switch (choice)
        {
        case enFindCurrencyMenuOptions::eFindByCode:
        {
            clsCurrency Currency = clsCurrency::FindByCode(_ReadCurrencyCode());
            _ShowResults(Currency);

            break;
        }

        case enFindCurrencyMenuOptions::eFindByCountry:
        {
            clsCurrency Currency = clsCurrency::FindByCountry(_ReadCountry());

            _ShowResults(Currency);

            break;
        }
        }
    }

    public :

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\tFind Currency Screen"); 

        _PerfromFindCurrencyScreenOpiton((enFindCurrencyMenuOptions)_ReadCurrencyScreenChoice());
    }
};