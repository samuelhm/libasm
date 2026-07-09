# NASM Intel - Sintaxis para Linux x86_64

[Referencia Rapida](common.md) | [NASM Intel](nasm.md) | [Registros](registers.md) | [Syscalls](syscalls.md)

---

## Introducción y Sintaxis Básica

**NASM** (Netwide Assembler) es un ensamblador para x86 que usa la sintaxis **Intel**, donde el *destino va primero*. Se compila con:

    $ nasm -f elf64 archivo.asm -o archivo.o
    $ ld archivo.o -o programa
    $ ./programa

**Intel vs AT&T**:

    ; Sintaxis Intel (NASM) - destino primero
    mov rax, 42
    add rax, rbx
    ; Sintaxis AT&T (GAS) - origen primero, sufijos de tamaño
    ; movq $42, %rax
    ; addq %rbx, %rax

**Comentarios**: punto y coma `;` hasta fin de línea.

**Literales numéricos**:

    mov rax, 100           ; decimal
    mov rax, 0x100          ; hexadecimal
    mov rax, 100b           ; binario (NASM)
    mov rax, 0100o          ; octal
    mov rax, `'a`           ; carácter ASCII
    mov rax, `Hola`         ; cadena de 4 bytes en little-endian

**Tamaños de operandos**: NASM detecta el tamaño por el nombre del registro o por los especificadores `BYTE`, `WORD`, `DWORD` o `QWORD`.

    mov al, 10              ; 8 bits (registro AL)
    mov ax, 10              ; 16 bits (registro AX)
    mov eax, 10             ; 32 bits (registro EAX)
    mov rax, 10             ; 64 bits (registro RAX)
    mov BYTE  [rbx], 10        ; forzar 8 bits en memoria
    mov DWORD [rbx], 10       ; forzar 32 bits en memoria

**Direccionamiento de memoria**: siempre con corchetes `[ ]`.

    mov rax, [rbx]                ; [rbx]
    mov rax, [rbx + 8]            ; [rbx+8], desplazamiento
    mov rax, [rbx + rcx*4]         ; [rbx+rcx*4], escalado
    mov rax, [rbx + rcx*8 + 16]    ; base + índice*escala + desplazamiento

**Símbolos especiales**:

- `$` - dirección de la línea actual
- `$$` - dirección de inicio de la sección actual
- `$ + n` - desplazamiento desde línea actual

Directivas de Sección y Estructura

Estas palabras le dicen a NASM cómo organizar el archivo objeto para que el enlazador (`ld`) y el kernel de Linux sepan qué va en cada sitio.

Secciones que uso al programar (lo demás lo genera el enlazador, no me preocupo):

| Sección | Descripción |
|----|----|
| `.text` | Código ejecutable. Aquí van todas mis instrucciones. |
| `.data` | Variables inicializadas (con valor conocido en el binario). Ocupan espacio en disco. |
| `.bss` | Variables sin inicializar. **No ocupan espacio en el binario**, solo en RAM al cargar (rellenadas a 0). Usar siempre que se pueda: ahorra espacio en el ejecutable. |
| `.rodata` | Constantes, mensajes, tablas de búsqueda, formatos. Solo lectura. Se carga en la misma página que `.text` (más caché). |

Layout típico en memoria de un ejecutable ELF64 Linux:

    ; Direcciones virtuales altas (0x7fff...)
    ;    [stack]  ->  crece hacia abajo (RSP)
    ;
    ;    [vsyscall/vDSO]
    ;    [mmap, brk]
    ;
    ;    [shared libraries cargadas]
    ;
    ; Direcciones bajas (0x400000 aprox. en x86_64)
    ;    [.text]      - código, ejecutable, solo lectura
    ;    [.rodata]    - constantes, solo lectura
    ;    [.data]      - variables inicializadas, lectura/escritura
    ;    [.bss]       - variables sin inicializar, lectura/escritura (0)
    ;    [heap]  ->  crece hacia arriba (brk/mmap)

Ver las secciones de un binario con `readelf`:

    $ readelf -S programa              ; muestra todas las secciones
    $ readelf -l programa              ; muestra los segmentos (program headers)
    $ objdump -h programa              ; muestra secciones con tamaños
    $ size programa                    ; tamaño de .text, .data, .bss
    $ nm programa                      ; lista símbolos de .symtab

## Directivas de Datos

