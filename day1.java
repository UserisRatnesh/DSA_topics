import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class day1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<List<Integer>> adjList = createGraph(sc);

        int n = adjList.size();

        boolean[] visited = new boolean[n];
        Arrays.fill(visited, false);
        for (int i = 1; i < n; i++) {
            if (!visited[i]) {
                bfs(adjList, i, visited);
            }
        }

    }

    // Bfs
    // We are using visited to keep multiple components in check
    public static void bfs(List<List<Integer>> adjList, int startNode, boolean[] visited) {

        Queue<Integer> que = new LinkedList<>();
        que.add(startNode);
        visited[startNode] = true;
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                int node = que.poll();

                System.out.print(node + " ");
                for (Integer child : adjList.get(node)) {
                    if (!visited[child]) {
                        que.add(child);
                        visited[child] = true;
                    }
                }
            }
        }
        return;
    }

    // Create adjList for undirected and unweighted graph
    public static List<List<Integer>> createGraph(Scanner sc) {
        int n = sc.nextInt();
        int e = sc.nextInt();
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<>());
        }

        for (int i = 0; i < e; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            adjList.get(u).add(v);
            adjList.get(v).add(u);
        }

        return adjList;

    }

    // Create adjList for directed and weighted graph
    public static List<List<Pair>> createWeightedGraph(Scanner sc) {
        int n = sc.nextInt();
        int e = sc.nextInt();
        List<List<Pair>> adjList = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<>());
        }

        for (int i = 0; i < e; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int wt = sc.nextInt();
            Pair p = new Pair(v, wt);
            adjList.get(u).add(p);
        }

        return adjList;

    }

    // Dfs traversal for multiple component graph
    public List<Integer> dfsOfGraph(int V, List<Integer> adj[]) {
        boolean[] visited = new boolean[V];
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, adj, list, visited);
            }
        }

        return list;

    }

    public void dfs(int node, List<Integer> adj[], List<Integer> list, boolean[] visited) {

        visited[node] = true;
        list.add(node);
        for (Integer child : adj[node]) {
            if (!visited[child]) {
                dfs(child, adj, list, visited);
            }
        }

    }

    // Bfs traversal for multiple component graph
    public List<Integer> bfsOfGraph(int V, List<Integer> adj[]) {

        List<Integer> list = new ArrayList<>();
        boolean[] visited = new boolean[V];

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                bfs(i, visited, adj, list);
            }
        }

        return list;
    }

    public void bfs(int node, boolean[] visited, List<Integer> adj[], List<Integer> list) {

        Queue<Integer> que = new LinkedList<>();
        que.add(node);
        visited[node] = true;
        while (!que.isEmpty()) {
            int size = que.size();
            while (size-- > 0) {
                int u = que.poll();
                list.add(u);
                for (Integer child : adj[u]) {
                    if (!visited[child]) {
                        que.add(child);
                        visited[child] = true;
                    }
                }
            }
        }
    }

    // Finding number of islands
    public int numIslands(char[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int ans = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    ans++;
                    dfs(i, j, grid, visited);
                }
            }
        }

        return ans;
    }

    public void dfs(int row, int col, char[][] grid, boolean[][] visited) {

        visited[row][col] = true;

        int rows = grid.length;
        int cols = grid[0].length;

        // Go to all four directions and
        // if value is 1 and not visited then call dfs again
        int[] x = { -1, -1, 0, 1, 1, 1, 0, -1 };
        int[] y = { 0, 1, 1, 1, 0, -1, -1, -1 };
        for (int i = 0; i < 8; i++) {
            int newRow = row + x[i];
            int newCol = col + y[i];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]
                    && grid[newRow][newCol] == '1') {
                dfs(newRow, newCol, grid, visited);
            }
        }
    }

    // Change color of cells having same color and connected
    public int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        boolean[][] visited = new boolean[image.length][image[0].length];
        dfs(image, sr, sc, oldColor, newColor, visited);
        return image;
    }

    public void dfs(int[][] image, int sr, int sc, int oldColor, int newColor, boolean[][] visited) {

        visited[sr][sc] = true;
        image[sr][sc] = newColor;
        int[] x = { -1, 0, 1, 0 };
        int[] y = { 0, 1, 0, -1 };
        for (int i = 0; i < 4; i++) {
            int newRow = sr + x[i];
            int newCol = sc + y[i];
            if (newRow >= 0 && newRow < image.length && newCol >= 0 && newCol < image[0].length
                    && !visited[newRow][newCol] && image[newRow][newCol] == oldColor) {
                dfs(image, newRow, newCol, oldColor, newColor, visited);
            }
        }
    }

}

// Creating a Pair class
class Pair {
    int node;
    int wt;

    public Pair(int node, int wt) {
        this.node = node;
        this.wt = wt;
    }
}
