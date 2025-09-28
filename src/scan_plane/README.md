# 👨‍💻 Scan Plane - Persona B

¡Hola! Esta es **tu parte** del proyecto. Serás la persona encargada del **corazón del escáner**: hacer los escaneos reales y mostrar los resultados al usuario.

## 🎯 Tu misión principal
Recibir las tareas de la Persona A, hacer los escaneos de red usando la librería pcap, y entregar resultados bonitos y organizados.

---

## 🚀 Carpeta `engine/` - El corazón del escáner

**¿Qué hace?** El cerebro principal que coordina todo el proceso de escaneo.

### 📝 Archivos que debes crear:
- [ ] `scan_engine.c` - El controlador principal de todos los escaneos
- [ ] `session_manager.c` - Maneja el estado de cada sesión de escaneo
- [ ] `result_collector.c` - Recoge y organiza todos los resultados

### ✅ Tareas específicas:
- [ ] **Inicializar motor de escaneo**:
  - [ ] Preparar la librería pcap
  - [ ] Configurar timeouts y parámetros de red
  - [ ] Crear estructuras para guardar resultados
- [ ] **Procesar tareas de escaneo**:
  - [ ] Recibir lista de tareas de la Persona A
  - [ ] Distribuir tareas entre los diferentes tipos de escaneo
  - [ ] Coordinar el trabajo de todos los hilos
- [ ] **Controlar el flujo**:
  - [ ] Saber cuándo empezar y terminar cada escaneo
  - [ ] Manejar errores sin que se rompa el programa
  - [ ] Llevar estadísticas de progreso

---

## 📡 Carpeta `pcap/` - Comunicación de red

**¿Qué hace?** Usar la librería pcap para enviar y recibir paquetes por la red.

### 📁 Subcarpeta `capture/`
#### 📝 Archivos que debes crear:
- [ ] `packet_capture.c` - Captura paquetes que llegan de la red
- [ ] `device_manager.c` - Maneja las tarjetas de red del computador
- [ ] `filter_manager.c` - Filtra solo los paquetes que nos interesan

#### ✅ Tareas específicas:
- [ ] **Configurar captura**:
  - [ ] Encontrar la tarjeta de red correcta
  - [ ] Ponerla en modo "promiscuo" para escuchar todo
  - [ ] Configurar filtros para capturar solo respuestas a nuestros escaneos
- [ ] **Capturar respuestas**:
  - [ ] Escuchar paquetes TCP y UDP que lleguen
  - [ ] Identificar qué respuestas corresponden a qué escaneo
  - [ ] Guardar la información importante de cada respuesta

### 📁 Subcarpeta `decode/`
#### 📝 Archivos que debes crear:
- [ ] `packet_decoder.c` - Interpreta los paquetes capturados
- [ ] `tcp_decoder.c` - Especializado en paquetes TCP
- [ ] `udp_decoder.c` - Especializado en paquetes UDP

#### ✅ Tareas específicas:
- [ ] **Decodificar paquetes TCP**:
  - [ ] Leer flags TCP (SYN, ACK, RST, FIN, etc.)
  - [ ] Extraer puertos origen y destino
  - [ ] Determinar el estado del puerto (abierto/cerrado/filtrado)
- [ ] **Decodificar paquetes UDP**:
  - [ ] Detectar respuestas UDP
  - [ ] Manejar mensajes ICMP de "puerto no alcanzable"
  - [ ] Determinar estado UDP (abierto|filtrado/cerrado)

### 📁 Subcarpeta `send/`
#### 📝 Archivos que debes crear:
- [ ] `packet_sender.c` - Envía paquetes de escaneo
- [ ] `tcp_packet_builder.c` - Construye paquetes TCP para escaneos
- [ ] `udp_packet_builder.c` - Construye paquetes UDP
- [ ] `checksum_calculator.c` - Calcula checksums correctos

#### ✅ Tareas específicas:
- [ ] **Construir paquetes TCP**:
  - [ ] Crear headers TCP con flags correctos para cada tipo de escaneo
  - [ ] SYN scan: solo flag SYN activado
  - [ ] NULL scan: todos los flags desactivados
  - [ ] FIN scan: solo flag FIN activado
  - [ ] XMAS scan: flags FIN, PSH, URG activados
  - [ ] ACK scan: solo flag ACK activado
- [ ] **Construir paquetes UDP**:
  - [ ] Crear headers UDP simples
  - [ ] Manejar payload vacío o con datos de prueba
