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
circle circleFrom(point a, point b, point c){
    /* Função que calcula um círculo a partir de três pontos */
    point I = getCenterCicle(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);

    I.x+=a.x;
    I.y+=a.y;
    return {I, distande(I, a)};
}

circle circleFrom(point a, point b){
    /* Função que calcula um círculo a partir de dois pontos */
    point c = {(a.x + b.x)/2, (a.y + b.y)/2};
    return {c, distande(a, c)/2};
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

circle minimumEnclosingCircle(vector <point> P){
    /* Função que calcula o círculo mínimo que envolve todos os pontos */
    int n = P.size();

    if(n == 0) return {{0, 0}, 0};

    if(n == 1) return {P[0], 0};

    circle MEC = {{0, 0}, INF};

    for(ll i=0; i<n; ++i ){
        for(ll j = i+1; j<n; ++j){
            circle C = circleFrom(P[i], P[j]);

            if(C.radius < MEC.radius && isValidCircle(C, P)){
                MEC = C;
            }
        }
    }

    for(ll i=0; i<n; ++i ){
        for(ll j=i+1; j<n; ++j){
            for(ll k=j+1; k<n; ++k){
                circle C = circleFrom(P[i], P[j], P[k]);

                if(C.radius < MEC.radius && isValidCircle(C, P)){
                    MEC = C;
                }
            }
        }
    }
    return MEC;
}

int main()
{
 
    circle mec = minimumEnclosingCircle({ { 0, 0 },
                                            { 0, 1 },
                                            { 1, 0 } });
 
    cout << "Center = { " << mec.center.x << ", " << mec.center.y
         << " } Radius = " << mec.radius << endl;
 
    circle mec2 = minimumEnclosingCircle({ { 5, -2 },
                                             { -3, -2 },
                                             { -2, 5 },
                                             { 1, 6 },
                                             { 0, 2 } });
 
    cout << "Center = { " << mec2.center.x << ", " << mec2.center.y
         << " } Radius = " << mec2.radius << endl;
 
    return 0;
}