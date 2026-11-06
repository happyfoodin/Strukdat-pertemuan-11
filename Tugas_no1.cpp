#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;

    public:
        Graph (int banyakTitik) {
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
        }

        bool addEdge(int i, int j) {
            if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
                adjMatrix[i][j] = 1;
                adjMatrix[j][i] = 1;
                return true;
            }
            return false;
        }

        void bfs(int startVertex) {
            vector<bool> visited(numberVertex, false);
            queue<int> titikVisit;

            visited[startVertex] = true;
            titikVisit.push(startVertex);

            while (!titikVisit.empty()) {
                int currentVertex = titikVisit.front();
                titikVisit.pop();
                cout << char('A' + currentVertex) << " ";

                for (int i = 0; i < numberVertex; i++) {
                    if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                        visited[i] = true;
                        titikVisit.push(i);
                    }
                }
            }
            cout << endl;
        }
};

int main() {
    system("cls");
    Graph graphh(6);

    int jumlahEdge;
    cout << "Jumlah edge : ";
    cin >> jumlahEdge;

    cout << "Masukkan edge (contoh: A B)" << endl;
    for (int i = 0; i < jumlahEdge; i++) {
        char a, b;
        cout << "Edge " << i + 1 << " : ";
        cin >> a >> b;
        a = toupper(a);
        b = toupper(b);

        if (!graphh.addEdge(a - 'A', b - 'A')) {
            cout << "Vertex Invalid, hanya A-F" << endl;
            i--;
        }
    }

    char start;
    cout << "Vertex awal : ";
    cin >> start;
    start = toupper(start);

    if (start < 'A' || start > 'F') {
        cout << "Vertex awal nonvalid" << endl;
        return 0;
    }

    cout << "Urutan BFS : ";
    graphh.bfs(start - 'A');

    return 0;
}