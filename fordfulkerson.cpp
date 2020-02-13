#include "fordfulkerson.h"

FordFulkerson::FordFulkerson(int nombresNoeuds) {
    this->nombresNoeuds = nombresNoeuds;
    residuel.assign(nombresNoeuds, vector<Arc>());
    parent.resize(nombresNoeuds);
    parentArc.resize(nombresNoeuds);
}

void FordFulkerson::ajouterArc(int source, int target, double capacite) {
    Arc arc = Arc(target, capacite, residuel[target].size());
    Arc inverseArc = Arc(source, capacite, residuel[source].size());
    residuel[source].push_back(arc);
    residuel[target].push_back(inverseArc);
}

Arc FordFulkerson::prendreArc(int source, int indice) {
    return residuel[source][indice];
}

bool FordFulkerson::bfs(int s, int t) {
    int u, v;
    fill(parent.begin(), parent.end(), -1);

    queue<int> q;
    q.push(s);
    parent[s] = -2;
    while (!q.empty()) {
        u = q.front();
        q.pop();

        for (int i = 0; i < residuel[u].size(); i++) {
            v = residuel[u][i].target;
            if (parent[v] == -1 && residuel[u][i].capacite - residuel[u][i].flot > EPS) {
                parent[v] = u;
                parentArc[v] = i;
                q.push(v);

                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

double FordFulkerson::caculer(int s, int t) {
    double totalFlot = 0;
    while (bfs(s, t)) {
        double increment = numeric_limits<double>::infinity();
        int u, v, i;
        v = t;
        while (v != s) {
            u = parent[v];
            i = parentArc[v];
            Arc arc = residuel[u][i];

            increment = min(increment, arc.capacite - arc.flot);
            v = u;
        }
        totalFlot += increment;

        v = t;
        while (v != s) {
            u = parent[v];
            i = parentArc[v];
            Arc& arc = residuel[u][i];
            // arc.inverse là index của cạnh đảo của arc trong residuel[v]
            Arc& inverseArc = residuel[v][arc.inverse];

            arc.flot += increment;
            inverseArc.flot -= increment;
            v = u;
        }
    }
    return totalFlot;
}

FordFulkerson::~FordFulkerson() {

}
