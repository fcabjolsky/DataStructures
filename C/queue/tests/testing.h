#ifndef TESTING_H
#define TESTING_H

#include <stdbool.h>

#define debug_print(fmt, ...)                                           \
    do { if (DEBUG_PRINT) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                  __LINE__, __func__, __VA_ARGS__);     \
    } while (0)


#define print_test(message, result) do { \
    real_print_test(message, result, __FILE__, __LINE__, #result); \
  } while (0)

void real_print_test(const char* message, bool ok,
		     const char* file, int line, const char* failed_expr);

int failure_count(void);

void print_header(const char* message);

#if defined(DEBUG) || !defined(CORRECTOR)
#define DEBUG_PRINT 1
#else
#define DEBUG_PRINT 0
#endif

#endif // TESTING_H
