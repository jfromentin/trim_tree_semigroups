#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>

using namespace std;

#ifndef GMAX
static const size_t g_max=60;
#else
static const size_t g_max=GMAX;
#endif


#endif
