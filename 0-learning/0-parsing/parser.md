# Parser de Argumentos - ft_nmap

## Validaciones Clave

- `--ip` o `--file` deben proveer al menos un objetivo (no ambos obligatoriamente, pero el programa necesita objetivos)
- Máximo **1024 puertos** en total
- `--speedup` entre **0 y 250**
- `--scan` sólo acepta los valores listados en la tabla

---

## Tabla de Argumentos y Formatos Aceptados

| Argumento | Tipo de valor | Formatos válidos | Valores permitidos/límites | Valor por defecto | Ejemplos | Notas/Validaciones |
|-----------|---------------|------------------|---------------------------|-------------------|----------|-------------------|
| `--help` | Flag | Ninguno (solo presencia) | — | `false` | `--help` | Muestra ayuda y termina |
| `--ip` | String | IPv4 (x.x.x.x) o hostname/FQDN | IPv4: 4 octetos 0–255<br>FQDN: formato básico (letras/números/-/.) | — | `--ip 192.168.1.10`<br>`--ip example.com` | Debe permitir múltiples llamadas. No obligatorio resolver DNS en el parser |
| `--file` | String (ruta) | Ruta a fichero de texto | Archivo con lista de objetivos (IPs o hostnames) | — | `--file targets.txt` | Parser debe leer todas las entradas; ignorar líneas vacías y comentarios opcionales |
| `--ports` | String | Rango `N-M`, lista CSV `P1,P2,...`, o mezcla `1,3-7,22` | Puertos: 1–65535<br>Máximo 1024 puertos totales | `1-1024` | `--ports 80`<br>`--ports 1-1024`<br>`--ports 22,80,443`<br>`--ports 1,5-15,80` | Expandir rangos y deduplicar. Si total > 1024 → error. Validar N ≤ M en rangos |
| `--speedup` | Entero | Decimal entero positivo o 0 | 0 ≤ valor ≤ 250 | `0` | `--speedup 70`<br>`--speedup 0` | Representa número de hilos. 0 puede significar valor por defecto del scheduler |
| `--scan` | String (lista CSV) | Tokens: `SYN`, `ACK`, etc. | `SYN`, `NULL`, `ACK`, `FIN`, `XMAS`, `UDP` (case-insensitive) | Todos los tipos | `--scan SYN`<br>`--scan SYN,ACK,UDP` | Permitir combinaciones; ignorar duplicados; tokens desconocidos → error |

---

## Ejemplos Prácticos de Uso

### 1. Escanear una IP con 70 hilos y sólo SYN en el rango 70–90
```bash
./ft_nmap --ip 10.0.0.5 --speedup 70 --ports 70-90 --scan SYN
```

### 2. Escanear targets desde fichero, todos los escaneos, puertos por defecto
```bash
./ft_nmap --file targets.txt
```

### 3. Escanear puertos puntuales y rangos mezclados
```bash
./ft_nmap --ip server.example.com --ports 22,80,8000-8100 --scan SYN,UDP --speedup 200
```