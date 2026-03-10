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

      if(names.size() >= 100000) break;
   }

   arquivo.close();
};

// Função para ordenar os nomes usando o algoritmo Bubble Sort
void bubbleSort(vector<string> &names, long long &totalTrocas) {
   // A cada iteração, o maior elemento é colocado na posição correta, então o próximo loop pode ignorar os últimos elementos já ordenados
   for (size_t i = 0; i < names.size() - 1; i++) {
      for (size_t j = 0; j < names.size() - 1 - i; j++) {
         if (names[j] > names[j + 1]) {
            // Troca os nomes de posição
            swap(names[j], names[j + 1]);       
            totalTrocas++;
         }
      }
   }
};

int main() {
   vector<string> names; // Vetor para armazenar os nomes lidos do arquivo
   long long totalTrocas = 0; // Variável para contar o número total de trocas realizadas durante a ordenação
   
   readAndWriteFile(names);
   
   cout << "===========================================" << endl;
   cout << "Quantidade de nomes lidos: " << names.size() << endl;
   
   auto inicio = chrono::high_resolution_clock::now();
   // Ordena os nomes usando o algoritmo Bubble Sort e conta o número de trocas realizadas
   bubbleSort(names, totalTrocas);
   auto fim = chrono::high_resolution_clock::now();

   auto duracao = fim - inicio;
   auto minutos = chrono::duration_cast<chrono::minutes>(duracao);
   auto segundos = chrono::duration_cast<chrono::seconds>(duracao) % 60;
   auto ms = chrono::duration_cast<chrono::milliseconds>(duracao) % 1000;;
   
   // Exibe o tempo de execução formatado e o número total de trocas realizadas
   cout << "Tempo de execucao: " << setfill('0') << setw(2) << minutos.count() << ":" << setw(2) << segundos.count() << ":" << setw(2) << ms.count() << endl;
   cout << "Trocas realizadas: " << totalTrocas << endl;
   cout << "===========================================" << endl;


   return 0;
};