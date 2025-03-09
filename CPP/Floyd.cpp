#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int s[100][100];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			s[i][j]=0x3f3f3f3f;
			if(i==j) 
                s[i][j]=0;
		}	
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		s[x][y]=s[y][x]=z;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				s[i][j]=min(s[i][j],s[i][k]+s[k][j]);
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s[i][j]==0x3f3f3f3f)
                cout<<0<<" ";
            else
                cout<<s[i][j]<<" ";    
        }  
        cout<<"\n";
    }
	return 0;	
 } 