#pragma once
#include <iostream>
#include <iomanip>
#include "../Global.h"
#include "../Libraries/clsDate.h"
#include "../Libraries/clsUtil.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
     
        cout << setw(33) << left << "" << "____________________________________\n\n";
        cout << setw(33) << left << "" << Title << "\n";
        
        if (SubTitle != "")
        {
            cout << "\t\t\t\t  " << SubTitle << endl;
        }
        
        cout << setw(33) << left << "" << "____________________________________\n\n";
        cout << setw(33) << left << "" << "User: " << CurrentUser.GetUserName() << "\n";
        cout << setw(33) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << "\n";
      
    }

    static bool CheckRights(clsUser::enPermissions Permisson)
    {
        if (!CurrentUser.CheckAccessPerimission(Permisson))
        {
            cout << "\t\t\t\t-------------------------------------------\n";
            cout << "\n\t\t\t\t  Access Denied! Contact your Admin\n";
            cout << "\t\t\t\t-------------------------------------------\n";

            return false;
        }

        else
            return true;
    }
};