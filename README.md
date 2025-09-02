# Batalha Naval

Este projeto implementa um jogo de Batalha Naval em C, com um tabuleiro 10x10, quatro navios posicionados (dois em direções ortogonais e dois em diagonais) e três habilidades especiais com áreas de efeito (Cone, Cruz e Octaedro). O programa atende aos requisitos dos desafios de nível novato, intermediário e avançado.

## Pré-requisitos

- **Compilador C**: Um compilador compatível com C, como `gcc` (GNU Compiler Collection), deve estar instalado.
- **Sistema operacional**: O programa foi testado em sistemas baseados em Unix (Linux, macOS) e Windows (com MinGW ou Cygwin, por exemplo).
- **Ferramentas**: Certifique-se de ter o `make` (opcional, para automação) ou um terminal para executar comandos de compilação.

## Instruções de Compilação

1. **Salve o código-fonte**:
   - Copie o código do arquivo `batalha_naval.c` para um arquivo com o mesmo nome no seu computador.

2. **Compile o programa**:
   - Abra um terminal na pasta onde o arquivo `batalha_naval.c` está localizado.
   - Execute o seguinte comando para compilar o programa usando o `gcc`:
     ```bash
     gcc batalha_naval.c -o batalha_naval
     ```
   - Isso gerará um executável chamado `batalha_naval` (ou `batalha_naval.exe` no Windows).

3. **Verifique erros**:
   - Se houver erros de compilação, verifique se o compilador está instalado corretamente e se o código-fonte foi copiado sem alterações.

## Instruções de Execução

1. **Execute o programa**:
   - No terminal, na mesma pasta do executável, execute:
     ```bash
     ./batalha_naval
     ```
   - No Windows, use:
     ```bash
     batalha_naval.exe
     ```

2. **Saída esperada**:
   - O programa exibirá o tabuleiro 10x10 com:
     - `~` para água (posições vazias).
     - `N` para navios (quatro navios posicionados).
     - `X` para áreas de efeito das habilidades (Cone, Cruz e Octaedro).
   - O tabuleiro inclui índices de linhas e colunas para facilitar a visualização.
   - Exemplo de saída parcial:
     ```
     Tabuleiro com navios e áreas de efeito:
        0  1  2  3  4  5  6  7  8  9
      0  ~  ~  ~  ~  ~  ~  ~  X  ~  ~
      1  ~  N  ~  ~  ~  ~  X  N  X  ~
      2  ~  ~  ~  N  N  N  X  X  X  ~
      ...
     ```

3. **Erros durante a execução**:
   - Se aparecer uma mensagem como "Erro: Posição inválida para o navio X!", o programa detectou uma sobreposição ou posição fora dos limites. Nesse caso, revise as coordenadas dos navios no código (variável `navios` na função `main`).

## Estrutura do Código

- **Tabuleiro**: Matriz 10x10 inicializada com zeros (água).
- **Navios**: Quatro navios de tamanho 3, posicionados nas coordenadas [2,3] (horizontal), [6,7] (vertical), [1,1] (diagonal crescente) e [3,8] (diagonal decrescente).
- **Habilidades**:
  - **Cone**: Área de efeito em forma de triângulo, centrada em [4,4].
  - **Cruz**: Área de efeito em forma de cruz, centrada em [7,2].
  - **Octaedro**: Área de efeito em forma de losango, centrada em [1,7].
- **Validações**: O programa verifica se os navios e habilidades estão dentro dos limites do tabuleiro e não se sobrepõem.

## Notas Adicionais

- O programa não requer entrada do usuário; todas as coordenadas são fixas no código.
- As habilidades são aplicadas sem lógica de dano, apenas marcando as áreas de efeito.
- Para modificar posições de navios ou habilidades, edite as estruturas `navios` e `origens` na função `main` do arquivo `batalha_naval.c`.

## Problemas Comuns e Soluções

- **Erro: "gcc não encontrado"**:
  - Instale o `gcc` no seu sistema:
    - Linux: `sudo apt-get install gcc` (Ubuntu/Debian) ou equivalente.
    - macOS: Instale o Xcode Command Line Tools com `xcode-select --install`.
    - Windows: Instale o MinGW ou use um ambiente como Cygwin.
- **Saída desalinhada**:
  - Certifique-se de usar um terminal com fonte monoespaçada para alinhamento correto.
- **Navios ou habilidades não aparecem**:
  - Verifique se as coordenadas definidas em `navios` e `origens` estão dentro dos limites do tabuleiro (0 a 9).
