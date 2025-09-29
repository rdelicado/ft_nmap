# 🔌 Ejercicio 1.4: Fundamentos de Sockets

## 🎯 Objetivo
Entender qué son los sockets y cómo crear un cliente y servidor básicos usando las llamadas al sistema más fundamentales. Este ejercicio te dará las bases para comprender cómo nmap crea conexiones personalizadas.

---

## 📘 Teoría imprescindible

### 1. ¿Qué es un socket?
Un socket es un **endpoint de comunicación** que permite que dos programas (en la misma máquina o en diferentes redes) intercambien datos. Es como un "teléfono" que puedes usar para llamar o recibir llamadas.

### 2. Tipos de sockets más comunes
- **TCP (SOCK_STREAM)**: Orientado a conexión, fiable, garantiza orden.
- **UDP (SOCK_DGRAM)**: Sin conexión, rápido, no garantiza entrega.

### 3. Roles fundamentales
- **Cliente**: Inicia la conexión (como hacer una llamada telefónica).
- **Servidor**: Espera conexiones (como esperar que te llamen).

### 4. Flujo típico TCP
**Servidor:**
1. `socket()` → crear el socket
2. `bind()` → asociar a una IP y puerto local
3. `listen()` → ponerse en modo "escucha"
4. `accept()` → esperar y aceptar conexiones
5. `read()/write()` → comunicarse con cliente
6. `close()` → cerrar conexión

**Cliente:**
1. `socket()` → crear el socket
2. `connect()` → conectar al servidor
3. `write()/read()` → enviar/recibir datos
4. `close()` → cerrar conexión

---

## 🛠️ Tu tarea: Cliente y servidor eco básicos

Vamos a crear **dos programas separados**:

### Programa 1: `echo_server.c`
```
./echo_server <puerto>
```
- Escucha en el puerto especificado
- Acepta una conexión
- Lee lo que envía el cliente
- Lo devuelve tal como lo recibió (eco)
- Cierra la conexión

### Programa 2: `echo_client.c`  
```
./echo_client <IP> <puerto> <mensaje>
```
- Se conecta al servidor
- Envía el mensaje
- Lee la respuesta
- Muestra lo que recibió
- Cierra la conexión

---

## 🔧 Herramientas necesarias

### Cabeceras para ambos programas
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

### Constantes útiles
```c
#define BUFFER_SIZE 1024
#define BACKLOG 10
```

---

## 🧰 Funciones nuevas en este ejercicio

### `bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))`
- **Qué hace:** asocia el socket a una dirección local específica (IP + puerto).
- **Cuándo usarlo:** siempre en el servidor, para "reservar" el puerto donde escuchará.
- **Detalle clave:** `addr.sin_addr.s_addr = INADDR_ANY` permite escuchar en todas las interfaces.

### `listen(sockfd, backlog)`
- **Qué hace:** pone el socket en modo "escucha" para conexiones entrantes.
- **Parámetro backlog:** número máximo de conexiones pendientes en cola (típicamente 5-10).
- **Resultado:** después de esto, el socket está listo para `accept()`.

### `accept(sockfd, (struct sockaddr *)&client_addr, &client_len)`
- **Qué hace:** bloquea hasta que llega una conexión, luego devuelve un **nuevo socket** para comunicarse con ese cliente específico.
- **Socket original vs nuevo:** el original sigue escuchando; usas el nuevo para hablar con el cliente.
- **Información del cliente:** puedes obtener su IP y puerto si pasas los parámetros opcionales.

### `write(sockfd, buffer, length)` y `read(sockfd, buffer, capacity)`
- **Qué hacen:** envían y reciben datos a través del socket conectado.
- **Diferencia con `send`/`recv`:** estas funciones son más genéricas (funcionan con archivos, pipes, sockets).
- **Valor devuelto:** bytes escritos/leídos, o `-1` si hay error.

### `INADDR_ANY`
- **Qué es:** constante que significa "cualquier interfaz disponible" (0.0.0.0).
- **Uso típico:** `addr.sin_addr.s_addr = INADDR_ANY;` en servidores.
- **Alternativa:** puedes especificar una IP concreta con `inet_pton`.

---

