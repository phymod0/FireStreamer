#include <string>
#include <vector>

#include "BaseApplication.h"
#include "Configuration.h"
#include "Database.h"
#include "LoggerHelper.h"

class ApplicationServer : public BaseApplication
{
private:
    static const std::string SERVER_NAME;
    static const std::vector<std::string> tableDefinitions;
    void initialize();

public:
    ApplicationServer(const Configuration& configuration);
};
