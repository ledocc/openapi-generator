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

#include "StoreApi.h"


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

StoreApiException::StoreApiException(boost::beast::http::status statusCode, std::string what)
  : m_status(statusCode),
    m_what(what)
{
}

boost::beast::http::status StoreApiException::getStatus() const
{
    return m_status;
}

const char* StoreApiException::what() const noexcept
{
    return m_what.c_str();
}

std::string StoreApi::base64encode(const std::string& str) {
    return base64encodeImpl(str);
}

void
StoreApi::deleteOrder(
    const std::string& orderId) {
    std::string requestBody;
    std::string path = m_context + "/store/order/%1%";
    std::map<std::string, std::string> headers;
    // path params
    const auto formattedPath = boost::format(path) % orderId;
    path = formattedPath.str();



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
        deleteOrder_handleStdException(e);
    }
    catch(...) {
        deleteOrder_handleUncaughtException();
    }

    if (statusCode == boost::beast::http::status(400)) {
        throw StoreApiException(statusCode, "Invalid ID supplied");
    }
    if (statusCode == boost::beast::http::status(404)) {
        throw StoreApiException(statusCode, "Order not found");
    }

}

std::shared_ptr<Order>
StoreApi::getOrderById(
    const int64_t& orderId) {
    std::string requestBody;
    std::string path = m_context + "/store/order/%1%";
    std::map<std::string, std::string> headers;
    // path params
    const auto formattedPath = boost::format(path) % orderId;
    path = formattedPath.str();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    getOrderById_setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);


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
        getOrderById_handleStdException(e);
    }
    catch(...) {
        getOrderById_handleUncaughtException();
    }

    std::shared_ptr<Order> result = std::make_shared<Order>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw StoreApiException(statusCode, "Invalid ID supplied");
    }
    if (statusCode == boost::beast::http::status(404)) {
        throw StoreApiException(statusCode, "Order not found");
    }

    return result;
}

void StoreApi::deleteOrder_setPreferredMediaTypeHeader(
    std::map<std::string, std::string>& headers, const std::string& headerName, const std::vector<std::string>& contentTypes) {
    const std::string contentType = selectPreferredContentType(contentTypes);
    headers[headerName] = contentType;
}

void StoreApi::deleteOrder_handleStdException(
    const std::exception& e) {
    throw e;
}

void StoreApi::deleteOrder_handleUncaughtException() {
    throw;
}

void StoreApi::getOrderById_setPreferredMediaTypeHeader(
    std::map<std::string, std::string>& headers, const std::string& headerName, const std::vector<std::string>& contentTypes) {
    const std::string contentType = selectPreferredContentType(contentTypes);
    headers[headerName] = contentType;
}

void StoreApi::getOrderById_handleStdException(
    const std::exception& e) {
    throw e;
}
void StoreApi::getOrderById_handleUncaughtException() {
    throw;
}
std::map<std::string, int32_t>
StoreApi::getInventory(
    ) {
    std::string requestBody;
    std::string path = m_context + "/store/inventory";
    std::map<std::string, std::string> headers;

    static const std::vector<std::string> acceptTypes{ "application/json", };
    getInventory_setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);


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
        getInventory_handleStdException(e);
    }
    catch(...) {
        getInventory_handleUncaughtException();
    }

    std::map<std::string, int32_t> result = std::map<std::string, int32_t>();
    if (statusCode == boost::beast::http::status(200)) {
        // TODO result = convertMapResponse(resultObject);
    }

    return result;
}
void StoreApi::getInventory_setPreferredMediaTypeHeader(
    std::map<std::string, std::string>& headers, const std::string& headerName, const std::vector<std::string>& contentTypes) {
    const std::string contentType = selectPreferredContentType(contentTypes);
    headers[headerName] = contentType;
}

void StoreApi::getInventory_handleStdException(
    const std::exception& e) {
    throw e;
}

void StoreApi::getInventory_handleUncaughtException() {
    throw;
}

std::shared_ptr<Order>
StoreApi::placeOrder(
    const std::shared_ptr<Order>& order) {
    std::string requestBody;
    std::string path = m_context + "/store/order";
    std::map<std::string, std::string> headers;
    // Body params
    requestBody = order->toJsonString();

    static const std::vector<std::string> acceptTypes{ "application/xml","application/json", };
    placeOrder_setPreferredMediaTypeHeader(headers, "Accept", acceptTypes);

    static const std::vector<std::string> contentTypes{ "application/json", };
    placeOrder_setPreferredMediaTypeHeader(headers, "ContentType", contentTypes);

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
        placeOrder_handleStdException(e);
    }
    catch(...) {
        placeOrder_handleUncaughtException();
    }

    std::shared_ptr<Order> result = std::make_shared<Order>();
    if (statusCode == boost::beast::http::status(200)) {
        result->fromJsonString(responseBody);
    }
    if (statusCode == boost::beast::http::status(400)) {
        throw StoreApiException(statusCode, "Invalid Order");
    }

    return result;
}
void StoreApi::placeOrder_setPreferredMediaTypeHeader(
    std::map<std::string, std::string>& headers, const std::string& headerName, const std::vector<std::string>& contentTypes) {
    const std::string contentType = selectPreferredContentType(contentTypes);
    headers[headerName] = contentType;
}

void StoreApi::placeOrder_handleStdException(
    const std::exception& e) {
    throw e;
}

void StoreApi::placeOrder_handleUncaughtException() {
    throw;
}


}  // namespace org
}  // namespace openapitools
}  // namespace client
}  // namespace api
