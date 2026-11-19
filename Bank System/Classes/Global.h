#pragma once 

#include <iostream>
#include "Models/clsUser.h"

 clsUser CurrentUser = clsUser::Find("", ""); // this will return an empty object.
// We Created this file (library) unitl all the files and classes see the global variable I need, if We put the global variable in the main -> the class will not see it.

