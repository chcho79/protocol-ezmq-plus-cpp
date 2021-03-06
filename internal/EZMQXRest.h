/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/


#ifndef EZMQ_X_REST_H
#define EZMQ_X_REST_H

#include <string>
#include <curl/curl.h>

namespace EZMQX {

typedef enum
{   WrongCode = 0,
    Success = 200,
    Created = 201,
    Accepted = 202,
    BadRequest = 400,
    Unauthorized = 401,
    Forbidden = 403,
    NotFound = 404,
    NotAllowed = 405,
    Conflict = 409,
    InternalError = 500,
    Unabailable = 503
}HttpStatus;

class RestResponse
{
private:
    HttpStatus status;
    std::string payload;
public:
    RestResponse() : status(WrongCode), payload(""){};
    RestResponse(HttpStatus restStatus, const std::string &restPayload): status(restStatus), payload(restPayload){};
    HttpStatus getStatus(){return status;};
    std::string getPayload(){return payload;};
};

class rest
{
public:
    virtual ~rest() = 0;
    virtual RestResponse Get(const std::string &url) = 0;
    virtual RestResponse Get(const std::string &url, const std::string &query) = 0;
    virtual RestResponse Put(const std::string &url, const std::string &payload) = 0;
    virtual RestResponse Post(const std::string &url, const std::string &payload) = 0;
    virtual RestResponse Delete(const std::string &url, const std::string &query) = 0;
};

class SimpleRest : public rest
{
private:
    CURL *curl;
    // make noncopyable
    SimpleRest(const SimpleRest&) = delete;
    SimpleRest& operator = (const SimpleRest&) = delete;
public:
    SimpleRest();
    ~SimpleRest();
    RestResponse Get(const std::string &url);
    RestResponse Get(const std::string &url, const std::string &query);
    RestResponse Put(const std::string &url, const std::string &payload);
    RestResponse Post(const std::string &url, const std::string &payload);
    RestResponse Delete(const std::string &url, const std::string &query);
};

class RestFactoryInterface
{
public:
    virtual rest* getSomeRest() = 0;
    virtual ~RestFactoryInterface() = 0;
};

// rest Factory
class RestFactory : public RestFactoryInterface
{
public:
    rest* getSomeRest();
};

// fake accessor fot RestService
class FakeRestAccessor;

//singleton
class RestService
{
friend FakeRestAccessor;
private:
    static RestFactoryInterface* factory;

public:
    RestService(){};
    ~RestService();
    static RestResponse Get(const std::string &url);
    static RestResponse Get(const std::string &url, const std::string &query);
    static RestResponse Put(const std::string &url, const std::string &payload);
    static RestResponse Post(const std::string &url, const std::string &payload);
    static RestResponse Delete(const std::string &url, const std::string &query);
};

} // namespace EZMQX

#endif //EZMQ_X_REST_H