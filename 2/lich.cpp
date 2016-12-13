#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <stack>
using namespace std;

typedef pair<int,int> coppia;

map<coppia,int> MEMO;
vector<vector<coppia> > adj;
vector<long unsigned int> L;
stack<int> foglie;

int dfs(int node, int from){
  int ret=0;
  coppia i=coppia(node,from);
  map<coppia,int>::iterator it=MEMO.find(i);
  if(from !=-1 && it!=MEMO.end() ){
    return (*it).second;
  }

  for(auto &x : adj[node]){
    if(from!=x.first){
      ret=max(dfs(x.first,node)+x.second,ret);
    }
  }
  MEMO[i]=ret;
  return ret;
}


int main(){
  ifstream in("input.txt");
  unsigned long int N;
  in >> N;
  adj.resize(N);
  for(int i=0;i<N-1;i++){
    int a,b,c;
    in>>a>>b>>c;
    adj[a].push_back(coppia(b,c));
    adj[b].push_back(coppia(a,c));
  }

  unsigned long int nl;
  in>>nl;
  L.resize(nl);
  for(int i=0;i<nl;i++){
    int c;
    in>>c;
    L.push_back(c);
  }




  ofstream out("output.txt");
  int cammini[N];
  for(int i=0;i<N;i++){
    cammini[i]=dfs(i,-1);
    cout<<cammini[i]<<"\n";
  }


  return 0;
}
