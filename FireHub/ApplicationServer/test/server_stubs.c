#include "soap/ApplicationServer.nsmap"
#include "soap/soapH.h"

int ns1__getMovieInstanceMetadataById(
    struct soap* soap,
    LONG64 movieInstanceId,
    struct ns1__getMovieInstanceMetadataByIdResponse& response
)
{
    (void) soap;
    (void) movieInstanceId;
    (void) response;
    return SOAP_OK;
}

int ns1__createMovieInstanceMetadataById(
    struct soap* soap,
    struct ns1__MovieInstanceMetadata* movieInstanceMetadata,
    struct ns1__createMovieInstanceMetadataByIdResponse& response
)
{
    (void) soap;
    (void) movieInstanceMetadata;
    (void) response;
    return SOAP_OK;
}
