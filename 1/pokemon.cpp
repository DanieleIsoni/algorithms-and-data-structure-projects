#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <queue>

using namespace std;

vector<vector<int> > adj;

void mostraPercorso(int u, int v, int * padri){
  while (padri[u]!=padri[v]) {
    cout<<padri[u]<<" "<<padri[v]<<endl;
    if(padri[u]!=-1)
      u=padri[u];
    if(padri[v]!=-1)
      v=padri[v];
  }
}


void bfs(int r, int N, int * padri){
  queue<int> q;
  q.push(r);
  bool visitato[N];
  for (int i = 0; i < N; i++) {
    visitato[i]=false;
  }
  visitato[r]=true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for(int v : adj[u]){
      if(!visitato[v]){
        visitato[v]=true;
        q.push(v);
      }
      else if(u<v){
        cout<<"Trovato collegamento da "<<u<<" a "<<v<<endl;
        mostraPercorso(u,v,padri);
      }
    }
  }
}

int main(){
  ifstream in("input.txt");
  int N,M;
  in>>N>>M;
  adj.resize(N);

	//used to count cycles
	int counterCycles=0;
	int added[N];
  for(int i=0;i<N;i++) added[i]=-1;


  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
	  if(added[to]!=-1){
			counterCycles++;
      //trovato ciclo
    }
    else
      added[to]=from;
    adj[from].push_back(to);
  	adj[to].push_back(from);
  }

  bfs(0,N,added);


	/*
  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
	*/

  return 0;
}
