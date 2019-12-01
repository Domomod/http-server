//
// Created by dominik on 30.11.19.
//

#ifndef HTTP_SERVER_HTTPSTATUSCODES_H
#define HTTP_SERVER_HTTPSTATUSCODES_H

#include <string>
#include <map>

/*!
 * @brief Status codes proposed by RFC7231
 */
enum class StatusCode : unsigned int
{
    Continue = 100,
    Switching_Protocols = 101,
    OK = 200,
    Created = 201,
    Accepted = 202,
    Non_Authoritative_Information = 203,
    No_Content = 204,
    Reset_Content = 205,
    Partial_Content = 206,
    Multiple_Choices = 300,
    Moved_Permanently = 301,
    Found = 302,
    See_Other = 303,
    Not_Modified = 304,
    Use_Proxy = 305,
    Temporary_Redirect = 307,
    Bad_Request = 400,
    Unauthorized = 401,
    Payment_Required = 402,
    Forbidden = 403,
    Not_Found = 404,
    Method_Not_Allowed = 405,
    Not_Acceptable = 406,
    Proxy_Authentication_Required = 407,
    Request_Time_out = 408,
    Conflict = 409,
    Gone = 410,
    Length_Required = 411,
    Precondition_Failed = 412,
    Request_Entity_Too_Large = 413,
    Request_URI_Too_Large = 414,
    Unsupported_Media_Type = 415,
    Requested_range_not_satisfiab = 416,
    Expectation_Failed = 417,
    Internal_Server_Error = 500,
    Not_Implemented = 501,
    Bad_Gateway = 502,
    Service_Unavailable = 503,
    Gateway_Time_out = 504,
    HTTP_Version_not_supported = 505
};

/*!
 * @brief Returns the reason phrase corresponding to given status code. Names as proposed by RFC7231
 * @param code A status code proposed by RFC4231
 * @return Corresponding reason phrase.
 */
static std::string ReasonPhrase(StatusCode code)
{
    static std::map<StatusCode, std::string> ReasonPhrases = {
            {StatusCode::Continue,                      "Continue"},
            {StatusCode::Switching_Protocols,           "Switching Protocols"},
            {StatusCode::OK,                            "OK"},
            {StatusCode::Created,                       "Created"},
            {StatusCode::Accepted,                      "Accepted"},
            {StatusCode::Non_Authoritative_Information, "Non_Authoritative_Information"},
            {StatusCode::No_Content,                    "No_Content"},
            {StatusCode::Reset_Content,                 "Reset_Content"},
            {StatusCode::Partial_Content,               "Partial_Content"},
            {StatusCode::Multiple_Choices,              "Multiple_Choices"},
            {StatusCode::Moved_Permanently,             "Moved_Permanently"},
            {StatusCode::Found,                         "Found"},
            {StatusCode::See_Other,                     "See_Other"},
            {StatusCode::Not_Modified,                  "Not_Modified"},
            {StatusCode::Use_Proxy,                     "Use_Proxy"},
            {StatusCode::Temporary_Redirect,            "Temporary_Redirect"},
            {StatusCode::Bad_Request,                   "Bad_Request"},
            {StatusCode::Unauthorized,                  "Unauthorized"},
            {StatusCode::Payment_Required,              "Payment_Required"},
            {StatusCode::Forbidden,                     "Forbidden"},
            {StatusCode::Not_Found,                     "Not_Found"},
            {StatusCode::Method_Not_Allowed,            "Method_Not_Allowed"},
            {StatusCode::Not_Acceptable,                "Not_Acceptable"},
            {StatusCode::Proxy_Authentication_Required, "Proxy_Authentication_Required"},
            {StatusCode::Request_Time_out,              "Request_Time_out"},
            {StatusCode::Conflict,                      "Conflict"},
            {StatusCode::Gone,                          "Gone"},
            {StatusCode::Length_Required,               "Length_Required"},
            {StatusCode::Precondition_Failed,           "Precondition_Failed"},
            {StatusCode::Request_Entity_Too_Large,      "Request_Entity_Too_Large"},
            {StatusCode::Request_URI_Too_Large,         "Request_URI_Too_Large"},
            {StatusCode::Unsupported_Media_Type,        "Unsupported_Media_Type"},
            {StatusCode::Requested_range_not_satisfiab, "Requested_range_not_satisfiab"},
            {StatusCode::Expectation_Failed,            "Expectation_Failed"},
            {StatusCode::Internal_Server_Error,         "Internal_Server_Error"},
            {StatusCode::Not_Implemented,               "Not_Implemented"},
            {StatusCode::Bad_Gateway,                   "Bad_Gateway"},
            {StatusCode::Service_Unavailable,           "Service_Unavailable"},
            {StatusCode::Gateway_Time_out,              "Gateway_Time_out"},
            {StatusCode::HTTP_Version_not_supported,    "HTTP_Version_not_supported"}
    };

    return ReasonPhrases[code];
}



#endif //HTTP_SERVER_HTTPSTATUSCODES_H
