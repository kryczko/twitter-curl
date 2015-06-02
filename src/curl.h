/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2012, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include <stdio.h>
#include <iostream>
#include <curl/curl.h>
#include <string.h>

#include "info.h"


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int c_curl(char* url, char* head, char* body, char* date, char* title) {
      CURL *curl_handle;
      static const char *headerfilename = head;
      FILE *headerfile;
      static const char *bodyfilename = body;
      FILE *bodyfile;
 
      curl_global_init(CURL_GLOBAL_ALL);
 
      /* init the curl session */ 
      curl_handle = curl_easy_init();
 
      /* set URL to get */ 
      curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
      /* no progress meter please */ 
      curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
      /* send all data to this function  */ 
      curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
      /* open the header file */ 
      headerfile = fopen(headerfilename, "wb");
      if(!headerfile) {
        curl_easy_cleanup(curl_handle);
        return -1;
      }
 
      /* open the body file */ 
      bodyfile = fopen(bodyfilename, "wb");
      if(!bodyfile) {
        curl_easy_cleanup(curl_handle);
        fclose(headerfile);
        return -1;
      }
 
      /* we want the headers be written to this file handle */ 
      curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, headerfile);
 
      /* we want the body be written to this file handle instead of stdout */ 
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
      
      
      /* get it! */ 
      if (curl_easy_perform(curl_handle)) {
          return -1;
      }
 
      /* close the header file */ 
      fclose(headerfile);
      
      fputs("{", bodyfile);
      char json_date[100], json_title[100];
      sprintf(json_date, "\"date\": %s,", date);
      sprintf(json_title, "\"title\": %s", title);
      fputs(json_date, bodyfile);
      fputs(json_title, bodyfile);
      fputs("}", bodyfile);
 
      /* close the body file */ 
      fclose(bodyfile);
 
      /* cleanup curl stuff */ 
      curl_easy_cleanup(curl_handle);
      return 0;
}

bool curl(Item* q, Global_Info* i) {
    /* Since we are using a C library, we need to convert
       the strings to chars. In C++, it is much more conv
       enient to use string.                             */
    
    char char_url[1024], char_head[1024], char_body[1024], char_date[1024], char_title[1024];
    strncpy(char_url, (i->total + q->currentquery()).c_str(), sizeof(char_url));
    strncpy(char_head, (q->currentheader() + ".js").c_str(), sizeof(char_head));
    strncpy(char_body, (q->currentbody() + ".js").c_str(), sizeof(char_body));
    strncpy(char_date, (q->current_date()).c_str(), sizeof(char_date));
    strncpy(char_title, (q->title).c_str(), sizeof(char_title));
    if (!c_curl(char_url, char_head, char_body, char_date, char_title)) {
        std::cout << "*** Success with curl for: " << q->title << "  |  date: " << q->current.tm_year + 1900 << "-" << q->current.tm_mon + 1 << "-" << q->current.tm_mday << " ***\n";
        return true;
    } 
    return false;
}