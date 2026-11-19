#pragma once 

#include <iostream>
#include "clsScreen.h"
#include "../Libraries/clsInputValidate.h"
#include "../Models/clsBankClient.h"

class clsWithdrawScreen: protected clsScreen
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

        static string _ReadAccountNumber()
        {
            string AccountNumber;

            cout << "\nPlease Enter Client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();

            return AccountNumber;
        }

    public:
    
        static void ShowWithdrawScreen()
        {
            clsUtil::ClearScreen();

            _DrawScreenHeader("\t   Withdraw Screen");

            string AccountNumber = _ReadAccountNumber();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nClient With Account Number [" << AccountNumber << "] does not found.\n";

                AccountNumber = _ReadAccountNumber();
            }

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            _PrintClient(Client1);

            double amount = 0;
            cout << "\nPlease Enter Amount To Withdraw: ";
            amount = clsInputValidate::ReadDblNumber();

            char answer = 'n';

            cout << "\nAre you sure you want to perform this transaction? [y/n] ";
            cin >> answer;

            if (answer == 'y' || answer == 'Y')
            {
                if (Client1.Withdraw(amount))
                {
                    cout << "\nAmount Withdraw Successfully.\n";
                    cout << "\nNew Balance is: " << Client1.GetAccountBalance() << endl;
                }
                else 
                {
                    cout << "\nCannot withdraw, Insuffecient Balance!\n";
                    cout << "\nAmount to withdraw is: " << amount;
                    cout << "\nYour Balance is: "<< Client1.GetAccountBalance(); 

                }
            }

            else
            {
                cout << "\nOperation Was Cancelled.\n";
            }
        }
};