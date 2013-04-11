// webserver.h

/*  Copyright 2013 Aalborg University. All rights reserved.
 *   
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED BY Aalborg University ''AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Aalborg University OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 *  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *  
 *  The views and conclusions contained in the software and
 *  documentation are those of the authors and should not be interpreted
 *  as representing official policies, either expressed.
 */

/** \defgroup webserver Webserver
 *
 *  The webserver is a single threaded event based webserver, built on
 *  top of the event loop implemented in LibEV.
 *
 *  \{
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <stddef.h>

// HTTP status codes according to
// http://www.w3.org/Protocols/rfc2616/rfc2616.html
#define WS_HTTP_STATUS_CODE_MAP(XX) \
	XX(200,200 OK) \
	XX(404,404 Not Found)

enum ws_http_status_code
{
#define XX(num, str) WS_HTTP_##num = num,
	WS_HTTP_STATUS_CODE_MAP(XX)
#undef XX
};

// Port numbers are assigned according to
// http://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xml
// (Site may have very long loading time)
#define WS_PORT_MAP(XX) \
   XX(  80, HTTP    ) \
   XX( 443, HTTPS   ) \
   XX(8080, HTTP_ALT)

enum ws_port
{
#define XX(num, str) WS_PORT_##str = num,
   WS_PORT_MAP(XX)
#undef XX
};

// Structs
struct ev_loop;
struct ws;
struct ws_request;
struct ws_response;

// Callbacks
typedef int (*nodata_cb)(struct ws_request *req);
typedef int (*data_cb)(struct ws_request *req,
      const char *buf, size_t len);

// Settings
struct ws_settings {
   unsigned short int port;
   nodata_cb on_request_begin;
   data_cb   on_request_method;
   data_cb   on_request_url;
   nodata_cb on_request_url_complete;
   data_cb   on_request_header_field;
   data_cb   on_request_header_value;
   nodata_cb on_request_header_complete;
   data_cb   on_request_body;
   nodata_cb on_request_complete;
};
#define WS_SETTINGS_DEFAULT { \
   .port = WS_PORT_HTTP, \
   .on_request_begin = NULL, \
   .on_request_method = NULL, \
   .on_request_url = NULL, \
   .on_request_url_complete = NULL, \
   .on_request_header_field = NULL, \
   .on_request_header_value = NULL, \
   .on_request_header_complete = NULL, \
   .on_request_body = NULL, \
   .on_request_complete = NULL }

// Webserver functions
struct ws *ws_create(struct ws_settings *settings, struct ev_loop *loop);
void ws_destroy(struct ws *instance);
void ws_start(struct ws *instance);
void ws_stop(struct ws *instance);

// Response functions
struct ws_response *ws_response_create(
      struct ws_request *req,
      enum ws_http_status_code status,
      char *body);

#endif

/** } */
