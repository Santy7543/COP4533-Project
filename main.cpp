#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList; // undirected/bi-directional graph

public:
    // Add edge function
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // BFS function
    void bfs(int start) {
        std::unordered_set<int> visited;
        std::queue<int> q;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    // Measure BFS time
    void measureBFS(int start) {
        auto start_time = std::chrono::high_resolution_clock::now();

        bfs(start);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        std::cout << "\nTime taken for BFS: " << elapsed.count() << " ms\n";
    }

    // Calculate space used by the graph
    size_t calculateSpace() {
        size_t space = 0;

        for (const auto& pair : adjList) {
            space += sizeof(pair.first) + sizeof(pair.second) + pair.second.size() * sizeof(int);
        }

        return space;
    }
};


int main() {
    Graph g;
    for (int i = 0; i < 1000; ++i) {
        g.addEdge(i, i + 1);
    }

    std::cout << "BFS starting from node 0:\n";
    g.measureBFS(0);\
    std::cout << "Space used by the graph: " << g.calculateSpace() << " bytes\n";
    return 0;
}
