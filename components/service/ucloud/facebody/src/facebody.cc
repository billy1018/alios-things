#include <iostream>
#include "alibabacloud/core/AlibabaCloud.h"
#include "alibabacloud/facebody/FacebodyClient.h"
#include "alibabacloud/core/CommonClient.h"
#include "facebody.h"
#include "sdkconfig.h"

extern "C" {
using namespace std;
using namespace AlibabaCloud;
using namespace AlibabaCloud::Facebody;

static ClientConfiguration configuration;
static string key = CLOUD_AI_ACCESS_KEY;
static string secret = CLOUD_AI_ACCESS_SECRET;

int facebody_comparing_ai(char *url_a, char *url_b, facebody_comparing_cb_t cb) {
    InitializeSdk();
    configuration.setRegionId(CLOUD_AI_REGION_ID);
    configuration.setEndpoint(CLOUD_AI_FACEBODY_ENDPOINT);
    FacebodyClient client(key, secret, configuration);
    Model::CompareFaceRequest request;
    string tmpImageURLA, tmpImageURLB;
    face_rect_t face_rect;
    float confidence;
    int ret;

    tmpImageURLA = url_a;
    tmpImageURLB = url_b;

    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURLA(tmpImageURLA);
    request.setImageURLB(tmpImageURLB);

    auto outcome =  client.compareFace(request);
    //cout << endl << "facebody describeInstances returned:" << endl;
    //cout << "error code: " << outcome.error().errorCode() << endl;
    //cout << "requestId: " << outcome.result().requestId() << endl << endl;

    cout << "confidence:" << outcome.result().getData().confidence << endl;
    cout << "x:" << outcome.result().getData().rectAList[0] << endl;
    cout << "y:" << outcome.result().getData().rectAList[1] << endl;
    cout << "w:" << outcome.result().getData().rectAList[2] << endl;
    cout << "h" << outcome.result().getData().rectAList[3] << endl;

    if (cb) {
        confidence = outcome.result().getData().confidence;
        face_rect.x = outcome.result().getData().rectAList[0];
        face_rect.y = outcome.result().getData().rectAList[1];
        face_rect.w = outcome.result().getData().rectAList[2];
        face_rect.h = outcome.result().getData().rectAList[3];
        ret = cb(confidence, &face_rect);
    }
    ShutdownSdk();
    return ret;
}

int facebody_recognize_expression_ai(char *url, facebody_recognize_expression_cb_t cb) {

    InitializeSdk();
    configuration.setRegionId(CLOUD_AI_REGION_ID);
    configuration.setEndpoint(CLOUD_AI_FACEBODY_ENDPOINT);
    FacebodyClient client(key, secret, configuration);
    Model::RecognizeExpressionRequest request;
    string tmpImageURL;
    string expression;
    float faceProbability;
    face_rect_t face_rect;
    int ret;

    tmpImageURL = url;
    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURL(tmpImageURL);
    auto outcome = client.recognizeExpression(request);
    cout << endl << "facebody describeInstances returned:" << endl;
    cout << "error code: " << outcome.error().errorCode() << endl;
    cout << "requestId: " << outcome.result().requestId() << endl << endl;

    //cout << "expression:" << outcome.result().getData().elements[0].expression << endl;
    cout << "face probablility:" << outcome.result().getData().elements[0].faceProbability << endl;
    cout << "x:" << outcome.result().getData().elements[0].faceRectangle.left << endl;
    cout << "y:" << outcome.result().getData().elements[0].faceRectangle.top << endl;
    cout << "w:" << outcome.result().getData().elements[0].faceRectangle.width << endl;
    cout << "h:" << outcome.result().getData().elements[0].faceRectangle.height << endl;

    if (cb) {
        expression = outcome.result().getData().elements[0].expression;
        if (!expression.empty()) {
            faceProbability = outcome.result().getData().elements[0].faceProbability;
            face_rect.x = 20;//outcome.result().getData().elements[0].faceRectangle.left;
            face_rect.y = 20;//outcome.result().getData().elements[0].faceRectangle.top;
            face_rect.w = outcome.result().getData().elements[0].faceRectangle.width;
            face_rect.h = outcome.result().getData().elements[0].faceRectangle.height;
            ret = cb((char *)expression.c_str(), faceProbability, &face_rect);
        }
    }
    ShutdownSdk();
    return ret;
}

int facebody_generate_human_anime_style_ai(char *url, facebody_generate_human_anime_stype_cb_t cb) {
    InitializeSdk();
    configuration.setRegionId(CLOUD_AI_REGION_ID);
    configuration.setEndpoint(CLOUD_AI_FACEBODY_ENDPOINT);
    FacebodyClient client(key, secret, configuration);
    Model::GenerateHumanAnimeStyleRequest request;
    string tmpImageURL, outImageURL;
    int ret;

    tmpImageURL = url;
    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURL(tmpImageURL);

    auto outcome = client.generateHumanAnimeStyle(request);
    cout << endl << "facebody describeInstances returned:" << endl;
    cout << "error code: " << outcome.error().errorCode() << endl;
    cout << "requestId: " << outcome.result().requestId() << endl << endl;
    cout << "image url:" << outcome.result().getData().imageURL << endl;

    outImageURL = outcome.result().getData().imageURL;
    if (!outImageURL.empty() && cb) {
        ret = cb((char *)outImageURL.c_str());
    }
    ShutdownSdk();
    return ret;
}

int facebody_config_and_generate_human_anime_style_ai(char *key, char *secret, char *region_id,
        char *endpoint, char *url, facebody_generate_human_anime_stype_haascv_cb_t cb, void *data) {
    InitializeSdk();
    string sKey = key;
    string sSecret = secret;
    string sRegionId = region_id;
    string sEndPoint = endpoint;
    cout << "Key: " << sKey.c_str() << endl;
    cout << "Secret: " << sSecret.c_str() << endl;
    cout << "RegionId: " << sRegionId.c_str() << endl;
    cout << "EndPoint: " << sEndPoint.c_str() << endl;
    configuration.setRegionId(sRegionId);
    configuration.setEndpoint(sEndPoint);
    FacebodyClient client(sKey, sSecret, configuration);
    Model::GenerateHumanAnimeStyleRequest request;
    string tmpImageURL, outImageURL;
    int ret;

    tmpImageURL = url;
    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURL(tmpImageURL);

    auto outcome = client.generateHumanAnimeStyle(request);
    cout << endl << "facebody describeInstances returned:" << endl;
    cout << "error code: " << outcome.error().errorCode() << endl;
    cout << "requestId: " << outcome.result().requestId() << endl << endl;
    cout << "image url:" << outcome.result().getData().imageURL << endl;

    outImageURL = outcome.result().getData().imageURL;
    if (!outImageURL.empty() && cb) {
        ret = cb((char *)outImageURL.c_str(), data);
    }
    ShutdownSdk();
    return ret;
}

int facebody_config_and_recognize_expression_ai(char *key, char *secret, char *region_id,
                char *endpoint, char *url, facebody_recognize_expression_cb_t cb) {

    InitializeSdk();
    string sKey = key;
    string sSecret = secret;
    string sRegionId = region_id;
    string sEndPoint = endpoint;
    cout << "Key: " << sKey.c_str() << endl;
    cout << "Secret: " << sSecret.c_str() << endl;
    cout << "RegionId: " << sRegionId.c_str() << endl;
    cout << "EndPoint: " << sEndPoint.c_str() << endl;
    configuration.setRegionId(sRegionId);
    configuration.setEndpoint(sEndPoint);
    FacebodyClient client(sKey, sSecret, configuration);
    Model::RecognizeExpressionRequest request;
    string tmpImageURL;
    string expression;
    float faceProbability;
    face_rect_t face_rect;
    int ret;

    tmpImageURL = url;
    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURL(tmpImageURL);
    auto outcome = client.recognizeExpression(request);
    cout << endl << "facebody describeInstances returned:" << endl;
    cout << "error code: " << outcome.error().errorCode() << endl;
    cout << "requestId: " << outcome.result().requestId() << endl << endl;

    //cout << "expression:" << outcome.result().getData().elements[0].expression << endl;
    cout << "face probablility:" << outcome.result().getData().elements[0].faceProbability << endl;
    cout << "x:" << outcome.result().getData().elements[0].faceRectangle.left << endl;
    cout << "y:" << outcome.result().getData().elements[0].faceRectangle.top << endl;
    cout << "w:" << outcome.result().getData().elements[0].faceRectangle.width << endl;
    cout << "h:" << outcome.result().getData().elements[0].faceRectangle.height << endl;

    if (cb) {
        expression = outcome.result().getData().elements[0].expression;
        if (!expression.empty()) {
            faceProbability = outcome.result().getData().elements[0].faceProbability;
            face_rect.x = 20;//outcome.result().getData().elements[0].faceRectangle.left;
            face_rect.y = 20;//outcome.result().getData().elements[0].faceRectangle.top;
            face_rect.w = outcome.result().getData().elements[0].faceRectangle.width;
            face_rect.h = outcome.result().getData().elements[0].faceRectangle.height;
            ret = cb((char *)expression.c_str(), faceProbability, &face_rect);
        }
    }
    ShutdownSdk();
    return ret;
}

int facebody_config_and_comparing_ai(char *key, char *secret, char *region_id,
                        char *endpoint, char *url_a, char *url_b,
                        facebody_comparing_cb_t cb) {
    InitializeSdk();
    string sKey = key;
    string sSecret = secret;
    string sRegionId = region_id;
    string sEndPoint = endpoint;
    cout << "Key: " << sKey.c_str() << endl;
    cout << "Secret: " << sSecret.c_str() << endl;
    cout << "RegionId: " << sRegionId.c_str() << endl;
    cout << "EndPoint: " << sEndPoint.c_str() << endl;
    configuration.setRegionId(sRegionId);
    configuration.setEndpoint(sEndPoint);
    configuration.setConnectTimeout(6000);
    configuration.setReadTimeout(6000);
    FacebodyClient client(sKey, sSecret, configuration);
    Model::CompareFaceRequest request;
    string tmpImageURLA, tmpImageURLB;
    face_rect_t face_rect;
    float confidence;
    int ret;

    tmpImageURLA = url_a;
    tmpImageURLB = url_b;

    request.setScheme("http");
    request.setMethod(HttpRequest::Method::Post);
    request.setImageURLA(tmpImageURLA);
    request.setImageURLB(tmpImageURLB);
    request.setConnectTimeout(6000);
    request.setReadTimeout(6000);

    auto outcome =  client.compareFace(request);
    //cout << endl << "facebody describeInstances returned:" << endl;
    //cout << "error code: " << outcome.error().errorCode() << endl;
    //cout << "requestId: " << outcome.result().requestId() << endl << endl;

    cout << "confidence:" << outcome.result().getData().confidence << endl;
    cout << "x:" << outcome.result().getData().rectAList[0] << endl;
    cout << "y:" << outcome.result().getData().rectAList[1] << endl;
    cout << "w:" << outcome.result().getData().rectAList[2] << endl;
    cout << "h" << outcome.result().getData().rectAList[3] << endl;

    if (cb) {
        confidence = outcome.result().getData().confidence;
        face_rect.x = outcome.result().getData().rectAList[0];
        face_rect.y = outcome.result().getData().rectAList[1];
        face_rect.w = outcome.result().getData().rectAList[2];
        face_rect.h = outcome.result().getData().rectAList[3];
        ret = cb(confidence, &face_rect);
    }
    ShutdownSdk();
    return ret;
}

}
