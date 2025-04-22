#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <iomanip>
#include <fstream>
using namespace std;

struct PeakMemory {
    size_t peak_mem_bytes;
};

// Graph class implementing BFS traversal with performance measurements
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

    // Calculate static space used by the graph
    size_t calculateSpace() {
        size_t space = 0;

        for (const auto& pair : adjList) {
            space += sizeof(pair.first) + sizeof(pair.second) + pair.second.size() * sizeof(int);
        }

        return space;
    }

    // Calculate peak memory used by BFS    
    PeakMemory bfsWithPeakMem(int start) {
        unordered_set<int> visited;
        queue<int> q;
        size_t peak_memory = 0;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            // Calculate current memory usage
            size_t current_memory = 0;
            current_memory += visited.size() * sizeof(int); // Memory for the visited set
            current_memory += q.size() * sizeof(int); // Memory for the queue
            
            // If current memory usage is higher than peak, update the peak
            peak_memory = std::max(peak_memory, current_memory);

            int current = q.front();
            q.pop();

            for (int neighbor : adjList[current]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }

        return {peak_memory};
    }

    // Measure BFS peak memory usage
    PeakMemory measurePeakMem(int start, int run_number) {
        PeakMemory metrics = bfsWithPeakMem(start);
        cout << "\nPeak memory during BFS" << run_number << ": " << metrics.peak_mem_bytes << " bytes";
        return metrics;
    }

};


int main() {
    Graph g;

    ofstream sparseFile("sparse_bfs_results.csv");
    ofstream denseFile("dense_bfs_results.csv");

    if (!sparseFile.is_open()) {
        cerr << "Error: Could not open 'sparse_bfs_results.csv'" << endl;
        return 1;
    }
    if (!denseFile.is_open()) {
        cerr << "Error: Could not open 'dense_bfs_results.csv'" << endl;
        sparseFile.close();
        return 1;
    }

    sparseFile << "Size,Time(ms),Static_Space(bytes),Peak_Memory(bytes)\n";
    denseFile << "Size,Time(ms),Static_Space(bytes),Peak_Memory(bytes)\n";


    vector<int> sparse_sizes = {100, 1000, 2500, 5000, 10000};    
    vector<int> dense_sizes = {100, 1000, 2500, 5000}; // avoid huge sizes for dense

    for (int size : sparse_sizes) {
        for (int i = 0; i < size; ++i) {
            g.addEdge(i, i + 1);
        }

        std::cout << "\nTesting graph with " << size << " nodes: " << endl;

        double total_time = 0;
        size_t total_peak_memory = 0;
        for (int run = 0; run < sparse_sizes.size(); run++) {
            double time = g.measureBFS(0, run + 1);
            PeakMemory mem = g.measurePeakMem(0, run + 1);
            total_time += time;
            total_peak_memory += mem.peak_mem_bytes;
        }
        std::cout << endl;
        
        double average_time = total_time / sparse_sizes.size();
        size_t average_peak_memory = total_peak_memory / sparse_sizes.size();
        size_t static_space = g.calculateSpace();

        std::cout << "Average time: " << fixed << setprecision(3) << average_time << " ms" << endl;
        std::cout << "Static space: " << static_space << " bytes" << endl;
        std::cout << "Average peak memory: " << average_peak_memory << " bytes" << endl;

        sparseFile << size << "," << average_time << "," << static_space << "," << average_peak_memory << "\n";

        g.clear();
    }

    for (int size : dense_sizes) {
        int k = size / 10; // 10% dense

        g.addDenseEdges(g, size, k);
        std::cout << "\nTesting graph with " << size << " nodes: " << endl;

        double total_time = 0;
        size_t total_peak_memory = 0;
        for (int run = 0; run < dense_sizes.size(); run++) {
            double time = g.measureBFS(0, run + 1);
            PeakMemory mem = g.measurePeakMem(0, run + 1);
            total_time += time;
            total_peak_memory += mem.peak_mem_bytes;
        }
        std::cout << endl;
        
        double average_time = total_time / dense_sizes.size();
        size_t average_peak_memory = total_peak_memory / dense_sizes.size();
        size_t static_space = g.calculateSpace();

        std::cout << "Average time: " << fixed << setprecision(3) << average_time << " ms" << endl;
        std::cout << "Static space: " << static_space << " bytes" << endl;
        std::cout << "Average peak memory: " << average_peak_memory << " bytes" << endl;

        denseFile << size << "," << average_time << "," << static_space << "," << average_peak_memory << "\n";

        g.clear();
    }

    sparseFile.close();
    denseFile.close();
    std::cout << "\nResults have been printed to 'sparse_bfs_results' and 'dense_bfs_results'" << endl;
    return 0;
}
