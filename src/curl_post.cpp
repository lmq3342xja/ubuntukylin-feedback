#include "curl_post.h"
#include <curl/curl.h>
#include <QDebug>

#define POSTURL "http://localhost/php/ubuntukylin_feedback.php"

//QString->char *
static void save_q_string_2_m_string(QString q_string, char **m_buf)
{
    int len;
    std::string tmp_str;
    char *m_buf_tmp;

    tmp_str = q_string.toStdString();
    len = tmp_str.length() + 1;

    if ((m_buf_tmp = (char *)malloc(len)) == NULL)
        return;

    memset(m_buf_tmp, 0, len);
    memcpy(m_buf_tmp, tmp_str.c_str(), len);

    if (*m_buf)
        free(*m_buf);
    *m_buf = m_buf_tmp;
}

bool sendPost(QString feedbackInfo){
    CURL *curl;
    CURLcode res;
    char * feedback_temp = (char *)malloc(2048);
    save_q_string_2_m_string(feedbackInfo,&feedback_temp);
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, POSTURL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, feedback_temp);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
//    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    res = CURLE_OK;

}

