#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Libraries/clsString.h"
#include "../Libraries/clsDate.h"
#include <vector>
#include "../Libraries/clsUtil.h"
#include <fstream>

using namespace std;

class clsUser : public clsPerson
{
public:
    struct stLoginRegisterRecord; // we write this here because we will use it in private section before we define it in public section

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    // Important Methods

    stLoginRegisterRecord static _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegister ;
        vector<string> vLoginRegisters = clsString::Split(Line, Seperator);

        LoginRegister.DateTime = vLoginRegisters[0];
        LoginRegister.UserName = vLoginRegisters[1];
        LoginRegister.Password = clsUtil::DecryptText(vLoginRegisters[2]);
        LoginRegister.Permissions = stoi(vLoginRegisters[3]);

        return LoginRegister;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";

        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(_Password) + Seperator; 
        LoginRecord += to_string(_Permissions); 

        return LoginRecord;
    }

    static clsUser _ConvertLineToUserObject(string Line , string Seperator = "#//#")
    {
        vector <string> vUserData;

        vUserData = clsString::Split(Line,Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                       vUserData[3], vUserData[4],clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static clsUser _GetEmptyUserObject ()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0); 
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers; 

        fstream Myfile; 
        Myfile.open("Users.txt", ios::in); 

        if (Myfile.is_open())
        {
            string Line;

            while (getline(Myfile,Line))
            {
                clsUser user = _ConvertLineToUserObject(Line);
                vUsers.push_back(user);
            }

            Myfile.close(); 
        }

        return vUsers; 
    }

    void _AddDataLineToFile(string DataLine)
    {
        fstream Myfile;

        Myfile.open("Users.txt", ios::out | ios::app); 

        if (Myfile.is_open())
        {
            Myfile << DataLine << endl;

            Myfile.close();
        }
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.GetFirstName()+ Seperator;
        UserRecord += User.GetLastName() + Seperator;
        UserRecord += User.GetEmail() + Seperator;
        UserRecord += User.GetPhone() + Seperator;
        UserRecord += User._UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.GetPassword()) + Seperator;
        UserRecord += to_string(User._Permissions);

        return UserRecord;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream Myfile; 

        Myfile.open("Users.txt",ios::out);
        string DataLine; 

        if (Myfile.is_open())
        {
            for (clsUser & user : vUsers)
            {
                if (!user.MarkedForDelete())
                {

                    DataLine = _ConverUserObjectToLine(user);
                    Myfile << DataLine << endl;
                }
            }

            Myfile.close(); 
        }
    }

    void _Update()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser &user : vUsers)
        {
            if (user._UserName == _UserName)
            {
                user = *this; 
                break; 
            }
        }

        _SaveUsersDataToFile(vUsers); 
    }

public:

    enum enPermissions{
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTransactions = 32,
        pManageUsers = 64,
        pShowLogInRegister = 128
    };

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions; 
    };

    // Constructor
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDelete()
    {
        return _MarkedForDelete;
    }

    // Set And Get
    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    string GetPassword()
    {
        return _Password;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    // Important Methods
    static clsUser Find(string UserName)
    {
        fstream Myfile;

        Myfile.open("Users.txt", ios::in); // read mode.

        if (Myfile.is_open())
        {
            string Line;

            while (getline(Myfile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);

                if (User._UserName == UserName)
                {
                    Myfile.close();
                    return User;
                }
            }
        }

        return _GetEmptyUserObject(); 
    }

    static clsUser Find (string UserName, string Password)
    {
        fstream Myfile;

        Myfile.open("Users.txt", ios::in); // read mode.

        if (Myfile.is_open())
        {
            string Line;

            while (getline(Myfile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);

                if (User._UserName == UserName && User._Password == Password)
                {
                    Myfile.close();
                    return User;
                }
            }
        }

        return _GetEmptyUserObject(); 
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults Save ()
    {
        switch (_Mode)
        {
            case enMode::EmptyMode : 
            {
                if (IsEmpty())
                    return enSaveResults::svFaildEmptyObject;
            }

            case enMode::UpdateMode: 
            {
                _Update();
                return enSaveResults::svSucceeded; 
            }

            case enMode::AddNewMode: 
            {
                if (IsUserExist(_UserName))
                    return enSaveResults::svFaildUserExists;
                
                else 
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode; 
                    return enSaveResults::svSucceeded;
                }
            }

            }
    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    bool Delete ()
    {
        vector<clsUser> _vUsers;

        _vUsers = _LoadUsersDataFromFile(); 

        for (clsUser & U : _vUsers)
        {
            if (U._UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break; 
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static vector <clsUser> GetUsersList ()
    {
        return _LoadUsersDataFromFile(); 
    }

    bool CheckAccessPerimission(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::eAll)
            return true;
        
        if ((this->_Permissions & Permission) == Permission)
            return true;
        
        else
            return false; 
    }

    void RegisterLogIn ()
    {
        string stDataLine = _PrepareLogInRecord();

        fstream Myfile;
        Myfile.open("LoginRegister.txt", ios::out | ios::app);

        if (Myfile.is_open())
        {
            Myfile << stDataLine << endl;

            Myfile.close();
        }
    }

    static vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecords;

        string Line;
        stLoginRegisterRecord LoginRegisterRecord;

        fstream Myfile;

        Myfile.open("LoginRegister.txt", ios::in);

        if (Myfile.is_open())
        {
            while (getline(Myfile,Line))
            {
                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecords.push_back(LoginRegisterRecord); 
            }

            Myfile.close();
        }

        return vLoginRegisterRecords;
    }
};