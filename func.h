#include <iostream>
using namespace std;
int N , num[15];	//全排列矩阵 1是个位
int mid_num[15] , mid_next[15];	//中介数、下一个中介数 

void calu_mid_num_jian()	//计算递减进位制中介数 
{
	//for (int i = n ; i >= 2 ; i--)
	//{
	//	int temp_small = 0;	//i的右边比i小的数字个数
	//	for (int j = i - 1 ; j >= 1 ; j --)
	//	{
	//		if (num[j] < num[i])
	//			temp_small ++;
	//	}
	//	mid_num[num[i]] = temp_small;	//index=2的是高位，进制是2，index=n的是低位，进制是n 
	//}
	for (int i = 2; i <= N; i++)
	{
		int indexnum = 0;
		for (int j = 1; j <= N; j++)
		{
			if (num[j] == i)
			{
				indexnum = j;
				break;
			}
		}
		int temp_small = 0;	
		for (int j = indexnum ; j >= 1 ; j --)
		{
			if (num[j] < num[indexnum])
				temp_small ++;
		}
		mid_num[i] = temp_small;	//index=2的是高位，进制是2，index=n的是低位，进制是n 
	}
	
}

void calu_mid_num_next()	//计算下一个中介数 
{
	//for (int i = 1; i <= n; i++)
	//{
	////	mid_num[i] = 0;
	//	mid_next[i] = 0;
	//}
	if (mid_num[N] + 1 < N)	//最低位不需要进位 
	{
		mid_next[N] =  mid_num[N] + 1;
		for(int i = N - 1 ; i >= 2 ; i--)
			mid_next[i] = mid_num[i];
	}
	else
	{
		mid_next[N] = 1;	//进位标记 
		for(int i = N ; i >= 2 ; i--)
		{
			if(mid_num[i] + mid_next[i] >= i)
			{
				mid_next[i] = 0;	//进位之后这一位成0了
				mid_next[i-1] = 1; 	//下一位有个进位标记 
			}
			else
			mid_next[i] =  mid_num[i] + mid_next[i];	//	没进位的话这一位就是原来数 
		}
	}

}

void calu_next_num_jian()	//由中介数计算递减进位制的下一个序列 
{
	for (int i = 1 ; i <= N ; i++)
		num[i] = 0;
	for(int i = N ; i >= 2 ; i--)
	{
		int num_zero = 0;	//空位数，从右到左开始寻找空位 
		for (int j = N ; j >= 1 ; j --)
		{
			if(num[j] == 0)
				num_zero ++;
			if(num_zero == mid_next[i] + 1)
			{
				num[j] = i;
				break;
			} 
		}
	}
	for(int i = N ; i >= 1 ; i--)	//最后再把1填进去 
	{
		if (num[i] == 0)
		{
			num[i] = 1;
			break;
		}
	}
	
	for (int i = 1; i <= N/2; i++)	//翻转一下
	{
		int temp = num[i];
		num[i] = num[N + 1 - i];
		num[N + 1 - i] = temp;
	}
}

void calu_mid_num_exchange()	//邻位对换中介数 
{
	for(int i = 2 ; i <= N ; i ++)
	{
		int index_i = 0;	//先找到i的位置 
		for(int j = 1 ; j <= N ; j ++)
		{
			if(num[j] == i)
			{
				index_i = j;
				break;
			} 
		}
		
		int num_small = 0;	//小的个数 
		if (i == 2)	//2的方向向左，所以向右搜索，index减小的方向 
		{
			for(int j = index_i ; j >= 1 ; j --)
			{
				if (num[j] < i)
					num_small ++;
			}
		}
		else if (i % 2 == 1)	//i奇数 
		{
			if(mid_num[i-1] % 2 == 1)	//i-1 奇数，向右，向左搜索，index增加 
			{
				for(int j = index_i ; j <= N ; j ++)
				{
					if (num[j] < i)
						num_small ++;
				} 
			} 
			else	//i-1 偶数，向左，向右搜索，index减小 
			{
				for(int j = index_i ; j >= 1 ; j --)
				{
					if (num[j] < i)
						num_small ++;
				}
			}
		} 
		else	//i偶数 
		{
			if((mid_num[i-1]+mid_num[i-2]) % 2 == 1)	//奇数，向右，向左搜索，index增加
			{
				for(int j = index_i ; j <= N ; j ++)
				{
					if (num[j] < i)
						num_small ++;
				} 
			} 
			else	//偶数，向左，向右搜索，index减小
			{
				for(int j = index_i ; j >= 1 ; j --)
				{
					if (num[j] < i)
						num_small ++;
				}
			}
		} 
		mid_num[i] = num_small;
	} 
} 

void calu_next_num_exchange()	//由中介数计算邻位对换的下一个序列
{
	for (int i = 1 ; i <= N ; i++)
		num[i] = 0;
	for (int i = N ; i >= 3 ; i --)
	{
		int num_zero = 0;	//空位数
		if (i % 2 == 1)	//i奇数 
		{
			if(mid_next[i-1] % 2 == 1)	//i-1 奇数，向右，index增加 
			{
				for(int j = 1 ; j <= N ; j ++)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			} 
			else	//i-1 偶数，向左，index减小 
			{
				for(int j = N ; j >= 1 ; j --)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			}
		} 
		else	//i偶数
		{
			if((mid_next[i-1]+mid_next[i-2]) % 2 == 1) //奇数，向右，index增加 
			{
				for(int j = 1 ; j <= N ; j ++)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				}
			}
			else	//偶数，向左，index减小 
			{
				for(int j = N ; j >= 1 ; j --)
				{
					if (num[j] == 0)
						num_zero ++;
					if(num_zero == mid_next[i] + 1)
					{
						num[j] = i;
						break;
					} 
				} 
			}
		}
	} 
	int num_zero = 0;	//空位数
	for(int j = N ; j >= 1 ; j --)	//把2放进去 
	{
		if (num[j] == 0)
			num_zero ++;
		if(num_zero == mid_next[2] + 1)
		{
			num[j] = 2;
			break;
		} 
	} 
	for(int i = N ; i >= 1 ; i--)	//最后再把1填进去 
	{
		if (num[i] == 0)
		{
			num[i] = 1;
			break;
		}
	}
	for (int i = 1; i <= N / 2; i++)	//翻转一下
	{
		int temp = num[i];
		num[i] = num[N + 1 - i];
		num[N + 1 - i] = temp;
	}
}

void print_array()
{
	for (int i = N ; i >= 1 ; i --)
		cout << num[i] << ' ';
	cout << endl;
}

int pailie[10] = {0,1,2,6,24,120,720,5040,40320,362880};
void jian()
{
	print_array();
	for (int i = 1 ; i < pailie[N] ; i ++)
	{
		calu_mid_num_jian();
		calu_mid_num_next();
		calu_next_num_jian();
		print_array();
	}
}

void change()
{
	print_array();
	for (int i = 1; i < pailie[N]; i++)
	{
		calu_mid_num_exchange();
		calu_mid_num_next();
		calu_next_num_exchange();
		print_array();
	}
}
/*

int main()
{
	cin >> N;
	for (int i = 1 ; i <= N ; i ++)
	{ 
		num[i] = N+1-i;
		mid_num[i] = 0;
		mid_next[i] = 0;
	}

//	jian();
	change();
	system("pause"); 
	return 0;
}
*/