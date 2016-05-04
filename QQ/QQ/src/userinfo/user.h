#ifndef _user_h_
#define _user_h_

enum UserState
{	
	US_OFFLINE,//����
	US_ONLINE,//����
	US_HIDE,//����
	US_AWAY,//�뿪
	US_BUSY,//æµ
	US_MUTEX//�����
};

#define MAX_BUFSIZE 256
//�����û��ṹͼ
typedef struct UserInfo
{
	char _id[MAX_BUFSIZE];//�û�Id��
	char _passwd[MAX_BUFSIZE];//�û�����
	char _nickname[MAX_BUFSIZE];//�û��ǳ�
	char _logo[MAX_BUFSIZE];//�û�logo
	char _signature[MAX_BUFSIZE*2];//����ǩ��
	UserState _state;//�û���״̬
	long _lastlogin;//�ϴε�¼ʱ��
	char _ip[MAX_BUFSIZE];//�û�ip
	unsigned long _port;//�˿�
	UserInfo()
	{
		memset(_id,0,MAX_BUFSIZE);
		memset(_passwd,0,MAX_BUFSIZE);
		memset(_nickname,0,MAX_BUFSIZE);
		memset(_logo,0,MAX_BUFSIZE);
		memset(_signature,0,MAX_BUFSIZE*2);
		memset(_ip,0,MAX_BUFSIZE);
		_state = US_OFFLINE;
		_lastlogin = 0;
		_port = 0;
	}
	UserInfo& operator = (const UserInfo& other)
	{
		memset(_id,0,MAX_BUFSIZE);
		memset(_passwd,0,MAX_BUFSIZE);
		memset(_nickname,0,MAX_BUFSIZE);
		memset(_logo,0,MAX_BUFSIZE);
		memset(_signature,0,MAX_BUFSIZE*2);
		memset(_ip,0,MAX_BUFSIZE);

		memcpy(_id,other._id,strlen(other._id));
		memcpy(_passwd,other._passwd,strlen(other._passwd));
		memcpy(_nickname,other._nickname,strlen(other._nickname));
		memcpy(_logo,other._logo,strlen(other._logo));
		memcpy(_signature,other._signature,strlen(other._signature));
		memcpy(_ip,other._ip,strlen(other._ip));
		_state = other._state;
		_lastlogin = other._lastlogin;
		_port = other._port;
	
		return (*this);
	}
	void IP(const char* ip)
	{
		assert(ip);
		memset(_ip,0,MAX_BUFSIZE);
		memcpy(_ip,ip,strlen(ip));
	}
	void ID(const char* id)
	{
		assert(id);
		memset(_id,0,MAX_BUFSIZE);
		memcpy(_id,id,strlen(id));
	}
	void PSD(const char* psd)
	{
		assert(psd);
		memset(_passwd,0,MAX_BUFSIZE);
		memcpy(_passwd,psd,strlen(psd));
	}
	void NickName(const char* nickname)
	{
		assert(nickname);
		memset(_nickname,0,MAX_BUFSIZE);
		memcpy(_nickname,nickname,strlen(nickname));
	}
	void Logo(const char* logo)
	{
		assert(logo);
		memset(_logo,0,MAX_BUFSIZE);
		memcpy(_logo,logo,strlen(logo));
	}
	void Signature(const char* sig)
	{
		assert(sig);
		memset(_signature,0,MAX_BUFSIZE*2);
		memcpy(_signature,sig,strlen(sig));
	}
}USERINFO,*LPUSERINFO;





#endif//_user_h_