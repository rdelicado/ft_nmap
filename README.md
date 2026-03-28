# ft_nmap

`ft_nmap` es un escáner de red avanzado inspirado en `nmap`, capaz de realizar escaneos de puertos utilizando diversas técnicas (SYN, NULL, FIN, XMAS, ACK, UDP) con soporte para multihilos.

## 📂 Estructura del Proyecto

El código fuente está organizado en módulos funcionales para facilitar el desarrollo paralelo entre dos desarrolladores:

### 📡 `src/network/` - Especialista en Redes (Persona A)
Este módulo se encarga de la comunicación de bajo nivel con la red.
- **Responsabilidades:**
    - **Crafting de paquetes:** Construcción manual de cabeceras IP, TCP y UDP.
    - **Captura con `libpcap`:** Configuración de filtros y captura de respuestas.
    - **Lógica de Escaneo:** Implementación de las técnicas de escaneo (SYN, ACK, UDP, etc.).
    - **Análisis de Estado:** Determinar si un puerto está `OPEN`, `CLOSED` o `FILTERED` según las respuestas.

### ⚙️ `src/engine/` - Especialista en Sistemas (Persona B)
Este módulo actúa como el motor, orquestador y gestor de datos.
- **Responsabilidades:**
    - **Parsing avanzado (`src/engine/parse/`):** Validación de argumentos, puertos, IPs y archivos de entrada.
    - **Multithreading:** Gestión de hilos con `pthread` para paralelizar el escaneo (`--speedup`).
    - **Gestión de Objetivos:** Orquestar la lista de objetivos y repartirlos entre los hilos.
    - **Reportería:** Recolección de resultados y generación de la tabla final de salida.
    - **Manejo de Señales:** Limpieza de recursos y salida controlada (SIGINT).

### 🛠️ Otros directorios y archivos clave:
- `src/main.c`: Punto de entrada principal del programa. Se encarga de la comprobación de privilegios de root e inicia el flujo de parsing.
- `src/utils/`: Funciones de utilidad genéricas (limpieza de memoria, impresión formateada, etc.).
- `include/`: Contiene `ft_nmap.h` con las estructuras compartidas (`t_config`, `t_target`) y todos los prototipos.

---

## 🚀 Cómo empezar
Si eres un nuevo desarrollador en el proyecto:
1. Identifica tu carpeta de trabajo (`src/network/` o `src/engine/`).
2. Consulta `include/ft_nmap.h` para conocer las estructuras comunes y declarar tus funciones.
3. El `Makefile` ya está configurado para compilar todos los archivos `.c` dentro de estas carpetas automáticamente.
