#include <iostream>
#include <algorithm> // Para std::sort
#include <vector>

using namespace std;

double calcularMediana(vector<int>& datos) {
    // Ordenar el vector
    sort(datos.begin(), datos.end());

    int n = datos.size();
    if (n % 2 == 0) {
        // Si el número de elementos es par, la mediana es el promedio de los dos valores centrales
        return (datos[n / 2 - 1] + datos[n / 2]) / 2.0;
    }
    else {
        // Si el número de elementos es impar, la mediana es el valor central
        return datos[n / 2];
    }
}

int main() {
    int n;
    cout << "Ingrese el número de elementos: ";
    cin >> n;

    vector<int> datos(n);
    cout << "Ingrese los elementos:\n";
    for (int i = 0; i < n; ++i) {
        cin >> datos[i];
    }

    double mediana = calcularMediana(datos);
    cout << "La mediana es: " << mediana << endl;

    return 0;
}