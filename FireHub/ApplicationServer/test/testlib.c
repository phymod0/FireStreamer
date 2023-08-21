#include "ctest.h"

#include <stdio.h>

GLOBAL_BEFORE_EACH
{
#ifndef TEST_DB_PATH
#error TEST_DB_PATH not defined
#endif /* TEST_DB_PATH */
    const char* testDBPath = TEST_DB_PATH;
    if (access(testDBPath, F_OK) != 0) {
        // Test DB doesn't exist
        return;
    } else if (remove(testDBPath) != 0) {
        fprintf(
            stderr,
            "FATAL: Failed to delete test database at %s\n",
            testDBPath);
        exit(1);
    }
}
