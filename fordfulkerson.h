#ifndef _FORD_FULKERSON_H_
#define _FORD_FULKERSON_H_

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "arc.h"
using namespace std;

const double EPS = 1e-2;


class FordFulkerson {
private:
    int nombresNoeuds;
    vector<vector<Arc>> residuel;
    vector<int> parent;
    vector<int> parentArc;
    bool bfs(int s, int t);
public:
    FordFulkerson(int nombresNoeuds);
    void ajouterArc(int source, int target, double capacite);
    Arc prendreArc(int source, int indice);
    double caculer(int s, int t);
    ~FordFulkerson();
};

#endif