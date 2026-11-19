#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsCurrency.h"
#include "../Libraries/clsInputValidate.h"
class clsUpdatCurrencyRateScreen : protected clsScreen
{
private:

    static string _ReadCurrencyCode()
    {
        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code Not Found, Enter Again: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return CurrencyCode;
    }

    static float _ReadNewRate()
    {
        float NewRate = 0;

        cout << "\nPlease Enter New Rate: ";
        NewRate = clsInputValidate::ReadFloatNumber();

        return NewRate;
    }

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\n\nCurrency Card:\n";
        cout << "_____________________________________________\n\n";
        cout << "Country        : " << Currency.GetCountry() << endl;
        cout << "Currency Code  : " << Currency.GetCurrencyCode() << endl;
        cout << "Currency Name  : " << Currency.GetCurrencyName() << endl;
        cout << "Rate           : " << Currency.GetRate() << endl;
        cout << "_____________________________________________\n";
    }

public:
    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\t Update Currency Rate Screen");

        string CurrencyCode = _ReadCurrencyCode();
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        _PrintCurrencyCard(Currency);

        cout << "\nAre you sure you want update the rate of this Currency y/n? ";
        char answer;
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            cout << "\nUpdate Rate: \n";
            cout << "---------------------\n";

            Currency.UpdateRate(_ReadNewRate());
            
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrencyCard(Currency);
        }

        else
        {
            cout << "\nCurrency Rate Update Cancelled :-)\n";
        }
    }
};
