# 🌊 Ejercicio 1.3: Explorando UDP

## 🎯 Objetivo
Aprender cómo funciona el protocolo UDP y construir un pequeño programa de prueba para enviar un datagrama (paquete) a un puerto destino, manejar la posible respuesta y entender por qué los escaneos UDP son diferentes a los TCP.

---

## 📘 Teoría imprescindible

### 1. ¿Qué es UDP?
UDP (User Datagram Protocol) es un protocolo **sin conexión**. No hay handshake de 3 pasos: envías un datagrama y, si el destino quiere, responde. No se garantiza que los datos lleguen, ni que lleguen en orden.

### 2. ¿Cómo detectas si un puerto UDP está abierto?
- Si el servicio responde con algún datagrama → puerto **posiblemente abierto**.
- Si recibes un mensaje ICMP "Destination unreachable, Port unreachable" → puerto **cerrado**.
- Si no hay respuesta → puede estar **abierto o filtrado** (no hay forma de saberlo solo con UDP).

### 3. Diferencias con TCP
| Característica       | TCP                         | UDP                       |
|----------------------|-----------------------------|---------------------------|
| Conexión              | Sí (handshake)              | No                        |
| Confirmación          | Sí (ACKs)                   | No                        |
| Velocidad             | Menor (fiable)              | Mayor (no fiable)         |
| Detección puerto      | Respuesta explícita         | Respuesta/ICMP o silencio |

---

## 🛠️ Tu tarea: Probar un puerto UDP
Vamos a crear un programa sencillo que:
```
./udp_sender <IP> <PORT>
```
- Envíe un datagrama UDP con un pequeño mensaje.
- Espere una respuesta (si existe).
- Informe si recibió algo o si hubo timeout.

No podremos detectar "cerrado" sin manejar ICMP, pero esta práctica te mostrará la mecánica básica.

---

## 🔧 Herramientas necesarias