### `INADDR_ANY`
- **Qué es:** constante que significa "cualquier interfaz disponible" (0.0.0.0).
- **Uso típico:** `addr.sin_addr.s_addr = INADDR_ANY;` en servidores.
- **Alternativa:** puedes especificar una IP concreta con `inet_pton`.

### `setsockopt()` con `SO_REUSEADDR`
- **Qué hace:** permite reutilizar inmediatamente un puerto que acaba de liberarse.
- **Por qué lo necesitas:** evita el error "Address already in use" al reiniciar el servidor.
- **Uso típico:**
  ```c
  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  ```

---

## 🧪 Plan de trabajo detallado

### Paso 1: Implementar el servidor eco (`echo_server.c`)

#### 1.1 Estructura básica y validación
- Declara una función `print_usage()` que muestre: `"Usage: ./echo_server <port>"`
- En `main()`, valida que recibes exactamente 2 argumentos (`argc == 2`)
- Crea una función `parse_port()` que convierta el argumento a entero y valide rango 1-65535
- Si hay error en argumentos, muestra usage y termina con `EXIT_FAILURE`

#### 1.2 Configuración del socket servidor
- Declara variables: `int server_fd, client_fd, port`
- Declara estructuras: `struct sockaddr_in server_addr, client_addr`
- Declara: `socklen_t client_len = sizeof(client_addr)`
- Crea el socket TCP: `server_fd = socket(AF_INET, SOCK_STREAM, 0)`
- Verifica que `server_fd != -1`, si falla usa `perror("socket")` y termina

#### 1.3 Configurar reutilización de puerto (opcional pero recomendado)
- Declara: `int opt = 1`
- Llama: `setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))`
- Si falla, muestra advertencia pero continúa

#### 1.4 Configurar dirección del servidor
- Limpia la estructura: `memset(&server_addr, 0, sizeof(server_addr))`
- Configura familia: `server_addr.sin_family = AF_INET`
- Configura IP: `server_addr.sin_addr.s_addr = INADDR_ANY`
- Configura puerto: `server_addr.sin_port = htons(port)`

#### 1.5 Bind y Listen
- Haz bind: `bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))`
- Si falla, usa `perror("bind")`, cierra socket y termina
- Haz listen: `listen(server_fd, BACKLOG)`
- Si falla, usa `perror("listen")`, cierra socket y termina
- Imprime: `"Server listening on port %d\n", port`

#### 1.6 Accept y comunicación
- Llama: `client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)`
- Si falla, usa `perror("accept")`, cierra socket servidor y termina
- Imprime: `"Client connected from %s\n"` (usa `inet_ntoa(client_addr.sin_addr)`)

#### 1.7 Lectura y eco
- Declara buffer: `char buffer[BUFFER_SIZE]`
- Lee datos: `ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1)`
- Si `bytes_read > 0`:
  - Termina el string: `buffer[bytes_read] = '\0'`
  - Imprime: `"Received: %s\n", buffer`
  - Envía eco: `write(client_fd, buffer, bytes_read)`
  - Imprime: `"Echo sent back to client\n"`
- Si `bytes_read <= 0`, maneja error o desconexión

#### 1.8 Limpieza
- Cierra socket cliente: `close(client_fd)`
- Cierra socket servidor: `close(server_fd)`
- Termina con `EXIT_SUCCESS`

### Paso 2: Implementar el cliente eco (`echo_client.c`)

#### 2.1 Estructura básica y validación
- Declara `print_usage()`: `"Usage: ./echo_client <IP> <port> <message>"`
- Valida que recibes exactamente 4 argumentos (`argc == 4`)
- Reutiliza `parse_port()` del servidor para validar el puerto
- Verifica que el mensaje no esté vacío

#### 2.2 Configuración del socket cliente
- Declara: `int client_fd, port`
- Declara: `struct sockaddr_in server_addr`
- Declara: `char *server_ip = argv[1], *message = argv[3]`
- Crea socket: `client_fd = socket(AF_INET, SOCK_STREAM, 0)`
- Verifica que no falle

