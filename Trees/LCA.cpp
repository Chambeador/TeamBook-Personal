const int N = 2e5+100;
vector<vector<int>> g(N);
vector<int> dist(N,0);
vector<vector<int>> saltos(25, vector<int> (N));
 
//dfs para calcular el nivel 2^0 del binary lifting y la distancia a los nodos
void dfs(int u, int p = -1, int d = 0){
     saltos[0][u] = p;
     if(saltos[0][u] == -1) saltos[0][u] = u;
     dist[u] = d;
     for(auto v: g[u]){
         if(p == v) continue;
         dfs(v,u,d+1);
     }
}
 
//construccion de la tabla del binary lifting
void build(int n){
     for(int i = 0; i < 25; i++){
        for(int j = 0; j < n; j++) 
            saltos[i][j] = -1;
     }
     dfs(0);
     for(int i = 1; i < 25; i++){
        for(int u = 0; u < n; u++){
            if(saltos[i-1][u] != -1){
               saltos[i][u] = saltos[i-1][saltos[i-1][u]];
            }
        }
     }
}
 
//metodo para sacar el lca del nodo v, u
int lca(int u, int v){
    if(dist[u] < dist[v]) swap(u,v);
    int distancia = dist[u]-dist[v];
    for(int i = 24; i >= 0; i--){
         if((distancia>>i)&1){
             u = saltos[i][u];
         }
    }
 
    if(u == v) return u;
    
    for(int i = 24; i >= 0; i--){
        if(saltos[i][u] != saltos[i][v]){
            u = saltos[i][u];
            v = saltos[i][v];
        }
    }
    return saltos[0][u];
}


