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
    public static char[][] fill(char[][] matrix) {
        int row = matrix.length;
        int col = matrix[0].length;

        char[][] ans = new char[row][col];

        // We will perform bfs
        boolean[][] visited = new boolean[row][col];
        Queue<int[]> que = new LinkedList<>();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if ((i == 0 || i == row - 1 || j == 0 || j == col - 1) && matrix[i][j] == 'O') {
                    que.add(new int[] { i, j });
                    visited[i][j] = true;
                }

            }
        }

        int[] x = { -1, 0, 1, 0 };
        int[] y = { 0, 1, 0, -1 };

        // mark all zeros that can be visited from zeros added to question

        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                int[] arr = que.poll();
                int r = arr[0], c = arr[1];
                for (int i = 0; i < 4; i++) {
                    int newR = r + x[i], newC = c + y[i];
                    if (newR >= 0 && newR < row && newC >= 0 && newC < col && !visited[newR][newC]
                            && matrix[newR][newC] == 'O') {
                        visited[newR][newC] = true;
                        que.add(new int[] { newR, newC });
                    }
                }
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (matrix[i][j] == 'X' || !visited[i][j]) {
                    ans[i][j] = 'X';
                } else {
                    ans[i][j] = 'O';
                }
            }
        }

        return ans;

    }

    // Number of distinct islands
    public static int countDistinctIslands(int[][] grid) {
        return 0;
    }

}
