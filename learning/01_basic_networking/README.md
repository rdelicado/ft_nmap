# 🟢 Fase 1: Fundamentos de Red

Bienvenido a tu primera fase. Aquí vas a entender **cómo funciona realmente** la comunicación en redes antes de empezar a hackear con pcap.

## 🎯 **1.1 - Direcciones IP y Puertos**

### **¿Qué es una dirección IP?**
Una IP es como la **dirección de una casa** en internet:
- `192.168.1.1` = La "casa" (computadora)
- Cada número va de 0 a 255
- Se separan por puntos

### **¿Qué son los puertos?**
Los puertos son como las **puertas de esa casa**:
- `192.168.1.1:80` = Casa 192.168.1.1, puerta número 80
- Cada servicio usa una puerta diferente:
  - Puerto 80 = Servidor web (HTTP)
  - Puerto 22 = SSH (conexión remota)
  - Puerto 443 = HTTPS (web segura)
  - Puerto 21 = FTP (transferencia archivos)

### **¿Cómo se conectan los programas?**
Imagina que quieres ver una página web:
1. Tu navegador se conecta a `google.com:80`
2. Le dice: "Hola, dame la página principal"
3. El servidor responde con el HTML
4. Tu navegador lo muestra bonito

---

## 🛠️ **EJERCICIO 1.1: Parser básico de IPs**

Vamos a crear tu primer programa que entienda direcciones IP.

### **Tu misión:**
Crear un programa que:
1. Reciba una IP como argumento: `./ejercicio1 192.168.1.1`
2. La valide (números entre 0-255)
3. La separe en sus 4 partes
4. Diga si es válida o no

### **¿Estás listo?**
Dime **"Sí, vamos con el Ejercicio 1.1"** y te creo el código base para empezar.

---

## 📋 **Progreso Fase 1:**
- [ ] 1.1 - Direcciones IP y puertos ← **ESTÁS AQUÍ**
- [ ] 1.2 - Protocolo TCP
- [ ] 1.3 - Protocolo UDP  
- [ ] 1.4 - Sockets básicos

¡El primer paso de muchos! 🔥