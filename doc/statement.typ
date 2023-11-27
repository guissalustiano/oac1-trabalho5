#import "template.typ": *

#show: project.with(
  title: "Atividade 5 - Org. Arg. 1",
  authors: (
	"Profa. Dra. Cíntia Borges Margi (cintia@usp.br)",
	"Guilherme S. Salustiano (salustiano@usp.br)",
  ),
)
#show link: underline

== Contexto
Cache é um conceito universal da computação, usado em diversas contextos para melhorar o desempenho de programs.
Nessa atividade iremos implementar e analisar o cache para um banco de dados chave valor inspirado no cache estudado do RISC-V.

O banco de dados é o mais simples possível com apenas duas funções:
```c
db_data_t get(db_key_t key);
void put(db_key_t key, db_data_t data);
```
O `put` salva o valor `data` em um arquivo com o nome `key` e o `get` lê o arquivo com o nome `key` e retorna o valor salvo. 
Isso é propositalmente lento.

Sendo a chave um número inteiro sem sinal de 64 bits e o valor uma struct de 32 bytes definidos em `database_t.h`.

== Tarefa
Você deve implementar um cache associativo com o número de conjuntos configurável pela variável `ASSOCIATIVITY` no arquivo `database.h`.
Você deve usar a variável `static cache_entry_t cache[CACHE_SIZE];` para armazenar o cache, não é permitido usar outras variáveis globais.
Em caso de hit você deve também incrementar o valor de cache_hits;

Você pode baixar o código base #link("https://github.com/guissalustiano/oac1-trabalho3/tree/main/float_lib")[no repositorio do experimento], disponivel da pasta `src`.
Um makefile também foi fornecido para facilitar a compilação e execução do programa, para executar basta rodar `make run`.

Após terminar a implementação, você deve rodar o programa para diferentes valores de `ASSOCIATIVITY` e gerar um arquivo `brenchmark.txt` com os resultados.
Para fazer isso basta executar o comando abaixo:
```bash
make -s run_brenchmark
```

Atenção, isso altera o valor de `ASSOCIATIVITY` no arquivo `database.h`, para voltar ao valor padrão você pode rodar `make reset`.

= Entrega final
Ao final, gere um zip `atv5.zip` com os arquivos.
```bash
atvr5.zip
├── database.c
├── brenchmark.txt
```

#bibliography("references.bib")
