#ifndef BAIDUTRANSLATOR_H
#define BAIDUTRANSLATOR_H
#include "Translator.h"
#include <QObject>

class BaiduTranslator: public Translator
{
    Q_OBJECT
public:
    BaiduTranslator(QObject *parent=0);
    ~BaiduTranslator();
    std::string getSign(std::string query,
                        std::string appid, std::string secret,
                        std::string salt);
    void handle_write(char *ptr, size_t size, size_t nmemb);
    void parseResult(std::string json);
    std::string updateRequet();

};/*BaiduTranslator*/

#endif
