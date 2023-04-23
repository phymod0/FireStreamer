#include <stdexcept>

#include "LoggerHelper.h"
#include "Utils.h"

using std::runtime_error;
using std::string;
using std::vector;

static const Logger LOG = LoggerHelper::getBootstrapLogger(__FILE__);

namespace Utils
{

template <typename T>
string vectorToString(const vector<T> vec)
{
    string result = "[";
    bool elementAdded = false;
    for (const T& elem : vec) {
        if (elementAdded) {
            result += ", ";
        }
        result += elem;
        elementAdded = true;
    }
    return result + "]";
}

string getJsonString(const Json::Value& root, const vector<string>& path)
{
    LOG->trace("Returning value in {} at path {}", root.toStyledString(),
               vectorToString(path));
    if (path.empty()) {
        if (root.type() != Json::stringValue) {
            throw runtime_error("Expected string at termination but was type " +
                                root.type());
        }
        return root.asString();
    }
    const string& node = path[0];
    if (root.type() != Json::objectValue && root.type() != Json::nullValue) {
        throw runtime_error("Neither object value nor null value");
    }
    if (root.empty()) {
        throw runtime_error("Unable to find \"" + node + "\" in empty JSON");
    }
    if (!root.isMember(node)) {
        throw "Unable to find \"" + node +
            "\" in members of JSON structure: " + root.toStyledString();
    }
    return getJsonString(root[node],
                         vector<string>(path.begin() + 1, path.end()));
}

}   // namespace Utils