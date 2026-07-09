# Syscalls Linux - x86_64

[Referencia Rapida](common.md) | [NASM Intel](nasm.md) | [Registros](registers.md) | [Syscalls](syscalls.md)

---

## Syscalls Esenciales

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 0 | read | `RDI`=fd, `RSI`=buf, `RDX`=count | `RAX`=bytes leídos o -errno | Lee hasta count bytes del fd hacia buf. |
| 1 | write | `RDI`=fd, `RSI`=buf, `RDX`=count | `RAX`=bytes escritos o -errno | Escribe hasta count bytes de buf al fd. |
| 2 | open | `RDI`=path, `RSI`=flags, `RDX`=mode | `RAX`=fd o -errno | Abre/crea un archivo. flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT… |
| 3 | close | `RDI`=fd | `RAX`=0 o -errno | Cierra un file descriptor. |
| 4 | stat | `RDI`=path, `RSI`=statbuf | `RAX`=0 o -errno | Obtiene metadatos de un archivo por ruta. |
| 5 | fstat | `RDI`=fd, `RSI`=statbuf | `RAX`=0 o -errno | Obtiene metadatos de un archivo por fd. |
| 6 | lstat | `RDI`=path, `RSI`=statbuf | `RAX`=0 o -errno | Como stat pero no sigue enlaces simbólicos. |
| 7 | poll | `RDI`=fds, `RSI`=nfds, `RDX`=timeout | `RAX`=nº listos o -errno | Espera eventos en múltiples fds. |
| 8 | lseek | `RDI`=fd, `RSI`=offset, `RDX`=whence | `RAX`=nueva posición o -errno | Reposiciona el cursor de lectura/escritura del fd. |
| 9 | mmap | `RDI`=addr, `RSI`=len, `RDX`=prot, `R10`=flags, `R8`=fd, `R9`=offset | `RAX`=dir mapeada o -errno | Mapea archivo o memoria anónima al espacio de direcciones. |
| 10 | mprotect | `RDI`=addr, `RSI`=len, `RDX`=prot | `RAX`=0 o -errno | Cambia permisos de una región de memoria. |
| 11 | munmap | `RDI`=addr, `RSI`=len | `RAX`=0 o -errno | Desmapea una región de memoria. |
| 12 | brk | `RDI`=addr | `RAX`=nuevo program break o -errno | Cambia el fin del segmento de datos (heap). |
| 13 | rt_sigaction | `RDI`=sig, `RSI`=act, `RDX`=oldact, `R10`=sigsetsize | `RAX`=0 o -errno | Instala/consulta un manejador de señal. |
| 14 | rt_sigprocmask | `RDI`=how, `RSI`=set, `RDX`=oldset, `R10`=sigsetsize | `RAX`=0 o -errno | Bloquea/desbloquea señales. |
| 16 | ioctl | `RDI`=fd, `RSI`=request, `RDX`=arg | `RAX`=depende o -errno | Operación de control sobre un dispositivo. |
| 17 | pread64 | `RDI`=fd, `RSI`=buf, `RDX`=count, `R10`=offset | `RAX`=bytes leídos o -errno | Lee en una posición sin modificar el cursor. |
| 18 | pwrite64 | `RDI`=fd, `RSI`=buf, `RDX`=count, `R10`=offset | `RAX`=bytes escritos o -errno | Escribe en una posición sin modificar el cursor. |
| 21 | access | `RDI`=path, `RSI`=mode | `RAX`=0 (accesible) o -errno | Comprueba permisos de acceso a un archivo. |
| 22 | pipe | `RDI`=fds\[2\] | `RAX`=0 o -errno | Crea un pipe unidireccional. fds\[0\]=lectura, fds\[1\]=escritura. |
| 23 | select | `RDI`=nfds, `RSI`=readfds, `RDX`=writefds, `R10`=exceptfds, `R8`=timeout | `RAX`=nº listos o -errno | Multiplexa E/S con timeout. |
| 24 | sched_yield | (sin args) | `RAX`=0 | Cede voluntariamente la CPU. |
| 32 | dup | `RDI`=oldfd | `RAX`=nuevo fd (mínimo disponible) | Duplica un fd. |
| 33 | dup2 | `RDI`=oldfd, `RSI`=newfd | `RAX`=newfd o -errno | Duplica oldfd exactamente en newfd. |
| 35 | nanosleep | `RDI`=req, `RSI`=rem | `RAX`=0 o -errno | Suspende el proceso con precisión de nanosegundos. |
| 39 | getpid | (sin args) | `RAX`=pid | Devuelve el PID del proceso actual. |
| 40 | sendfile | `RDI`=out_fd, `RSI`=in_fd, `RDX`=offset, `R10`=count | `RAX`=bytes enviados o -errno | Copia datos entre fds dentro del kernel sin pasar por usuario. |
| 41 | socket | `RDI`=domain, `RSI`=type, `RDX`=protocol | `RAX`=fd o -errno | Crea un socket. domain: AF_INET, AF_UNIX… type: SOCK_STREAM, SOCK_DGRAM… |
| 42 | connect | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Conecta un socket a una dirección remota. |
| 43 | accept | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=nuevo fd o -errno | Acepta una conexión entrante en un socket. |
| 44 | sendto | `RDI`=fd, `RSI`=buf, `RDX`=len, `R10`=flags, `R8`=dest_addr, `R9`=addrlen | `RAX`=bytes enviados o -errno | Envía datos a una dirección específica (UDP). |
| 45 | recvfrom | `RDI`=fd, `RSI`=buf, `RDX`=len, `R10`=flags, `R8`=src_addr, `R9`=addrlen | `RAX`=bytes recibidos o -errno | Recibe datos conociendo la dirección de origen. |
| 48 | shutdown | `RDI`=fd, `RSI`=how | `RAX`=0 o -errno | Cierra parcial o totalmente una conexión socket. |
| 49 | bind | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Asocia un socket a una dirección local. |
| 50 | listen | `RDI`=fd, `RSI`=backlog | `RAX`=0 o -errno | Marca un socket como pasivo para aceptar conexiones. |
| 56 | clone | `RDI`=flags, `RSI`=child_stack, `RDX`=ptid, `R10`=ctid, `R8`=tls | `RAX`=pid del hijo o -errno | Crea un nuevo proceso/hilo con control fino sobre qué se comparte. |
| 57 | fork | (sin args) | `RAX`=0 (hijo) o pid\>0 (padre) o -errno | Clona el proceso actual. Hijo idéntico con PID distinto. |
| 59 | execve | `RDI`=path, `RSI`=argv, `RDX`=envp | `RAX`=-errno (solo si falla) | Reemplaza el proceso actual con un nuevo programa. |
| 60 | exit | `RDI`=status | NO retorna | Termina el proceso actual. Solo el hilo llamador termina. |
| 61 | wait4 | `RDI`=pid, `RSI`=wstatus, `RDX`=options, `R10`=rusage | `RAX`=pid del hijo o -errno | Espera a que un hijo cambie de estado. |
| 62 | kill | `RDI`=pid, `RSI`=sig | `RAX`=0 o -errno | Envía una señal a un proceso. |
| 72 | fcntl | `RDI`=fd, `RSI`=cmd, `RDX`=arg | `RAX`=depende de cmd o -errno | Manipula atributos de un fd (bloqueo, flags, dup…). |
| 74 | fsync | `RDI`=fd | `RAX`=0 o -errno | Fuerza escritura a disco de datos y metadatos del fd. |
| 79 | getcwd | `RDI`=buf, `RSI`=size | `RAX`=buf o -errno | Devuelve el directorio de trabajo actual. |
| 80 | chdir | `RDI`=path | `RAX`=0 o -errno | Cambia el directorio de trabajo actual. |
| 83 | mkdir | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Crea un directorio. |
| 87 | unlink | `RDI`=path | `RAX`=0 o -errno | Elimina un nombre de archivo (y el archivo si es el último enlace). |
| 88 | symlink | `RDI`=target, `RSI`=linkpath | `RAX`=0 o -errno | Crea un enlace simbólico. |
| 89 | readlink | `RDI`=path, `RSI`=buf, `RDX`=bufsiz | `RAX`=bytes en buf o -errno | Lee el destino de un enlace simbólico. |
| 90 | chmod | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Cambia los permisos de un archivo. |
| 96 | gettimeofday | `RDI`=tv, `RSI`=tz | `RAX`=0 | Obtiene la hora actual (segundos + microsegundos). |
| 102 | getuid | (sin args) | `RAX`=uid real | UID real del proceso. |
| 103 | syslog | `RDI`=type, `RSI`=buf, `RDX`=len | `RAX`=depende de type o -errno | Lee/escribe el buffer de mensajes del kernel. |
| 104 | getgid | (sin args) | `RAX`=gid real | GID real del proceso. |
| 105 | setuid | `RDI`=uid | `RAX`=0 o -errno | Cambia el UID (real, efectivo y guardado). |
| 110 | getppid | (sin args) | `RAX`=ppid | Devuelve el PID del proceso padre. |
| 186 | gettid | (sin args) | `RAX`=tid | Devuelve el TID del hilo actual. |
| 201 | time | `RDI`=tloc | `RAX`=segundos desde epoch | Devuelve el tiempo en segundos desde 1970-01-01. |
| 202 | futex | `RDI`=uaddr, `RSI`=op, `RDX`=val, `R10`=timeout, `R8`=uaddr2, `R9`=val3 | `RAX`=depende de op | Primitiva de bloqueo rápida en espacio de usuario (base de mutex). |
| 213 | epoll_create | `RDI`=size | `RAX`=fd o -errno | Crea una instancia epoll para monitorizar múltiples fds. |
| 217 | getdents64 | `RDI`=fd, `RSI`=dirp, `RDX`=count | `RAX`=bytes leídos o -errno | Lee entradas de un directorio (versión 64 bits). |
| 228 | clock_gettime | `RDI`=clockid, `RSI`=tp | `RAX`=0 o -errno | Obtiene tiempo de un reloj específico con precisión de nanosegundos. |
| 231 | exit_group | `RDI`=status | NO retorna | Termina todos los hilos del proceso. |
| 232 | epoll_wait | `RDI`=epfd, `RSI`=events, `RDX`=maxevents, `R10`=timeout | `RAX`=nº eventos listos o -errno | Espera eventos en fds monitorizados por epoll. |
| 233 | epoll_ctl | `RDI`=epfd, `RSI`=op, `RDX`=fd, `R10`=event | `RAX`=0 o -errno | Añade/modifica/elimina fds en una instancia epoll. |
| 318 | getrandom | `RDI`=buf, `RSI`=buflen, `RDX`=flags | `RAX`=bytes escritos o -errno | Obtiene bytes aleatorios del kernel (entropía criptográfica). |

