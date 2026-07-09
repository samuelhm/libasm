# Referencia Rapida - ASM x86_64

[Referencia Rapida](common.md) | [NASM Intel](nasm.md) | [Registros](registers.md) | [Syscalls](syscalls.md)

---

## Registros de Propósito General

| 64 | 32 | Descripción | ¿Lo preservo? |
|----|----|----|----|
| `RAX` | `EAX` | Retorno de función / ID de syscall. | Volátil\* |
| `RDI` | `EDI` | 1.º argumento de función y syscall. | Volátil |
| `RSI` | `ESI` | 2.º argumento / puntero a buffer (`read`/`write`). | Volátil |
| `RDX` | `EDX` | 3.º argumento / longitud en `read`/`write`. | Volátil |
| `RCX` | `ECX` | 4.º argumento en C ABI / contador de bucles. En syscall es `R10`. | Volátil |
| `R8` | `R8D` | 5.º argumento en ABI y syscall. | Volátil |
| `R9` | `R9D` | 6.º argumento en ABI y syscall. | Volátil |
| `RBP` | `EBP` | Puntero al frame actual de la función. En `_start` lo inicializas a 0. | Preservado |
| `RBX` | `EBX` | Callee-saved para preservar valores entre llamadas. | Preservado |
| `R10` | `R10D` | 4.º argumento en **syscall** (en ABI normal no se usa). | Volátil\* |
| `R11` | `R11D` | Destruido por `syscall` (guarda `RFLAGS`). | Volátil\* |
| `R12-R15` | `R12D-R15D` | Callee-saved adicionales. Variables locales persistentes. Ideales para `i`, `contador`, `ptr`, etc. | Preservado |

**Volátil**: la función llamada puede modificarlo, así que si quieres conservar su valor debes guardarlo en la pila (`push`) antes de llamar y restaurarlo (`pop`) después.

**Volátil\***: serán siempre volátiles aunque intentes preservarlos - la función/syscall los machaca.

**Preservado**: la función llamada los guarda automáticamente según la ABI; no necesitas hacer `push`/`pop` tú mismo.

## Registros de Estado y Vectoriales

| Registro | Qué es | Cuándo lo uso |
|----|----|----|
| `RIP` | Instruction pointer: próxima instrucción a ejecutar. | Para PC-relative: `lea rax, [rel msg]`, `call [rel func]`. |
| `RFLAGS` | Banderas: ZF, SF, CF, OF, PF, IF, DF. | Tras `cmp`/`test` antes de un `jXX`. |
| `CR3` | Page table base (solo kernel). `0xC0000080` = `IA32_EFER` MSR. | No se accede desde usuario. |
| `XMM0-XMM7` | 128 bits para `float`/`double`/`__m128i`. Argumentos y retorno en C ABI. | Cuando paso/tengo `float` o `double`. |
| `XMM8-XMM15` | 128 bits extra (volátiles, no se usan en ABI). | SIMD local. |
| `FS base` | En Linux apunta al TLS del hilo actual. | Acceso a variables `__thread`. |

Top 25 Syscalls (las que uso siempre)

En orden de uso. `RDI, RSI, RDX, R10, R8, R9` para los argumentos; retorno en `RAX`.

