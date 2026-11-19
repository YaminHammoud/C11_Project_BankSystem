#pragma once 

#include <iostream> 
#include <iomanip>
#include "clsScreen.h"
#include "../Models/clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.GetCountry();
        cout << "| " << left << setw(10) << Currency.GetCurrencyCode();
        cout << "| " << left << setw(30) << Currency.GetCurrencyName();
        cout << "| " << left << setw(10) << Currency.GetRate() << "\n";
    }

    public: 

    static void ShowCurrenciesListScreen()
    {
        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "\t Currencies List Screen";
        string SubTitle = "\t  (" + to_string(vCurrencies.size()) + ") Currency(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "__________________________________________________________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(30) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)\n";
        cout << setw(8) << left << "" << "__________________________________________________________________________________________\n\n";

        if (vCurrencies.size() == 0)
        {
            cout << setw(33) << left << "" << "No Currencies Available In the System!";
            return; 
        }

        for (clsCurrency C : vCurrencies)
        {
            _PrintCurrencyRecordLine(C);
        }
        cout << setw(8) << left << "" << "_______________________________________________________________________________\n\n";
    }
};