# 2048

## Para compilar e executar o jogo, use os comandos:

```gcc
gcc main.c fila_dinamica.c tabuleiro.c arquivo.c bubble_sort.c -o main.exe
```

```cmd
main.exe (Windows)
```

```bash
./main.exe (Linux)
```

## TODO 

- [x]  Adicionar a lógica de soma para linhas e colunas:
    - Deslizar e combinar para a direita 
    - Deslizar e combinar para a esquerda
    - Deslizar e combinar para cima
    - Deslizar e combinar para baixo

 - [x]  Verificar se a jogada é válida (uma peça foi movida ou combinada):
    
    - Implementar uma função que verifica se o estado do tabuleiro mudou após uma jogada. Se não houver mudança, a jogada é inválida e um novo tile não deve ser adicionado.
 
 - [x] Condição de Derrota:
    
    - Verificar se não há mais movimentos possíveis ou espaços vazios.

- [ ] Refinar a interface do jogo:

  -  Melhorar a impressão do tabuleiro e fornecer feedback claro ao usuário sobre o estado do jogo (por exemplo, vitória, derrota, jogadas inválidas, cores por numeros).
  
  
- [x] Arquivos:
     - Criar, apagar e acessar um perfil (sem senha), composto por um nome de no máximo 3 letras, todas maiúsculas.  
     
     - Exibir todos os perfis.
     
     - Visualizar os primeiros 10 perfis, ordenados por ambos os tipos de pontuação.
     
     - Buscar um perfil a partir de seu nome, e exibir suas pontuações máximas. (Deve ser possível mesmo que não seja um dos 10 primeiros em nenhuma das duas pontuações).
