# Nome do diretório de build
BUILD_DIR = build

# Comando padrão: configura e compila
all:
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(BUILD_DIR)

# Atalho para rodar o benchmark após compilar
run: all
	@./$(BUILD_DIR)/sortbenchmark.out

# Limpeza total: apaga a pasta build inteira
clean:
	@rm -r $(BUILD_DIR)
	@echo "Pasta $(BUILD_DIR) removida."