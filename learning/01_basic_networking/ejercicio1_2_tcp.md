# 🧠 Ejercicio 1.2: Entendiendo TCP paso a paso

## 🎯 Objetivo
Aprender cómo funciona el protocolo TCP en la práctica para detectar si un puerto está abierto usando la función `connect()`.

---

## 📘 Teoría imprescindible

### 1. ¿Qué es TCP?
TCP (Transmission Control Protocol) es un protocolo orientado a conexión. Para que dos equipos hablen, primero establecen una conexión que garantiza que los datos llegan en orden y sin pérdidas.

### 2. Handshake de 3 pasos (Three-way handshake)
1. **SYN**: Tu equipo (cliente) envía un paquete con el flag SYN (synchronize) al servidor.
2. **SYN-ACK**: El servidor responde con SYN + ACK si el puerto está abierto.
3. **ACK**: Tu equipo confirma con un ACK y la conexión queda abierta.

Si el puerto está cerrado, normalmente recibes un paquete con flag RST (reset) o la conexión falla.

### 3. Flags más importantes en TCP
- **SYN**: inicia una conexión.
- **ACK**: confirma recepción.
- **RST**: resetea/conexión rechazada.
- **FIN**: cierra una conexión de forma ordenada.

### 4. Detectar estado de un puerto con sockets básicos
No vamos a construir paquetes a mano todavía. Usaremos la llamada al sistema `connect()`, que, internamente, realiza el handshake por ti. Según el resultado de `connect()`, podrás saber si el puerto acepta conexiones.

---

## 🛠️ Tu tarea: Mini escáner TCP con `connect()`
Vamos a crear un programa que reciba:

```
./tcp_scanner <IP> <PUERTO>
```

y te diga si el puerto parece **abierto**, **cerrado** o si hubo algún **error de red/time-out**.

---

