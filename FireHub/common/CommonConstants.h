#ifndef COMMON_CONSTANTS
#define COMMON_CONSTANTS

#include <string>

namespace Constants
{

const std::string CONFIG_PATH = "/home/phymod0/.fireStreamer/config.json";

namespace TableDefinitions
{

const std::string MOVIE_INSTANCE_METADATA = "MOVIE_INSTANCE_METADATA"
                                            "("
                                            "ID INTEGER PRIMARY KEY "
                                            "AUTOINCREMENT,"
                                            "TITLE TEXT,"
                                            "MAGNET_LINK TEXT,"
                                            "COVER_IMAGE_LINK TEXT"
                                            ")";

}

};   // namespace Constants

#endif /* COMMON_CONSTANTS */