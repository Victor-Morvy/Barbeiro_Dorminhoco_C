# Barbeiro_Dorminhoco_C
Implementação do desafio barbeiro dorminhoco em C, com semaphores e multi processos

## Introdução
Este projeto foi dado como trabalho para entrega pelo professor Cesar Tegani Tofanini, na matéria de Programação distribuída, paralela e concorrente na Universidade Padre Anchieta de Jundiaí - SP. E tem como o objetivo implantar o desafio do Barbeiro Dorminhoco utilizando semaphores na linguagem C, sem a utilização de Mutex.

## Objetivo
Implantar o desafio "Barbeiro Dorminhoco" em C, utilizando semaphores.

## Metodologia
- O barbeiro abre a loja, e dorme.
- Caso algum cliente chegue, ou for o próximo na cadeira de espera, ele acordará o barbeiro que inicia o corte de cabelo.
- Ao finalizar o corte, o cliente vai embora, e o barbeiro volta a dormir.
- Caso algum outro cliente chegue e o barbeiro estiver cortando o cabelo, este cliente tetará sentar na cadeira de espera.
- Se não tiver espaço nas cadeiras de espera, o cliente irá embora.
- Se não houver clientes para atender, o barbeiro irá dormir.

## Utilização
Para iniciar o programa como o barbeiro, é necessário inicia-lo com o parâmetro "BARBEIRO", e para iniciar o programa como cliente, é necessário o parâmetro "CLIENTE".
Para cada programa com o parâmetro aberto, é um cliente a mais que iniciará a rotina de cliente.

#### Obs.: Esta barbearia é pequena e comporta apenas 01 barbeiro.

## Variáveis globais
- QTTOTAL (Quantidade total de cadeiras para espera).
- TEMPO (Tempo que o barbeiro leva para cortar o cabelo dos clientes).
