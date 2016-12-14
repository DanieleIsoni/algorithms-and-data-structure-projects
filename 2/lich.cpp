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



long int dmn=4000000, dmx=0;
int trova(long int root, long int from,  long int L, long int* cammini)
{
  cout<<"TROVA "<<root<<" "<<from<<endl;
  if(adj[root].size()==1 && root!=from)
  {
    //if(cammini[*(adj[root].begin())->first]>= dmn &&  cammini[*(adj[root].begin())->first]>=)
    //FOGLIA
    int tempMin = min(dmn, cammini[root]);
    int tempMax = max(dmx, cammini[root]);
    if(abs(tempMin-tempMax)<=L)
      {
        dmn=tempMin;
        dmx=tempMax;
        return 1;
      }
    else
      return 0;
  }
  else
  {
    int c=1;
    int b=-1;
    for(auto &x : adj[root])
      {
        int tempMin = min(dmn, cammini[x.first]);
        int tempMax = max(dmx, cammini[x.first]);
        if(x.first!=from && abs(tempMin-tempMax)<=L){
          dmn=tempMin;
          dmx=tempMax;
          c+=trova(x.first,root,L,cammini);
        }
        else if(x.first!=from)
        {
          b=max(b,trova(x.first,root,L,cammini));
        }
      }

      return max(c,b);
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
  long int cammini[N];
  for(int i=0;i<N;i++){
    cammini[i]=dfs(i,-1);
    cout<<cammini[i]<<"\n";
  }

  for(int i=0;i<nl;i++)
  {
    int val=trova(0,-1,L[i],cammini);
    cout<<L[i]<<"->"<<val<<endl;
    out<<L[i]<<endl;
    dmn=4000000;
    dmx=-1;

  }


  return 0;
}
