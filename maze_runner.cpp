#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

void sleep_ms(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

const int ROWS = 21;
const int COLS = 21;

const char WALL = '#';
const char PATH = ' ';
const char START = 'S';
const char END = 'E';
const char ROBOT = 'R';
const char VISITED = '.';
const char SOLUTION = '*';

char maze[ROWS][COLS];
char originalMaze[ROWS][COLS];

int dfs_steps = 0;
int bfs_steps = 0;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

using namespace std;

void resetMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = originalMaze[i][j];
        }
    }
}

void printMaze(string algorithmName) {
    system(CLEAR_SCREEN);
    cout << "=== " << algorithmName << " SIMULATION ===\n";
    cout << "Finding path from Top-Left to Bottom-Right...\n\n";

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == WALL)      cout << "\033[37m" << char(219) << " \033[0m";
            else if (maze[i][j] == ROBOT) cout << "\033[31m" << 'R' << " \033[0m";
            else if (maze[i][j] == SOLUTION) cout << "\033[32m" << '.' << " \033[0m";
            else if (maze[i][j] == START) cout << "\033[33m" << 'S' << " \033[0m";
            else if (maze[i][j] == END)   cout << "\033[33m" << 'E' << " \033[0m";
            else cout << maze[i][j] << " ";
        }
        cout << "\n";
    }
    sleep_ms(50);
}

void generateMazeRecursive(int x, int y) {
    maze[x][y] = PATH;

    int dirs[] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        swap(dirs[i], dirs[r]);
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]] * 2;
        int ny = y + dy[dirs[i]] * 2;

        if (nx > 0 && nx < ROWS - 1 && ny > 0 && ny < COLS - 1 && maze[nx][ny] == WALL) {
            maze[x + dx[dirs[i]]][y + dy[dirs[i]]] = PATH;
            generateMazeRecursive(nx, ny);
        }
    }
}

void initializeMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j] = WALL;
        }
    }

    generateMazeRecursive(1, 1);

    maze[1][1] = START;
    maze[ROWS - 2][COLS - 2] = END;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            originalMaze[i][j] = maze[i][j];
        }
    }
}

bool solveDFS(int x, int y) {
    if (maze[x][y] == END) return true;

    if (maze[x][y] != START) maze[x][y] = ROBOT;
    printMaze("DFS (Backtracking)");
    dfs_steps++;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (maze[nx][ny] == PATH || maze[nx][ny] == END) {
            if (solveDFS(nx, ny)) {
                if (maze[x][y] != START) maze[x][y] = SOLUTION;
                return true;
            }
        }
    }

    if (maze[x][y] != START) maze[x][y] = VISITED;
    printMaze("DFS (Backtracking)");
    return false;
}

struct Node {
    int x, y;
};

void solveBFS() {
    bfs_steps = 0;
    
    queue<Node> q;
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

    q.push({1, 1});
    visited[1][1] = true;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (maze[current.x][current.y] != START && maze[current.x][current.y] != END) {
            maze[current.x][current.y] = VISITED;
        }

        bfs_steps++;
        if (bfs_steps % 5 == 0) printMaze("BFS (Shortest Path)");

        if (current.x == ROWS - 2 && current.y == COLS - 2) {
            cout << "\nTarget Reached via BFS!\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (maze[nx][ny] != WALL && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    srand(time(NULL));

    cout << "Generating Random Maze...\n";
    initializeMaze();

    cout << "Press ENTER to start DFS (Backtracking) Robot...";
    cin.get();
    
    if (!solveDFS(1, 1)) cout << "\nNo path found using DFS!\n";
    else cout << "\nDFS Path Found! Total Steps: " << dfs_steps << endl;

    sleep_ms(2000);

    resetMaze();
    cout << "\nPress ENTER to start BFS (Shortest Path) Robot...";
    cin.get();
    
    solveBFS();
    cout << "\nBFS Search Complete! Nodes Visited: " << bfs_steps << endl;

    sleep_ms(1000);
    system(CLEAR_SCREEN);

    cout << "==========================================\n";
    cout << "       ALGORITHM PERFORMANCE REPORT       \n";
    cout << "==========================================\n";
    cout << "Maze Size: " << ROWS << "x" << COLS << "\n\n";
    
    cout << "1. DFS (Backtracking):\n";
    cout << "   - Steps Taken: " << dfs_steps << "\n";
    cout << "   - Logic: Depth-first. Risky but memory efficient.\n\n";

    cout << "2. BFS (Breadth First Search):\n";
    cout << "   - Steps Taken: " << bfs_steps << "\n";
    cout << "   - Logic: Breadth-first. Guarantees shortest path.\n";
    cout << "==========================================\n";

    return 0;
}