#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> adjTemp;
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
      cout<<" added "<<from<<endl;
      cycles[numeroCicli].push_back(from);
    }
    cout<<"cliclo n. "<<numeroCicli<<" ha "<<count<<" elementi "<<endl;
    numeroCicli++;
  }

void dfs_visit(int u, int * color, int * padri){
    color[u]=1;
    for(int v : adj[u]){
      if(color[v]==0){
        padri[v]=u;
        cout<<"from "<<u<<" to "<<v<<endl;
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




pair<int,int> coppia(int a, int b)
{
  pair<int,int> x;
  if(a<b)
    {
      x.first=a;
      x.second=b;
    }
  else
  {
    x.first=b;
    x.second=a;
  }
  return x;
}

bool eliminaDuplicati(){
  set<pair<int,int> > archi;
  bool ret=false;
//vector<int>  cicli;
//  cicli.resize(cicli.size());

  for(vector<int> &c :cycles)
  {

    if(c.size()>2)
    {
      int cont=0;
      for(int i=0;i<c.size()-1;i++)
      {
        set<pair<int,int> >::iterator it=archi.find(coppia(c[i],c[i+1]));
        if(it!=archi.end())
        {
          //elimino quelli in comune dal grafo precedente
          int a=(*it).first;
          int b=(*it).second;
          adj[a].erase(std::remove(adj[a].begin(), adj[a].end(), b), adj[a].end());
          cont++;

          adj[b].erase(std::remove(adj[b].begin(), adj[b].end(), a), adj[b].end());
          //ret=true;

        }
        else
        {

            archi.insert(coppia(c[i],c[i+1]));
        }

      }
      set<pair<int,int> >::iterator it=archi.find(coppia(c[c.size()-1],c[0]));
      if(it!=archi.end())
      {
        cont++;
        //int a=(*it).first;
        //int b=(*it).second;
        //adj[a].erase(std::remove(adj[a].begin(), adj[a].end(), b), adj[a].end());
        //adj[b].erase(std::remove(adj[b].begin(), adj[b].end(), a), adj[b].end());
      }

        //cout << "cont:" <<cont<<" size: "<<c.size()<< endl;
        //se il numero di achi in comune tra almeno 2 cicli è pari
        if(cont%2==1)
          return true;
    }

  }
    return false;

}

bool eliminaDuplicati2(){
  set<pair<int,int> > archi;
  bool ret=false;
//vector<int>  cicli;
//  cicli.resize(cicli.size());

  for(vector<int> &c :cycles)
  {

    if(c.size()>2)
    {
      int cont=0;
      for(int i=0;i<c.size()-1;i++)
      {
        set<pair<int,int> >::iterator it=archi.find(coppia(c[i],c[i+1]));
        if(it!=archi.end())
        {
          //elimino quelli in comune dal grafo precedente
          int a=(*it).first;
          int b=(*it).second;
          adj[a].erase(std::remove(adj[a].begin(), adj[a].end(), b), adj[a].end());
          cont++;

          adj[b].erase(std::remove(adj[b].begin(), adj[b].end(), a), adj[b].end());
          return true;

        }
        else
        {

            archi.insert(coppia(c[i],c[i+1]));
        }

      }

      set<pair<int,int> >::iterator it=archi.find(coppia(c[c.size()-1],c[0]));
      if(it!=archi.end())
      {
        cont++;
        //int a=(*it).first;
        //int b=(*it).second;
        //adj[a].erase(std::remove(adj[a].begin(), adj[a].end(), b), adj[a].end());
        //adj[b].erase(std::remove(adj[b].begin(), adj[b].end(), a), adj[b].end());
      }


        //cout << "cont:" <<cont<<" size: "<<c.size()<< endl;
        //se il numero di achi in comune tra almeno 2 cicli è pari
        if(cont%2==1)
          return true;
    }

  }
    return false;

}


map<pair<int,int> ,int> piazzaPokemon(int m)
{
  map<pair<int,int> ,int> pokemon;

//vector<int>  cicli;
//  cicli.resize(cicli.size());

  for(vector<int> &c :cycles)
  {
    int questo=0;
    if(c.size()>2)
    {
      //controllo che in nessun arco ci sia già un pokemon
      /* map<pair<int,int> ,int>::iterator trovato=pokemon.end();

      for(int i=0;i<c.size()-1 && trovato==pokemon.end();i++)
      {
        map<pair<int,int> ,int>::iterator it=pokemon.find(coppia(c[i],c[i+1]));
        if(it!=pokemon.end())
        {
          trovato=it;//calcolo l'indice dell'arco che ho trovato
        }
      }

      if(trovato==pokemon.end())//allora questo è un ciclo normale
    */    for(int i=0;i<c.size()-1;i++)
          {
            questo=(1+questo)%m;
            pokemon[coppia(c[i],c[i+1])]=questo;
          }

    /* LE RIGHE QUA SALTANO L'ARCO CON IL POKEMON GIÀ POSIZIONATO
    else
      {
        questo=(*trovato).second;
        cout<<"TROVATO -> "<<questo<<endl;
        for(int i=0;i<c.size()-1;i++)
        {

          pair <int,int> test = coppia(c[i],c[i+1]);
          cout<<(*trovato).first.first<<" "<<test.first<<" AND "<<(*trovato).first.second<<" "<<test.second<<endl;
          if((*trovato).first.first!=test.first || (*trovato).first.second!=test.second)
          {//arco normale
            questo=(1+questo)%m;
            pokemon[test]=questo;

              cout<<"questo ->"<<questo<<endl;
          }
          else{
            cout<<"trovato arco in comune"<<endl;
          }

          //altrimenti non faccio niente e mantenfo il vecchio pokemon
        }

      }*/
    }

  }
    return pokemon;
}

//bool verifica(int m )



int main(){
  ifstream in("input.txt");
//  int N,M;
  in>>N>>M;
  adj.resize(N);
  adjTemp.resize(N);
  cycles.resize(N);

  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
    adj[from].push_back(to);
    adj[to].push_back(from);
    adjTemp[from].push_back(to);
    adjTemp[to].push_back(from);
  }

  dfs();

 bool dispari=eliminaDuplicati();

 int j = 0;
 for (auto x: adjTemp){
   adj[j] = x;
 }
 dispari = dispari || eliminaDuplicati2();

  //dfs();

  int MAX=cycles[0].size();
  for(int i=0;i<numeroCicli;i++){
    cout<<"Il ciclo "<<i<<" ha "<<cycles[i].size()<<" elementi \n";
    MAX=MCD(MAX,cycles[i].size());

   for(int &b : cycles[i])
      cout<<b<<"\t";
    cout<<endl<<endl;
  }
  if(dispari && MAX!=1 && MAX%2 == 0 && MAX != 6)
    MAX/=2;


  map<pair<int,int> ,int> pokemon=piazzaPokemon(MAX);



  ofstream out("output.txt");

  //cout<<"POKEMON MASSIMI --> "<<MAX<<endl;
  out<<MAX<<endl;
  for(int v=0;v<N;v++)
    for(int &w :adjTemp[v])
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
