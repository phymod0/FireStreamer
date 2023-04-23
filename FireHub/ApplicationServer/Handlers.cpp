#include "soap/ApplicationServer.nsmap"
#include "soap/soapH.h"

#include <iostream>
#include <string>

#include <sqlite3.h>

using namespace std;

int ns1__getMovieInstanceMetadataById(
    struct soap* soap,
    LONG64 movieInstanceId,
    struct ns1__getMovieInstanceMetadataByIdResponse& response
)
{
    const string titleResponse =
        "Got movie title: " + to_string(movieInstanceId);
    response.movieInstanceMetadata = soap_new_req_ns1__MovieInstanceMetadata(
        soap, movieInstanceId, titleResponse
    );
    return SOAP_OK;
}