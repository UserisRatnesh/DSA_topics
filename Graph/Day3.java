import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Day3
 */
public class Day3 {

    public static void main(String[] args) {

        int[][] grid = { { 0, 1, 1, 0 }, { 1, 1, 0, 0 }, { 0, 0, 1, 1 } };
        int[][] ans = nearest(grid);
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                System.out.print(ans[i][j] + " ");
            }

            System.out.println();
        }

    }

    // Distance of nearest cell having one
    // distance = |i1-i2| + |j1-j2|
    // Why dfs is not working for this question

    // I don't know why but this one is not getting accepted
    public static int[][] nearest(int[][] grid) {
        int row = grid.length;
        int col = grid[0].length;

        int[][] ans = new int[row][col];
        for (int i = 0; i < row; i++) {
            Arrays.fill(ans[i], 0);

        }

        boolean[][] visited = new boolean[row][col];
        Queue<int[]> que = new LinkedList<>();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == 1) {
                    que.add(new int[] { i, j, 0 });
                    visited[i][j] = true;
                } else {
                    visited[i][j] = false;
                }
            }
        }

        int[] x = { -1, 0, 1, 0 };
        int[] y = { 0, 1, 0, -1 };

        // Now perform bfs

        while (!que.isEmpty()) {

            int[] arr = que.poll();
            int r = arr[0], c = arr[1];
            int dist = arr[2];
            ans[r][c] = dist;
            for (int i = 0; i < 4; i++) {
                int newR = r + x[i], newC = c + y[i];
                if (newR >= 0 && newR < row && newC >= 0 && newC < col && !visited[newR][newC]) {
                    que.add(new int[] { newR, newC, dist + 1 });
                    visited[newR][newC] = true;
                }
            }
        }

        return ans;
    }

    // Surrounded regions
    // Done using BFS on the O tha is at boundary.
    // Can be done using DFS also.
    public char[][] fillSurroundedRegion(char[][] mat) {

        int rows = mat.length;
        int cols = mat[0].length;

        // make deep copy of mat
        char[][] ans = new char[rows][cols];
        for (int i = 0; i < rows; i++) {
            ans[i] = Arrays.copyOf(mat[i], mat[i].length);
        }

        // Jitne bhi boundary pe O hai unpe four directionally
        // iterate karke mark karlo, wo kabhi bhi X nahi ban sakte
        Queue<int[]> que = new LinkedList<>();
        boolean visited[][] = new boolean[rows][cols];

        // first and last row me O ko mark karo
        for (int j = 0; j < cols; ++j) {
            if (ans[0][j] == 'O') {
                visited[0][j] = true;
                que.add(new int[] { 0, j });
            }
            if (ans[rows - 1][j] == 'O') {
                visited[rows - 1][j] = true;
                que.add(new int[] { rows - 1, j });
            }
        }

        // first and last col me O ko mark karo
        for (int i = 0; i < rows; ++i) {
            if (ans[i][0] == 'O') {
                visited[i][0] = true;
                que.add(new int[] { i, 0 });
            }
            if (ans[i][cols - 1] == 'O') {
                visited[i][cols - 1] = true;
                que.add(new int[] { i, cols - 1 });
            }
        }

        // Now perform bfs on que data
        bfs(ans, que, visited);

        // now convert all non visited O to X
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!visited[i][j]) {
                    ans[i][j] = 'X';
                }
            }
        }

        return ans;

    }

    public void bfs(char[][] ans, Queue<int[]> que, boolean[][] visited) {
        int rows = ans.length;
        int cols = ans[0].length;
        int[] dirX = { -1, 0, 1, 0 };
        int[] dirY = { 0, 1, 0, -1 };
        while (!que.isEmpty()) {
            int[] arr = que.poll();
            int x = arr[0];
            int y = arr[1];
            for (int i = 0; i < 4; i++) {
                int newX = x + dirX[i];
                int newY = y + dirY[i];
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY]
                        && ans[newX][newY] == 'O') {
                    visited[newX][newY] = true;
                    que.add(new int[] { newX, newY });
                }
            }
        }
    }

    // Number of distinct islands
    public static int countDistinctIslands(int[][] grid) {
        return 0;
    }

}
