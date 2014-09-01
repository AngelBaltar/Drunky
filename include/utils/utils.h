/* 
 * File:   utils.h
 * Author: angel
 *
 * Created on 2 de julio de 2014, 11:13
 */

#ifndef UTILS_H
#define	UTILS_H

#include <sstream>

#define STR1(z) #z
#define STR(z) STR1(z)

static inline std::string int2string(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

#endif	/* UTILS_H */

