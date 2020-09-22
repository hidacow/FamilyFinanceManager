#include<iostream>
#include <math.h>
using namespace std;
int main()
{
	float n,x,y,a,b,c;
	cin>>n>>x>>y;
	if(y>n*x){exit(0);
	}
	c=y/x;
	b=ceil(c);
	a=n-b;
	cout<<a;
	return 0;
	
	
 } 
