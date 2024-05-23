#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

struct Point {
    double x, y;
};

// Función para comparar puntos por coordenada x
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// Función para comparar puntos por coordenada y
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// Función para calcular la distancia euclídea entre dos puntos
double dist(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Función de fuerza bruta para encontrar la distancia mínima entre puntos en un conjunto pequeño
double bruteForce(std::vector<Point>& points, int left, int right) {
    double minDist = std::numeric_limits<double>::infinity();
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            double d = dist(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}

// Función para encontrar la distancia mínima en una franja de ancho 2*delta
double stripClosest(std::vector<Point>& strip, double delta) {
    double minDist = delta;
    std::sort(strip.begin(), strip.end(), compareY);
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double d = dist(strip[i], strip[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}

// Función recursiva para encontrar la distancia mínima utilizando el enfoque de divide y vencerás
double closestUtil(std::vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        return bruteForce(points, left, right);
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, left, mid);
    double dr = closestUtil(points, mid + 1, right);

    double delta = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (std::abs(points[i].x - midPoint.x) < delta) {
            strip.push_back(points[i]);
        }
    }

    return std::min(delta, stripClosest(strip, delta));
}

// Función principal para encontrar la distancia mínima entre el par de puntos más cercano
double closestPair(std::vector<Point>& points) {
    std::sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size() - 1);
}

int main() {
    std::vector<Point> points = { {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4} };
    double result = closestPair(points);
    std::cout << "La distancia mínima es " << result << std::endl;
    return 0;
}

