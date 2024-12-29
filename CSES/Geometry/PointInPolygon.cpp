#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define PI 3.14159265
#define DEG2RAD PI/180
#define ll long long

template<typename T = ll>
struct Vec3 {
    T x, y, z;

    Vec3(T x = 0, T y = 0, T z = 0): x(x), y(y), z(z) {};

    double Length() const {
        return sqrt(x*x + y*y + z*z);
    }

    static double SqrDistance(const Vec3<T>& v1, const Vec3<T>& v2) {
        T dx = (v1.x-v2.x);
        T dy = (v1.y-v2.y);
        T dz = (v1.z-v2.z);
        return dx*dx + dy*dy + dz*dz;
    }

    static double Distance(const Vec3<T>& v1, const Vec3<T>& v2) {
        return sqrt(Vec3<T>::SqrDistance(v1, v2));
    }

    static double Angle(const Vec3<T>& v1, const Vec3<T>& v2) {
        return atan2((v1 ^ v2).Length(), v1*v2);
    }

    static int Orientation(const Vec3<T>& p1, const Vec3<T>& p2, const Vec3<T>& p3) {
        double zCross = ((p2-p1)^(p3-p1)).z;

        if(zCross > 1e-7) return 1; // Counter-Clockwise
        else if (zCross < -1e-7) return -1; // Clockwise
        else return 0; // Collinear
    }

    Vec3<T> operator+(const Vec3<T>& other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    Vec3<T> operator-(const Vec3<T>& other) const {
        return {this->x - other.x, this->y - other.y, this->z - other.z};
    }

    Vec3<T> operator-() const {
        return {-this->x, -this->y, -this->z};
    }

    Vec3<T> operator*(T s) const {
        return {this->x*s, this->y*s, this->z*s}; 
    }

    Vec3<T> operator/(T s) const {
        return {this->x/s, this->y/s, this->z/s}; 
    }

    // Normalize
    Vec3<double> Norm() const {
        double len = this->Length();
        return { this->x / len, this->y / len, this->z / len };
    }

private:
    double lerp(double a, double b, double t) const {
        return (1.0 - t) * a + b * t;
    }

public:

    // Lerp
    Vec3<double> Lerp(const Vec3<T>& target, double t) const {
        return {lerp(this->x, target.x, t), lerp(this->y, target.y, t), lerp(this->z, target.z, t)};
    }

    // Rotate
    Vec3<T> Rotate(double angle, Vec3<int> axis = {0, 0, 1}) {
        return {};
    }

    // Considering XZ as horizontal plane
    /*
    Vec3<double> ToPolar(double r) const {
        return {};
    }
    */

   // Considering XZ as horizontal plane. X is Longitude, Y is Latitude, Z is Radius
    Vec3<double> ToEuclidean() const {
        return {z*cos(y * DEG2RAD)*cos(x * DEG2RAD), z * sin(y * DEG2RAD), z * cos(y * DEG2RAD) * sin(x * DEG2RAD)};
    }

    // Rodrigues Rotation
    /*Vec3<T> RotateAround(const Vec3<T>& v, ) {

    }*/

    // Dot
    T operator*(const Vec3<T>& other) const {
        return this->x * other.x + this->y * other.y + this->z * other.z; 
    }

    // Cross
    Vec3<T> operator^(const Vec3<T>& other) const {
        return {
                this->y * other.z - this->z * other.y,
                this->z * other.x - this->x * other.z,
                this->x * other.y - this->y * other.x // Equivalent to 2D Cross
            }; 
    }

    bool operator==(const Vec3<T> other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    void Print() const {
        printf("[ %.2lf, %.2lf, %.2lf ]\n", (double)this->x, (double)this->y, (double)this->z);
    }
};

template<typename T = ll>
struct Polygon {
    int v;
    std::vector<Vec3<T>> points;

    Polygon(int v = 0, const std::vector<Vec3<T>>& points = std::vector<Vec3<T>>()) : v(v), points(points) {}
    Polygon(const std::vector<Vec3<T>>& points = std::vector<Vec3<T>>()) : v(points.size()), points(points) {}
    
    int ContainsInside(const Vec3<T>& p) {
        if(this->v < 3) return false;
        bool inside = false;

        for(int i = 1; i <= this->v; i++) {
            Vec3<T> p1 = this->points[i-1], p2 = this->points[i%this->v];
            if(Vec3<T>::Orientation(p1, p2, p) == 0 && std::min(p1.x, p2.x) <= p.x && p.x <= std::max(p1.x, p2.x) && std::min(p1.y, p2.y) <= p.y && p.y <= std::max(p1.y, p2.y)) return 2;
            if((p1.x <= p.x && p.x < p2.x && Vec3<T>::Orientation(p, p1, p2) < 0) || (p2.x <= p.x && p.x < p1.x && Vec3<T>::Orientation(p, p2, p1) < 0))
                inside = !inside;
        }

        return inside;
    }
};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    std::vector<Vec3<ll>> points = std::vector<Vec3<ll>>(n);
    for(int i = 0; i < n; i++)
        scanf("%lli%lli", &points[i].x, &points[i].y);

    Polygon<ll> polygon = Polygon<ll>(points);
    
    Vec3<ll> P;
    for(int i = 0; i < m; i++) {
        scanf("%lli%lli", &P.x, &P.y);

        int pointInPolygon = polygon.ContainsInside(P);
        if(pointInPolygon == 2) puts("BOUNDARY");
        else if(pointInPolygon) puts("INSIDE");
        else puts("OUTSIDE");
    }

    return 0;
}