#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> cicli;
int numCicli = 0;

void stampaCiclo(int s, int v, int * parents){
  cout << "s " << s << " v " << v << endl;
  while(s!=v){
    cout << s << " ";
    s = parents[s];
  }
  cout << s << endl;
}

/*
  Questa funzione mi dà segmentation fault solo perchè uso una matrice di vector
  se usassi una matrice semplice (int cicli[100][100]) non dà errore e non
  capisco perché
*/
void salvaCiclo(int s, int v, int * parents){
  while(s != v){
    cout << "ciao" << endl;
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
    numCicli++;
  }
}

void dfs(int s, int * parents, bool * visited){
  visited[s]=true;
  for(int v: adj[s]){
    if (!visited[v]){
      parents[v]=s;
      dfs(v, parents, visited);
    } else if (s > v) {
      stampaCiclo(s, v, parents);
      //salvaCiclo(s, v, parents);
    }
  }
}

int main(){
  ifstream in("input.txt");
  int N,M;
  in>>N>>M;
  adj.resize(N);

  int parents[N];
  for(int i=0;i<N;i++)
    parents[i]=-1;

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

  dfs(0,parents, visited);
  cout << endl << "parents:" << " ";
  for (int i = 0; i < N; i++) {
    cout << parents[i] << " ";
  }
  cout << endl;

  /*
  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
*/

  return 0;
}
