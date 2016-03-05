#include "Translator.h"
#include "Utils.h"
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

Translator::Translator(QObject *parent):
        QObject(parent),
        _site("http://api.fanyi.baidu.com/api/trans/vip/translate"),
        _query("hello world"),
        _from("auto"),
        _to("zh"),
        _appid("appid"),
        _secret("secret"),
        _salt("98765"),
        _header(NULL)
{
    init();
}
Translator::~Translator()
{
    curl_slist_free_all(_header);
    curl_easy_cleanup(_curl);
}

int Translator::init()
{
    srand(time(NULL));
    _header = curl_slist_append(_header, "Accept: */*");
    _curl = curl_easy_init();
    if(!_curl)
    {
        std::cout << "Error to initialize libcurl." << std::endl;
        return 1;
    }
    return 0;

}

void Translator::setSite(std::string site)
{
    _site = site;
}
void Translator::setFrom(QString from)
{
    _from = from.toStdString();
}
void Translator::setTo(QString to)
{
    _to = to.toStdString();
}
void Translator::setQuery(QString query)
{
    _query = query.toStdString();
    //for(std::basic_string<char>::iterator iter = _query.begin(); iter != _query.end(); iter++)
    //    if(*iter == '\n')
    //        *iter = ' ';
}
void Translator::setAppid(QString appid) {
    _appid = appid.toStdString();
}
void Translator::setSecret(QString secret) {
    _secret = secret.toStdString();
}

std::string Translator::getSign(std::string ,
                        std::string , std::string ,
                        std::string )
{
    return _site;
}

void Translator::translate()
{
    _transThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Translator::blockTranslate, this)));
}
void Translator::translate(QString src)
{
    setQuery(src);
    translate();
}

std::string Translator::blockTranslate()
{
    boost::mutex::scoped_lock lock(_mutex);
    _result.clear();
    updateRequet();
    curl_easy_setopt(_curl, CURLOPT_URL, _request.c_str());
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _header);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)this);//the last parameter in write_callback, which is FILE poniter to stdout by default
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_callback);
    CURLcode res = curl_easy_perform(_curl);
    if(CURLE_OK!=res)
    {
        std::cerr << "curl_easy_perform failed: " << curl_easy_strerror(res) << std::endl;
        return NULL;
    }
    else
    {
        parseResult(_result);
    }

    return _result;
}

std::string Translator::updateRequet()
{
    _request.clear();
    updateSalt();
    getSign(_query, _appid, _secret, _salt);
    _request=_site+"?q="+Utils::urlEncode(_query)+"&from="+_from+"&to="+_to+"&appid="+_appid+"&salt="+_salt+"&sign="+_sign;
    //std::cout << "Request:" << _request << std::endl;
    return _request;
}
void Translator::updateSalt()
{
    _random = rand();
    char tmp[33];
    sprintf(tmp, "%d", _random);
    _salt = std::string(tmp);
}

int Translator::getAuth(std::string siteName)
{
    bool ret;
    std::ifstream inputFs;
    inputFs.open("config.json");
    std::string content;
    std::stringstream ss;
    ss << inputFs.rdbuf();
    content = ss.str();
    Json::Reader reader;
    Json::Value value;
    ret = reader.parse(content, value);
    if(!ret) {
        std::cerr << "config file type error." << std::endl;
        return 1;
    }
    _appid = value[siteName]["appid"].asString();
    _secret = value[siteName]["secret"].asString();

    inputFs.close();
    return 0;
}
