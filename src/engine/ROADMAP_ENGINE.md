# 🗺️ ROADMAP DE IMPLEMENTACIÓN - MÓDULO ENGINE

**Responsable:** Persona B (Especialista en Sistemas)  
**Carpeta:** `src/engine/`  
**Estado actual:** Parsing completado ✅  

---

## 📊 RESUMEN DE PROGRESO

- [x] **Paso 0:** Parsing de argumentos completo
- [ ] **Paso 1:** Arreglar bug inicial en main.c
- [ ] **Paso 2:** Crear sistema de almacenamiento de resultados
- [ ] **Paso 3:** Implementar resolución de nombres de servicio
- [ ] **Paso 4:** Crear tabla de salida formateada
- [ ] **Paso 5:** Implementar multithreading con pthread
- [ ] **Paso 6:** Añadir manejo de señales (SIGINT)
- [ ] **Paso 7:** Implementar medición de tiempos
- [ ] **Paso 8:** Pruebas finales e integración

---

## ✅ PASO 0: Parsing de Argumentos (COMPLETADO)

**Estado:** ✅ HECHO  
**Archivos:** `src/engine/parse/*.c`

Ya tienes todo el sistema de parsing funcionando:
- Puertos (rangos, listas, mezclados)
- IPs y hostnames
- Tipos de escaneo
- Speedup
- Archivos de entrada

**No hay nada que hacer aquí.**

---

## 🔧 PASO 1: Arreglar Bug Inicial en main.c

**Archivo:** `src/main.c`  
**Líneas:** 57, 78-82  
**Prioridad:** 🔴 CRÍTICA (el programa no funciona sin esto)

### ¿Qué hay que hacer?

En `main.c`, la variable `current` está inicializada a `{0}` (es decir, vale NULL), por lo que el bucle `while (current != NULL)` nunca entra y nunca se escanea nada.

### ¿Cómo arreglarlo?

**Cambio en línea 57:**
```c
// ANTES:
t_target *current = {0};

// DESPUÉS:
t_target *current;
```

**Cambio en línea 78:**
```c
// ANTES:
while (current != NULL)

// DESPUÉS:
current = config.targets;
while (current != NULL)
```

### ¿Por qué este cambio?

Porque necesitas que `current` apunte al primer objetivo de la lista `config.targets` para poder recorrerla. Sin esto, el programa parsea todo correctamente pero luego no hace nada.

### Resultado esperado:

Después de este cambio, el programa debería poder iterar por todos los objetivos y llamar a `scan_target()` para cada uno.

---

## 🤝 ACUERDO ENGINE-NETWORK (CERRAR ANTES DEL PASO 2)

**Objetivo:** dejar por escrito qué debe entregar NETWORK para que ENGINE pueda continuar sin bloquearse.

### Qué debe entregar NETWORK en cada resultado

Por cada combinación de puerto + tipo de escaneo, NETWORK debe devolver:

- `target_ip`: objetivo escaneado
- `port`: número de puerto
- `protocol`: `tcp` o `udp`
- `scan_type`: `SYN`, `NULL`, `ACK`, `FIN`, `XMAS` o `UDP`
- `state`: estado final normalizado
- `timed_out`: si se agotó el tiempo de espera (`0`/`1`)
- `error_code`: `0` si todo bien, otro valor si hubo error

### Estados permitidos (lista cerrada)

Para evitar dudas, ENGINE solo aceptará estos estados:

- `open`
- `closed`
- `filtered`
- `unfiltered`
- `open|filtered`

Si NETWORK devuelve otro texto, ENGINE lo tratará como error de contrato.

### Qué NO debe hacer ENGINE

- No interpretar paquetes.
- No decidir estados desde respuestas de red crudas.
- No depender de detalles internos de pcap.

ENGINE solo recibe resultados ya clasificados y los guarda/muestra.

### Criterio de cierre de este acuerdo

Este acuerdo se considera cerrado cuando:

- Existe una estructura común en `include/ft_nmap.h` con esos campos.
- `scan_target()` deja de ser solo impresión y entrega datos reales a ENGINE.
- Ambos validan un caso simple (`127.0.0.1`, puertos `22,80`, escaneo `SYN`) y ENGINE puede imprimir resultados sin adivinar estados.

### Mensaje corto para coordinación (copiar y pegar)

"Necesito que NETWORK me entregue resultados ya clasificados por puerto y tipo de escaneo con estos campos: target_ip, port, protocol, scan_type, state, timed_out y error_code. Yo en ENGINE solo voy a guardar, ordenar y mostrar; no voy a interpretar paquetes."

---

## 📦 PASO 2: Crear Sistema de Almacenamiento de Resultados