### Cabeceras
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
```

### Funciones a utilizar
- `socket(AF_INET, SOCK_DGRAM, 0)` → crea un socket UDP.
- `sendto()` → envía un datagrama a un destino.
- `recvfrom()` → intenta recibir una respuesta.
- `setsockopt()` con `SO_RCVTIMEO` → fija un timeout para `recvfrom`.
- `inet_pton()` → validar y convertir la IP.
- `close()` → cerrar el socket.

---

## 🧪 Plan de trabajo

### Paso 1: Validar argumentos
- Igual que en TCP: IP + puerto entre 1 y 65535.
- Puedes reutilizar la lógica de `parse_port` del ejercicio anterior.

### Paso 2: Crear socket UDP
- `socket(AF_INET, SOCK_DGRAM, 0)`
- Manejar errores con `perror` si falla.

### Paso 3: Construir dirección destino
- Usar `struct sockaddr_in` con IP y puerto como antes.
- Convertir IP con `inet_pton`.

### Paso 4: Enviar paquete
- Crear un pequeño mensaje, por ejemplo `"PING"`.
- Usar `sendto(sockfd, message, length, 0, (struct sockaddr *)&target, sizeof(target))`.
- Confirmar cuántos bytes se enviaron.

### Paso 5: Configurar timeout de recepción
- Usar `struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };`
- `setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));`

### Paso 6: Esperar respuesta
- Usar `recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, NULL, NULL)`.
- Si devuelve `-1` con `errno == EWOULDBLOCK` o `EAGAIN`, significa timeout.
- Si recibe algo, imprimir el mensaje.

### Paso 7: Cerrar socket y terminar
- `close(sockfd);`

---

## 🧰 Funciones y conceptos nuevos en este ejercicio

Además de las llamadas reutilizadas del ejercicio TCP (`socket`, `struct sockaddr_in`, `inet_pton`, `close`), aquí aparecen utilidades específicas para trabajar con datagramas y manejar la falta de respuesta típica en UDP.

### `socket(AF_INET, SOCK_DGRAM, 0)`
- **Qué cambia frente a TCP:** al usar `SOCK_DGRAM` el kernel crea un socket sin conexión (UDP). No hay handshake ni control de flujo.
- **Consecuencia práctica:** puedes enviar un paquete con `sendto` sin esperar confirmación previa del destino.

### `sendto(sockfd, payload, len, flags, (struct sockaddr *)&target, sizeof(target))`
- **Qué hace:** envía un datagrama a la dirección especificada, incluso si no se llamó a `connect`.
- **Parámetros clave:**
  - `payload` y `len` → los datos que quieres transmitir.
  - `flags` → normalmente `0` para un envío sencillo.
  - `target` → dirección IPv4 y puerto preparados con `struct sockaddr_in`.
- **Valor devuelto:** bytes enviados (`ssize_t`) o `-1` si hay error. Si es `-1`, `errno` te dice si fue, por ejemplo, red inalcanzable.

### `recvfrom(sockfd, buffer, sizeof(buffer) - 1, flags, NULL, NULL)`
- **Qué hace:** espera a que llegue un datagrama. También puede rellenar la dirección de origen (si proporcionas punteros en lugar de `NULL`).
- **Retorno:** bytes recibidos (`≥ 0`) o `-1` si falló/expiró el tiempo de espera.
- **Uso típico:**
  1. Limpias el búfer (`memset`).
  2. Llamas a `recvfrom`.
  3. Si la respuesta es ≥ 0, terminas el búfer con `\0` para imprimirlo como string.

### `setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))`
- **Qué hace:** configura opciones adicionales del socket. En este ejercicio se usa `SO_RCVTIMEO` para limitar cuánto tiempo bloquea `recvfrom`.
- **Estructura auxiliar:** `struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };` define segundos y microsegundos de espera.
- **Por qué es útil:** muchos servicios UDP no responden; con un timeout evitas que tu programa quede bloqueado para siempre.

### `struct timeval`
- **Definición:** estructura con dos campos (`tv_sec`, `tv_usec`) que representa un intervalo.
- **Contexto:** se usa en `setsockopt` para configurar timeouts y también en otras API como `select`.

### `errno`, `EAGAIN` y `EWOULDBLOCK`
- **Qué aportan:** indican si `recvfrom` terminó por falta de datos dentro del tiempo límite.
- **Uso práctico:** si `recvfrom` devuelve `-1` y `errno` es `EAGAIN` o `EWOULDBLOCK`, interpretas que hubo timeout y decides si reintentar o marcar el puerto como “abierto/filtrado”.

> 💡 **Recuerda:** al no existir handshake en UDP, una ausencia de respuesta no equivale a “puerto abierto”; sólo sabes que no recibiste el ICMP de puerto cerrado.

---

## ✅ Checklist del ejercicio
- [ ] Validar IP y puerto.
- [ ] Crear socket UDP.
- [ ] Enviar datagrama con `sendto`.
- [ ] Configurar timeout para la recepción.
- [ ] Procesar respuesta o tiempo de espera.
- [ ] Mostrar mensajes en inglés como "Sent X bytes", "Response received", "No response (timeout)".

---

## 📌 Casos de prueba sugeridos
- **Sin servicio UDP escuchando** → lo normal es no recibir nada (timeout).
- **Servicio UDP activo**: puedes usar `nc -u -l 9999` para escuchar en un puerto UDP y responder manualmente.
  1. Ejecuta `nc -u -l 9999` en una terminal.
  2. Corre tu programa con `./udp_sender 127.0.0.1 9999`.
  3. En la terminal del `nc`, escribe una respuesta y pulsa Enter.
  4. Comprueba que tu programa la recibe.
- **IP inválida** → `inet_pton` debe detectar el error.
- **Puerto fuera de rango** → error al validar.

---

## 🧭 Consejos útiles
- Usa `printf` antes y después de enviar para saber en qué paso estás.
- Asegúrate de terminar el buffer recibido con `\0` para imprimirlo como string.
- Si quieres probar varios puertos, puedes poner un bucle en torno a `sendto/recvfrom`.
- No olvides cerrar el socket incluso si hay errores.

---

## 🚀 ¿Listo para programar?
Cuando quieras arrancar, dime **"Vamos con el código del ejercicio 1.3"** y te acompaño para que lo construyas tú mismo, paso a paso. Recuerda: en este ejercicio no te daré el código completo, solo pistas y confirmaciones como hicimos en el 1.1.
