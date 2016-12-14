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


int valori[10000];
void dfsInsimi(int node, int father, int * cammini, int mn, int mx, int size, int L){
  for(auto &x : adj[node]){
      if(father!=x.first){
        //cout<<size<<" "<<x.first<<" "<<node<<" "<<father<<" ADS "<<mn<<" "<<mx<<" "<<cammini[x.first]<<" if -->"<<(abs(mn-cammini[x.first])<=L && abs(mx-cammini[x.first])<=L)<<endl;

      int mn2 = min(mn,cammini[x.first]);
      int mx2 = max(mx,cammini[x.first]);
      if(abs(mn-cammini[x.first])<=L && abs(mx-cammini[x.first])<=L)
        dfsInsimi(x.first,node,cammini,mn2,mx2,size+1,L);
      else{
        dfsInsimi(x.first,node,cammini,cammini[x.first],cammini[x.first],1,L);

            cout<<"Finito --> "<<size<<endl;
      }

    }

  }
//  if(counter==0)
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

  //bfs(0,N,cammini);
for (int i = 0; i < nl; i++) {
  cout<<"------ "<<L[i]<<" -------"<<endl;

  dfsInsimi(0,-1,cammini,cammini[0],cammini[0],1,L[i]);
  /* code */
}




  return 0;
}