**Archivo nuevo:** `src/engine/results.c`  
**Prioridad:** 🟡 ALTA

### ¿Qué hay que hacer?

Crear un sistema para **guardar los resultados** que tu compañero te devuelve desde `scan_target()`. Ahora mismo, `scan_target()` no devuelve nada (es `void`), pero necesitas que te diga qué puertos están abiertos/cerrados/filtrados.

### ¿Cómo hacerlo?

**1. Modificar la estructura `t_scan_result` en `include/ft_nmap.h`:**

Ya tienes la estructura definida, pero necesitas añadir un campo para el nombre del servicio:

```c
typedef struct s_scan_result
{
    int             port;
    char            *state;        // "open", "closed", "filtered"
    char            *scan_type;    // "SYN", "UDP", "NULL", etc.
    char            *service;      // "http", "ssh", "unknown"
}   t_scan_result;
```

**2. Crear una lista de resultados en `t_config`:**

Añade en la estructura `t_config` (línea 39 de `ft_nmap.h`):

```c
typedef struct s_config 
{
    // ... campos existentes ...
    t_scan_result   **results;     // Array dinámico de resultados
    int             result_count;  // Contador de resultados
} t_config;
```

**3. Crear archivo `src/engine/results.c` con estas funciones:**

```c
// Inicializar sistema de resultados
void init_results(t_config *config);

// Añadir un resultado nuevo
void add_result(t_config *config, int port, char *state, char *scan_type);

// Liberar todos los resultados
void free_results(t_config *config);
```

### ¿Por qué este cambio?

Porque necesitas un lugar donde **guardar todos los resultados** de los escaneos. Tu compañero va a escanear muchos puertos con varios tipos de escaneo, y tú necesitas almacenar toda esa información para luego mostrarla en una tabla.

### Detalles de implementación:

- `results` es un **array dinámico** que crece con `realloc()` cada vez que añades un resultado
- `result_count` lleva la cuenta de cuántos resultados hay
- Cada resultado contiene: puerto, estado, tipo de escaneo y servicio

---

## 🔍 PASO 3: Implementar Resolución de Nombres de Servicio

**Archivo nuevo:** `src/engine/services.c`  
**Prioridad:** 🟡 ALTA

### ¿Qué hay que hacer?

Crear una función que **traduzca números de puerto a nombres de servicio**. Por ejemplo:
- Puerto 80 → "http"
- Puerto 22 → "ssh"
- Puerto 443 → "https"

### ¿Cómo hacerlo?

**1. Crear archivo `src/engine/services.c` con esta función:**

```c
char *get_service_name(int port, const char *protocol);
```

**2. Dentro de la función, usar `getservbyport()`:**

Esta es una función de C que busca en `/etc/services` automáticamente:

```c
char *get_service_name(int port, const char *protocol)
{
    struct servent *service;
    
    // protocol puede ser "tcp" o "udp"
    service = getservbyport(htons(port), protocol);
    
    if (service != NULL)
        return strdup(service->s_name);  // Devolver nombre encontrado
    else
        return strdup("unknown");         // Puerto sin nombre conocido
}
```

### ¿Por qué este cambio?

Porque el enunciado dice que debes **mostrar el nombre del servicio** (no solo el número del puerto). Los usuarios quieren ver "http" en lugar de "80".

### ¿Cuándo se usa?

Cuando añades un resultado en `add_result()`, llamas a `get_service_name(port, "tcp")` para obtener el nombre y lo guardas en el campo `service` de `t_scan_result`.

---

## 📊 PASO 4: Crear Tabla de Salida Formateada

**Archivo nuevo:** `src/engine/output.c`  
**Prioridad:** 🟡 ALTA

### ¿Qué hay que hacer?

Crear una función que **imprima todos los resultados** en formato de tabla clara y bonita, como hace nmap.

### ¿Cómo hacerlo?

**1. Crear archivo `src/engine/output.c` con esta función:**

```c
void print_results(t_config *config);
```

**2. Formato de la tabla:**

```
Scan Results for 192.168.1.1:
PORT      STATE       SERVICE     SCAN
22/tcp    open        ssh         SYN
80/tcp    open        http        SYN
443/tcp   filtered    https       SYN
53/udp    open        domain      UDP

Scan completed in 2.45 seconds
```

### ¿Por qué este formato?

- **PORT**: Número de puerto + protocolo (tcp/udp)
- **STATE**: Estado del puerto (open/closed/filtered)
- **SERVICE**: Nombre del servicio
- **SCAN**: Tipo de escaneo usado

### Detalles de implementación:

**Agrupar por objetivo:**
Si hay múltiples IPs, imprime una tabla por cada IP.

**Ordenar por puerto:**
Antes de imprimir, ordena los resultados por número de puerto (de menor a mayor).

