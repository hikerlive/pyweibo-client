/**
 * weibo_service.h
 */

#include "sinaweibo/plugin_weibo.h"
#include "sqlite3/sqlite3.h"
#include <string>

class WeiboService {
public:
	WeiboService();
	~WeiboService();

	int Login(const char* username, const char* password);
	int Logout(const char* username, const char* password);
	int GetMessageTree(const char* cursorid, int count, WeiboMessageInfos& weibos);
	int GetMessageById(const char* msgid, WeiboMessageInfo& weibo);

private:
	static unsigned int __stdcall UpdateMessageThreadProc(void* param);
	int UpdateMessage(int incount, int& outcount);

private:
	std::string _username;
	std::string _password;
	sqlite* _sqlite;
	IPlugin* _weibo;
};

