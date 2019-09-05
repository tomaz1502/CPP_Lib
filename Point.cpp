#include <bits/stdc++.h>
using namespace std;

using type = double;

struct Point{
    type x, y;

    Point() { }
    Point(type x_, type y_) : x(x_) , y(y_) {}
    Point(Point P, Point Q) : x(Q.x - P.x) , y(Q.y - P.y) {}

    Point operator+(Point P) { return Point(P.x + x, P.y + y); }
    Point operator-(Point P) { return Point(x - P.x, y - P.y); }
    Point operator*(type c) { return Point(c * x, c * y); }
    Point operator/(type c) { return Point(x / c, y / c); }
    bool operator==(Point P) { return x == P.x and y == P.y; }
    bool operator!=(Point P) { return !(*this == P); }

};

type sq(Point P){ return P.x*P.x + P.y*P.y; }
double abs(Point P) { return sqrt(sq(P)); }

ostream& operator<<(ostream &os, Point P){
    return os << "(" << P.x << ", " << P.y << ")";
}

int sign(type x){ return (type(0) < x) - (x < type(0)); }

type dot(Point P, Point Q){ return P.x * Q.x + P.y * Q.y; }
bool perp(Point P, Point Q){ return dot(P,Q) == 0; }
type angle(Point P, Point Q){
    double ctht = dot(P,Q) / abs(P) / abs(Q);
    return acos(max(-1.0, min(1.0, ctht))); // care is never enough
}

type cross(Point P, Point Q){ return P.x * Q.y - P.y * Q.x; }
bool ccw(Point P, Point Q, Point R){ return cross(Q-P, R-Q) > 0; }
type orientation(Point P, Point Q, Point R){ return cross(Q-P, R-Q); }
Point perp(Point P){ return Point(-P.y, P.x); }




struct Line{ //line that is oriented by V and satisfies ax + by = c
    Point V;
    type c;

    Line(Point V_, type c_) : V(V_) , c(c_) {}
    Line(type a, type b, type c_) : V(b, -a), c(c_) {}
    Line(Point P, Point Q) : V(Q-P) , c(cross(V,P)) {}

    type side(Point P){ return cross(V, P) - c; } // >0 -> "esquerda"
    type dist(Point P){ return abs(side(P)) / abs(V); }
    type sqdist(Point P){ return side(P) * side(P) / (type)sq(V); }
    Line perpThrough(Point P){ return Line(P, P + perp(V)); }

};

bool intersect_L(Line L1, Line L2, Point &R){
    type c = cross(L1.V, L2.V);
    if(c == 0) return false;
    R = (L2.V * L1.c - L1.V * L2.c) / c;
    return true;
}

bool cmp(Point P, Point Q){
    if(P.x == Q.x) return P.y < Q.y;
    return P.x < Q.x;
}

vector< Point > convex_hull(vector< Point > pts){
    sort(pts.begin(), pts.end(), cmp);
    vector< Point > low, up, ret;


    for(int i = 0; i<pts.size(); i++){
        while(low.size() > 1){
            type c = cross(pts[i] - low.back(), low.back() - low[low.size() - 2]);
            if(c >= 0) break;
            low.pop_back();
        }
        low.push_back(pts[i]);
    }

    for(int i = pts.size() - 1; i>=0; i--){
        while(up.size() > 1){
            type c = cross(pts[i] - up.back(), up.back() - up[up.size() - 2]);
            if(c >= 0) break;
            up.pop_back();
        }
        up.push_back(pts[i]);
    }

    low.pop_back(); up.pop_back();
    ret.insert(ret.end(), low.begin(), low.end());
    ret.insert(ret.end(), up.begin(), up.end());

    return ret;
}