## Sistema de Archivos

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 2 | open | `RDI`=path, `RSI`=flags, `RDX`=mode | `RAX`=fd o -errno | Abre/crea un archivo |
| 3 | close | `RDI`=fd | `RAX`=0 o -errno | Cierra un fd |
| 4 | stat | `RDI`=path, `RSI`=statbuf | `RAX`=0 o -errno | Metadatos por ruta |
| 5 | fstat | `RDI`=fd, `RSI`=statbuf | `RAX`=0 o -errno | Metadatos por fd |
| 6 | lstat | `RDI`=path, `RSI`=statbuf | `RAX`=0 o -errno | Como stat sin seguir symlinks |
| 79 | getcwd | `RDI`=buf, `RSI`=size | `RAX`=buf o -errno | Directorio de trabajo actual |
| 80 | chdir | `RDI`=path | `RAX`=0 o -errno | Cambia directorio de trabajo |
| 81 | fchdir | `RDI`=fd | `RAX`=0 o -errno | Cambia directorio por fd |
| 82 | rename | `RDI`=oldpath, `RSI`=newpath | `RAX`=0 o -errno | Renombra/mueve archivo |
| 83 | mkdir | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Crea directorio |
| 84 | rmdir | `RDI`=pathname | `RAX`=0 o -errno | Elimina directorio vacío |
| 85 | creat | `RDI`=pathname, `RSI`=mode | `RAX`=fd o -errno | Crea/trunca archivo (obsoleto, usar open) |
| 86 | link | `RDI`=oldpath, `RSI`=newpath | `RAX`=0 o -errno | Crea enlace duro |
| 87 | unlink | `RDI`=path | `RAX`=0 o -errno | Elimina nombre de archivo |
| 88 | symlink | `RDI`=target, `RSI`=linkpath | `RAX`=0 o -errno | Crea enlace simbólico |
| 89 | readlink | `RDI`=path, `RSI`=buf, `RDX`=bufsiz | `RAX`=bytes o -errno | Lee destino de symlink |
| 90 | chmod | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Cambia permisos |
| 91 | fchmod | `RDI`=fd, `RSI`=mode | `RAX`=0 o -errno | Cambia permisos por fd |
| 92 | chown | `RDI`=path, `RSI`=owner, `RDX`=group | `RAX`=0 o -errno | Cambia propietario |
| 93 | fchown | `RDI`=fd, `RSI`=owner, `RDX`=group | `RAX`=0 o -errno | Cambia propietario por fd |
| 94 | lchown | `RDI`=path, `RSI`=owner, `RDX`=group | `RAX`=0 o -errno | chown sin seguir symlinks |
| 95 | umask | `RDI`=mask | `RAX`=máscara anterior | Máscara de permisos por defecto |
| 133 | mknod | `RDI`=pathname, `RSI`=mode, `RDX`=dev | `RAX`=0 o -errno | Crea nodo de dispositivo o FIFO |
| 257 | openat | `RDI`=dirfd, `RSI`=pathname, `RDX`=flags, `R10`=mode | `RAX`=fd o -errno | open relativo a un fd de directorio |
| 258 | mkdirat | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode | `RAX`=0 o -errno | mkdir relativo a un fd |
| 259 | mknodat | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode, `R10`=dev | `RAX`=0 o -errno | mknod relativo a un fd |
| 260 | fchownat | `RDI`=dirfd, `RSI`=pathname, `RDX`=owner, `R10`=group, `R8`=flags | `RAX`=0 o -errno | fchown relativo a un fd |
| 263 | unlinkat | `RDI`=dirfd, `RSI`=pathname, `RDX`=flags | `RAX`=0 o -errno | unlink relativo a un fd |
| 264 | renameat | `RDI`=olddirfd, `RSI`=oldpath, `RDX`=newdirfd, `R10`=newpath | `RAX`=0 o -errno | rename relativo a fds |
| 265 | linkat | `RDI`=olddirfd, `RSI`=oldpath, `RDX`=newdirfd, `R10`=newpath, `R8`=flags | `RAX`=0 o -errno | link relativo a fds |
| 266 | symlinkat | `RDI`=target, `RSI`=newdirfd, `RDX`=linkpath | `RAX`=0 o -errno | symlink relativo a un fd |
| 267 | readlinkat | `RDI`=dirfd, `RSI`=pathname, `RDX`=buf, `R10`=bufsiz | `RAX`=bytes o -errno | readlink relativo a un fd |
| 268 | fchmodat | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode, `R10`=flags | `RAX`=0 o -errno | chmod relativo a un fd |
| 269 | faccessat | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode, `R10`=flags | `RAX`=0 o -errno | access relativo a un fd |
| 280 | utimensat | `RDI`=dirfd, `RSI`=pathname, `RDX`=times, `R10`=flags | `RAX`=0 o -errno | Actualiza timestamps con precisión ns |
| 316 | renameat2 | `RDI`=olddirfd, `RSI`=oldpath, `RDX`=newdirfd, `R10`=newpath, `R8`=flags | `RAX`=0 o -errno | rename con flags (RENAME_NOREPLACE, RENAME_EXCHANGE) |
| 332 | statx | `RDI`=dirfd, `RSI`=pathname, `RDX`=flags, `R10`=mask, `R8`=statxbuf | `RAX`=0 o -errno | Metadatos extendidos de archivo |
| 437 | openat2 | `RDI`=dirfd, `RSI`=pathname, `RDX`=how, `R10`=size | `RAX`=fd o -errno | openat con control extendido (struct open_how) |
| 452 | fchmodat2 | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode, `R10`=flags | `RAX`=0 o -errno | fchmodat con flags (AT_SYMLINK_NOFOLLOW) |
| 21 | access | `RDI`=path, `RSI`=mode | `RAX`=0 o -errno | Comprueba permisos de acceso |
| 439 | faccessat2 | `RDI`=dirfd, `RSI`=pathname, `RDX`=mode, `R10`=flags | `RAX`=0 o -errno | faccessat con flags extendidos |
| 76 | truncate | `RDI`=path, `RSI`=length | `RAX`=0 o -errno | Trunca/extiende archivo a tamaño dado |
| 77 | ftruncate | `RDI`=fd, `RSI`=length | `RAX`=0 o -errno | Trunca/ extiende por fd |
| 285 | fallocate | `RDI`=fd, `RSI`=mode, `RDX`=offset, `R10`=len | `RAX`=0 o -errno | Preasigna espacio en disco |
| 187 | readahead | `RDI`=fd, `RSI`=offset, `RDX`=count | `RAX`=0 o -errno | Carga archivo en caché de páginas |
| 40 | sendfile | `RDI`=out_fd, `RSI`=in_fd, `RDX`=offset, `R10`=count | `RAX`=bytes o -errno | Copia directa entre fds |
| 326 | copy_file_range | `RDI`=fd_in, `RSI`=off_in, `RDX`=fd_out, `R10`=off_out, `R8`=len, `R9`=flags | `RAX`=bytes o -errno | Copia rango de bytes entre fds |
| 277 | sync_file_range | `RDI`=fd, `RSI`=offset, `RDX`=nbytes, `R10`=flags | `RAX`=0 o -errno | Sincroniza rango de un archivo a disco |
| 275 | splice | `RDI`=fd_in, `RSI`=off_in, `RDX`=fd_out, `R10`=off_out, `R8`=len, `R9`=flags | `RAX`=bytes o -errno | Mueve datos entre fds sin copia |
| 276 | tee | `RDI`=fd_in, `RSI`=fd_out, `RDX`=len, `R10`=flags | `RAX`=bytes o -errno | Duplica pipe a otro pipe |
| 278 | vmsplice | `RDI`=fd, `RSI`=iov, `RDX`=nr_segs, `R10`=flags | `RAX`=bytes o -errno | Mueve datos usuario↔pipe |
| 162 | sync | (sin args) | `RAX`=0 | Sincroniza todos los buffers a disco |
| 306 | syncfs | `RDI`=fd | `RAX`=0 o -errno | Sincroniza filesystem asociado al fd |
| 74 | fsync | `RDI`=fd | `RAX`=0 o -errno | Sincroniza datos+metadatos de un fd |
| 75 | fdatasync | `RDI`=fd | `RAX`=0 o -errno | Sincroniza solo datos (no metadatos) |
| 303 | name_to_handle_at | `RDI`=dirfd, `RSI`=pathname, `RDX`=handle, `R10`=mount_id, `R8`=flags | `RAX`=0 o -errno | Obtiene handle persistente de archivo |
| 304 | open_by_handle_at | `RDI`=mount_fd, `RSI`=handle, `RDX`=flags | `RAX`=fd o -errno | Abre archivo por handle |
| 436 | close_range | `RDI`=first, `RSI`=last, `RDX`=flags | `RAX`=0 o -errno | Cierra rango de fds de forma eficiente |
| 78 | getdents | `RDI`=fd, `RSI`=dirp, `RDX`=count | `RAX`=bytes o -errno | Lee entradas de directorio |
| 217 | getdents64 | `RDI`=fd, `RSI`=dirp, `RDX`=count | `RAX`=bytes o -errno | getdents con estructura de 64 bits |
| 137 | statfs | `RDI`=path, `RSI`=buf | `RAX`=0 o -errno | Estadísticas del filesystem |
| 138 | fstatfs | `RDI`=fd, `RSI`=buf | `RAX`=0 o -errno | statfs por fd |
| 132 | utime | `RDI`=filename, `RSI`=times | `RAX`=0 o -errno | Cambia timestamps de archivo |
| 235 | utimes | `RDI`=filename, `RSI`=times | `RAX`=0 o -errno | Cambia timestamps con microsegundos |
| 261 | futimesat | `RDI`=dirfd, `RSI`=pathname, `RDX`=times | `RAX`=0 o -errno | utimes relativo a un fd |
| 262 | newfstatat | `RDI`=dirfd, `RSI`=pathname, `RDX`=statbuf, `R10`=flags | `RAX`=0 o -errno | stat relativo a un fd con flags |
| 457 | statmount | `RDI`=mnt_id, `RSI`=flags, `RDX`=buf, `R10`=bufsize | `RAX`=0 o -errno | Info detallada de un punto de montaje |
| 458 | listmount | `RDI`=req, `RSI`=mnt_ids, `RDX`=nr_mnt_ids, `R10`=flags | `RAX`=nº o -errno | Lista puntos de montaje |
| 165 | mount | `RDI`=source, `RSI`=target, `RDX`=fstype, `R10`=mountflags, `R8`=data | `RAX`=0 o -errno | Monta filesystem |
| 166 | umount2 | `RDI`=target, `RSI`=flags | `RAX`=0 o -errno | Desmonta filesystem con flags |
| 155 | pivot_root | `RDI`=new_root, `RSI`=put_old | `RAX`=0 o -errno | Cambia el root filesystem |
| 161 | chroot | `RDI`=path | `RAX`=0 o -errno | Cambia el directorio raíz |
| 188 | setxattr | `RDI`=path, `RSI`=name, `RDX`=value, `R10`=size, `R8`=flags | `RAX`=0 o -errno | Establece atributo extendido |
| 189 | lsetxattr | `RDI`=path, `RSI`=name, `RDX`=value, `R10`=size, `R8`=flags | `RAX`=0 o -errno | setxattr sin seguir symlinks |
| 190 | fsetxattr | `RDI`=fd, `RSI`=name, `RDX`=value, `R10`=size, `R8`=flags | `RAX`=0 o -errno | setxattr por fd |
| 191 | getxattr | `RDI`=path, `RSI`=name, `RDX`=value, `R10`=size | `RAX`=bytes o -errno | Lee atributo extendido |
| 192 | lgetxattr | `RDI`=path, `RSI`=name, `RDX`=value, `R10`=size | `RAX`=bytes o -errno | getxattr sin seguir symlinks |
| 193 | fgetxattr | `RDI`=fd, `RSI`=name, `RDX`=value, `R10`=size | `RAX`=bytes o -errno | getxattr por fd |
| 194 | listxattr | `RDI`=path, `RSI`=list, `RDX`=size | `RAX`=bytes o -errno | Lista atributos extendidos |
| 195 | llistxattr | `RDI`=path, `RSI`=list, `RDX`=size | `RAX`=bytes o -errno | listxattr sin seguir symlinks |
| 196 | flistxattr | `RDI`=fd, `RSI`=list, `RDX`=size | `RAX`=bytes o -errno | listxattr por fd |
| 197 | removexattr | `RDI`=path, `RSI`=name | `RAX`=0 o -errno | Elimina atributo extendido |
| 198 | lremovexattr | `RDI`=path, `RSI`=name | `RAX`=0 o -errno | removexattr sin symlinks |
| 199 | fremovexattr | `RDI`=fd, `RSI`=name | `RAX`=0 o -errno | removexattr por fd |
| 463 | setxattrat | `RDI`=dirfd, `RSI`=pathname, `RDX`=name, `R10`=value, `R8`=size, `R9`=flags | `RAX`=0 o -errno | setxattr relativo a fd |
| 464 | getxattrat | `RDI`=dirfd, `RSI`=pathname, `RDX`=name, `R10`=value, `R8`=size | `RAX`=bytes o -errno | getxattr relativo a fd |
| 465 | listxattrat | `RDI`=dirfd, `RSI`=pathname, `RDX`=list, `R10`=size | `RAX`=bytes o -errno | listxattr relativo a fd |
| 466 | removexattrat | `RDI`=dirfd, `RSI`=pathname, `RDX`=name | `RAX`=0 o -errno | removexattr relativo a fd |
| 428 | open_tree | `RDI`=dfd, `RSI`=path, `RDX`=flags | `RAX`=fd o -errno | Abre árbol de montaje |
| 429 | move_mount | `RDI`=from_dfd, `RSI`=from_path, `RDX`=to_dfd, `R10`=to_path, `R8`=flags | `RAX`=0 o -errno | Mueve montaje |
| 430 | fsopen | `RDI`=fs_name, `RSI`=flags | `RAX`=fd o -errno | Abre contexto de filesystem |
| 431 | fsconfig | `RDI`=fd, `RSI`=cmd, `RDX`=key, `R10`=value, `R8`=aux | `RAX`=0 o -errno | Configura contexto de filesystem |
| 432 | fsmount | `RDI`=fs_fd, `RSI`=flags, `RDX`=ms_flags | `RAX`=0 o -errno | Monta desde contexto |
| 433 | fspick | `RDI`=dfd, `RSI`=path, `RDX`=flags | `RAX`=fd o -errno | Selecciona filesystem existente |
| 442 | mount_setattr | `RDI`=dfd, `RSI`=path, `RDX`=flags, `R10`=uattr, `R8`=usize | `RAX`=0 o -errno | Cambia atributos de montaje |
| 467 | open_tree_attr | `RDI`=dfd, `RSI`=path, `RDX`=flags, `R10`=uattr, `R8`=usize | `RAX`=fd o -errno | Atributos para open_tree |
| 468 | file_getattr | `RDI`=dfd, `RSI`=pathname, `RDX`=uattr, `R10`=usize, `R8`=flags | `RAX`=0 o -errno | Atributos de archivo |
| 469 | file_setattr | `RDI`=dfd, `RSI`=pathname, `RDX`=uattr, `R10`=usize, `R8`=flags | `RAX`=0 o -errno | Cambia atributos de archivo |
| 136 | ustat | `RDI`=dev, `RSI`=ubuf | `RAX`=0 o -errno | Estadísticas de filesystem (obsoleto) |
| 139 | sysfs | `RDI`=option, `RSI`=arg1, `RDX`=arg2 | `RAX`=0 o -errno | Info de tipos de filesystem |
| 179 | quotactl | `RDI`=cmd, `RSI`=special, `RDX`=id, `R10`=addr | `RAX`=0 o -errno | Control de cuotas de disco |
| 443 | quotactl_fd | `RDI`=fd, `RSI`=cmd, `RDX`=id, `R10`=addr | `RAX`=0 o -errno | quotactl por fd |
| 167 | swapon | `RDI`=path, `RSI`=swapflags | `RAX`=0 o -errno | Activa swap en dispositivo |
| 168 | swapoff | `RDI`=path | `RAX`=0 o -errno | Desactiva swap |
| 253 | inotify_init | (sin args) | `RAX`=fd o -errno | Crea instancia inotify |
| 294 | inotify_init1 | `RDI`=flags | `RAX`=fd o -errno | inotify_init con flags (IN_NONBLOCK, IN_CLOEXEC) |
| 254 | inotify_add_watch | `RDI`=fd, `RSI`=pathname, `RDX`=mask | `RAX`=wd o -errno | Añade watch a inotify |
| 255 | inotify_rm_watch | `RDI`=fd, `RSI`=wd | `RAX`=0 o -errno | Elimina watch de inotify |
| 300 | fanotify_init | `RDI`=flags, `RSI`=event_f_flags | `RAX`=fd o -errno | Crea instancia fanotify |
| 301 | fanotify_mark | `RDI`=fd, `RSI`=flags, `RDX`=mask, `R10`=dirfd, `R8`=pathname | `RAX`=0 o -errno | Marca archivos para fanotify |

