#ifndef YOUDAO_TRANSLATOR_H
#define YOUDAO_TRANSLATOR_H
#include "Translator.h"

class YoudaoTranslator : public Translator
{
public:
    //YoudaoTranslator(std::string keyform, std::string key);
    YoudaoTranslator(QObject *parent=0);
    ~YoudaoTranslator();

    void handle_write(char *ptr, size_t size, size_t nmemb);
    void parseResult(std::string json);
    std::string updateRequet();
};

#endif /* YOUDAO_TRANSLATOR_H */
