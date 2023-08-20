#include "soap/ApplicationServer.nsmap"
#include "soap/soapH.h"

#include <iostream>
#include <string>

#include "ApplicationServer.h"
#include "CommonConstants.h"
#include "LoggerHelper.h"
#include "MovieInstanceMetadataDAO.h"

#include <sqlite3.h>

using namespace std;

static inline ApplicationServer* getApplication(struct soap* soap)
{
    return (ApplicationServer*) soap->user;
}

int ns1__getMovieInstanceMetadataById(
    struct soap* soap,
    LONG64 movieInstanceId,
    struct ns1__getMovieInstanceMetadataByIdResponse& response)
{
    ApplicationServer* app = getApplication(soap);
    Database& dbHandle = app->getDBHandle();
    const Logger log = app->getLogger();
    MovieInstanceMetadataDAO metadataDao(dbHandle, log);

    log->debug(
        "Received request for movie metadata instance with ID {}",
        movieInstanceId);
    const string titleResponse =
        "Got movie title: " + to_string(movieInstanceId);
    response.movieInstanceMetadata =
        soap_new_req_ns1__MovieInstanceMetadata(soap, titleResponse);
    return SOAP_OK;
}

int ns1__createMovieInstanceMetadataById(
    struct soap* soap,
    struct ns1__MovieInstanceMetadata* movieInstanceMetadata,
    struct ns1__createMovieInstanceMetadataByIdResponse& response)
{
    ApplicationServer* app = getApplication(soap);
    Database& dbHandle = app->getDBHandle();
    const Logger log = app->getLogger();
    MovieInstanceMetadataDAO metadataDao(dbHandle, log);

    const string& title = movieInstanceMetadata->title;
    const string* magnetLink = movieInstanceMetadata->magnetLink;
    const string* coverImageLink = movieInstanceMetadata->coverImageLink;
    log->debug(
        "Received request to create movie metadata instance ({})",
        title);
    // Create instance metadata
    try {
        const LONG64 createdInstanceId =
            metadataDao.create(title, magnetLink, coverImageLink);
        response.movieInstanceId = createdInstanceId;
    } catch (const string& error) {
        log->error("Request failed due to error: {}", error);
        return SOAP_SVR_FAULT;
    }
    return SOAP_OK;
}
