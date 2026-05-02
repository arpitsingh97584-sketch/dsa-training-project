/*
 * ================================================================
 *   Delhi–Dehradun Expressway Simulation — Advanced DSA Project
 * ================================================================
 *
 *  DSA Concepts:
 *  1. Graph (Adjacency List)          — Cities & Roads
 *  2. Dijkstra's Algorithm            — Shortest path (dist/time/toll)
 *  3. Bellman-Ford Algorithm          — Negative cycle detection (fuel arbitrage)
 *  4. Kruskal's Algorithm + DSU       — Minimum Spanning Tree
 *  5. Fenwick Tree (BIT)              — Range sum queries on tolls
 *  6. Bloom Filter                    — Fast vehicle toll-pass check
 *  7. Heap / Priority Queue           — Used in Dijkstra & Top-K
 *  8. Hashing (unordered_map)         — Fast city/vehicle lookup
 *
 *  Input: expressway.txt (or hardcoded sample below)
 *  Output: CLI-based results
 * ================================================================
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <numeric>

using namespace std;

// ───────────────────────────────────────────────
//  SECTION 1 — Graph Structures
// ───────────────────────────────────────────────

struct Edge {
    int to;
    int dist;   // km
    int time;   // minutes
    int toll;   // INR
};

struct City {
    string name;
    int km_from_delhi; // position on expressway
};

const int INF = INT_MAX;

class ExpresswayGraph {
public:
    int numCities;
    vector<City> cities;
    vector<vector<Edge>> adj;
    unordered_map<string, int> cityIndex;

    ExpresswayGraph() : numCities(0) {}

    void addCity(const string& name, int km) {
        cityIndex[name] = numCities++;
        cities.push_back({name, km});
        adj.push_back({});
    }

    void addEdge(const string& from, const string& to, int dist, int time, int toll) {
        int u = cityIndex[from], v = cityIndex[to];
        adj[u].push_back({v, dist, time, toll});
        adj[v].push_back({u, dist, time, toll});
    }

    void printGraph() {
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║         EXPRESSWAY GRAPH — ADJACENCY LIST                ║\n";
        cout << "╚══════════════════════════════════════════════════════════╝\n";
        for (int u = 0; u < numCities; u++) {
            cout << "\n  [" << u << "] " << cities[u].name << " (" << cities[u].km_from_delhi << " km from Delhi)\n";
            for (auto& e : adj[u]) {
                cout << "      → [" << e.to << "] " << cities[e.to].name
                     << "  | Dist: " << e.dist << " km"
                     << "  | Time: " << e.time << " min"
                     << "  | Toll: ₹" << e.toll << "\n";
            }
        }
        cout << "\n";
    }
};

// ───────────────────────────────────────────────
//  SECTION 2 — Dijkstra's Algorithm
//  Weight mode: 0=distance, 1=time, 2=toll
// ───────────────────────────────────────────────

struct DijkResult {
    vector<int> dist;
    vector<int> parent;
    bool found;
    int cost;
    vector<int> path;
};

DijkResult dijkstra(ExpresswayGraph& g, int src, int dst, int mode) {
    int n = g.numCities;
    vector<int> d(n, INF), par(n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    d[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost > d[u]) continue;
        for (auto& e : g.adj[u]) {
            int w = (mode == 0) ? e.dist : (mode == 1) ? e.time : e.toll;
            if (d[u] + w < d[e.to]) {
                d[e.to] = d[u] + w;
                par[e.to] = u;
                pq.push({d[e.to], e.to});
            }
        }
    }

    DijkResult res;
    res.dist = d; res.parent = par;
    res.found = (d[dst] != INF);
    res.cost  = d[dst];

    if (res.found) {
        for (int v = dst; v != -1; v = par[v]) res.path.push_back(v);
        reverse(res.path.begin(), res.path.end());
    }
    return res;
}

void printDijkstra(ExpresswayGraph& g, int src, int dst, int mode) {
    string label[] = {"Distance", "Time", "Toll"};
    string unit[]  = {"km", "min", "₹"};
    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  DIJKSTRA — Shortest " << left << setw(37) << (label[mode] + " Path") << "║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  From : " << g.cities[src].name << "\n";
    cout << "  To   : " << g.cities[dst].name << "\n";

    auto res = dijkstra(g, src, dst, mode);
    if (!res.found) { cout << "  ✗ No path found!\n\n"; return; }

    cout << "  Optimal " << label[mode] << " : " << res.cost << " " << unit[mode] << "\n\n";

    // Also compute other metrics along the path
    int totalDist = 0, totalTime = 0, totalToll = 0;
    for (int i = 0; i + 1 < (int)res.path.size(); i++) {
        int u = res.path[i], v = res.path[i+1];
        for (auto& e : g.adj[u]) {
            if (e.to == v) { totalDist += e.dist; totalTime += e.time; totalToll += e.toll; break; }
        }
    }

    cout << "  Path:\n";
    for (int i = 0; i < (int)res.path.size(); i++) {
        int n = res.path[i];
        cout << "    " << (i == 0 ? "🚗" : "  ") << " [" << n << "] " << g.cities[n].name;
        if (i + 1 < (int)res.path.size()) cout << "\n       ↓\n";
    }
    cout << "  🏁\n\n";
    cout << "  Summary → Distance: " << totalDist << " km | Time: " << totalTime << " min | Toll: ₹" << totalToll << "\n\n";
}

// ───────────────────────────────────────────────
//  SECTION 3 — Bellman-Ford (Negative Cycle Detection)
//  Detects "fuel arbitrage" (negative-weight cycles)
// ───────────────────────────────────────────────

void bellmanFord(ExpresswayGraph& g, int src) {
    int n = g.numCities;
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int iter = 0; iter < n - 1; iter++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;
            for (auto& e : g.adj[u]) {
                if (dist[u] + e.dist < dist[e.to]) {
                    dist[e.to] = dist[u] + e.dist;
                    parent[e.to] = u;
                }
            }
        }
    }

    // Check for negative cycles (V-th relaxation)
    bool hasNegCycle = false;
    int cycleNode = -1;
    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;
        for (auto& e : g.adj[u]) {
            if (dist[u] + e.dist < dist[e.to]) {
                hasNegCycle = true;
                cycleNode = e.to;
            }
        }
    }

    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BELLMAN-FORD — Fuel Arbitrage Detection                 ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  Source: " << g.cities[src].name << "\n\n";

    cout << "  Shortest distances from " << g.cities[src].name << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "    → " << g.cities[i].name << ": ";
        if (dist[i] == INF) cout << "∞ (unreachable)\n";
        else cout << dist[i] << " km\n";
    }

    cout << "\n  Negative Cycle (Fuel Arbitrage): ";
    if (hasNegCycle) {
        cout << "⚠️  DETECTED at node [" << cycleNode << "] " << g.cities[cycleNode].name << "\n";
        cout << "  → A route exists where fuel savings create infinite profit!\n\n";
    } else {
        cout << "✓ None detected. All routes are financially stable.\n\n";
    }
}

// ───────────────────────────────────────────────
//  SECTION 4 — Kruskal's MST + Disjoint Set Union
// ───────────────────────────────────────────────

struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        return true;
    }
};

struct MSTEdge {
    int u, v, dist;
};

void kruskalMST(ExpresswayGraph& g) {
    vector<MSTEdge> allEdges;
    for (int u = 0; u < g.numCities; u++) {
        for (auto& e : g.adj[u]) {
            if (e.to > u) allEdges.push_back({u, e.to, e.dist});
        }
    }
    sort(allEdges.begin(), allEdges.end(), [](auto& a, auto& b){ return a.dist < b.dist; });

    DSU dsu(g.numCities);
    vector<MSTEdge> mst;
    int totalWeight = 0;

    for (auto& e : allEdges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.dist;
        }
    }

    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  KRUSKAL — Minimum Spanning Tree (MST)                  ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  Edges in MST (minimum road network):\n\n";
    for (auto& e : mst) {
        cout << "    " << left << setw(18) << g.cities[e.u].name
             << " ──── " << setw(18) << g.cities[e.v].name
             << "  [" << e.dist << " km]\n";
    }
    cout << "\n  Total MST Weight: " << totalWeight << " km\n";
    cout << "  (This is the minimum road length to connect all cities)\n\n";
}

// ───────────────────────────────────────────────
//  SECTION 5 — Fenwick Tree (Binary Indexed Tree)
//  Range sum queries on toll collection data
// ───────────────────────────────────────────────

class FenwickTree {
    vector<int> bit;
    int n;
public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int i, int delta) {
        for (++i; i <= n; i += i & (-i))
            bit[i] += delta;
    }

    int query(int i) {
        int sum = 0;
        for (++i; i > 0; i -= i & (-i))
            sum += bit[i];
        return sum;
    }

    int rangeQuery(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

void demonstrateFenwick(ExpresswayGraph& g) {
    // Simulate daily toll collections per city (index = city index)
    vector<int> tollsCollected = {0, 12500, 9800, 15200, 11000, 8700, 7200, 5500};
    // Pad if fewer cities
    while ((int)tollsCollected.size() < g.numCities) tollsCollected.push_back(5000);

    int n = g.numCities;
    FenwickTree ft(n);
    for (int i = 0; i < n; i++) ft.update(i, tollsCollected[i]);

    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  FENWICK TREE — Toll Range Queries                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  Daily toll collections per plaza:\n";
    for (int i = 0; i < n; i++) {
        cout << "    [" << i << "] " << left << setw(18) << g.cities[i].name
             << " ₹" << tollsCollected[i] << "\n";
    }

    cout << "\n  Range Queries (O(log N) each):\n";
    cout << "    Total toll [0.." << n-1 << "] (all plazas)  : ₹" << ft.rangeQuery(0, n-1) << "\n";
    if (n > 2) {
        cout << "    Total toll [1.." << min(3, n-1) << "] (mid section)  : ₹" << ft.rangeQuery(1, min(3, n-1)) << "\n";
        cout << "    Total toll [" << n/2 << ".." << n-1 << "] (second half)  : ₹" << ft.rangeQuery(n/2, n-1) << "\n";
    }

    // Dynamic update
    cout << "\n  Update: New vehicles pay toll at " << g.cities[1].name << " (+₹3000)\n";
    ft.update(1, 3000);
    cout << "    Total toll after update [0.." << n-1 << "]      : ₹" << ft.rangeQuery(0, n-1) << "\n\n";
}

// ───────────────────────────────────────────────
//  SECTION 6 — Bloom Filter
//  Probabilistic vehicle check (O(1) lookup)
// ───────────────────────────────────────────────

class BloomFilter {
    static const int BITS = 1024;
    bitset<BITS> filter;

    // Three simple hash functions
    int h1(const string& s) {
        int h = 0; for (char c : s) h = (h * 31 + c) % BITS; return h;
    }
    int h2(const string& s) {
        int h = 0; for (char c : s) h = (h * 37 + c) % BITS; return h;
    }
    int h3(const string& s) {
        int h = 5381; for (char c : s) h = ((h << 5) + h) ^ c; return abs(h) % BITS;
    }

public:
    void insert(const string& vehicleId) {
        filter.set(h1(vehicleId));
        filter.set(h2(vehicleId));
        filter.set(h3(vehicleId));
    }

    bool mightContain(const string& vehicleId) {
        return filter.test(h1(vehicleId)) &&
               filter.test(h2(vehicleId)) &&
               filter.test(h3(vehicleId));
    }
};

void demonstrateBloomFilter() {
    BloomFilter bf;

    // Vehicles that have passed a toll plaza
    vector<string> registered = {
        "DL01AB1234", "UP14CD5678", "HR26EF9012",
        "UK07GH3456", "DL02IJ7890", "UP80KL2345"
    };

    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  BLOOM FILTER — Fast Vehicle Toll-Pass Check            ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  Registering vehicles that passed toll...\n";
    for (auto& v : registered) {
        bf.insert(v);
        cout << "    ✓ Registered: " << v << "\n";
    }

    cout << "\n  Checking vehicles at next plaza:\n";
    vector<string> toCheck = {
        "DL01AB1234",  // registered
        "UK07GH3456",  // registered
        "MH12XX9999",  // NOT registered
        "DL02IJ7890",  // registered
        "RJ14YY0001"   // NOT registered
    };

    for (auto& v : toCheck) {
        bool passed = bf.mightContain(v);
        bool actual = find(registered.begin(), registered.end(), v) != registered.end();
        cout << "    [" << v << "] → "
             << (passed ? "✓ Likely passed toll" : "✗ Has NOT passed toll");
        if (passed && !actual) cout << " ⚠️ (False positive — Bloom Filter trade-off)";
        cout << "\n";
    }

    cout << "\n  Note: Bloom Filter uses O(1) time, O(m) space, no false negatives.\n\n";
}

// ───────────────────────────────────────────────
//  SECTION 7 — Top-K Toll Plazas (Max-Heap)
// ───────────────────────────────────────────────

void topKTollPlazas(ExpresswayGraph& g, int k) {
    // Simulate toll collections
    vector<pair<int,string>> tollData;
    vector<int> sample = {5500, 12500, 9800, 15200, 11000, 8700, 7200, 6100};
    for (int i = 0; i < g.numCities; i++) {
        int toll = (i < (int)sample.size()) ? sample[i] : 5000 + i * 700;
        tollData.push_back({toll, g.cities[i].name});
    }

    // Max-heap
    priority_queue<pair<int,string>> pq;
    for (auto& t : tollData) pq.push(t);

    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  TOP-K TOLL PLAZAS (Max-Heap)                           ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "  Top " << k << " busiest toll plazas today:\n\n";
    int rank = 1;
    while (!pq.empty() && rank <= k) {
        auto [toll, name] = pq.top(); pq.pop();
        cout << "  #" << rank++ << "  " << left << setw(20) << name << "  ₹" << toll << "\n";
    }
    cout << "\n";
}

// ───────────────────────────────────────────────
//  SECTION 8 — File Input (expressway.txt)
// ───────────────────────────────────────────────

bool loadFromFile(ExpresswayGraph& g, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) return false;

    int numCities, numEdges;
    fin >> numCities >> numEdges;

    for (int i = 0; i < numCities; i++) {
        string name; int km;
        fin >> name >> km;
        g.addCity(name, km);
    }

    for (int i = 0; i < numEdges; i++) {
        string from, to; int dist, time, toll;
        fin >> from >> to >> dist >> time >> toll;
        g.addEdge(from, to, dist, time, toll);
    }
    return true;
}

void loadSampleData(ExpresswayGraph& g) {
    // From the report's sample input format
    g.addCity("Delhi",       0);
    g.addCity("Baghpat",    47);
    g.addCity("Shamli",     77);
    g.addCity("Saharanpur", 122);
    g.addCity("Dehradun",   192);

    g.addEdge("Delhi",     "Baghpat",    47,  40,  60);
    g.addEdge("Baghpat",   "Shamli",     30,  25,  40);
    g.addEdge("Shamli",    "Saharanpur", 45,  35,  60);
    g.addEdge("Saharanpur","Dehradun",   70,  60, 100);
    g.addEdge("Delhi",     "Saharanpur", 170, 130, 180);
}

// ───────────────────────────────────────────────
//  MAIN
// ───────────────────────────────────────────────

void printBanner() {
    cout << "\n";
    cout << "  ████████████████████████████████████████████████████████\n";
    cout << "  █                                                      █\n";
    cout << "  █   Delhi–Dehradun Expressway — Advanced DSA Project   █\n";
    cout << "  █   Dijkstra | Bellman-Ford | Kruskal | Fenwick Tree   █\n";
    cout << "  █   Bloom Filter | Heap | Hashing | DSU                █\n";
    cout << "  █                                                      █\n";
    cout << "  ████████████████████████████████████████████████████████\n\n";
}

int main() {
    printBanner();

    ExpresswayGraph g;

    // Try loading from file, else use sample
    if (!loadFromFile(g, "expressway.txt")) {
        cout << "  [Info] expressway.txt not found. Using sample data from report.\n";
        loadSampleData(g);
    } else {
        cout << "  [Info] Loaded graph from expressway.txt\n";
    }

    g.printGraph();

    int src = 0; // Delhi
    int dst = g.numCities - 1; // Dehradun

    // ── 1. Dijkstra (Distance) ──
    printDijkstra(g, src, dst, 0);

    // ── 2. Dijkstra (Time) ──
    printDijkstra(g, src, dst, 1);

    // ── 3. Dijkstra (Toll) ──
    printDijkstra(g, src, dst, 2);

    // ── 4. Bellman-Ford ──
    bellmanFord(g, src);

    // ── 5. Kruskal's MST ──
    kruskalMST(g);

    // ── 6. Fenwick Tree ──
    demonstrateFenwick(g);

    // ── 7. Bloom Filter ──
    demonstrateBloomFilter();

    // ── 8. Top-K Toll Plazas ──
    topKTollPlazas(g, min(3, g.numCities));

    // ── Interactive Mode ──
    cout << "  ══════════════════════════════════════════════════════════\n";
    cout << "  INTERACTIVE MODE\n";
    cout << "  ══════════════════════════════════════════════════════════\n";

    char again = 'y';
    while (again == 'y' || again == 'Y') {
        cout << "\n  Cities available:\n";
        for (int i = 0; i < g.numCities; i++)
            cout << "    [" << i << "] " << g.cities[i].name << "\n";

        int s, d;
        cout << "  Enter Source (0-" << g.numCities-1 << "): "; cin >> s;
        cout << "  Enter Destination (0-" << g.numCities-1 << "): "; cin >> d;

        if (s < 0 || s >= g.numCities || d < 0 || d >= g.numCities) {
            cout << "  Invalid input.\n";
        } else {
            int mode;
            cout << "  Optimize by: 0=Distance  1=Time  2=Toll → "; cin >> mode;
            if (mode < 0 || mode > 2) cout << "  Invalid mode.\n";
            else printDijkstra(g, s, d, mode);
        }

        cout << "  Run again? (y/n): "; cin >> again;
    }

    cout << "\n  Thank you! Safe travels on the expressway 🛣️\n\n";
    return 0;
}
