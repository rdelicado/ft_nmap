# 🛠️ Ejercicio 1.1: Parser de IPs - Guía de Desarrollo

## 🎯 **Tu misión:**
Crear `ip_parser.c` que valide direcciones IPv4.

---

## 📋 **Especificaciones del programa:**

### **Entrada:**
```bash
./ip_parser 192.168.1.1
./ip_parser 300.400.500.600  # Debe detectar error
./ip_parser 192.168.1        # Debe detectar error (faltan octetos)
```

### **Salida esperada:**
```
IP válida: 192.168.1.1
  - Octeto 1: 192
  - Octeto 2: 168  
  - Octeto 3: 1
  - Octeto 4: 1
```

O en caso de error:
```
Error: IP inválida - El octeto 300 está fuera de rango (0-255)
```

---

## 🧠 **Funciones que necesitas conocer:**

### **1. Para argumentos de línea de comandos:**
```c
int main(int argc, char **argv)
```
- `argc` = número de argumentos (incluye el nombre del programa)
- `argv[0]` = nombre del programa ("./ip_parser")
- `argv[1]` = primer argumento (la IP que escribió el usuario)

### **2. Para separar la IP por puntos:**
```c
char *strtok(char *str, const char *delim);
```
- Separa un string usando un delimitador
- **Ejemplo:** `strtok("192.168.1.1", ".")` → devuelve "192"
- **¡CUIDADO!** Modifica el string original

### **3. Para convertir string a número:**
```c
int atoi(const char *str);
```
- Convierte "192" → 192
- Si no puede convertir, devuelve 0

### **4. Para manejar strings:**
```c
#include <string.h>
char *strcpy(char *dest, const char *src);  // Copiar strings
int strlen(const char *s);                   // Longitud del string
```

---

## 🏗️ **Estructura sugerida del programa:**

### **1. Validar argumentos:**
- ¿El usuario pasó exactamente 1 argumento?
- Si no, mostrar uso: `"Uso: ./ip_parser <IP>"`

### **2. Crear copia de la IP:**
- `strtok()` modifica el string original
- Haz una copia para no perder el original

### **3. Separar por octetos:**
- Usar `strtok()` con delimitador "."
- Debe encontrar exactamente 4 partes
- Si encuentra menos o más → error

### **4. Validar cada octeto:**
- Convertir a número con `atoi()`
- Verificar rango 0-255
- Si está fuera → error con mensaje específico

### **5. Mostrar resultado:**
- Si todo está bien → mostrar IP válida y octetos
- Si hay error → mensaje de error específico

---

## 🔍 **Casos de prueba que debes manejar:**

### **✅ Casos válidos:**
- `192.168.1.1`
- `0.0.0.0`  
- `255.255.255.255`
- `127.0.0.1`

### **❌ Casos inválidos:**
- `300.168.1.1` (octeto > 255)
- `192.168.1` (faltan octetos)
- `192.168.1.1.1` (sobran octetos)
- `192.abc.1.1` (octeto no numérico)
- `192.-5.1.1` (octeto negativo)

---

## 💡 **Pistas importantes:**

### **Pista 1 - Copia del string:**
```c
char ip_copy[16];  // Suficiente para "255.255.255.255"
strcpy(ip_copy, argv[1]);
```

### **Pista 2 - Contar octetos:**
```c
int octeto_count = 0;
char *token = strtok(ip_copy, ".");
while (token != NULL) {
    octeto_count++;
    // Procesar token aquí
    token = strtok(NULL, ".");  // ¡NULL en siguientes llamadas!
}
```

### **Pista 3 - Validar rango:**
```c
int num = atoi(token);
if (num < 0 || num > 255) {
    printf("Error: Octeto %d fuera de rango\n", num);
    return 1;
}
```

### **Pista 4 - Detectar octetos no numéricos:**
```c
// Si atoi() devuelve 0, podría ser "0" válido o "abc" inválido
// Necesitas verificar si el token realmente es "0"
```

---

## 🚀 **¡A programar!**

### **Tu proceso:**
1. **Crea el archivo:** `touch ip_parser.c`
2. **Programa:** Sigue la estructura sugerida
3. **Compila:** `gcc -o ip_parser ip_parser.c`
4. **Prueba:** Con todos los casos de arriba
5. **Pregunta:** Si te atascas en algo específico

### **Cuando termines o te atasques:**
- Dime **"He terminado el Ejercicio 1.1"** para revisarlo
- O **"Me he atascado en [parte específica]"** para ayuda puntual

¡Dale caña! 💪🔥