//
// Created by dominik on 04.11.19.
//

#include <http-server/http/HttpRequest.h>
#include <http-server/http/HttpParser.h>

/*!
 * @brief Translates a http request from a string to a HttpRequest.
 * @details Constraints on the string containing the http request:
 *          <ul>
 *              <li> must contain only one http request, with the end indicating CR LF CR LF trimmed.
 *              <li> use only single spaces as word's separators.
 *              <li> use CR LF as line's separators.
 *              <li> can't contain the body section.
 *          </ul>
 * @param message Message to be parsed.
 * @return Message as HttpRequest
 * @see HttpRequest
 */
HttpRequest HttpParser::parse_message(const std::__cxx11::string &message)
{
    HttpRequest httpRequest;

    std::vector<std::__cxx11::string> request_lines;
    iter_split(request_lines, message, boost::algorithm::first_finder("\r\n"));
    bool is_header = true;
    for (auto line : request_lines)
    {
        if (is_header)
        {
            parse_request_type(httpRequest, line);
            is_header = false;
        }
        else
        {
            parse_keys_and_values(httpRequest, line);
        }
    }
    return httpRequest;
}

/*!
 * @brief Translates a line of header key and values to a multi-dictionary (one key  can hold multiple values).
 * @param httpRequest The http request in which the translated data will be stored.
 * @param line line of header key and values separated by single spaces
 */
void HttpParser::parse_keys_and_values(HttpRequest &httpRequest, std::__cxx11::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));

    for(auto& word : words){
        if (word.back() == ':' || word.back() == ',')
        {
            word.pop_back();
        }
    }



    httpRequest.header_info.insert(
                    std::pair<std::__cxx11::string, std::vector<std::__cxx11::string>>(
                            words[0], std::vector<std::__cxx11::string>(words.begin() + 1, words.end())
                    )
            );
}

/*!
 * @brief Translates the first line of http request which contains the request type, file, params and http protocol version.
 * @param httpRequest The http request in which the translated data will be stored.
 * @param line Line such as GET|PUT|POST|ect. /<filename>?<params> HTTP<digit>+.<digit>+
 */
void HttpParser::parse_request_type(HttpRequest &httpRequest, std::__cxx11::string &line)
{
    std::vector<std::__cxx11::string> words;
    iter_split(words, line, boost::algorithm::first_finder(" "));
    httpRequest.request_type = words[0];
    httpRequest.path = words[1];
    httpRequest.http_version = words[2];
}