# Scan Plane

Este bloque queda para la persona encargada del motor de escaneo y la generación de resultados.

## Submódulos
- `engine/`: lógica principal del motor, distribución de técnicas y ciclo de vida de las sesiones.
- `pcap/`: interacción con libpcap (subdirectorios `capture/`, `decode/`, `send/`).
- `techniques/`: implementación concreta de SYN, NULL, FIN, XMAS, ACK y UDP.
- `session/`: estructuras compartidas por los hilos, seguimiento de progreso y métricas.
- `services/`: resolución de nombres de servicio y metadatos por puerto.
- `report/`: formateo y serialización de los resultados.
- `concurrency/`: utilidades específicas de hilos (pool, colas, locks).
- `utils/`: helpers adicionales que no encajan en las categorías anteriores.

Añade aquí tus fuentes según lo vayas implementando.
