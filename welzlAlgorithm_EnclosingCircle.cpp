#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef long long ll;

const ld INF = 1e18;

typedef struct point{
    ld x, y;
} point;

typedef struct circle{
    point center;
    ld radius;
} circle;

ld distande(point a, point b){
    /* Função que calcula a distância de dois pontos dados */
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool is_inside(point p, circle c){
    /* Função que verifica se um ponto está dentro de um círculo */
    return distande(p, c.center) <= c.radius;
}

point getCenterCicle(ld bx, ld by, ld cx, ld cy){
    /* Função que calcula o centro de um círculo dados dois pontos */
 
    ld B = bx * bx + by * by;
    ld C = cx * cx + cy * cy;
    ld D = bx * cy - by * cx;

    point center;
    center.x = (B * cy - by * C)/ (2 * D);
    center.y = (bx * C - cx * B)/ (2 * D);
    return center;
}

circle circleFrom(point a, point b){
    /* Função que calcula um círculo a partir de dois pontos */
    point c = {(a.x + b.x)/2, (a.y + b.y)/2};
    return {c, distande(a, c)/2};
}

circle circleFrom(point a, point b, point c){
    /* Função que calcula um círculo a partir de três pontos */
    point I = getCenterCicle(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);

    I.x+=a.x;
    I.y+=a.y;
    return {I, distande(I, a)};
}

bool isValidCircle(circle C, vector <point> P){
    /* Função que verifica se um círculo é válido */
    for(ll i = 0; i < P.size(); i++){
        if(!is_inside(P[i], C)){
            return false;
        }
    }
    return true;
}

circle minTrivialCircle(vector <point> P){
    /* Função que calcula o círculo mínimo trivial */
    ll n = P.size();

    assert(P.size() <= 3);

    if(P.empty()){
        return {{0, 0}, 0};
    }
    else if(P.size() == 1){
        return {P[0], 0};
    }
    else if(P.size() == 2){
        return circleFrom(P[0], P[1]);
    }

    for(ll i = 0; i < 3; ++i){
        for(ll j = i + 1; j < 3; ++j){
            circle c = circleFrom(P[i], P[j]);
            if(isValidCircle(c, P)){
                return c;
            }
        }
    }
    return circleFrom(P[0], P[1], P[2]);
}

circle welzlAlgorithm(vector <point> P, vector <point> R, ll n){
    /* Função que calcula o círculo mínimo usando o algoritmo de Welzl */
    
    if(n == 0 || R.size() == 3){
        return minTrivialCircle(R);
    }

    ll idx = rand() % n;
    point p = P[idx];

    swap(P[idx], P[n - 1]);

    circle d = welzlAlgorithm(P, R, n - 1);

    if(is_inside(p, d)){
        return d;
    }

    R.push_back(p);
    return welzlAlgorithm(P, R, n-1);
}

circle welzl(vector <point> P){
    /* Função que calcula o círculo mínimo usando o algoritmo de Welzl */
    vector <point> R = P;
    random_shuffle(R.begin(), R.end());
    return welzlAlgorithm(R, {}, R.size());
}

int main()
{
 
    circle mec = welzl({ { 0, 0 },
                                            { 0, 1 },
                                            { 1, 0 } });
 
    cout << "Center = { " << mec.center.x << ", " << mec.center.y
         << " } Radius = " << mec.radius << endl;
 
    circle mec2 = welzl({ { 5, -2 },
                                             { -3, -2 },
                                             { -2, 5 },
                                             { 1, 6 },
                                             { 0, 2 } });
 
    cout << "Center = { " << mec2.center.x << ", " << mec2.center.y
         << " } Radius = " << mec2.radius << endl;
 
    return 0;
}