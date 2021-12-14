/*## ����������
** ����������**
-�ṩ�˵��������û�����
- ���ݽ��������̽��п���
- ���ļ��Ķ�д����*/
#include "SpeechManager.h"

void myPrint(int val)
{
	cout << val << "  ";
}
//���캯��
SpeechManager::SpeechManager()
{
	// �ڴ��������ʱ����Ҫ���г�ʼ��
	InitSpeech();
	// ������12��ѡ�� �������Ӧ����
	CreatSpeaker();
}

// ��ʾ�˵�
void SpeechManager::ShowMenu()
{
	cout << "********************************************" << endl;
	cout <<  "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout <<  "*************   1.��ʼ�ݽ�����  *************" << endl;
	cout <<  "*************   2.�鿴�����¼  *************" << endl;
	cout <<  "*************   3.��ձ�����¼  *************" << endl;
	cout <<  "*************   0.�˳���������  *************" << endl;
	cout <<  "********************************************" << endl;
}

// �˳�����
void SpeechManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}

// ��ʼ������:ѡ������ ����������
void SpeechManager::InitSpeech()
{
	// ��������Ԫ�ض������
	v1.clear();
	v2.clear();
	vVictory.clear();
	mSpeaker.clear();

	//��ʼ����������
	ContentIndex = 1;
}

// ����ѡ��
void SpeechManager::CreatSpeaker()
{
	// ����д��12��ѡ������
	string nameSeed = "ABCDEFGHIJKL";
	// ���δ�����12��ѡ��
	for (int i = 0; i < nameSeed.size();i++) {
		string name = "ѡ��";
		name += nameSeed[i];
		// ͨ��ѡ���ഴ��ѡ��
		Speaker speaker;
		speaker.name = name;  //��ʼ��ѡ������
		// ��ʼ��ѡ�����ֳɼ�
		for (int j = 0; j < 2; j++) {
			speaker.score[j] = 0;
		}
		// ��12��ѡ�ֱ�ŷŽ���һ��������
		v1.push_back(i + 1001);
		// ����źͶ�Ӧ����ѡ�ַŽ�������
		mSpeaker.insert(make_pair(i + 1001, speaker));
	}
}

// ��ʼ����  
void SpeechManager::StartContent()
{
	// ѡ�ִ�����Ϻ��һ�ֳ�ǩ  ��v1�����е�12λѡ�ֱ�Ŵ���˳����г�ǩ  ����֮��ǰ������Ϊ��һ�� ��������Ϊ�ڶ���
	SpeechDraw();
	// ��һ��12λѡ���Ѿ���ǩ��� ��ʼ��һ�ֱ��� ���Ұѽ�����6�˷�������2
	SpeechContest();
	ContentIndex++;   //��ʾ����ڶ��ֱ���
	// ��ʼ�ڶ��ֳ�ǩ  
	SpeechDraw();
	// �ڶ���6λѡ���Ѿ���ǩ��� ��ʼ��һ�ֱ��� ���Ұѽ�����6�˷�������2
	SpeechContest();
	ContentIndex--;   //��λ �´ε�һ�λ��ǽ����һ�ֱ���
	system("cls");
}

// ѡ�ֳ�ǩ
void SpeechManager::SpeechDraw()
{
	// ��ǩҪ��Ϊ����  ��ͬ���ִβ�ͬ�Ĵ��� ContentIndex
	cout << "---------��" << ContentIndex << "��ѡ�����ڳ�ǩ---------" << endl;
	system("pause");
	// ��һ�ֱ�����ǩ
	if (ContentIndex == 1)
	{
		random_shuffle(v1.begin(), v1.end());  // ��װ����12λѡ�ֵ�����1����˳��  ǰ������Ϊ��һ�� ��������Ϊ�ڶ���
		vector<int>::iterator pos = v1.begin();
		for (int i = 0; i < 2; i++) {
			int n = 0;
			cout << "��" << i+1 << "��ѡ��Ϊ:" << endl;
			for (; n < 6; pos++, n++) {
				cout << "���:" << *pos << "  ����:" << mSpeaker[*pos].name << endl;
			}
			cout << endl;
		}
	}
	// �ڶ��ֱ�����ǩ
	else {
		random_shuffle(v2.begin(), v2.end());  // ��װ�����Ѿ��������ڶ��ֱ�����6λѡ�ֵ�����2����˳��
		cout << "�ڶ��ֲ���ѡ��˳��Ϊ:" << endl;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << "���:" << *it << "  ����:" << mSpeaker[*it].name << endl;
		}
		cout << endl;
	}
	system("pause");
	system("cls");
	ShowMenu();
}