## Memoria

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 9 | mmap | `RDI`=addr, `RSI`=len, `RDX`=prot, `R10`=flags, `R8`=fd, `R9`=offset | `RAX`=dir mapeada o -errno | Mapea archivo o memoria anónima |
| 10 | mprotect | `RDI`=addr, `RSI`=len, `RDX`=prot | `RAX`=0 o -errno | Cambia protección de memoria |
| 11 | munmap | `RDI`=addr, `RSI`=len | `RAX`=0 o -errno | Desmapea región |
| 12 | brk | `RDI`=addr | `RAX`=nuevo brk o -errno | Ajusta el fin de la heap (program break) |
| 25 | mremap | `RDI`=old_addr, `RSI`=old_len, `RDX`=new_len, `R10`=flags, `R8`=new_addr | `RAX`=nueva dir o -errno | Redimensiona/reamplía un mapeo |
| 26 | msync | `RDI`=addr, `RSI`=len, `RDX`=flags | `RAX`=0 o -errno | Sincroniza mmap con disco |
| 27 | mincore | `RDI`=addr, `RSI`=len, `RDX`=vec | `RAX`=0 o -errno | Comprueba si páginas están en RAM |
| 28 | madvise | `RDI`=addr, `RSI`=len, `RDX`=advice | `RAX`=0 o -errno | Aconseja al kernel sobre uso de memoria |
| 440 | process_madvise | `RDI`=pidfd, `RSI`=iov, `RDX`=iovcnt, `R10`=advice, `R8`=flags | `RAX`=bytes o -errno | madvise sobre otro proceso |
| 149 | mlock | `RDI`=addr, `RSI`=len | `RAX`=0 o -errno | Bloquea páginas en RAM |
| 150 | munlock | `RDI`=addr, `RSI`=len | `RAX`=0 o -errno | Desbloquea páginas |
| 151 | mlockall | `RDI`=flags | `RAX`=0 o -errno | Bloquea todo el espacio de direcciones |
| 152 | munlockall | (sin args) | `RAX`=0 | Desbloquea todo el espacio |
| 325 | mlock2 | `RDI`=addr, `RSI`=len, `RDX`=flags | `RAX`=0 o -errno | mlock con flags |
| 216 | remap_file_pages | `RDI`=addr, `RSI`=size, `RDX`=prot, `R10`=pgoff, `R8`=flags | `RAX`=0 o -errno | Reorganiza páginas de un mapeo (obsoleto) |
| 237 | mbind | `RDI`=addr, `RSI`=len, `RDX`=mode, `R10`=nodemask, `R8`=maxnode, `R9`=flags | `RAX`=0 o -errno | Política de memoria NUMA |
| 238 | set_mempolicy | `RDI`=mode, `RSI`=nodemask, `RDX`=maxnode | `RAX`=0 o -errno | Política NUMA por defecto |
| 239 | get_mempolicy | `RDI`=mode, `RSI`=nodemask, `RDX`=maxnode, `R10`=addr, `R8`=flags | `RAX`=0 o -errno | Consulta política NUMA |
| 450 | set_mempolicy_home_node | `RDI`=addr, `RSI`=len, `RDX`=home_node, `R10`=flags | `RAX`=0 o -errno | Nodo home para memoria |
| 256 | migrate_pages | `RDI`=pid, `RSI`=maxnode, `RDX`=old_nodes, `R10`=new_nodes | `RAX`=nº no migradas o -errno | Migra páginas entre nodos NUMA |
| 319 | memfd_create | `RDI`=name, `RSI`=flags | `RAX`=fd o -errno | Crea fd anónimo en memoria |
| 447 | memfd_secret | `RDI`=flags | `RAX`=fd o -errno | memfd no accesible por kernel |
| 329 | pkey_mprotect | `RDI`=addr, `RSI`=len, `RDX`=prot, `R10`=pkey | `RAX`=0 o -errno | mprotect con protection keys |
| 330 | pkey_alloc | `RDI`=flags, `RSI`=access_rights | `RAX`=pkey o -errno | Asigna protection key |
| 331 | pkey_free | `RDI`=pkey | `RAX`=0 o -errno | Libera protection key |
| 453 | map_shadow_stack | `RDI`=addr, `RSI`=size, `RDX`=flags | `RAX`=dir o -errno | Mapea shadow stack (CET) |
| 462 | mseal | `RDI`=addr, `RSI`=len, `RDX`=flags | `RAX`=0 o -errno | Sella rango de memoria (inmutable) |
| 451 | cachestat | `RDI`=addr, `RSI`=len, `RDX`=flags, `R10`=cstat | `RAX`=0 o -errno | Estadísticas de caché de páginas |

