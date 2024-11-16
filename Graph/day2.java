
// Date : 13/11/2024

// Date : 14/11/2024
// Date : 15/11/2024
// These two days were skipped because i was having fever

import java.util.LinkedList;
import java.util.Queue;

public class day2 {
    public static void main(String[] args) {

    }

    // Find number of enclaves
    public static int numberOfEnclave(int[][] grid) {
        int row = grid.length;
        int col = grid[0].length;

        // Perform dfs or bfs on each boundary land cell
        // because it can lead to walking off out of cell
        boolean[][] visited = new boolean[row][col];

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if ((i == 0 || i == row - 1 || j == 0 || j == col - 1) && !visited[i][j] && grid[i][j] == 1) {
                    dfs(grid, i, j, visited);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    ans++;
                }
            }
        }

        return ans;
    }

    public static void dfs(int[][] grid, int sr, int sc, boolean[][] visited) {
        visited[sr][sc] = true;

        int[] x = { -1, 0, 1, 0 };
        int[] y = { 0, 1, 0, -1 };
        for (int i = 0; i < 4; i++) {
            int newRow = sr + x[i];
            int newCol = sc + y[i];
            if (newRow >= 0 && newRow < grid.length && newCol >= 0 && newCol < grid[0].length
                    && !visited[newRow][newCol] && grid[newRow][newCol] == 1) {
                dfs(grid, newRow, newCol, visited);
            }
        }
    }

    // Rotten oranges
    // We will perform bfs
    public static int orangeRotting(int[][] grid) {
        int row = grid.length;
        int col = grid[0].length;

        int fresh = 0;
        boolean[][] visited = new boolean[row][col];
        Queue<Pair> que = new LinkedList<>();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 1)
                    fresh++;
                if (grid[i][j] == 2) {
                    // it is rotten so add in que
                    que.add(new Pair(i, j));
                    visited[i][j] = true;
                }
            }
        }

        int[] x = { -1, 0, 1, 0 };
        int[] y = { 0, 1, 0, -1 };

        // Now perform bfs
        int mins = 0;
        while (!que.isEmpty()) {
            int size = que.size();
            mins++;
            while (size-- > 0) {
                Pair p = que.poll();
                int r = p.first;
                int c = p.second;
                for (int i = 0; i < 4; i++) {
                    int newRow = r + x[i];
                    int newCol = c + y[i];
                    if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col && grid[newRow][newCol] == 1
                            && !visited[newRow][newCol]) {
                        visited[newRow][newCol] = true;
                        fresh--;
                        que.add(new Pair(newRow, newCol));
                    }
                }

            }
        }

        if (fresh == 0) {
            // -1 because above we are adding time to rott the first set of rotten oranges
            return mins - 1;
        }
        return -1;

    }

}

class Pair {
    int first;
    int second;

    public Pair(int first, int second) {
        this.first = first;
        this.second = second;
    }
}