**Calcular anchos de columna:**
Para que quede alineado, calcula el ancho máximo de cada columna antes de imprimir.

---

## 🧵 PASO 5: Implementar Multithreading con pthread

**Archivo nuevo:** `src/engine/threading.c`  
**Prioridad:** 🔴 CRÍTICA (requisito obligatorio)

### ¿Qué hay que hacer?

Crear un sistema de **hilos paralelos** para escanear más rápido según el valor de `--speedup`.

### ¿Cómo funciona el multithreading?

Imagina que tienes que escanear 1000 puertos:
- **Sin hilos (--speedup 0)**: Escaneas 1 puerto, esperas respuesta, escaneas otro... (lento)
- **Con 10 hilos (--speedup 10)**: 10 puertos se escanean al mismo tiempo (10x más rápido)

### ¿Cómo hacerlo?

**1. Crear estructura para pasar datos a cada hilo:**

```c
typedef struct s_thread_data
{
    t_target    *target;     // Objetivo a escanear
    t_config    *config;     // Configuración general
    int         thread_id;   // Número del hilo (0, 1, 2...)
    int         *ports;      // Array de puertos que debe escanear este hilo
    int         port_count;  // Cuántos puertos tiene asignados
}   t_thread_data;
```

**2. Crear función que ejecuta cada hilo:**

```c
void *thread_scan_worker(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    
    // Escanear cada puerto asignado a este hilo
    for (int i = 0; i < data->port_count; i++)
    {
        int port = data->ports[i];
        // Llamar a scan_target() de tu compañero
        // Guardar resultados con add_result()
    }
    
    return NULL;
}
```

**3. Crear función principal de threading en `src/engine/threading.c`:**

```c
void run_parallel_scan(t_config *config)
{
    int num_threads = config->speedup;
    
    // Si speedup es 0, escanear secuencialmente
    if (num_threads == 0)
    {
        // Escaneo tradicional sin hilos
        return;
    }
    
    // Crear array de hilos
    pthread_t threads[num_threads];
    t_thread_data thread_data[num_threads];
    
    // Dividir puertos entre hilos
    // (cada hilo recibe una parte de los puertos)
    
    // Crear los hilos
    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, thread_scan_worker, &thread_data[i]);
    }
    
    // Esperar a que terminen todos
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
```

### ¿Por qué este cambio?

Porque es un **requisito obligatorio** del proyecto. El parámetro `--speedup` debe funcionar y debe usar `pthread`.

### ⚠️ Importante: Mutex para proteger resultados

Como varios hilos van a escribir resultados al mismo tiempo, necesitas un **mutex** (cerrojo) para que no se pisen entre ellos:

```c
pthread_mutex_t results_mutex;

// Antes de añadir resultado:
pthread_mutex_lock(&results_mutex);
add_result(config, port, state, scan_type);
pthread_mutex_unlock(&results_mutex);
```

### ¿Qué es un mutex?

Es como un **"turno de palabra"**. Imagina que varios hilos quieren escribir en la misma lista:
- Sin mutex: todos escriben a la vez → se rompe todo ❌
- Con mutex: cada uno espera su turno → todo funciona ✅

---

## 🛑 PASO 6: Añadir Manejo de Señales (SIGINT)

**Archivo nuevo:** `src/engine/signals.c`  
**Prioridad:** 🟢 MEDIA (mejora la experiencia)

### ¿Qué hay que hacer?

Hacer que cuando el usuario pulse **Ctrl+C**, el programa se cierre correctamente en lugar de dejar basura.

### ¿Cómo hacerlo?

**1. Crear archivo `src/engine/signals.c`:**

```c
#include <signal.h>

volatile sig_atomic_t g_interrupted = 0;

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_interrupted = 1;  // Marcar que se interrumpió
        printf("\n\nScan interrupted by user (Ctrl+C)\n");
    }
}

void setup_signal_handlers(void)
{
    struct sigaction sa;
    
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    sigaction(SIGINT, &sa, NULL);
}
```

**2. En `main.c`, al inicio:**

```c
setup_signal_handlers();
```

**3. Dentro de los bucles de escaneo, comprobar:**

```c
if (g_interrupted)
{
    printf("Cleaning up...\n");
    break;  // Salir del bucle
}
```

### ¿Por qué este cambio?

Si el usuario cancela el escaneo con Ctrl+C, debe:
1. Detener el escaneo inmediatamente
2. Liberar memoria (targets, resultados, hilos)
3. Mostrar los resultados parciales (si los hay)
4. Salir limpiamente

Sin esto, al presionar Ctrl+C el programa se cierra bruscamente y puede dejar hilos corriendo o memoria sin liberar.

---

## ⏱️ PASO 7: Implementar Medición de Tiempos