## Procesos e Hilos

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 39 | getpid | (sin args) | `RAX`=pid | PID del proceso |
| 110 | getppid | (sin args) | `RAX`=ppid | PID del padre |
| 186 | gettid | (sin args) | `RAX`=tid | TID del hilo actual |
| 56 | clone | `RDI`=flags, `RSI`=child_stack, `RDX`=ptid, `R10`=ctid, `R8`=tls | `RAX`=pid o -errno | Crea proceso/hilo (flags: CLONE_VM, CLONE_FS...) |
| 435 | clone3 | `RDI`=cl_args, `RSI`=size | `RAX`=pid o -errno | clone con estructura extendida |
| 57 | fork | (sin args) | `RAX`=0 o pid o -errno | Clona el proceso (copia todo) |
| 58 | vfork | (sin args) | `RAX`=0 o pid o -errno | fork con memoria compartida (obsoleto) |
| 59 | execve | `RDI`=path, `RSI`=argv, `RDX`=envp | `RAX`=-errno si falla | Ejecuta nuevo programa |
| 322 | execveat | `RDI`=dirfd, `RSI`=pathname, `RDX`=argv, `R10`=envp, `R8`=flags | `RAX`=-errno si falla | execve relativo a fd de directorio |
| 60 | exit | `RDI`=status | NO retorna | Termina el hilo actual |
| 231 | exit_group | `RDI`=status | NO retorna | Termina todos los hilos del proceso |
| 61 | wait4 | `RDI`=pid, `RSI`=wstatus, `RDX`=options, `R10`=rusage | `RAX`=pid o -errno | Espera cambio de estado de un hijo |
| 247 | waitid | `RDI`=idtype, `RSI`=id, `RDX`=infop, `R10`=options | `RAX`=0 o -errno | wait con más opciones |
| 62 | kill | `RDI`=pid, `RSI`=sig | `RAX`=0 o -errno | Envía señal a proceso |
| 200 | tkill | `RDI`=tid, `RSI`=sig | `RAX`=0 o -errno | Envía señal a un hilo específico |
| 234 | tgkill | `RDI`=tgid, `RSI`=tid, `RDX`=sig | `RAX`=0 o -errno | Envía señal a hilo de un thread group |
| 157 | prctl | `RDI`=option, `RSI`=arg2, `RDX`=arg3, `R10`=arg4, `R8`=arg5 | `RAX`=depende o -errno | Control de atributos del proceso |
| 158 | arch_prctl | `RDI`=code, `RSI`=addr | `RAX`=0 o -errno | Control de estado arquitectónico (FSBASE, GS...) |
| 135 | personality | `RDI`=persona | `RAX`=anterior o -errno | Cambia dominio de ejecución |
| 218 | set_tid_address | `RDI`=tidptr | `RAX`=tid | Dirección para notificar tid al hacer exit |
| 272 | unshare | `RDI`=flags | `RAX`=0 o -errno | Descomparte namespaces |
| 308 | setns | `RDI`=fd, `RSI`=nstype | `RAX`=0 o -errno | Entra en un namespace existente |
| 470 | listns | `RDI`=req, `RSI`=nr_nsid, `RDX`=nsid, `R10`=flags | `RAX`=0 o -errno | Lista namespaces |
| 309 | getcpu | `RDI`=cpu, `RSI`=node, `RDX`=tcache | `RAX`=0 | CPU y nodo NUMA actual |
| 24 | sched_yield | (sin args) | `RAX`=0 | Cede la CPU |
| 219 | restart_syscall | (sin args) | `RAX`=resultado | Reinicia syscall interrumpida (interno) |
| 334 | rseq | `RDI`=rseq, `RSI`=rseq_len, `RDX`=flags, `R10`=sig | `RAX`=0 o -errno | Restartable sequences (operaciones atómicas por CPU) |
| 471 | rseq_slice_yield | `RDI`=rseq, `RSI`=rseq_len | `RAX`=0 o -errno | Cede slice en rseq |
| 324 | membarrier | `RDI`=cmd, `RSI`=flags, `RDX`=cpu_id | `RAX`=0 o -errno | Barrera de memoria entre hilos |

