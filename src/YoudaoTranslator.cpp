#include "YoudaoTranslator.h"
#include "Utils.h"
#include <json/json.h>
#include <iostream>
#include <sstream>

YoudaoTranslator::YoudaoTranslator(QObject *parent):
    Translator(parent)
{
    setSite("http://fanyi.youdao.com/openapi.do");
    getAuth("Youdao");
}

YoudaoTranslator::~YoudaoTranslator()
{
    //
}

void YoudaoTranslator::handle_write(char *ptr, size_t size, size_t nmemb)
{
    std::cout << "Recieved from Youdao:" << std::string(ptr, size*nmemb) << std::endl;
    _result += std::string(ptr, size*nmemb);
}
void YoudaoTranslator::parseResult(std::string json)
{
    if(json.empty()) {
        std::cerr << "JSON parse failed" << std::endl;
        return;
    }
    Json::Reader _reader;
    Json::Value _value;
    bool ret = _reader.parse(json, _value);
    if(!ret) {
        std::cerr << "JSON parse failed." << std::endl;
    }
    std::stringstream youdaoSS;
    unsigned int i,j;
    int error_code = _value["errorCode"].asInt();
    if(error_code != 0)
    {
        youdaoSS << "Error!\nError code:" << error_code << "\n";
    }
    if(_value.isMember("basic"))
    {
        std::string basic;
        for(i=0; i<_value["basic"]["explains"].size(); i++)
        {
            basic += _value["basic"]["explains"][i].asString();
        }
        youdaoSS << "[Basic]:\n" << basic << "\n\n";

    }
    if(_value.isMember("translation"))
    {
        std::string sentence;
        youdaoSS << "[Translate]:\n";
        for(i=0; i<_value["translation"].size(); i++) {

            sentence = _value["translation"][i].asString();
            youdaoSS << sentence << "\n" ;
        }
        youdaoSS << "\n" ;
    }
    if(_value.isMember("web"))
    {
        std::string web_key, web_value;
        youdaoSS << "[Web]:\n";
        for(i=0; i<_value["web"].size(); i++)
        {
            web_key = _value["web"][i]["key"].asString();
            youdaoSS << i << ". " << web_key << "\n";
            if(_value["web"][i]["value"].isArray()) {
                for(j=0; j<_value["web"][i]["value"].size(); j++) {
                    web_value += _value["web"][i]["value"][j].asString() + "; ";
                }

            }
            youdaoSS << "value:" << web_value << "\n";
            web_value.clear();
        }
    }
    std::string output = youdaoSS.str();
#ifdef WIN32
    //No need for GUI
    //output = Utils::UTF8ToGBK(output);
#endif
    _result =  output;
    emit resultChanged();
}
std::string YoudaoTranslator::updateRequet()
{
    _request.clear();
    _request = _site+"?keyfrom="+_appid+"&key="+_secret+"&type=data&doctype=json&version=1.1&q="+Utils::urlEncode(_query);
    //std::cout << "Request:" << _request << std::endl;
    return _request;
}
