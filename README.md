# ft_nmap

ft_nmap es un escaner de puertos en C, basado en la parte obligatoria del proyecto ft_nmap.

## Plan general de trabajo (solo este archivo)

Fuente de verdad:
- ft_nmap.pdf

Arquitectura acordada:
- Envio en paralelo con grupo de hilos.
- Recepcion con multiplexacion usando select.

## Reparto de trabajo

### Persona A (NETWORK)
- Implementar envio y recepcion de paquetes reales.
- Gestionar captura con pcap y tiempos de espera.
- Clasificar estados por puerto y tipo de escaneo.
- Rellenar resultados por objetivo para que ENGINE los pueda imprimir.

### Persona B (ENGINE)
- Validar argumentos y preparar configuracion.
- Construir lista final de objetivos desde IP unica o fichero.
- Lanzar scan_start una sola vez desde main.
- Mostrar salida final (puerto, estado, servicio y tiempo total).
- Controlar errores y liberar memoria correctamente.

## Flujo del programa

1. Comprobar permisos de administrador.
2. Parsear y validar argumentos.
3. Preparar lista final de objetivos.
4. Ejecutar scan_start.
5. Recibir resultados.
6. Imprimir salida final.
7. Liberar memoria.

## Requisitos obligatorios a recordar

- Escaneos: SYN, NULL, ACK, FIN, XMAS y UDP.
- Si no se indica scan, ejecutar todos.
- Puertos por defecto: 1-1024.
- Maximo de puertos por ejecucion: 1024.
- Speedup por defecto: 0. Maximo: 250.
- No usar el nmap real.
