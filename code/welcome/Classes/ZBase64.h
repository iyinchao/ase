#pragma once
#include <stdio.h>
#include <string>
#include <iostream>

class ZBase64
{
public:
	/*����
    DataByte
        [in]��������ݳ���,���ֽ�Ϊ��λ
    */
    std::string Encode(const unsigned char* Data,int DataByte);
    /*����
    DataByte
        [in]��������ݳ���,���ֽ�Ϊ��λ
    OutByte
        [out]��������ݳ���,���ֽ�Ϊ��λ,�벻Ҫͨ������ֵ����
        ������ݵĳ���
    */
    std::string Decode(const char* Data,int DataByte,int& OutByte);
};

