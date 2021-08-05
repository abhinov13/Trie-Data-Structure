/*
The Given Code is used to generate a trie out of all possible substrings of a single string.
*/
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
typedef map<string,int> edge;
typedef vector<edge> tree;

void printTree(tree &t,int node)
{
	for(auto i : t[node])
	{
		if(i.second != 0)
		{
			cout << i.first << endl;
			printTree(t,i.second);
		}
	}
}

bool find(edge &e,char s,string &temp)
{
	for(auto i : e)
	{
		if(i.first[0] == s && i.second != 0)
		{
			temp = i.first;
			return true;
		}
	}
	return false;
}
void addToTree(string &s,tree &t)
{
	int prev = 0;
	string temp = "";
	for(int i = 0;i < s.size();i++)
	{
		
		if(find(t[prev],s[i],temp))//present in a string of size greater than 1
		{	int len = 0,inds = i,inde = 0;
			while(inde < temp.size() && inds < s.size() && s[inds] == temp[inde])
			{
				len++;
				inde++;
				inds++;
			}
			string common = temp.substr(0,len);
			
			if(len == temp.size())
			{
				prev = t[prev][temp];
			}
			else
			{
				t.resize(t.size() + 1);
				int save = t[prev][temp];

				t[prev].erase(temp);
				t[prev][common] = t.size() - 1;
				t[t.size() - 1][temp.substr(len,temp.size() - len)] = save;

				prev = t.size() - 1;
			}
			i += (len - 1);			
		}
		else//not present at all
		{
			t.resize(t.size() + 1);
			t[prev][s.substr(i,s.size() - i)] = t.size() - 1;
			prev = t.size() - 1;
			i = s.size() - 1;
		}
		
	}
}
tree buildTree(string s)
{
	tree t(1);
	string cur;
	for(int i = 0;i < s.size();i++)
	{
		cur = s.substr(i,s.size() - i);
		addToTree(cur,t);
	}
	return t;
}


int main()
{
	string s;
	cin >> s;
	tree t;
	t = buildTree(s);
	printTree(t,0);
	return 0;
}
