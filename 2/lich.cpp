#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <stack>
#include "math.h"
using namespace std;

typedef pair<int,int> coppia;

long int N;
map<long int,int> MEMO;
vector<vector<coppia> > adj;
vector<long unsigned int> L;

int abs(int a){
  return a<0?-a:a;
}

int dfs(int node, int from){
  int ret=0;
  long int i=node+(N*(from+1));//coppia(node,from);
  int m=MEMO[i];
  if(from !=-1 && m!=0){
    return m;
  }

  for(auto &x : adj[node]){
    if(from!=x.first){
      ret=max(dfs(x.first,node)+x.second,ret);
    }
  }
  MEMO[i]=ret;
  return ret;
}




int trova(long int root, long int from, long int dmn, long int dmx)
{
  int c=0;
  for(auto &x :adj[root])
  {
    int mx=0;
    if(x.first!=from && abs(cammini[x.first]-dmn)<=L && abs(cammini[x.first]-dmx)<=L)
    {
      c++;
      mx=max(mx, max(trova(x.first, root,cammini[x.first],cammini[x.first]),trova(x.first, root, )));
    }
  }
  if(c==0)
  {
    return 1;
  }



}



















int main(){
  ifstream in("input.txt");
  in >> N;
  adj.resize(N);
  for(int i=0;i<N-1;i++){
    int a,b,c;
    in>>a>>b>>c;
    adj[a].push_back(coppia(b,c));
    adj[b].push_back(coppia(a,c));
  }

  long int nl;
  in>>nl;
  L.resize(0);
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
