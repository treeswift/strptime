#include "strptime.h"
#include "LibOb_strptime.h"

const char* strptime(const char* source, const char* format, struct tm* tp) {
    stTimeZone tz = LibOb_localTimeZone(NULL);
    return LibOb_strptime(source, format, tp, &tz);
}