- [ ] **Enviar paquetes**:
  - [ ] Calcular checksums correctos (TCP e IP)
  - [ ] Enviar a la dirección IP y puerto correctos
  - [ ] Controlar la velocidad de envío

---

## 🎯 Carpeta `techniques/` - Tipos de escaneo

**¿Qué hace?** Implementar cada uno de los 6 tipos de escaneo que pide el proyecto.

### 📝 Archivos que debes crear:
- [ ] `syn_scan.c` - Escaneo SYN (el más común)
- [ ] `null_scan.c` - Escaneo NULL (sin flags)
- [ ] `fin_scan.c` - Escaneo FIN
- [ ] `xmas_scan.c` - Escaneo XMAS (Christmas tree)
- [ ] `ack_scan.c` - Escaneo ACK
- [ ] `udp_scan.c` - Escaneo UDP
- [ ] `scan_common.c` - Funciones compartidas por todos

### ✅ Tareas específicas por tipo:

#### [ ] **SYN Scan**:
- [ ] Enviar paquete con flag SYN
- [ ] Si respuesta SYN+ACK → Puerto ABIERTO
- [ ] Si respuesta RST → Puerto CERRADO
- [ ] Si no hay respuesta → Puerto FILTRADO

#### [ ] **NULL Scan**:
- [ ] Enviar paquete sin ningún flag activado
- [ ] Si respuesta RST → Puerto CERRADO
- [ ] Si no hay respuesta → Puerto ABIERTO|FILTRADO

#### [ ] **FIN Scan**:
- [ ] Enviar paquete con flag FIN
- [ ] Si respuesta RST → Puerto CERRADO
- [ ] Si no hay respuesta → Puerto ABIERTO|FILTRADO

#### [ ] **XMAS Scan**:
- [ ] Enviar paquete con flags FIN+PSH+URG (como árbol navideño "iluminado")
- [ ] Si respuesta RST → Puerto CERRADO
- [ ] Si no hay respuesta → Puerto ABIERTO|FILTRADO

#### [ ] **ACK Scan**:
- [ ] Enviar paquete con flag ACK
- [ ] Si respuesta RST → Puerto NO FILTRADO
- [ ] Si no hay respuesta → Puerto FILTRADO
- [ ] (Este escaneo no detecta si está abierto, solo si hay firewall)

#### [ ] **UDP Scan**:
- [ ] Enviar paquete UDP vacío
- [ ] Si respuesta UDP → Puerto ABIERTO
- [ ] Si ICMP "port unreachable" → Puerto CERRADO
- [ ] Si no hay respuesta → Puerto ABIERTO|FILTRADO

---

## 📊 Carpeta `session/` - Control de sesiones

**¿Qué hace?** Manejar el estado y progreso de los escaneos.

### 📝 Archivos que debes crear:
- [ ] `scan_session.c` - Estructura principal de cada sesión
- [ ] `progress_tracker.c` - Seguimiento del progreso
- [ ] `timing_controller.c` - Control de tiempos y timeouts

### ✅ Tareas específicas:
- [ ] **Crear sesión de escaneo**:
  - [ ] Guardar configuración (IPs, puertos, tipos de escaneo)
  - [ ] Inicializar contadores de progreso
  - [ ] Preparar estructuras para resultados
- [ ] **Seguir progreso**:
  - [ ] Contar cuántas tareas se han completado
  - [ ] Mostrar puntos o barra de progreso al usuario
  - [ ] Calcular tiempo estimado restante
- [ ] **Controlar tiempos**:
  - [ ] Medir cuánto tarda cada escaneo
  - [ ] Implementar timeouts para paquetes perdidos
  - [ ] Registrar tiempo total del escaneo

---

## 🏷️ Carpeta `services/` - Identificación de servicios

**¿Qué hace?** Saber qué servicio corre normalmente en cada puerto.

### 📝 Archivos que debes crear:
- [ ] `service_resolver.c` - Resuelve puerto → nombre de servicio
- [ ] `service_database.c` - Base de datos de servicios conocidos
- [ ] `port_info.c` - Información adicional de puertos

### ✅ Tareas específicas:
- [ ] **Base de datos de servicios**:
  - [ ] Puerto 22 → "ssh"
  - [ ] Puerto 80 → "http"
  - [ ] Puerto 443 → "https"
  - [ ] Puerto 21 → "ftp"
  - [ ] Etc. (al menos los más comunes del 1-1024)
