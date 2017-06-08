# Estrutura de Dados

Este é o repositório de desenvolvimento do trabalho de Estrutura de Dados. IFES - Serra 2017

Uma empresa que fabrica rolamentos possui maquinarios para
produzi-los, requisicoes de pedidos e um tecnico para consertar quando
uma maquina quebra. O processo dela funcionar eh o seguinte:
chega um pedido de um rolamento especifico, podendo ser cilindrico,
conico, esferico de aco ou de titanio.

cada rolamento tem uma ordem a ser seguida nas maquinas e um tempo pra
ficar la dentro sendo processada, alem de uma prioridade especifica
pra cada pedido. por isso, as maquinas possuem filas de prioridade
aonde os pedidos vao ficando a medida que vao requisitando seu uso.
somente depois de sair da ultima maquina que o pedido deveria ficar,
eh que finalmente o pedido fica pronto.

Um rolamento cilindrico possui prioridade 1, o conico possui prioridade
2, e esferico prioridade 3. Quanto maior o numero, mais urgente eh o pedido.

a media de chegada de um pedido de rolamento cilindrico eh de 21.5 ,
de um conico 19.1 e de um esferico 8.0.

a ordem do maquinario para um rolamento cilindrico eh TORNO,FRESA,TORNO,MANDRIL.
a ordem do maquinario para um rolamento conico eh TORNO,MANDRIL,TORNO.
a ordem do maquinario para um rolamento esferico de aco eh FRESA,MANDRIL,TORNO.
a ordem do maquinario para um rolamento esferico de titanio eh FRESA,MANDRIL,TORNO,FRESA,TORNO.

o tempo de estadia no mandril eh 1.2 , 2.1 , 1.4 e 1.5 para
cilindrico, conico, aco e titanio, respectivamente.

o tempo de estadia na fresa eh 0.5 , 0.5 e 0.6 para cilindrico, aco e
titanio, respectivamente.

o tempo de estadia no torno eh 0.8 , 1.8 , 1.0 e 1.6 para cilindrico,
conico, aco e titanio, respectivamente.

entao resumindo tudo:

Estadia_Mandril_Cilindrico 1.2
Estadia_Fresa_Cilindrico 0.5
Estadia_Torno_Cilindrico 0.8

Estadia_Mandril_Conico 2.1
Estadia_Torno_Conico 1.8

Estadia_Mandril_Esferico_Aco 1.4
Estadia_Fresa_Esferico_Aco 0.5
Estadia_Torno_Esferico_Aco 1.0

Estadia_Mandril_Esferico_Titanio 1.5
Estadia_Fresa_Esferico_Titanio 0.6
Estadia_Torno_Esferico_Titanio 1.6

Chegada_Media_Cilindrico 21.5
Chegada_Media_Conico 19.1
Chegada_Media_Esferico 8.0

Frequencia_Quebra_Mandril 1.0
Frequencia_Quebra_Fresa 0.5
Frequencia_Quebra_Torno 3.0

Tempo para consertar maquinas 20.0

sequencia_cilindrica eh TORNO,FRESA,TORNO,MANDRIL
sequencia_conica eh TORNO,MANDRIL,TORNO
sequencia_esferica_titanio eh FRESA,MANDRIL,TORNO,FRESA,TORNO
sequencia_esferica_aco eh FRESA,MANDRIL,TORNO

Seu objetivo eh fazer um simulador dessa empresa que usando todos os
dados definidos anteriormente e recebendo como argumento de entrada do
programa C um double que representará o tempo de simulacao total,
imprima na tela quantos rolamentos foram construidos de cada tipo e o
tempo medio de construcao de cada tipo. ps: faca o simulador dividindo
tudo em bibliotecas [ ou seja, varias , varios arquivos, etc. ] , faca 
pouco a pouco, juntar tudo de vez certamente baguncará sua cabeca e 
colocara ainda mais dificuldade na hora de debugar.

a funcao gera_exponencial abaixo retorna o tempo que vai demorar para
chegar outro pedido, passando como argumento a media de chegada do
pedido que voce quer saber.

float Gera_Exponencial (float avg)
{
    float u=0; /* Gera randomicamente um numero entre 0 e 1 */
    do u = (new random().nextFloat());
        while ((u==0) || (u==1));
    return (-avg * log (u));
}

para saber quanto tempo o rolamento vai ficar no maquinario, use a funcao abaixo:
2.0 * Estadia_Equipamento_Rolamento * new random().nextFloat()

PS: deve ser utilizado fila e lista nesse problema, [fila de prioridade] , structs,
alem de TADs. Flags nao serao aceitos, usem DEFINE para simular as prioridades.
Ponteiro para funcao será necessario em praticamente todas structs para nao ter que
saber qual tipo que foi passado e somente precisar saber em tempo real.



