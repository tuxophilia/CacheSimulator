#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
	int a=250;
	srand(a);
	int r=rand();
	
	for(int i=0;i<500;i++)
	{
		r=rand();
		if(r%99999999>9999999)
		{
		cout<<r%99999999<<" r"<<endl;
		}
		else
		i--;
	}
	return 0;
}
