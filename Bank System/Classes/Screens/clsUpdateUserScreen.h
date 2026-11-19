#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "../Models/clsUser.h"
#include "../Libraries/clsInputValidate.h"
class clsUpdateUserScreen: protected clsScreen
{
    private :
        static void _ReadUserInfo(clsUser &User)
        {
            cout << "\nEnter FirstName: ";
            User.SetFirstName(clsInputValidate::ReadString());

            cout << "\nEnter LastName: ";
            User.SetLastName(clsInputValidate::ReadString());

            cout << "\nEnter Email: ";
            User.SetEmail(clsInputValidate::ReadString());

            cout << "\nEnter Phone: ";
            User.SetPhone(clsInputValidate::ReadString());

            cout << "\nEnter Password: ";
            User.SetPassword(clsInputValidate::ReadString());

            cout << "\nEnter Permission: ";
            User.SetPermissions(_ReadPermissionsToSet());
        }

        static void _PrintUser(clsUser User)
        {
            cout << "\nUser Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << User.GetFirstName();
            cout << "\nLastName    : " << User.GetLastName();
            cout << "\nFull Name   : " << User.FullName();
            cout << "\nEmail       : " << User.GetEmail();
            cout << "\nPhone       : " << User.GetPhone();
            cout << "\nUser Name   : " << User.GetUserName();
            cout << "\nPassword    : " << User.GetPassword();
            cout << "\nPermissions : " << User.GetPermissions();
            cout << "\n___________________\n";
        }

        static int _ReadPermissionsToSet()
        {

            int Permissions = 0;
            char Answer = 'n';

            cout << "\nDo you want to give full access? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                return -1;
            }

            cout << "\nDo you want to give access to : \n ";

            cout << "\nShow Client List? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {

                Permissions += clsUser::enPermissions::pListClients;
            }

            cout << "\nAdd New Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "\nDelete Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "\nUpdate Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pUpdateClients;
            }

            cout << "\nFind Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pFindClient;
            }

            cout << "\nTransactions? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pTransactions;
            }

            cout << "\nManage Users? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pManageUsers;
            }

            cout << "\nShow Login Register? y/n? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pShowLogInRegister;
            }
            
            return Permissions;
        }

    public : 

    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t  Update User Screen"); 

        string UserName = "";

        cout << "\nPlease Enter User Name: "; 
        UserName= clsInputValidate::ReadString(); 

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString(); 
        }

        clsUser user1 = clsUser::Find(UserName); 
        _PrintUser(user1); 

        cout << "\nAre you sure you want update this user y/n? ";
        char answer = 'n';
        cin >> answer; 

        if (toupper(answer) == 'Y')
        {
            cout << "\n\nUpdate User Info: ";
            cout << "\n------------------\n"; 
            _ReadUserInfo(user1);
            
            clsUser::enSaveResults SaveResult;
            SaveResult = user1.Save();
            
            switch (SaveResult)
            {
                case clsUser::enSaveResults::svSucceeded : 
                {
                    cout << "\nUser Updated Succesfully :-)\n"; 
                    _PrintUser(user1); 
                    break; 
                }

                case clsUser::enSaveResults::svFaildEmptyObject:
                {
                    cout << "Update Faild, Empty Object :-(\n";
                    break;
                }
            }
        }
        else 
        {
            cout << "\nUpdate Cancelled.\n"; 
        }
    }
};