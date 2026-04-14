#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char tablero[10][11];     // mundo real
char visible[10][11];     // lo que el ratón ve

int ratonX = 0, ratonY = 10;
int acciones = 0;
bool juegoActivo = true;

// Inicializar
void inicializar() {
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            tablero[i][j] = '.';
            visible[i][j] = '?'; // desconocido
        }
    }
}

// Colocar elementos
void colocarElementos(char tipo, int cantidad) {
    int count = 0;
    while(count < cantidad) {
        int x = rand() % 10;
        int y = rand() % 11;

        if(tablero[x][y] == '.' && !(x == ratonX && y == ratonY)) {
            tablero[x][y] = tipo;
            count++;
        }
    }
}

// Imprimir mapa visible
void imprimirVisible() {
    cout << "\nMAPA DESCUBIERTO:\n";
    for(int i=0;i<10;i++){
        for(int j=0;j<11;j++){
            if(i == ratonX && j == ratonY)
                cout << "R ";
            else
                cout << visible[i][j] << " ";
        }
        cout << endl;
    }
}

// Movimiento
void moverRaton(char dir) {
    int nx = ratonX;
    int ny = ratonY;

    if(dir == 'w') nx--;
    else if(dir == 's') nx++;
    else if(dir == 'a') ny--;
    else if(dir == 'd') ny++;

    if(nx >= 0 && nx < 10 && ny >= 0 && ny < 11){
        ratonX = nx;
        ratonY = ny;
        acciones++;
    } else {
        cout << "Movimiento invalido\n";
    }
}

// Evaluar
void evaluarCasilla() {
    if(tablero[ratonX][ratonY] == 'G') {
        cout << "💀 Gato - Perdiste\n";
        juegoActivo = false;
    }
    else if(tablero[ratonX][ratonY] == 'T') {
        cout << "💀 Trampa - Perdiste\n";
        juegoActivo = false;
    }
    else if(tablero[ratonX][ratonY] == 'Q') {
        cout << "🎉 Queso encontrado - Ganaste\n";
        juegoActivo = false;
    }
}

// Percepciones + memoria
void percepciones() {
    bool gato = false, trampa = false;

    if(ratonX > 0){
        if(tablero[ratonX-1][ratonY]=='G') gato=true;
        if(tablero[ratonX-1][ratonY]=='T') trampa=true;
        visible[ratonX-1][ratonY] = '.';
    }
    if(ratonX < 9){
        if(tablero[ratonX+1][ratonY]=='G') gato=true;
        if(tablero[ratonX+1][ratonY]=='T') trampa=true;
        visible[ratonX+1][ratonY] = '.';
    }
    if(ratonY > 0){
        if(tablero[ratonX][ratonY-1]=='G') gato=true;
        if(tablero[ratonX][ratonY-1]=='T') trampa=true;
        visible[ratonX][ratonY-1] = '.';
    }
    if(ratonY < 10){
        if(tablero[ratonX][ratonY+1]=='G') gato=true;
        if(tablero[ratonX][ratonY+1]=='T') trampa=true;
        visible[ratonX][ratonY+1] = '.';
    }

    cout << "\nPERCEPCIONES:\n";
    if(gato) cout << "🐱 Gato cerca\n";
    if(trampa) cout << "⚠️ Trampa cerca\n";
    if(!gato && !trampa) cout << "✔️ Zona segura\n";
}

// Acción
void mostrarAccion(char mov) {
    cout << "\nMovimiento: " << mov;
    cout << " | Acciones: " << acciones << endl;
}

int main() {
    srand(time(0));

    inicializar();
    colocarElementos('G',5);
    colocarElementos('T',4);
    colocarElementos('Q',1);

    cout << "🐭 MODO ULTRA PRO ACTIVADO\n";
    cout << "Explora el mapa usando percepciones\n";

    while(juegoActivo) {
        imprimirVisible();

        char mov;
        cout << "\n(w/a/s/d): ";
        cin >> mov;

        moverRaton(mov);
        evaluarCasilla();
        percepciones();
        mostrarAccion(mov);
    }

    cout << "\nJuego terminado en " << acciones << " acciones\n";
    return 0;
}