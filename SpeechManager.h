/*## 创建管理类
** 功能描述：**
-提供菜单界面与用户交互
- 对演讲比赛流程进行控制
- 与文件的读写交互*/
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
	//无参构造
	SpeechManager();

	// 显示菜单
	void ShowMenu();

	// 退出程序
	void ExitSystem();

	// 初始化属性:选手属性 比赛轮数等
	void InitSpeech();

	// 创建选手
	void CreatSpeaker();

	// 开始比赛  
	void StartContent();

	// 选手抽签
	void SpeechDraw();

	// 正式比赛 评委打分
	void SpeechContest();

	//保存冠亚季军记录到文件中
	void SaveRecord();

	// 加载文件中保存的记录
	void LoadRecord();

	// 析构
	~SpeechManager();

public:
	// 第一轮存储选手的容器 12人   总共12人   存选手编号即可
	vector<int> v1;

	// 第一轮成功晋级 存储选手的容器 总共6人
	vector<int> v2;

	// 第二轮成功晋级 存储选手的容器 总共3人  也相当于是胜利者容器
	vector<int> vVictory;

	// 用map 键-编号  值-具体选手 来存储选手
	map<int, Speaker> mSpeaker;

	// 保存往届比赛得奖者记录的容器    键--届数   值--具体信息
	map<int, Speaker> mRecord;

	// 比赛轮数
	int ContentIndex;

};
