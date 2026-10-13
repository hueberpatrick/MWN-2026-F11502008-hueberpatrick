import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# Project directories
BASE = Path(__file__).resolve().parent.parent
RESULTS = BASE / "results"

# Load actual ns-3 simulation data
df = pd.read_csv(RESULTS / "ntn-traffic.csv")

sizes = df["size_bytes"].to_numpy()

# The first entry is the simulation start, not an inter-arrival time.
intervals = df["interarrival_ms"].to_numpy()[1:]

# --------------------------------------------------
# 1. Packet Size PDF (discrete probability mass)
# --------------------------------------------------
values, counts = np.unique(sizes, return_counts=True)
probabilities = counts / counts.sum()

plt.figure(figsize=(7, 4))
plt.bar(values.astype(str), probabilities)
plt.xlabel("Packet Size [Bytes]")
plt.ylabel("Relative Frequency")
plt.title("Packet Size – Empirical PDF")
plt.grid(axis="y", alpha=0.3)
plt.tight_layout()
plt.savefig(RESULTS / "packet_size_pdf.png", dpi=200)
plt.close()

# --------------------------------------------------
# 2. Packet Size CDF
# --------------------------------------------------
sorted_sizes = np.sort(sizes)
cdf_sizes = np.arange(1, len(sorted_sizes) + 1) / len(sorted_sizes)

plt.figure(figsize=(7, 4))
plt.step(sorted_sizes, cdf_sizes, where="post")
plt.xlabel("Packet Size [Bytes]")
plt.ylabel("Cumulative Probability")
plt.title("Packet Size – Empirical CDF")
plt.ylim(0, 1.05)
plt.grid(alpha=0.3)
plt.tight_layout()
plt.savefig(RESULTS / "packet_size_cdf.png", dpi=200)
plt.close()

# --------------------------------------------------
# 3. Inter-Arrival Time PDF (density histogram)
# --------------------------------------------------
plt.figure(figsize=(7, 4))
plt.hist(intervals, bins=15, density=True, edgecolor="black", alpha=0.75)
plt.xlabel("Inter-Arrival Time [ms]")
plt.ylabel("Probability Density [1/ms]")
plt.title("Inter-Arrival Time – Empirical PDF")
plt.grid(axis="y", alpha=0.3)
plt.tight_layout()
plt.savefig(RESULTS / "interarrival_pdf.png", dpi=200)
plt.close()

# --------------------------------------------------
# 4. Inter-Arrival Time CDF
# --------------------------------------------------
sorted_intervals = np.sort(intervals)
cdf_intervals = np.arange(1, len(sorted_intervals) + 1) / len(sorted_intervals)

plt.figure(figsize=(7, 4))
plt.step(sorted_intervals, cdf_intervals, where="post")
plt.xlabel("Inter-Arrival Time [ms]")
plt.ylabel("Cumulative Probability")
plt.title("Inter-Arrival Time – Empirical CDF")
plt.ylim(0, 1.05)
plt.grid(alpha=0.3)
plt.tight_layout()
plt.savefig(RESULTS / "interarrival_cdf.png", dpi=200)
plt.close()

# Summary
print("Traffic analysis completed successfully.")
print(f"Packets analyzed: {len(sizes)}")
print(f"Mean packet size: {np.mean(sizes):.2f} bytes")
print(f"Mean inter-arrival time: {np.mean(intervals):.2f} ms")
print("Four diagrams saved in:", RESULTS)