Red - Sockets

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 41 | socket | `RDI`=domain, `RSI`=type, `RDX`=protocol | `RAX`=fd o -errno | Crea un socket |
| 53 | socketpair | `RDI`=domain, `RSI`=type, `RDX`=protocol, `R10`=fds\[2\] | `RAX`=0 o -errno | Crea par de sockets conectados |
| 42 | connect | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Conecta a dirección remota |
| 43 | accept | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=fd o -errno | Acepta conexión entrante |
| 288 | accept4 | `RDI`=fd, `RSI`=addr, `RDX`=addrlen, `R10`=flags | `RAX`=fd o -errno | accept con flags (SOCK_NONBLOCK, SOCK_CLOEXEC) |
| 49 | bind | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Asocia socket a dirección local |
| 50 | listen | `RDI`=fd, `RSI`=backlog | `RAX`=0 o -errno | Pone socket en modo pasivo |
| 44 | sendto | `RDI`=fd, `RSI`=buf, `RDX`=len, `R10`=flags, `R8`=dest_addr, `R9`=addrlen | `RAX`=bytes o -errno | Envía datos a dirección |
| 46 | sendmsg | `RDI`=fd, `RSI`=msg, `RDX`=flags | `RAX`=bytes o -errno | Envía datos con múltiples buffers |
| 307 | sendmmsg | `RDI`=fd, `RSI`=msgvec, `RDX`=vlen, `R10`=flags | `RAX`=nº o -errno | Envía múltiples mensajes en una llamada |
| 45 | recvfrom | `RDI`=fd, `RSI`=buf, `RDX`=len, `R10`=flags, `R8`=src_addr, `R9`=addrlen | `RAX`=bytes o -errno | Recibe datos con dirección de origen |
| 47 | recvmsg | `RDI`=fd, `RSI`=msg, `RDX`=flags | `RAX`=bytes o -errno | Recibe datos en múltiples buffers |
| 299 | recvmmsg | `RDI`=fd, `RSI`=msgvec, `RDX`=vlen, `R10`=flags, `R8`=timeout | `RAX`=nº o -errno | Recibe múltiples mensajes en una llamada |
| 48 | shutdown | `RDI`=fd, `RSI`=how | `RAX`=0 o -errno | Cierra parcial/totalmente la conexión |
| 51 | getsockname | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Dirección local del socket |
| 52 | getpeername | `RDI`=fd, `RSI`=addr, `RDX`=addrlen | `RAX`=0 o -errno | Dirección remota del socket |
| 54 | setsockopt | `RDI`=fd, `RSI`=level, `RDX`=optname, `R10`=optval, `R8`=optlen | `RAX`=0 o -errno | Configura opciones de socket |
| 55 | getsockopt | `RDI`=fd, `RSI`=level, `RDX`=optname, `R10`=optval, `R8`=optlen | `RAX`=0 o -errno | Consulta opciones de socket |

## Señales

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 13 | rt_sigaction | `RDI`=sig, `RSI`=act, `RDX`=oldact, `R10`=sigsetsize | `RAX`=0 o -errno | Instala/consulta manejador de señal |
| 14 | rt_sigprocmask | `RDI`=how, `RSI`=set, `RDX`=oldset, `R10`=sigsetsize | `RAX`=0 o -errno | Bloquea/desbloquea señales |
| 15 | rt_sigreturn | (sin args) | NO retorna | Retorna de manejador de señal (interno) |
| 127 | rt_sigpending | `RDI`=set, `RSI`=sigsetsize | `RAX`=0 o -errno | Señales pendientes |
| 128 | rt_sigtimedwait | `RDI`=set, `RSI`=info, `RDX`=timeout, `R10`=sigsetsize | `RAX`=sig o -errno | Espera señal con timeout |
| 129 | rt_sigqueueinfo | `RDI`=tgid, `RSI`=sig, `RDX`=info | `RAX`=0 o -errno | Envía señal con datos |
| 297 | rt_tgsigqueueinfo | `RDI`=tgid, `RSI`=tid, `RDX`=sig, `R10`=info | `RAX`=0 o -errno | rt_sigqueueinfo a hilo específico |
| 130 | rt_sigsuspend | `RDI`=set, `RSI`=sigsetsize | `RAX`=-errno | Suspende proceso hasta señal |
| 131 | sigaltstack | `RDI`=ss, `RSI`=old_ss | `RAX`=0 o -errno | Define pila alternativa para señales |
| 62 | kill | `RDI`=pid, `RSI`=sig | `RAX`=0 o -errno | Envía señal a proceso |
| 200 | tkill | `RDI`=tid, `RSI`=sig | `RAX`=0 o -errno | Envía señal a hilo |
| 234 | tgkill | `RDI`=tgid, `RSI`=tid, `RDX`=sig | `RAX`=0 o -errno | Envía señal a hilo de thread group |
| 282 | signalfd | `RDI`=fd, `RSI`=mask, `RDX`=sigsetsize, `R10`=flags | `RAX`=fd o -errno | Crea fd para recibir señales |
| 289 | signalfd4 | `RDI`=fd, `RSI`=mask, `RDX`=sigsetsize, `R10`=flags | `RAX`=fd o -errno | signalfd con flags |
| 34 | pause | (sin args) | `RAX`=-errno | Espera cualquier señal |

Tiempo y Temporizadores

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 35 | nanosleep | `RDI`=req, `RSI`=rem | `RAX`=0 o -errno | Suspende con precisión ns |
| 230 | clock_nanosleep | `RDI`=clockid, `RSI`=flags, `RDX`=request, `R10`=remain | `RAX`=0 o -errno | nanosleep usando un clockid |
| 96 | gettimeofday | `RDI`=tv, `RSI`=tz | `RAX`=0 o -errno | Hora actual (s + us) |
| 164 | settimeofday | `RDI`=tv, `RSI`=tz | `RAX`=0 o -errno | Cambia la hora del sistema (root) |
| 228 | clock_gettime | `RDI`=clockid, `RSI`=tp | `RAX`=0 o -errno | Tiempo de un reloj con precisión ns |
| 227 | clock_settime | `RDI`=clockid, `RSI`=tp | `RAX`=0 o -errno | Ajusta un reloj (root) |
| 229 | clock_getres | `RDI`=clockid, `RSI`=res | `RAX`=0 o -errno | Resolución de un reloj |
| 305 | clock_adjtime | `RDI`=clockid, `RSI`=tmx | `RAX`=estado o -errno | Ajusta dinámicamente reloj (NTP) |
| 201 | time | `RDI`=tloc | `RAX`=segundos desde epoch | Tiempo en segundos desde epoch |
| 100 | times | `RDI`=tms | `RAX`=clock ticks o -errno | Tiempos de CPU del proceso |
| 36 | getitimer | `RDI`=which, `RSI`=value | `RAX`=0 o -errno | Valor de un temporizador de intervalo |
| 38 | setitimer | `RDI`=which, `RSI`=new, `RDX`=old | `RAX`=0 o -errno | Configura temporizador de intervalo |
| 37 | alarm | `RDI`=seconds | `RAX`=segundos restantes | Programa SIGALRM en segundos |
| 222 | timer_create | `RDI`=clockid, `RSI`=evp, `RDX`=timerid | `RAX`=0 o -errno | Crea temporizador POSIX |
| 223 | timer_settime | `RDI`=timerid, `RSI`=flags, `RDX`=new_value, `R10`=old_value | `RAX`=0 o -errno | Arma/desarma temporizador |
| 224 | timer_gettime | `RDI`=timerid, `RSI`=curr_value | `RAX`=0 o -errno | Consulta tiempo restante |
| 225 | timer_getoverrun | `RDI`=timerid | `RAX`=overrun o -errno | Nº de expiraciones perdidas |
| 226 | timer_delete | `RDI`=timerid | `RAX`=0 o -errno | Elimina temporizador |
| 283 | timerfd_create | `RDI`=clockid, `RSI`=flags | `RAX`=fd o -errno | Crea fd de temporizador |
| 286 | timerfd_settime | `RDI`=fd, `RSI`=flags, `RDX`=new_value, `R10`=old_value | `RAX`=0 o -errno | Arma temporizador fd |
| 287 | timerfd_gettime | `RDI`=fd, `RSI`=curr_value | `RAX`=0 o -errno | Consulta temporizador fd |
| 159 | adjtimex | `RDI`=tmx | `RAX`=estado o -errno | Ajuste fino del reloj del kernel |

