#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
vector<string> estudiantes;
void cargarEstudiantes() {
    ifstream file("Estudiantes.txt");
    string line;
    while (getline(file, line)) {
        estudiantes.push_back(line);
    }
    file.close();
}
string extraerNombre(string linea) {
    size_t pos = linea.find(": ");
    if (pos != string::npos) {
        return linea.substr(pos + 2);
    }
    return linea;
}
int main() {
    cargarEstudiantes();
    int opcion;
    float n1, n2;
    vector<float> notas(3);
    float suma = 0, promedio, mayor, menor;
    string estudianteSeleccionado;
    bool notasRegistradas = false;
    int totalAprobados = 0;
    int totalReprobados = 0;
    do {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Operaciones basicas" << endl;
        cout << "2. Registro de notas" << endl;
        cout << "3. Guardar resultados" << endl;
        cout << "4. Ver aprobados/reprobados" << endl;
        cout << "5. Salir" << endl;
        if (!estudianteSeleccionado.empty()) {
            cout << "Estudiante seleccionado: " << estudianteSeleccionado << endl;
        }
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1: {
                int opMatematica;
                cout << "\n===== OPERACIONES MATEMATICAS =====" << endl;
                cout << "1. Suma" << endl;
                cout << "2. Resta" << endl;
                cout << "3. Multiplicacion" << endl;
                cout << "4. Division" << endl;
                cout << "5. Volver al menu" << endl;
                cout << "Seleccione operacion: ";
                cin >> opMatematica;
                if (opMatematica >= 1 && opMatematica <= 4) {
                    cout << "Ingrese primer numero: ";
                    cin >> n1;
                    cout << "Ingrese segundo numero: ";
                    cin >> n2;
                    switch (opMatematica) {
                        case 1:
                            cout << "Resultado: " << n1 + n2 << endl;
                            break;
                        case 2:
                            cout << "Resultado: " << n1 - n2 << endl;
                            break;
                        case 3:
                            cout << "Resultado: " << n1 * n2 << endl;
                            break;
                        case 4:
                            if (n2 != 0) {
                                cout << "Resultado: " << n1 / n2 << endl;
                            } else {
                                cout << "Error: No se puede dividir para cero." << endl;
                            }
                            break;
                    }
                }
                break;
            }
            case 2: {
                string nombreBusqueda;
                cout << "\nIngrese nombre del estudiante a buscar: ";
                getline(cin, nombreBusqueda);
                bool encontrado = false;
                for (size_t i = 0; i < estudiantes.size(); i++) {
                    string nombre = extraerNombre(estudiantes[i]);
                    if (nombre.find(nombreBusqueda) != string::npos) {
                        estudianteSeleccionado = nombre;
                        encontrado = true;
                        cout << "Estudiante encontrado: " << estudianteSeleccionado << endl;
                        break;
                    }
                }
                if (encontrado) {
                    suma = 0;
                    mayor = -1;
                    menor = 101;   
                    for (int i = 0; i < 3; i++) {
                        cout << "Ingrese nota " << i + 1 << ": ";
                        cin >> notas[i];
                        suma += notas[i];
                        if (notas[i] > mayor) mayor = notas[i];
                        if (notas[i] < menor) menor = notas[i];
                    }
                    promedio = suma / 3;
                    string estado = (promedio >= 7) ? "APROBADO" : "REPROBADO";
                    if (estado == "APROBADO") {
                        totalAprobados++;
                    } else {
                        totalReprobados++;
                    }
                    cout << "\n===== RESULTADOS =====" << endl;
                    cout << "Promedio: " << promedio << endl;
                    cout << "Nota Mayor: " << mayor << endl;
                    cout << "Nota Menor: " << menor << endl;
                    cout << "Estado: " << estado << endl;
                    notasRegistradas = true;
                } else {
                    cout << "Estudiante no encontrado." << endl;
                }
                break;
            }
            case 3: {
                if (notasRegistradas && !estudianteSeleccionado.empty()) {
                    ofstream archivo("resultados.txt", ios::app);
                    time_t now = time(0);
                    string fecha = ctime(&now);
                    string estado = (promedio >= 7) ? "APROBADO" : "REPROBADO";

                    archivo << "========================================" << endl;
                    archivo << "Nombre del estudiante: " << estudianteSeleccionado << endl;
                    archivo << "Promedio: " << promedio << endl;
                    archivo << "Nota Mayor: " << mayor << endl;
                    archivo << "Nota Menor: " << menor << endl;
                    archivo << "Estado: " << estado << endl;
                    archivo << "Fecha: " << fecha;
                    archivo << "Lenguaje utilizado: C++" << endl;
                    archivo << "========================================" << endl << endl;
                    archivo.close();
                    cout << "Datos guardados en resultados.txt" << endl;
                } else {
                    cout << "Primero registre notas para un estudiante." << endl;
                }
                break;
            }

            case 4: {
                cout << "\n===== ESTADO GENERAL =====" << endl;
                int contadorAprobados = 0;
                int contadorReprobados = 0;
                ifstream archivoLectura("resultados.txt");
                string lineaLectura;
                if (archivoLectura.is_open()) {
                    while (getline(archivoLectura, lineaLectura)) {
                        if (lineaLectura.find("Estado: APROBADO") != string::npos) {
                            contadorAprobados++;
                        } else if (lineaLectura.find("Estado: REPROBADO") != string::npos) {
                            contadorReprobados++;
                        }
                    }
                    archivoLectura.close();
                    cout << "Total aprobados en archivo: " << contadorAprobados << endl;
                    cout << "Total reprobados en archivo: " << contadorReprobados << endl;
                } else {
                    cout << "No hay archivo de resultados generado aun." << endl;
                }
                cout << "\nEstadistica de la sesion actual:" << endl;
                cout << "Total aprobados registrados: " << totalAprobados << endl;
                cout << "Total reprobados registrados: " << totalReprobados << endl;
                break;
            }
            default:
                if (opcion != 5) {
                    cout << "Opcion invalida." << endl;
                }
        }
    } while (opcion != 5);
    cout << "Programa finalizado." << endl;
    return 0;
}
