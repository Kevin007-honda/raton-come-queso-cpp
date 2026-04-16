#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// MATRIZ 10 x 11
char tablero[10][11];

// POSICION RATON
int ratonX = 0;
int ratonY = 10;

// CONTROL
int acciones = 0;
bool juegoActivo = true;

// -------------------------------------
// LIMPIAR PANTALLA
// -------------------------------------
void limpiarPantalla() {
    system("clear");   // Linux / Codespaces
    // system("cls");  // Windows
}

// -------------------------------------
// INICIALIZAR TABLERO
// -------------------------------------
void inicializar() {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 11; j++) {
            tablero[i][j] = '.';
        }
    }
}

// -------------------------------------
// COLOCAR ELEMENTOS
// -------------------------------------
void colocarElemento(char tipo, int cantidad) {

    int count = 0;

    while(count < cantidad) {

        int x = rand() % 10;
        int y = rand() % 11;

        if(tablero[x][y] == '.' &&
           !(x == ratonX && y == ratonY)) {

            tablero[x][y] = tipo;
            count++;
        }
    }
}

// -------------------------------------
// TABLERO UNIFORME
// -------------------------------------
void imprimirTablero() {

    cout << "\033[1;36m";
    cout << "==============================================================\n";
    cout << "                   RATON COME QUESO\n";
    cout << "==============================================================\n";
    cout << "\033[0m\n";

    // COLUMNAS
    cout << "     ";
    for(int j = 0; j < 11; j++) {
        if(j < 10) cout << " " << j << "  ";
        else       cout << j << "  ";
    }
    cout << endl;

    cout << "   +";
    for(int j = 0; j < 11; j++) {
        cout << "---+";
    }
    cout << endl;

    // FILAS
    for(int i = 0; i < 10; i++) {

        cout << " " << i << " |";

        for(int j = 0; j < 11; j++) {

            string celda = " ";

            if(i == ratonX && j == ratonY)
                celda = "R";

            else if(tablero[i][j] == 'G')
                celda = "G";

            else if(tablero[i][j] == 'T')
                celda = "T";

            else if(tablero[i][j] == 'Q')
                celda = "Q";

            else
                celda = ".";

            cout << " " << celda << " |";
        }

        cout << endl;

        cout << "   +";
        for(int j = 0; j < 11; j++) {
            cout << "---+";
        }
        cout << endl;
    }

    cout << endl;
}

// -------------------------------------
// MOVER RATON
// -------------------------------------
void moverRaton(char dir) {

    int nuevoX = ratonX;
    int nuevoY = ratonY;

    if(dir == 'w') nuevoX--;
    else if(dir == 's') nuevoX++;
    else if(dir == 'a') nuevoY--;
    else if(dir == 'd') nuevoY++;
    else return;

    if(nuevoX >= 0 && nuevoX < 10 &&
       nuevoY >= 0 && nuevoY < 11) {

        ratonX = nuevoX;
        ratonY = nuevoY;
        acciones++;
    }
}

// -------------------------------------
// PERCEPCIONES
// -------------------------------------
void detectarAlertas() {

    bool gato = false;
    bool trampa = false;

    if(ratonX > 0) {
        if(tablero[ratonX-1][ratonY] == 'G') gato = true;
        if(tablero[ratonX-1][ratonY] == 'T') trampa = true;
    }

    if(ratonX < 9) {
        if(tablero[ratonX+1][ratonY] == 'G') gato = true;
        if(tablero[ratonX+1][ratonY] == 'T') trampa = true;
    }

    if(ratonY > 0) {
        if(tablero[ratonX][ratonY-1] == 'G') gato = true;
        if(tablero[ratonX][ratonY-1] == 'T') trampa = true;
    }

    if(ratonY < 10) {
        if(tablero[ratonX][ratonY+1] == 'G') gato = true;
        if(tablero[ratonX][ratonY+1] == 'T') trampa = true;
    }

    cout << "================ PERCEPCIONES ================\n";

    if(gato) cout << "Hay un gato cerca\n";
    if(trampa) cout << "Hay una trampa cerca\n";

    if(!gato && !trampa)
        cout << "Zona segura\n";

    cout << "==============================================\n";
}

// -------------------------------------
// EVALUAR CASILLA
// -------------------------------------
void evaluarCasilla() {

    if(tablero[ratonX][ratonY] == 'G') {
        cout << "\nGAME OVER: gato.\n";
        juegoActivo = false;
    }

    else if(tablero[ratonX][ratonY] == 'T') {
        cout << "\nGAME OVER: trampa.\n";
        juegoActivo = false;
    }

    else if(tablero[ratonX][ratonY] == 'Q') {
        cout << "\nGANASTE: encontraste el queso.\n";
        juegoActivo = false;
    }
}

// -------------------------------------
// ACCIONES
// -------------------------------------
void mostrarAccion(char mov) {

    cout << "\nMovimiento: " << mov << endl;
    cout << "Acciones realizadas: " << acciones << endl;
}

// -------------------------------------
// MENU
// -------------------------------------
void menu() {

    cout << "=====================================\n";
    cout << "      RATON COME QUESO\n";
    cout << "=====================================\n";
    cout << "1. Iniciar Juego\n";
    cout << "2. Salir\n";
    cout << "Seleccione opcion: ";
}

// -------------------------------------
// MAIN
// -------------------------------------
int main() {

    srand(time(0));

    int opcion;

    do {

        menu();
        cin >> opcion;

        if(opcion == 1) {

            acciones = 0;
            juegoActivo = true;
            ratonX = 0;
            ratonY = 10;

            inicializar();

            colocarElemento('G', 5);
            colocarElemento('T', 4);
            colocarElemento('Q', 1);

            while(juegoActivo) {

                limpiarPantalla();

                imprimirTablero();

                char mov;
                cout << "Movimiento (w/a/s/d): ";
                cin >> mov;

                moverRaton(mov);
                evaluarCasilla();

                if(juegoActivo) {
                    detectarAlertas();
                    mostrarAccion(mov);

                    cout << "\nENTER para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }

            cout << "\nPartida terminada en "
                 << acciones
                 << " acciones.\n\n";
        }

    } while(opcion != 2);

    cout << "\nHasta luego.\n";

    return 0;
}