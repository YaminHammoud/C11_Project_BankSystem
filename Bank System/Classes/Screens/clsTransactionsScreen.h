#pragma once 
#include <iostream>
#include "../Libraries/clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

class clsTransactonsScreen : protected clsScreen
{
    private : 

    enum enTransactionMenuOptions{
        eDeposit = 1, 
        eWithdraw=2,
        eShowTotalBalances=3,
        eTransfer = 4,
        eTransferLog = 5,
        eShowMainMenu= 6
    };

    static short _ReadTransactionMenuOption ()
    {
        

        cout << endl  << setw(33) << left << "" << "Choose What do you want to do [1 to 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1,6,"Please Enter a Number Between 1 and 6: ");

        return choice;
    }

    static void _GoBackToTransactionsMenu ()
    {
        cout << setw(33) << left << "" << "\nPress any key to go back to Transactions Menu...";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        cin.get();                                                     // Wait for user input

        ShowTransactionMenu();
    }

    static void _ShowDepositScreen ()
    {
        // cout << "\nDeposit Screen Will be here........\n";
        clsDepositScreen::ShowDepositScreen();  
        }

    static void _ShowWithdrawScreen ()
    {
        // cout << "\nWithdraw Screen Will be here.............\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        // cout << "\nBalances Screen Will be here.............\n";
        clsTotalBalances::ShowTotalBalances(); 
    }

    static void _ShowTransferScreen()
    {
        // cout << "\nTransfer Screen Will Be Here............\n";
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        // cout << "\nTransfer Log Screen Will be here.....................\n";
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerformTransactinMenuOption(enTransactionMenuOptions TransactionMenuOption)
    {
        switch (TransactionMenuOption)
        {
            case enTransactionMenuOptions::eDeposit : 
            {
                clsUtil::ClearScreen();
                _ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break; 
            }

            case enTransactionMenuOptions::eWithdraw: 
            {
                clsUtil::ClearScreen();
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break; 
            }

            case enTransactionMenuOptions::eShowTotalBalances: 
            {
                clsUtil::ClearScreen();
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionMenuOptions::eTransfer: 
            {
                clsUtil::ClearScreen();
                _ShowTransferScreen(); 
                _GoBackToTransactionsMenu();
                break; 
            }

            case enTransactionMenuOptions::eTransferLog:
            {
                clsUtil::ClearScreen(); 
                _ShowTransferLogScreen(); 
                _GoBackToTransactionsMenu();
                break;
            }

            case enTransactionMenuOptions::eShowMainMenu:
            {

            }
        }
    }

    public :

    static void ShowTransactionMenu()
    {

        if (!CheckRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }
        clsUtil::ClearScreen();

        _DrawScreenHeader("\t Transactins Screen");

        cout << endl << setw(33) << left << "" << "==========================================\n";
        cout << setw(33) << left << "" << "\t\tTransaction Menu\n";
        cout << setw(33) << left << "" << "==========================================\n\n";
        cout << setw(33) << left << "" << "\t[1] Deposit.\n";
        cout << setw(33) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(33) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(33) << left << "" << "\t[4] Transfer.\n";
        cout << setw(33) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(33) << left << "" << "\t[6] Main Menu.\n\n";

        cout << setw(33) << left << "" << "==========================================";

        _PerformTransactinMenuOption(enTransactionMenuOptions(_ReadTransactionMenuOption()));
    }
};