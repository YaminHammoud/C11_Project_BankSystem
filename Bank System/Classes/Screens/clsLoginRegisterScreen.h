#pragma once
#include <iostream>
#include <vector>
#include "../Models/clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << left << setw(33) << LoginRegisterRecord.DateTime;
        cout << "| " << left << setw(25) << LoginRegisterRecord.UserName;
        cout << "| " << left << setw(10) << LoginRegisterRecord.Password;
        cout << "| " << left << setw(12) << LoginRegisterRecord.Permissions << endl;
    }

public:

    static void ShowLoginRegisterScreen()
    {
        if (!CheckRights(clsUser::enPermissions::pShowLogInRegister))
            return;

        vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecords = clsUser::GetLoginRegisterList();

        string Title = "\tLogin Register List Screen\n";
        string SubTitle = "\t  (" + to_string(vLoginRegisterRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n"
             << endl;

        cout << setw(8) << left << "" << "| " << left << setw(33) << "Date/Time";
        cout << "| " << left << setw(25) << "UserName";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n"
             << endl;

        if (vLoginRegisterRecords.size() == 0)
        {
            cout << "\n\t\t There is no Records Available in System!\n";
            return;
        }

        for (auto &Record : vLoginRegisterRecords)
        {

            _PrintLoginRegisterRecordLine(Record);
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n"
             << endl;
    }
};