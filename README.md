# Libasm

[![Assembly](https://img.shields.io/badge/Language-x86__64_ASM-6E4C13?style=for-the-badge&logo=assembly&logoColor=white)](https://en.wikipedia.org/wiki/X86-64)
[![NASM](https://img.shields.io/badge/Assembler-NASM-CC0000?style=for-the-badge)](https://nasm.us/)
[![42School](https://img.shields.io/badge/School-42_Barcelona-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr/)
[![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)](https://github.com/samuelhm/libasm)

[![Intel Syntax](https://img.shields.io/badge/Syntax-Intel-blue?style=flat-square)]()
[![Syscalls](https://img.shields.io/badge/Concept-Syscalls-orange?style=flat-square)]()
[![Calling Convention](https://img.shields.io/badge/ABI-System_V_AMD64-green?style=flat-square)]()
[![Low Level](https://img.shields.io/badge/Skill-Low_Level_Programming-red?style=flat-square)]()

---

## Descripcion

Implementacion en **x86-64 assembly** de funciones esenciales de la biblioteca estandar de C, escritas con sintaxis Intel y compiladas con NASM. El proyecto introduce la programacion a bajo nivel: registros, syscalls, calling conventions, manejo manual de stack y acceso directo al kernel de Linux.

La parte bonus extiende la libreria con conversion de bases numericas y operaciones sobre listas enlazadas, demostrando manejo avanzado de punteros y llamadas a funciones como callbacks desde assembly.

---

## Caracteristicas Principales

### Mandatory -- Funciones de libc

| Funcion | Descripcion |
|---------|-------------|
| `ft_strlen` | Longitud de cadena |
| `ft_strcpy` | Copia de cadena |
| `ft_strcmp` | Comparacion de cadenas |
| `ft_write` | Escritura sobre file descriptor (syscall) |
| `ft_read` | Lectura desde file descriptor (syscall) |
| `ft_strdup` | Duplicacion de cadena (via malloc) |

### Bonus -- Utilidades adicionales

| Funcion | Descripcion |
|---------|-------------|
| `ft_atoi_base` | Conversion de string a entero en base arbitraria |
| `ft_list_push_front` | Inserta nodo al inicio de lista enlazada |
| `ft_list_size` | Cuenta elementos de lista enlazada |
| `ft_list_sort` | Ordena lista enlazada con funcion de comparacion |
| `ft_list_remove_if` | Elimina nodos que cumplan condicion |

---

## Stack Tecnologico

| Categoria | Tecnologia |
|-----------|------------|
| Lenguaje | x86-64 Assembly (Intel syntax) |
| Assembler | NASM |
| Compilador C | GCC |
| Build System | Makefile |
| Syscalls | Linux x86-64 (write, read) |
| ABI | System V AMD64 |
| Enlazado | Biblioteca estatica (`libasm.a`) |

---

## Decisiones Tecnicas

### Syscalls y errno

Las funciones `ft_write` y `ft_read` invocan directamente al kernel mediante la instruccion `syscall`. Cuando el kernel devuelve un error (valor negativo en `rax`), el codigo lo niega para obtener el codigo de error POSIX y lo almacena en `errno` a traves de `__errno_location`. Esto garantiza compatibilidad con `perror()` y `strerror()`.

### Manejo de registros volatiles

En las funciones que llaman a `malloc`, `free` o callbacks (`ft_strdup`, `ft_list_sort`, `ft_list_remove_if`), se preservan los registros callee-saved (`r12`-`r15`, `rbp`) y se protegen los volatiles (`rdi`, `rsi`, `rcx`, `r10`, `r11`) mediante `push`/`pop` antes de cada `call`. La alineacion de stack a 16 bytes se mantiene en todo momento, requisito del ABI para llamadas a funciones de libc.

### Swap de datos en lugar de nodos

`ft_list_sort` implementa bubble sort intercambiando los punteros `data` de los nodos en lugar de reenlazar los punteros `next`. Esto simplifica el algoritmo en assembly sin alterar el resultado final de ordenacion.

---

## Instalacion

### Prerrequisitos

- NASM 2.15+
- GCC
- GNU Make
- Linux x86-64

### Compilacion

```bash
git clone https://github.com/samuelhm/libasm.git
cd libasm

# Parte mandatory
make

# Parte mandatory + bonus
make bonus

# Limpiar objetos
make clean

# Limpiar todo
make fclean

# Recompilar desde cero
make re
```

### Tests

```bash
# Ejecutar tests de la parte mandatory
make && ./programa

# Ejecutar tests de la parte bonus
make bonus && ./programa_bonus
```

---

## Estructura del Proyecto

```
libasm/
├── ft_strlen.s                    # Longitud de cadena
├── ft_strcpy.s                    # Copia de cadena
├── ft_strcmp.s                    # Comparacion de cadenas
├── ft_write.s                     # Escritura (syscall)
├── ft_read.s                      # Lectura (syscall)
├── ft_strdup.s                    # Duplicacion (malloc + ft_strcpy)
├── ft_atoi_base_bonus.s           # Conversion con base arbitraria
├── ft_list_push_front_bonus.s     # Insercion en lista
├── ft_list_size_bonus.s           # Conteo de elementos
├── ft_list_sort_bonus.s           # Ordenacion de lista
├── ft_list_remove_if_bonus.s      # Eliminacion condicional
├── main.c                         # Tests mandatory (vs libc)
├── main_bonus.c                   # Tests bonus
├── Makefile                       # Sistema de build
└── docs/                          # Documentacion de referencia
```

---

## Contacto

**Samuel Hurtado Marin**

[![GitHub](https://img.shields.io/badge/GitHub-samuelhm-181717?style=flat-square&logo=github)](https://github.com/samuelhm/)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-shurtado--m-0A66C2?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/shurtado-m/)

---

*Proyecto desarrollado como parte del curriculum de 42 Barcelona, introduciendo los fundamentos del lenguaje ensamblador y la interaccion directa con el kernel.*
