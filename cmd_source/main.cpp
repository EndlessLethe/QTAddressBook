#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <set>
#include<windows.h>
using namespace std;

const int stoptimelong = 500;  //Sleep�����Ժ���Ϊ��λ��Sleep(500);��ʾͣ����



struct inf{
	string name, pho, cls, email;
	inf() = default;
};

class sys {
	public:
		sys() {//���캯�������ļ��ж�����ʷ����
			string a, b, c, d;
			ifstream input("test.txt");
			if (!input) {
				cout << "��ȡ��ʷ��¼ʧ��" << endl; 
			}
			else {
				while (input >> a >> b >> c >> d) {//��ʱ�����ܺ��в��������������������Ҫ���
					save(a, b, c, d);
				}
			}
			input.close();
		}
		~sys() {//������ʷ����
			ofstream output("test.txt");
			if (!output) {
				cout << "��������г��ִ���" << endl; 
			}
			else {
				for (auto iter=saved.begin(); iter!=saved.end(); iter++) {//���������� 
				 	output << iter->second.name << " " << iter->second.pho <<
					  " " << iter->second.cls << " " << iter->second.email << endl;
				}
			}
			output.close();
			
		}
		void show() {//����show����ͨ�����������ͬ�����õ���ͬ�����������ͳ���
			cout << "show all the records" << endl;
			find();
			cout << endl;
		}
		void show_off () {
			cout << "show office records" << endl;
			find(1);
			cout << endl;
		}
		void show_per() {
			cout << "show person records" << endl;
			find(2);
			cout << endl;
		}
		void show_com() {
			cout << "show commercial records" << endl;
			 find(3);
			 cout << endl;
		}
		void add(string a, string b, string c, string d) {//��Ϊ����ͼ�ν��棬һ���ᴫ��4���������޲�����NULL��䣩
			if (saved.count(a+b)) {//a+b����֤�������ֻ����ظ�����Ȼ����ΪӢ�ģ��ֻ�Ϊ���֣�
				cout << "¼�������ظ�" << endl;
				return; 
			}
			else if (saved.size() >= 15) {
				cout << "����ռ�����" << endl;
				return;
			}
			else {
				save(a, b, c, d);
			}
		}
		void det(string a) {
			for (auto iter = saved.begin(); iter != saved.end(); iter++) {
				if (iter->second.name == a) saved.erase(a+ iter->second.pho);
			}
		}
		void change(string a, string b, string c, string d) {
			if (!saved.count(a+b)) {
				cout << "No file exists" << endl;
			}
			else {
				save(a, b, c, d);
			}
		}
		void call() {
			int times = 0;
			cout << "All name" << endl;
			set <string> is_print;//��map���ƣ��ڲ�����ͬ���ú��ƽ����ά��
			for (auto iter = saved.begin(); iter != saved.end(); iter++) {
				if (!is_print.count(iter->second.name)) {//���أ�����ͬһ�����ж���ֻ���
					cout << ++times << ": " << iter->second.name << endl;
					is_print.insert(iter->second.name);
				}
			}
			cout << "Who's number you want to know?" << endl;
			string who;
			cin >> who;
			times = 0;
			for (auto iter = saved.begin(); iter != saved.end(); iter++) {
				if (iter->second.name == who) {
					cout << ++times << ": ";
					for (auto ch : iter->second.pho) {//c++11���﷨����ӡpho��ÿһλ 
						cout << ch;
						Sleep(stoptimelong);
					}
					cout << endl;
				}
			}
			cout << endl;
		}

	private:
		map <string, inf> saved;//map�ڲ�������С��ƽ����(�����)��ά���ģ������Զ������ֵ�������ֱ�������žͺ�
		
		void find() {//��findһ������������
			int times = 0;
			for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
			 	cout << ++times << ": " << iter->second.name << " " << iter->second.pho <<
				  " " << iter->second.cls << " " << iter->second.email << endl;
			}
		}
		void find(int a) {
			int times = 0;
			stringstream ss;
			string s;
			ss << a;
			ss >> s;
			for (auto iter=saved.begin(); iter!=saved.end(); iter++) {
			 	if (iter->second.cls == s) cout << ++times << ": " << iter->second.name << " " << iter->second.pho <<
				  " " << iter->second.cls << " " << iter->second.email << endl;
			}
		}
		void find(string a) {
			int times = 0;
			for (auto iter = saved.begin(); iter != saved.end(); iter++) {
				if (iter->second.name == a) cout << ++times << ": " << iter->second.name << " " << iter->second.pho <<
					" " << iter->second.cls << " " << iter->second.email << endl;
			}
		}
		void save(string a, string b, string c, string d) {
				saved[a + b].name = a;
				saved[a + b].pho = b;
				saved[a + b].cls = c;
				saved[a + b].email = d;
		}
};

int main()
{
	sys a;
	a.show();
	a.add("z", "32462", "3", "2");
	a.add("zz", "424", "1", "2");
	a.add("zz", "32452456", "2", "2");
	a.add("z", "59654", "3", "2");
	a.show();
//	cout << "com::" << endl;
	a.show_com();
	a.call();
	cout << "Please input 4 strings as name, pho, class, email" << endl;
	cout << "class office input 1, class person input 2, \
class commercial input 3" << endl;
	string n, p, c, e;
	cin >> n >> p >> c >> e;
	a.add(n, p, c, e);
	a.show();
	system("pause");
	return 0;
}
