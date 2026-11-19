#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsBankClient.h"
#include "../Libraries/clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\n\nClient Card: ";
        cout << "\n----------------------------";
        cout << "\n\nFull Name  : " << Client.FullName();
        cout << "\nAcc. Number: " << Client.AccountNumber();
        cout << "\nBalance    : " << Client.GetAccountBalance();
        cout << "\n\n----------------------------\n\n";
    }

    static string _ReadAccountNumber(string Message = "\nPlease Enter Account Number: ")
    {
        string AccountNumber = "";
        cout << Message;
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not found, please enter another account number: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static float _ReadAmount(clsBankClient SourceClient)
    {

        cout << "\n\nPlease Enter Transfer Amount: ";
        float TransferAmount = clsInputValidate::ReadFloatNumber();

        while (TransferAmount > SourceClient.GetAccountBalance())
        {
            cout << "\nThe Amount Exceeded the balance, plese enter another amount: ";
            TransferAmount = clsInputValidate::ReadFloatNumber();
        }

        return TransferAmount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));
        _PrintClientCard(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "));
        _PrintClientCard(DestinationClient);

        float TransferAmount = _ReadAmount(SourceClient);

        cout << "\nAre you sure you want perform this transfer y/n? ";
        char answer;
        cin >> answer;

        if (toupper(answer) == 'Y')
        {
            if (SourceClient.Transfer(TransferAmount, DestinationClient, CurrentUser.GetUserName()))
            {
                cout << "\nTransfer Done Successfully.\n\n";
                _PrintClientCard(SourceClient);
                _PrintClientCard(DestinationClient);
            }
        }

        else
        {
            cout << "\nTransfer Cancelled.\n";
        }
    }
};