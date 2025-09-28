# 📚 Guía de Aprendizaje FT_NMAP - De Zero a Hero

¡Bienvenido a tu ruta de aprendizaje personalizada para el proyecto ft_nmap! Esta guía te llevará paso a paso desde los conceptos más básicos hasta completar todo el proyecto.

## 🎯 **¿Qué vas a aprender?**

Vas a dominar todo lo necesario para crear un escáner de puertos como nmap:
- Cómo funcionan las redes y los paquetes
- Usar la librería pcap para capturar y enviar paquetes
- Crear diferentes tipos de escaneos (SYN, NULL, FIN, etc.)
- Manejar hilos para hacer escaneos rápidos
- Integrar todo en un programa completo

---

## 📋 **HOJA DE RUTA COMPLETA**

### 🟢 **Fase 1: Fundamentos de Red (01_basic_networking/)**
**Objetivo:** Entender cómo funciona la comunicación en redes antes de usar pcap.

#### 📝 **Lo que vas a aprender:**
- [ ] **1.1 - Direcciones IP y puertos** 
  - Qué es una dirección IP (192.168.1.1)
  - Qué son los puertos (80, 443, 22, etc.)
  - Cómo se conectan los programas usando IP:puerto
  
- [ ] **1.2 - Protocolo TCP**
  - Qué es TCP y para qué sirve
  - Los "flags" TCP: SYN, ACK, RST, FIN, PSH, URG
  - El "handshake" de 3 pasos: SYN → SYN+ACK → ACK
  
- [ ] **1.3 - Protocolo UDP**
  - Diferencia entre TCP y UDP
  - Por qué UDP es más simple pero menos confiable
  
- [ ] **1.4 - Sockets básicos**
  - Crear conexiones simples con `socket()`
  - Entender `connect()`, `bind()`, `listen()`

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 1.1:** Programa que parsea direcciones IP
- [ ] **Ejercicio 1.2:** Cliente TCP simple que se conecta a un puerto
- [ ] **Ejercicio 1.3:** Detectar si un puerto está abierto usando connect()
- [ ] **Ejercicio 1.4:** Entender timeouts y errores de conexión

---

### 🔵 **Fase 2: Primeros pasos con PCAP (02_pcap_basics/)**
**Objetivo:** Dominar la librería pcap para capturar y analizar tráfico.

#### 📝 **Lo que vas a aprender:**
- [ ] **2.1 - Instalación y setup de pcap**
  - Instalar libpcap-dev
  - Compilar programas con `-lpcap`
  - Permisos para capturar paquetes
  
- [ ] **2.2 - Capturar tráfico existente**
  - Encontrar interfaces de red disponibles
  - Abrir una interfaz para captura
  - Capturar paquetes que ya circulan por la red
  
- [ ] **2.3 - Filtros de captura**
  - Filtrar solo paquetes TCP
  - Filtrar por puerto específico
  - Filtrar por dirección IP
  
- [ ] **2.4 - Analizar paquetes capturados**
  - Extraer headers Ethernet, IP y TCP/UDP
  - Leer flags TCP de paquetes reales
  - Identificar origen y destino

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 2.1:** Listar todas las interfaces de red
- [ ] **Ejercicio 2.2:** Capturar 10 paquetes y mostrar IPs origen/destino
- [ ] **Ejercicio 2.3:** Capturar solo tráfico hacia puerto 80
- [ ] **Ejercicio 2.4:** Decoder básico que muestre flags TCP
- [ ] **Ejercicio 2.5:** Detectar paquetes SYN, ACK, RST en tráfico real

---

### 🟡 **Fase 3: Creación de Paquetes (03_packet_creation/)**
**Objetivo:** Aprender a crear y enviar tus propios paquetes de red.

#### 📝 **Lo que vas a aprender:**
- [ ] **3.1 - Raw sockets**
  - Qué son los raw sockets y por qué los necesitas
  - Diferencia con sockets normales
  - Permisos de root necesarios
  
