#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char tablero[10][11];
int ratonX = 0, ratonY = 10;
int acciones = 0;
bool juegoActivo = true;

// Inicializar tablero
void inicializar() {
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            tablero[i][j] = '.';
        }
    }
}

// Colocar gatos
void colocarGatos() {
    int count = 0;
    while(count < 5) {
        int x = rand() % 10;
        int y = rand() % 11;

        if(tablero[x][y] == '.' && !(x == ratonX && y == ratonY)) {
            tablero[x][y] = 'G';
            count++;
        }
    }
}

// Colocar trampas
void colocarTrampas() {
    int count = 0;
    while(count < 4) {
        int x = rand() % 10;
        int y = rand() % 11;

        if(tablero[x][y] == '.' && !(x == ratonX && y == ratonY)) {
            tablero[x][y] = 'T';
            count++;
        }
    }
}

// Colocar queso
void colocarQueso() {
    while(true) {
        int x = rand() % 10;
        int y = rand() % 11;

        if(tablero[x][y] == '.' && !(x == ratonX && y == ratonY)) {
            tablero[x][y] = 'Q';
            break;
        }
    }
}

// Imprimir tablero
void imprimirTablero() {
    cout << "\nTABLERO:\n";
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            if(i == ratonX && j == ratonY)
                cout << "R ";
            else
                cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

// Movimiento
void moverRaton(char dir) {
    int nuevoX = ratonX;
    int nuevoY = ratonY;

    if(dir == 'w') nuevoX--;
    else if(dir == 's') nuevoX++;
    else if(dir == 'a') nuevoY--;
    else if(dir == 'd') nuevoY++;
    else {
        cout << "Movimiento invalido\n";
        return;
    }

    if(nuevoX >= 0 && nuevoX < 10 && nuevoY >= 0 && nuevoY < 11){
        ratonX = nuevoX;
        ratonY = nuevoY;
        acciones++;
    } else {
        cout << "No puedes salir del tablero\n";
    }
}

// Evaluar casilla
void evaluarCasilla() {
    if(tablero[ratonX][ratonY] == 'G') {
        cout << "\n💀 PERDISTE: te comio un gato\n";
        juegoActivo = false;
    }
    else if(tablero[ratonX][ratonY] == 'T') {
        cout << "\n💀 PERDISTE: caíste en una trampa\n";
        juegoActivo = false;
    }
    else if(tablero[ratonX][ratonY] == 'Q') {
        cout << "\n🎉 GANASTE: encontraste el queso\n";
        juegoActivo = false;
    }
}

// Detectar alertas
void detectarAlertas(int x, int y) {
    bool gatoCerca = false;
    bool trampaCerca = false;

    if(x > 0){
        if(tablero[x-1][y] == 'G') gatoCerca = true;
        if(tablero[x-1][y] == 'T') trampaCerca = true;
    }

    if(x < 9){
        if(tablero[x+1][y] == 'G') gatoCerca = true;
        if(tablero[x+1][y] == 'T') trampaCerca = true;
    }

    if(y > 0){
        if(tablero[x][y-1] == 'G') gatoCerca = true;
        if(tablero[x][y-1] == 'T') trampaCerca = true;
    }

    if(y < 10){
        if(tablero[x][y+1] == 'G') gatoCerca = true;
        if(tablero[x][y+1] == 'T') trampaCerca = true;
    }

    cout << "\n--- PERCEPCIONES ---\n";

    if(gatoCerca)
        cout << "🐱 Hay un gato cerca\n";

    if(trampaCerca)
        cout << "⚠️ Hay una trampa cerca\n";

    if(!gatoCerca && !trampaCerca)
        cout << "✔️ No hay peligro cercano\n";

    cout << "--------------------\n";
}

// Mostrar acción
void mostrarAccion(char mov) {
    cout << "\n--- ACCION ---\n";
    cout << "Movimiento: " << mov << endl;
    cout << "Total acciones: " << acciones << endl;
    cout << "----------------\n";
}

int main() {
    srand(time(0));

    inicializar();
    colocarGatos();
    colocarTrampas();
    colocarQueso();

    cout << "🐭 JUEGO RATON COME QUESO\n";

    while(juegoActivo) {
        imprimirTablero();

        char mov;
        cout << "\nMovimiento (w/a/s/d): ";
        cin >> mov;

        moverRaton(mov);
        evaluarCasilla();
        detectarAlertas(ratonX, ratonY);
        mostrarAccion(mov);
    }

    cout << "\nJuego terminado en " << acciones << " acciones.\n";

    return 0;
}