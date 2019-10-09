#include <bits/stdc++.h>
using namespace std;

int main(int argc,char* argv[]) {
        int N,M ;
        if(argc<2){
                cerr<<"Unsufficient number of arguments" ;
                return 0 ;
        }
        string test=argv[1] ;
        ifstream NM ;
        NM.open(test+".NM") ;
        NM>>N>>M ;
        NM.close() ;
        string input = test+".satoutput" ;
        string output = test+".mapping" ;
        freopen(input.c_str(), "r", stdin);
        freopen(output.c_str(), "w", stdout);        
        string s;
        cin>>s;
        if(s=="UNSAT"){
                cout<<'0';
                return 0;
        }
        vector<vector<int> > maping;
        for(int i=0;i<M;i++){
                int flag =0;
                vector<int> t;
                maping.push_back(t);
                for(int j=0;j<N;j++){
                        int k;
                        cin>>k;
                        if(k>0) k=1;
                        else k=0;
                        maping[i].push_back(k);
                        
                        if(maping[i][j]>0 && flag>0){
                                cout<<'0';
                                return 0;
                        }
                        if(maping[i][j]>0){
                                flag=1;
                        }
                        
                }
        }
        for(int i=0;i<M;i++){
                int index =0;
                for(int j=0;j<N;j++){
                        if(maping[i][j]>0){
                                cout<<i+1<<' '<<j+1<<endl;
                                break;
                        }
                }
        }
        return 0;
}