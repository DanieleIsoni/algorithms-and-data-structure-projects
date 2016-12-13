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

int dfs(int node, int from, int ** M){
  int ret=0;
  if(from !=-1 && M[node][from]!=-1){
    return M[node][from];
  }

  for(auto &x : adj[node]){
    if(from!=x.first){
      ret=max(dfs(x.first,node,M)+x.second,ret);
    }
  }
  M[node][from]=ret;
  return ret;
}
/*
int cammini(map<int,int> &MEMO, int r, int from)
{
  int m;
  if(MEMO.find(r)==MEMO.end() || MEMO[r]==0)
  {
    int mx=0;
    for(auto &x : adj[r])
      {
        if(from!=x.first)
          {
            m=cammini(MEMO,x.first,r);
            if(m==0)
              foglie.push(x.first);
          mx=max(mx,m+x.second);
          }
      }

    MEMO[r]=mx;
  }
  return MEMO[r];
}
*/

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

/*  map<int,int> MEMO;
  cammini(MEMO,0,-1);

  while(!foglie.empty())
  {
    int s=foglie.top();foglie.pop();
    cammini(MEMO,s,-1);
  }



  for(auto &x: MEMO)
    cout<<x.first<<"\t"<<x.second<<endl;*/
    int ** M = new int *[N];
    for(int i = 0; i <N; i++)
      M[i] = new int[N];
    for (int i = 0; i < N; i++) {
      for (int a = 0; a < N; a++) {
        M[i][a]=-1;
      }
    }





  int cammini[N];
  for(int i=0;i<N;i++){
    cammini[i]=dfs(i,-1,M);
    cout<<cammini[i]<<" ";
  }

  ofstream out("output.txt");
  for (int i = 0; i < N; i++) {
    for (int a = 0; a < N; a++) {
      out<<M[i][a]<<";";

    }
    out<<endl;
  }
  return 0;
}
