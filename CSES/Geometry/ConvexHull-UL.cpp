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
        T zCross = ((p3-p1)^(p2-p1)).z;
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
    Vec3<T> Rotate(double angle, Vec3<double> axis = {0, 0, 1}) {
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
 
bool pp(const Vec3<double>& lhs, const Vec3<double>& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}
 
struct Polygon {
    int v;
    std::vector<Vec3<double>> points;
 
    Polygon(int v = 0, const std::vector<Vec3<double>>& points = std::vector<Vec3<double>>()) : v(v), points(points) {}
    Polygon(const std::vector<Vec3<double>>& points = std::vector<Vec3<double>>()) : v(points.size()), points(points) {}
 
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
    
    bool isPointInside(const Vec3<double>& p) {
        return false;
    }
 
    std::vector<Vec3<double>> ConvexHull() {
        int n = points.size();
        if (n < 3) return points;  // Convex hull is not possible with less than 3 points
 
        // Step 1: Sort the points lexicographically (by x, then by y)
        std::sort(points.begin(), points.end(), pp);
 
        // Step 2: Build the lower hull
        std::vector<Vec3<double>> lower;
        for (int i = 0; i < n; i++) {
            while (lower.size() >= 2 && Vec3<double>::Orientation(lower[lower.size() - 2], lower.back(), points[i]) < 0)
                lower.pop_back();  // Remove the last point if it makes a non-counter-clockwise turn
            lower.push_back(points[i]);
        }
 
        // Step 3: Build the upper hull
        std::vector<Vec3<double>> upper;
        for (int i = n - 1; i >= 0; i--) {
            while (upper.size() >= 2 && Vec3<double>::Orientation(upper[upper.size() - 2], upper.back(), points[i]) < 0)
                upper.pop_back();  // Remove the last point if it makes a non-counter-clockwise turn
            upper.push_back(points[i]);
        }
 
        // Step 4: Concatenate lower and upper hulls, removing the last point of each because it's repeated
        lower.pop_back();
        upper.pop_back();
        lower.insert(lower.end(), upper.begin(), upper.end());
 
        return lower;  // The full convex hull
    }
 
private:
    void RadialSort(bool clockwise = false) {
        auto minPointIt = std::min_element(points.begin(), points.end(),
            [](const Vec3<double>& a, const Vec3<double>& b) {
                return (a.y < b.y) || (a.y == b.y && a.x < b.x);
            });
        Vec3<double> pivot = *minPointIt;
 
        std::sort(points.begin(), points.end(), [pivot, clockwise](const Vec3<double>& lhs, const Vec3<double>& rhs) {
            
            int o = Vec3<double>::Orientation(pivot, lhs, rhs);
 
            // If cross product is positive, lhs is to the left of rhs
            // If cross product is negative, lhs is to the right of rhs
            // If they are collinear, sort by distance from pivot
            if (o == 0) return Vec3<double>::SqrDistance(pivot, lhs) < Vec3<double>::SqrDistance(pivot, rhs);
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
    
    Polygon cnvxHuller = Polygon(points);
    auto cnvxHull = cnvxHuller.ConvexHull();
 
    printf("%d\n", cnvxHull.size());
    for(auto p : cnvxHull) printf("%.0lf %.0lf\n", p.x, p.y);
}