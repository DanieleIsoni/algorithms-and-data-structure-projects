#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int> > adj;

int dfs(int s, bool * visitato){
		visitato[s]=false;
		int tot=0;
		if((adj[s]).size()>1){
			for(int vicino : adj[s]){
				if(!visitato[vicino]){
					tot+=dfs(vicino,visitato);
				}
				else
					return 1;
			}
		}
		
		return tot;
}

int main(){
  ifstream in("input.txt");
  int N,M;
  in>>N>>M;
  adj.resize(N);
  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
    adj[from].push_back(to);
	adj[to].push_back(from);
  }
  
  bool visitato[N];
  for(int i=0;i<N;i++) visitato[i]=false;
  

  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
  
  
  cout<<dfs(0,visitato);
  return 0;
}
