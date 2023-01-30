#include "soap/soapH.h"
#include "soap/ApplicationServer.nsmap"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    return soap_serve(soap_new());
}

int ns1__getMovieInstanceMetadataById(
        struct soap* soap,
        LONG64 movieInstanceId,
        struct ns1__getMovieInstanceMetadataByIdResponse &response)
{
    const string titleResponse = "Got movie with title: " + to_string(movieInstanceId);
    response.movieInstanceMetadata =
            soap_new_req_ns1__MovieInstanceMetadata(soap, movieInstanceId, titleResponse);
    return SOAP_OK;
}
