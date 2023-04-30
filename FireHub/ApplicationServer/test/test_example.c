#include <string.h>
#include "ctest.h"


static int add_ints(int a, int b)
{
	return a + b;
}


static void reverse(char* dest, const char* src)
{
	size_t len = strlen(src);
	for (size_t i=0; i<len; ++i)
		dest[i] = src[len - i - 1];
	dest[len] = '\0';
}


TEST_DEFINE(test_add_ints, res)
{
	TEST_AUTONAME(res);
	int a = 2, b = 3, sum = a + b;

	test_check(res, "Addition #1 succeeded", add_ints(-1, add_ints(a, b)) == sum - 1);
	test_check(res, "Addition #2 succeeded", add_ints(a, b) == sum);
	test_check(res, "Addition #3 succeeded", add_ints(add_ints(a, b), -1) == sum - 1);
}


TEST_DEFINE(test_str_reverse, res)
{
	test_name(res, "String reversal test");

	char arr[] = "Hello world!";
	char rev[sizeof arr];
	reverse(rev, arr);

	bool equal = true;
	size_t len = (sizeof arr) - 1;
	for (size_t i=0; i<len; ++i)
		if (arr[i] != rev[len-i-1]) {
			equal = false;
			break;
		}

	test_check(res, "Successfully reversed", equal);
}


TEST_START
(
	test_add_ints,
	test_str_reverse,
)
