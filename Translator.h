#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <curl/curl.h>
#include <QObject>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
class Translator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(QString from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QString to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
    Q_PROPERTY(QString appid READ appid WRITE setAppid NOTIFY appidChanged)
    Q_PROPERTY(QString secret READ secret WRITE setSecret NOTIFY secretChanged)
signals:
    void queryChanged();
    void fromChanged();
    void toChanged();
    void resultChanged();
    void appidChanged();
    void secretChanged();
public:
    //QMLRegisterType only allow the default constructor
    Translator(QObject *parent=0);
    virtual ~Translator();
    std::string blockTranslate();
    Q_INVOKABLE void translate();
    Q_INVOKABLE void translate(QString src);


    QString query() const { return QString(_query.c_str()); }
    QString from() const { return QString(_from.c_str()); }
    QString to() const { return QString(_to.c_str()); }
    QString result() const { return QString(_result.c_str()); }
    QString appid() const { return QString(_appid.c_str()); }
    QString secret() const { return QString(_secret.c_str()); }
    Q_INVOKABLE void setQuery(QString query);
    Q_INVOKABLE void setFrom(QString from);
    Q_INVOKABLE void setTo(QString to);
    Q_INVOKABLE void setAppid(QString appid);
    Q_INVOKABLE void setSecret(QString secret);

private:
    int init();
    virtual std::string getSign(std::string query,
                        std::string appid, std::string secret,
                        std::string salt);
    virtual void handle_write(char *ptr, size_t size, size_t nmemb) = 0;
    virtual void parseResult(std::string json) = 0;
    virtual std::string updateRequet();
    static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
    {
        size_t realsize = size * nmemb;
        ((Translator *) userdata)->handle_write(ptr, size, nmemb);
        return realsize;
    }

protected:
    void setSite(std::string site);
    void updateSalt();
    int getAuth(std::string siteName);
protected:
    std::string _site;
    std::string _query;
    std::string _from;
    std::string _to;
    std::string _appid;
    std::string _secret;
    std::string _salt;
    std::string _sign;
    std::string _request;
    struct curl_slist *_header;
    CURL *_curl;
    std::string _result;
    int _random;
    boost::shared_ptr<boost::thread> _transThread;
    boost::mutex _mutex;
};

#endif
