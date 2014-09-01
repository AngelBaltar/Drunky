/* 
 * File:   Debug.h
 * Author: angel
 *
 */

#ifndef DEBUG_H
#define	DEBUG_H

namespace Debug
{
    void debugButtonPressed();
    bool isDebugEnabled();
};

#define DEBUG(statements) \
do{\
    if(Debug::isDebugEnabled()){\
            statements;\
    }\
}while(0);

#endif	/* DEBUG_H */

