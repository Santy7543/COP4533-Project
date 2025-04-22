#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjList; // undirected/bi-directional graph

public:
    void clear() {
        adjList.clear();
    }

    // Add edge function
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Adds dense edges
    // size is the number of vertices in the graph
    // k controls how many neighbors each vertex will be connected to 
    // For each vertex i, it connects to the next k vertices: (i+1), (i+2), ..., (i+k), as long as they are within bounds: <= (i+j)
    void addDenseEdges(Graph& g, int size, int k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 1; j <= k && i + j < size; ++j) {
                g.addEdge(i, i + j);
            }
        }
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
            //std::cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    // Measure BFS time
    double measureBFS(int start, int run_number) {
        auto start_time = std::chrono::high_resolution_clock::now();

        bfs(start);

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end_time - start_time;

        std::cout << "\nTime taken for BFS" << run_number << ": " << elapsed.count() << " ms";
        return elapsed.count();
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

    ofstream sparseFile("sparse_bfs_results.csv");
    ofstream denseFile("dense_bfs_results.csv");

    sparseFile << "Size,Time(ms),Space(bytes)\n";
    denseFile << "Size,Time(ms),Space(bytes)\n";


    vector<int> sparse_sizes = {100, 1000, 2500, 5000, 10000};    
    vector<int> dense_sizes = {100, 1000, 2500, 5000}; // avoid huge sizes for dense

    for (int size : sparse_sizes) {
        for (int i = 0; i < size; ++i) {
            g.addEdge(i, i + 1);
        }

        std::cout << "\nTesting graph with " << size << " nodes: " << endl;

        double total_time = 0;
        for (int run = 0; run < sparse_sizes.size(); run++) {
            double time = g.measureBFS(0, run + 1);
            total_time += time;
        }
        std::cout << endl;
        
        double average_time = total_time / 3;
        size_t space = g.calculateSpace();

        std::cout << "Average time: " << fixed << setprecision(3) << average_time << " ms" << endl;
        std::cout << "Space used: " << space << " bytes" << endl;

        sparseFile << size << "," << average_time << "," << space << "\n";

        g.clear();
    }

    for (int size : dense_sizes) {
        int k = size / 10; // 10% dense

        g.addDenseEdges(g, size, k);
        std::cout << "\nTesting graph with " << size << " nodes: " << endl;

        double total_time = 0;
        for (int run = 0; run < dense_sizes.size(); run++) {
            double time = g.measureBFS(0, run + 1);
            total_time += time;
        }
        std::cout << endl;
        
        double average_time = total_time / 3;
        size_t space = g.calculateSpace();

        std::cout << "Average time: " << fixed << setprecision(3) << average_time << " ms" << endl;
        std::cout << "Space used: " << space << " bytes" << endl;

        denseFile << size << "," << average_time << "," << space << "\n";

        g.clear();
    }

    sparseFile.close();
    denseFile.close();
    std::cout << "\nResults have been printed to 'sparse/dense_bfs_results" << endl;
    return 0;
}
