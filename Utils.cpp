#include "Utils.h"
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <iomanip>

std::string Utils::UTF8ToGBK(const std::string strUTF8)
{
#ifdef WIN32
    const char *tmpUTF8 = strUTF8.c_str();
	int len = MultiByteToWideChar(CP_UTF8, 0, tmpUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, tmpUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
#else 
    char inbuf[TEXT_BUFSIZE];
    char outbuf[TEXT_BUFSIZE];
    size_t inlen = strUTF8.size();
    size_t outlen = TEXT_BUFSIZE;
    memcpy(inbuf, strUTF8.c_str(), inlen);
    code_convert("utf-8", "gbk", inbuf, &inlen, outbuf, &outlen);
    return std::string(outbuf);
#endif
}
std::string Utils::GBKToUTF8(const std::string strGBK)
{
#ifdef WIN32
    const char *tmpGBK = strGBK.c_str();
	int len = MultiByteToWideChar(CP_ACP, 0, tmpGBK, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, tmpGBK, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
#else
    char inbuf[TEXT_BUFSIZE];
    char outbuf[TEXT_BUFSIZE];
    size_t inlen = strGBK.size();
    size_t outlen = TEXT_BUFSIZE;
    memcpy(inbuf, strGBK.c_str(), inlen);
    code_convert("gbk", "utf-8", inbuf, &inlen, outbuf, &outlen);
    return std::string(outbuf);
#endif
}

#ifndef WIN32
int Utils::code_convert(const char *from_charset, const char *to_charset,
        char *inbuf, size_t *inlen,
        char *outbuf, size_t *outlen)
{
    iconv_t cd;
    char **pin = &inbuf;
    char **pout = &outbuf;
     
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) 
        return -1;

    memset(outbuf,0,*outlen);
    if (iconv(cd,pin,inlen,pout,outlen)==(unsigned long)-1) 
    {
        printf("Error: %s\n", strerror(errno));
    }
    iconv_close(cd);
    return 0;
}
#endif

std::string Utils::getStrMD5(std::string str)
{
    unsigned char *tmp_hash;
    char result[MD5_DIGEST_LENGTH*2 + 1] = {0};
    tmp_hash = MD5((const unsigned char*)str.c_str(), str.length(), NULL);
    unsigned long i;
    for(i=0; i<MD5_DIGEST_LENGTH; i++) {
        sprintf(result+2*i, "%02x", tmp_hash[i]);
    }
    return std::string(result);
}
std::string Utils::getStrSHA1(std::string str)
{
    unsigned char tmp_hash[SHA_DIGEST_LENGTH];
    char result[SHA_DIGEST_LENGTH*2 + 1] = {0};
    SHA1((const unsigned char*)str.c_str(), str.size(), tmp_hash);
    unsigned long i;
    for(i=0; i<SHA_DIGEST_LENGTH; i++) {
        sprintf(result+2*i, "%02x", tmp_hash[i]);
    }
    return std::string(result);
}

std::string Utils::urlEncode(std::string &url)
{
    std::stringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = url.begin(), n = url.end(); i != n; ++i) {
        std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        // make sure c is positive for msvc assertion
        if (c >= 0 && (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')) {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}
