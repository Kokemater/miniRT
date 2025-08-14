#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y, z;
} Vec3;

// --- Vector Operations ---
Vec3 subtract(Vec3 a, Vec3 b) {
    Vec3 res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

Vec3 add(Vec3 a, Vec3 b) {
    Vec3 res = {a.x + b.x, a.y + b.y, a.z + b.z};
    return res;
}

Vec3 scale(Vec3 v, double t) {
    Vec3 res = {v.x * t, v.y * t, v.z * t};
    return res;
}

// --- Determinant of 3x3 matrix ---
double det3x3(Vec3 a, Vec3 b, Vec3 c) {
    return
        a.x * (b.y * c.z - b.z * c.y) -
        a.y * (b.x * c.z - b.z * c.x) +
        a.z * (b.x * c.y - b.y * c.x);
}

// --- Solve system using Cramer's Rule ---
void solveIntersection(Vec3 rL, Vec3 v, Vec3 rP, Vec3 u, Vec3 w) {
    Vec3 d = subtract(rP, rL); // RHS

    // Matrix columns: A = [v, -u, -w]
    Vec3 col1 = v;
    Vec3 col2 = scale(u, -1);
    Vec3 col3 = scale(w, -1);

    // Compute determinant of A
    double D = det3x3(col1, col2, col3);
    if (fabs(D) < 1e-8) {
        printf("No unique intersection (parallel or coplanar).\n");
        return;
    }

    // D_t (replace column 1 with d)
    double Dt = det3x3(d, col2, col3);

    // D_s (replace column 2 with d)
    double Ds = det3x3(col1, d, col3);

    // D_q (replace column 3 with d)
    double Dq = det3x3(col1, col2, d);

    double t = Dt / D;
    double s = Ds / D;
    double q = Dq / D;

    // Compute intersection point
    Vec3 intersection = add(rL, scale(v, t));

    printf("Intersection point: (%.4f, %.4f, %.4f)\n", intersection.x, intersection.y, intersection.z);
    printf("Parameters: t = %.4f, s = %.4f, q = %.4f\n", t, s, q);
}

// --- Main Example ---
int main() {
    // Line
    Vec3 rL = {1, 1, 1};
    Vec3 v  = {1, 0, -1};

    // Plane
    Vec3 rP = {0, 0, 0};
    Vec3 u  = {1, 1, 0};
    Vec3 w  = {0, 0, 1};

    solveIntersection(rL, v, rP, u, w);

    return 0;
}
