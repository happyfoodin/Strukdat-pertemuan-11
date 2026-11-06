#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void dijkstra(int source, vector<int>& distance, vector<int>& parent) {
        vector<bool> visited(V, false);
        distance.assign(V, INT_MAX);
        parent.assign(V, -1);
        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    void printPath(int dest, vector<int>& parent) {
        if (parent[dest] == -1) {
            cout << char('A' + dest);
            return;
        }
        printPath(parent[dest], parent);
        cout << " -> " << char('A' + dest);
    }

    void showAllRoutes(int source) {
        vector<int> distance, parent;
        dijkstra(source, distance, parent);

        cout << "Rute terpendek dari lokasi " << char('A' + source) << ":" << endl;
        for (int i = 0; i < V; i++) {
            if (i == source) continue;

            cout << char('A' + source) << " ke " << char('A' + i) << " : ";
            if (distance[i] == INT_MAX) {
                cout << "Tidak terjangkau" << endl;
            } else {
                printPath(i, parent);
                cout << " (" << distance[i] << ")" << endl;
            }
        }
    }

    void recommendRoute(int source, int dest) {
        vector<int> distance, parent;
        dijkstra(source, distance, parent);

        cout << "Rekomendasi rute tercepat: ";
        if (distance[dest] == INT_MAX) {
            cout << "Tidak terjangkau" << endl;
        } else {
            printPath(dest, parent);
            cout << endl << "Total jarak : " << distance[dest] << endl;
        }
    }
};

int main() {
    system("cls");
    Graph graph(6);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 4);
    graph.addEdge(4, 5, 3);

    graph.showAllRoutes(0);

    char asal, tujuan;
    cout << endl << "Lokasi asal   (A-F) : ";
    cin >> asal;
    cout << "Lokasi tujuan (A-F) : ";
    cin >> tujuan;
    asal = toupper(asal);
    tujuan = toupper(tujuan);

    if (asal < 'A' || asal > 'F' || tujuan < 'A' || tujuan > 'F') {
        cout << "Lokasi nonvalid, hanya A-F" << endl;
        return 0;
    }

    graph.recommendRoute(asal - 'A', tujuan - 'A');

    return 0;
}