Ejemplo de uso de directivas de datos:

    section .data
        msg    db "Hola, mundo", 10     ; cadena + salto de l\u00ednea (ASCII 10)
        msglen equ $ - msg             ; longitud de msg (12 bytes)
        nums   dd 100, 200, 300           ; array de 3 dword
        big    dq 0x0080402001000080    ; qword 64 bits (little-endian)
    ; Little-endian: 0x0080402001000080 se almacena en memoria como
    ; bytes 80 00 00 01 00 20 40 80  (el byte menos significativo primero)
    section .bss
        buffer  resb 1024              ; 1024 bytes sin inicializar
        tabla  resq 100                ; 100 quadwords (800 bytes)
        contador resd 1                 ; 1 dword (4 bytes)
    section .rodata
        fmt    db "Resultado: %d", 10, 0   ; solo lectura (en .rodata)

## Preprocesador y Macros

Ejemplo de macros multi-línea:

    ; Macro para imprimir una cadena por syscall write
    %macro print_str 1
        mov rax, 1              ; syscall write
        mov rdi, 1              ; stdout
        mov rsi, %1              ; puntero a la cadena
        mov rdx, 8              ; longitud (s\u00f3lo un ejemplo)
        syscall
    %endmacro
    ; Uso:
    section .data
        saludo db "Hola", 10
    section .text
        print_str saludo

Instrucciones de Movimiento de Datos

## Instrucciones Aritméticas

| Instrucción | Descripción | Ejemplo |
|----|----|----|
| `add dst, src` | Suma: `dst = dst + src`. Flags: OF, SF, ZF, AF, CF, PF. | `add rax, rbx` |
| `sub dst, src` | Resta: `dst = dst - src`. | `sub rsp, 16` |
| `adc dst, src` | Suma con acarreo: `dst = dst + src + CF`. Para aritmética de más de 64 bits. | `adc rdx, rcx` |
| `sbb dst, src` | Resta con acarreo: `dst = dst - src - CF`. | `sbb rax, rbx` |
| `inc dst` | Incrementa en 1 (no afecta CF). | `inc rax` |
| `dec dst` | Decrementa en 1 (no afecta CF). | `dec rcx` |
| `neg dst` | Niega (complemento a 2): `dst = -dst`. | `neg rax` |
| `mul src` | Multiplicación **sin signo**: `RAX = RAX * src` (8/16/32/64 bits). Resultado de doble ancho en `RDX:RAX`. | `mul rbx` |
| `imul src` | Multiplicación **con signo**. | `imul rbx` |
| `imul dst, src` | Multiplica `dst * src`, resultado en `dst` (mismo tamaño). | `imul rax, rbx` |
| `imul dst, src1, src2` | `dst = src1 * src2`. | `imul rax, rbx, 10` |
| `div src` | División **sin signo**: divide `RDX:RAX` por `src`. Cociente en `RAX`, resto en `RDX`. | `div rbx` |
| `idiv src` | División **con signo**. | `idiv rbx` |
| `cdq` | Extiende el signo de `EAX` a `EDX:EAX` (32 bits). | `cdq` |
| `cqo` | Extiende el signo de `RAX` a `RDX:RAX` (64 bits). | `cqo` |
| `cdqe` | Extiende el signo de `EAX` a `RAX`. | `cdqe` |
| `cbw` / `cwde` | Extensiones de signo de 8/16 bits a 16/32 bits. | `cwde` |

Instrucciones Lógicas y de Bits

| Instrucción | Descripción | Ejemplo |
|----|----|----|
| `and dst, src` | AND bit a bit. Flags: OF=CF=0, SF, ZF, PF. | `and rax, 0x0F` (máscara de 4 bits bajos) |
| `or dst, src` | OR bit a bit. | `or rax, 1` (setear bit 0) |
| `xor dst, src` | XOR bit a bit. `xor rax, rax` pone `rax = 0` de forma eficiente. | `xor rax, rax` |
| `not dst` | NOT bit a bit (invierte todos los bits). | `not rax` |
| `test dst, src` | AND sin guardar resultado. Solo afecta flags. Equivale a `cmp` contra 0. | `test al, al` (verifica si AL es 0) |
| `shl dst, n` | Desplazamiento lógico a la izquierda (equivale a `sal`). | `shl rax, 3` (multiplica por 8) |
| `shr dst, n` | Desplazamiento lógico a la derecha (rellena con 0). | `shr rax, 1` (divide por 2 sin signo) |
| `sal dst, n` | Desplazamiento aritmético a la izquierda (idéntico a `shl`). | `sal rax, 1` |
| `sar dst, n` | Desplazamiento aritmético a la derecha (rellena con bit de signo). | `sar rax, 1` (divide por 2 con signo) |
| `rol dst, n` | Rotación a la izquierda. | `rol rax, 8` |
| `ror dst, n` | Rotación a la derecha. | `ror rax, 8` |
| `rcl dst, n` | Rotación a la izquierda con CF. | `rcl rax, 1` |
| `rcr dst, n` | Rotación a la derecha con CF. | `rcr rax, 1` |
| `bt base, idx` | Test bit: `CF = bit idx de base`. | `bt rax, 5` |
| `bts base, idx` | Test and set. | `bts [rbx], 3` |
| `btr base, idx` | Test and reset. | `btr rax, 7` |
| `btc base, idx` | Test and complement. | `btc rax, 9` |
| `bsf dst, src` | Bit scan forward: encuentra el primer bit a 1 (hacia el LSB). | `bsf rax, rbx` |
| `bsr dst, src` | Bit scan reverse: primer bit a 1 hacia el MSB. | `bsr rax, rbx` |
| `popcnt dst, src` | Cuenta bits a 1 (popcount). Requiere SSE4.2. | `popcnt rax, rbx` |
| `lzcnt dst, src` | Cuenta ceros a la izquierda. Requiere LZCNT. | `lzcnt rax, rbx` |
| `tzcnt dst, src` | Cuenta ceros a la derecha. Equivale a `bsf`. Requiere BMI1. | `tzcnt rax, rbx` |

