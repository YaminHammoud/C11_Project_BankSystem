#pragma once 

#include <iostream>
#include "clsScreen.h"
#include "../Libraries/clsUtil.h"
#include "../Models/clsBankClient.h"

class clsTotalBalances : protected clsScreen
{
private:
    static void PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << setw(20) << left << "" << "| " << left << setw(15) << Client.AccountNumber()
             << "| " << left << setw(40) << Client.FullName()
             << "| " << left << setw(12) << Client.GetAccountBalance()
             << "|" << endl;
    }

public:
    static void ShowTotalBalances ()
    {
        clsUtil::ClearScreen();

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t Total Balances Screen";
        string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n\n";

        cout << setw(20) << left << "" << string(74, '-') << endl;

        cout << setw(20) << left << "" << "| " << left << setw(15) << "Account Number"
             << "| " << left << setw(40) << "Client Name"
             << "| " << left << setw(12) << "Balance"
             << "|" << endl;
        cout << setw(20) << left << "" << string(74, '-') << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        for (auto &C : vClients)
        {
            PrintClientRecordBalanceLine(C); 
        }
        cout << setw(20) << left << "" << string(74, '-') << endl;

        cout << setw(25) << left << "" << "\t\t  Total Balances = " << TotalBalances ;

        cout << "\n" << setw(25) << left << ""  << "("<< clsUtil::NumberToText(TotalBalances) << ")";
    }
};
