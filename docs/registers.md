# Registros de Assembly - x86_64

[Referencia Rapida](common.md) | [NASM Intel](nasm.md) | [Registros](registers.md) | [Syscalls](syscalls.md)

---

## Registros de Propósito General

## Registros de Estado y Control

Registros Vectoriales y de Punto Flotante

## XMM / YMM / ZMM - Registros SIMD (128 / 256 / 512 bits)

| Registro | Tamaño | ABI System V |
|----|----|----|
| XMM0-XMM7 | 128 bits | Argumentos y retorno de punto flotante. Volátiles. |
| XMM8-XMM15 | 128 bits | Uso general SIMD. Volátiles. |
| YMM0-YMM15 | 256 bits | Superponen a XMM0-XMM15 (bits 255:128 por encima). AVX/AVX2. |
| ZMM0-ZMM31 | 512 bits | Superponen a YMM0-YMM15. AVX-512. ZMM16-ZMM31 solo en modo 64 bits. |
| MMX0-MMX7 | 64 bits | Alias de la mantisa de ST0-ST7 (FPU). Obsoleto, reemplazado por SSE. |
| ST0-ST7 | 80 bits | Pila de punto flotante x87. Obsoleto en x86_64; se prefiere SSE/AVX. |

Registros de Control del Sistema

Estos registros solo pueden ser leídos/escritos desde **anillo 0 (kernel)**. Un programa en espacio de usuario que intente acceder a ellos (p. ej. `MOV CR0, RAX`) provocará una excepción **\#GP(0)** (General Protection Fault).

| Registro | Propósito |
|----|----|
| CR0 | Control del modo de operación del procesador. Flags: PE (Protected Mode), MP, EM, TS, ET, NE, WP, AM, NW, CD, PG (Paging). |
| CR2 | Contiene la dirección lineal que causó un **Page Fault**. El kernel lo lee en el handler de \#PF para saber qué dirección falló. |
| CR3 | Puntero a la **Page Table de nivel superior** (PML4 en x86_64). Se recarga en cada cambio de contexto para cambiar el espacio de memoria virtual. |
| CR4 | Habilita extensiones arquitectónicas: PAE, PSE, PGE, OSFXSR, OSXMMEXCPT, UMIP, SMEP, SMAP, etc. |
| CR8 | **Task Priority Register**. Controla la prioridad de interrupción que acepta el procesador (solo en modo x86_64). |
