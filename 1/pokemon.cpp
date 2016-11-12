#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> cycles;
int numeroCicli=0;
int N,M;

int Time=0;

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

map<pair<int,int> ,int> piazzaPokemon(int m)
{
  map<pair<int,int> ,int> pokemon;

//vector<int>  cicli;
//  cicli.resize(cicli.size());

  for(vector<int> &c :cycles)
  {
    int questo=-1;//tanto lo incremento a 0 prima di assegnarlo
    for(int i=1;i<c.size();i++)
      {

        pair<int,int> x;
        if(c[i-1]<c[i])
          {
            x.first=c[i-1];
            x.second=c[i];
          }
        else
        {
          x.first=c[i];
          x.second=c[i-1];
        }

        pokemon[x]=(++questo)%m;

      }
    }

    return pokemon;
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
    //cout<<"Il ciclo "<<i<<" ha "<<cycles[i].size()<<" elementi \n";
    MAX=MCD(MAX,cycles[i].size());

//    for(int &b : cycles[i])
//      cout<<b<<"\t";
//    cout<<endl<<endl;
  }



  map<pair<int,int> ,int> pokemon=piazzaPokemon(MAX);
  ofstream out("output.txt");

  //cout<<"POKEMON MASSIMI --> "<<MAX<<endl;
  out<<MAX<<endl;
  for(int v=0;v<N;v++)
    for(int &w :adj[v])
    {
        if(v<w)//altrimenti l'ho già stampato
        {

            pair<int,int> p;
            p.first=v; p.second=w;
          if( pokemon.find(p) != pokemon.end())
          {
            //cout<<"ARCO "<<v<< " "<<w<<" POKEMON "<<pokemon[p]<<endl;
            out<<pokemon[p]<<endl;
          }
          else
            //cout<<"ARCO "<<v<< " "<<w<<" POKEMON 0"<<endl;
            out<<pokemon[p]<<endl;
        }
  }
  return 0;
}
