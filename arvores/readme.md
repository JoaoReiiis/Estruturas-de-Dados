# ABB, AVL e Árvores Rubro-Negras em C++

Este repositório contém três implementações em C++ de árvores de busca:

1. **Árvore Binária de Busca (ABB)**
2. **Árvore AVL (AVL Tree)**
3. **Árvore Rubro-Negra (Red-Black Tree)**

Ambas suportam inserção e remoção recursiva e vários tipos de percorrimentos. A versão AVL adiciona balanceamento automático através de rotações, e a versão Rubro-Negra também utiliza balanceamento com propriedades específicas de coloração.

## Funcionalidades

- **Inserção recursiva**: adiciona novos nós mantendo as propriedades de busca.
- **Remoção recursiva**: remove nós mantendo as propriedades de busca.
- **Percursos**:
  - **Em Ordem (In-Ordem)**: visita nós em ordem crescente de valores (esquerda, raiz, direita).
  - **Pré-Ordem (Pre-Ordem)**: visita a raiz primeiro, depois os nós esquerda e direita (raiz, esquerda, direita).
  - **Pós-Ordem (Post-Ordem)**: visita os nós esquerda, depois direita e, finalmente, a raiz (esquerda, direita, raiz).
- **Balanceamento (AVL)**: garante que a altura da árvore permaneça O(log n) após cada inserção.
- **Balanceamento (Rubro-Negra)**: mantém o balanceamento através de rotações e recolormento, garantindo que a árvore permaneça aproximadamente balanceada após cada inserção.

## Instruções de Uso

1. **Compilar o código**:

```bash
# Para ABB:
g++ -std=c++17 abb.cpp -o abb

# Para AVL:
g++ -std=c++17 avl.cpp -o avl

# Para Árvore Rubro-Negra:
g++ -std=c++17 rubro_negra.cpp -o rubro_negra
```
2. **Executar**:

   ```bash
   ./abb   # testando a ABB
   ./avl   # testando a AVL
   ./rn    # testando a RN
   ```

   Cada programa insere um conjunto de valores pré-definidos, realiza o percurso em ordem e imprime o resultado.

## Como Funcionam as Árvores

### 1. Árvore Binária de Busca (ABB)

- Cada nó possui no máximo dois filhos: **esquerdo** e **direito**.
- Propriedade principal: para todo nó `N`:
  - Valores na subárvore esquerda < `N`.
  - Valores na subárvore direita > `N`.

**Inserção Recursiva**:
1. Se o nó atual é `nullptr`, cria-se um novo nó.
2. Se o valor a inserir é menor, chama-se recursivamente na subárvore esquerda.
3. Caso contrário, chama-se recursivamente na subárvore direita.
4. Atualiza-se o ponteiro do pai para o nó retornado.

**Percurso In-Order**:
1. Visita recursiva à subárvore esquerda.
2. Processa (imprime) o valor do nó.
3. Visita recursiva à subárvore direita.

**Complexidade**: O(h), onde h é a altura da árvore. No pior caso (desbalanceada), h = n.

### 2. Árvore AVL

É uma ABB que mantém a altura balanceada. Para cada nó, define-se:

```
altura(n) = 1 + max(altura(n->esquerdo), altura(n->direito))
fatorBalanceamento(n) = altura(n->esquerdo) - altura(n->direito)
```

- Se o fator de balanceamento estiver fora de {-1, 0, 1}, aplica-se rotações para restaurar o balanceamento:
  - **Rotação Simples à Direita (LL)**
  - **Rotação Simples à Esquerda (RR)**
  - **Rotação Dupla Esquerda-Direita (LR)**
  - **Rotação Dupla Direita-Esquerda (RL)**

**Fluxo de Inserção**:
1. Insere o novo valor como em uma ABB comum.
2. Ao retornar da recursão, calcula-se a altura e fator de balanceamento de cada nó no caminho de volta.
3. Se necessário, aplica-se a rotação adequada:
   - Caso LL: fatorBalanceamento(n) > 1 e fatorBalanceamento(n->esquerdo) >= 0
   - Caso LR: fatorBalanceamento(n) > 1 e fatorBalanceamento(n->esquerdo) < 0
   - Caso RR: fatorBalanceamento(n) < -1 e fatorBalanceamento(n->direito) <= 0
   - Caso RL: fatorBalanceamento(n) < -1 e fatorBalanceamento(n->direito) > 0

**Vantagem**: a árvore permanece balanceada, garantindo O(log n) em todas as operações.

---

### 3. Árvore Rubro-Negra

Árvore Rubro-Negra é uma árvore binária de busca balanceada, com as seguintes propriedades adicionais:

    Todo nó é vermelho ou preto.
    A raiz é sempre preta.
    Todas as folhas (NIL) são pretas.
    Se um nó é vermelho, então ambos os filhos são pretos (não há dois nós vermelhos consecutivos).
    Para cada nó, todos os caminhos do nó até folhas descendentes contêm o mesmo número de nós pretos.

Inserção:

    Insere o nó como vermelho (exceto a raiz que deve ser preta).
    Se o pai for vermelho, ajusta-se a árvore com rotações e mudanças de cor para manter as propriedades.

Balanceamento:

    Utiliza rotações (simples e duplas) e mudança de cores para manter as propriedades da árvore rubro-negra após a inserção.

Complexidade: Operações de busca, inserção e remoção são executadas em O(log n) devido ao balanceamento mantido nas operações da árvore.
