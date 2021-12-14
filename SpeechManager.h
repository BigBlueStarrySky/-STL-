/*## ����������
** ����������**
-�ṩ�˵��������û�����
- ���ݽ��������̽��п���
- ���ļ��Ķ�д����*/
#pragma once
#include "Speaker.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#define FileName "speecher.csv"
using namespace std;

class SpeechManager
{
public:
	//�޲ι���
	SpeechManager();

	// ��ʾ�˵�
	void ShowMenu();

	// �˳�����
	void ExitSystem();

	// ��ʼ������:ѡ������ ����������
	void InitSpeech();

	// ����ѡ��
	void CreatSpeaker();

	// ��ʼ����  
	void StartContent();

	// ѡ�ֳ�ǩ
	void SpeechDraw();

	// ��ʽ���� ��ί���
	void SpeechContest();

	//������Ǽ�����¼���ļ���
	void SaveRecord();

	// �����ļ��б���ļ�¼
	void LoadRecord();

	// ����
	~SpeechManager();

public:
	// ��һ�ִ洢ѡ�ֵ����� 12��   �ܹ�12��   ��ѡ�ֱ�ż���
	vector<int> v1;

	// ��һ�ֳɹ����� �洢ѡ�ֵ����� �ܹ�6��
	vector<int> v2;

	// �ڶ��ֳɹ����� �洢ѡ�ֵ����� �ܹ�3��  Ҳ�൱����ʤ��������
	vector<int> vVictory;

	// ��map ��-���  ֵ-����ѡ�� ���洢ѡ��
	map<int, Speaker> mSpeaker;

	// ������������ý��߼�¼������    ��--����   ֵ--������Ϣ
	map<int, Speaker> mRecord;

	// ��������
	int ContentIndex;

};
