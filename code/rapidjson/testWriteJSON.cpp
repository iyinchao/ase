#include "CCStdC.h"
#include "cocos2d.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
using namespace  rapidjson;

USING_NS_CC;

int main()
{
	//*** 生成 json 文件，存储在 getWritablePath 文件夹下 ***
    rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	
	// json object 格式添加 “名称/值” 对
	object.AddMember("inttag", 1, allocator);
	object.AddMember("doubletag", 1.0, allocator);
	object.AddMember("booltag", true, allocator);
	object.AddMember("hellotag", "helloworld", allocator);
	
	// json 加入数组
	array.PushBack(object, allocator);
	
	// json object 格式添加 “名称/值” 对
	writedoc.AddMember("json", "json string", allocator);
	writedoc.AddMember("array", array, allocator);
 
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("myhero.json");
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s",buffer.GetString());

    return 0;
}
