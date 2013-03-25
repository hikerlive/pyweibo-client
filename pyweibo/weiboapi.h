/**
 * weiboapi.h
 */

#ifndef WEIBOAPI_H
#define WEIBOAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (WEIBOAPI_LIBRARY)
# define WEIBOAPI_EXPORT __declspec(dllexport)
#else
# define WEIBOAPI_EXPORT
#endif

typedef long weibo_handle_t;

int login(const char* username, const char* password);
int logout(const char* username, const char* password);
weibo_handle_t getWeiboTree(const char* cursorid, int count, const char** j_weibos, int* len);
weibo_handle_t getWeiboById(const char* msgid, const char** j_weibo, int* len);
void free_weibo_handle(weibo_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif 
