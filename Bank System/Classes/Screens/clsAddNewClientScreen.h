#pragma once 

#include <iostream> 
#include "clsScreen.h"
#include "../Models/clsBankClient.h"
#include "../Libraries/clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
{
    private : 

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter First Name: ";
        Client.SetFirstName(clsInputValidate::ReadString());
        cout << "\nEnter Last Name: ";
        Client.SetLastName(clsInputValidate::ReadString());
        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());
        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());
        cout << "\nEnter Pin Code: ";
        Client.SetPinCode(clsInputValidate::ReadString());
        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
    }

public:

    static void ShowAddNewClientScreen()
    {
        if (!CheckRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nEnter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is already exist, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nClient Added Successfully :-) : \n";
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\n Adding Failed, Empty Object :-(\n";
            break;
        }

        case clsBankClient::enSaveResults::svFaildAccountNumberExist:
        {
            cout << "\n Adding Failed, Account Number Is Exist :-( \n";
            break;
        }
        }
    }
};