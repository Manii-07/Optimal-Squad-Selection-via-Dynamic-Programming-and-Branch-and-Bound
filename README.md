# Optimal Squad Selection via Dynamic Programming and Branch-and-Bound

## Overview

This project is a C++-based optimization system designed to build the best possible football squad under a fixed budget constraint. The project compares two advanced algorithmic techniques:

- Dynamic Programming (DP)
- Branch-and-Bound (B&B)

The system selects exactly 11 players from a dataset while maximizing the total squad rating without exceeding the given budget.

This project demonstrates practical applications of:
- Optimization algorithms
- Search-space pruning
- Knapsack Problem
- Algorithm performance comparison
- Sorting algorithms

---

# Objectives

The main objectives of this project are:

- Build an optimal football squad under budget constraints
- Compare Dynamic Programming and Branch-and-Bound approaches
- Analyze execution efficiency and optimization quality
- Demonstrate real-world applications of algorithm design techniques

---

# Features

✅ Reads player data from CSV files  
✅ Selects exactly 11 players  
✅ Maximizes total squad rating  
✅ Maintains budget constraints  
✅ Uses Dynamic Programming optimization  
✅ Uses Branch-and-Bound optimization  
✅ Sorts output using Merge Sort  
✅ Displays execution time for both algorithms  
✅ Compares algorithm performance  

---

# Algorithms Used

## 1. Dynamic Programming (DP)

The Dynamic Programming solution is based on the classical **0/1 Knapsack Problem** with an additional constraint requiring exactly 11 players.

### Working Principle
- Evaluates all possible combinations
- Stores intermediate results
- Prevents repeated computations
- Guarantees an optimal solution

### Complexity
- Time Complexity: `O(n × budget × k)`
- Space Complexity: `O(n × budget × k)`

Where:
- `n` = number of players
- `budget` = maximum allowed budget
- `k` = squad size (11)

---

## 2. Branch-and-Bound (B&B)

Branch-and-Bound is an optimization technique that reduces unnecessary computations using upper-bound estimation.

### Working Principle
- Explores promising states first
- Calculates upper bounds
- Prunes non-optimal branches
- Improves search efficiency

### Complexity
- Worst Case: Exponential
- Practical Performance: Faster due to pruning

---

## 3. Merge Sort

Merge Sort is used to sort the final selected squad according to player ratings.

### Complexity
- Time Complexity: `O(n log n)`
- Space Complexity: `O(n)`

---

# Technologies Used

- C++
- STL (Standard Template Library)
- File Handling
- CSV Parsing
- Queue Data Structure
- Sorting Algorithms
- Optimization Techniques

---

# Project Structure

```bash
optimal-squad-selection-dp-branch-bound/
│
├── src/
│   └── main.cpp
│
├── data/
│   └── players.csv
│
├── docs/
│   └── report.pdf
│
├── screenshots/
│   └── output.png
│
├── README.md
├── LICENSE
└── .gitignore
```

---

# Input Dataset Format

The dataset file `players.csv` should follow this structure:

```csv
name,position,cost,rating
Messi,Forward,120,95
Ronaldo,Forward,115,93
Mbappe,Forward,110,92
De Bruyne,Midfielder,100,91
```

---

# How the System Works

## Step 1 — Load Dataset
The program reads player information from `players.csv`.

## Step 2 — Enter Budget
The user enters the maximum squad budget.

Example:
```txt
Enter Budget: 1000
```

## Step 3 — Run Dynamic Programming
The system calculates the optimal squad using DP.

## Step 4 — Run Branch-and-Bound
The system calculates the optimal squad using B&B.

## Step 5 — Compare Results
The program displays:
- Best squad
- Total rating
- Total cost
- Execution time

---

# Compilation and Execution

## Compile

```bash
g++ src/main.cpp -o squad
```

## Run

### Windows
```bash
squad.exe
```

### Linux / Mac
```bash
./squad
```

---

# Sample Output

```txt
Enter Budget: 1000

==============================
DYNAMIC PROGRAMMING RESULT
==============================
Maximum Rating: 945

Messi | Forward | Cost: 120 | Rating: 95
Mbappe | Forward | Cost: 110 | Rating: 92

Total Cost: 995 / 1000
Execution Time: 0.012 seconds

==============================
BRANCH AND BOUND RESULT
==============================
Maximum Rating: 945

Messi | Forward | Cost: 120 | Rating: 95
Mbappe | Forward | Cost: 110 | Rating: 92

Total Cost: 995 / 1000
Execution Time: 0.004 seconds
```

---

# Comparison Between Algorithms

| Feature | Dynamic Programming | Branch-and-Bound |
|---|---|---|
| Guarantees Optimal Solution | Yes | Yes |
| Memory Usage | High | Lower |
| Speed | Slower for large datasets | Faster due to pruning |
| Technique | Table-based optimization | State-space search |
| Complexity | Polynomial | Exponential (Pruned) |

---

# Real-World Applications

This project can be applied in:

- Fantasy Football Systems
- Sports Team Management
- Resource Allocation Problems
- Budget Optimization
- Decision Support Systems
- AI-based Squad Recommendation Systems

---

# Learning Outcomes

Through this project, the following concepts were implemented and analyzed:

- Dynamic Programming
- Branch-and-Bound
- Merge Sort
- Knapsack Optimization
- File Handling in C++
- Time Complexity Analysis
- Space Complexity Analysis
- Algorithm Performance Comparison

---

# Future Improvements

The project can be enhanced further by adding:

- Graphical User Interface (GUI)
- Position Constraints (GK, DEF, MID, FWD)
- Real football API integration
- Genetic Algorithm implementation
- Web-based dashboard
- Machine Learning recommendation system
- Multi-objective optimization

---

# Why This Project Is Important

This project demonstrates how advanced algorithms can solve real-world optimization problems efficiently. It highlights the importance of:
- Computational efficiency
- Search optimization
- Data-driven decision making
- Algorithmic problem solving

It also provides practical understanding of how optimization techniques are used in modern sports analytics systems.

---

# Author

## Usman Akram

C++ Developer | Algorithm Enthusiast | AI & Optimization Learner

---

# License

This project is licensed under the MIT License.

---

# GitHub Repository Topics

```txt
cpp
dynamic-programming
branch-and-bound
algorithms
data-structures
optimization
football
knapsack-problem
sports-analytics
merge-sort
```