## Comparación y Saltos Condicionales

Todas las instrucciones de salto (`jXX`) leen los **flags** que dejó la última operación que modificó flags (`cmp`, `test`, `add`, `sub`, etc.).

| Instrucción | Descripción | Ejemplo |
|----|----|----|
| `cmp rax, rbx` | Compara `rax - rbx` y actualiza flags. No guarda el resultado. | `cmp rax, rbx` |
| `test rax, rbx` | AND sin guardar. `test rax, rax` verifica si `rax = 0`. | `test rax, rax` |
| `jmp etiqueta` | Salto **incondicional**. | `jmp .mi_etiqueta` |

Tras una instrucción que modifica flags (`cmp`, `test`, `add`, `sub`, etc.), los saltos leen esos flags. Los ejemplos siguientes asumen `cmp rax, rbx`.

Saltos condicionales **sin signo** (tras `cmp rax, rbx`):

| Salto | Salta si... | Equivale a... |
|----|----|----|
| `je / jz` | `rax == rbx` | Equal / Zero (ZF=1) |
| `jne / jnz` | `rax != rbx` | Not equal / Not zero (ZF=0) |
| `ja` / `jnbe` | `rax > rbx` *(sin signo)* | Above (CF=0 y ZF=0) |
| `jae` / `jnb` / `jnc` | `rax >= rbx` | Above or equal (CF=0) |
| `jb` / `jnae` / `jc` | `rax  rbx` (con signo) | ZF=0 y SF=OF |
| `jge` / `jnl` | `rax >= rbx`            | SF=OF        |
| `jl` / `jnge` | `rax < rbx`             | SF≠OF        |
| `jle` / `jng` | `rax <= rbx`            | ZF=1 o SF≠OF |

Saltos por flag individual:

| Salto         | Salta si...                      |
|---------------|----------------------------------|
| `jc` / `jb`   | CF=1 (acarreo / menor sin signo) |
| `jnc` / `jae` | CF=0 (sin acarreo)               |
| `jz` / `je`   | ZF=1 (resultado cero)            |
| `jnz` / `jne` | ZF=0 (no cero)                   |
| `js`          | SF=1 (signo negativo)            |
| `jns`         | SF=0 (signo positivo o cero)     |
| `jo`          | OF=1 (overflow)                  |
| `jno`         | OF=0 (sin overflow)              |
| `jp` / `jpe`  | PF=1 (paridad par)               |
| `jnp` / `jpo` | PF=0 (paridad impar)             |

## Bucles e Iteraciones

| Instrucción | Descripción | Ejemplo |
|----|----|----|
| `loop etiqueta` | Decrementa `RCX` y salta si no es cero. Equivale a `dec rcx; jnz etiqueta`. | `loop .bucle` |
| `loope` / `loopz` | Decrementa `RCX` y salta si no es cero *y* ZF=1. | `loope .bucle` |
| `loopne` / `loopnz` | Decrementa `RCX` y salta si no es cero *y* ZF=0. | `loopne .bucle` |
| `jrcxz etiqueta` | Salta si `RCX = 0` (sin decrementar). Para bucles con contador inicial a 0. | `jrcxz .fin` |

