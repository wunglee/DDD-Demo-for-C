//
// Created by 王立 on 2021/5/25.
//

#ifndef DDD_DEMO_FOR_C_HTTP_H
#define DDD_DEMO_FOR_C_HTTP_H

#include <string>
#include <boost/any.hpp>
/**
 * 这是模拟，随便写
 */
class HttpRequest {
public:
  HttpRequest(const std::string &url,
              boost::any body=boost::none) : url(url), body(body) {}
  std::string url;
  boost::any body;
};
class HttpResponse {
public:
    HttpResponse(const boost::any &body=boost::none) : body(body) {}
    boost::any body;
};


#endif //DDD_DEMO_FOR_C_HTTP_H
