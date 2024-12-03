#include <stdio.h>
#include <math.h>

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


int main() {

    int t;
    scanf("%d", &t);
    while(t--) {
        Vec3<double> p1, p2, p3;
        scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y);

        int o = Vec3<double>::Orientation(p1, p2, p3); 
        if(o > 0) puts("RIGHT");
        else if(o == 0) puts("TOUCH");
        else puts("LEFT");
    }

    return 0;
}