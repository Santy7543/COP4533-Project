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

    ofstream dataFile("bfs_results.csv");
    dataFile << "Size,Time(ms),Space(bytes)\n";

    vector<int> sizes = {100, 1000, 10000, 100000};    

    for (int size : sizes) {
        for (int i = 0; i < size; ++i) {
            g.addEdge(i, i + 1);
        }

        cout << "\nTesting graph with " << size << " nodes: " << endl;

        double total_time = 0;
        for (int run = 0; run < 3; run++) {
            double time = g.measureBFS(0, run + 1);
            total_time += time;
        }
        cout << endl;
        
        double average_time = total_time / 3;
        size_t space = g.calculateSpace();

        cout << "Average time: " << fixed << setprecision(3) << average_time << " ms" << endl;
        cout << "Space used: " << space << " bytes" << endl;

        dataFile << size << "," << average_time << "," << space << "\n";

        g.clear();
    }

    dataFile.close();
    cout << "\nResults have been printed to 'bfs_results.csv'" << endl;
    return 0;
}