- [ ] **3.2 - Headers de red**
  - Estructura del header IP
  - Estructura del header TCP
  - Estructura del header UDP
  - Cálculo de checksums
  
- [ ] **3.3 - Envío con pcap**
  - Usar `pcap_inject()` para enviar paquetes
  - Construir paquetes completos (Ethernet + IP + TCP/UDP)
  
- [ ] **3.4 - Paquetes para cada tipo de escaneo**
  - Crear paquete SYN
  - Crear paquete NULL (sin flags)
  - Crear paquetes FIN, XMAS, ACK
  - Crear paquetes UDP

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 3.1:** Crear estructura básica de header TCP
- [ ] **Ejercicio 3.2:** Calcular checksum TCP correctamente
- [ ] **Ejercicio 3.3:** Enviar un paquete SYN simple
- [ ] **Ejercicio 3.4:** Enviar paquete UDP a puerto específico
- [ ] **Ejercicio 3.5:** Crear función genérica para construir paquetes TCP

---

### 🟠 **Fase 4: Técnicas de Escaneo (04_scan_techniques/)**
**Objetivo:** Implementar cada tipo de escaneo y entender cómo interpretarlos.

#### 📝 **Lo que vas a aprender:**
- [ ] **4.1 - SYN Scan (Stealth scan)**
  - Por qué se llama "stealth"
  - Enviar SYN → analizar respuesta
  - SYN+ACK = abierto, RST = cerrado, nada = filtrado
  
- [ ] **4.2 - NULL Scan**
  - Paquete sin flags TCP
  - Basado en comportamiento de TCP stack
  - RST = cerrado, nada = abierto|filtrado
  
- [ ] **4.3 - FIN Scan**
  - Solo flag FIN activado
  - Similar lógica a NULL scan
  
- [ ] **4.4 - XMAS Scan**
  - Flags FIN+PSH+URG (como luces de navidad)
  - Similar lógica a NULL y FIN
  
- [ ] **4.5 - ACK Scan**
  - Solo para detectar firewalls
  - No detecta puertos abiertos/cerrados
  - RST = no filtrado, nada = filtrado
  
- [ ] **4.6 - UDP Scan**
  - Más complejo que TCP
  - Respuesta UDP = abierto
  - ICMP "port unreachable" = cerrado
  - Nada = abierto|filtrado

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 4.1:** Implementar SYN scan básico
- [ ] **Ejercicio 4.2:** Probar SYN scan contra puerto abierto conocido
- [ ] **Ejercicio 4.3:** Implementar NULL scan y comparar resultados
- [ ] **Ejercicio 4.4:** Implementar los 6 tipos de escaneo
- [ ] **Ejercicio 4.5:** Crear tabla comparativa de resultados por técnica
- [ ] **Ejercicio 4.6:** Manejar timeouts para respuestas lentas

---

### 🔴 **Fase 5: Threading y Concurrencia (05_threading/)**
**Objetivo:** Hacer múltiples escaneos simultáneamente para mayor velocidad.

#### 📝 **Lo que vas a aprender:**
- [ ] **5.1 - Fundamentos de pthreads**
  - Crear y terminar hilos
  - Pasar datos a hilos
  - Esperar que terminen los hilos
  
- [ ] **5.2 - Sincronización**
  - Mutexes para proteger datos compartidos
  - Problem de condiciones de carrera
  - Cuándo usar locks
  
- [ ] **5.3 - Pool de hilos**
  - Crear N hilos trabajadores
  - Cola de tareas compartida
  - Distribuir trabajo entre hilos
  
- [ ] **5.4 - Thread-safe con pcap**
  - Un hilo por interfaz o compartir interfaz
  - Sincronizar envío y captura
  - Evitar conflicts en pcap

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 5.1:** Crear 5 hilos que escaneen puertos diferentes
- [ ] **Ejercicio 5.2:** Pool de hilos básico con cola de tareas
- [ ] **Ejercicio 5.3:** Escaneo multi-thread de rango de puertos
- [ ] **Ejercicio 5.4:** Medir diferencia de velocidad: 1 hilo vs N hilos
- [ ] **Ejercicio 5.5:** Implementar límite máximo de 250 hilos

