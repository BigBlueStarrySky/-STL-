/*## 创建管理类
** 功能描述：**
-提供菜单界面与用户交互
- 对演讲比赛流程进行控制
- 与文件的读写交互*/
#include "SpeechManager.h"

void myPrint(int val)
{
	cout << val << "  ";
}
//构造函数
SpeechManager::SpeechManager()
{
	// 在创建对象的时候需要进行初始化
	InitSpeech();
	// 创建了12名选手 并放入对应容器
	CreatSpeaker();
}

// 显示菜单
void SpeechManager::ShowMenu()
{
	cout << "********************************************" << endl;
	cout <<  "*************  欢迎参加演讲比赛 ************" << endl;
	cout <<  "*************   1.开始演讲比赛  *************" << endl;
	cout <<  "*************   2.查看往届记录  *************" << endl;
	cout <<  "*************   3.清空比赛记录  *************" << endl;
	cout <<  "*************   0.退出比赛程序  *************" << endl;
	cout <<  "********************************************" << endl;
}

// 退出程序
void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

// 初始化属性:选手属性 比赛轮数等
void SpeechManager::InitSpeech()
{
	// 将容器中元素都清除掉
	v1.clear();
	v2.clear();
	vVictory.clear();
	mSpeaker.clear();

	//初始化比赛轮数
	ContentIndex = 1;
}

// 创建选手
void SpeechManager::CreatSpeaker()
{
	// 首先写出12名选手种子
	string nameSeed = "ABCDEFGHIJKL";
	// 依次创建出12名选手
	for (int i = 0; i < nameSeed.size();i++) {
		string name = "选手";
		name += nameSeed[i];
		// 通过选手类创建选手
		Speaker speaker;
		speaker.name = name;  //初始化选手姓名
		// 初始化选手两轮成绩
		for (int j = 0; j < 2; j++) {
			speaker.score[j] = 0;
		}
		// 将12名选手编号放进第一轮容器里
		v1.push_back(i + 1001);
		// 将编号和对应具体选手放进容器里
		mSpeaker.insert(make_pair(i + 1001, speaker));
	}
}

// 开始比赛  
void SpeechManager::StartContent()
{
	// 选手创建完毕后第一轮抽签  将v1容器中的12位选手编号打乱顺序进行抽签  打乱之后前六个人为第一组 后六个人为第二组
	SpeechDraw();
	// 第一轮12位选手已经抽签完毕 开始第一轮比赛 并且把晋级的6人放入容器2
	SpeechContest();
	ContentIndex++;   //表示进入第二轮比赛
	// 开始第二轮抽签  
	SpeechDraw();
	// 第二轮6位选手已经抽签完毕 开始第一轮比赛 并且把晋级的6人放入容器2
	SpeechContest();
	ContentIndex--;   //复位 下次第一次还是进入第一轮比赛
	system("cls");
}

// 选手抽签
void SpeechManager::SpeechDraw()
{
	// 抽签要分为两轮  不同的轮次不同的处理 ContentIndex
	cout << "---------第" << ContentIndex << "轮选手正在抽签---------" << endl;
	system("pause");
	// 第一轮比赛抽签
	if (ContentIndex == 1)
	{
		random_shuffle(v1.begin(), v1.end());  // 对装满了12位选手的容器1打乱顺序  前六个人为第一组 后六个人为第二组
		vector<int>::iterator pos = v1.begin();
		for (int i = 0; i < 2; i++) {
			int n = 0;
			cout << "第" << i+1 << "组选手为:" << endl;
			for (; n < 6; pos++, n++) {
				cout << "编号:" << *pos << "  姓名:" << mSpeaker[*pos].name << endl;
			}
			cout << endl;
		}
	}
	// 第二轮比赛抽签
	else {
		random_shuffle(v2.begin(), v2.end());  // 对装满了已经晋级到第二轮比赛的6位选手的容器2打乱顺序
		cout << "第二轮参赛选手顺序为:" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << "编号:" << *it << "  姓名:" << mSpeaker[*it].name << endl;
		}
		cout << endl;
	}
	system("pause");
	system("cls");
	ShowMenu();
}

