// программа для генерации значений от разных параметров

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

struct Rect {
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    double Area() const { return (x_max - x_min) * (y_max - y_min); }
};

bool InIntersection(double x, double y) {
    const double r1 = 1.0;
    const double r2 = std::sqrt(5.0) / 2.0;
    const double r3 = r2;

    double dx1 = x - 1.0;
    double dy1 = y - 1.0;
    double dx2 = x - 1.5;
    double dy2 = y - 2.0;
    double dx3 = x - 2.0;
    double dy3 = y - 1.5;

    if (dx1 * dx1 + dy1 * dy1 > r1 * r1) {
        return false;
    }
    if (dx2 * dx2 + dy2 * dy2 > r2 * r2) {
        return false;
    }
    return dx3 * dx3 + dy3 * dy3 <= r3 * r3;
}

double EstimateArea(const Rect& R, int N, std::mt19937& gen) {
    std::uniform_real_distribution<double> dist_x(R.x_min, R.x_max);
    std::uniform_real_distribution<double> dist_y(R.y_min, R.y_max);

    int M = 0;
    for (int i = 0; i < N; ++i) {
        double x = dist_x(gen);
        double y = dist_y(gen);
        if (InIntersection(x, y)) {
            ++M;
        }
    }

    double s_rec = R.Area();
    return (static_cast<double>(M) / static_cast<double>(N)) * s_rec;
}

int main() {
    const double s_exact = (0.25 * M_PI) + (1.25 * std::asin(0.8)) - 1.0;

    Rect wide{0.0, 3.2, 0.0, 3.2};
    Rect narrow{0.88, 2.0, 0.88, 2.0};

    constexpr int kSeed = 42;
    std::mt19937 rng(kSeed);

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "N,"
              << "S_wide,S_narrow,"
              << "rel_err_wide,rel_err_narrow\n";

    for (int N = 100; N <= 100000; N += 500) {
        double s_wide = EstimateArea(wide, N, rng);
        double s_narrow = EstimateArea(narrow, N, rng);

        double rel_err_wide = std::fabs(s_wide - s_exact) / s_exact;
        double rel_err_narrow = std::fabs(s_narrow - s_exact) / s_exact;

        std::cout << N << "," << s_wide << "," << s_narrow << ","
                  << rel_err_wide << "," << rel_err_narrow << "\n";
    }

    return 0;
}
