//比赛规则
//* 学校举行一场演讲比赛，共有** 12个人 * *参加。 * *比赛共两轮 * *，第一轮为淘汰赛，第二轮为决赛。
//* 比赛方式： * *分组比赛，每组6个人 * *；选手每次要随机分组，进行比赛
//* 每名选手都有对应的 * *编号 * *，如 10001 ~10012
//* 第一轮分为两个小组，每组6个人。 整体按照选手编号进行 * *抽签 * *后顺序演讲。
//* 当小组演讲完后，淘汰组内排名最后的三个选手， * *前三名晋级 * *，进入下一轮的比赛。
//* 第二轮为决赛， * *前三名胜出 * *
//*每轮比赛过后需要 * *显示晋级选手的信息 * *
//程序功能
//* 开始演讲比赛：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
//* 查看往届记录：查看之前比赛前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
//* 清空比赛记录：将文件中数据清空
//* 退出比赛程序：可以退出当前程序
#include "SpeechManager.h"
#include "Speaker.h"
#include <ctime>
// 测试 对象是否初始化成功
void test(const SpeechManager &sm)
{
	cout << "测试" << endl;
	for (map<int, Speaker>::const_iterator it = sm.mSpeaker.begin(); it != sm.mSpeaker.end(); it++) {
		cout << "编号:" << it->first << "\t" << "姓名:" << it->second.name << "\t" << "第一轮比赛成绩:" << it->second.score[0] << "\t"
			<< "第二轮比赛成绩:" << it->second.score[1] << endl;
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm; // 创建演讲管理者对象
	//test(sm);
	int select;  // 存储用户对功能的选项
	while (true)
	{
		// 展示菜单
		sm.ShowMenu();
		// 提示用户输入功能选项  并且对输入选项作出预防bug处理
		while (true)
		{
			cout << "请输入你的选项:" ;
			cin >> select;
			if (cin.fail())  // 说明输入的不是数字 对此做出预防处理
			{
				cout << "输入错误, 请输入数字" << endl;
				cin.clear();     //清除cin.fail()这个错误状态
				cin.sync();    //清除缓冲区
				cin.ignore(); //忽略掉缓冲区的内容，直到遇到EOF为止
			}
			else {// 输入的是数字 说明输入正确 退出循环
				break;
			}
		}
		//根据用户输入的选项 做出不同的处理
		switch (select)
		{
		case 1: //开始演讲比赛
			//抽签 → 开始第一轮演讲比赛 → 显示第一轮比赛结果 → 开始第二轮演讲比赛 → 显示前三名结果 → 保存分数
			sm.StartContent();
			break;
		case 2: //查看往届记录
			break;
		case 3: //清空比赛记录
			break;
		case 0: //退出比赛程序
			sm.ExitSystem();
			break;
		default: //输入错误
			cout << "输入错误, 请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}	
	}
	return 0;
}