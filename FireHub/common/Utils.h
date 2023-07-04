#ifndef UTILS
#define UTILS

#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

namespace Utils
{

std::string getJsonString(
    const Json::Value& root,
    const std::vector<std::string>& path);

}

#endif /* UTILS */
