# Control Plane

Este bloque está pensado para la persona responsable de toda la entrada y preparación del escaneo.

## Submódulos
- `cli/`: parsing de argumentos, pantalla de ayuda y validación básica.
- `config/`: carga y persistencia de opciones globales (rangos de puertos, modos de escaneo, velocidad).
- `targets/`: lectura y normalización de IPs y hostnames (entrada directa o desde fichero).
- `scheduler/`: creación de tareas por puerto/objetivo y coordinación con el pool de hilos.

Añade aquí tus `.c` y `.h` específicos según avances.
