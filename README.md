# 🐭 Ratón Come Queso - Simulación de Agente Inteligente en C++

## 📌 Descripción del Proyecto

Este proyecto consiste en la simulación de un agente inteligente (ratón) que interactúa con un entorno parcialmente observable, con el objetivo de encontrar un queso evitando peligros como gatos y trampas.

El sistema fue desarrollado en lenguaje C++ utilizando programación estructurada, sin uso de programación orientada a objetos ni librerías avanzadas, cumpliendo con las restricciones académicas.

---

## 🧠 Características principales

- ✔️ Tablero de 10 filas x 11 columnas
- ✔️ Posicionamiento aleatorio de elementos:
  - 5 gatos 🐱
  - 4 trampas ⚠️
  - 1 queso 🧀
- ✔️ Agente inicia en la esquina superior derecha
- ✔️ Movimiento controlado por el usuario (W, A, S, D)
- ✔️ Sistema de percepciones (detección de peligros cercanos)
- ✔️ Conteo de acciones realizadas
- ✔️ Registro de movimientos
- ✔️ Finalización por victoria o derrota

---

## 🔥 Modo ULTRA PRO

El sistema implementa un entorno **parcialmente observable**, donde:

- ❌ El usuario NO puede ver directamente gatos, trampas o queso
- ✔️ Solo recibe percepciones del entorno
- ✔️ El agente construye un mapa parcial del entorno

Esto simula el comportamiento de un agente inteligente en condiciones reales.

---

## 🎮 Controles del juego

| Tecla | Acción       |
|------|-------------|
| W    | Arriba      |
| S    | Abajo       |
| A    | Izquierda   |
| D    | Derecha     |

---

## ⚙️ Requisitos

- Compilador de C++ (g++)
- Terminal o consola

---

## ▶️ Cómo ejecutar el programa

1. Compilar el código:

```bash
g++ main.cpp -o juego

2. ejecutar el juego
./juego