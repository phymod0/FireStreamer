#include "ctest.h"
#include "defs.h"
#include "soapH.h"

#include <cstring>
#include <string>

using std::string;

BEFORE_EACH {}

AFTER_EACH {}

TEST(test_soap_request, soap)
{
    DESCRIPTION("Movie instance metadata creation");

    int soap_err;
    const string testTitle = "da cunjooring";

    // Test write
    ns1__MovieInstanceMetadata* createInput =
        soap_new_req_ns1__MovieInstanceMetadata(soap, testTitle);
    ns1__createMovieInstanceMetadataByIdResponse createOutput;
    soap_err = soap_call_ns1__createMovieInstanceMetadataById(
        soap,
        APPLICATION_SERVER_ENDPOINT,
        NULL,
        createInput,
        createOutput);
    ASSERT_TRUE(
        SOAP_OK == soap_err,
        "Movie instance metadata create operation returns success");
    ASSERT_TRUE(
        1 == createOutput.movieInstanceId,
        "Returned movie instance ID must be equal to 1");

    // Get value back in a new request
    ns1__getMovieInstanceMetadataByIdResponse getOutput;
    soap_err = soap_call_ns1__getMovieInstanceMetadataById(
        soap,
        APPLICATION_SERVER_ENDPOINT,
        NULL,
        1,
        getOutput);
    ASSERT_TRUE(
        SOAP_OK == soap_err,
        "Movie instance metadata get operation returns success");
    ns1__MovieInstanceMetadata* mimResult = getOutput.movieInstanceMetadata;
    ASSERT_NOT_NULL(
        mimResult,
        "Existing instance metadata should be returned from server");
    ASSERT_TRUE(
        testTitle == mimResult->title,
        "Returned title must match what was created");

#if 0
    if (soap_err != SOAP_OK) {
        soap_print_fault(soap, stderr);
    }
#endif
}

TEST_SUITE(test_soap_request)
