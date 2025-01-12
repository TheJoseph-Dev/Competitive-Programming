#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

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


public:

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

    ll Area() {
        ll s = 0;
        for(int i = 0; i < this->v; i++) {
            s += this->points[i].x * this->points[(i+1)%v].y;
            s -= this->points[i].y * this->points[(i+1)%v].x;
        }
        
        return llabs(s);
    }
};

int main() {

    int n;
    scanf("%d", &n);

    std::vector<Vec3<ll>> points = std::vector<Vec3<ll>>(n);
    for(int i = 0; i < n; i++)
        scanf("%lli%lli", &points[i].x, &points[i].y);

    /*
        Source (and Demonstration): https://usaco.guide/plat/geo-pri?lang=java#lattice-points-in-polygon
        The number of intersections of a line with lattice points is the
        greatest common divisor of P1.x - P2.x and P1.y - P2.y
    */

    ll b = 0;
    for(int i = 0; i < n; i++)
        b += std::__gcd(abs(points[i].x-points[(i+1)%n].x), abs(points[i].y-points[(i+1)%n].y));

    // Lattice inside => Pick's theorem: https://en.wikipedia.org/wiki/Pick%27s_theorem
    // I = A - b/2 + 1 where A = area, b = boundary lattice points

    Polygon<ll> polygon = Polygon<ll>(points);
    ll A = polygon.Area();
    ll i = (A - b)/2 + 1;

    printf("%lli %lli\n", i, b);

    return 0;
}