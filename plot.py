import subprocess
import matplotlib.pyplot as plt
import pandas as pd

# compile and run C++ program
subprocess.run(["g++", "-o", "graph_bfs", "main.cpp"])
subprocess.run(["./graph_bfs"])

sparse_df = pd.read_csv("sparse_bfs_results.csv")
sparse_inputSize = sparse_df["Size"]
sparse_time = sparse_df["Time(ms)"].tolist()
sparse_static_size = sparse_df["Static_Space(bytes)"].tolist()
sparse_peak_mem = sparse_df["Peak_Memory(bytes)"].tolist()

dense_df = pd.read_csv("dense_bfs_results.csv")
dense_inputSize = dense_df["Size"]
dense_time = dense_df["Time(ms)"].tolist()
dense_static_size = dense_df["Static_Space(bytes)"].tolist()
dense_peak_mem = dense_df["Peak_Memory(bytes)"].tolist()

fig, axes = plt.subplots(1, 3, figsize=(18, 5))

axes[0].plot(sparse_inputSize, sparse_time, label="Sparse Graph", marker='o', color='blue')
axes[0].plot(dense_inputSize, dense_time, label="Dense Graph", marker='o', color='red')
axes[0].legend()
axes[0].set_xlabel("Number of Vertices")
axes[0].set_xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
axes[0].set_ylabel("Time (ms)")
axes[0].set_title("BFS Runtime Performance")
axes[0].grid(True)

axes[1].plot(sparse_inputSize, sparse_static_size, label="Sparse Graph", marker='o', color='blue')
axes[1].plot(dense_inputSize, dense_static_size, label="Dense Graph", marker='o', color='red')
axes[1].legend()
axes[1].set_xlabel("Number of Vertices")
axes[1].set_xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
axes[1].set_ylabel("Static Memory Usage (1e7 bytes)")
axes[1].set_title("Static Graph Memory Usage (Adjacency List Size)")
axes[1].grid(True)

axes[2].bar(sparse_inputSize - 100, sparse_peak_mem, width=200, label='Sparse Graph', color='skyblue', align='center')
axes[2].bar(dense_inputSize + 100, dense_peak_mem, width=200, label='Dense Graph', color='salmon', align='center')
axes[2].set_xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
axes[2].set_xlabel("Number of Vertices")
axes[2].set_ylabel("Byte Memory Usage During BFS (bytes)")
axes[2].set_title("Peak Memory Usage During BFS")
axes[2].legend()
axes[2].grid(True)

fig.suptitle("BFS Performance Comparison")
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()

# plt.figure(figsize=(10, 6))
# plt.plot(sparse_inputSize, sparse_time, label="Sparse Graph", marker='o', color='blue')
# plt.plot(dense_inputSize, dense_time, label="Dense Graph", marker='o', color='red')
# plt.legend()
# plt.xlabel("Number of Vertices")
# plt.xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
# plt.ylabel("Time (ms)")
# plt.title("BFS Runtime Performance")
# plt.grid(True)
# plt.tight_layout()
# plt.show()

# plt.figure(figsize=(10, 6))
# plt.plot(sparse_inputSize, sparse_static_size, label="Sparse Graph", marker='o', color='blue')
# plt.plot(dense_inputSize, dense_static_size, label="Dense Graph", marker='o', color='red')
# plt.legend()
# plt.xlabel("Number of Vertices")
# plt.xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
# plt.ylabel("Static Memory Usage (1e7 bytes)")
# plt.title("Static Graph Memory Usage (Adjacency List Size)")
# plt.grid(True)
# plt.tight_layout()
# plt.show()

# plt.figure(figsize=(10, 6))
# plt.bar(sparse_inputSize - 100, sparse_peak_mem, width=200, label='Sparse Graph', color='skyblue', align='center')
# plt.bar(dense_inputSize + 100, dense_peak_mem, width=200, label='Dense Graph', color='salmon', align='center')
# plt.xticks(sparse_inputSize.tolist() + dense_inputSize.tolist())
# plt.xlabel("Number of Vertices")
# plt.ylabel("Peak Memory Usage During BFS (1e7 bytes)")
# plt.title("Peak BFS Memory Usage")
# plt.legend()
# plt.grid(True)
# plt.tight_layout()
# plt.show()