Usuarios, Grupos y Seguridad

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 102 | getuid | (sin args) | `RAX`=uid | UID real |
| 104 | getgid | (sin args) | `RAX`=gid | GID real |
| 107 | geteuid | (sin args) | `RAX`=euid | UID efectivo |
| 108 | getegid | (sin args) | `RAX`=egid | GID efectivo |
| 105 | setuid | `RDI`=uid | `RAX`=0 o -errno | Cambia UID (real, efectivo, guardado) |
| 106 | setgid | `RDI`=gid | `RAX`=0 o -errno | Cambia GID |
| 113 | setreuid | `RDI`=ruid, `RSI`=euid | `RAX`=0 o -errno | Cambia UID real y efectivo |
| 114 | setregid | `RDI`=rgid, `RSI`=egid | `RAX`=0 o -errno | Cambia GID real y efectivo |
| 117 | setresuid | `RDI`=ruid, `RSI`=euid, `RDX`=suid | `RAX`=0 o -errno | Cambia UID real, efectivo y guardado |
| 118 | getresuid | `RDI`=ruid, `RSI`=euid, `RDX`=suid | `RAX`=0 o -errno | Obtiene UID real, efectivo y guardado |
| 119 | setresgid | `RDI`=rgid, `RSI`=egid, `RDX`=sgid | `RAX`=0 o -errno | Cambia GID real, efectivo y guardado |
| 120 | getresgid | `RDI`=rgid, `RSI`=egid, `RDX`=sgid | `RAX`=0 o -errno | Obtiene GID real, efectivo y guardado |
| 122 | setfsuid | `RDI`=fsuid | `RAX`=uid anterior | Cambia UID para filesystem |
| 123 | setfsgid | `RDI`=fsgid | `RAX`=gid anterior | Cambia GID para filesystem |
| 115 | getgroups | `RDI`=size, `RSI`=list | `RAX`=nº o -errno | Lista grupos suplementarios |
| 116 | setgroups | `RDI`=size, `RSI`=list | `RAX`=0 o -errno | Cambia grupos suplementarios |
| 121 | getpgid | `RDI`=pid | `RAX`=pgid o -errno | PGID de un proceso |
| 109 | setpgid | `RDI`=pid, `RSI`=pgid | `RAX`=0 o -errno | Cambia PGID |
| 111 | getpgrp | (sin args) | `RAX`=pgid | PGID del proceso actual |
| 124 | getsid | `RDI`=pid | `RAX`=sid o -errno | SID de un proceso |
| 112 | setsid | (sin args) | `RAX`=sid o -errno | Crea nueva sesión |
| 125 | capget | `RDI`=hdrp, `RSI`=datap | `RAX`=0 o -errno | Obtiene capacidades POSIX |
| 126 | capset | `RDI`=hdrp, `RSI`=datap | `RAX`=0 o -errno | Cambia capacidades POSIX |
| 317 | seccomp | `RDI`=operation, `RSI`=flags, `RDX`=args | `RAX`=0 o -errno | Filtro de syscalls (sandbox, SECCOMP-BPF) |
| 250 | keyctl | `RDI`=operation, `RSI`=arg2, `RDX`=arg3, `R10`=arg4, `R8`=arg5 | `RAX`=depende o -errno | Control de claves del kernel |
| 248 | add_key | `RDI`=type, `RSI`=description, `RDX`=payload, `R10`=plen, `R8`=keyring | `RAX`=serial o -errno | Añade clave al keyring |
| 249 | request_key | `RDI`=type, `RSI`=description, `RDX`=callout_info, `R10`=dest_keyring | `RAX`=serial o -errno | Solicita clave del keyring |
| 444 | landlock_create_ruleset | `RDI`=attr, `RSI`=size, `RDX`=flags | `RAX`=fd o -errno | Crea ruleset Landlock |
| 445 | landlock_add_rule | `RDI`=ruleset_fd, `RSI`=rule_type, `RDX`=rule_attr, `R10`=flags | `RAX`=0 o -errno | Añade regla Landlock |
| 446 | landlock_restrict_self | `RDI`=ruleset_fd, `RSI`=flags | `RAX`=0 o -errno | Aplica restricción Landlock |
| 459 | lsm_get_self_attr | `RDI`=name, `RSI`=value, `RDX`=size, `R10`=flags | `RAX`=0 o -errno | Atributos LSM del proceso |
| 460 | lsm_set_self_attr | `RDI`=name, `RSI`=value, `RDX`=size, `R10`=flags | `RAX`=0 o -errno | Cambia atributos LSM |
| 461 | lsm_list_modules | `RDI`=ids, `RSI`=size, `RDX`=flags | `RAX`=0 o -errno | Lista módulos LSM activos |