#### 2.3 Configurar dirección del servidor
- Limpia estructura: `memset(&server_addr, 0, sizeof(server_addr))`
- Configura familia: `server_addr.sin_family = AF_INET`
- Convierte IP: `inet_pton(AF_INET, server_ip, &server_addr.sin_addr)`
- Verifica que `inet_pton` devuelva 1, si no, error de IP inválida
- Configura puerto: `server_addr.sin_port = htons(port)`

#### 2.4 Conectar al servidor
- Conecta: `connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))`
- Si falla, usa `perror("connect")`, cierra socket y termina
- Imprime: `"Connected to server %s:%d\n", server_ip, port`

#### 2.5 Envío y recepción
- Envía mensaje: `write(client_fd, message, strlen(message))`
- Imprime: `"Sent: %s\n", message`
- Declara: `char buffer[BUFFER_SIZE]`
- Lee respuesta: `ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1)`
- Si `bytes_read > 0`:
  - Termina string: `buffer[bytes_read] = '\0'`
  - Imprime: `"Received echo: %s\n", buffer`

#### 2.6 Limpieza
- Cierra socket: `close(client_fd)`
- Termina con `EXIT_SUCCESS`

### Paso 3: Pruebas paso a paso
### Paso 3: Pruebas paso a paso

#### Prueba 1: Compilación
```bash
gcc -Wall -Wextra -Werror echo_server.c -o echo_server
gcc -Wall -Wextra -Werror echo_client.c -o echo_client
```

#### Prueba 2: Funcionamiento básico
- Terminal 1: `./echo_server 8080`
- Debes ver: `"Server listening on port 8080"`
- Terminal 2: `./echo_client 127.0.0.1 8080 "Hello World"`
- Cliente debe mostrar: `"Connected to server..."` y `"Received echo: Hello World"`
- Servidor debe mostrar: `"Client connected from 127.0.0.1"` y `"Received: Hello World"`

#### Prueba 3: Casos de error
- Puerto inválido: `./echo_server 0` o `./echo_server 70000`
- IP inválida: `./echo_client 999.999.999.999 8080 "test"`
- Servidor no disponible: cliente sin servidor corriendo
- Puerto ocupado: dos servidores en el mismo puerto

#### Prueba 4: Mensajes largos
- Probar con mensaje de 500+ caracteres para verificar que el buffer maneja bien

---

## 🚀 ¿Listo para programar?

Este ejercicio requiere implementar **dos programas completos** que trabajen juntos. Como es más complejo, te recomiendo este orden:

1. **"Vamos con el servidor"** → Implementar `echo_server.c` paso a paso
2. **"Vamos con el cliente"** → Implementar `echo_client.c` paso a paso  
3. **"Probemos todo"** → Ejecutar las pruebas y verificar funcionamiento

Dime con cuál quieres empezar y te guío paso a paso, manteniendo el enfoque de que tú escribas el código siguiendo mis indicaciones detalladas.

## ✅ Checklist del ejercicio
- [ ] **Servidor**: Valida puerto, crea socket, hace bind/listen/accept.
- [ ] **Servidor**: Lee mensaje del cliente y lo devuelve exactamente igual.
- [ ] **Cliente**: Valida IP/puerto/mensaje, se conecta al servidor.
- [ ] **Cliente**: Envía mensaje y muestra la respuesta recibida.
- [ ] **Ambos**: Manejan errores con `perror()` y cierran sockets correctamente.
- [ ] **Prueba**: Funciona la comunicación completa entre cliente y servidor.

---

## 📌 Casos de prueba sugeridos
- **Funcionamiento normal**: servidor en 8080, cliente conecta y envía mensaje.
- **Puerto ocupado**: intentar levantar dos servidores en el mismo puerto.
- **Servidor no disponible**: cliente intenta conectar a puerto sin servidor.
- **Mensajes largos**: probar con strings de varios cientos de caracteres.
- **IP inválida**: cliente con IP mal formada.

---

## 🧭 Consejos útiles
- Usa `printf` para trackear el flujo: "Server listening...", "Client connected!", etc.
- El buffer para `read()` debe tener espacio extra para el `\0` final.
- Si `accept()` falla, el servidor debe seguir escuchando (no terminar).
- Para pruebas rápidas, usa `127.0.0.1` (localhost).
- Si el socket queda "ocupado" tras cerrar el servidor, usa `setsockopt` con `SO_REUSEADDR`.

---