/**
 * weibo_service.cpp
 */

#include "weibo_service.h"

WeiboService::WeiboService()
{
}
WeiboService::~WeiboService()
{
}
int WeiboService::Login(const char* username, const char* password)
{
	return 0;
}
int WeiboService::Logout(const char* username, const char* password)
{
	return 0;
}
int WeiboService::GetMessageByTree(const char* cursorid, int count, WeiboMessageInfos& weibos)
{
	return 0;
}
int WeiboService::GetMessageById(const char* msgid, WeiboMessageInfo& weibo)
{
	return 0;
}
unsigned int __stdcall WeiboService::UpdateMessageThreadProc(void* param)
{
	return 0;
}
int WeiboService::UpdateMessage(int incount, int& outcount)
{
	return 0;
}
