#include<bits/stdc++.h>
using namespace std;
template<typename T>



class Unweighted_Graph{
    // Features
    //   - 1. can create directed graph 
    //   - 2. can create undirected graph
    //   - 3. Print your adjacency list
    //   - 4. can detect cycle for both type of graphs
    //   - 5. can print the length of shortest path from a given source node to a given destination node
    //   - 6. Topological sorted order
    

public:
    // adj represents the adjacency list representation of a graph
    map<T,vector<T>> adj;


    // 0 -> use 0 for creating a directed graph
    // 1 -> use 1 for creating a undirected graph
    // U denotes the source node
    // V denotes the destination node

    void addEdge(T u,T v,int dir=1){
        adj[u].push_back(v);
        if(dir == 1){
            adj[v].push_back(u);
        }
    }

    void print_graph(){
        // node represents the current node
        for(auto node: adj){
            // print the current node
            cout<<node.first<<" "<<"->"<<" ";
            // print all its neighbours
            for(auto nbr: adj[node.first]){
                cout<<nbr<<" ";
            }
            cout<<endl;
        }
    }


    // Utility functiomn for detecting a cycle
    bool dfs(map<T,int> &visited,T curr){
        // 0 -> node visited yet
        // 1 -> in recursion stack
        // 2 -> completely explored

        // Put this node in the recursion stack
        visited[curr] = 1;
        bool is_cyclic = false;


        // Explore all its neighbours
        for(auto nbr: adj[curr]){
            if(visited[nbr] == 0){
                is_cyclic = dfs(visited,nbr);
                if(is_cyclic){
                    return true;
                }
            }
            else if(visited[nbr] == 1){
                is_cyclic = true;
                return true;
            }
        }

        // Mark current node as completely explored  
        visited[curr] = 2;
        return is_cyclic;
    }


    bool detect_cycle_directed(){
        map<T,int> visited;
        // Mark all nodes as unvisited
        for(auto node: adj){
            visited[node.first] = 0;
        }
        bool cyclic = false;


        for(auto node: adj){
            if(visited[node.first] == 0){
                cyclic = dfs(visited,node.first);
            }
        }

        return cyclic;
    }



   bool cycle_unweighted_helper(T curr,map<T,int> &visited,T parent){
        visited[curr] = 1;


        for(auto nbr: adj[curr]){
            if(nbr == parent){
                continue;
            }
            else if(visited[nbr] == 1){
                return true;
            }
            else if(visited[nbr] == 0){
                bool is_cycle = cycle_unweighted_helper(nbr,visited,curr);
                if(is_cycle){
                    return true;
                }
            }
        }

        return false;
    }


    bool detect_cycle_undirected(){
        map<T,int> visited;

        // Mark all nodes as Unvisited
        for(auto node: adj){
            visited[node.first] = 0;
        } 

        for(auto node: adj){
            if(visited[node.first] == 1){
                continue;
            }
            bool iscycle = cycle_unweighted_helper(node.first,visited,-1);
            if(iscycle){
                return true;
            }
        }
        return false;
    }




    void detect_cycle(int dir = 1){
        if(dir == 1){
            bool is_cycle = detect_cycle_undirected();

            if(is_cycle){
                cout<<"CYCLE FOUND"<<endl;
            }
            else{
                cout<<"CYCLE NOT FOUND"<<endl;
            }
            return ;
        }
        else{
            bool is_cycle = detect_cycle_directed();

            if(is_cycle){
                cout<<"CYCLE FOUND"<<endl;
            }
            else{
                cout<<"CYCLE NOT FOUND"<<endl;
            }
        }
    }


    void shortest_path(T source,T destination){
        map<T,int> visited,dist;
        // Mark all nodes Unvisited
        for(auto node: adj){
            visited[node.first] = 0;
            dist[node.first] = 0;
        }

        // Make a Queue for storing nodes
        queue<T> q;

        // Insert the source node into the queue to start the traversal
        q.push(source);
        visited[source] = 1;

        while(!q.empty()){
            T curr = q.front();
            q.pop();

            for(auto nbr: adj[curr]){
                if(visited[nbr] == 1){
                    continue;
                }
                q.push(nbr);
                visited[nbr] = 1;
                dist[nbr] = dist[curr] + 1;
            }
        }

        cout<<dist[destination]<<endl;
    }


    bool dfs_for_topo(map<T,int> &visited,T curr,vector<T> &ans){
        // 0 -> node visited yet
        // 1 -> in recursion stack
        // 2 -> completely explored

        // Put this node in the recursion stack
        visited[curr] = 1;
        bool is_cyclic = false;


        // Explore all its neighbours
        for(auto nbr: adj[curr]){
            if(visited[nbr] == 0){
                is_cyclic = dfs_for_topo(visited,nbr,ans);
                if(is_cyclic){
                    return true;
                }
            }
            else if(visited[nbr] == 1){
                is_cyclic = true;
                return true;
            }
        }

        // Mark current node as completely explored  
        visited[curr] = 2;
        ans.push_back(curr);
        return is_cyclic;
    }


    void topo_order(int dir = 1){
        if(dir == 1){
            cout<<"CANNOT DO"<<endl;
            return ;
        }
        
        map<T,int> visited;
        for(auto node: adj){
            visited[node.first] = 0;
        }
        vector<T> ans;
        for(auto node: adj){
            if(node.first == 0){
                int can_do = dfs_for_topo(visited,node.first,ans);

                if(can_do == true){
                    cout<<"CANNOT DO"<<endl;
                    return ;
                }
            }
        }
        for(auto node: ans){
            cout<<node<<" ";
        }
        cout<<endl;


    }

};





int main(){
    Unweighted_Graph<int> g;
    g.addEdge(0,1,0);
    g.addEdge(1,2,0);
    g.addEdge(2,3,0);
    g.addEdge(3,4,0);
    //g.addEdge(3,0,0);
    g.print_graph();
    g.detect_cycle(0);
    g.shortest_path(0,4);
    g.topo_order(0);

    return 0;
}