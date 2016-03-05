#include "BaiduTranslator.h"
#include "Utils.h"
#include <json/json.h>
#include <iostream>
#include <sstream>

BaiduTranslator::BaiduTranslator(QObject *parent):
    Translator(parent)
{
    setSite("http://api.fanyi.baidu.com/api/trans/vip/translate");
    getAuth("Baidu");
    std::cout << _appid << _secret << std::endl;
}

BaiduTranslator::~BaiduTranslator()
{
    //
}

std::string BaiduTranslator::getSign(std::string query,
                        std::string appid, std::string secret,
                        std::string salt)
{
    std::string concat = appid + query + salt + secret;
    _sign = Utils::getStrMD5(concat);
    return _sign;
}

void BaiduTranslator::handle_write(char *ptr, size_t size, size_t nmemb) {
    std::cout << "Recieved from Baidu:" << std::string(ptr, size*nmemb) << std::endl;
    _result += std::string(ptr, size*nmemb);
}
void BaiduTranslator::parseResult(std::string json)
{
    if(json.empty())
    {
        std::cerr << "Request failed." << std::endl;
    }

    Json::Reader _reader;
    Json::Value _value;
    bool ret = _reader.parse(json, _value);
    if(!ret) {
        std::cerr << "JSON parse failed." << std::endl;
    }
    std::stringstream baiduSS;
    if (_value.isMember("error_code")) {
        std::string error_code = _value["error_code"].asString();
        std::string error_msg = _value["error_msg"].asString();
        baiduSS << "error_code:" << error_code << "\n";
        baiduSS << "error_msg:" << error_msg << "\n";
    }
    else {
        unsigned int i = 0;
        std::string from = _value["from"].asString();
        std::string dst;
        baiduSS << "Source language : " << from << "\n";
        baiduSS << "Translate result:\n" << dst;
        for(i=0; i<_value["trans_result"].size(); i++) {
            dst = _value["trans_result"][i]["dst"].asString();
#ifdef WIN32
            dst = Utils::UTF8ToGBK(dst);
#endif
            baiduSS << dst << "\n";
        }
    }
    _result = baiduSS.str();
    emit resultChanged();
}
std::string BaiduTranslator::updateRequet()
{
    _request.clear();
    updateSalt();
    getSign(_query, _appid, _secret, _salt);
    _request=_site+"?q="+Utils::urlEncode(_query)+"&from="+_from+"&to="+_to+"&appid="+_appid+"&salt="+_salt+"&sign="+_sign;
    std::cout << "Request:" << _request << std::endl;
    return _request;
}
