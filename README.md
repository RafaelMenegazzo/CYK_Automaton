# CYK Parser em C

Este é um analisador sintático baseado no algoritmo **CYK (Cocke–Younger–Kasami)**, implementado em linguagem **C**, que verifica se uma string pertence à linguagem gerada por uma **gramática livre de contexto** na **Forma Normal de Chomsky (CNF)**.

## Sobre o Projeto

O projeto permite:

- Utilizar uma **gramática padrão** de exemplo.
- Criar sua **própria gramática** (desde que esteja na CNF).
- Testar múltiplas strings para verificar se são aceitas.
- Visualizar a **tabela CYK** gerada durante o processo de análise.

Este projeto é ideal para estudantes e professores de **compiladores**, **linguagens formais**, **autômatos** e **gramáticas**.

---

## 🔧 Compilação

### Pré-requisitos

- Compilador `gcc` ou compatível.
- Ambiente Unix/Linux, WSL ou MinGW (Windows).

### Como compilar

```bash
gcc -std=c11 -Wall -Wextra cyk_demo.c -o cyk_demo
