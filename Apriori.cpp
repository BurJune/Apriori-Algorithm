#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
#define maxn 2005
//获得输入的个数和支持度
float support=0;
float b_size=0;
//L1_num是存放L1集合的数量，L2_num是存放L2集合的数量
int L1_num = 0;
int L2_num = 0;
//set用来存放L1和L2的数据
set<set<int> >  s[4];
//vector用来存放data.txt的数据
vector<int> b[maxn];
//在数组中出现的频率就是支持度×总个数


//输入总个数和支持度
int getinformation() {
	cout << "请输入事物总个数" << endl;
	cin >> b_size;
	cout << "请输入支持度：" << endl;
	cin >> support;
	cout << "您输入的事物总个数为：" << b_size << endl << "您输入的支持度为" << support << endl;
	cout << "please key in your datas" << endl;
	return 0;
}

//双指针法，给一个集合，获得这个集合在总数据集中的频度
    int return_freqent_number(set<int> s){
	int freqent = 0, index;
	set<int>::iterator it;
	vector<int> v;
	for (it = s.begin(); it != s.end(); it++) {
		v.push_back(*it);
	}
	int v_size = v.size();
	for (int i = 0; i < 2000; i++) {
		index = 0;
		for (int j = 0; j < v_size; j++) {
			while (index < b[i].size() && v[j] != b[i][index]) index++;
		}
		if (index < b[i].size()) freqent++;
	}

	return freqent;
}






int main() {
	getinformation();
	float freqent_num = support * b_size;
	string str;
	
	int data;
	
	int num, i=0;
	
//标准输入，把所有的数据存放在二维数组vector里
	while (getline(cin, str)) {
		//cout << str << endl;

		for (auto j = 0; j < str.size(); j++)
		{
			if (isdigit(str[j])) {
				num = str[j] - '0';

				while (isdigit(str[++j]))
				{
					num *= 10;
					num += (str[j] - '0');

				}
				b[i].push_back(num);
			}


		}
		i++;

	}





	//遍历b找出符合频繁项集的，需要计数。
	//用数组，来存放频繁项集的个数,由于没有超过1000序号的，设置为1000
	int freqent_1[2005] = {};
	//两次循环也就是遍历，看每个有啥。
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < b[i].size(); j++)
			freqent_1[b[i][j]]++;
	}
	//测试代码看看frequent_1里都是傻
	//for (int i = 1; i != 100; i++) {
	//	cout << freqent_1[i] << endl;
	//}
	//目前，b[n]是一条数据
	//先找出L1中的频繁项集，即为一个set,而且最后的结果是输出集合的集合，使用set的嵌套
	//s[1]:{  {1},2....}
	//s[2]:{  1,2  ....}
	
	set<set<int> >::iterator iter_outside=s[1].begin();

	//看l1内有多少频繁项，存到集合里
	for (int i = 0; i < maxn; i++) {
		if (freqent_1[i] >= freqent_num)
		{
			//cout << "频繁项是" << i << " " << "的频度是" << freqent_1[i] << endl; 		
			set<int> s_inside;
			s_inside.insert(i);
			s[1].insert(s_inside);
		}
	}		
	cout << "Min_Support:" << support << endl;;
	cout << "频繁项集L1为：{ ";
	for (auto it = s[1].cbegin(); it != s[1].cend(); it++)
	{

		for (auto it2 = (*it).cbegin(); it2 != (*it).cend(); it2++)
			cout << "{" << (*it2) << "}" ;
		L1_num++;
	}cout << "}" << endl;
	
	//s[1]里装了1-24的频繁项集合，目前要做并集，让s[1]内的集合并起来


	//需要看看setset内部情况
//	for (; iter_outside != s[1].end(); iter_outside++)
//	{
//		set<int>::iterator iter_inside = (*iter_outside).begin();//i不是集合当然不能插入
//		for (; iter_inside != (*iter_outside).end(); iter_inside++)
//		{
//			cout << "set中为" << (*iter_inside) << endl;
//		}
//cout << endl;
//	}
	//这段代码只能获得连续的L1(1-24)的，有很大的缺陷
	//for (int i = 1; i <= L1_num; i++) {
	//

	//	for (int j = i + 1; j <= L1_num; j++) {
	//		
	//	set<int> L2;
	//     L2.insert(i);
	//		L2.insert(j);
	//		s[2].insert(L2);
	//	}
	//}
	//测试输入是否正确
	//问题在于这个函数返回的数据结构没有指针可以指向

	//给了第一个L1，返回C1
	
	//_________________________________L1-->C1_________
		int temp[100] = {};
		int k = 0;
		//考虑把S[1]的数据放到一个数组里，然后用这个数组的数字循环，但是插入的是数组内的数字
		set<set<int> >::iterator iter_outside_second = s[1].begin();
		for (; iter_outside_second != s[1].end(); iter_outside_second++)
		{
			set<int>::iterator iter_inside = (*iter_outside_second).begin();
			for (; iter_inside != (*iter_outside_second).end(); iter_inside++)
			{
				temp[++k] = (*iter_inside);
			}

		}
		//可以考虑计算一下temp中大于0的数是多少
		int cnt = 0;
		for (int i = 0; i < 100; i++) {
			if (temp[i] > 0)cnt++;
		}

		for (int i = 1; i <= cnt; i++) {


			for (int j = i + 1; j <= cnt; j++) {

				set<int> L2;
				L2.insert(temp[i]);
				L2.insert(temp[j]);
				s[2].insert(L2);
			}
		}
		//___________________________

	//此时s[2]内装的需要遍历
	//cout << "此时s[2]内装: {  " ;
	//set<set<int> >::iterator iter_outside2= s[2].begin();
	//for (; iter_outside2 != s[2].end(); iter_outside2++)
	//{
	//	cout << "{"  ;
	//	set<int>::iterator iter_inside = (*iter_outside2).begin();//i不是集合当然不能插入
	//	for (; iter_inside != (*iter_outside2).end(); iter_inside++)
	//	{
	//		cout << (*iter_inside) <<" ";
	//	}cout << "}" ;
	//}	
	//cout << " }" << endl;
	//现在要从s[2]中找出频繁项集
	set<set<int> >::iterator iter_outside3 = s[2].begin();
	cout<< "频繁项集L2为 {";
	for (; iter_outside3 != s[2].end(); iter_outside3++)
	{
		int temp_support = 0;
		temp_support = return_freqent_number((*iter_outside3));
		if (temp_support >= freqent_num) {
			set<int>::iterator iter_inside1 = (*iter_outside3).begin();//i不是集合当然不能插入
			cout << "{ ";
			for (; iter_inside1 != (*iter_outside3).end(); iter_inside1++)
			{
				cout << (*iter_inside1) << " ";
			}
			cout << "}" ;
			//cout<<" 的频度为" << temp_support << endl;
		}
	}cout << "}";


return 0;

}



