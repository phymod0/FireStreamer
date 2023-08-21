#ifndef COMMON_CONSTANTS
#define COMMON_CONSTANTS

namespace Constants
{
// TODO(phymod0): s/phymod0/<user>/
inline const char* CONFIG_PATH = "/home/phymod0/.fireStreamer/config.json";

namespace EnvironmentVariables
{
inline const char* DB_PATH = "FIRESTREAMER_DB_PATH";
}   // namespace EnvironmentVariables

namespace TableDefinitions
{
// TODO(phymod0): Delegate table creation to DAO setup and remove DAO-specific
// constants from here
inline const char* MOVIE_INSTANCE_METADATA =
    "MOVIE_INSTANCE_METADATA"
    "("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "TITLE TEXT,"
    "MAGNET_LINK TEXT,"
    "COVER_IMAGE_LINK TEXT"
    ")";
}   // namespace TableDefinitions

namespace DatabaseCommands
{
inline const char* BEGIN_TRANSACTION = "BEGIN TRANSACTION;";
inline const char* END_TRANSACTION = "END TRANSACTION;";
}   // namespace DatabaseCommands
}   // namespace Constants

#endif /* COMMON_CONSTANTS */
