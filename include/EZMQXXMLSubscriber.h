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
typedef std::function<void(std::string topic, const std::string& payload)> XmlSubCb;
typedef std::function<void(std::string topic, EZMQX::ErrorCode errCode)> SubErrCb;

class BlockingQue;
class XmlSubscriber
{
    private:
        std::mutex lock;
        std::atomic_bool terminated;
        std::list<std::shared_ptr<ezmq::EZMQSubscriber>> subscribers;
        std::map<std::string, std::shared_ptr<Representation>> repDic;
        std::string token;
        EZMQX::XmlSubCb mSubCb;
        EZMQX::SubErrCb mSubErrCb;
        std::shared_ptr<EZMQX::BlockingQue> que;
        std::thread mThread;
        void handler();
        void internalSubCb(std::string topic, const ezmq::EZMQMessage &event);
        void initialize(const std::list<EZMQX::Topic> &topics, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        virtual void verifyTopics(const std::string &topic, std::list<EZMQX::Topic> &verified);
        virtual void verifyTopics(const std::list<EZMQX::Topic> &topics);

        // delete default ctor
        XmlSubscriber();
        XmlSubscriber(const std::list<EZMQX::Topic> &topics, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        XmlSubscriber(const std::string &topic, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        // make noncopyable
        XmlSubscriber(const XmlSubscriber&) = delete;
        XmlSubscriber& operator = (const XmlSubscriber&) = delete;

    public:
        static std::shared_ptr<EZMQX::XmlSubscriber> getSubscriber(const std::string &topic, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        static std::shared_ptr<EZMQX::XmlSubscriber> getSubscriber(const EZMQX::Topic &topic, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        static std::shared_ptr<EZMQX::XmlSubscriber> getSubscriber(const std::list<EZMQX::Topic> &topics, EZMQX::XmlSubCb &subCb, EZMQX::SubErrCb &errCb);
        bool isTerminated();
        void terminate();
        std::list<EZMQX::Topic> getTopics();
};

}

#endif //EZMQ_X_SUBSCRIBER_H