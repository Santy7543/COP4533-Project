import subprocess
import matplotlib.pyplot as plt
import pandas as pd

# compile and run C++ program
subprocess.run(["g++", "-o", "bfs_test", "main.cpp"])
subprocess.run(["./bfs_test"])


sparse_df = pd.read_csv("sparse_bfs_results.csv")
sparse_inputSize = sparse_df["Size"].tolist()
sparse_time = sparse_df["Time(ms)"].tolist()
sparse_space = sparse_df["Space(bytes)"].tolist()

dense_df = pd.read_csv("dense_bfs_results.csv")
dense_inputSize = dense_df["Size"].tolist()
dense_time = dense_df["Time(ms)"].tolist()
dense_space = dense_df["Space(bytes)"].tolist()

# print("Input Size:", inputSize)
# print("Time:", time)
# print("Space:", space)

plt.plot(sparse_inputSize, sparse_time, label="Sparse Graph", marker='o', color='blue')
plt.plot(dense_inputSize, dense_time, label="Dense Graph", marker='o', color='red')
plt.legend()
plt.xlabel("Number of Vertices")
plt.xticks(sparse_inputSize + dense_inputSize)
plt.ylabel("Time (ms)")
plt.title("BFS Performance")
plt.grid(True)
plt.show()
