// pyweibo.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "pyweibo.h"
#include "ssclientda/export/ssclientda.h"
#include "json/inc/json.h"

IClientServiceFactory* _ssclientda = 0;
#define _accountsvc GetClientdaSvc()->GetAccountSvc()
#define _weibosvc GetClientdaSvc()->GetWeiboSvc()
#define _noticesvc GetClientdaSvc()->GetNoticeSvc()

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			 if (!_ssclientda)
				 ::SSInit(&_ssclientda);
		}break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH: 
		{
			if (_ssclientda)
				::SSUninit();
		}break;
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
std::string bool2number(const std::string& sender)
{
	Json::Reader j_reader;
	Json::FastWriter j_writer;
	Json::Value j_sender(Json::objectValue), j_out(Json::objectValue);
	if (j_reader.parse(sender, j_sender)) {
		if (!j_sender["allow_all_act_msg"].isNull())
			j_sender["allow_all_act_msg"] = j_sender["allow_all_act_msg"].asBool() ? 1 : 0;
		
		if (!j_sender["following"].isNull())
			j_sender["following"] = j_sender["following"].asBool() ? 1 : 0;

		if (!j_sender["geo_enabled"].isNull())
			j_sender["geo_enabled"] = j_sender["geo_enabled"].asBool() ? 1 : 0;

		if (!j_sender["verified"].isNull())
			j_sender["verified"] = j_sender["verified"].asBool() ? 1 : 0;
	}
	return j_writer.write(j_sender);
}
std::string simplejson(const std::string& sender)
{
	Json::Reader j_reader;
	Json::FastWriter j_writer;
	Json::Value j_sender(Json::objectValue), j_out(Json::objectValue);
	if (j_reader.parse(sender, j_sender)) {
		if (!j_sender["screen_name"].isNull())
			j_out["screen_name"] = j_sender["screen_name"].asString();
		
		if (!j_sender["url"].isNull())
			j_out["url"] = j_sender["url"].asString();

		if (!j_sender["profile_image_url"].isNull())
			j_out["profile_image_url"] = j_sender["profile_image_url"].asString();
	}
	return j_writer.write(j_out);
}

IClientServiceFactory* GetClientdaSvc() {
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
weibo_handle_t get_weibo_tree(const char* cursorid, int count, char** j_weibos, int* len) 
{
	if (!_ssclientda)
		return 0;

	WeiboMessageInfosGroup groups;
	int result = _weibosvc->GetMessageTree(cursorid, count, 1, groups);
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
				j_weibo["sender"] = bool2number(pos->sender);
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
			strcpy((*j_weibos), json_tree.c_str());
			*((*j_weibos)+length) = '\0';
			return (weibo_handle_t)(*j_weibos);
		}
	}
	return 0;
}
weibo_handle_t get_weibo(const char* msgid, char** j_strweibo, int* len)
{
	WeiboMessageInfoT weibo;
	int result = _weibosvc->GetMessageById(msgid, weibo);
	if (result == 0) {
		Json::Value j_weibo(Json::objectValue);
		j_weibo["msgid"] = weibo.msgid;
		j_weibo["msgtype"] = weibo.msgtype;
		j_weibo["rootid"] = weibo.rootid;
		j_weibo["sender"] = bool2number(weibo.sender);
		j_weibo["contents"] = weibo.contents;
		j_weibo["timestamp"] = Json::Value((double)weibo.timestamp);
		
		Json::FastWriter j_writer;
		std::string str = j_writer.write(j_weibo);
		int length = str.length();
		if (length > 0) {
			*len = length +1;
			*j_strweibo = (char*)malloc(length+1);
			strcpy((*j_strweibo), str.c_str());
			*((*j_strweibo)+length) = '\0';
			return (weibo_handle_t)(*j_strweibo);
		}
	}
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