| \# | Nombre | Argumentos | Retorno | Qué hace |
|----|----|----|----|----|
| 0 | read | `RDI`=fd, `RSI`=buf, `RDX`=count | `RAX`=bytes leídos o -errno | Lee `count` bytes del `fd` a `buf`. |
| 1 | write | `RDI`=fd, `RSI`=buf, `RDX`=count | `RAX`=bytes escritos o -errno | Escribe `count` bytes de `buf` al `fd`. |
| 2 | open | `RDI`=path, `RSI`=flags, `RDX`=mode | `RAX`=fd o -errno | Abre/crea archivo. `flags`: `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`, `O_TRUNC`, `O_APPEND`. |
| 3 | close | `RDI`=fd | `RAX`=0 o -errno | Cierra un descriptor. |
| 4 | stat | `RDI`=path, `RSI`=statbuf | `RAX`=0 o -errno | Metadatos por ruta. `statbuf` apunta a struct stat (~144 bytes). |
| 5 | fstat | `RDI`=fd, `RSI`=statbuf | `RAX`=0 o -errno | Metadatos por fd. |
| 8 | lseek | `RDI`=fd, `RSI`=offset, `RDX`=whence | `RAX`=nueva posición o -errno | Mueve el cursor. `whence`: 0=SET, 1=CUR, 2=END. |
| 9 | mmap | `RDI`=addr, `RSI`=len, `RDX`=prot, `R10`=flags, `R8`=fd, `R9`=offset | `RAX`=dir o -errno | Mapea memoria. `prot`: PROT_READ\|WRITE\|EXEC. `flags`: MAP_PRIVATE\|MAP_ANONYMOUS\|MAP_FIXED. |
| 10 | mprotect | `RDI`=addr, `RSI`=len, `RDX`=prot | `RAX`=0 o -errno | Cambia permisos de un mapeo. |
| 11 | munmap | `RDI`=addr, `RSI`=len | `RAX`=0 o -errno | Desmapea memoria. |
| 12 | brk | `RDI`=addr | `RAX`=nuevo brk o -errno | Ajusta el fin del segmento de datos (heap). Para `malloc` casero. |
| 16 | ioctl | `RDI`=fd, `RSI`=request, `RDX`=arg | `RAX`=depende o -errno | Operación de control sobre dispositivo (terminales, sockets, etc.). |
| 21 | access | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Comprueba permisos. `mode`: R_OK=4, W_OK=2, X_OK=1, F_OK=0. |
| 22 | pipe | `RDI`=fds\[2\] | `RAX`=0 o -errno | Crea un pipe. `fds[0]`=lectura, `fds[1]`=escritura. |
| 33 | dup2 | `RDI`=oldfd, `RSI`=newfd | `RAX`=newfd o -errno | Duplica `oldfd` en `newfd`. Usado para redireccionar stdin/stdout/stderr. |
| 35 | nanosleep | `RDI`=req, `RSI`=rem | `RAX`=0 o -errno | Duerme con precisión ns. `struct timespec` (tv_sec, tv_nsec). |
| 39 | getpid | (sin args) | `RAX`=pid | PID del proceso actual. |
| 41 | socket | `RDI`=domain, `RSI`=type, `RDX`=protocol | `RAX`=fd o -errno | Crea socket. AF_INET=2 (IPv4), AF_INET6=10. SOCK_STREAM=1, SOCK_DGRAM=2. |
| 42 | connect | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Conecta a servidor. |
| 43 | accept | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=fd o -errno | Acepta conexión entrante (server). |
| 49 | bind | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Asocia socket a puerto/dir local. |
| 50 | listen | `RDI`=fd, `RSI`=backlog | `RAX`=0 o -errno | Marca socket como pasivo (server). |
| 57 | fork | (sin args) | `RAX`=0 (hijo) o pid (padre) | Clona el proceso. |
| 59 | execve | `RDI`=path, `RSI`=argv, `RDX`=envp | nunca retorna si éxito | Reemplaza el proceso con uno nuevo. |
| 60 | exit | `RDI`=status | NO retorna | Termina el proceso. Solo el hilo. |
| 61 | wait4 | `RDI`=pid, `RSI`=wstatus, `RDX`=options, `R10`=rusage | `RAX`=pid del hijo o -errno | Espera al hijo. `pid=-1` = cualquier hijo. |
| 62 | kill | `RDI`=pid, `RSI`=sig | `RAX`=0 o -errno | Envía señal. `pid=0` = grupo, `pid=-1` = todos. |
| 228 | clock_gettime | `RDI`=clockid, `RSI`=tp | `RAX`=0 o -errno | Hora actual. `CLOCK_MONOTONIC`=1, `CLOCK_REALTIME`=0. |
| 231 | exit_group | `RDI`=status | NO retorna | Termina todos los hilos. Lo normal para salir. |

## Instrucciones que más uso

Selección reducida para tener siempre a mano. Para el listado completo mira `nasm.html`.

Secciones ELF64 (las que uso siempre)

## Errores comunes

- **Olvidar `global _start`** → el linker no encuentra el punto de entrada.
- **Olvidar `section .text`** → NASM no sabe dónde va el código.
- **Usar `RCX` en lugar de `R10`** como 4º argumento de `syscall` → `syscall` destruye `RCX`.
- **No guardar `RBX, RBP, R12-R15`** en una función → pierdes valores al retornar.
- **Desbalancear la pila** (un `push` sin `pop`) → crash en el `ret`.
- **Llamar a `int 0x80` en 64 bits** → usa la convención de 32 bits (RCX en lugar de R10).
- **Olvidar alinear la pila a 16 bytes** antes de `call` → crashea si la función llamada usa SSE/AVX.
- **Confundir `jz` y `je`** → son lo mismo, pero `je` se usa tras `cmp` y `jz` tras `test` (ambos miran ZF).
- **Confundir `ja` (sin signo) y `jg` (con signo)** → con números negativos `ja` falla.
- **No comprobar el retorno de `syscall`** → asumir éxito cuando fue error.
- **Pasar argumentos en `RCX` en syscall 64 bits** → es `R10`.
- **Olvidar `align 16` en `.bss`** para buffers que se pasarán a SIMD.
