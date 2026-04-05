# Plan de Trabajo ft_nmap (Parte Obligatoria)

Fuente principal: ft_nmap.pdf.

Meta: terminar primero toda la parte obligatoria, de forma estable y sin errores graves.

## 1) Reparto de trabajo claro

- Persona A (NETWORK): se encarga de enviar y recibir paquetes de red, y de decidir el estado de cada puerto segun la respuesta.
- Persona B (ENGINE): se encarga del flujo general del programa, de guardar resultados, de mostrarlos en pantalla y del control de errores.

Regla simple:
- NETWORK interpreta respuestas de red.
- ENGINE coordina y muestra.

## 2) Estado actual del proyecto

- La lectura de argumentos ya esta bastante avanzada.
- Hay un bloqueo en [src/main.c](src/main.c): el recorrido de objetivos no arranca bien.
- El archivo [src/network/scan.c](src/network/scan.c) todavia es una simulacion.
- El Makefile ya enlaza pcap y pthread, que son obligatorias.

## 3) Lista corta de requisitos obligatorios (en palabras simples)

- El programa se debe llamar ft_nmap.
- Debe existir ayuda por linea de comandos.
- Debe aceptar un objetivo directo o un archivo con objetivos.
- Debe aceptar IPv4 y hostname.
- Debe soportar estos tipos de escaneo: SYN, NULL, ACK, FIN, XMAS y UDP.
- Si no se indica tipo de escaneo, debe usar todos.
- Debe aceptar puertos por lista o por rango.
- Si no se indica puerto, usar 1-1024.
- Nunca escanear mas de 1024 puertos por ejecucion.
- El valor de speedup debe ser 0 por defecto y 250 como maximo.
- Debe mostrar nombre de servicio por puerto (sin version).
- Debe mostrar tiempo total de escaneo.
- No debe romperse con errores de memoria o cierres inesperados.
- No se puede llamar al programa nmap real.

## 4) Plan por fases (detallado y sin dudas)

## Fase 0: Desbloquear el arranque

Objetivo:
- Que el programa realmente recorra objetivos y llame al escaneo.

Tareas Persona B (ENGINE):
- Arreglar [src/main.c](src/main.c) para que el puntero de recorrido empiece en la lista de objetivos.
- Validar que, con un objetivo valido, se llame al escaneo al menos una vez.

Tareas Persona A (NETWORK):
- Confirmar que la funcion de escaneo devuelve un resultado util para que ENGINE pueda guardarlo.

Se considera terminado cuando:
- El programa no se queda sin hacer nada y llega a ejecutar el escaneo.

## Fase 1: Acordar que datos se pasan entre ambos

Objetivo:
- Definir exactamente que datos entrega NETWORK y como los usa ENGINE.

Tareas Persona A (NETWORK):
- Entregar por cada puerto: numero de puerto, tipo de escaneo y estado detectado.

Tareas Persona B (ENGINE):
- Guardar esos datos de forma ordenada y segura.
- Asegurar liberacion de memoria en rutas de error.

Se considera terminado cuando:
- Hay una estructura de resultados comun y estable para los dos.

## Fase 2: Hacer funcionar los escaneos obligatorios

Objetivo:
- Tener activos todos los tipos obligatorios.

Tareas Persona A (NETWORK):
- Implementar SYN, NULL, ACK, FIN, XMAS y UDP.
- Para cada uno, definir claramente como se decide el estado del puerto.

Tareas Persona B (ENGINE):
- Si el usuario no elige tipo, activar todos.
- Si el usuario elige varios, ejecutarlos sin romper el flujo.

Se considera terminado cuando:
- Cada tipo funciona por separado y tambien en conjunto.

## Fase 3: Cumplir limites del enunciado

Objetivo:
- Respetar todos los limites obligatorios de puertos y speedup.

Tareas Persona B (ENGINE):
- Forzar maximo 1024 puertos por ejecucion.
- Aplicar por defecto 1-1024 si no se indican puertos.
- Forzar speedup: 0 por defecto y maximo 250.

Tareas Persona A (NETWORK):
- Ajustar el uso de hilos segun el valor de speedup recibido.

Se considera terminado cuando:
- Los casos limite se comportan bien y no producen errores raros.

## Fase 4: Salida final clara

Objetivo:
- Mostrar una salida clara, util y facil de leer.

Tareas Persona B (ENGINE):
- Mostrar puerto, estado y nombre de servicio.
- Mostrar tiempo total del escaneo.
- Mantener formato limpio para uno o varios objetivos.

Tareas Persona A (NETWORK):
- Entregar informacion suficiente para que ENGINE pueda sacar una conclusion por puerto.

Se considera terminado cuando:
- La salida cumple lo pedido en el enunciado y se entiende rapido.

## Fase 5: Cierre obligatorio antes de bonus

Objetivo:
- Confirmar que no hay huecos en mandatory.

Tareas de ambos:
- Probar errores de entrada, permisos y rutas invalidas.
- Confirmar que no hay cierres inesperados.
- Revisar uno por uno todos los puntos del PDF obligatorio.

Se considera terminado cuando:
- Todo mandatory esta completo y estable.
- Solo en ese momento se puede hablar de bonus.

## 5) Proxima tanda de trabajo (inmediata)

1. Persona B: arreglar [src/main.c](src/main.c) para desbloquear el flujo.
2. Persona A: definir y documentar la forma exacta del resultado por puerto.
3. Persona A: reemplazar la simulacion de [src/network/scan.c](src/network/scan.c) por una base real.
4. Persona B: empezar guardado de resultados y salida basica.

## 6) Regla para no desviarse

Si una tarea no cubre un punto obligatorio del PDF, no entra al sprint.
