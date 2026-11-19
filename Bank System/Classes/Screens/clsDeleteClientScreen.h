#pragma once 
#include <iostream>
#include "../Models/clsBankClient.h"
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
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

public:
    static void ShowDeleteClientScreen()
    {
        if (!CheckRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient Doesn't Exist, Enter Another Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClient(Client);

        cout << "\nAre You Sure You Want Delete This Client? Y/N : ";
        char answer = 'n';
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nClient Isn't Deleted\n";
            }
        }
        else
        {
            cout << "\nDelete Cancelled.\n";
        }
    }
};