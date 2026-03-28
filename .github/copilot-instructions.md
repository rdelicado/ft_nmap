# Instrucciones del proyecto ft_nmap

Estas instrucciones aplican a todo el repositorio.

## Fuente de verdad

- El alcance obligatorio se basa en el enunciado de ft_nmap.
- Si hay conflicto entre una propuesta y el enunciado, priorizar el enunciado.
- Evitar funcionalidades fuera de alcance obligatorio salvo que se pidan expresamente como bonus.

## Objetivo del proyecto

Reimplementar parte de nmap en C, usando pcap y pthread, sin invocar nmap real.

## Requisitos obligatorios a respetar

- Nombre del ejecutable: ft_nmap.
- Lenguaje: C.
- Makefile con reglas habituales y recompilacion incremental.
- Ayuda disponible por CLI.
- Objetivos: IPv4 simple y FQDN.
- Entrada por objetivo unico o por fichero de objetivos.
- Escaneos soportados: SYN, NULL, ACK, FIN, XMAS, UDP.
- Si no se indica scan, ejecutar todos.
- Permitir scan individual o varios a la vez.
- Puertos por rango o lista.
- Si no se indican puertos: 1-1024.
- Maximo de puertos por ejecucion: 1024.
- Speedup por hilos: default 0, maximo 250.
- Mostrar tipo de servicio por puerto (nombre, no version).
- Salida clara con tiempo total de escaneo.
- Manejo robusto de errores (sin fallos inesperados).

## Alcance tecnico obligatorio

- Usar librerias C estandar, pcap y pthread en la parte obligatoria.
- No depender de herramientas externas para hacer el escaneo real.

## Politica de trabajo para cambios

- Antes de implementar, validar que el cambio aporta a un requisito obligatorio.
- En revisiones, comprobar primero cumplimiento de requisitos antes de optimizaciones.
- Si algo no esta claro, derivar decision al enunciado de ft_nmap.
