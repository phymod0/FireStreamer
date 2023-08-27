#include "ctest.h"
#include "defs.h"
#include "soapH.h"

#include <cstring>
#include <string>

using std::string;

BEFORE_EACH {}

AFTER_EACH {}

TEST(test_get_without_instances, soap)
{
    DESCRIPTION("retrieve movie instances with no added movies");

    // Try to get the metadata with ID 1
    int soap_err;
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
    ASSERT_NULL(
        mimResult,
        "Existing instance metadata returned by server should be null");

#if 0
    if (soap_err != SOAP_OK) {
        soap_print_fault(soap, stderr);
    }
#endif
}

TEST(test_create_single_movie_instance_metadata, soap)
{
    DESCRIPTION("single movie instance metadata creation");

    int soap_err;
    const string testTitle = "The Conjuring";

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
}

TEST(test_create_multiple_instances, soap)
{
    DESCRIPTION("creation of multiple instances");

    int soap_err;
    const string testTitle1 = "da cunjooring";
    const string testTitle2 = "random bollywood cringefest";

    ns1__MovieInstanceMetadata* createInput;
    ns1__createMovieInstanceMetadataByIdResponse createOutput;
    // Write first movie
    createInput = soap_new_req_ns1__MovieInstanceMetadata(soap, testTitle1);
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
    // Write second movie
    createInput = soap_new_req_ns1__MovieInstanceMetadata(soap, testTitle2);
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
        2 == createOutput.movieInstanceId,
        "Returned movie instance ID must be equal to 2");

    ns1__getMovieInstanceMetadataByIdResponse getOutput;
    ns1__MovieInstanceMetadata* mimResult;
    // Get first movie back in a new request
    soap_err = soap_call_ns1__getMovieInstanceMetadataById(
        soap,
        APPLICATION_SERVER_ENDPOINT,
        NULL,
        1,
        getOutput);
    ASSERT_TRUE(
        SOAP_OK == soap_err,
        "Movie instance metadata get operation returns success");
    mimResult = getOutput.movieInstanceMetadata;
    ASSERT_NOT_NULL(
        mimResult,
        "Existing instance metadata should be returned from server");
    ASSERT_TRUE(
        testTitle1 == mimResult->title,
        "Returned title must match what was created");
    // Get second movie back in a new request
    soap_err = soap_call_ns1__getMovieInstanceMetadataById(
        soap,
        APPLICATION_SERVER_ENDPOINT,
        NULL,
        2,
        getOutput);
    ASSERT_TRUE(
        SOAP_OK == soap_err,
        "Movie instance metadata get operation returns success");
    mimResult = getOutput.movieInstanceMetadata;
    ASSERT_NOT_NULL(
        mimResult,
        "Existing instance metadata should be returned from server");
    ASSERT_TRUE(
        testTitle2 == mimResult->title,
        "Returned title must match what was created");
}

TEST_SUITE(
    test_get_without_instances,
    test_create_single_movie_instance_metadata,
    test_create_multiple_instances)
