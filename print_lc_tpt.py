import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_lc = pd.read_csv("./LCtpt.csv")

totalNumLc = 4
filtered_data_lc = [None] * totalNumLc
for i in range(0, totalNumLc, 1):
    filtered_data_lc[i] = data_lc[(data_lc["time"] > 32) & (data_lc["drb"] == i+1)]

x_values_lc = [[] for _ in range(totalNumLc)]
y_values_lc = [[] for _ in range(totalNumLc)]

for i in range(0, totalNumLc, 1):
    x_values_lc[i] = (filtered_data_lc[i]["time"] - 32)
    y_values_lc[i] = filtered_data_lc[i]["tpt"]

fig, ax = plt.subplots()
plt.xlim(0, 30)
plt.ylim(0, 100)

for i in range(0, totalNumLc, 1):
    label = f"LC Index {i}"
    ax.plot(x_values_lc[i], y_values_lc[i], label=label)

ax.legend()
ax.set(xlabel="Time (sec)", ylabel="Throughput (kbps)",title="Throughput of each logical")
ax.grid()

plt.show()

