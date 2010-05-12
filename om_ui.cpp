/*
om_ui.h: assorted ui and console io functions.
*/

#include <stdio>
#include <stdarg>

#include "om_incl.h"
#include "om_ui.h"

void MSG (char *arg_fmt, ... ) {
	std::va_list arg_ptr;
	std::va_start (arg_ptr, arg_fmt);

	std::cerr << "DEBUG:"


	          std::cerr << std::endl;

	va_end (arg_ptr);
}