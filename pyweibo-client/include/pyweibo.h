/**
 * pyweibo.h
 */

#ifndef WEIBOAPI_H
#define WEIBOAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined (PYWEIBO_EXPORTS)
# define WEIBOAPI_EXPORT __declspec(dllexport)
#else
# define WEIBOAPI_EXPORT
#endif

typedef long weibo_handle_t;

WEIBOAPI_EXPORT int login(const char* username, const char* password);
WEIBOAPI_EXPORT int logout(const char* username, const char* password);
WEIBOAPI_EXPORT weibo_handle_t get_weibo_tree(const char* cursorid, int count, char** j_weibos, int* len);
WEIBOAPI_EXPORT weibo_handle_t get_weibo(const char* msgid, char** j_weibo, int* len);
WEIBOAPI_EXPORT void free_weibo_handle(weibo_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif 
