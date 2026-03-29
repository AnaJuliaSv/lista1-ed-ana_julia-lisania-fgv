Repositório destinado a entrega da lista 1 da disciplina de Estrutura de Dados.

## Descrição do Sistema

O repositório em questão implementa e simula o projeto de um sistema de reservas de salas. 
No contexto do sistema, salas podem ser reservadas de segunda à sexta-feira, com horários de 7 da manhã até às 21 horas da noite. Cada disciplina é única dentro do sistema. 

Cada sala tem um número identificador e uma capacidade máxima de alunos, e não pode possuir duas reservas no mesmo dia e horário. Uma disciplina pode reservar quantas horas lhe forem necessárias para utilizar a sala, contudo, as restrições acima com relação a capacidade e horários de sala devem ser respeitadas.

Existem duas classes principais para o sistema:

1. ReservationRequest : responsável por ditar como será uma requisição de reserva, e todos os parâmetros que ela deverá ter.
```c++
ReservationRequest request(nome_disciplina, dia_semana, hora_inicio, hora_termino, qtd_estudantes);
```

2. ReservationSystem : onde as operações com requisição de reserva serão modeladas, tais como: reservar, cancelar e exibir o quadro de horários semanal de cada sala.  Um objeto dessa classe define quantas salas estão disponíveis para uso no prédio e qual é a capacidade de cada uma delas.
```c++
ReservationSystem reservation_system(5, {60, 40, 40, 35, 50});
```


## Instruções de Compilação

O repositório foi todo programado na linguagem C++, dessa forma, é necessário compilar os arquivos antes de, de fato, executar o programa. As instruções abaixo são para compilar os arquivos .cpp do repositório, todos de uma vez:

1. Certifique-se que seus arquivos .hpp estão na mesma pasta que os arquivos .cpp.
2. Certifique-se de ter o 'g++' instalado na sua máquina.
3. Em seu terminal, dentro da pasta em que estão os seus arquivos, execute o comando:
```bash
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o main_reserve
```
Após o comando, será criado nessa mesma pasta um arquivo executável.


## Instruções de Execução

Agora sim, após compilar, para executar o arquivo você deve voltar à seu terminal e rodar o comando:

- **Windows**
```bash
.\main_reserve.exe
```

- **Linux**
```bash
./main_reserve
```


## Estrutura de Dados do Sistema

Dentro do sistema, cada instância de ReservationRequest criada e reservada com sucesso pela instância de ReservationSystem, é colocado em array de tipo struct Reservation, interna à ReservationSystem. Um objeto dessa struct tem os mesmos atributos que uma instância request teria, guardando assim, todos os dados da requisição de reserva que for bem sucedida. Se a requisição feita puder ser atendida, uma nova reserva é adicionada ao array de reservas na última posição de memória, e a contagem de reservas totais, na variável destinada à contagem, é atualizada.

Através da contagem de reservas totais, conseguimos acessar cada uma das reservas já feitas pelo sistema e registradas no array do tipo Reservation. No mais, o sistema mantém constante a quantidade de salas totais disponíveis para alocação e suas capacidades, que são armazenadas em um array de inteiros. 
