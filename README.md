# COP4533-Project
Graph Algorithms

## Overview
Implementation and analysis of a Breadth-First Search (BFS) algorithm:
A BFS is a graph traversal algorithm that visits all vertices at the current depth before moving to the next depth level.

## Dependencies
Required:
    - C++ compiler (g++)
    - Python 3
    - matplotlib library
    - pandas library
Note: Using Anaconda is recommended as it has Python and all required libraries (matplotlib and pandas) pre-installed.

## How to Run
plot.py will automatically compile and run main.cpp and display the visualizations once ran. 
If that does not work then:
1. Compile and run the C++ implementation:
   ```
   g++ main.cpp -o graph_bfs
   ./graph_bfs
   ```
2. Comment out lines 6 and 7 of plot.py and run the visualization:
   ```
   python plot.py
   ```
Note: Running in Anaconda Prompt ensures all required Python libraries are available.

## Features
- BFS implementation for both sparse and dense graphs
- Performance testing with multiple input sizes
- Memory usage analysis:
    - Static space is measured (graph structure memory)
    - Peak memory is tracked during the BFS traversal
- Graphic Visualization of time complexity:
    - Sparse Graph: Each node only connects to adjacent nodes to create a linked-list-like structure
    - Dense Graph: Each node connects to k others to create an interconnected structure
- CSV output for result analysis using pandas and matplotlib

## Output
- The program tests BFS on different graph sizes
- Each size is tested multiple times to get average time and peak memory measurements
- Results are saved to two CSV files:
    - sparse_bfs_results.csv: Results for sparse graph tests
    - dense_bfs_results.csv: Results for dense graph tests
- Each CSV includes:
    - Graph size
    - Average execution time
    - Static space usage
    - Peak memory usage during BFS
- Python script creates graphs that show:
    - Time complexity growth
    - Performance comparison between sparse and dense graphs

## Authors
Anthony Franzino and Santiago Roa

