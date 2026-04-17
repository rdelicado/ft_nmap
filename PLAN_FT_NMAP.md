# Plan General ft_nmap (Referencia de trabajo)

Fuente principal y obligatoria:
- ft_nmap.pdf

Este archivo no es una lista diaria de tareas.
Este archivo define el marco general para tomar decisiones y guiar el desarrollo.

## 1) Objetivo del proyecto

Completar la parte obligatoria de ft_nmap con estabilidad, sin salirse del alcance pedido en el PDF.

## 2) Alcance obligatorio resumido

- Ejecutable llamado ft_nmap.
- Ayuda por linea de comandos.
- Objetivo por IP/hostname o por fichero.
- Se admiten FQDN (no se exige resolver DNS segun el PDF).
- Escaneos obligatorios: SYN, NULL, ACK, FIN, XMAS y UDP.
- Si no se indica tipo de escaneo, se ejecutan todos.
- Se debe poder ejecutar cada tipo de escaneo individualmente
  y tambien varios al mismo tiempo.
- Puertos por rango, lista o mixto.
- Si no se indican puertos: 1-1024.
- Maximo de puertos por ejecucion: 1024.
- Speedup: por defecto 0, maximo 250.
- Mostrar estado por puerto y nombre de servicio (tipo, no version).
- Mostrar configuracion del escaneo antes de empezar.
- Mostrar tiempo total del escaneo.
- Manejo robusto de errores (nada de segfault, double free, etc).
- No usar nmap real.

Flags obligatorios segun el PDF:
- `--help`
- `--ports` (rango, lista o mixto)
- `--ip` (IPv4 o hostname)
- `--file` (fichero con lista de objetivos)
- `--speedup` (numero de hilos, 0-250)
- `--scan` (SYN/NULL/FIN/XMAS/ACK/UDP)

Librerias requeridas:
- libpcap (`-lpcap`)
- pthread (`-lpthread`)

## 3) Arquitectura acordada

Arquitectura seleccionada:
- Thread pool de N hilos (segun `--speedup`) para envio de paquetes.
- Recepcion con multiplexacion usando `select` (no bloqueante).

Idea base:
- Cada hilo del pool recibe un job (1 IP + 1 puerto + 1 tipo de escaneo)
  y solo se encarga de ENVIAR el paquete de prueba.
  El hilo queda libre inmediatamente despues de enviar.
- Un bucle principal en NETWORK usa `select` para recibir las respuestas
  a medida que llegan, sin bloquear.
- Cuando no quedan jobs pendientes ni respuestas esperadas,
  se sale del bucle y se devuelve el control a ENGINE.

Ventaja: los hilos no pierden tiempo esperando timeouts.
La recepcion es centralizada y eficiente.

## 4) Separacion de responsabilidades

### ENGINE (Rubén):
- Parseo y validacion de argumentos.
- Construccion de la lista final de objetivos (`target_list`).
- Resolucion de hostnames a IPv4.
- Validacion de limites (maximo 1024 puertos, speedup 0-250).
- Creacion y gestion del Thread Pool (hilos, mutexes, colas de trabajo).
- Generacion de jobs para la cola del Thread Pool.
- Impresion de "Scan Configurations" antes de escanear.
- Coordinacion de la llamada a la capa de red (`scan_start`).
- Medicion del tiempo total del escaneo.
- Impresion de resultados finales en formato tabla.
- Resolucion de nombres de servicio por puerto (`getservbyport`).
- Control de errores de flujo y liberacion de memoria.

### NETWORK (compañero):
- Diseño e implementacion de la funcion worker que consumiran los hilos.
- Envio de paquetes de prueba en crudo.
- Recepcion de respuestas con `select` de forma concurrente.
- Control de tiempos de espera y timeouts en los sockets.
- Clasificacion del estado final por puerto y tipo de escaneo.
- Relleno de `output` en cada `t_target` para que ENGINE
  solo tenga que leerlo y mostrarlo.
- Respeto de la señal de terminacion (variable global de señal).

## 5) Contrato de datos entre modulos

### Entrada a NETWORK (lo que ENGINE prepara):

```c
int  scan_start(t_config *config);
```

