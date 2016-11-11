#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > adj;



int main(){
  ifstream in("input.txt");
  int N,M;
  in>>N>>M;
  adj.resize(N);

	//used to count cycles
	int counterCycles=0;
	bool added[N];
  for(int i=0;i<N;i++) added[i]=false;


  for(int i=0;i<M;i++){
    int from, to;
    in>>from>>to;
	  if(added[to])
			counterCycles++;
    adj[from].push_back(to);
  	adj[to].push_back(from);
		added[to]=true;
  }

	cout<<"COUNTED --> "<<counterCycles<<endl;

	/*
  for(int i=0;i<N;i++){
    cout<<"Nodo "<<i<<" ha "<<adj[i].size()<<" vicini \n";
    for(int j=0;j<adj[i].size();j++)
      cout<<"  "<<adj[i][j]<<"\n";
  }
	*/

  return 0;
}
