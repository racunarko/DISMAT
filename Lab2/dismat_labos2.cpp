#include <iostream>
//#include <chrono>
//using namespace std::chrono;

using namespace std;

// povezanost grafa provjeravam algoritmom Deep-First Search

// traverse() - putuje po grafu
void traverse(int** graph, int n, int u, bool visited[]) {
    visited[u] = true;
    for(int v = 0; v < n; v++) { // v kao vertex/vertices
        if (graph[u][v] && !visited[v]) {
            traverse(graph, n, v, visited);
        }
    }
}

// isConnected() - provjerava vrhove koji su posjeceni u traverse()
bool isConnected(int** graph, int n) {
    bool *visited = new bool[n];
    for(int u = 0; u < n; u++) { // za svaki vertex u
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        traverse(graph, n, u, visited);
        for (int i = 0; i < n; i++) {
            if (!visited[i])
                return false;
        }
    }
    return true;
}


// funkcije kojima provjeravam je li ciklus hamiltonovski

// provjerava mogu li staviti vrh u path
bool isAppropriate(int** graph, int vertex, int path[], int position) {
    if(graph[path[position - 1]][vertex] == 0)
        return false;
    for (int i = 0; i < position; ++i) {
        if(path[i] == vertex)
            return false;
    }
    return true;
}

// trazi hamiltonovski put
bool hamiltonCycle(int** graph, int n, int path[], int position) {
    if (position == n) {
        if(!graph[path[position - 1]][path[0]])
            return false;
        else
            return true;
    }

    for (int v = 1; v < n; ++v) {
        if(isAppropriate(graph, v, path, position)) {
            path[position] = v;
            if(hamiltonCycle(graph, n, path, position + 1)) {
                return true;
            }
            path[position] = -1;
        }
    }
    return false;
}

// provjerava je li graf hamiltonovski
bool isHamiltonian(int** graph, int n) {
    int* path = new int[n];
    for (int i = 0; i < n; ++i) {
        path[i] = -1;
    }
    path[0] = 0;
    if(hamiltonCycle(graph, n, path, 1)) {
        return true;
    }
    return false;
}

// funkcije za izlazni ispis

void printConnected(bool connected) {
    cout << "Graf G ";
    if(connected)
        cout << "je";
    else
        cout << "nije";
    cout << " povezan graf" << endl;
}

void printHamilton(bool hamiltonian) {
    cout << "Graf G ";
    if(hamiltonian)
        cout << "je";
    else
        cout << "nije";
    cout << " hamiltonovski graf" << endl;
}

int main() {
    int n, k[4];

    cout << "Unesite prirodan broj n: ";
    cin >> n;
    for (int i = 0; i < 4; ++i) {
        cout << "Unesite vrijednost prirodnog broja k_" << i + 1 << ": ";
        cin >> k[i];
    }

//    auto begin = high_resolution_clock::now();

    // radi matricu susjedstva
    int** M = new int*[n];            // matrica
    for (int i = 0; i < n; ++i) {
        M[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            int tmp = abs(i - j);
            // dodjeljivanje vrijednosti u matricu
            if(tmp == k[0] || tmp == k[1] || tmp == k[2] || tmp == k[3]) {
                M[i][j] = 1;
            }
            else {
                M[i][j] = 0;
            }
        }
    }

    // ispis matrice susjedstva
//    cout << "Matrica" << endl;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << M[i][j] << "  ";
//        }
//        cout << endl;
//    }

    bool connected = isConnected(M, n);

    bool hamiltonian = false;
    if(connected)
        hamiltonian = isHamiltonian(M, n);

    printConnected(connected);
    printHamilton(hamiltonian);

//    auto end = high_resolution_clock::now();
//    auto elapsed = duration_cast<nanoseconds>(end - begin);
//    cout << elapsed.count() * 1e-9 << " seconds" << endl;

    return 0;
}