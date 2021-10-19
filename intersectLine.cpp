#include <bits/stdc++.h>
using namespace std;

typedef struct point {
    double x, y;
} point;

bool onSegment(point p, point q, point r) {
    /* Verifica se o ponto Q pertence a linha PR */
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(point p, point q, point r) {
    /* Retorna o valor da orientação do vetor (pqr) */
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);  //Angulo entre os pontos pq e pr subtraídos
              
    if (val == 0) return 0; // colinear

    return (val > 0) ? 1 : 2; //1 se pqr está no sentido horário, 2 se anti-horário
}

bool intersect(point p, point q, point r, point s){
    /* Verifica se as retas pq e rs se interceptam */
    int o1 = orientation(p, q, r);
    int o2 = orientation(p, q, s);
    int o3 = orientation(r, s, p);
    int o4 = orientation(r, s, q);

    if (o1 != o2 && o3 != o4) return true; // As retas se interceptam pois satisfazem a regra de orientacão diferente

    if (o1 == 0 && onSegment(p, r, q)) return true; // pq é colinear e está no segmento rs
    if (o2 == 0 && onSegment(p, s, q)) return true; // pq é colinear e está no segmento rs
    if (o3 == 0 && onSegment(r, p, s)) return true; // rs é colinear e está no segmento pq
    if (o4 == 0 && onSegment(r, q, s)) return true; // rs é colinear e está no segmento pq

    return false; // As retas não se interceptam
}

int main(){
    point p1, p2, q1, q2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> q1.x >> q1.y >> q2.x >> q2.y;
    if (intersect(p1, p2, q1, q2)) cout << "Intersect" << endl;
    else cout << "Not Intersect" << endl;
    return 0;
}