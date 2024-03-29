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
    const Logger log = app->getLogger();
    MovieInstanceMetadataDAO metadataDao = app->getMovieInstanceMetadataDAO();

    log->debug(
        "Received read request for movie metadata instance with ID {}",
        movieInstanceId);
    metadataDao.getById(
        movieInstanceId,
        [soap,
         &response](string& title, string* magnetLink, string* coverImageLink) {
            response.movieInstanceMetadata =
                soap_new_set_ns1__MovieInstanceMetadata(
                    soap,
                    title,
                    magnetLink,
                    coverImageLink);
        });
    return SOAP_OK;
}

int ns1__createMovieInstanceMetadataById(
    struct soap* soap,
    struct ns1__MovieInstanceMetadata* movieInstanceMetadata,
    struct ns1__createMovieInstanceMetadataByIdResponse& response)
{
    ApplicationServer* app = getApplication(soap);
    const Logger log = app->getLogger();
    MovieInstanceMetadataDAO metadataDao = app->getMovieInstanceMetadataDAO();

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
        log->info(
            "Create movie instance metadata with ID: {}",
            response.movieInstanceId);
    } catch (const string& error) {
        log->error("Request failed due to error: {}", error);
        return SOAP_SVR_FAULT;
    }
    return SOAP_OK;
}