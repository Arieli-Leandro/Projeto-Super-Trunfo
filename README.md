# 🎮 UnderTrunfo — Super Trunfo inspirado em Undertale

Um projeto desenvolvido em grupo como trabalho final da disciplina **Fundamentos da Programação 2**, utilizando a linguagem C e a biblioteca Raylib. O UnderTrunfo combina a mecânica clássica do Super Trunfo com uma identidade visual inspirada no universo de *Undertale*, incluindo artes em pixel art desenhadas pixel por pixel pela equipe.

## 🖤 Sobre o projeto

O UnderTrunfo é um jogo de cartas em que o jogador enfrenta uma CPU, escolhendo atributos de suas cartas para disputar cada rodada. A temática, os personagens e a interface foram desenvolvidos para trazer a atmosfera de Undertale à experiência de jogar Super Trunfo.

Além da partida, o projeto conta com um sistema de gerenciamento de cartas, permitindo cadastrar, consultar, alterar e excluir cartas do baralho. Dessa forma, o trabalho reúne conceitos de programação em C, manipulação de dados, desenvolvimento de jogos e criação de interfaces gráficas.

## ✨ Funcionalidades

### 🃏 Partida de Super Trunfo
- Partidas entre o jogador e a CPU.
- Seleção de atributos para disputar cada rodada.
- Comparação dos atributos das cartas.
- Embaralhamento e distribuição das cartas entre os jogadores.
- Contagem de cartas durante a partida.
- Sistema de vitória, derrota e encerramento de jogo.
- Opção de jogar novamente.
- Configuração da dificuldade da CPU.

### 📚 Gerenciamento de cartas
- **Criar cartas:** cadastrar novas cartas e definir seus atributos.
- **Visualizar cartas:** consultar as cartas cadastradas.
- **Alterar cartas:** modificar informações e atributos de cartas existentes.
- **Deletar cartas:** remover cartas do conjunto cadastrado.

As cartas possuem nome, classificação e os atributos **Fight, IQ, Danger e Mercy**, além da identificação de uma carta especial Super Trunfo.

### 🎨 Interface e recursos visuais
- Interface gráfica desenvolvida com Raylib.
- Artes em pixel art desenhadas pixel por pixel pela equipe.
- Elementos visuais inspirados em Undertale.
- Animações durante a partida.
- Efeitos sonoros e música.
- Telas de carregamento, pausa e fim de jogo.
- Opções para controlar música e efeitos sonoros.

### 💻 Compatibilidade
- Suporte à compilação no Windows e no Linux.
- Makefile para facilitar o processo de compilação em ambos os sistemas operacionais.

## 🛠️ Tecnologias utilizadas

- **C:** linguagem utilizada para implementar a lógica do jogo e o gerenciamento das cartas.
- **Raylib:** biblioteca utilizada para desenvolver a interface gráfica, renderizar imagens, tratar entradas e reproduzir recursos audiovisuais.
- **Raygui:** biblioteca auxiliar para a criação de elementos de interface.
- **Makefile:** automação do processo de compilação.
- **Git e GitHub:** versionamento e colaboração no desenvolvimento do projeto.

## 🎯 Objetivos acadêmicos

O desenvolvimento do UnderTrunfo teve como objetivo aplicar, na prática, os conhecimentos adquiridos na disciplina de Fundamentos da Programação 2, integrando lógica de programação, organização do código, manipulação de estruturas de dados e desenvolvimento de um jogo completo.

O projeto também proporcionou experiência com bibliotecas gráficas, criação de recursos visuais, gerenciamento de funcionalidades e desenvolvimento colaborativo de software.

## 👥 Equipe

Projeto desenvolvido em grupo para a disciplina **Fundamentos da Programação 2**.

Equipe Executora: Arieli Leandro, Gustavo Henrique, Gustavo Gaspar

## 📌 Observações

Este projeto foi desenvolvido com finalidade acadêmica. Undertale e seus elementos originais pertencem aos seus respectivos criadores e detentores de direitos. As artes produzidas pela equipe foram desenvolvidas especificamente para o projeto.

## ⚙️ Como compilar e executar

O UnderTrunfo utiliza um `Makefile` para automatizar a compilação do jogo e do gerenciador de cartas. O processo é adaptado para Windows e Linux.

### 📋 Pré-requisitos

Antes de compilar, verifique se você possui:

- **GCC:** compilador utilizado para compilar os arquivos em C.
- **Make:** ferramenta responsável por executar as instruções do `Makefile`.
- **Raylib:** biblioteca utilizada para gráficos, áudio e funcionalidades do jogo. O projeto inclui arquivos de biblioteca e cabeçalhos em suas pastas correspondentes.

No Windows, é necessário utilizar um ambiente que disponibilize o GCC e o Make, como o MSYS2 com MinGW-w64. No Linux, instale o GCC, o Make e as dependências de desenvolvimento necessárias para a Raylib.

### 📥 1. Baixe o projeto

Clone o repositório utilizando o Git:

```bash
git clone https://github.com/Arieli-Leandro/Projeto-Super-Trunfo.git
```

Em seguida, entre na pasta do projeto:

```bash
cd Projeto-Super-Trunfo
```

Após esses comandos, você estará na pasta que contém os diretórios `build`, `game` e `gerenciador`, além dos arquivos `README.md` e `makefile`.

### 🔨 2. Compile o projeto

No terminal, dentro da pasta que contém o `Makefile`, execute:

```bash
make
```

Esse comando compila tanto o jogo quanto o gerenciador de cartas. Os executáveis são gerados na pasta `build`, seguindo esta estrutura:

```text
build/
├── gerenciador       # Gerenciador de cartas (Linux)
└── bin/
    └── undertale_trunfo  # Executável do jogo (Linux)
```

No Windows, os executáveis recebem a extensão `.exe`.

### 🎮 3. Execute o jogo

Para compilar e executar o jogo, utilize:

```bash
make run-game
```

Esse comando executa o jogo com os argumentos definidos no `Makefile` para cada sistema operacional.

### 🃏 4. Execute o gerenciador de cartas

Para abrir o programa responsável pelo gerenciamento das cartas, utilize:

```bash
make run-ger
```

O gerenciador permite trabalhar com as cartas do jogo, incluindo as funcionalidades de criação, visualização, alteração e exclusão.

### 🧹 5. Limpe os arquivos compilados

Para remover os executáveis gerados, execute:

```bash
make clean
```

Também é possível remover apenas o executável do gerenciador:

```bash
make clean-ger
```

Ou apenas o executável do jogo:

```bash
make clean-game
```

Para compilar novamente após a limpeza, execute `make`.

## 🕹️ Controles do jogo

- **V:** abre o menu de pausa, no qual é possível sair do jogo e habilitar ou desabilitar os efeitos sonoros e a música.
- **Q:** alterna o modo de tela cheia, conforme implementado no jogo.


