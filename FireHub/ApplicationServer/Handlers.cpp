#include "soap/ApplicationServer.nsmap"
#include "soap/soapH.h"

#include <iostream>
#include <string>

#include "ApplicationServer.h"
#include "LoggerHelper.h"

#include <sqlite3.h>

using namespace std;

static inline ApplicationServer* getApplication(struct soap* soap)
{
    return (ApplicationServer*) soap->user;
}

int ns1__getMovieInstanceMetadataById(
    struct soap* soap,
    LONG64 movieInstanceId,
    struct ns1__getMovieInstanceMetadataByIdResponse& response
)
{
    const ApplicationServer* app = getApplication(soap);
    const Logger log = app->getLogger();
    log->debug(
        "Received request for movie metadata instance with ID {}",
        movieInstanceId
    );
    const string titleResponse =
        "Got movie title: " + to_string(movieInstanceId);
    response.movieInstanceMetadata =
        soap_new_req_ns1__MovieInstanceMetadata(soap, titleResponse);
    return SOAP_OK;
}

int ns1__createMovieInstanceMetadataById(
    struct soap* soap,
    struct ns1__MovieInstanceMetadata* movieInstanceMetadata,
    struct ns1__createMovieInstanceMetadataByIdResponse& response
)
{
    const ApplicationServer* app = getApplication(soap);
    const Logger log = app->getLogger();
    log->debug(
        "Received request to create movie metadata instance ({}, {}, {})",
        movieInstanceMetadata->title,
        (void*) movieInstanceMetadata->magnetLink,
        (void*) movieInstanceMetadata->coverImageLink
    );
    response.movieInstanceId = 786;
    return SOAP_OK;
}