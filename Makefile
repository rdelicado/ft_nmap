MAKEFLAGS += --no-print-directory

# --- Configuración básica --- #
NAME        = ft_nmap

# Compilador y flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinclude

# libs comunes
LIBS        = -lm
THREAD_LIBS = -pthread

# --- PCAP (requerido) --- #
PCAP_PKG     = libpcap
PCAP_CFLAGS := $(shell pkg-config --cflags $(PCAP_PKG) 2>/dev/null)
PCAP_LIBS   := $(shell pkg-config --libs   $(PCAP_PKG) 2>/dev/null)

# Fallback: si no hay pkg-config, intenta -lpcap
ifeq ($(PCAP_LIBS),)
  PCAP_LIBS   = -lpcap
endif

CFLAGS  += $(PCAP_CFLAGS)
LIBS    += $(PCAP_LIBS)

# --- Directorios --- #
SRC_DIR     = src/
OBJ_DIR     = obj/

# --- Fuentes y objetos --- #
SRC_FILES   = $(shell find $(SRC_DIR) -name "*.c" 2>/dev/null || true)
OBJ_FILES   = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

# --- Colores --- #
GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
YELLOW      = \033[1;33m
NC          = \033[0m

# --- Reglas --- #
all: check-pcap $(NAME)

check-pcap:
	@if ! pkg-config --exists libpcap 2>/dev/null && [ ! -f /usr/include/pcap/pcap.h ] && [ ! -f /usr/include/pcap.h ]; then \
		printf "$(RED)[!] libpcap no encontrada. Ejecuta 'make deps' para instalar dependencias.$(NC)\n"; \
		exit 1; \
	fi

$(NAME): $(OBJ_FILES)
	@printf "$(GREEN)[✔] Enlazando objetos...$(NC)\n"
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ $(LIBS) $(THREAD_LIBS)
	@printf "$(GREEN)[✔] $(NAME) compilado correctamente!$(NC)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)[⚙] Compilando: $<$(NC)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

# --- Limpieza --- #
clean:
	@printf "$(RED)[✗] Eliminando objetos...$(NC)\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(RED)[✗] Eliminando ejecutable...$(NC)\n"
	@rm -f $(NAME)

re: fclean all

# --- Dependencias del sistema --- #
deps:
	@if command -v apt-get >/dev/null 2>&1; then \
		printf "$(YELLOW)[i] Instalando deps con apt-get...$(NC)\n"; \
		sudo apt-get update && sudo apt-get install -y build-essential libpcap-dev pkg-config; \
	elif command -v dnf >/dev/null 2>&1; then \
		printf "$(YELLOW)[i] Instalando deps con dnf...$(NC)\n"; \
		sudo dnf install -y gcc make libpcap-devel pkg-config; \
	elif command -v pacman >/dev/null 2>&1; then \
		printf "$(YELLOW)[i] Instalando deps con pacman...$(NC)\n"; \
		sudo pacman -Sy --needed base-devel libpcap pkgconf; \
	elif command -v zypper >/dev/null 2>&1; then \
		printf "$(YELLOW)[i] Instalando deps con zypper...$(NC)\n"; \
		sudo zypper install -y gcc make libpcap-devel pkg-config; \
	else \
		printf "$(RED)[!] No se detectó gestor de paquetes.$(NC)\n"; \
		printf "$(YELLOW)Instala manualmente: gcc make libpcap-dev pkg-config$(NC)\n"; \
	fi

# --- Capacidades para ejecutar sin root (Linux) --- #
# cap: $(NAME)
#	@echo "$(YELLOW)[i] Asignando CAP_NET_RAW,CAP_NET_ADMIN a $(NAME)$(NC)"
#	@sudo setcap cap_net_raw,cap_net_admin=eip ./$(NAME) || true
#	@echo "$(GREEN)[✔] Hecho. Si falla, ejecuta como root o usa sudo al correr el binario.$(NC)"

# uncap:
#	@sudo setcap -r ./$(NAME) || true

# --- PHONY --- #
.PHONY: all clean fclean re deps check-pcap