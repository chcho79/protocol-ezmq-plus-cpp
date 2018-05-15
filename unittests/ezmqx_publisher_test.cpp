#include <iostream>
#include <EZMQXConfig.h>
#include <EZMQXException.h>
#include <gtest.h>
#include <gmock.h>
#include <iostream>
#include <EZMQXConfig.h>
#include <EZMQXException.h>
#include <UnitTestHelper.h>
#include <string>

using testing::Action;
using testing::ActionInterface;
using testing::Assign;
using testing::ByMove;
using testing::ByRef;
using testing::DefaultValue;
using testing::DoDefault;
using testing::IgnoreResult;
using testing::Invoke;
using testing::InvokeWithoutArgs;
using testing::MakePolymorphicAction;
using testing::Ne;
using testing::PolymorphicAction;
using testing::Return;
using testing::ReturnNull;
using testing::ReturnRef;
using testing::ReturnRefOfCopy;
using testing::SetArgPointee;
using testing::SetArgumentPointee;
using testing::Unused;
using testing::_;
using testing::AtLeast;
using testing::get;
using testing::internal::BuiltInDefaultValue;
using testing::internal::Int64;
using testing::internal::UInt64;
using testing::make_tuple;
using testing::tuple;
using testing::tuple_element;
using testing::SetArgReferee;

TEST(Publisher, onDocker)
{
    // ToDo
}

TEST(Publisher, onFakeDocker)
{
    EZMQX::FakeSingletonAccessor::setFake();
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startDockerMode();

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    EZMQX::AmlPublisher* pub1 = nullptr;
    EZMQX::AmlPublisher* pub2 = nullptr;

    EXPECT_THROW(pub1 = EZMQX::AmlPublisher::getPublisher("/T/A", EZMQX::AmlModelId, amlId, 4000), EZMQX::Exception);
    EXPECT_THROW(pub2 = EZMQX::AmlPublisher::getPublisher("/T/B", EZMQX::AmlFilePath, "sample_data_model.aml", 4001), EZMQX::Exception);

    if (pub1)
    {
        delete pub1;
    }

    if (pub2)
    {
        delete pub2;
    }

    config->reset();
}

TEST(Publisher, onStandAloneWithoutTns)
{
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startStandAloneMode(false, "127.0.0.1");

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    EZMQX::AmlPublisher* pub1 = EZMQX::AmlPublisher::getPublisher("/T/A", EZMQX::AmlModelId, amlId, 4000);
    EZMQX::AmlPublisher* pub2 = EZMQX::AmlPublisher::getPublisher("/T/B", EZMQX::AmlFilePath, "sample_data_model.aml", 4001);

    if (pub1)
    {
        EZMQX::Topic t = pub1->getTopic();
    }

    if (pub1)
    {
        delete pub1;
    }

    if (pub2)
    {
        delete pub2;
    }

    config->reset();
}

TEST(Publisher, onStandAloneWithTns)
{
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startStandAloneMode(true, "127.0.0.1");

    EZMQX::AmlPublisher* pub1 = nullptr;
    EZMQX::AmlPublisher* pub2 = nullptr;

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    EXPECT_THROW(pub1 = EZMQX::AmlPublisher::getPublisher("/T/A", EZMQX::AmlModelId, amlId, 4000), EZMQX::Exception);
    EXPECT_THROW(pub2 = EZMQX::AmlPublisher::getPublisher("/T/B", EZMQX::AmlFilePath, "sample_data_model.aml", 4001), EZMQX::Exception);

    if (pub1)
    {
        delete pub1;
    }

    if (pub2)
    {
        delete pub2;
    }

    config->reset();
}

TEST(Publisher, publish)
{
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startStandAloneMode(false, "127.0.0.1");

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    //wrong case : duplecated port
    EZMQX::AmlPublisher* pub = EZMQX::AmlPublisher::getPublisher("/TT/A", EZMQX::AmlModelId, amlId, 4000);

    // create AMLObject
    std::string deviceId = "GTC001";
    std::string timeStamp = "123456789";

    AML::AMLObject amlObj(deviceId, timeStamp);

    // create "Model" data
    AML::AMLData model;
    model.setValue("ctname", "Model_107.113.97.248");
    model.setValue("con", "SR-P7-970");

    // create "Sample" data
    AML::AMLData axis;
    axis.setValue("x", "20");
    axis.setValue("y", "110");
    axis.setValue("z", "80");

    AML::AMLData info;
    info.setValue("id", "f437da3b");
    info.setValue("axis", axis);

    std::vector<std::string> appendix;
    appendix.push_back("52303");
    appendix.push_back("935");
    appendix.push_back("1442");

    AML::AMLData sample;
    sample.setValue("info", info);
    sample.setValue("appendix", appendix);

    // Add Datas to AMLObject
    amlObj.addData("Model", model);
    amlObj.addData("Sample", sample);

    pub->publish(amlObj);

    if (pub)
    {
        delete pub;
    }

    config->reset();
}

TEST(Publisher, duplecatedPort)
{
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startStandAloneMode(false, "127.0.0.1");

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    //wrong case : duplecated port
    EZMQX::AmlPublisher* pub1 = EZMQX::AmlPublisher::getPublisher("/T/C", EZMQX::AmlModelId, amlId, 4000);
    EZMQX::AmlPublisher* pub2 = nullptr;

    EXPECT_THROW(pub2 = EZMQX::AmlPublisher::getPublisher("/T/C", EZMQX::AmlModelId, amlId, 4000), EZMQX::Exception);

    if (pub1)
    {
        delete pub1;
    }

    if (pub2)
    {
        delete pub2;
    }

    config->reset();
}

TEST(Publisher, invalidPath)
{
    EZMQX::Config* config = EZMQX::Config::getInstance();

    config->startStandAloneMode(false, "127.0.0.1");

    std::list<std::string> amlPath(1, "sample_data_model.aml");
    std::list<std::string> amlIds(1);
    amlIds = config->addAmlModel(amlPath);
    std::string amlId = amlIds.front();

    //wrong case : invalid amlfile path
    EZMQX::AmlPublisher* pub = nullptr;

    EXPECT_THROW(pub = EZMQX::AmlPublisher::getPublisher("/T/C", EZMQX::AmlModelId, "invalid.aml", 4000), EZMQX::Exception);

    if (pub)
    {
        delete pub;
    }

    config->reset();
}