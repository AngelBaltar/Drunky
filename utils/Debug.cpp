#include "utils/Debug.h"

static bool dbg_enabled=false;

void Debug::debugButtonPressed()
{
    dbg_enabled=!dbg_enabled;
}
 
bool Debug::isDebugEnabled()
{
    return dbg_enabled;
}