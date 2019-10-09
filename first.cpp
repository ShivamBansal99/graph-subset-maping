#include <bits/stdc++.h>
#define vi vector<int>
#define vvi vector<vi>

using namespace std ;

void printMat(vvi x){
        for(auto i:x){
                for(auto j:i)
                        cout<<j<<" ";
                cout<<endl ;
        }
}
int count_edges(vvi x){
        int count=0;
        for(auto i:x){
                for(auto j:i)
                        if(i[j]>0) count++;
        }
        return count;
}
vector<int> get_all_edges(vector<vector<int> > g, int n,int i){
    vector<int> edges;
    for(int j=0;j<n;j++){
        if(g[i][j]>0) edges.push_back(j);
    }
    return edges;
}

vector<int> get_all_non_edges(vector<vector<int> > g, int n,int i){
    vector<int> edges;
    for(int j=0;j<n;j++){
        if(g[i][j]==0) edges.push_back(j);
    }
    return edges;
}

int main(int argc,char *argv[]){
        string test=argv[1] ;
        string input=test+".graph" ;
        string output=test+".satinput" ;
        freopen(input.c_str(), "r", stdin);
        freopen(output.c_str(), "w", stdout);
        int a,b,temp,M=-1,N=-1 ;
        vvi gEdges,gDashEdges ;
        bool first=true,change=false ;
        while(cin>>temp){
                if(!first){ //scanned b
                        b=temp ;
                        if(a==0&&b==0){
                                change=true ;
                                first=!first ;
                                continue;
                        }
                        if(!change){        //for edges of G
                                if(max(a,b)>N)
                                        N=max(a,b) ;                        //N
                                gEdges.push_back(vi(2,0)) ;
                                gEdges[gEdges.size()-1][0]=a ;
                                gEdges[gEdges.size()-1][1]=b ;
                        }
                        else{                        //for Edges of GDash
                                if(max(a,b)>M)
                                        M=max(a,b) ;                        //M
                                gDashEdges.push_back(vi(2,0)) ;
                                gDashEdges[gDashEdges.size()-1][0]=a ;
                                gDashEdges[gDashEdges.size()-1][1]=b ;                                
                        }
                }
                a=temp ; //scanned a
                first=!first ;
        }
        ofstream NM ;
        NM.open(test+".NM") ;
        NM<<N<<" "<<M<<endl ;
        NM.close() ;
        vvi g(N,vi(N,0)) ;
        vvi g_dash(M,vi(M,0)) ;
        for(auto i:gEdges)
                g[i[0]-1][i[1]-1]=1 ;
        for(auto i:gDashEdges)
                g_dash[i[0]-1][i[1]-1]=1 ;
       // printMat(g) ;
       // printMat(g_dash) ;
        int g_dash_countEdges = count_edges(g_dash);
        int g_countNonEdges = N*N-count_edges(g);
        int count = g_dash_countEdges*g_countNonEdges+ g_dash_countEdges*N+(N*(M)*(M-1))/2+M*(1+(N*(N-1))/2);
        cout<<"p cnf "<<N*M<<' '<<count<<endl; 
        for(int i=0;i<M;i++){
                for(int j=0;j<N;j++){
                        cout<<i*N+j+1<<' ';
                }
                cout<<'0'<<endl;
                for(int j=0;j<N;j++){
                        for(int k=j+1;k<N;k++){
                                cout<<-1*(i*N+j+1)<<' '<<-1*(i*N+k+1)<<' '<<'0'<<'\n';
                        }
                }
        }
        for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                        for(int k=j+1;k<M;k++){
                                cout<<-1*(j*N+i+1)<<' '<<-1*(k*N+i+1)<<' '<<'0'<<'\n';
                        }
                }
        }
        vvi g_dash_all_edges;
        for(int i=0;i<M;i++){
        	vector<int> z = get_all_edges(g_dash,M,i);
        	g_dash_all_edges.push_back(z);
        }
        vvi g_all_edges;
        for(int i=0;i<N;i++){
        	vector<int> z = get_all_edges(g,N,i);
        	g_all_edges.push_back(z);
        }
        vvi g_dash_non_edges;
        for(int i=0;i<M;i++){
        	vector<int> z = get_all_non_edges(g_dash,M,i);
        	g_dash_non_edges.push_back(z);
        }
        for(int i=0;i<M;i++){
        	vector<int> z = g_dash_all_edges[i];
                for(int j=0;j<N;j++){
                        vector<int> y = g_all_edges[j];
                        for(int k=0;k<z.size();k++){
                                cout<<-1*(i*N+j+1)<<' ';
                                for(int r=0;r<y.size();r++){
                                        cout<<(z[k]*N+y[r]+1)<<' ';
                                }
                                cout<<' '<<'0'<<endl;
                        }
                }
        }
        for(int i=0;i<N;i++){
        	vector<int> y = g_all_edges[i];
                for(int j=0;j<M;j++){
                        vector<int> z = g_dash_non_edges[j];
                        for(int k=0;k<z.size();k++){
                                for(int r=0;r<y.size();r++){
                                        cout<<-1*(j*N+i+1)<<' '<<-1*(z[k]*N+y[r]+1)<<' '<<'0'<<endl;;
                                }
                                
                        }
                }
        }
}
