# The Maze Runner: Autonomous Robot Simulation

A terminal-based C++ simulation that generates random mazes and visualizes two classic pathfinding algorithms: *Depth First Search (DFS)* and *Breadth First Search (BFS)*.

## 🚀 Features

* *Random Maze Generation:* Uses Recursive Backtracking to create unique 21x21 mazes every time you run it.
* *Real-time Visualization:* Watch the robot explore the maze step-by-step using ANSI colors and console animations.
* *Cross-Platform:* Runs on both Windows and Linux/macOS.
* *Performance Metrics:* Compares the efficiency (steps taken) of DFS vs. BFS at the end of the simulation.

## 🧠 Algorithms Implemented



### 1. Depth First Search (DFS)
* *Behavior:* The "Brave but Blind" approach. It rushes deep into a path until it hits a wall, then backtracks to find a new route.
* *Pros:* Memory efficient.
* *Cons:* Does not guarantee the shortest path.

### 2. Breadth First Search (BFS)
* *Behavior:* The "Flood Fill" approach. It explores the maze layer-by-layer, expanding equally in all directions.
* *Pros:* *Guaranteed* to find the shortest possible path from Start to End.
* *Cons:* Uses more memory to store the frontier of exploration.

## 🛠 Tech Stack
* *Language:* C++ (Standard 11+)
* *Libraries:* iostream, vector, queue, thread
* *Visuals:* ANSI Escape Codes for colored terminal output.

## 💻 How to Run

### 1. Compile
Open your terminal/command prompt and run:

```bash
g++ -o maze main.cpp
