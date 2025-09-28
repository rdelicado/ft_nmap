# División de trabajo propuesta

## Persona A – Control Plane
- Ubicación principal: `src/control_plane/`
- Responsabilidades:
  - Implementar el parser de argumentos y la ayuda (`cli/`).
  - Gestionar opciones globales y validaciones (`config/`).
  - Cargar, limpiar y validar objetivos individuales o por fichero (`targets/`).
  - Preparar la planificación de puertos/hosts y coordinar el pool de hilos (`scheduler/`).
- Headers relevantes: secciones de `control_plane.h`.

## Persona B – Scan Plane
- Ubicación principal: `src/scan_plane/`
- Responsabilidades:
  - Desarrollar el motor central de escaneo (`engine/`).
  - Manejar la interacción con libpcap para captura/decodificación/envío (`pcap/`).
  - Implementar las técnicas SYN, NULL, FIN, XMAS, ACK y UDP (`techniques/`).
  - Mantener el estado de las sesiones y estadísticas (`session/`).
  - Resolver nombres de servicio (`services/`).
  - Formatear y presentar resultados (`report/`).
  - Crear utilidades de concurrencia y helpers de apoyo (`concurrency/`, `utils/`).
- Headers relevantes: secciones de `scan_plane.h` y `support.h`.

## Artefactos añadidos
- `include/control_plane.h`
- `include/scan_plane.h`
- `include/support.h`
- `src/control_plane/` y subdirectorios (`cli/`, `config/`, `targets/`, `scheduler/`).
- `src/scan_plane/` y subdirectorios (`engine/`, `pcap/`, `pcap/capture/`, `pcap/decode/`, `pcap/send/`, `techniques/`, `session/`, `report/`, `services/`, `concurrency/`, `utils/`).
- `.gitkeep` en cada subcarpeta para preservar la estructura vacía.
- `src/control_plane/README.md` y `src/scan_plane/README.md`.

De esta manera cada persona puede trabajar de forma aislada y utilizar únicamente las secciones del header compartido que le correspondan.
