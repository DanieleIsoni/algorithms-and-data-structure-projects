#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> cycles;
int numeroCicli=0;
int N,M;

int time=0;

void calcolaLung(int from, int to, int * padri){
  cycles[numeroCicli].push_back(from);
  int count=1;
    while(from != to){
      count++;
      from=padri[from];
      //cout<<" added "<<from<<endl;
      cycles[numeroCicli].push_back(from);
    }
  //  cout<<"cliclo n. "<<numeroCicli<<" ha "<<count<<" elementi "<<endl;
    numeroCicli++;
  }

void dfs_visit(int u, int * color, int * padri){
    color[u]=1;
    for(int v : adj[u]){
      if(color[v]==0){
        padri[v]=u;
        dfs_visit(v,color,padri);
      }
      if(color[v]==1 && v != padri[u])
        calcolaLung(u,v,padri);
    }
    color[u]=2;
  }

void dfs(){
  int color[N];
  int d[N];
  int f[N];
  int padri[N];
  for(int i=0; i<N; i++){
    color[i]=0;
    padri[i]=-1;
  }

  for(int i=0; i<N; i++){
    if(color[i]==0)
      dfs_visit(i,color,padri);
  }
}

int MCD(int a, int b)
{
    do
    {
        if(a>b)
        {
            a = (a-b);
        }
        else if(a<b)
        {
            b = (b-a);
        }
    }
    while(a!=b);
    return a;
}

int main(){
  ifstream in("input.txt");
//  int N,M;
  in>>N>>M;
  adj.resize(N);
  cycles.resize(N);

  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
    adj[from].push_back(to);
    adj[to].push_back(from);
  }

  dfs();

  int MAX=cycles[0].size();
  for(int i=1;i<numeroCicli;i++){
    cout<<"Il ciclo "<<i<<" ha "<<cycles[i].size()<<" elementi \n";
    MAX=MCD(MAX,cycles[i].size());
    //for(int j=0;j<cycles[i].size();j++)
    //  cout<<"  "<<cycles[i][j];
    cout<<endl;
  }
cout<<"POKEMON MASSIMI --> "<<MAX<<endl;


  return 0;
}
