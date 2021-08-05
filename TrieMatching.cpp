/*
The given code is useful for string matching between a string and multiple patterns are present.
Note: only {'A','C','G','T'} are the allowed characters within the text and patterns and the strings should be ended with a variable
that does not belong to this set to mark their end points.
You can hardcode the main function to make it so that the user does not need to manually end the string with a random symbol that is not
in the set. 
*/
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}
	int operator[](int i)
	{
		return next[i];
	}
	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};
void set(Node &node,int l,int r)
{
	node.next[l] = r;
}
int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}
vector<Node> BuildTrie(const vector<string> &patterns)
{
	vector<Node> trie(1);
	
	int prev = 0;
	for(int s = 0; s < patterns.size();s++)
	{
		for(int i = 0;i < patterns[s].size();i++)
		{
			if(trie[prev][letterToIndex(patterns[s][i])] == NA)
			{
				set(trie[prev],letterToIndex(patterns[s][i]),trie.size());
				trie.resize(trie.size() + 1);
				prev = trie.size() - 1;
			}
			else
			{
				prev = trie[prev][letterToIndex(patterns[s][i])];
			}
		}
	}
	return trie;
}
bool matches(string& text,vector <Node>& trie)
{
	//matching code
	int i = 0,cur = 0;
	while(i < text.size())
	{
		if(trie[cur][letterToIndex(text[i])] == NA)
		{
			return false;
		}
		else
		{
			cur = trie[cur][letterToIndex(text[i])];
		}
		i++;
	}
	return true;
}
vector <int> solve (string text, int n, const vector <string>& patterns)
{
	vector <int> result;
	vector<Node> trie;
	trie = BuildTrie(patterns);
	
	string sub;
	for(int i = 0;i < text.size();i++)
	{
		sub = text.substr(i,text.size() - i);
		if(matches(sub,trie))
		{
			result.push_back(i);
		}
	}
	
	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
