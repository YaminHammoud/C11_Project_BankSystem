#pragma once 
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Models/clsBankClient.h"

using namespace std; 

class clsClientListScreen : protected clsScreen 
{
    private :
        static void _PrintClientRecord(clsBankClient Client)
        {
            cout << setw(8) << left << "";
            cout << "| " << left << setw(15) << Client.AccountNumber();
            cout << "| " << left << setw(20) << Client.FullName();
            cout << "| " << left << setw(12) << Client.GetPhone();
            cout << "| " << left << setw(20) << Client.GetEmail();
            cout << "| " << left << setw(10) << Client.GetPinCode();
            cout << "| " << left << setw(12) << Client.GetAccountBalance();
        }

    public:
        static void ShowClientsList()
        {

            if (!CheckRights(clsUser::enPermissions::pListClients))
            {
                return; 
            }

            vector<clsBankClient> vClients = clsBankClient::GetClientsList();

            string Title = "\t  Client List Screen";
            string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s).";

            _DrawScreenHeader(Title, SubTitle);

            cout << "\n" << setw(8) << left << "" <<"---------------------------------------------------------------------------------------------------------\n";

            cout << setw(8) << left << "";
            cout << "| " << left << setw(15) << "Account Number";
            cout << "| " << left << setw(20) << "Client Name";
            cout << "| " << left << setw(12) << "Phone";
            cout << "| " << left << setw(20) << "Email";
            cout << "| " << left << setw(10) << "Pin Code";
            cout << "| " << left << setw(12) << "Balance";

            cout <<"\n" << setw(8) << left << "" << "---------------------------------------------------------------------------------------------------------\n";

            if (vClients.size() == 0)
            {
                cout << "\n\t\t\t\tSorry, There Is No Clients In System :-(\n\n";
            }
            else
            {
                for (clsBankClient &C : vClients)
                {
                   _PrintClientRecord(C);
                    cout << "\n";
                }
            }

            cout << setw(8) << left << "" << "---------------------------------------------------------------------------------------------------------\n";
        }
};