// ��ʽ���� ��ί���
void SpeechManager::SpeechContest()
{
	cout << "------------- ��" << ContentIndex << "����ʽ������ʼ��------------- " << endl;
	system("pause");
	vector<int> vTemp;  // ����һ�������� ���ݱ���������ָ��v1��v2  �����ظ�����
	if (ContentIndex == 1) {
		vTemp = v1;
	}
	else {
		vTemp = v2;
	}
	// �������������ѡ��  ������д��
	int num = 1; //��ʾ���ڱ����ڶ���λѡ��
	int i = 1; // ��ʾ��һ�ֵڼ���ѡ��
	// ����һ����ʱ��������ѡ�ֵķ����ͱ����ϵ����  �����ɸߵ�������
	multimap<double, int, greater<double>> scoreGroup;
	//for_each(vTemp.begin(), vTemp.end(), myPrint);
	for (vector<int>::iterator it = vTemp.begin(); it != vTemp.end() && num <= 12; it++, num++) {
		// 10λ��ί������� (˫������)  ����һ�����������洢���� deque˫�����������
		deque<double> d;
		for (int j = 0; j < 10; j++) {
			double score = (rand() % 4001 + 6000) / 100.0f;    //������ ��ת���ɸ����� ����һ���ķ������ʸ�С
			d.push_back(score);
		}
		// �Է�������һ���Ӹߵ��׵����� �Ӷ�����ȥ����߷ֺ���ͷ�
		sort(d.begin(), d.end(), greater<double>());
		// ȥ����߷ֺ���ͷ�
		d.pop_back();   d.pop_front();
		// �����ƽ������Ϊ��ѡ�ֵĴ��ֱ��������յ÷� accumulate(iterator beg, iterator end, value);   valueΪ��ʼƫ����
		double avg = accumulate(d.begin(), d.end(), 0.0f) / double(d.size());
		// ���÷ָ�ֵ��ѡ�ֵķ���
		//cout << "���:" << *it << "����:" << mSpeaker[*it].name << "����:" << avg << endl;
		mSpeaker[*it].score[ContentIndex - 1] = avg;
		// ���ڰ��շ����������Ͷ�Ӧ��ŷ���multimap(�Է�����һ��) ���������Զ�����
		scoreGroup.insert(make_pair(avg, *it));
		// ÿһ��ѡ�ֱ���һ�γɼ�
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "������������:" << endl;
			// ����scoreGroup ��ӡ������ ��ȡ��ǰ��������
			int ranking = 1; //��¼ÿ��ѡ�ֵ�����  ������˳���ǰ��շ����Ӹߵ���
			for (multimap<double, int>::iterator mit = scoreGroup.begin(); mit != scoreGroup.end(); mit++, ranking++) {
				cout << "���:" << mit->second << " ����:" << mSpeaker[mit->second].name << " ����:" << mit->first << endl;
				if (ranking <= 3) {
					ContentIndex == 1 ? (v2.push_back(mit->second)) : (vVictory.push_back(mit->second)); // ��ÿ��������������뵽����������
				}
			}
			cout << endl;
			// ��������֮�� �ѷ���-���������� �����洢��һ���ѡ��
			scoreGroup.clear();
		}
	}
	
	if (ContentIndex == 1) {
		cout << "��һ�ֳɹ�������ѡ��Ϊ:" << endl;
		for (vector<int>::iterator it1 = v2.begin(); it1 != v2.end(); it1++) {
			cout << "���:" <<*it1 << " ����:" << mSpeaker[*it1].name << " ����:" << mSpeaker[*it1].score[ContentIndex - 1] << endl;
		}
		cout << endl;
	}
	else {
		cout << "���յý�ѡ��Ϊ:" << endl;
		string nameSeed1[] = { "�ھ�:", "�Ǿ�:", "����:" };
		int i = 0;
		for (vector<int>::iterator it2 = vVictory.begin(); it2 != vVictory.end(); it2++, i++) {
			cout << nameSeed1[i] << mSpeaker[*it2].name << " ���:" << *it2 << endl;
		}
		cout << endl;
		SaveRecord();
		cout << "����������!" << endl;
	}
	system("pause");
	system("cls");
	ShowMenu();
}

//������Ǽ�����¼���ļ���
void SpeechManager::SaveRecord()
{
	// �����ļ�д����
	ofstream ofs;
	// ָ���ļ��򿪷�ʽ ���ı�д(ios::out)��׷��(ios::app)�ķ�ʽ
	ofs.open(FileName, ios::out | ios::app);
	// ���ý���(�����victory������)ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		// �����������д��
		ofs << *it << "," << mSpeaker[*it].score[1] << ",";  // ÿһ����߶�ֻռһ��
	}
	ofs << endl;  // д��һ�����з� �����´�׷��
	ofs.close();
	cout << "��¼����ɹ�" << endl;
}

//����
SpeechManager::~SpeechManager()
{

}
