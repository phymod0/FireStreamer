#ifndef CTEST_H
#define CTEST_H

#include <stdbool.h>
#include <stdlib.h>
#include <sys/cdefs.h>

#include "soap/soapH.h"

#define MAX_CHECKNAMES_PER_UNIT 256
#define N_RUNS_PER_TEST         1
#define PRINT_WIDTH             64

struct test_result;
typedef struct test_result test_result_t;

typedef void (*test_t)(struct soap* soap_ctx, test_result_t* result);
typedef void (*test_before_hook_t)(test_result_t* result);
typedef void (*test_after_hook_t)(void);

void __ctest_reserved_before_test_hook(test_result_t* result);
void __ctest_reserved_after_test_hook(void);
void __ctest_reserved_global_before_test_hook(test_result_t* result);
void __ctest_reserved_global_after_test_hook(void);

void test_name(test_result_t* result, const char* name);
void test_acheck(test_result_t* result, bool check);
void test_check(test_result_t* result, const char* name, bool check);
int test_run(
    const test_t* tests,
    size_t n_tests,
    test_before_hook_t before_hook,
    test_after_hook_t after_hook,
    test_before_hook_t global_before_hook,
    test_after_hook_t global_after_hook,
    const char* module_name);

#define TEST_DEFINE(name, soap_ctx, result)                                    \
    __attribute_used__ void name(struct soap* soap_ctx, test_result_t* result)
#define BEFORE_EACH                                                            \
    void __ctest_reserved_before_test_hook(                                    \
        __attribute__((unused)) test_result_t* __ctest_reserved_result)
#define AFTER_EACH void __ctest_reserved_after_test_hook(void)
#define GLOBAL_BEFORE_EACH                                                     \
    void __ctest_reserved_global_before_test_hook(                             \
        __attribute__((unused)) test_result_t* __ctest_reserved_result)
#define GLOBAL_AFTER_EACH void __ctest_reserved_global_after_test_hook(void)
// Recommend using these macros instead of calling functions directly
#define TEST(name, soap_ctx)                                                   \
    TEST_DEFINE(name, soap_ctx, __ctest_reserved_result)
#define DESCRIPTION(desc) test_name(__ctest_reserved_result, desc);
#define ASSERT_TRUE(cond, desc)                                                \
    test_check(__ctest_reserved_result, desc, (cond))
#define ASSERT_FALSE(cond, desc)                                               \
    test_check(__ctest_reserved_result, desc, !(cond))
#define FAIL(desc) test_check(__ctest_reserved_result, desc, false)
#define TEST_SUITE(...)                                                        \
    int main(void)                                                             \
    {                                                                          \
        test_t test_fns[] = {__VA_ARGS__};                                     \
        const size_t n_tests = sizeof test_fns / sizeof test_fns[0];           \
        return test_run(                                                       \
            test_fns,                                                          \
            n_tests,                                                           \
            __ctest_reserved_before_test_hook,                                 \
            __ctest_reserved_after_test_hook,                                  \
            __ctest_reserved_global_before_test_hook,                          \
            __ctest_reserved_global_after_test_hook,                           \
            __FILE__);                                                         \
    }

#endif /* CTEST_H */
