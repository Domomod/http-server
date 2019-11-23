//
// Created by dominik on 06.11.19.
//

#ifndef HTTP_SERVER_HTTPRESPONSE_H
#define HTTP_SERVER_HTTPRESPONSE_H

class HttpRequest;

/*!
 * @brief http response representation
 */
class HttpRequest{
public:
    void setResponse(std::string code);
    void setHttpVersion(std::string version);
    void setSerwerDate(std::string date);
    void setSerwer(std::string serwer);
    void setCookie(std::string cookie);
    void setExpires(std::string expire);
    void setCacheControl(std::string cache);
    void setConnection(std::string con){connection=con};
    void setTransferEncoding(std::string encoding){transferEncoding=encoding};
    void setContentType(std::string type){contentType=type};
    void setBody(std::string message){body=message;}
private:
    std::string responseCode;
    std::string httpVersion;
    std::string date;
    std::string serwer;
    std::string setCookie;
    std::string expires;
    std::string cacheControl;
    std::string connection;
    std::string transferEncoding;
    std::string contentType; //MIME TYPE!
    std::string body;

};

#endif //HTTP_SERVER_HTTPRESPONSE_H