## 🔧 Herramientas que necesitas

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
```

### Funciones importantes
- `socket(AF_INET, SOCK_STREAM, 0)` → crea un socket TCP.
- `struct sockaddr_in` → estructura para definir IP y puerto destino.
- `inet_pton(AF_INET, ip_string, &sockaddr.sin_addr)` → convierte texto a IP binaria.
- `connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))` → intenta el handshake TCP.
- `close(socket_fd)` → cierra el socket, se llame `connect` o no.

---

## 🧪 Plan paso a paso

### Paso 1: Validar argumentos
- Debes recibir exactamente 2 argumentos: IP y puerto.
- Validar que el puerto sea un número entre 1 y 65535.

### Paso 2: Preparar el socket
1. Crear socket TCP con `socket()`.
2. Configurar `sockaddr_in`:
   - `sin_family = AF_INET`
   - `sin_port = htons(puerto)` (convertir a network byte order)
   - `inet_pton` para convertir la IP

### Paso 3: Intentar conectar con `connect()`
- Devuelve 0 si la conexión se estableció (puerto abierto).
- Devuelve `-1` si algo falla. Usa `errno` para saber qué pasó.
  - `ECONNREFUSED` → puerto cerrado.
  - `ETIMEDOUT` → no hay respuesta (podría estar filtrado).
  - Otros valores → error de red (ej. IP incorrecta).

### Paso 4: Mostrar resultados
- Si `connect == 0`: `Port OPEN`
- Si `errno == ECONNREFUSED`: `Port CLOSED`
- Si `errno == ETIMEDOUT`: `No response (filtered or host down)`
- Otro error: muestra el mensaje con `strerror(errno)`.

### Paso 5: Cerrar socket
- Usa `close(socket_fd)` tanto en éxito como en fallo para liberar recursos.

---

## 🧰 Funciones y llamadas nuevas en este ejercicio

A diferencia del ejercicio 1.1 (centrado en parsear direcciones IP), aquí empezamos a dialogar con el stack de red del sistema operativo. Estas son las herramientas nuevas que utilizas y qué aporta cada una:

### `socket(AF_INET, SOCK_STREAM, 0)`
- **Qué hace:** pide al kernel que cree un endpoint de comunicación orientado a conexión (TCP).
- **Parámetros clave:**
  - `AF_INET` → familia de direcciones IPv4.
  - `SOCK_STREAM` → indica flujo fiable (TCP).
  - `0` → protocolo por defecto para la combinación (el kernel elige TCP).
- **Valor devuelto:** descriptor de fichero ≥ 0 si todo va bien; `-1` si hay error (por ejemplo, límite de sockets abiertos).
- **Por qué lo necesitas:** sin este descriptor no puedes iniciar el handshake TCP.

### `struct sockaddr_in`
- **Qué hace:** representa una dirección IPv4 + puerto en formato binario que entiende el kernel.
- **Campos relevantes:**
  - `sin_family` → debe ser `AF_INET` para IPv4.
  - `sin_port` → puerto en *network byte order* (debes convertirlo con `htons`).
  - `sin_addr` → dirección IP preparada con `inet_pton`.
- **Por qué lo necesitas:** todas las llamadas de red (`connect`, `send`, etc.) esperan direcciones empaquetadas en esta estructura.

### `htons(puerto)`
- **Qué hace:** convierte un entero de orden de bytes de host a orden de red (big-endian).
- **Por qué lo necesitas:** el estándar TCP/IP exige que los puertos viajen en orden de red; si no conviertes, el kernel interpreta otra cifra.

### `inet_pton(AF_INET, ip_string, &sockaddr.sin_addr)`
- **Qué hace:** transforma una IP escrita como texto (`"192.168.1.10"`) a su representación binaria.
- **Valor devuelto:** `1` si la cadena es una IPv4 válida, `0` si es texto pero no IP, `-1` si hay error de sistema.
- **Por qué lo necesitas:** `struct sockaddr_in` guarda la IP como un número (`in_addr`), no como string.

### `connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))`
- **Qué hace:** inicia el *three-way handshake* con el host y puerto de destino usando el socket ya creado.
- **Resultado esperado:**
  - `0` → el handshake se completó; el puerto está aceptando conexiones.
  - `-1` → algo salió mal; revisas `errno` para saber si fue rechazo (`ECONNREFUSED`), timeout (`ETIMEDOUT`), red inalcanzable, etc.
- **Por qué lo necesitas:** te permite inferir el estado del puerto sin construir paquetes a mano.

### `close(socket_fd)`
- **Qué hace:** libera el descriptor y notifica al kernel que puede cerrar la conexión (si existía).
- **Por qué lo necesitas:** evitar fugas de recursos y dejar el estado del sistema limpio para pruebas sucesivas.

### `errno` y `strerror(errno)`
- **Qué hacen:**
  - `errno` guarda el motivo del último fallo de system call en el hilo actual.
  - `strerror` convierte ese código en un mensaje legible.
- **Por qué lo necesitas:** según `errno` puedes distinguir entre puerto cerrado (`ECONNREFUSED`), timeout (`ETIMEDOUT`), IP inválida (`EHOSTUNREACH`), etc., y mostrar un mensaje claro en pantalla.

> 📝 **Tip:** si varias llamadas pueden fallar, lee `errno` inmediatamente después de cada una. Llamadas posteriores pueden sobrescribirlo.

---

## ✅ Checklist del ejercicio
- [ ] Validar IP con `inet_pton` y mostrar error si es inválida.
- [ ] Validar que el puerto sea numérico y esté entre 1 y 65535.
- [ ] Crear socket TCP.
- [ ] Intentar `connect` y manejar `errno`.
- [ ] Cerrar el socket antes de salir.
- [ ] Mostrar mensajes claros en inglés:
  - `Trying IP: x.x.x.x Port: N`
  - `Port OPEN`
  - `Port CLOSED (connection refused)`
  - `No response (timeout)`
  - `Network error: <mensaje>` (usa `strerror(errno)`)

---

## 🧑‍💻 Casos de prueba sugeridos
- Un puerto abierto conocido (p. ej. un servidor local escuchando en 8000).
- Un puerto cerrado en tu PC.
- Una IP inválida (ej. `999.999.999.999`).
- Un puerto fuera de rango (`0` o `70000`).
- Un host que tarde en responder para ver el timeout.

> Consejo: puedes levantar un servidor sencillo con `python3 -m http.server 8000` y hacer tus pruebas.

---

## 🚀 Lista para programar
Cuando quieras te guío paso a paso sobre cómo estructurar el código o revisar el resultado. Dime **"Vamos con el código del ejercicio 1.2"** y armamos juntos la base.
