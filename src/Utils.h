#ifndef UTILS_H
#define UTILS_H

#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <iconv.h>
#include <errno.h>
#endif

class  Utils
{
public:
	Utils();
	~Utils();
	static std::string UTF8ToGBK(const std::string strUTF8);
	static std::string GBKToUTF8(const std::string strGBK);

    static std::string getStrMD5(std::string str);
    static std::string getStrSHA1(std::string str);
    static std::string urlEncode(std::string &url);
    
#ifndef WIN32
    static const size_t TEXT_BUFSIZE = 2048;
    static int code_convert(const char *from_charset, const char *to_charset, 
            char *inbuf, size_t *inlen, 
            char *outbuf, size_t *outlen);
#endif
};


#endif /* UTILS_H */
