#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <set>
#include<windows.h>
using namespace std;

const int stoptimelong = 500;  //Sleep函数以毫秒为单位，Sleep(500);表示停半秒



struct inf{
	string name, pho, cls, email;
	inf() = default;
};

class sys {
	public:
		sys() {//构造函数，从文件中读入历史数据
			string a, b, c, d;
			ifstream input("test.txt");
			if (!input) {
				cout << "读取历史纪录失败" << endl; 
			}
			else {
				while (input >> a >> b >> c >> d) {//此时不可能含有不符合条件的情况，不需要检查
					save(a, b, c, d);
				}
			}
			input.close();
		}
		~sys() {//保存历史数据
			ofstream output("test.txt");
			if (!output) {
				cout << "保存过程中出现错误" << endl; 
			}
			else {
				for (auto iter=saved.begin(); iter!=saved.end(); iter++) {//迭代器遍历 
				 	output << iter->second.name << " " << iter->second.pho <<
					  " " << iter->second.cls << " " << iter->second.email << endl;
				}
			}
			output.close();
			
		}
		void show() {//几个show函数通过传入参数不同，来得到不同结果——解耦和抽象
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
		void add(string a, string b, string c, string d) {//因为最后的图形界面，一定会传入4个参数（无参数以NULL填充）
			if (saved.count(a+b)) {//a+b即保证姓名和手机不重复（显然名字为英文，手机为数字）
				cout << "录入数据重复" << endl;
				return; 
			}
			else if (saved.size() >= 15) {
				cout << "储存空间已满" << endl;
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
			set <string> is_print;//和map类似，内部数据同样用红黑平衡树维护
			for (auto iter = saved.begin(); iter != saved.end(); iter++) {
				if (!is_print.count(iter->second.name)) {//判重，可能同一人名有多个手机号
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
					for (auto ch : iter->second.pho) {//c++11新语法，打印pho的每一位 
						cout << ch;
						Sleep(stoptimelong);
					}
					cout << endl;
				}
			}
			cout << endl;
		}

	private:
		map <string, inf> saved;//map内部是以最小堆平衡树(红黑树)来维护的，可以自动按照字典序排序，直接添加序号就好
		
		void find() {//对find一共有三个重载
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
