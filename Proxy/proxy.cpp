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

map<int, vector<string>> Logs;

vector<string> getBugs(string words)
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

bool getLogs() {
	ifstream in("�����б�.txt");
	if (!in) {
		cerr << "ERROR:�ļ��򿪴���..." << endl;
		return -1;
	}
	string line;
	int i = 0;
	while (getline(in, line)) {
		Logs[i] = getBugs(line);
		i++;
	}
	in.close();

	return 0;

}

int main() {
	getLogs(); //��ȡ�ļ�
	for (int i = 0;i < Logs.size();i++) {
		cout << "��" << i << "����: ";
		for (vector<string>::iterator iter = Logs[i].begin(); iter != Logs[i].end(); iter++) {
			cout << (*iter) << " ";
		}
		cout << endl;
	}
	return 0;
}
