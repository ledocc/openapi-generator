#define BOOST_TEST_INCLUDED
#include <list>
#include "../ApprovalTests.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <initializer_list>

#include "api/HttpClientImpl.h"
#include "api/PetApi.h"
#include "model/Pet.h"

#include <vector>
#include <tuple>

using namespace ApprovalTests;
using namespace org::openapitools::client::api;


#define REQUIRE_THROW(fn, ex, lambda) do { \
        bool exceptionThrown = false;      \
        try { fn; }                        \
        catch(const ex& e) {               \
            exceptionThrown = true;        \
            lambda(e);                     \
         }                                 \
         BOOST_REQUIRE(exceptionThrown);   \
    } while (0)


struct fixture {
    fixture() {}
    ~fixture() {}

    std::shared_ptr<HttpClient> client = std::make_shared<HttpClientImpl>("localhost", "8080");
};


BOOST_FIXTURE_TEST_SUITE(PetApiTest, fixture)


BOOST_AUTO_TEST_CASE(getPetById_success) {
    PetApi api(client);
    const auto resp = api.getPetById(0);

    Approvals::verify(resp->toJsonString(true));
}

BOOST_AUTO_TEST_CASE(getPetById_invalid_id) {
    PetApi api(client);

    REQUIRE_THROW(api.getPetById(1), PetApiException, [](const auto& e) {
        BOOST_REQUIRE_EQUAL(e.getStatus(), boost::beast::http::status{400});
        BOOST_REQUIRE_EQUAL(e.what(), "Invalid ID supplied");
    });
}

BOOST_AUTO_TEST_CASE(getPetById_not_found) {
    PetApi api(client);
    REQUIRE_THROW(api.getPetById(2), PetApiException, [](const auto& e) {
        BOOST_REQUIRE_EQUAL(e.getStatus(), boost::beast::http::status{404});
        BOOST_REQUIRE_EQUAL(e.what(), "Pet not found");
    });
}

BOOST_AUTO_TEST_CASE(addPet) {
    PetApi api(client);

    const auto petJson = R"JSON(
    {
        "id": "0",
        "name": "doggie",
        "status": "available"
    })JSON";

    auto pet = std::make_shared<Pet>();
    pet->fromJsonString(petJson);


    const auto responsePet = api.addPet(pet);
    BOOST_REQUIRE_EQUAL(0, responsePet->getId());
}

BOOST_AUTO_TEST_CASE(updatePet_success) {
    PetApi api(client);

    const auto petJson = R"JSON(
    {
        "id": "1",
        "name": "cat",
        "status": "available"
    })JSON";

    auto pet = std::make_shared<Pet>();
    pet->fromJsonString(petJson);

    const auto responsePet = api.updatePet(pet);
    Approvals::verify(responsePet->toJsonString(true));
}

BOOST_DATA_TEST_CASE(updatePet_fails, boost::unit_test::data::make(
        std::vector<std::tuple<int, int, std::string>>{
            {400, 400, "Invalid ID supplied"},
            {404, 404, "Pet not found"},
            {405, 405, "Validation exception"}}), pet_id, expected_http_status, expected_error_message) {

    PetApi api(client);

    auto pet = std::make_shared<Pet>();
    pet->setId(pet_id);
    pet->setName("doggie");
    pet->setStatus("available");
    const auto photoUrls = std::vector<std::string>();
    pet->setPhotoUrls(photoUrls);

    REQUIRE_THROW(api.updatePet(pet), PetApiException, [&](const auto& e) {
        BOOST_REQUIRE_EQUAL(e.getStatus(), boost::beast::http::status{expected_http_status});
        BOOST_REQUIRE_EQUAL(e.what(), expected_error_message);
    });

}

BOOST_AUTO_TEST_SUITE_END()
