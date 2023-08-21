#include "ctest.h"
#include "defs.h"
#include "soapH.h"

#include <cstring>

BEFORE_EACH {}

AFTER_EACH {}

TEST(test_soap_request, soap)
{
    DESCRIPTION("Movie instance metadata creation success");

    int soap_err;
    ns1__MovieInstanceMetadata* input =
        soap_new_req_ns1__MovieInstanceMetadata(soap, "Children of the wheat");
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
        1 == output.movieInstanceId,
        "Returned movie instance ID must be equal to 1");
#if 0
    if (soap_err != SOAP_OK) {
        soap_print_fault(soap, stderr);
    }
#endif
}

TEST_SUITE(test_soap_request)
