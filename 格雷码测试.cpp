#include <iostream>
#include <vector>
#include <string>
#include <time.h>
 
void GrayCodeOne(int num);
void GrayCodeTwo(int num);
 
using namespace std;
 
int main()
{
	int count;
	cout << "Input Code Number:";  
	cin >> count;//输入一个整形数
 
	cout << "Produce Gray Code using method 1" << endl;
	clock_t beginOne = clock();
	GrayCodeOne(count);
	clock_t endOne = clock();
	cout << "Gray Code First Method using time: " << (endOne - beginOne) << endl;
 
	cout << "Produce Gray Code using method 2" << endl;
	clock_t beginTwo = clock();
	GrayCodeTwo(count);
	clock_t endTwo = clock();
	cout << "Gray Code Second Method using time: " << (endTwo - beginTwo) << endl;
 
	return 0;
}
 
// Method to produce gray code using method inserting 0 in front of old gray code by positive  
//方法1中的已有的格雷码序列，正向前面一位加0，逆向前面一位加1
// and inserting 1 in front of old gray code by nagative.
void GrayCodeOne(int num)
{
	if (num < 1)
	{
		cout << "Error input Integer" << endl;
		return;
	}
 
	vector<string> codeVec;  //定义一个字符串类型的向量 用来存放编码序列
 
	int cIdx = 1;
	for (; cIdx <= num; cIdx++)
	{
                //如果num=1,则for循环只有一次，codeVec大小就为2，里面放的是0,1
		//开始向量为空，for循环的第一次，该向量大小一定小于2，直接存放0,1，
                //存放一次结束后向量大小为2，则进入下面的else里
                if (codeVec.size() < 2)  
		{
			codeVec.push_back("0");
			codeVec.push_back("1");
		}
		else
		{
                        //如果codeVec大小大于等于2个，则开始在，0和1上进行下面操作
			vector<string> tranVec;  
			tranVec.resize(2 * codeVec.size());  //定义一个中转向量，确定tranVec的大小为原有元素向量的2倍
			int tranIdx = 0;
                        //迭代器对向量进行遍历
			vector<string>::iterator codeIter = codeVec.begin();
			for (; codeIter != codeVec.end(); codeIter++)
			{
                                //在正序输出的每个元素的前面加0
				string str = "0";
				str.append(*codeIter);
				tranVec[tranIdx++] = str;//将加0后的元素重新存到转移向量
			}
 
			vector<string>::reverse_iterator rCodeIter = codeVec.rbegin();  //逆序迭代器，rbegin指向容器c的最后一个元素
			for (; rCodeIter != codeVec.rend(); rCodeIter++)
			{
                                //在逆序输出的每个元素的前面加1
				string str = "1";
				str.append(*rCodeIter);
				tranVec[tranIdx++] = str; 
			}
 
			codeVec.assign(tranVec.begin(), tranVec.end());
                        //将区间tranVec[first,last)的元素全部赋值到当前的codeVec容器中
                        //就是当前依序所编码的格雷码
		}
	}
 
	//vector<string>::iterator vecIter = codeVec.begin();
	//for (; vecIter != codeVec.end(); vecIter++)
	//{
	//	cout << *vecIter << endl;
	//}
 
	return;
}
 
// Method to produce gray code using method inserting 0/1 in the back of first gray code
// then inserting 1/0 in the back of next gray code.
void GrayCodeTwo(int num)
{
	if (num < 1)
	{
		cout << "Input error Integer" << endl;
		return;
	}
 
	vector<string> codeVec;
 
	int cIdx = 1;
	for (; cIdx <= num; cIdx++)
	{
		if (codeVec.size() < 2)
		{
			codeVec.push_back("0");
			codeVec.push_back("1");
		}
		else
		{
			vector<string> tranVec;
			int tranIdx = 0;
			int cIdx = codeVec.size();
 
			tranVec.resize(2 * cIdx);
			for (int vIdx = 0; vIdx < cIdx; vIdx++)
			{
				string str = codeVec[vIdx];
				if (0 == (vIdx % 2))
				{
					string str0 = str;
					str0.append("0");
					tranVec[tranIdx++] = str0;
 
					string str1 = str;
					str1.append("1");
					tranVec[tranIdx++] = str1;
				}
				else
				{
					string str0 = str;
					str0.append("1");
					tranVec[tranIdx++] = str0;
 
					string str1 = str;
					str1.append("0");
					tranVec[tranIdx++] = str1;
				}
			}
 
			codeVec.assign(tranVec.begin(), tranVec.end());
		}
	}
 
	//vector<string>::iterator vecIter = codeVec.begin();
	//for (; vecIter != codeVec.end(); vecIter++)
	//{
	//	cout << *vecIter << endl;
	//}
 
	return;
}