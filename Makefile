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
# Detectar sistema operativo
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# macOS: libpcap viene preinstalado
	PCAP_CFLAGS =
	PCAP_LIBS   = -lpcap
else
	# Linux: usar pkg-config si está disponible
	PCAP_PKG     = libpcap
	PCAP_CFLAGS := $(shell pkg-config --cflags $(PCAP_PKG) 2>/dev/null)
	PCAP_LIBS   := $(shell pkg-config --libs   $(PCAP_PKG) 2>/dev/null)
	
	# Fallback: si no hay pkg-config
	ifeq ($(PCAP_LIBS),)
		PCAP_LIBS = -lpcap
	endif
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
ifeq ($(UNAME_S),Darwin)
	@if [ ! -f /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/pcap/pcap.h ] && \
		[ ! -f /usr/local/include/pcap/pcap.h ] && \
		[ ! -f /opt/homebrew/include/pcap/pcap.h ]; then \
		printf "$(RED)[!] libpcap no encontrada en macOS.$(NC)\n"; \
		printf "$(YELLOW)[i] Ejecuta 'make deps' para ver las instrucciones de instalación.$(NC)\n"; \
		exit 1; \
	fi
else
	@if ! pkg-config --exists libpcap 2>/dev/null && \
		[ ! -f /usr/include/pcap/pcap.h ] && \
		[ ! -f /usr/include/pcap.h ]; then \
		printf "$(RED)[!] libpcap no encontrada. Ejecuta 'make deps' para instalar dependencias.$(NC)\n"; \
		exit 1; \
	fi
endif

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
ifeq ($(UNAME_S),Darwin)
	@printf "$(YELLOW)╔════════════════════════════════════════════════════════╗$(NC)\n"
	@printf "$(YELLOW)║          Instalación de dependencias - macOS          ║$(NC)\n"
	@printf "$(YELLOW)╚════════════════════════════════════════════════════════╝$(NC)\n"
	@printf "\n"
	@printf "$(BLUE)[1] Xcode Command Line Tools (RECOMENDADO):$(NC)\n"
	@printf "    xcode-select --install\n"
	@printf "\n"
	@printf "$(BLUE)[2] Homebrew (alternativa):$(NC)\n"
	@printf "    brew install libpcap\n"
	@printf "\n"
	@printf "$(YELLOW)[i] Después de instalar, ejecuta 'make' de nuevo.$(NC)\n"
else
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
endif

# --- PHONY --- #
.PHONY: all clean fclean re deps check-pcap