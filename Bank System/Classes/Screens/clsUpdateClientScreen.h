#pragma once 

#include <iostream>
#include "clsScreen.h"
#include "../Models/clsBankClient.h"
#include "../Libraries/clsInputValidate.h"




class clsUpdateClientScreen : protected clsScreen
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

    public : 

    static void ShowUpdateClientScreen ()
    {
        if (!CheckRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        _DrawScreenHeader("\t Update Client Screen");

        
            cout << "\nEnter Client Account Number: ";
            string AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nNo Client Found, Enter Another Account Number: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient Client = clsBankClient::Find(AccountNumber);

            _PrintClient(Client);

            cout << "\nAre you sure you want to update this client ? y/n? ";
            char answer = 'n';
            cin >> answer; 

            if (answer == 'Y' || answer == 'y')
            {

                cout << "\nUpdate Client Info: \n";
                cout << "\n____________________\n";
                _ReadClientInfo(Client);

                clsBankClient::enSaveResults SaveResult;

                SaveResult = Client.Save();

                switch (SaveResult)
                {
                case clsBankClient::enSaveResults::svFaildEmptyObject:
                    cout << "\n Save Failed Empty Client :-(\n";

                    break;

                case clsBankClient::svSucceeded:

                    cout << "\nClient Update Successfully, Updated Client: \n";

                    _PrintClient(Client);

                    break;
                }
            }
            else 
            {
                cout << "\nUpdate Cancelled.\n";
            }
    }
};