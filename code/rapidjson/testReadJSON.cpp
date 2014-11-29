#include "CCStdC.h"
#include "cocos2d.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
using namespace  rapidjson;

USING_NS_CC;

int main()
{
	auto path = FileUtils::getInstance()->getWritablePath();

	//*** ��ȡ json �ļ� ***
	rapidjson::Document readdoc;
	bool bRet = false;
	ssize_t size = 0;
	std::string load_str;

	// getFileData �����ָ������ȡ��Ŀ¼�� Resource �ļ���
	unsigned char* titlech = FileUtils::getInstance()->getFileData(path, "r", &size);
	load_str = std::string((const char*)titlech,size);

	//load_str = cocos2d::FileUtils::getInstance()->getStringFromFile("..\\myhero.json");
	readdoc.Parse<0>(load_str.c_str());	
	if(readdoc.HasParseError())
	{
		CCLOG("GetParseError%s\n", readdoc.GetParseError());
	}

	if(!readdoc.IsObject())
		return 0;

	rapidjson::Value& _json = readdoc["json"];
	const char* ch = _json.GetString();
	cocos2d::log(ch);
	cocos2d::log(_json.GetString());

	rapidjson::Value& _array = readdoc["array"];
	if(_array.IsArray())
	{
		CCLOG("test");
		for(int i=0; i<_array.Capacity(); i++)
		{
			//CCLOG("%d", i);
			rapidjson::Value& arraydoc = _array[i];
			if(arraydoc.HasMember("inttag"))
			{
				int _inttag = arraydoc["inttag"].GetInt();
				CCLOG("%d", _inttag);
			}
			if(arraydoc.HasMember("doubletag"))
			{
				double _doubletag = arraydoc["doubletag"].GetDouble();
				CCLOG("%lf", _doubletag);
			}
			if(arraydoc.HasMember("booltag"))
			{
				bool _booltag = arraydoc["booltag"].GetBool();
				CCLOG("%d", _booltag);
			}
			if(arraydoc.HasMember("hellotag"))
			{
				const char* _hellotag = arraydoc["hellotag"].GetString();
				CCLOG("%s", _hellotag);
			}
		}
	}

    return 0;
}
