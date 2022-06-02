* Projeto 2: Concorrência entre processos

* Aluno: 
    * Rafael Avraham Gildin Acherboim - 31940242

* Esclarecimento dos 5 pontos propostos:

    1. 
    - A conta to pode/deve receber mais de uma transferência simultânea; 
    - R: A conta to só pode receber 1 transferência por vez. Para tal usou-se o mutex, que permite apenas 1 thread acessar à região crítica.
    2. 
    - A conta from pode enviar mais de uma transferência simultânea;
    - R: A conta from só pode enviar 1 transferência por vez. Para tal usou-se o mutex, que permite apenas 1 thread acessar à região crítica.
    3. 
    - A conta from não pode enviar dinheiro se não tiver mais saldo; 
    - R: Se uma das contas não tem saldo, ela não consegue transferir. Usar from.saldo = 0, to.saldo = 0
    4. 
    - A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar;
    - R: Com base nas threads criadas, 90% transfere da conta FROM para TO, e 10% transfere da conta TO para FROM.
    5. 
    - Poderão ser realizadas até 100 transações simultâneas de transferência.
    - R: Foram criadas mais de 100 threads, ou seja, elas podem tentar transferir simultaneamente, mas apenas 1 transfere por vez. 

* Foto da execução do programa:
    * ![Alt text](imagens/ex1.png?raw=true "Execução 1-50")
    * ![Alt text](imagens/ex2.png?raw=true "Execução 51-100")