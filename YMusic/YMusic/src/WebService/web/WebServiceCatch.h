#pragma once

#include "../Utilty/base/Buffer.h"
enum CatchStrategyType
{
	CST_CATCH         = 1,   //ǿ��catch
	CST_NOCATCH       = 1<<1,//��ǿ��catch
	CST_NET           = 1<<2,//������
	CST_NONET         = 1<<3, //������
	CST_UPDATA        = 1<<4

};
class CWebServiceCatch
{
	static const int cacheVer = 1;
public:
	bool LoadCache(const std::string& url,CBuffer& buffer);
	void SaveCache(const std::string& url,CBuffer& buffer,int nTimeLen);
private:
	std::string GetFilePath(const std::string& url);
};


