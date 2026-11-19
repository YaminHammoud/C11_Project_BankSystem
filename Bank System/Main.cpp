#include <iostream>
#include "Classes/Screens/clsLoginScreen.h"
#include "Classes/Libraries/clsUtil.h"

using namespace std;






int main() 
{ 
    
      
    clsUtil::ClearScreen();
    cout << "\n";

    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break; 
        }
    }


    cout << endl;

    return 0;
}