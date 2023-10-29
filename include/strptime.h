#ifndef _LIBOB_STRPTIME_H_
#define _LIBOB_STRPTIME_H_

#include <time.h>

/* BEGIN_DECLS */
#ifdef __cplusplus
extern "C" {
#endif

const char* strptime(const char* source, const char* format, struct tm* tp);

/* END_DECLS */
#ifdef __cplusplus
}
#endif

#endif /* _LIBOB_STRPTIME_H_ */