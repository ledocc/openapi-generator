/**
 * OpenAPI Petstore
 * This is a sample server Petstore server. For this sample, you can use the api key `special-key` to test the authorization filters.
 *
 * The version of the OpenAPI document: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 5.3.1-SNAPSHOT.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */


#include <sstream>
#include <string>
#include <map>
#include <array>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/format.hpp>
#include <boost/version.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/algorithm/string.hpp>

#include "PetApi.h"


namespace org {
namespace openapitools {
namespace client {
namespace api {

using namespace org::openapitools::client::model;


namespace {
std::string selectPreferredContentType(const std::vector<std::string>& contentTypes) {
    if (contentTypes.size() == 1) {
        return contentTypes.at(0);
    }

    static const std::array<std::string, 2> preferredTypes = {"json", "xml"};
    for (const auto& preferredType: preferredTypes) {
        const auto ret = std::find_if(contentTypes.cbegin(),
                                      contentTypes.cend(),
                                      [preferredType](const std::string& str) {
                                            return str.find(preferredType) != std::string::npos;});
        if (ret != contentTypes.cend()) {
            return *ret;
        }
    }

    if (contentTypes.size() == 0) {
        return "application/json";
    }

    return contentTypes.at(0);
}

std::string base64encodeImpl(const std::string& str) {
#if BOOST_VERSION < 107100
    return boost::beast::detail::base64_encode(str);
#else
    return boost::beast::detail::base64::encode(str);
#endif
}
}

PetApiException::PetApiException(boost::beast::http::status statusCode, std::string what)
  : m_status(statusCode),
    m_what(what)
{
}

boost::beast::http::status PetApiException::getStatus() const
{
    return m_status;
}

const char* PetApiException::what() const noexcept
{
    return m_what.c_str();
}

std::shared_ptr<Pet>
PetApi::addPet(
    const std::shared_ptr<Pet>& pet) {
    std::string requestBody;
    std::string path = m_context + "/pet";
    std::map<std::string, std::string> headers;
    // Body params
    requestBody = pet->toJsonString();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);

    static const std::vector<std::string> contentTypes{ "application/json","application/xml", };
    setPreferredMediaTypeHeader(headers, "ContentType", contentTypes);

    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("POST",
                              path,
                              requestBody,
                              headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::shared_ptr<Pet> result = std::make_shared<Pet>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }
    if (statusCode == boost::beast::http::status(405)) {
        throw PetApiException(statusCode, "Invalid input");
    }

    return result;
}

// vendor extension
std::shared_ptr<Pet>
PetApi::updatePet(
    const std::shared_ptr<Pet>& pet) {
    std::string requestBody;
    std::string path = m_context + "/pet";
    std::map<std::string, std::string> headers;
    // Body params
    requestBody = pet->toJsonString();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);

    static const std::vector<std::string> contentTypes{ "application/json","application/xml", };
    setPreferredMediaTypeHeader(headers, "ContentType", contentTypes);

    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("PUT",
                path,
                requestBody,
                headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::shared_ptr<Pet> result = std::make_shared<Pet>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw PetApiException(statusCode, "Invalid ID supplied");
    }
    if (statusCode == boost::beast::http::status(404)) {
        throw PetApiException(statusCode, "Pet not found");
    }
    if (statusCode == boost::beast::http::status(405)) {
        throw PetApiException(statusCode, "Validation exception");
    }