IPC y Sincronización

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 22 | pipe | `RDI`=fds\[2\] | `RAX`=0 o -errno | Crea pipe unidireccional |
| 293 | pipe2 | `RDI`=fds\[2\], `RSI`=flags | `RAX`=0 o -errno | pipe con flags (O_NONBLOCK, O_CLOEXEC) |
| 284 | eventfd | `RDI`=initval | `RAX`=fd o -errno | Crea fd de evento (contador) |
| 290 | eventfd2 | `RDI`=initval, `RSI`=flags | `RAX`=fd o -errno | eventfd con flags |
| 64 | semget | `RDI`=key, `RSI`=nsems, `RDX`=semflg | `RAX`=semid o -errno | Crea/obtiene conjunto de semáforos |
| 65 | semop | `RDI`=semid, `RSI`=sops, `RDX`=nsops | `RAX`=0 o -errno | Opera sobre semáforos |
| 66 | semctl | `RDI`=semid, `RSI`=semnum, `RDX`=cmd, `R10`=arg | `RAX`=depende o -errno | Control de semáforos |
| 220 | semtimedop | `RDI`=semid, `RSI`=sops, `RDX`=nsops, `R10`=timeout | `RAX`=0 o -errno | semop con timeout |
| 29 | shmget | `RDI`=key, `RSI`=size, `RDX`=shmflg | `RAX`=shmid o -errno | Crea/obtiene segmento de memoria compartida |
| 30 | shmat | `RDI`=shmid, `RSI`=shmaddr, `RDX`=shmflg | `RAX`=dir o -errno | Adjunta segmento de memoria compartida |
| 67 | shmdt | `RDI`=shmaddr | `RAX`=0 o -errno | Desadjunta segmento |
| 31 | shmctl | `RDI`=shmid, `RSI`=cmd, `RDX`=buf | `RAX`=0 o -errno | Control de memoria compartida |
| 68 | msgget | `RDI`=key, `RSI`=msgflg | `RAX`=msqid o -errno | Crea/obtiene cola de mensajes |
| 69 | msgsnd | `RDI`=msqid, `RSI`=msgp, `RDX`=msgsz, `R10`=msgflg | `RAX`=0 o -errno | Envía mensaje |
| 70 | msgrcv | `RDI`=msqid, `RSI`=msgp, `RDX`=msgsz, `R10`=msgtyp, `R8`=msgflg | `RAX`=bytes o -errno | Recibe mensaje |
| 71 | msgctl | `RDI`=msqid, `RSI`=cmd, `RDX`=buf | `RAX`=0 o -errno | Control de cola de mensajes |
| 240 | mq_open | `RDI`=name, `RSI`=oflag, `RDX`=mode, `R10`=attr | `RAX`=mqdes o -errno | Abre cola de mensajes POSIX |
| 241 | mq_unlink | `RDI`=name | `RAX`=0 o -errno | Elimina cola de mensajes |
| 242 | mq_timedsend | `RDI`=mqdes, `RSI`=msg_ptr, `RDX`=msg_len, `R10`=msg_prio, `R8`=abs_timeout | `RAX`=0 o -errno | Envía mensaje con timeout |
| 243 | mq_timedreceive | `RDI`=mqdes, `RSI`=msg_ptr, `RDX`=msg_len, `R10`=msg_prio, `R8`=abs_timeout | `RAX`=bytes o -errno | Recibe mensaje con timeout |
| 244 | mq_notify | `RDI`=mqdes, `RSI`=notification | `RAX`=0 o -errno | Notificación de mensaje |
| 245 | mq_getsetattr | `RDI`=mqdes, `RSI`=newattr, `RDX`=oldattr | `RAX`=0 o -errno | Atributos de cola de mensajes |
| 202 | futex | `RDI`=uaddr, `RSI`=op, `RDX`=val, `R10`=timeout, `R8`=uaddr2, `R9`=val3 | `RAX`=depende de op | Espera/despierta en dirección de usuario (mutex) |
| 449 | futex_waitv | `RDI`=waiters, `RSI`=nr_waiters, `RDX`=flags, `R10`=timeout, `R8`=clockid | `RAX`=nº o -errno | Espera en múltiples futexes |
| 454 | futex_wake | `RDI`=uaddr, `RSI`=mask, `RDX`=nr, `R10`=flags | `RAX`=nº o -errno | Despierta waiters de futex |
| 455 | futex_wait | `RDI`=uaddr, `RSI`=val, `RDX`=mask, `R10`=flags, `R8`=timeout, `R9`=clockid | `RAX`=0 o -errno | Espera en futex |
| 456 | futex_requeue | `RDI`=uaddr, `RSI`=mask, `RDX`=uaddr2, `R10`=nr_wake, `R8`=nr_requeue | `RAX`=0 o -errno | Reencola waiters entre futexes |
| 270 | pselect6 | `RDI`=nfds, `RSI`=readfds, `RDX`=writefds, `R10`=exceptfds, `R8`=timeout, `R9`=sigmask | `RAX`=nº o -errno | select con máscara de señales |
| 271 | ppoll | `RDI`=fds, `RSI`=nfds, `RDX`=timeout, `R10`=sigmask, `R8`=sigsetsize | `RAX`=nº o -errno | poll con máscara de señales |
| 213 | epoll_create | `RDI`=size | `RAX`=fd o -errno | Crea instancia epoll |
| 291 | epoll_create1 | `RDI`=flags | `RAX`=fd o -errno | epoll_create con flags |
| 233 | epoll_ctl | `RDI`=epfd, `RSI`=op, `RDX`=fd, `R10`=event | `RAX`=0 o -errno | Gestiona fds en epoll |
| 232 | epoll_wait | `RDI`=epfd, `RSI`=events, `RDX`=maxevents, `R10`=timeout | `RAX`=nº o -errno | Espera eventos epoll |
| 281 | epoll_pwait | `RDI`=epfd, `RSI`=events, `RDX`=maxevents, `R10`=timeout, `R8`=sigmask, `R9`=sigsetsize | `RAX`=nº o -errno | epoll_wait con máscara de señales |
| 441 | epoll_pwait2 | `RDI`=epfd, `RSI`=events, `RDX`=maxevents, `R10`=timeout, `R8`=sigmask, `R9`=sigsetsize | `RAX`=nº o -errno | epoll_pwait con timeout ns |
| 23 | select | `RDI`=nfds, `RSI`=readfds, `RDX`=writefds, `R10`=exceptfds, `R8`=timeout | `RAX`=nº o -errno | Multiplexor de E/S |
| 7 | poll | `RDI`=fds, `RSI`=nfds, `RDX`=timeout | `RAX`=nº o -errno | Espera eventos en fds |

E/S Asíncrona e io_uring

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 206 | io_setup | `RDI`=nr_events, `RSI`=ctx_idp | `RAX`=0 o -errno | Crea contexto AIO |
| 207 | io_destroy | `RDI`=ctx_id | `RAX`=0 o -errno | Destruye contexto AIO |
| 208 | io_getevents | `RDI`=ctx_id, `RSI`=min_nr, `RDX`=nr, `R10`=events, `R8`=timeout | `RAX`=nº o -errno | Espera completados AIO |
| 209 | io_submit | `RDI`=ctx_id, `RSI`=nr, `RDX`=iocbpp | `RAX`=nº o -errno | Envía operaciones AIO |
| 210 | io_cancel | `RDI`=ctx_id, `RSI`=iocb, `RDX`=result | `RAX`=0 o -errno | Cancela operación AIO |
| 333 | io_pgetevents | `RDI`=ctx_id, `RSI`=min_nr, `RDX`=nr, `R10`=events, `R8`=timeout, `R9`=sigmask | `RAX`=nº o -errno | io_getevents con máscara de señales |
| 425 | io_uring_setup | `RDI`=entries, `RSI`=params | `RAX`=fd o -errno | Crea instancia io_uring (cola circular compartida) |
| 426 | io_uring_enter | `RDI`=fd, `RSI`=to_submit, `RDX`=min_complete, `R10`=flags, `R8`=sig | `RAX`=nº o -errno | Envía/espera operaciones io_uring |
| 427 | io_uring_register | `RDI`=fd, `RSI`=opcode, `RDX`=arg, `R10`=nr_args | `RAX`=0 o -errno | Registra buffers/fds para io_uring |

Varios / Sistema

