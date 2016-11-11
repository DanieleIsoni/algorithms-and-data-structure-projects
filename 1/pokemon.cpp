#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

vector<vector<int> > adj;
//stack<stack<int>> cycles;
set<int> supporto;

void calcolaCiclo(int from, int to, int * added){
  cout<<from<<" "<<to<<endl;
  if(from!=-1 && to!=-1){
    if(supporto.find(from)==supporto.end() )
      supporto.insert(from);
    if(supporto.find(to)==supporto.end() )
      supporto.insert(to);
    if(from != to )
      calcolaCiclo(added[from],added[to],added);
    else
      cout<<"fine ciclo"<<endl;
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
      calcolaCiclo(from,to, added);
    }
    else
      added[to]=from;
    adj[from].push_back(to);
  	adj[to].push_back(from);
  }

	cout<<"COUNTED --> "<<counterCycles<<endl;
for(int i=0;i<N;i++) cout<<added[i]<<" ";


	/*
  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
	*/

  return 0;
}
