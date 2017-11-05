#include<iostream>
#include<thread>
#include <fstream>  
#include <ctime>  
#include <windows.h>  
#include <tchar.h>  
#include <sys/timeb.h>  
#include <time.h>  
#include <cmath>  
#include <stdio.h>  
#include "func.h"
using namespace std;

string s="";
void PrintArray(int *array,int size,int*index)  //字典序法
{
	for(int i=0;i<size;i++)
	{
		cout<<array[index[i]-1];
	}
	cout<<endl;
}
bool find(int*index,int size)  //字典序
{
	bool match=false;
	int find=-1;
	for(int i=size-1;i>=1;i--)//寻找交换点
	{
		if(index[i]>index[i-1])
		{
			match=true;
			find=i-1;
			break;
		}

	}
	if(!match)
	{
		return false;
	}
	for(int i=size-1;i>find;i--)
	{
		if(index[i]>index[find])//交换
		{
			int temp=index[i];
			index[i]=index[find];
			index[find]=temp;
			break;
		}
	}
	int index2[1000];
	for(int i=0;i<1000;i++)//初始化为0
		index2[i]=0;

	for(int i=find+1;i<=size-1;i++)
	{
		index2[i]=index[i];
	}
	for(int i=find+1;i<=size-1;i++)
	{
		index[i]=index2[find+size-i];
	}
	return  true;

}
void dic(int* array,int size)   //字典序
{
	int index[1000];
	for(int i=0;i<size;i++)//得到一个字典序最小的排列
	{
		index[i]=i+1;
	}
	PrintArray(array,size,index);//输出第一个排列
	
	while(find(index,size))
	{
		PrintArray(array,size,index);
	}
}

//递增序法
bool End(int *index,int size)//判断是否终结，递增进位制数最大,是否结束
{
	for(int i=size-2;i>=0;i--)
	{
		if(index[i]!=i+1)
		{
			return false;
		}
	}
	return true;

}
void plusIndex(int *index,int size)  //递增进位制数+1
{
	for(int i=0;i<=size-2;i++)
	{
		if(index[i]+1>=i+2)
		{
			index[i]=0;

		}else
		{
			index[i]=index[i]+1;
			break;
		}
	}

}
void PrintArray2(int*array,int*index,int size) //由递增进位制数打印对应序列
{
	int Kong[1000];
	for(int i=0;i<1000;i++)
	{
		Kong[i]=-1;
	}
	for(int i=size-2;i>=0;i--)
	{
		int num=0;
		for(int j=0;j<size;j++)
		{
			if(num==index[i])
			{
				while(Kong[j]!=-1)
				{
					j++;
				}
				Kong[j]=array[i+1];
				break; //找到空位之后，跳出循环
			}
			if(Kong[j]==-1)
			{
				num++;
			}
			
		}
	}
	for(int i=0;i<size;i++)
	{
		if(Kong[i]==-1)
		{
			Kong[i]=array[0];
			break;
		}
	}
	for(int i=size-1;i>=0;i--)
	{
		cout<<Kong[i];
	}
	cout<<endl;
}

void incre(int*array,int size)//递增进位制数
{
	int index[1000];
	for(int i=size-2;i>=0;i--)
	{
		index[i]=0;
	}
	int num=0;
	
	PrintArray2(array,index,size);
	while(!End(index,size))
	{
		plusIndex(index,size); //进位制数+1
		PrintArray2(array,index,size);

	}
}



//多线程法 采用n各线程的递增进位制法
void PrintArray3(int*array,int*index,int size) //由递增进位制数打印对应序列
{
	int Kong[1000];
	for(int i=0;i<1000;i++)
	{
		Kong[i]=-1;
	}
	for(int i=size-2;i>=0;i--)
	{
		int num=0;
		for(int j=0;j<size;j++)
		{
			if(num==index[i])
			{
				while(Kong[j]!=-1)
				{
					j++;
				}
				Kong[j]=array[i+1];
				break; //找到空位之后，跳出循环
			}
			if(Kong[j]==-1)
			{
				num++;
			}
			
		}
	}
	for(int i=0;i<size;i++)
	{
		if(Kong[i]==-1)
		{
			Kong[i]=array[0];
			break;
		}
	}
	for(int i=size-1;i>=0;i--)
	{
		char a[8];
		_itoa_s(Kong[i],a,10);
		s+=a[0];
		if(a[1]!='\0')
		{
			s+=a[1];
		}
	}
	s+='\n';
}
bool End_Thread(int *index,int size,int *end)//判断是否终结，递增进位制数最大,是否结束
{
	for(int i=size-2;i>=0;i--)
	{
		if(index[i]!=end[i])
		{
			return false;
		}
	}
	return true;

}
void incre_Thread(int*array,int size,int *BeginIndex,int*EndIndex)//递增进位制数
{
	do{

		PrintArray3(array,BeginIndex,size);
		plusIndex(BeginIndex,size); //进位制数+1
		

	}while(!End_Thread(BeginIndex,size,EndIndex));
}

void thread_incre(int*array,int size)
{
	int index=1000;
	int n=2; //这里是线程的数目 最大为 size-1
	int thread_num=n+1;  
	int End[10][100];
	for(int i=size-2;i>=0;i--) //这是起始、终止的index
	{
		End[0][i]=0;
		End[thread_num-1][i]=i+1;
	}

	int begin=int((size-2)/(thread_num-2));
	for(int i=1;i<thread_num-1;i++)
	{
		End[i][size-2]=begin;
		begin=begin+int((size-2)/(thread_num-2));

	}
	for(int i=1;i<thread_num-1;i++)
	{
		for(int j=size-3;j>=0;j--)
		{
			End[i][j]=0;
		}
	}
	for(int i=0;i<thread_num-1;i++) //开启多线程
	{
		thread t1(incre_Thread,array,size,End[i],End[i+1]);
		t1.join();
	}
	PrintArray3(array,End[thread_num-1],size);
	cout<<s.c_str();
	s="";

}

int main()
{
	//序列要求是正数
	int A[100];
	int n;
	int end=1;
	while(end)
	{
		cout<<"请输入要排列的整数n："<<endl;
		cin>>n;
		N=n;
		for (int i = 1 ; i <= N ; i ++)
		{ 
			num[i] = N+1-i;
			mid_num[i] = 0;
			mid_next[i] = 0;
		}
		if(n>=100)
		{

			cout<<"输入数据过大"<<endl;
			system("pause");
			return 0;
		}
		for(int i=1;i<=n;i++)
		{
			A[i-1]=i;

		}
		cout<<"请输入方法 1：字典序法  2：递增序法  3： 递减序法  4：交换法   5：多线程法"<<endl;
		int choice;
		cin>>choice;
		 DWORD start, end;  
		start = GetTickCount(); 
		switch(choice)
		{
			case 1:		
				dic(A,n);
				break;
			case 2:
				incre(A,n);
				break;
			case 3:
				jian();
				break;
			case 4:
				change();
				break;
			case 5:
				thread_incre(A,n);
				break;
			default:
				cout<<"没有这种方法！";
		}
		 end = GetTickCount();
		cout<<"运行时间："<<end-start<<" ms"<<endl;
		cout<<"输入1继续，输入0结束"<<endl;
		cin>>end;
	}
	system("pause");
	return 0;

}