**Archivo:** `src/engine/output.c` (añadir funciones)  
**Prioridad:** 🟡 ALTA (requisito obligatorio)

### ¿Qué hay que hacer?

Medir cuánto tiempo tarda el escaneo completo y mostrarlo al final.

### ¿Cómo hacerlo?

**1. Usar `gettimeofday()` para medir:**

```c
#include <sys/time.h>

struct timeval start, end;

// Al inicio del escaneo:
gettimeofday(&start, NULL);

// Al final del escaneo:
gettimeofday(&end, NULL);

// Calcular diferencia:
double elapsed = (end.tv_sec - start.tv_sec) + 
                 (end.tv_usec - start.tv_usec) / 1000000.0;

printf("Scan completed in %.2f seconds\n", elapsed);
```

### ¿Por qué este cambio?

El enunciado dice que debes **mostrar el tiempo total de escaneo**. Es útil para que el usuario sepa si `--speedup` está funcionando (más hilos = menos tiempo).

### ¿Dónde ponerlo?

- **Inicio**: Justo antes de llamar a `run_parallel_scan()` o al bucle de escaneo
- **Fin**: Justo después de terminar todos los escaneos, antes de imprimir la tabla

---

## 🧪 PASO 8: Pruebas Finales e Integración

**Prioridad:** 🟢 BAJA (al final de todo)

### ¿Qué hay que hacer?

Probar que todo funciona correctamente junto con el código de tu compañero.

### Pruebas a realizar:

**1. Escaneo básico sin hilos:**
```bash
sudo ./ft_nmap --ip 127.0.0.1 --ports 22,80,443 --scan SYN --speedup 0
```

**2. Escaneo con múltiples hilos:**
```bash
sudo ./ft_nmap --ip 127.0.0.1 --ports 1-100 --speedup 10
```

**3. Múltiples objetivos desde archivo:**
```bash
sudo ./ft_nmap --file targets.txt --scan SYN,UDP
```

**4. Interrumpir con Ctrl+C:**
- Debe mostrar resultados parciales
- No debe dejar procesos huérfanos

**5. Comprobar que no hay fugas de memoria:**
```bash
valgrind --leak-check=full ./ft_nmap --ip 127.0.0.1
```

### ¿Por qué estas pruebas?

Para asegurar que:
- Los hilos se crean y terminan correctamente
- No hay condiciones de carrera (race conditions)
- La memoria se libera completamente
- El programa es robusto ante errores

---

## 📝 NOTAS IMPORTANTES

### Orden recomendado de implementación:

1. **Primero:** Pasos 1-4 (sin threading)
   - Arregla el bug
   - Implementa resultados, servicios y salida
   - Prueba con `--speedup 0` (sin hilos)

2. **Segundo:** Paso 5 (threading)
   - Una vez funcione sin hilos, añade paralelización
   - Prueba con valores bajos (2-4 hilos) primero

3. **Tercero:** Pasos 6-8 (refinamiento)
   - Señales, tiempos, pruebas finales

### Comunicación con tu compañero:

Tu compañero debe modificar `scan_target()` para que:
- **Devuelva** el estado del puerto (o use un callback)
- **Sea thread-safe** (que varios hilos puedan llamarla simultáneamente)

Coordina con él cuando llegues al Paso 5.

---

## 🎯 OBJETIVOS DE CADA ARCHIVO NUEVO

| Archivo                       | Propósito                                    |
|-------------------------------|----------------------------------------------|
| `src/engine/results.c`        | Almacenar y gestionar resultados de escaneo |
| `src/engine/services.c`       | Resolver nombres de servicio (/etc/services)|
| `src/engine/output.c`         | Imprimir tabla formateada + tiempos         |
| `src/engine/threading.c`      | Gestión de hilos con pthread                |
| `src/engine/signals.c`        | Capturar Ctrl+C y limpiar recursos          |

---

## ✅ CHECKLIST FINAL

Antes de considerar tu parte terminada:

- [ ] El programa compila sin warnings
- [ ] Funciona con `--speedup 0` (sin hilos)
- [ ] Funciona con `--speedup 10` (con hilos)
- [ ] Funciona con múltiples IPs desde archivo
- [ ] Funciona con todos los tipos de escaneo
- [ ] Muestra nombres de servicio correctos
- [ ] Muestra tiempo total de escaneo
- [ ] Se puede interrumpir con Ctrl+C limpiamente
- [ ] No hay fugas de memoria (valgrind limpio)
- [ ] La tabla de salida es clara y ordenada

---

**¡Buena suerte con la implementación! 🚀**

**Recuerda:** Ve paso a paso, prueba cada cosa antes de pasar a la siguiente, y no dudes en pedir ayuda.
