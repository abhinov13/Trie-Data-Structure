/*
The given code generates a single Trie out of all the given patterns. (It does not include the substrings within a pattern).
*/
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t(1);
  // write your code here
  int prev;
  for(int s = 0;s < patterns.size();s++)
  {
  	prev = 0;
  	for(int i = 0;i < patterns[s].size();i++)
  	{
  		if(t[prev][patterns[s][i]] == 0)
  		{
  			t[prev][patterns[s][i]] = t.size();//push back the node
  			t.resize(t.size() + 1);
  			prev = t.size() - 1;
		}
		else
		{
			prev = t[prev][patterns[s][i]];
		}
	}
  }
  
  return t;
}

int main()
{
  int n;
  cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++)
  {
   	string s;
    cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