    return result;
}

void
PetApi::deletePet(
    const int64_t& petId, const std::string& apiKey) {
    std::string requestBody;
    std::string path = m_context + "/pet/%1%";
    std::map<std::string, std::string> headers;
    // path params
    const auto formattedPath = boost::format(path) % petId;
    path = formattedPath.str();
    // headers
    headers.emplace(std::make_pair("apiKey", boost::lexical_cast<std::string>(apiKey)));



    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("DELETE",
                              path,
                              requestBody,
                              headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    if (statusCode == boost::beast::http::status(400)) {
        throw PetApiException(statusCode, "Invalid pet value");
    }

}

// vendor extension
std::shared_ptr<Pet>
PetApi::getPetById(
    const int64_t& petId) {
    std::string requestBody;
    std::string path = m_context + "/pet/%1%";
    std::map<std::string, std::string> headers;
    // path params
    const auto formattedPath = boost::format(path) % petId;
    path = formattedPath.str();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);


    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("GET",
                path,
                requestBody,
                headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::shared_ptr<Pet> result = std::make_shared<Pet>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw PetApiException(statusCode, "Invalid ID supplied");
    }
    if (statusCode == boost::beast::http::status(404)) {
        throw PetApiException(statusCode, "Pet not found");
    }

    return result;
}


// vendor extension
void
PetApi::updatePetWithForm(
    const int64_t& petId, const std::string& name, const std::string& status) {
    std::string requestBody;
    std::string path = m_context + "/pet/%1%";
    std::map<std::string, std::string> headers;
    // form param
    std::stringstream formParams;
    formParams << "name=";
    formParams << base64encode(name);
    formParams << '&';
    formParams << "status=";
    formParams << base64encode(status);
    
    requestBody = formParams.str();
    // path params
    const auto formattedPath = boost::format(path) % petId;
    path = formattedPath.str();


    static const std::vector<std::string> contentTypes{ "application/x-www-form-urlencoded", };
    setPreferredMediaTypeHeader(headers, "ContentType", contentTypes);

    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("POST",
                path,
                requestBody,
                headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    if (statusCode == boost::beast::http::status(405)) {
        throw PetApiException(statusCode, "Invalid input");
    }

}

std::vector<std::shared_ptr<Pet>>
PetApi::findPetsByStatus(
    const std::vector<std::string>& status) {
    std::string requestBody;
    std::string path = m_context + "/pet/findByStatus";
    std::map<std::string, std::string> headers;
    // query params
    std::stringstream queryParamStream;
    queryParamStream << '?';
    queryParamStream << "status=";
    queryParamStream << boost::algorithm::join(status, ",");
    path += queryParamStream.str();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);


    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("GET",
                              path,
                              requestBody,
                              headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::vector<std::shared_ptr<Pet>> result = std::vector<std::shared_ptr<Pet>>();
    if (statusCode == boost::beast::http::status(200)) {
        createModelVectorFromJsonString(result, responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw PetApiException(statusCode, "Invalid status value");
    }

    return result;
}
std::vector<std::shared_ptr<Pet>>
PetApi::findPetsByTags(
    const std::vector<std::string>& tags) {
    std::string requestBody;
    std::string path = m_context + "/pet/findByTags";
    std::map<std::string, std::string> headers;
    // query params
    std::stringstream queryParamStream;
    queryParamStream << '?';
    queryParamStream << "tags=";
    queryParamStream << boost::algorithm::join(tags, ",");
    path += queryParamStream.str();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);


    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("GET",
                              path,
                              requestBody,
                              headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::vector<std::shared_ptr<Pet>> result = std::vector<std::shared_ptr<Pet>>();
    if (statusCode == boost::beast::http::status(200)) {
        createModelVectorFromJsonString(result, responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw PetApiException(statusCode, "Invalid tag value");
    }

    return result;
}
std::shared_ptr<ApiResponse>
PetApi::uploadFile(
    const int64_t& petId, const std::string& additionalMetadata, const std::string& file) {
    std::string requestBody;
    std::string path = m_context + "/pet/%1%/uploadImage";
    std::map<std::string, std::string> headers;
    // path params
    const auto formattedPath = boost::format(path) % petId;
    path = formattedPath.str();

    static const std::vector<std::string> acceptTypes{ "application/json", };
    setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);

    static const std::vector<std::string> contentTypes{ "multipart/form-data", };
    setPreferredMediaTypeHeader(headers, "ContentType", contentTypes);

    auto statusCode = boost::beast::http::status::unknown;
    std::string responseBody;
    try {
        std::tie(statusCode, responseBody) =
            m_client->execute("POST",
                              path,
                              requestBody,
                              headers);
    }
    catch(const std::exception& e) {
        handleStdException(e);
    }
    catch(...) {
        handleUncaughtException();
    }

    std::shared_ptr<ApiResponse> result = std::make_shared<ApiResponse>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }

    return result;
}


std::string PetApi::base64encode(const std::string& str) {
    return base64encodeImpl(str);
}

void PetApi::setPreferredMediaTypeHeader(std::map<std::string, std::string>& headers, const std::string& headerName, const std::vector<std::string>& contentTypes) {
    const std::string contentType = selectPreferredContentType(contentTypes);
    headers[headerName] = contentType;
}

void PetApi::handleStdException(const std::exception& e) {
    throw e;
}

void PetApi::handleUncaughtException() {
    throw;
}


}  // namespace org
}  // namespace openapitools
}  // namespace client
}  // namespace api
