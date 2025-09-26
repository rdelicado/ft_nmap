# ft_nmap (esqueleto)

Estructura pensada para dos personas trabajando en paralelo. No hay código implementado, solo placeholders y carpetas.

Propuesta de reparto:
- Persona A: src/persona_a
  - cli: parsing de argumentos, validaciones, lectura de fichero de IPs
  - common: logger, utilidades base y helpers
- Persona B: src/persona_b
  - engine: coordinación de hilos, planificación de puertos, agregación de resultados y formateo de salida
  - pcap: construcción de paquetes y captura/respuesta (SYN/NULL/ACK/FIN/XMAS/UDP)

Headers compartidos en include/ (pueden crear headers adicionales por persona si conviene):
- include/ft_nmap.h (API y tipos comunes) [placeholder]
- include/services.h (resolución de nombres de servicio) [placeholder]

Makefile:
- Es esquelético y no compila nada por defecto. Usen la diana `help` o extiéndanlo cuando empiecen a añadir .c.

Siguientes pasos sugeridos:
1) Acordar el contrato de tipos en `include/ft_nmap.h` (inputs/outputs, límites como 1024 puertos y 250 hilos).
2) Persona A implementa CLI y validaciones; Persona B define la interfaz del engine/pcap.
3) Añadir pruebas mínimas en una carpeta tests/ cuando haya implementación.
# ft_nmap
