#ifndef EXMQ_X_PUBLISHER_H
#define EXMQ_X_PUBLISHER_H

#include <string>
#include <memory>
#include <atomic>
#include <EZMQXTopic.h>
#include <EZMQPublisher.h>
#include <EZMQXErrorCode.h>

namespace EZMQX {
class Context;
/**
* @class Publisher
* Super class for Publisher.
*
*/
class Publisher
{
    protected:
        friend class Context;
        std::mutex lock;
        std::atomic_bool terminated;
        EZMQX::Context* ctx;
        ezmq::EZMQPublisher* pubCtx;
        int localPort;
        EZMQX::Topic topic;
        bool secured;
        std::string token;

        void validateTopic(const std::string topic);
        void registerTopic(EZMQX::Topic& topic);

        // delete default ctor
        Publisher();
        Publisher(int optionalPort, const std::string &serverSecretKey);

        // make noncopyable        
        Publisher(const Publisher&) = delete;
        Publisher& operator = (const Publisher&) = delete;

        bool isSecured();
        bool isTerminated();
        void terminate();
        void terminateOwnResource();
        EZMQX::Topic getTopic();

    public:
        ~Publisher();
};
} // namespace EZMQX

#endif //EXMQ_X_PUBLISHER_H