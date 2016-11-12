#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector< vector<int> > cicli;
int numCicli = 0;
int N,M;
//variabile di debug
int salvaCicloCounter = 0;

void stampaCiclo(int s, int v, int * parents){
  cout << "s " << s << " v " << v << endl;
  while(s!=v){
    cout << s << " ";
    s = parents[s];
  }
  cout << s << endl;
}

void salvaCiclo(int s, int v, int * parents){
  cout << "inizio salvaCiclo " << ++salvaCicloCounter <<"\n\n";
  if(cicli[numCicli].empty())
    cicli[numCicli].resize(0);
  while(s != v){
    cicli[numCicli].push_back(s);
    s = parents[s];
  }
  cicli[numCicli].push_back(s);

  /*
    Ho messo <= a 2 perchè ho visto che o mi ritorna un ciclo o mi ritorna
    una coppia sempre, quindi con questo controllo tolgo tutte le coppie
  */
  if(cicli[numCicli].size()<=2){
    cicli[numCicli].clear();
  } else {
    sort(cicli[numCicli].begin(), cicli[numCicli].end());
    numCicli++;
  }
}

void dfs(int s, int * parents, bool * visited){
  cout << "inizia dfs" << endl;
  visited[s]=true;
  for(int v: adj[s]){
    if (!visited[v]){
      parents[v]=s;
      dfs(v, parents, visited);
    } else if (s > v) {
      //stampaCiclo(s, v, parents);
      salvaCiclo(s, v, parents);
    }
  }
}

int mcd(int a, int b) {
    return b == 0 ? a : mcd(b, a % b);
}

int massimale(){
  int MCD = cicli[0].size();
  for (int i = 1; i < cicli.size(); i++) {
    MCD = mcd(MCD, cicli[i].size());
  }
  return MCD;
}

int main(){
  ifstream in("input.txt");
  in>>N>>M;
  adj.resize(N);
  cicli.resize(M);

  int parents[N];
  for(int i=0;i<N;i++)
      parents[i]=-1;

  /*for(int i=0;i<M;i++)
    cicli[i].resize(M);*/

  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
    adj[from].push_back(to);
    adj[to].push_back(from);
  }

  bool visited[N];
  for(int i=0; i<N; i++){
    visited[i]=false;
  }
  for (int i = 0; i < N; i++)
    dfs(0,parents, visited);

  //cout << massimale() << endl;

  /*cout << endl << "parents:" << " ";
  for (int i = 0; i < N; i++) {
    cout << parents[i] << " ";
  }*/
  cout << endl;
  for (int i = 0; i < cicli.size(); i++){
    for (int j = 0; j<cicli[i].size(); j++){
      cout << cicli[i][j] << " ";
    }
    if(cicli[i].size() != 0)
      cout << "\n\nlength: " << cicli[i].size() << "\n\n";
  }

/*
  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
*/

  return 0;
}