| \# | Nombre | Argumentos | Retorno | Descripción |
|----|----|----|----|----|
| 63 | uname | `RDI`=buf | `RAX`=0 o -errno | Información del sistema (kernel, hostname...) |
| 99 | sysinfo | `RDI`=info | `RAX`=0 o -errno | Estadísticas del sistema (RAM, swap, carga...) |
| 103 | syslog | `RDI`=type, `RSI`=buf, `RDX`=len | `RAX`=depende o -errno | Buffer de mensajes del kernel (dmesg) |
| 97 | getrlimit | `RDI`=resource, `RSI`=rlim | `RAX`=0 o -errno | Límites de recursos del proceso |
| 160 | setrlimit | `RDI`=resource, `RSI`=rlim | `RAX`=0 o -errno | Cambia límites de recursos |
| 302 | prlimit64 | `RDI`=pid, `RSI`=resource, `RDX`=new_limit, `R10`=old_limit | `RAX`=0 o -errno | get/set rlimit de otro proceso |
| 98 | getrusage | `RDI`=who, `RSI`=usage | `RAX`=0 o -errno | Uso de recursos del proceso |
| 318 | getrandom | `RDI`=buf, `RSI`=buflen, `RDX`=flags | `RAX`=bytes o -errno | Bytes aleatorios del kernel (entropía) |
| 101 | ptrace | `RDI`=request, `RSI`=pid, `RDX`=addr, `R10`=data | `RAX`=depende o -errno | Depuración/traceo de otro proceso |
| 298 | perf_event_open | `RDI`=attr, `RSI`=pid, `RDX`=cpu, `R10`=group_fd, `R8`=flags | `RAX`=fd o -errno | Monitorización de rendimiento hardware/software |
| 321 | bpf | `RDI`=cmd, `RSI`=attr, `RDX`=size | `RAX`=depende o -errno | Berkeley Packet Filter (programas en el kernel) |
| 169 | reboot | `RDI`=cmd, `RSI`=arg | `RAX`=0 o -errno | Reinicia el sistema |
| 246 | kexec_load | `RDI`=entry, `RSI`=nr_segments, `RDX`=segments, `R10`=flags | `RAX`=0 o -errno | Carga kernel para kexec |
| 320 | kexec_file_load | `RDI`=kernel_fd, `RSI`=initrd_fd, `RDX`=cmdline_len, `R10`=cmdline, `R8`=flags | `RAX`=0 o -errno | kexec desde fd |
| 172 | iopl | `RDI`=level | `RAX`=0 o -errno | Cambia nivel de privilegio E/S |
| 173 | ioperm | `RDI`=from, `RSI`=num, `RDX`=turn_on | `RAX`=0 o -errno | Permisos de puerto E/S |
| 153 | vhangup | (sin args) | `RAX`=0 | Cuelga terminal virtual |
| 154 | modify_ldt | `RDI`=func, `RSI`=ptr, `RDX`=bytecount | `RAX`=0 o -errno | Modifica LDT (tabla de descriptores local) |
| 163 | acct | `RDI`=filename | `RAX`=0 o -errno | Activa/desactiva contabilidad de procesos |
| 170 | sethostname | `RDI`=name, `RSI`=len | `RAX`=0 o -errno | Cambia el hostname |
| 171 | setdomainname | `RDI`=name, `RSI`=len | `RAX`=0 o -errno | Cambia el nombre de dominio NIS |
| 296 | pwritev | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt, `R10`=offset | `RAX`=bytes o -errno | writev con offset (scatter/gather) |
| 295 | preadv | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt, `R10`=offset | `RAX`=bytes o -errno | readv con offset |
| 19 | readv | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt | `RAX`=bytes o -errno | Lee en múltiples buffers (scatter) |
| 20 | writev | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt | `RAX`=bytes o -errno | Escribe desde múltiples buffers (gather) |
| 327 | preadv2 | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt, `R10`=offset, `R8`=flags | `RAX`=bytes o -errno | preadv con flags |
| 328 | pwritev2 | `RDI`=fd, `RSI`=iov, `RDX`=iovcnt, `R10`=offset, `R8`=flags | `RAX`=bytes o -errno | pwritev con flags |
| 73 | flock | `RDI`=fd, `RSI`=operation | `RAX`=0 o -errno | Bloqueo consultivo de archivo |
| 134 | uselib | `RDI`=library | `RAX`=0 o -errno | Carga librería compartida (obsoleto) |
| 95 | umask | `RDI`=mask | `RAX`=máscara anterior | Máscara de creación de archivos |
| 310 | process_vm_readv | `RDI`=pid, `RSI`=local_iov, `RDX`=liovcnt, `R10`=remote_iov, `R8`=riovcnt, `R9`=flags | `RAX`=bytes o -errno | Lee memoria de otro proceso |
| 311 | process_vm_writev | `RDI`=pid, `RSI`=local_iov, `RDX`=liovcnt, `R10`=remote_iov, `R8`=riovcnt, `R9`=flags | `RAX`=bytes o -errno | Escribe memoria en otro proceso |
| 312 | kcmp | `RDI`=pid1, `RSI`=pid2, `RDX`=type, `R10`=idx1, `R8`=idx2 | `RAX`=resultado o -errno | Compara recursos del kernel entre procesos |
| 323 | userfaultfd | `RDI`=flags | `RAX`=fd o -errno | Page faults manejados en espacio de usuario |
| 434 | pidfd_open | `RDI`=pid, `RSI`=flags | `RAX`=fd o -errno | Abre fd apuntando a un proceso |
| 424 | pidfd_send_signal | `RDI`=pidfd, `RSI`=sig, `RDX`=info, `R10`=flags | `RAX`=0 o -errno | Envía señal a través de pidfd |
| 438 | pidfd_getfd | `RDI`=pidfd, `RSI`=targetfd, `RDX`=flags | `RAX`=fd o -errno | Obtiene fd de otro proceso vía pidfd |
| 448 | process_mrelease | `RDI`=pidfd, `RSI`=flags | `RAX`=0 o -errno | Libera memoria de proceso muerto |
| 156 | \_sysctl | `RDI`=args | `RAX`=0 o -errno | Sysctl (obsoleto, usar /proc/sys) |
| 174 | create_module | `RDI`=name, `RSI`=size | `RAX`=0 o -errno | Crear módulo de kernel (obsoleto) |
| 175 | init_module | `RDI`=module_image, `RSI`=len, `RDX`=param_values | `RAX`=0 o -errno | Carga módulo de kernel |
| 313 | finit_module | `RDI`=fd, `RSI`=param_values, `RDX`=flags | `RAX`=0 o -errno | Carga módulo desde fd |
| 176 | delete_module | `RDI`=name, `RSI`=flags | `RAX`=0 o -errno | Descarga módulo de kernel |
| 177 | get_kernel_syms | `RDI`=table | `RAX`=nº o -errno | Símbolos del kernel (obsoleto) |
| 178 | query_module | `RDI`=name, `RSI`=which, `RDX`=buf, `R10`=ret | `RAX`=0 o -errno | Info de módulo (obsoleto) |
| 180 | nfsservctl | `RDI`=cmd, `RSI`=argp, `RDX`=resp | `RAX`=0 o -errno | Control NFS (obsoleto) |
| 236 | vserver | (sin args) | `RAX`=-errno | Virtual server (obsoleto) |
| 181 | getpmsg | `RDI`=fd, `RSI`=ctrl, `RDX`=bandp, `R10`=bandd, `R8`=maxband | `RAX`=0 o -errno | Mensaje STREAMS (obsoleto) |
| 182 | putpmsg | `RDI`=fd, `RSI`=ctrl, `RDX`=bandp, `R10`=bandd, `R8`=maxband | `RAX`=0 o -errno | Mensaje STREAMS (obsoleto) |
| 183 | afs_syscall | (sin args) | `RAX`=-errno | AFS filesystem (obsoleto) |
| 184 | tuxcall | (sin args) | `RAX`=-errno | TUX web server (obsoleto) |
| 185 | security | (sin args) | `RAX`=-errno | Security (obsoleto) |
| 205 | set_thread_area | `RDI`=u_info | `RAX`=0 o -errno | Área TLS de hilo |
| 211 | get_thread_area | `RDI`=u_info | `RAX`=0 o -errno | Área TLS de hilo |
| 212 | lookup_dcookie | `RDI`=cookie64, `RSI`=buf, `RDX`=len | `RAX`=bytes o -errno | Busca cookie de directorio |
| 273 | set_robust_list | `RDI`=head, `RSI`=len | `RAX`=0 o -errno | Lista de futexes robustos al hacer exit |
| 274 | get_robust_list | `RDI`=pid, `RSI`=head_ptr, `RDX`=len_ptr | `RAX`=0 o -errno | Consulta lista robusta |
| 203 | sched_setaffinity | `RDI`=pid, `RSI`=cpusetsize, `RDX`=mask | `RAX`=0 o -errno | CPU affinity de un hilo |
| 204 | sched_getaffinity | `RDI`=pid, `RSI`=cpusetsize, `RDX`=mask | `RAX`=0 o -errno | Consulta CPU affinity |
| 142 | sched_setparam | `RDI`=pid, `RSI`=param | `RAX`=0 o -errno | Prioridad estática |
| 143 | sched_getparam | `RDI`=pid, `RSI`=param | `RAX`=0 o -errno | Consulta prioridad |
| 144 | sched_setscheduler | `RDI`=pid, `RSI`=policy, `RDX`=param | `RAX`=0 o -errno | Política de planificación |
| 145 | sched_getscheduler | `RDI`=pid | `RAX`=policy o -errno | Consulta política |
| 146 | sched_get_priority_max | `RDI`=policy | `RAX`=prioridad máx o -errno | Prioridad máxima |
| 147 | sched_get_priority_min | `RDI`=policy | `RAX`=prioridad mín o -errno | Prioridad mínima |
| 148 | sched_rr_get_interval | `RDI`=pid, `RSI`=tp | `RAX`=0 o -errno | Quantum de RR |
| 314 | sched_setattr | `RDI`=pid, `RSI`=attr, `RDX`=flags | `RAX`=0 o -errno | Planificador con atributos extendidos |
| 315 | sched_getattr | `RDI`=pid, `RSI`=attr, `RDX`=size, `R10`=flags | `RAX`=0 o -errno | Consulta atributos extendidos |
| 251 | ioprio_set | `RDI`=which, `RSI`=who, `RDX`=ioprio | `RAX`=0 o -errno | Prioridad de E/S |
| 252 | ioprio_get | `RDI`=which, `RSI`=who | `RAX`=ioprio o -errno | Consulta prioridad de E/S |
| 279 | move_pages | `RDI`=pid, `RSI`=nr_pages, `RDX`=pages, `R10`=nodes, `R8`=status, `R9`=flags | `RAX`=nº migradas o -errno | Migra páginas entre nodos NUMA |
| 140 | getpriority | `RDI`=which, `RSI`=who | `RAX`=prioridad o -errno | Prioridad nice de un proceso |
| 141 | setpriority | `RDI`=which, `RSI`=who, `RDX`=prio | `RAX`=0 o -errno | Cambia prioridad nice |
| 335 | uretprobe | `RDI`=which, `RSI`=arg2, `RDX`=arg3, `R10`=arg4 | `RAX`=0 o -errno | probe de retorno en espacio de usuario |
| 336 | uprobe | `RDI`=arg1 | `RAX`=0 o -errno | probe en espacio de usuario |
| 16 | ioctl | `RDI`=fd, `RSI`=request, `RDX`=arg | `RAX`=depende o -errno | Control de dispositivo |
