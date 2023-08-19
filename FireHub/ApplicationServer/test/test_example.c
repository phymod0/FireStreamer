#include "ctest.h"
#include "defs.h"
#include "soapH.h"
#include <string.h>

#if 0

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

static int call() {
    // Create and initialize the soap instance
    struct soap *soap = soap_new();
    soap_init(soap);

    // Prepare the input parameters
    // (Replace these types and variables with your own)

    // Call the web service operation

    // Check the result for errors

    // Clean up the soap instance
    soap_destroy(soap);
    soap_end(soap);
    soap_free(soap);

    return 0;
}

#endif

BEFORE_EACH {}

AFTER_EACH {}

TEST(test_soap_request, soap)
{
    DESCRIPTION("Movie instance metadata creation success");

    int soap_err;
    ns1__MovieInstanceMetadata* input =
        soap_new_req_ns1__MovieInstanceMetadata(soap, "Fuck you");
    ns1__createMovieInstanceMetadataByIdResponse output;
    soap_err = soap_call_ns1__createMovieInstanceMetadataById(
        soap,
        APPLICATION_SERVER_ENDPOINT,
        NULL,
        input,
        output);
    ASSERT_TRUE(
        SOAP_OK == soap_err,
        "Movie instance metadata create operation returns success");
    ASSERT_TRUE(
        786 == output.movieInstanceId,
        "Returned movie instance ID must be equal to 786");
#if 0
    if (soap_err != SOAP_OK) {
        soap_print_fault(soap, stderr);
    }
#endif
}

TEST_SUITE(test_soap_request)
