/*
om_incl.h: global includes and definitions
*/

#ifndef _OM_INCL_
#define _OM_INCL_

#include <cassert>
#include <iostream>

#define PRINTVAR(var) std::cout << __FILE__ << ":" << __LINE__ << ": '" << \
	#var << "'=" << (var) << std::endl;

#define MSG(msg) std::cout << __FILE__ << ":" << __LINE__ << ": '" << msg << \
	std::endl;

#endif
