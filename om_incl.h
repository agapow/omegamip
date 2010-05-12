/*
om_incl.h: global includes and definitions
*/

#ifndef _OM_INCL_
#define _OM_INCL_

// INCLUDES

#include <cassert>


// CONSTANTS & DEFINITIONS

#ifdef OM_DEBUG

	#include <iostream>
	#include <stdlib.h>
	
	// in non-debug versions, these statements evaluate to nothing
	
	// call like "ASSERT(chain_id < 20, "my message");"
	#define ASSERT(t,m)     if (!t) { cout << __FILE__ << ":" << __LINE__  << \
		": Assertion \" << "#t << "\" failed (" << m << ")" << std::endl; \
		std::exit(1); }
	
	// call like "PRINTVAR(foo);"
	#define PRINTVAR(var)   std::cout << __FILE__ << ":" << __LINE__ << \
		": '" << #var << "'=" << (var) << std::endl;
	
	// call like "MSG("here is my message");"
	#define MSG(msg)        std::cout << __FILE__ << ":" << __LINE__ << \
		": " << msg << std::endl;

	// call like "MPI_MSG("here is my message");"
	#define MPI_MSG(msg)        std::cout << "[" << proc_id << "," << \
		chain_id << "] " << __FILE__ << ":" << __LINE__ << \
		": " << msg << std::endl;
	
#else

	#define NDEBUG          # switch off asserts
	#define PRINTVAR(var)   # don't print vars
	#define MSG(msg)        # don't print messages
	#define MPI_MSG(msg)    # don't print messages

#endif // OM_DEBUG


#endif // _OM_INCL_
