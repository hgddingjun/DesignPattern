#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//�зֳ�log: 
///		������������ʱ�䣬��������
///		map<int, vector<string>>: int ������ţ�Ȼ�����ǽ���Щ��������������ʱ�䣬����������
/// 

map<int, vector<string>> Cache;

class BugManager {
public:
	virtual void getBugs() = 0;
};

class RealBugModel {
public:
	void getBugs() {
		//���ļ���ȡ�����ҽ����Ϸ�װ��Cache��
		ifstream in("�����б�.txt");
		if (!in) {
			cerr << "ERROR:�ļ��򿪴���..." << endl;
		}
		string line;
		int i = 0;
		while (getline(in, line)) {
			Cache[i] = getCache(line);
			i++;
		}
		in.close();
	}
private:
	vector<string> getCache(string words)
	{
		vector<string> results;
		istringstream ss(words);
		while (!ss.eof()) {
			string word;
			getline(ss, word, '|');
			results.push_back(word);
		}
		return results;
	}
};

class ProxyBugModel {
public:
	ProxyBugModel():m_reload(false){}
	void getBugs() {
		if (m_reload) {
			cout << "���Ǵӻ��������ȡ��" << endl;
			showBugs();
		}
		else {
			cout << "������ʵ������" << endl;
			(new RealBugModel())->getBugs();
			showBugs();
			m_reload = true;
		}
	}
private:
	void showBugs() {
		for (int i = 0;i < Cache.size();i++) {
			cout << "��" << i << "����: ";
			for (vector<string>::iterator iter = Cache[i].begin(); iter != Cache[i].end(); iter++) {
				cout << (*iter) << " ";
			}
			cout << endl;
		}
	}
private:
	bool m_reload;//true:�ӻ��������ݣ���������realbug����
};


int main() {
	ProxyBugModel* p = new ProxyBugModel();
	for (int i = 0;i < 5;i++) {
		cout << "��" << i << "������: ";
		p->getBugs();
		cout << endl;
	}
	delete p;
	return 0;
}