#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Libraries/clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
    public:
        struct stTransferLogRecord;

    private:
        enum enMode
        {
            EmptyMode = 0,
            UpdateMode = 1,
            AddNewMode = 2
        };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClientsData;

        fstream MyFile;

        

        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line; 

            while (getline(MyFile,Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClientsData.push_back(Client);
            }

            MyFile.close();
        }

        return vClientsData;
    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClient = "";

        stClient = Client.GetFirstName() + Seperator;
        stClient += Client.GetLastName() + Seperator;
        stClient += Client.GetEmail() + Seperator;
        stClient += Client.GetPhone() + Seperator;
        stClient += Client.AccountNumber() + Seperator;
        stClient += Client.GetPinCode() + Seperator;
        stClient += to_string(Client.GetAccountBalance());

        return stClient;
    }

    static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        string Line; 
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);


        if (MyFile.is_open())
        {
            for (clsBankClient &C : vClients)
            {
                if (!C._MarkedForDelete)
                {
                    Line = _ConvertClientObjectToLine(C);

                    MyFile << Line << endl ; 
                }
              
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                

                break; 
            }
        }
        _SaveClientsDataToFile(vClients);
        }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _AddDataLineToFile(string Line)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << Line << endl;

            MyFile.close();
        }

        
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    string _PrapareTransferLogRecord(float Amount, clsBankClient DestinationClient,string UserName, string Seperator= "#//#")
    {
        string stTransferLog = "";

        stTransferLog += clsDate::GetSystemDateTimeString() + Seperator;
        stTransferLog += AccountNumber() + Seperator;
        stTransferLog += DestinationClient.AccountNumber() + Seperator;
        stTransferLog += to_string(Amount) + Seperator;
        stTransferLog += to_string(_AccountBalance) + Seperator;
        stTransferLog += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        stTransferLog += UserName; 

        return stTransferLog; 
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient , string UserName)
    {
        string stTransferLog = _PrapareTransferLogRecord(Amount, DestinationClient,  UserName);

        fstream Myfile;
        Myfile.open("TransferLog.txt", ios::out | ios::app);

        if (Myfile.is_open())
        {
            Myfile << stTransferLog << endl;

            Myfile.close();
        }
    }

    static stTransferLogRecord _ConvertTransferLogLineToRecord(string line)
    {
        stTransferLogRecord TransferLogRecord; 
        vector <string> vTransferLog = clsString::Split(line,"#//#"); 

        TransferLogRecord.DateTime = vTransferLog[0];
        TransferLogRecord.SourceAccNumber = vTransferLog[1];
        TransferLogRecord.DestinationAccNumber = vTransferLog[2];
        TransferLogRecord.TransferAmount = stof(vTransferLog[3]);
        TransferLogRecord.srcBalanceAfter = stof(vTransferLog[4]);
        TransferLogRecord.destBalanceAfter = stof(vTransferLog[5]);
        TransferLogRecord.UserName = vTransferLog[6];

        return TransferLogRecord;
    }

public :

    struct stTransferLogRecord
    {
        string DateTime; 
        string SourceAccNumber; 
        string DestinationAccNumber;
        float TransferAmount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName; 
    };

    clsBankClient(enMode Mode, string FirstName, string LastName,
                  string Email, string Phone, string AccountNumber, string PinCode,
                  float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    // we cancelled print because there shouldn't be any UI in the object 

    /* void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
            cout << "\nFirstName   : " << GetFirstName();
            cout << "\nLastName    : " << GetLastName();
        cout << "\nFull Name   : " << FullName();
            cout << "\nEmail       : " << GetEmail();
            cout << "\nPhone       : " << GetPhone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";
    } */

    static clsBankClient Find(string AccountNumber)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExist = 2
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {

        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
            break;
        }

        case enMode::UpdateMode:
        {
            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            if (IsClientExist(AccountNumber()))
            {
                return enSaveResults::svFaildAccountNumberExist;
            }

            else
            {
                _AddNew();

                _Mode = enMode::UpdateMode;

                return enSaveResults::svSucceeded;
            }
        }
        default:
            return enSaveResults::svFaildEmptyObject;
            break; 
        }
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject (string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete ()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile(); 

        for (clsBankClient & C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break; 
            }
        }

        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true; 
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        double TotalBalances = 0;

        for (clsBankClient &C : vClients)
        {
            TotalBalances += C.GetAccountBalance();
        }

        return TotalBalances;
    }

    void Deposit(double amount)
    {
        _AccountBalance += amount;
        Save();
    }

    bool Withdraw (double Amount)
    {
        if (_AccountBalance >= Amount)
        {
            _AccountBalance -= Amount;
            Save();

            return true; 
        }

        return false; 
    }

    bool Transfer (float Amount , clsBankClient & DestinationClient , string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount); 
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);

        return true; 
    }

    static vector <stTransferLogRecord>  GetTransferLogList()
    {
        stTransferLogRecord TransferLogRecord; 
        vector <stTransferLogRecord> vTransferLogRecords;
        string DataLine; 

        fstream Myfile ; 
        Myfile.open("TransferLog.txt" , ios::in); 

        if (Myfile.is_open())
        {
            while (getline(Myfile,DataLine))
            {
                TransferLogRecord = _ConvertTransferLogLineToRecord(DataLine); 
                vTransferLogRecords.push_back(TransferLogRecord); 
            }

            Myfile.close(); 
        }

        return vTransferLogRecords; 
    }
};
