#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Libraries/clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1
    };

    enMode _Mode;
    string _Country;
    string _CurrencyName;
    string _CurrencyCode;
    float _Rate;

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string DataLine = "";

        DataLine += Currency._Country + Seperator;
        DataLine += Currency._CurrencyCode + Seperator;
        DataLine += Currency._CurrencyName + Seperator;
        DataLine += to_string(Currency._Rate);

        return DataLine;
    }

    static clsCurrency _ConvertLineToCurrencyObject(string DataLine, string Seperator = "#//#")
    {
        vector<string> vCurrencyData = clsString::Split(DataLine, Seperator);

        return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
    }

    static vector<clsCurrency> _LoadCurrencyDataFromFile()
    {
        vector<clsCurrency> vCurrencies;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                vCurrencies.push_back(Currency);
            }

            MyFile.close();
        }

        return vCurrencies;
    }

    static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies)
    {
        fstream Myfile;

        Myfile.open("Currencies.txt", ios::out);

        if (Myfile.is_open())
        {
            string Line;

            for (clsCurrency C : vCurrencies)
            {
                Line = _ConvertCurrencyObjectToLine(C);
                Myfile << Line << endl;
            }

            Myfile.close();
        }
    }

    void _Update()
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();

        for (clsCurrency &C : vCurrencies)
        {
            if (C.GetCurrencyCode() == GetCurrencyCode())
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(vCurrencies);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    // Constructor
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    // Seteers And Getters:

    string GetCountry() { return _Country; }
    string GetCurrencyCode() { return _CurrencyCode; }
    string GetCurrencyName() { return _CurrencyName; }
    float GetRate() { return _Rate; }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream Myfile;

        Myfile.open("Currencies.txt", ios::in);

        if (Myfile.is_open())
        {
            string DataLine;
            while (getline(Myfile, DataLine))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(DataLine);

                if (Currency.GetCurrencyCode() == CurrencyCode)
                {
                    Myfile.close();
                    return Currency;
                }

            }
            Myfile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream Myfile;

        Myfile.open("Currencies.txt", ios::in);

        if (Myfile.is_open())
        {
            string DataLine;
            while (getline(Myfile, DataLine))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(DataLine);

                if (clsString::UpperAllString(Currency.GetCountry()) == Country)
                {
                    Myfile.close();
                    return Currency;
                }
            }

            Myfile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyDataFromFile();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency Currency = FindByCode(CurrencyCode);

        return (!Currency.IsEmpty());
    }

    float ConvertToUSD (float amount)
    {
        return (float)(amount/ _Rate); 
    }

    float ConvertToAnotherCurrency (float amount , clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(amount); 

        if (Currency2.GetCurrencyCode() == "USD")
            return AmountInUSD;

        return (float)(AmountInUSD * Currency2.GetRate()); 
    }
};