---

### 🟣 **Fase 6: Integración y Testing (06_integration_tests/)**
**Objetivo:** Juntar todo y crear el programa final completo.

#### 📝 **Lo que vas a aprender:**
- [ ] **6.1 - Arquitectura del programa completo**
  - Separar responsabilidades en módulos
  - Comunicación entre componentes
  - Manejo de errores global
  
- [ ] **6.2 - Parsing de argumentos**
  - Implementar todos los flags requeridos
  - Validación de entrada del usuario
  - Mensajes de error útiles
  
- [ ] **6.3 - Resolución de servicios**
  - Base de datos puerto → servicio
  - Servicios más comunes (80=http, 22=ssh, etc.)
  
- [ ] **6.4 - Formato de salida**
  - Replicar formato exacto del subject
  - Tablas organizadas y claras
  - Métricas de tiempo
  
- [ ] **6.5 - Testing completo**
  - Probar todos los casos del subject
  - Manejo de errores y edge cases
  - Validar contra nmap real (sin usarlo)

#### 🛠️ **Ejercicios prácticos:**
- [ ] **Ejercicio 6.1:** Integrar parser + configuración + escaneo
- [ ] **Ejercicio 6.2:** Implementar todas las opciones de CLI
- [ ] **Ejercicio 6.3:** Sistema completo con reporte final
- [ ] **Ejercicio 6.4:** Testing con casos del subject
- [ ] **Ejercicio 6.5:** Optimización y pulimento final

---

## 🎯 **CHECKLIST DE REQUISITOS DEL SUBJECT**

### ✅ **Requisitos Obligatorios:**
- [ ] Ejecutable llamado `ft_nmap`
- [ ] Menú de ayuda con `--help`
- [ ] Soporte para IPv4 simples (dirección/hostname)
- [ ] Soporte para FQDN (sin resolución DNS)
- [ ] Opción `--speedup` (0 por defecto, máx 250 hilos)
- [ ] Lectura desde archivo con `--file`
- [ ] 6 tipos de escaneo: SYN, NULL, ACK, FIN, XMAS, UDP
- [ ] Escaneos individuales o múltiples simultáneos
- [ ] Puertos por rango o individual (1-1024 por defecto)
- [ ] Máximo 1024 puertos por escaneo
- [ ] Resolución de tipos de servicio
- [ ] Salida clara con tiempos
- [ ] Makefile con reglas estándar
- [ ] Manejo de errores robusto (sin segfaults)
- [ ] Solo usar libc estándar + pcap + pthread

### 🌟 **Bonus Opcionales:**
- [ ] Gestión DNS/Version
- [ ] Detección de OS
- [ ] Evasión IDS/Firewall
- [ ] Ocultar dirección origen
- [ ] Flags adicionales

---

## 🗺️ **CÓMO USAR ESTA GUÍA**

1. **Sigue el orden:** Cada fase construye sobre la anterior
2. **No te saltes ejercicios:** Son la clave para entender
3. **Pregunta todo:** Cuando no entiendas algo, pregunta específicamente
4. **Prueba todo:** Cada concepto debe probarse con código real
5. **Referencia:** Usa esta guía para saber exactamente dónde estás

### 📍 **Formato para preguntas:**
Cuando preguntes algo, di:
- "Estoy en Fase X, Ejercicio Y"
- "No entiendo [concepto específico]"
- "¿Cómo hago [tarea específica]?"

### ⚡ **Consejos importantes:**
- **Instala dependencias primero:** `sudo apt-get install libpcap-dev`
- **Usa sudo cuando sea necesario:** Para raw sockets y captura
- **Compila con:** `gcc -o programa programa.c -lpcap -lpthread`
- **Empieza simple:** Programas de 50-100 líneas máximo al principio
- **Entiende antes de avanzar:** Cada concepto debe estar claro

---
