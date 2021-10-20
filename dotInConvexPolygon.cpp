#include <bits/stdc++.h>
using namespace std;

typedef struct point{
    double x, y;

    bool operator == (const point &p) const{
        return (x == p.x && y == p.y);
    }
    
}point;

bool comp(point a, point b){
    /* Função de comparação entre dois pontos */
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

int horario(point p, point q, point r){
    /* Função que retorna 1 se o ponto está no sentido
    horário do poligono*/

    int val = p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y);
    
    return val < 0ll;
}
 
int antiHorario(point p, point q, point r){
    /* Função que retorna 1 se o ponto está no sentido
    anti-horário do poligono*/

    int val = p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y);
    
    return val > 0ll;
}

vector <point> convexHull(vector <point> p){
    /* Função que retorna o poligono convexo de um conjunto de pontos */

    int n = p.size();

    sort(p.begin(), p.end(), comp);

    if(n <= 3) return p;

    point p1 = p[0], p2 = p[n-1];

    vector <point> up, down;

    up.push_back(p1);
    down.push_back(p1);

    for(int i=1; i<n; ++i){
        if(i == n-1 || !antiHorario(p1, p[i], p2)){
            while(up.size() >= 2 && antiHorario(up[up.size()-2], up[up.size()-1], p[i]))
                up.pop_back();
            up.push_back(p[i]);
        }

        if(i == n-1 || !horario(p1, p[i], p2)){
            while(down.size() >= 2 && horario(down[down.size()-2], down[down.size()-1], p[i]))
                down.pop_back();
            down.push_back(p[i]);
        }
    }

    for(int i=down.size()-2; i>=0; --i)
        up.push_back(down[i]);
    
    up.resize(unique(up.begin(), up.end()) - up.begin());
    return up;
}

bool isInside(vector <point> p, point q){
    /* Função que retorna true se o ponto está dentro do poligono */

    int n = p.size();
    p.push_back(q);
    p = convexHull(p);

    for (auto i: p){
        if(i.x == q.x && i.y == q.y) return false;
    }
    return true;
}

int main()
{
    // Points of the polygon
    // given in any order
    int n = 7;
    vector <point> points;
  
    points = { { 1, 1 }, { 2, 1 }, { 3, 1 },
               { 4, 1 }, { 4, 2 }, { 4, 3 },
               { 4, 4 } };
  
    // Query Points
    point query = { 3, 2 };
  
    // Check if its inside
    if (isInside(points, query)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
  
    return 0;
}


