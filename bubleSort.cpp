// Aluno: Guilherme Moro Guioti - 2262910
// Link planilha google sheets: https://docs.google.com/spreadsheets/d/1iCdzzmxq3TQKLZZYLcP2yU1SEVxffPIM31FEvYhgOrc/edit?usp=sharing
// Repositorio GitHub: https://github.com/GuilhermeGuioti/bubleSort.git

//A Complexidade: O(n2) - Algoritmo Bubble Sort, segue a lógica onde o esforço cresce ao quadrado do número de registros.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;

// Função para ler os nomes do arquivo e armazená-los em um vetor
void readAndWriteFile(vector<string> &names){
   ifstream arquivo("nomes.txt");

   if (!arquivo.is_open()) {
      cerr << "ERRO: O arquivo 'nomes.txt' nao foi encontrado na pasta do projeto!" << endl;
      return;
   }

   char c;
   string nomeAtual;
   bool dentroDasAspas = false;

   while (arquivo.get(c)) {
      if (c == '\'') {
         if (dentroDasAspas) {
            if (!nomeAtual.empty()) {
               names.push_back(nomeAtual);
               nomeAtual = "";
            }
            dentroDasAspas = false;
         } else {
            dentroDasAspas = true;
         }
      } else if (dentroDasAspas) {
         nomeAtual += c;
      }
   }

   arquivo.close();
};

// Função para ordenar os nomes usando o algoritmo Bubble Sort
void bubbleSort(vector<string> &names, long long &totalTrocas, long long &iteracoes) {
   // A cada iteração, o maior elemento é colocado na posição correta, então o próximo loop pode ignorar os últimos elementos já ordenados
   for (size_t i = 0; i < names.size() - 1; i++) {
      for (size_t j = 0; j < names.size() - 1 - i; j++) {
         iteracoes++; // Incrementa o contador de iterações a cada comparação realizada
         if (names[j] > names[j + 1]) {
            // Troca os nomes de posição
            swap(names[j], names[j + 1]);       
            totalTrocas++; // Incrementa o contador de trocas a cada vez que uma troca é realizada
         }
      }
   }
};

int main() {
   vector<string> todosOsNomes;
   readAndWriteFile(todosOsNomes);

   // Lista de quantidades de registros para testar, variando de 1.000 a 120.000 em incrementos de 10.000
   vector<int> quantidades = {1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000};

   cout << left << setw(15) << "Registros" << setw(20) << "Iteracoes" << setw(20) << "Trocas" << "Tempo (s)" << endl;
   cout << "-----------------------------------------------------------------" << endl;

   for (int qtd : quantidades) {
      // Verifica se o arquivo tem nomes suficientes para este teste
      if (qtd > todosOsNomes.size()) break;

      // Cria uma sublista com 'qtd' elementos para teste
      vector<string> sublista(todosOsNomes.begin(), todosOsNomes.begin() + qtd);
      long long iteracoes = 0;
      long long trocas = 0;

      // Início da medição de tempo
      auto inicio = chrono::high_resolution_clock::now();
      
      // Chama a função de ordenação
      bubbleSort(sublista, trocas, iteracoes);
      
      auto fim = chrono::high_resolution_clock::now();
      chrono::duration<double> duracao = fim - inicio;
      // Fim da medição de tempo

      // Exibição formatada para facilitar a cópia para Excel/Google Sheets
      cout << left << setw(15) << qtd 
            << setw(20) << iteracoes 
            << setw(20) << trocas 
            << fixed << setprecision(4) << duracao.count() << endl;
   }

   return 0;
};