- [ ] **Resolver servicios**:
  - [ ] Dado un puerto, devolver el nombre del servicio
  - [ ] Si no se conoce, devolver "Unassigned"
  - [ ] Manejar puertos que pueden tener varios servicios

---

## 📋 Carpeta `report/` - Presentación de resultados

**¿Qué hace?** Tomar todos los resultados y mostrarlos bonito al usuario.

### 📝 Archivos que debes crear:
- [ ] `report_generator.c` - Generador principal de reportes
- [ ] `result_formatter.c` - Formatea la salida
- [ ] `summary_creator.c` - Crea resúmenes estadísticos

### ✅ Tareas específicas:
- [ ] **Crear resumen inicial**:
  - [ ] Mostrar configuración del escaneo
  - [ ] "Target Ip-Address: X.X.X.X"
  - [ ] "No of Ports to scan: XX"
  - [ ] "Scans to be performed: SYN NULL FIN..."
  - [ ] "No of threads: XX"
- [ ] **Mostrar progreso**:
  - [ ] "Scanning.."
  - [ ] Puntos que se van añadiendo durante el escaneo
- [ ] **Formatear resultados finales**:
  - [ ] Tabla de puertos abiertos
  - [ ] Tabla de puertos cerrados/filtrados
  - [ ] Columnas: Puerto, Servicio, Resultados por tipo, Conclusión
- [ ] **Calcular estadísticas**:
  - [ ] Tiempo total del escaneo
  - [ ] Número de puertos en cada estado
  - [ ] Resumen final claro

---

## 🧵 Carpeta `concurrency/` - Manejo de hilos

**¿Qué hace?** Herramientas para que múltiples hilos trabajen sin problemas.

### 📝 Archivos que debes crear:
- [ ] `thread_pool.c` - Pool de hilos de trabajo
- [ ] `task_queue.c` - Cola de tareas thread-safe
- [ ] `sync_primitives.c` - Mutexes y semáforos

### ✅ Tareas específicas:
- [ ] **Pool de hilos**:
  - [ ] Crear N hilos (según configuración del usuario)
  - [ ] Cada hilo toma tareas de la cola cuando está libre
  - [ ] Terminar todos los hilos cuando se acabe el trabajo
- [ ] **Cola thread-safe**:
  - [ ] Permitir que múltiples hilos agreguen/saquen tareas
  - [ ] Usar mutexes para evitar condiciones de carrera
  - [ ] Notificar cuando hay nuevas tareas disponibles

---

## 🔧 Carpeta `utils/` - Herramientas auxiliares

**¿Qué hace?** Funciones útiles que se usan en varias partes.

### 📝 Archivos que debes crear:
- [ ] `network_utils.c` - Utilidades de red
- [ ] `string_utils.c` - Manipulación de strings
- [ ] `error_handling.c` - Manejo de errores
- [ ] `logging.c` - Sistema de logging

### ✅ Tareas específicas:
- [ ] **Utilidades de red**:
  - [ ] Convertir IPs entre formatos
  - [ ] Validar direcciones de red
  - [ ] Calcular checksums
- [ ] **Manejo de errores**:
  - [ ] Funciones para reportar errores sin crash
  - [ ] Cleanup seguro de recursos
  - [ ] Mensajes de error descriptivos

---

## 🔗 Conexión con la Persona A

**¿Cómo recibe el trabajo?** La Persona A te entregará:

- [ ] **Lista de tareas**: cada una con (IP, puerto, tipo de escaneo)
- [ ] **Configuración**: número de hilos, timeouts, etc.
- [ ] **Función callback**: para devolver resultados

**¿Qué debes entregar?** Al final de cada tarea:

- [ ] **Estado del puerto**: abierto/cerrado/filtrado/etc.
- [ ] **Información del servicio**: nombre del servicio en ese puerto
- [ ] **Detalles técnicos**: qué tipo de respuesta se recibió

---

## 🧪 Cómo probar tu trabajo

- [ ] **Prueba individual por técnica**: probar cada tipo de escaneo por separado
- [ ] **Prueba con puerto abierto conocido**: escanear puerto 80 de un servidor web
- [ ] **Prueba con puerto cerrado**: escanear puerto que sabes que está cerrado
- [ ] **Prueba de rendimiento**: probar con múltiples hilos
- [ ] **Prueba de errores**: qué pasa si no hay conexión de red

¡Tu trabajo es la parte más técnica y emocionante! Aquí es donde realmente se hace la "magia" del escaneo de puertos. 🎯🔥