`t_config` contiene:
- `target_list`: lista enlazada de `t_target`, cada uno con `hostname` e `ip` ya resueltos.
- `ports[65536]`: tabla booleana de puertos a escanear.
- `scan_syn`, `scan_null`, etc.: flags de tipos de escaneo activos.
- `speedup`: numero de hilos para el thread pool.

### Salida de NETWORK (lo que ENGINE recibe):

En cada `t_target`, NETWORK rellena:
- `output`: array dinamico de `t_scan_result*`.
- `output_count`: cantidad de resultados.

Cada `t_scan_result` contiene:
- `port`: numero de puerto.
- `state`: string con el estado final.
- `scan_type`: string con el tipo de escaneo (ej: "SYN").
- `timed_out`: 1 si agoto tiempo, 0 si no.
- `error`: 0 si ok, otro valor si error.

### Estados posibles por tipo de escaneo

Segun el comportamiento estandar de nmap:
- **SYN**: Open, Closed, Filtered
- **NULL/FIN/XMAS**: Open|Filtered, Closed
- **ACK**: Unfiltered, Filtered
- **UDP**: Open, Open|Filtered, Closed

### Nombre de servicio

ENGINE resuelve el nombre de servicio usando `getservbyport()`
y lo muestra en la tabla de resultados. Si no hay servicio conocido,
se muestra "Unassigned".

## 6) Señales

- Se registra un handler para SIGINT (Ctrl+C).
- El handler pone una variable global (`g_signal`) con el numero de señal.
- Tanto ENGINE como NETWORK comprueban esta variable para saber
  si deben terminar de forma ordenada.
- Si se recibe señal, NETWORK termina lo antes posible,
  ENGINE imprime los resultados parciales obtenidos y libera memoria.
- Solo se usa UNA variable global, tipo `volatile sig_atomic_t g_signal`.

## 7) Flujo general del programa

```
1. Comprobar permisos de root.
2. Parsear y validar argumentos.
3. Construir lista final de objetivos (build_target_list).
4. Imprimir "Scan Configurations".
5. Registrar tiempo de inicio (gettimeofday).
6. Lanzar scan_start una sola vez.
7. Registrar tiempo de fin.
8. Imprimir tiempo total del escaneo.
9. Imprimir resultados finales por objetivo.
10. Liberar memoria.
```

## 8) Formato de salida esperado

Antes del escaneo:
```
Scan Configurations
Target Ip-Address : x.x.x.x
No of Ports to scan : 20
Scans to be performed : SYN
No of threads : 70
Scanning..
```

Despues del escaneo:
```
Scan took X.XXXXX secs
IP address: x.x.x.x
Open ports:
Port    Service Name (if applicable) Results                         Conclusion
----------------------------------------------------------------------------------------
80      http                         SYN(Open)                       Open

Closed/Filtered/Unfiltered ports:
Port    Service Name (if applicable) Results                         Conclusion
----------------------------------------------------------------------------------------
90      Unassigned                   SYN(Filtered)                   Filtered
```

Si hay multiples tipos de escaneo, los resultados se muestran juntos:
```
80      http      SYN(Open) NULL(Closed) FIN(Closed) XMAS(Closed) ACK(Unfiltered) UDP(Open|Filtered)    Open
```

La "Conclusion" es el estado general del puerto considerando todos los escaneos.

## 9) Criterios de aceptacion (mandatory)

Solo se considera cerrada la parte obligatoria cuando:
- Los 6 tipos de escaneo funcionan segun el PDF.
- Se cumplen limites de puertos (max 1024) y speedup (0-250).
- La salida muestra "Scan Configurations" antes de escanear.
- La salida es clara, con nombre de servicio y tiempo total.
- No hay cierres inesperados en casos de error comunes.
- Se mantiene separacion limpia entre ENGINE y NETWORK.
- Ctrl+C termina limpiamente sin leaks ni crash.
- El contrato de datos se respeta: ENGINE prepara, NETWORK rellena, ENGINE muestra.

## 10) Regla de decisiones

Si aparece una duda:
1. Primero manda el PDF.
2. Si el PDF no entra en detalle, se sigue este plan general.
3. La guia de ENGINE se usa para estado diario y pendientes de Rubén.
