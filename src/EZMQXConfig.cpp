#include <EZMQXConfig.h>
#include <EZMQXContext.h>
#include <EZMQXException.h>

static const std::string LOCAL_ADDR = "localhost";

EZMQX::Config::Config(): initialized(false), ctx(EZMQX::Context::getInstance()){}

EZMQX::Config::Config(ModeOption mode): configMode(mode), initialized(false), ctx(EZMQX::Context::getInstance())
{
    initialize();
}

EZMQX::Config::~Config()
{
    terminate();
}

// mocking here
void EZMQX::Config::initialize()
{
    // mutex lock
    {
        std::lock_guard<std::mutex> scopedLock(lock);

        if (!initialized.load())
        {
            if (StandAlone == configMode)
            {
                ctx->setStandAloneMode(true);
                ctx->setHostInfo("localhost", "localhost");
            }
            else if(FullFeature == configMode)
            {
                ctx->initialize();
            }
            else
            {
                throw EZMQX::Exception("Invalid Operation", EZMQX::UnKnownState);
            }

            initialized.store(true);
        }
    }
    // mutex unlock

    return;
}

void EZMQX::Config::setHostInfo(std::string hostName, std::string hostAddr)
{
    // mutex lock
    {
        std::lock_guard<std::mutex> scopedLock(lock);

        if (configMode != StandAlone)
        {
            throw EZMQX::Exception("Invalid Operation", EZMQX::UnKnownState);
        }
        else
        {
            ctx->setHostInfo(hostName, hostAddr);
        }
    }
}

void EZMQX::Config::setTnsInfo(std::string remoteAddr)
{
    // mutex lock
    {
        std::lock_guard<std::mutex> scopedLock(lock);

        if (configMode != StandAlone)
        {
            throw EZMQX::Exception("Invalid Operation", EZMQX::UnKnownState);
        }
        else
        {
            ctx->setTnsInfo(remoteAddr);
        }
    }
    // mutex unlock
}

// mocking here
void EZMQX::Config::terminate()
{
    // mutex lock
    {
        std::lock_guard<std::mutex> scopedLock(lock);
    }
    // mutex unlock

    return;
}

std::list<std::string> EZMQX::Config::addAmlModel(const std::list<std::string>& amlFilePath)
{
    return ctx->addAmlRep(amlFilePath);
}