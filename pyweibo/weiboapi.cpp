/**
 * weiboapi.cpp
 */

#include "weiboapi.h"
#include "ssclientda/ssclientda.h"
#include <windows.h>
#include <string>

IClientServiceFactory* _ssclientda = 0;
#define _accountsvc GetClientdaSvc()->GetAccountSvc()
#define _weibosvc GetClientdaSvc()->GetWeiboSvc()
#define _noticesvc GetClientdaSvc()->GetNoticeSvc()

APIENTRY DllMain( HMODULE hModule,
				  DWORD ul_reason_for_call,
				  LPVOID lpReserved)
{
	switch(ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: 
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// class NoticeReceiver
class NoticeReceiver : public INoticeReceiver{
public:
	NoticeReceiver(){}
	~NoticeReceiver(){}
	void OnNotify(eNoticeType type, NoticeBase* ldata) {
		if (type == Notice_OnlineLogin) {
		}
		else if (type == Notice_Offline) {
		}
	}
};

// weiboapi
int GetClientdaSvc() {
	if (0 == _ssclientda) {
		SSInit(&_ssclientda);
	}
	return _ssclientda;
}
int login(const char* username, const char* password)
{
	int ret = 0;
    _accountsvc->Login(username, password, eLoginByPhone, true, true);
	return ret;
}
int logout(const char* username, const char* password)
{
	int ret = 0;
	_accountsvc->Logout();
	return ret;
}
weibo_handle_t getWeiboTree(const char* cursorid, int count, const char** j_weibos, int* len) 
{
	if (!__ssclientda)
		return 0;

	WeiboMessageInfosGroup groups;
	result = _WeiboSvc->GetMessageTree(cursorid.c_str(), count, mode, groups);
	if (result == 0) {
		Json::Value j_tree(Json::arrayValue);
		for (WeiboMessageInfosGroup::iterator itr = groups.begin(); itr!=groups.end(); itr++) {
			WeiboMessageInfos& group = (*itr);
			Json::Value j_root(Json::arrayValue);
			for (WeiboMessageInfos::reverse_iterator pos=group.rbegin(); pos!=group.rend(); pos++) {
				Json::Value j_weibo(Json::objectValue);
				j_weibo["msgid"] = pos->msgid;
				j_weibo["msgtype"] = pos->msgtype;
				j_weibo["rootid"] = pos->rootid;
				j_weibo["sender"] = pos->sender;
				j_weibo["contents"] = pos->contents;
				j_weibo["timestamp"] = Json::Value((double)pos->timestamp);
				j_root.append(j_weibo);
			}
			j_tree.append(j_root);
		}

		Json::FastWriter j_writer;
		std::string json_tree = j_writer.write(j_tree);
		int length = json_tree.length();
		if (length > 0) {
			*len = length+1;
			*j_weibos = (char*)malloc(length+1);
			strcpy(*j_weibos, json_tree.c_str(), *len);
			j_weibos[length] = '\0';
			return (weibo_handle_t)(*j_weibos);
		}
	}

	return 0;
}
weibo_handle_t getWeiboById(const char* msgid, const char** j_weibo, int* len)
{
	
	return 0;
}
void free_weibo_handle(weibo_handle_t handle)
{
	if (handle) {
		char* p = (char*)handle;
		if (p) {
			free(p);
		}
	}
}
