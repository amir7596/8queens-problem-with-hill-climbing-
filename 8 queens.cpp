#include<iostream>
#include<set>
#include<windows.h>
#include<vector>
#include<set>
#include<time.h>
using namespace std;
void gotoxy(int column, int line)            
{
  COORD coord;  coord.X = column;  coord.Y = line;  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 

int random(int a,int b)
{

	return rand()%(b-a+1)+a;
}

void firstmaker(bool map[8][8])
{
	set <int> s;
	for(int i=0;i<8;i++)
	{
		int t,k=s.size();
		while(s.size()==k)
		{
			t=random(0,7);
			s.insert(t);
		}
		map[i][t]=1;
	}
	s.clear();
}
void showmap(bool map[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<map[i][j]<<"  ";
		}
		cout<<endl;
	}
}
void onrem(bool map[8][8],int i)
{
		for(int j=0;j<8;j++)
		{
			if(map[j][i]==1)
			map[j][i]=0;
		}
}
void validate(bool map[][8],int score[][8],int k,int m)
{
	int crash=0;
	vector <pair<int,int> > coord;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(map[i][j]==1)
			coord.push_back(make_pair(i,j));
		}
	}
	for(int i=7;i>=0;i--)
	{
		int x=coord[i].first;
		int y=coord[i].second;
		for(int j=0;j<i;j++)
		{
			if(coord[j].first==x || coord[j].second==y ||coord[j].second-coord[j].first==y-x ||coord[j].second+coord[j].first==y+x)
			crash++;
		}
		coord.pop_back();
	}

	score[k][m]=crash;
	coord.clear();
}
void copy(bool first[8][8],bool second[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			second[i][j]=first[i][j];
		}
	}
}
void reset(bool map[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			map[i][j]=0;
		}
	}
}
int main()
{

	bool map[8][8]={0},smap[8][8]={0};
	int score [8][8]={0};
	firstmaker(map);
	set <int> mins;
	cout<<"initial state :\n";
	showmap(map);
    cout<<endl;
    int tek=0;
    while(1)
    {
    copy(map,smap);	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			onrem(map,j);
			map[i][j]=1;
			validate(map,score,i,j);
			copy(smap,map);
		}
	}
	int min=100;
    int x,y;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(score[i][j]<min)
			{
				min=score[i][j];
				x=i;
				y=j;
			}	
	    }
	    
	}
	onrem(map,y);
	map[x][y]=1;
	int ss=mins.size();
			mins.insert(min);
			if(mins.size()==ss)
			{
				cout<<endl<<tek<<endl;
				showmap(map);
				cout<<endl;
			//	system("PAUSE");
				mins.clear();
				reset(map);
				firstmaker(map);
				showmap(map);
				tek=0;
				cout<<endl;
			}
				
			if(min==0)
			{
				cout<<"final state with "<<tek<<" times  : \n";
				showmap(map);
				return 0;
			}
      tek++;
	}
}
