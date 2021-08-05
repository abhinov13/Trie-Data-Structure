/*
The following Code can be used to find the smallest substring in s1 that does not exist in string s2
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<queue>

#define trie vector<map<char,cus>>
using namespace std;
struct cus
{
	int val = -1;
};
trie buildTrie(string &str,vector<int> &parent)
{
	trie t(1);
	int cur = 0;
	parent.resize(1);
	parent[0] = -1;
	str += "$";
	for(int j = 0;j < str.size();j++)
	{
		string s = str.substr(j,str.size() - j);
		//cout << "Processing Full String "<< s << endl;
		cur = 0;
		for(int i = 0;i < s.size();i++)
		{
		//	cout << "adding " << s[i] << endl;
			if(t[cur][s[i]].val == -1)
			{
				t[cur][s[i]].val = t.size();
				
				parent.resize(parent.size() + 1);
				parent[parent.size() - 1] = cur;
				
				cur = t.size();
				t.resize(t.size() + 1);
		//		cout << "adding since no match" << endl;
			}
			else
			{
				cur = t[cur][s[i]].val;
		//		cout << "moving since match" << endl;
			}
		}
	}
	return t;
}

char findChar(trie &t,int par,int child)
{
	for(auto i : t[par])
	{
		if(t[par][i.first].val == child)
		{
			return i.first;
		}
	}
}
string trace(trie &t,vector<int> &parent,int start)
{
	string ans = "";
	int cur = start;
	while(parent[cur] != -1)
	{
		char c;
		c = findChar(t,parent[cur],cur);
		cur = parent[cur];
		ans = c + ans;
	}
	
	return ans;
}

string minMismatch(trie &t1,vector<int> &parent1, trie &t2,vector<int> &parent2)
{
	queue<int> proc;
	vector<int> match(t1.size(),-2);
	match[0] = 0;//root mapping
	proc.push(0);
	
	int set = -1;
	bool valid = false;
	while(proc.empty() == false && valid == false)
	{
		int cur = proc.front();
		int eq = match[cur];
		//cout << "cur " << cur << endl;
		
		for(auto i : t1[cur])
		{
			//cout << "FOUND " << i.first << endl;
			if(i.first != '$')
			{
				if(t2[eq][i.first].val == -1)//not present
				{
				//	cout << "NOT PRESENT SO SET = " << t1[cur][i.first].val << endl;
					set = t1[cur][i.first].val;
					valid = true;
				}
				else//present
				{
					//cout << "PRESENT " << endl;
				//	cout << "PUSH " << t1[cur][i.first].val << endl;
				//	cout << "MATCH " << t1[cur][i.first].val << " = " << t2[eq][i.first].val << endl;
					proc.push(t1[cur][i.first].val);
					match[t1[cur][i.first].val] = t2[eq][i.first].val;
				}
			}
			if(valid)
			break;
		}
		
		proc.pop();
	}
	
	string ans = trace(t1,parent1,set);
	return ans;
}


void printTrie(trie &t1,vector<int> &p)
{
	int cur = 0;
	queue<int> proc;
	proc.push(cur);
	while(proc.empty() == false)
	{
		cur = proc.front();
		cout << "cur = " << cur << endl;
		for(auto i : t1[cur])
		{
			if(i.first != '$')
			{
				cout << i.first << " " << t1[cur][i.first].val << endl; 
				proc.push(t1[cur][i.first].val);
			}
			else
			{
				cout << i.first << " " << t1[cur][i.first].val << endl;
			}
		}
		proc.pop();
	}
}

int main()
{
	string s1,s2;
	cin >> s1 >> s2;
	
	vector<int> p1,p2;
	trie t1 = buildTrie(s1,p1),t2 = buildTrie(s2,p2);
	
	//printTrie(t1,p1);
	//cout << endl;
	//printTrie(t2,p2);
	//cout << endl;
	
	cout << minMismatch(t1,p1,t2,p2) << endl;
	return 0;
}
