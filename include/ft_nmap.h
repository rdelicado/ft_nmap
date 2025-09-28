// Contiene la vista general del proyecto y reexporta los bloques principales.
// Incluye solo lo mínimo para facilitar que cada persona trabaje en su módulo.

#ifndef FT_NMAP_H
#define FT_NMAP_H

// Bloque A: Control plane (CLI, configuración, gestión de objetivos, scheduler)
#include "control_plane.h"

// Bloque B: Scan plane (motor de escaneo, pcap, reportes, servicios)
#include "scan_plane.h"

// Bloque común: utilidades compartidas (errores, tiempo, concurrencia, helpers)
#include "support.h"

#endif // FT_NMAP_H
