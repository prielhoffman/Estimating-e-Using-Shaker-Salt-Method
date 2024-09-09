# Estimating e Using Shaker Salt Method with OpenMP
This repository contains a parallelized program for calculating the mathematical constant e using the Monte Carlo method known as Shaker Salt. The program is designed to leverage OpenMP for parallel computations, measuring performance indicators such as running time, speedup, and efficiency across various numbers of threads.

# Overview
The program implements the Shaker Salt method, an embarrassingly parallel Monte Carlo approach for estimating e. The simulation runs independently 128 times, each with 10 oscillations (grains of sand) per run. The performance is evaluated by measuring running times for different numbers of threads and plotting results to assess acceleration and efficiency.

# Key Features
* Parallel Computation: Utilizes OpenMP to parallelize the Monte Carlo simulation for estimating e.
* Independent Runs: Performs 128 independent runs to obtain a robust estimate of e.
* Performance Metrics: Measures running time, speedup, and efficiency for 1, 2, 4, and 8 threads.
* Graphical Representation: Results are plotted to visualize running time, speedup, efficiency, and computational cost.

# How It Works
* Monte Carlo Simulation: Calculates e using the Shaker Salt method with 10 oscillations per run. Each run is independent of others.
* Parallel Execution: The program is parallelized using OpenMP to perform computations across multiple threads.
* Time Measurement: Running time is measured using wtime_get_omp for different thread counts (1, 2, 4, 8).
* Results Analysis: Results are collected, and performance metrics are calculated and presented in tables and graphs.

# Running the Program
1) Compile the Program:
gcc -fopenmp -o shaker_salt shaker_salt.c
2) Execute the Program for different numbers of threads:
OMP_NUM_THREADS=[number_of_threads] ./shaker_salt
Example for 4 threads:
OMP_NUM_THREADS=4 ./shaker_salt
3) Measurement:
The program will output running times for each configuration.
Results are saved for subsequent analysis and plotting.

# Notes
* Ensure that your environment supports OpenMP and that you have the necessary compiler flags for parallel execution.
* Be mindful of the effects of different thread counts on performance and resource utilization.
