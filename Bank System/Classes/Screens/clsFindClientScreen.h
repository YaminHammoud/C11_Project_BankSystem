#pragma once 
#include <iostream>
#include "../Models/clsBankClient.h"
#include "../Libraries/clsInputValidate.h"
#include "clsScreen.h"

class clsFindClientScreen : protected clsScreen
{
private:
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

    public : 

    static void ShowFindClientScreen ()
    {

        if (!CheckRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        _DrawScreenHeader("\t Find Client Screen");

        cout << "\nEnter Client Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nNo Client Found, Enter Another Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }

        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client);
    }
};