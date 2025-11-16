#include <iostream>
#include <random>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr int kNumOfCircles = 3;
    double x[kNumOfCircles];
    double y[kNumOfCircles];
    double r[kNumOfCircles];

    for (int i = 0; i < kNumOfCircles; ++i) {
        std::cin >> x[i] >> y[i] >> r[i];
    }

    double x_min = x[0] - r[0];
    double x_max = x[0] + r[0];
    double y_min = y[0] - r[0];
    double y_max = y[0] + r[0];

    for (int i = 1; i < kNumOfCircles; ++i) {
        x_min = std::min(x_min, x[i] - r[i]);
        x_max = std::max(x_max, x[i] + r[i]);
        y_min = std::min(y_min, y[i] - r[i]);
        y_max = std::max(y_max, y[i] + r[i]);
    }

    if (x_max <= x_min || y_max <= y_min) {
        std::cout << 0.0 << '\n';
        return 0;
    }

    double s_rec = (x_max - x_min) * (y_max - y_min);

    constexpr int kN = 1000000;

    constexpr int kSeed = 42;
    std::mt19937_64 rng(kSeed);
    std::uniform_real_distribution<double> dist_x(x_min, x_max);
    std::uniform_real_distribution<double> dist_y(y_min, y_max);

    int M = 0;
    double r2[kNumOfCircles];
    for (int i = 0; i < kNumOfCircles; ++i) {
        r2[i] = r[i] * r[i];
    }

    for (int i = 0; i < kN; ++i) {
        double xx = dist_x(rng);
        double yy = dist_y(rng);

        bool inside = true;
        for (int j = 0; j < kNumOfCircles; ++j) {
            double dx = xx - x[j];
            double dy = yy - y[j];
            if (dx * dx + dy * dy > r2[j]) {
                inside = false;
                break;
            }
        }
        if (inside) {
            ++M;
        }
    }

    double area = static_cast<double>(M) / static_cast<double>(kN) * s_rec;

    std::cout << area << '\n';

    return 0;
}