// 正式比赛 评委打分
void SpeechManager::SpeechContest()
{
	cout << "------------- 第" << ContentIndex << "轮正式比赛开始：------------- " << endl;
	system("pause");
	vector<int> vTemp;  // 创建一个新容器 根据比赛场次来指向v1或v2  减少重复代码
	if (ContentIndex == 1) {
		vTemp = v1;
	}
	else {
		vTemp = v2;
	}
	// 遍历新容器里的选手  对其进行打分
	int num = 1; //表示正在遍历第多少位选手
	int i = 1; // 表示第一轮第几组选手
	// 创建一个临时容器来将选手的分数和编号联系起来  分数由高到底排序
	multimap<double, int, greater<double>> scoreGroup;
	//for_each(vTemp.begin(), vTemp.end(), myPrint);
	for (vector<int>::iterator it = vTemp.begin(); it != vTemp.end() && num <= 12; it++, num++) {
		// 10位评委打出分数 (双精度型)  创建一个容器用来存储分数 deque双端数组更好用
		deque<double> d;
		for (int j = 0; j < 10; j++) {
			double score = (rand() % 4001 + 6000) / 100.0f;    //随机打分 并转化成浮点数 这样一样的分数概率更小
			d.push_back(score);
		}
		// 对分数进行一个从高到底的排序 从而方便去除最高分和最低分
		sort(d.begin(), d.end(), greater<double>());
		// 去除最高分和最低分
		d.pop_back();   d.pop_front();
		// 计算出平均分作为此选手的此轮比赛的最终得分 accumulate(iterator beg, iterator end, value);   value为初始偏移量
		double avg = accumulate(d.begin(), d.end(), 0.0f) / double(d.size());
		// 将得分赋值给选手的分数
		//cout << "编号:" << *it << "姓名:" << mSpeaker[*it].name << "分数:" << avg << endl;
		mSpeaker[*it].score[ContentIndex - 1] = avg;
		// 现在按照分数将分数和对应编号放入multimap(以防分数一样) 这样可以自动排序
		scoreGroup.insert(make_pair(avg, *it));
		// 每一组选手遍历一次成绩
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "组比赛结果如下:" << endl;
			// 遍历scoreGroup 打印出分数 并取出前三名晋级
			int ranking = 1; //记录每组选手的排名  遍历的顺序是按照分数从高到低
			for (multimap<double, int>::iterator mit = scoreGroup.begin(); mit != scoreGroup.end(); mit++, ranking++) {
				cout << "编号:" << mit->second << " 姓名:" << mSpeaker[mit->second].name << " 分数:" << mit->first << endl;
				if (ranking <= 3) {
					ContentIndex == 1 ? (v2.push_back(mit->second)) : (vVictory.push_back(mit->second)); // 将每组晋级的人数放入到晋级容器中
				}
			}
			cout << endl;
			// 遍历结束之后 把分数-编号容器清空 进而存储下一组的选手
			scoreGroup.clear();
		}
	}
	
	if (ContentIndex == 1) {
		cout << "第一轮成功晋级的选手为:" << endl;
		for (vector<int>::iterator it1 = v2.begin(); it1 != v2.end(); it1++) {
			cout << "编号:" <<*it1 << " 姓名:" << mSpeaker[*it1].name << " 分数:" << mSpeaker[*it1].score[ContentIndex - 1] << endl;
		}
		cout << endl;
	}
	else {
		cout << "最终得奖选手为:" << endl;
		string nameSeed1[] = { "冠军:", "亚军:", "季军:" };
		int i = 0;
		for (vector<int>::iterator it2 = vVictory.begin(); it2 != vVictory.end(); it2++, i++) {
			cout << nameSeed1[i] << mSpeaker[*it2].name << " 编号:" << *it2 << endl;
		}
		cout << endl;
		SaveRecord();
		cout << "本届比赛完毕!" << endl;
	}
	system("pause");
	system("cls");
	ShowMenu();
}

//保存冠亚季军记录到文件中
void SpeechManager::SaveRecord()
{
	// 创建文件写对象
	ofstream ofs;
	// 指定文件打开方式 以文本写(ios::out)和追加(ios::app)的方式
	ofs.open(FileName, ios::out | ios::app);
	// 将得奖者(编号在victory容器中)每个人的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		// 用左移运算符写入
		ofs << *it << "," << mSpeaker[*it].score[1] << ",";  // 每一届获奖者都只占一行
	}
	ofs << endl;  // 写入一个换行符 方便下次追加
	ofs.close();
	cout << "记录保存成功" << endl;
}

//析构
SpeechManager::~SpeechManager()
{

}
