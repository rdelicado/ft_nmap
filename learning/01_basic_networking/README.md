# 🟢 Fase 1: Fundamentos de Red

Esta fase te enseña los **fundamentos de networking** necesarios para entender cómo funciona nmap por dentro. Cada ejercicio incluye teoría detallada, ejemplos prácticos y casos de prueba.

---

## 📋 Planificación de Ejercicios

### **Ejercicio 1.1: Parser de Direcciones IP** ✅
- **Archivo**: [`ejercicio1_1_guia.md`](ejercicio1_1_guia.md)
- **Objetivo**: Validar y parsear direcciones IPv4
- **Conceptos**: Direcciones IP, puertos, validación de entrada
- **Implementación**: `ip_parser.c`

### **Ejercicio 1.2: Escáner TCP Básico** ✅  
- **Archivo**: [`ejercicio1_2_tcp.md`](ejercicio1_2_tcp.md)
- **Objetivo**: Detectar puertos TCP abiertos usando `connect()`
- **Conceptos**: TCP, handshake de 3 pasos, sockets, manejo de errores
- **Implementación**: `tcp_scanner.c`

### **Ejercicio 1.3: Exploración UDP** ✅
- **Archivo**: [`ejercicio1_3_udp.md`](ejercicio1_3_udp.md)  
- **Objetivo**: Enviar datagramas UDP y detectar respuestas
- **Conceptos**: UDP, protocolo sin conexión, timeouts, `sendto/recvfrom`
- **Implementación**: `udp_sender.c`


### **Ejercicio 1.4: Fundamentos de Sockets** 🔄
- **Archivo**: [`ejercicio1_4_sockets.md`](ejercicio1_4_sockets.md)
- **Objetivo**: Cliente y servidor TCP básicos
- **Conceptos**: `bind()`, `listen()`, `accept()`, comunicación bidireccional
- **Implementación**: `echo_server.c` + `echo_client.c`

---

## 🎯 Objetivos de Aprendizaje

Al completar esta fase serás capaz de:

- ✅ **Validar y parsear direcciones IP** usando funciones estándar
- ✅ **Detectar puertos TCP abiertos** con el método `connect()`  
- ✅ **Trabajar con UDP** enviando datagramas y manejando respuestas/timeouts
- 🔄 **Crear aplicaciones cliente-servidor** usando sockets básicos
- 🔄 **Manejar múltiples conexiones** y errores de red comunes

---

## 🛠️ Herramientas y Conceptos

### Funciones de Red Aprendidas
- `inet_pton()` → conversión de IP string a binario
- `socket()` → creación de endpoints de comunicación  
- `connect()` → establecimiento de conexiones TCP
- `sendto()/recvfrom()` → comunicación UDP sin conexión
- `setsockopt()` → configuración avanzada de sockets
- `bind()/listen()/accept()` → operaciones de servidor

### Estructuras de Datos
- `struct sockaddr_in` → direcciones IPv4 + puerto
- `struct timeval` → configuración de timeouts
- Enums para códigos de estado y constantes

### Conceptos de Red
- **TCP vs UDP**: diferencias y casos de uso
- **Network byte order**: `htons()` y conversiones  
- **Manejo de errores**: `errno`, `perror()`, códigos de retorno
- **Timeouts y bloqueo**: operaciones síncronas vs asíncronas

---

## 📁 Estructura de Archivos

```
01_basic_networking/
├── README.md                    ← Este archivo (planificación)
├── ejercicio1_1_guia.md        ← Guía detallada del parser IP
├── ejercicio1_2_tcp.md         ← Guía detallada del escáner TCP  
├── ejercicio1_3_udp.md         ← Guía detallada del explorador UDP
├── ejercicio1_4_sockets.md     ← Guía detallada de cliente/servidor
├── ip_parser.c                 ← Implementación del ejercicio 1.1
├── tcp_scanner.c               ← Implementación del ejercicio 1.2
├── udp_sender.c                ← Implementación del ejercicio 1.3
├── echo_server.c               ← Implementación del ejercicio 1.4 (servidor)
└── echo_client.c               ← Implementación del ejercicio 1.4 (cliente)
```

---

