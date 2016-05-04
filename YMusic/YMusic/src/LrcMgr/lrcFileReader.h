
/***********************************************************
 *	FileName��lrcFileReader.h
 *  Author  ��DFn Li
 *  Timer   : 2013/3/5 14:24
 *  E-Mail  : libyyu@qq.com
 *  Comment : read lrc from file
 *  Version : 1.0.0.1
 ***********************************************************/
#ifndef _LRCFILEREADER_H
#define _LRCFILEREADER_H

#pragma once

#include<vector>

#include "../Utilty/lock/RzLock.h"

using namespace std;

class CLrcFileReader
{
	enum TextEncodedMode
	{
		TEM_ANSI,
		TEM_UTF8,
		TEM_UNICODE,
		TEM_UNICODE_BIG
	};
public:
	TextEncodedMode CheckTextEncodedMode(FILE * file);
public:
	CString sArtist;// ������
	CString sTitle;// ������
	CString sAlbum;//ר����
	CString sLrcWriter;//���������

	int Offset;//ȫ��ʱ�����������ȫ����ǰ
	int iCount;//���LrcNode����
	class LrcNode
	{
	public:
		int StartShowTime;//��λ���룬�뿪ʼ����ʱ�ļ��ֵ
		CString sLyric;//�������
		int length;
		int OldPos;//�ϴ���ʾ��λ��
		LrcNode(int nStartShowTime,CString s )
		{
			StartShowTime = nStartShowTime;
			sLyric = s;
			length = 0;
			OldPos = 0;
		}
// 		LrcNode operator = (LrcNode& node)
// 		{
// 			StartShowTime = node.StartShowTime;
// 			sLyric = node.StartShowTime;
// 			length = node.StartShowTime;
// 			OldPos = node.OldPos;
// 			return (*this);
// 		}
		bool operator <(LrcNode &node)
		{
			return StartShowTime<node.StartShowTime;
		}
	};
	vector<LrcNode> Lyrics; 
	CRzLock         m_lock;

	bool Load(const wchar_t * FileName);
	bool Load(const char * FileName);

	bool Parse(FILE * file );//�����ļ�
	bool ParseLine(CString &line);//����һ��,�ɹ�������һ��tag, ����true�����򷵻�false
	void Clear();	
private:
//	TextEncodedMode CheckTextEncodedMode(FILE * file);
	int m_nErrorCounter;
};

#endif//_LRCFILEREADER_H