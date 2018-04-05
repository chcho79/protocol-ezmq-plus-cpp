#ifndef EZMQ_X_SUBSCRIBER_H
#define EZMQ_X_SUBSCRIBER_H

#include <string>
#include <list>
#include <queue>
#include <memory>
#include <atomic>
#include <EZMQXErrorCode.h>
#include <EZMQXTopic.h>
#include <EZMQSubscriber.h>
#include <AMLInterface.h>
#include <Representation.h>
#include <EZMQXAmlModelInfo.h>

namespace EZMQX
{
class BlockingQue;
class Context;
class Subscriber
{
    protected:
        std::mutex lock;
        std::atomic_bool terminated;
        EZMQX::Context* ctx;
        std::list<ezmq::EZMQSubscriber*> subscribers;
        std::map<std::string, std::shared_ptr<Representation>> repDic;
        std::string token;
        EZMQX::BlockingQue* que;
        std::thread mThread;

        void handler();
        virtual void cb(const std::string &_topic, const AMLObject* obj) = 0;

        void internalSubCb(std::string topic, const ezmq::EZMQMessage &event);
        void initialize(const std::list<EZMQX::Topic> &topics);

        virtual void verifyTopics(const std::string &topic, std::list<EZMQX::Topic> &verified);
        virtual void verifyTopics(const std::list<EZMQX::Topic> &topics);

        Subscriber();
        ~Subscriber();
        // make noncopyable
        Subscriber(const Subscriber&) = delete;
        Subscriber& operator = (const Subscriber&) = delete;

        bool isTerminated();
        void terminate();
        std::list<EZMQX::Topic> getTopics();
};

}

#endif //EZMQ_X_SUBSCRIBER_H