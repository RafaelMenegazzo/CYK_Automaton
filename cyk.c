#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_RULES 50
#define MAX_SYMBOLS 10
#define MAX_STRING 20
#define MAX_INPUT 100
// Estrutura para representar uma regra de produção
typedef struct {
 char left; // Lado esquerdo da regra (não-terminal)
 char right[3]; // Lado direito da regra (até 2 símbolos)
 int length; // Comprimento do lado direito (1 ou 2)
} Rule;
// Estrutura para a gramática
typedef struct {
 Rule rules[MAX_RULES];
 int num_rules;
 char start_symbol;
} Grammar;
// Função para limpar buffer de entrada
void clear_input_buffer() {
 int c;
 while ((c = getchar()) != '\n' && c != EOF);
}
// Função para adicionar uma regra à gramática
void add_rule(Grammar* g, char left, char* right) {
 g->rules[g->num_rules].left = left;
 strcpy(g->rules[g->num_rules].right, right);
 g->rules[g->num_rules].length = strlen(right);
 g->num_rules++;
}
// Função para inicializar uma gramática de exemplo
void init_example_grammar(Grammar* g) {
 g->num_rules = 0;
 g->start_symbol = 'S';

 // Gramática de exemplo:
 // S -> AB | BC
 // A -> BA | a
 // B -> CC | b
 // C -> AB | a

 add_rule(g, 'S', "AB");
 add_rule(g, 'S', "BC");
 add_rule(g, 'A', "BA");
 add_rule(g, 'A', "a");
 add_rule(g, 'B', "CC");
 add_rule(g, 'B', "b");
 add_rule(g, 'C', "AB");
 add_rule(g, 'C', "a");
}
// Função para verificar se uma string está na Forma Normal de Chomsky
bool is_cnf_rule(char* right) {
 int len = strlen(right);

 // Regra A -> a (um terminal minúsculo)
 if (len == 1) {
 return islower(right[0]);
 }

 // Regra A -> BC (dois não-terminais maiúsculos)
 if (len == 2) {
 return isupper(right[0]) && isupper(right[1]);
 }

 return false;
}
// Função para escolher tipo de gramática
int choose_grammar_type() {
 int choice;

 printf("========================================\n");
 printf(" ALGORITMO CYK - ANALISADOR SINTÁTICO\n");
 printf("========================================\n\n");

 printf("Escolha uma opção:\n");
 printf("1. Usar gramática padrão (exemplo demonstrativo)\n");
 printf("2. Criar minha própria gramática\n");
 printf("3. Ver exemplo de gramática CNF\n");
 printf("\nEscolha (1-3): ");

 while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
 clear_input_buffer();
 printf("Opção inválida! Digite 1, 2 ou 3: ");
 }
 clear_input_buffer();

 return choice;
}
// Função para mostrar exemplo de CNF
void show_cnf_example() {
 printf("\n=== EXEMPLO DE GRAMÁTICA CNF ===\n");
 printf("Forma Normal de Chomsky (CNF) permite apenas:\n\n");
 printf("1. A -> a (não-terminal produz um terminal)\n");
 printf("2. A -> BC (não-terminal produz dois não-terminais)\n\n");
 printf("Exemplo de gramática CNF para expressões aritméticas simples:\n");
 printf("S -> AB | AC # S produz AB ou AC\n");
 printf("A -> a # A produz 'a'\n");
 printf("B -> BC | b # B produz BC ou 'b'\n");
 printf("C -> a # C produz 'a'\n\n");
 printf("Esta gramática aceita strings como: 'aba', 'aa', etc.\n\n");
 printf("DICAS IMPORTANTES:\n");
 printf("- Não-terminais: letras MAIÚSCULAS (A, B, C, S, ...)\n");
 printf("- Terminais: letras minúsculas (a, b, c, ...)\n");
 printf("- Cada regra: lado esquerdo -> lado direito\n");
 printf("- Lado direito: UM terminal OU DOIS não-terminais\n\n");
}
// Função para criar gramática personalizada
void create_custom_grammar(Grammar* g) {
 char input[MAX_INPUT];
 char left, right[3];

 printf("\n=== CRIAÇÃO DE GRAMÁTICA PERSONALIZADA ===\n");
 printf("IMPORTANTE: Todas as regras devem estar na Forma Normal de Chomsky(CNF)!\n\n");
 printf("Formato CNF aceito:\n");
 printf("- A -> a (não-terminal -> terminal minúsculo)\n");
 printf("- A -> BC (não-terminal -> dois não-terminais maiúsculos)\n\n");
 printf("Exemplos válidos:\n");
 printf(" S -> AB\n");
 printf(" A -> a\n");
 printf(" B -> CD\n");
 printf(" C -> b\n\n");

 g->num_rules = 0;

 // Definir símbolo inicial
 printf("Digite o símbolo inicial da gramática (letra maiúscula): ");
 scanf(" %c", &g->start_symbol);
 clear_input_buffer();

 if (!isupper(g->start_symbol)) {
 printf("AVISO: Símbolo inicial deve ser maiúsculo. Convertendo para %c.\n",
 toupper(g->start_symbol));
 g->start_symbol = toupper(g->start_symbol);
 }

 printf("\nAgora digite as regras de produção:\n");
 printf("Formato: X -> YZ ou X -> a\n");
 printf("Digite 'fim' quando terminar.\n\n");

 int rule_count = 1;
 while (g->num_rules < MAX_RULES) {
 printf("Regra %d: ", rule_count);

 if (!fgets(input, MAX_INPUT, stdin)) {
 break;
 }

 // Remover quebra de linha
 input[strcspn(input, "\n")] = 0;

 // Verificar se quer parar
 if (strcmp(input, "fim") == 0 || strcmp(input, "FIM") == 0) {
 break;
 }

 // Parsear entrada no formato "X -> YZ" ou "X -> a"
 if (sscanf(input, " %c -> %s", &left, right) == 2) {
 // Validar formato
 if (!isupper(left)) {
 printf("ERRO: O lado esquerdo '%c' deve ser um não-terminal (maiúsculo).\n",
left);
 continue;
 }

 if (!is_cnf_rule(right)) {
 printf("ERRO: Regra '%s' não está na Forma Normal de Chomsky!\n", right);
 printf("Use: um terminal minúsculo (a-z) OU dois não-terminais maiúsculos(AB). \n");
 continue;
 }

 // Adicionar regra válida
 add_rule(g, left, right);
 printf("✓ Regra adicionada: %c -> %s\n", left, right);
 rule_count++;

 } else {
 printf("ERRO: Formato inválido. Use: X -> YZ ou X -> a\n");
 printf("Exemplo: S -> AB ou A -> a\n");
 }
 }

 if (g->num_rules == 0) {
 printf("ERRO: Nenhuma regra válida foi adicionada. Usando gramática padrão.\n");
 init_example_grammar(g);
 return;
 }

 printf("\n✓ Gramática personalizada criada com %d regras.\n", g->num_rules);
};
// Função para verificar se um não-terminal pode derivar um terminal
bool can_derive_terminal(Grammar* g, char nonterminal, char terminal) {
 for (int i = 0; i < g->num_rules; i++) {
 if (g->rules[i].left == nonterminal &&
 g->rules[i].length == 1 &&
 g->rules[i].right[0] == terminal) {
 return true;
 }
 }
 return false;
}
// Função para verificar se um não-terminal pode derivar dois não-terminais
bool can_derive_nonterminals(Grammar* g, char nonterminal, char nt1, char nt2) {
 for (int i = 0; i < g->num_rules; i++) {
 if (g->rules[i].left == nonterminal &&
 g->rules[i].length == 2 &&
 g->rules[i].right[0] == nt1 &&
 g->rules[i].right[1] == nt2) {
 return true;
 }
 }
 return false;
}
// Função para imprimir a tabela CYK
void print_table(bool table[][MAX_STRING][MAX_SYMBOLS], int n, char*
nonterminals, int num_nt) {
 printf("\nTabela CYK:\n");
 printf("Linha i representa subcadeias de comprimento i+1\n");
 printf("Coluna j representa subcadeia começando na posição j\n\n");

 for (int i = n-1; i >= 0; i--) {
 printf("Comprimento %d: ", i+1);
 for (int j = 0; j <= n-i-1; j++) {
 printf("[");
 bool first = true;
 for (int k = 0; k < num_nt; k++) {
 if (table[i][j][k]) {
 if (!first) printf(",");
 printf("%c", nonterminals[k]);
 first = false;
 }
 }
 if (first) printf(" ");
 printf("] ");
 }
 printf("\n");
 }
}
// Função para obter índice do não-terminal
int get_nt_index(char nt, char* nonterminals, int num_nt) {
 for (int i = 0; i < num_nt; i++) {
 if (nonterminals[i] == nt) return i;
 }
 return -1;
}
// Algoritmo CYK principal
bool cyk_algorithm(Grammar* g, char* string) {
 int n = strlen(string);
 if (n == 0) {
 printf("String vazia - REJEITADA\n");
 return false;
 }

 // Identificar todos os não-terminais únicos
 char nonterminals[MAX_SYMBOLS];
 int num_nt = 0;

 for (int i = 0; i < g->num_rules; i++) {
 char nt = g->rules[i].left;
 bool found = false;
 for (int j = 0; j < num_nt; j++) {
 if (nonterminals[j] == nt) {
 found = true;
 break;
 }
 }
 if (!found) {
 nonterminals[num_nt++] = nt;
 }
 }

 // Tabela CYK: table[i][j][k] = true se nonterminals[k] pode derivar
 // substring de comprimento i+1 começando na posição j
 bool table[MAX_STRING][MAX_STRING][MAX_SYMBOLS];

 // Inicializar tabela completamente
 for (int i = 0; i < MAX_STRING; i++) {
 for (int j = 0; j < MAX_STRING; j++) {
 for (int k = 0; k < MAX_SYMBOLS; k++) {
 table[i][j][k] = false;
 }
 }
 }

 printf("Analisando string: \"%s\"\n", string);
 printf("Símbolos não-terminais encontrados: ");
 for (int i = 0; i < num_nt; i++) {
 printf("%c ", nonterminals[i]);
 }
 printf("\n\n");

 // Passo 1: Preencher diagonal principal (substrings de comprimento 1)
 printf("=== PASSO 1: Substrings de comprimento 1 ===\n");
 for (int j = 0; j < n; j++) {
 printf("Posição %d, símbolo '%c': ", j, string[j]);
 bool found_any = false;
 for (int k = 0; k < num_nt; k++) {
 if (can_derive_terminal(g, nonterminals[k], string[j])) {
 table[0][j][k] = true;
 printf("%c ", nonterminals[k]);
 found_any = true;
 }
 }
 if (!found_any) printf("nenhum");
 printf("\n");
 }

 // Passo 2: Preencher resto da tabela (substrings de comprimento 2 até n)
 printf("\n=== PASSO 2: Substrings de comprimento maior ===\n");
 for (int i = 1; i < n; i++) { // comprimento da substring - 1
 printf("\nComprimento %d:\n", i+1);
 for (int j = 0; j <= n-i-1; j++) { // posição inicial
 printf(" Posição %d-%d: ", j, j+i);
 bool found_any = false;

 // Tentar todas as divisões possíveis
 for (int k = 0; k < i; k++) { // ponto de divisão
 // Verificar se alguma regra A -> BC pode ser aplicada
 for (int nt = 0; nt < num_nt; nt++) {
 if (!table[i][j][nt]) { // Se ainda não está na tabela
 for (int b = 0; b < num_nt; b++) {
 for (int c = 0; c < num_nt; c++) {
 if (table[k][j][b] &&
 table[i-k-1][j+k+1][c] &&
 can_derive_nonterminals(g, nonterminals[nt], nonterminals[b],
nonterminals[c])) {
 table[i][j][nt] = true;
 printf("%c ", nonterminals[nt]);
 found_any = true;
 break;
 }
 }
 if (table[i][j][nt]) break;
 }
 }
 }
 }
 if (!found_any) printf("nenhum");
 printf("\n");
 }
 }

 // Imprimir tabela final
 print_table(table, n, nonterminals, num_nt);

 // Verificar se o símbolo inicial pode derivar a string inteira
 int start_index = get_nt_index(g->start_symbol, nonterminals, num_nt);
 bool accepted = (start_index >= 0) && table[n-1][0][start_index];

 printf("\n=== RESULTADO ===\n");
 printf("Símbolo inicial: %c\n", g->start_symbol);
 printf("String \"%s\" é %s pela gramática.\n",
 string, accepted ? "ACEITA" : "REJEITADA");

 return accepted;
}
// Função para imprimir a gramática
void print_grammar(Grammar* g) {
 printf("=== GRAMÁTICA ===\n");
 printf("Símbolo inicial: %c\n", g->start_symbol);
 printf("Regras de produção:\n");
 for (int i = 0; i < g->num_rules; i++) {
 printf("%c -> %s\n", g->rules[i].left, g->rules[i].right);
 }
 printf("\n");
}
// Função para testar strings personalizadas
void test_custom_strings(Grammar* g) {
 char test_string[MAX_STRING];
 char choice;

 printf("\n=== TESTE DE STRINGS ===\n");

 do {
 printf("\nDigite uma string para testar (máximo %d caracteres): ",
MAX_STRING-1);
 if (!fgets(test_string, MAX_STRING, stdin)) {
 break;
 }

 // Remover quebra de linha
 test_string[strcspn(test_string, "\n")] = 0;

 if (strlen(test_string) == 0) {
 printf("String vazia não é válida!\n");
 continue;
 }

 printf("\n----------------------------------------\n");
 printf("TESTANDO STRING: \"%s\"\n", test_string);
 printf("----------------------------------------\n");

 bool result = cyk_algorithm(g, test_string);

 printf("\n>>> RESULTADO: String \"%s\" é %s <<<\n",
 test_string, result ? "ACEITA" : "REJEITADA");

 printf("\nDeseja testar outra string? (s/n): ");
 scanf(" %c", &choice);
 clear_input_buffer();

 } while (choice == 's' || choice == 'S');
}
// Função principal
int main() {
 Grammar g;
 int choice = choose_grammar_type();

 switch (choice) {
 case 1:
 init_example_grammar(&g);
 break;
 case 2:
 create_custom_grammar(&g);
 break;
 case 3:
 show_cnf_example();
 printf("Pressione Enter para continuar com a gramática padrão...\n");
 getchar();
 init_example_grammar(&g);
 break;
 default:
 init_example_grammar(&g);
 break;
 }

 print_grammar(&g);

 // Testar algumas strings
 char test_strings[][MAX_STRING] = {"baaba", "ab", "aab", "baba", "aa"};
 int num_tests = 5;
 bool results[5]; // Para armazenar os resultados

 printf("Testando %d strings com o algoritmo CYK:\n\n", num_tests);

 for (int i = 0; i < num_tests; i++) {
 printf("========================================\n");
 printf("TESTE %d - String: \"%s\"\n", i+1, test_strings[i]);
 printf("========================================\n");

 results[i] = cyk_algorithm(&g, test_strings[i]);

 printf("\n");
 if (i < num_tests - 1) {
 printf("Pressione Enter para próximo teste...\n");
 getchar();
 }
 }

 printf("========================================\n");
 printf("RESUMO FINAL DE TODOS OS TESTES\n");
 printf("========================================\n");
 for (int i = 0; i < num_tests; i++) {
 printf("Teste %d - String \"%s\": %s\n",
 i+1, test_strings[i], results[i] ? "ACEITA" : "REJEITADA");
 }

 // Oferecer teste de strings personalizadas
 printf("\nDeseja testar strings personalizadas? (s/n): ");
 char test_choice;
 scanf(" %c", &test_choice);
 clear_input_buffer();

 if (test_choice == 's' || test_choice == 'S') {
 test_custom_strings(&g);
 }

 return 0;
}