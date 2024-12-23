import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

class Day4 {

    public static void main(String[] args) {

    }

    public static int countDistinctIslands(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;

        HashSet<String> set = new HashSet<>();
        boolean[][] visited = new boolean[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    bfs(grid, i, j, set, visited);
                }
            }
        }

        return set.size();
    }

    public static void bfs(int[][] grid, int i, int j, HashSet<String> set, boolean[][] visited) {
        int rows = grid.length;
        int cols = grid[0].length;

        StringBuilder sb = new StringBuilder();
        sb.append(i - i).append(j - j);

        Queue<int[]> que = new LinkedList<>();
        que.add(new int[] { i, j });
        visited[i][j] = true;

        int[] dirX = { 0, 1, 0, -1 };
        int[] dirY = { 1, 0, -1, 0 };

        while (!que.isEmpty()) {
            int[] arr = que.poll();
            int r = arr[0];
            int c = arr[1];

            for (int k = 0; k < 4; ++k) {
                int newX = r + dirX[k];
                int newY = c + dirY[k];

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY]
                        && grid[newX][newY] == 1) {
                    que.add(new int[] { newX, newY });
                    visited[newX][newY] = true;
                    sb.append(i - newX).append(j - newY);

                }
            }
        }

        set.add(sb.toString());

    }

    // Detect a cycle in an undirected graph

    public static boolean isCycle(int v, List<Integer>[] adj) {

        boolean[] visited = new boolean[v];
        for (int i = 0; i < v; ++i) {
            if (!visited[i]) {

                // using bfs

                // if (isCycleBfs(i, adj, visited)) {
                // return true;
                // }

                // using dfs
                if (isCycleDfs(i, -1, adj, visited)) {
                    return true;
                }
            }
        }

        return false;

    }

    public static boolean isCycleBfs(int i, List<Integer>[] adj, boolean[] visited) {
        Queue<int[]> que = new LinkedList<>();
        que.add(new int[] { i, -1 });
        visited[i] = true;

        while (!que.isEmpty()) {
            int[] arr = que.poll();
            int node = arr[0];
            int parent = arr[1];

            for (Integer child : adj[node]) {
                if (child == parent) {
                    continue;
                }
                if (visited[child]) {
                    return true;
                }
                que.add(new int[] { child, node });
                visited[child] = true;
            }
        }

        return false;
    }

    public static boolean isCycleDfs(int node, int parent, List<Integer>[] adj, boolean[] visited) {

        visited[node] = true;
        for (Integer child : adj[node]) {
            if (child == parent) {
                continue;
            }
            if (visited[child] || isCycleDfs(child, node, adj, visited)) {
                return true;
            }

        }

        return false;

    }

}
