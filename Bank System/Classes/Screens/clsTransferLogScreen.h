#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsBankClient.h"


class clsTransferLogScreen : protected clsScreen
{
    private : 

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << "" << "| " << setw(30) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(15) << left << TransferLogRecord.SourceAccNumber;
        cout << "| " << setw(15) << left << TransferLogRecord.DestinationAccNumber;
        cout << "| " << setw(12) << left << TransferLogRecord.TransferAmount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(12) << left << TransferLogRecord.UserName;
        cout << "\n";
    }



    public : 

    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t  (" + to_string(vTransferLogRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n";

        cout << setw(8) << "" << "___________________________________________________________________________________________________________________\n\n";
        cout << setw(8) << "" << "| " << setw(30) << left << "Date/Time";
        cout << "| " << setw(15) << left << "s.Acct";
        cout << "| " << setw(15) << left << "d.Acct";
        cout << "| " << setw(12) << left << "Amount";
        cout << "| " << setw(10) << left << "s.Balance";
        cout << "| " << setw(10) << left << "d.Balance";
        cout << "| " << setw(12) << left << "User"; 
        cout << "\n";
        cout << setw(8) << "" << "___________________________________________________________________________________________________________________\n\n";

        if (vTransferLogRecords.size() == 0)
            cout << "\t\t\tNo Transfer Log Records Found.";

        else
        {
            for (auto &TransferLogRecord : vTransferLogRecords)
            {
                _PrintTransferLogRecordLine(TransferLogRecord);
            }
        }

        cout << setw(8) << "" << "___________________________________________________________________________________________________________________\n\n";
    }
};