Patrón típico de bucle con NASM (cuenta regresiva de 10 a 1):

    mov rcx, 10            ; contador inicial (10 iteraciones)
    .bucle:
        ; ... cuerpo del bucle ...
        loop .bucle              ; rcx--; salta a .bucle si rcx != 0
        ; al salir, rcx == 0
    ; Variante: salto al final si el contador empieza en 0
    jrcxz .fin               ; salta si rcx == 0
    .bucle:
        ; ... cuerpo ...
        loop .bucle
    .fin:

Llamadas a Funciones y Syscalls

| Instrucción | Descripción | Ejemplo |
|----|----|----|
| `call etiqueta` | Salta a la función guardando la dirección de retorno en la pila (`RSP`). | `call mi_funcion` |
| `ret` | Retorna de la función: `RIP = [RSP]; RSP += 8`. | `ret` |
| `syscall` | Invoca una **syscall de Linux**. Número en `RAX`, args en `RDI, RSI, RDX, R10, R8, R9`. Retorno en `RAX` (o `-errno`). | `mov rax, 60; xor rdi, rdi; syscall` (exit(0)) |
| `sysenter` | Syscall rápida (32 bits principalmente, raramente usado en x86_64 moderno). | `sysenter` |
| `int 0x80` | Llamada al sistema vía **interrupción 0x80** (32 bits, legada). En x86_64 usar `syscall`. | `int 0x80` |

Convención de syscall Linux x86_64:

- **RAX** = número de syscall
- **RDI** = arg1
- **RSI** = arg2
- **RDX** = arg3
- **R10** = arg4 (no RCX, ya destruido por `syscall`)
- **R8** = arg5
- **R9** = arg6
- **RAX** = retorno (0 o ≥0 = éxito, -errno en error)
- **RCX** y **R11** son destruidos por `syscall`

Pila (Stack)

Convención de llamada System V AMD64 (x86_64 Linux):

- Argumentos **enteros**: `RDI, RSI, RDX, RCX, R8, R9`
- Argumentos **flotantes**: `XMM0-XMM7`
- Retorno en `RAX` (enteros) o `XMM0` (flotantes)
- Registros **preservados por la función** (callee-saved): `RBX, RBP, R12-R15, RSP`
- Registros **volátiles** (caller-saved): `RAX, RCX, RDX, RSI, RDI, R8-R11`
- El frame se alinea a 16 bytes antes de la instrucción `call` (es decir, `RSP ≡ 0 (mod 16)` al entrar a la función).

Esqueleto clásico de función:

    global mi_funcion
    mi_funcion:
        push rbp              ; guarda el frame pointer
        mov  rbp, rsp          ; nuevo frame pointer
        push rbx              ; guarda registros callee-saved
        sub  rsp, 16          ; reserva 16 bytes de locales
        ; ... código de la función ...
        ; usar rax para el retorno
        add rsp, 16           ; libera locales
        pop rbx               ; restaura registros
        pop rbp               ; restaura frame pointer
        ret                   ; retorna (RSP += 8)

## Compilación y Buenas Prácticas

Comandos de ensamblado y enlazado:

    ; Ensamblar a objeto ELF64
    $ nasm -f elf64 archivo.asm -o archivo.o
    ; Enlazar a ejecutable (solo _start, sin libc)
    $ ld archivo.o -o programa
    ; O con gcc (permite usar extern, printf, etc.)
    $ gcc archivo.o -o programa
    ; Ensamblar, enlazar y ejecutar
    $ nasm -f elf64 archivo.asm -o archivo.o && ld archivo.o -o prog && ./prog
    ; Debugging con GDB
    $ nasm -f elf64 -g archivo.asm -o archivo.o
    $ ld archivo.o -o prog
    $ gdb ./prog

Buenas prácticas:

- **Documenta** con `;` cada sección, cada syscall y cada lógica no trivial.
- **Usa `equ`** para números mágicos: `STDIN equ 0`, `STDOUT equ 1`, `SYSCALL_WRITE equ 1`.
- **Guarda y restaura** registros callee-saved (`RBX, RBP, R12-R15`) en funciones.
- **Alinea la pila** a 16 bytes antes de `call` en x86_64 System V (importante para SSE/AVX).
- **Verifica retornos** de syscall: si `RAX` es negativo (≥ `0x8000000000000000`), es un error; el valor absoluto es `errno`.
- **Evita `int 0x80`** en x86_64; usa `syscall` (es más rápido y la convención de argumentos es `R10` en vez de `RCX`).
- **`xor reg, reg`** es más eficiente que `mov reg, 0` (ocupa menos bytes).
- **Usa `syscall` solo en núcleo**: para programas con libc, usa las funciones de C (`printf`, `scanf`, etc.) y enlaza con `gcc`.
