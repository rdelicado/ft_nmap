## 👨‍💻 Persona A - La parte de "entrada y configuración"
- **Carpeta de trabajo:** `src/control_plane/`
- **¿Qué hace esta persona?**
  - Crear el menú de ayuda y leer lo que el usuario escribe en la terminal (`cli/`)
  - Guardar y revisar las opciones del programa (puertos, velocidad, etc.) (`config/`)
  - Leer las direcciones IP desde archivo o desde la terminal (`targets/`)
  - Organizar el trabajo y repartir las tareas entre los hilos (`scheduler/`)
- **Archivos importantes:** principalmente `control_plane.h`

## 👨‍💻 Persona B - La parte de "escaneo y resultados" 
- **Carpeta de trabajo:** `src/scan_plane/`
- **¿Qué hace esta persona?**
  - Hacer funcionar el corazón del escáner (`engine/`)
  - Usar la librería pcap para enviar y recibir paquetes de red (`pcap/`)
  - Programar cada tipo de escaneo: SYN, NULL, FIN, XMAS, ACK y UDP (`techniques/`)
  - Controlar el progreso de los escaneos (`session/`)
  - Saber qué servicio corre en cada puerto (http, ssh, etc.) (`services/`)
  - Mostrar los resultados de forma bonita al usuario (`report/`)
  - Manejar los hilos y herramientas extras (`concurrency/`, `utils/`)
- **Archivos importantes:** `scan_plane.h` y `support.h`

