#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsCurrency.h"
#include "../Libraries/clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static string _ReadCurrencyCode(string Message)
    {
        string CurrencyCode = "";

        cout << Message ;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code Not Found, Enter Again: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return CurrencyCode;
    }

    static float _ReadAmount()
    {
        float amount = 0;

        cout << "\nPlease Enter Amount to Exchange: ";
        amount = clsInputValidate::ReadFloatNumber();

        return amount;
    }

    static void _PrintCurrencyCard(clsCurrency Currency , string Title = "CurrencyCard: ")
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________________________\n\n";
        cout << "Country        : " << Currency.GetCountry() << endl;
        cout << "Currency Code  : " << Currency.GetCurrencyCode() << endl;
        cout << "Currency Name  : " << Currency.GetCurrencyName() << endl;
        cout << "Rate           : " << Currency.GetRate() << endl;
        cout << "_____________________________________________\n";
    }

    static clsCurrency _GetCurrency (string Message)
    {
        string CurrencyCode = _ReadCurrencyCode(Message);

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        return Currency;
    }

    static void _PrintCurrencyCalculationsResluts(float amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1,"Converting From: ");
        float AmountInUSD = Currency1.ConvertToUSD(amount);

        cout << "\n";

        cout << amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInUSD << " USD";

        if (Currency2.GetCurrencyCode() == "USD")
            return;

        _PrintCurrencyCard(Currency2,"\nConverting From USD To: ");

        float AmountInCurrency2 = Currency1.ConvertToAnotherCurrency(amount, Currency2);

        cout << amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode();
    }

    public :

    static void ShowCurrencyCalculatorScreen()
    {
        char answer = 'Y';

        while (toupper(answer) == 'Y')
        {

            clsUtil::ClearScreen();
            _DrawScreenHeader("\t Currency Calculator Screen");

            clsCurrency Currency1 = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency Currency2 = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCurrencyCalculationsResluts(Amount, Currency1, Currency2);

            cout << "\n\nDo You want to perform another calculations y/n? ";
            cin >> answer;
        }
    }
};