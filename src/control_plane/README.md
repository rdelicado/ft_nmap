# 👨‍💻 Control Plane - Persona A

¡Hola! Esta es **tu parte** del proyecto. Serás la persona encargada de todo lo que tiene que ver con **recibir información del usuario** y **preparar el trabajo** antes de que empiece el escaneo.

## 🎯 Tu misión principal
Hacer que el programa entienda lo que el usuario quiere hacer y preparar todo para que la Persona B pueda hacer los escaneos.

---

## 📁 Carpeta `cli/` - Interfaz con el usuario

**¿Qué hace?** Aquí programas cómo el usuario habla con tu programa.

### 📝 Archivos que debes crear:
- [ ] `args_parser.c` - Lee lo que escribe el usuario (--ip, --ports, --scan, etc.)
- [ ] `help_menu.c` - Muestra la pantalla de ayuda cuando pone --help
- [ ] `input_validator.c` - Revisa que lo que escribió el usuario tenga sentido

### ✅ Tareas específicas:
- [ ] **Leer argumentos de la terminal**: cuando el usuario escribe `./ft_nmap --ip 192.168.1.1 --ports 80-443`, tu programa debe entender cada parte
- [ ] **Mostrar menú de ayuda**: si pone `--help`, mostrar todas las opciones disponibles de forma clara
- [ ] **Validar entrada**: 
  - [ ] Comprobar que las IPs están bien escritas
  - [ ] Ver que los puertos sean números válidos (1-65535)
  - [ ] Verificar que no pida más de 250 hilos
  - [ ] Revisar que los tipos de escaneo existan (SYN, NULL, FIN, etc.)

---

## ⚙️ Carpeta `config/` - Configuración del programa

**¿Qué hace?** Guardar todas las opciones que eligió el usuario y ponerlas en un formato que sea fácil de usar.

### 📝 Archivos que debes crear:
- [ ] `scan_config.c` - Estructura principal con todas las opciones
- [ ] `port_range.c` - Maneja rangos de puertos (ej: "80-443" o "22,80,443")
- [ ] `defaults.c` - Valores por defecto cuando el usuario no especifica algo

### ✅ Tareas específicas:
- [ ] **Crear estructura de configuración**: una "caja" donde guardar:
  - [ ] Lista de IPs a escanear
  - [ ] Lista de puertos (individual: 1-1024 por defecto)
  - [ ] Tipos de escaneo (todos si no especifica)
  - [ ] Número de hilos (0 por defecto, máximo 250)
- [ ] **Procesar rangos de puertos**: 
  - [ ] Convertir "80-443" en lista [80,81,82...443]
  - [ ] Convertir "22,80,443" en lista [22,80,443]
  - [ ] Validar que no sean más de 1024 puertos
- [ ] **Aplicar valores por defecto**:
  - [ ] Si no hay puertos: usar 1-1024
  - [ ] Si no hay tipo de escaneo: usar todos (SYN,NULL,FIN,XMAS,ACK,UDP)

---

## 🎯 Carpeta `targets/` - Objetivos a escanear

**¿Qué hace?** Procesar las direcciones IP y nombres de computadoras que se van a escanear.

### 📝 Archivos que debes crear:
- [ ] `target_parser.c` - Lee IPs desde línea de comandos o archivo
- [ ] `ip_validator.c` - Verifica que las IPs estén bien escritas
- [ ] `file_reader.c` - Lee archivo con lista de IPs

### ✅ Tareas específicas:
- [ ] **Leer IP individual**: cuando el usuario pone `--ip 192.168.1.1`
- [ ] **Leer archivo de IPs**: cuando pone `--file ips.txt`
  - [ ] Abrir el archivo línea por línea
  - [ ] Ignorar líneas vacías o comentarios
  - [ ] Crear lista con todas las IPs válidas
- [ ] **Validar direcciones IP**:
  - [ ] Comprobar formato IPv4 (ej: 192.168.1.1)
  - [ ] Verificar que cada número esté entre 0-255
  - [ ] Aceptar nombres de computadora (ej: google.com) pero NO hacer resolución DNS
- [ ] **Crear lista final**: estructura con todos los objetivos listos para escanear

---

## 📋 Carpeta `scheduler/` - Organizador de trabajo

**¿Qué hace?** Tomar todos los objetivos y puertos, y crear "trabajitos" pequeños para que los hilos los puedan hacer.

### 📝 Archivos que debes crear:
- [ ] `task_creator.c` - Crea tareas individuales (1 IP + 1 puerto + 1 tipo de escaneo)
- [ ] `work_queue.c` - Cola donde se guardan las tareas esperando
- [ ] `thread_coordinator.c` - Reparte el trabajo entre los hilos

### ✅ Tareas específicas:
- [ ] **Crear tareas individuales**: 
  - [ ] Para cada IP objetivo
  - [ ] Para cada puerto a escanear
  - [ ] Para cada tipo de escaneo
  - [ ] Crear una tarea = (IP + Puerto + Tipo de escaneo)
- [ ] **Gestionar cola de trabajo**:
  - [ ] Meter todas las tareas en una lista
  - [ ] Permitir que los hilos saquen tareas de la lista
  - [ ] Controlar que no se acaben las tareas antes de tiempo
- [ ] **Coordinar hilos**:
  - [ ] Crear el número de hilos que pidió el usuario
  - [ ] Dar trabajo a cada hilo cuando esté libre
  - [ ] Recoger los resultados cuando terminen

---

## 🔗 Conexión con la Persona B

**¿Cómo se comunican?** Al final de tu trabajo, debes entregar a la Persona B:

- [ ] **Lista de tareas listas**: cada una con IP, puerto y tipo de escaneo
- [ ] **Configuración completa**: cuántos hilos usar, timeouts, etc.
- [ ] **Callback para resultados**: una función donde la Persona B puede devolverte los resultados

---

## 🧪 Cómo probar tu trabajo

- [ ] **Prueba básica**: `./ft_nmap --help` debe mostrar la ayuda
- [ ] **Prueba con IP**: `./ft_nmap --ip 192.168.1.1` debe procesarla correctamente
- [ ] **Prueba con puertos**: `./ft_nmap --ip 192.168.1.1 --ports 80-90` debe crear 11 tareas
- [ ] **Prueba con archivo**: crear archivo con IPs y probarlo con `--file`
- [ ] **Prueba de errores**: probar con IPs malformadas, puertos inválidos, etc.

¡Recuerda que tu trabajo es la base de todo! Si está bien hecho, la Persona B podrá hacer su parte sin problemas. 🚀
