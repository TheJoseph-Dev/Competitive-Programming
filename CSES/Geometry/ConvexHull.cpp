#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define PI 3.14159265
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
        double zCross = ((p3-p1)^(p2-p1)).z;
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

    double Area() {
        double s = 0;
        for(int i = 0; i < this->v; i++) {
            s += this->points[i].x * this->points[(i+1)%v].y;
            s -= this->points[i].y * this->points[(i+1)%v].x;
        }
        
        return abs(s/2);
    }

    bool isConvex() {
        if(this->v <= 3) return true;
        
        this->RadialSort();

        bool sign = false;
        for(int i = 0; i < this->v; i++) {
            double zCross = ((points[i]-points[(i+1)%v]) ^ (points[(i+2)%v]-points[(i+1)%v])).z;
            
            if(i == 0) sign = (zCross > 0);
            else if(sign != (zCross > 0)) return false; 
        }

        return true;
    }
    
    bool isPointInside(const Vec3<T>& p) {
        return false;
    }

    std::vector<Vec3<T>> ConvexHull(bool includeCollinear = false) {
        if(this->v < 3) return std::vector<Vec3<T>>();
        this->RadialSort();

        // When doing this radial sort, collinear points have different behaviours
        // based on the angle with p0. A bad behaviour happens at the last sequence of points
        // which are collinear.
        // Given the points are sorted by the smallest distance (when points are collinear),
        // if we think of a square, both of the adjecent p0 sides will have the same "winding" direction.
        // Thus, it's needed to reverse these points
        if(includeCollinear) {
            int i = this->v-1;
            while (i >= 0 && Vec3<T>::Orientation(this->points[0], this->points[i], this->points.back()) == 0) 
                i--;
            std::reverse(points.begin()+i+1, points.end());
        }

        std::vector<Vec3<T>> hull = std::vector<Vec3<T>>();

        for(int i = 0; i < this->v; i++) {
            while(hull.size() > 1 && Vec3<T>::Orientation(hull[hull.size()-2], hull.back(), this->points[i]) < (1-includeCollinear)) 
                hull.pop_back();
            hull.push_back(this->points[i]);
        }

        return hull;
    }

private:
    void RadialSort(bool clockwise = false) {
        auto minPointIt = std::min_element(points.begin(), points.end(),
            [](const Vec3<T>& a, const Vec3<T>& b) {
                return (a.y < b.y) || (a.y == b.y && a.x < b.x);
            });
        Vec3<T> pivot = *minPointIt;

        std::sort(points.begin(), points.end(), [pivot, clockwise](const Vec3<T>& lhs, const Vec3<T>& rhs) {
            
            int o = Vec3<T>::Orientation(pivot, lhs, rhs);

            // If cross product is positive, lhs is to the left of rhs
            // If cross product is negative, lhs is to the right of rhs
            // If they are collinear, sort by distance from pivot
            if (o == 0) return Vec3<T>::SqrDistance(pivot, lhs) < Vec3<T>::SqrDistance(pivot, rhs);
            return (clockwise ? (o < 0) : (o > 0)); // Sort in counter-clockwise order
        });
    }
};

int main() {

    int n;
    scanf("%d", &n);

    std::vector<Vec3<double>> points = std::vector<Vec3<double>>(n);
    for(int i = 0; i < n; i++)
        scanf("%lf%lf", &points[i].x, &points[i].y);
    
    Polygon<double> cnvxHuller = Polygon<double>(points);
    auto cnvxHull = cnvxHuller.ConvexHull(true);

    printf("%d\n", cnvxHull.size());
    for(auto p : cnvxHull) printf("%.0lf %.0lf\n", p.x, p.y);
}