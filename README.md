# SortBenchmark

Este projeto realiza o benchmark de alta performance de algoritmos de ordenação utilizando a biblioteca **Google Benchmark**. Ele está otimizado para sistemas de larga escala (4M+ elementos) e suporta compilação multiplataforma.

## Requisitos Mínimos

*   **Compilador C++:** Suporte a C++17 (GCC 9+, Clang 10+ ou MSVC 2019+).
*   **CMake:** Versão 3.10 ou superior.
*   **Google Benchmark:** A biblioteca deve estar instalada no sistema.
    *   *Linux:* `sudo apt install libbenchmark-dev`
    *   *Windows:* `vcpkg install benchmark:x64-windows` (ou via build manual).

## Como Compilar e Rodar

### Opção 1: Via Terminal (Linux ou Windows com Make)
Se você possui o `make` instalado, utilize os atalhos:

```bash
make run      # Compila em modo Release e executa o benchmark
make clean    # Remove a pasta de build
```

### Opção 2: Via Visual Studio (Windows)
1. Abra o Visual Studio e selecione **"Abrir uma Pasta Local"**.
2. Escolha a raiz deste projeto. O VS detectará o arquivo `CMakeLists.txt` automaticamente.
3. Altere a configuração de build para **Release** no menu superior.
4. Pressione **F5** ou o botão de "Play" para compilar e executar.

### Opção 3: Via CMake Direto
Caso prefira não usar o Makefile:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/bin/sortbenchmark.out
```
