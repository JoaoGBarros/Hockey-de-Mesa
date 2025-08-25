# Hockey-de-Mesa
Repositório do Trabalho de PIC II - UFES 2025/1


## Descrição do trabalho
Este projeto consiste no desenvolvimento e construção de um jogo de hockey de mesa automatizado, inspirado em jogos clássicos como o pebolim e o air hockey. O objetivo foi criar uma experiência onde dois jogadores podem se enfrentar controlando seus respectivos "atletas" em campo através de controles Bluetooth.

Cada jogador é montado sobre um trilho de impressora, permitindo o movimento horizontal ao longo do campo. O "chute" é realizado por um solenoide de impacto, que impulsiona a bola em direção ao gol adversário. O sistema é gerenciado por um microcontrolador ESP32, que recebe os comandos dos controles, aciona os motores de passo para a movimentação e os solenoides para o ataque. Sensores de fim de curso (microswitches) são posicionados nos gols para que não seja possivel sobrecarregar o motor da impressora.

O projeto integra conceitos de eletrônica embarcada, programação de microcontroladores, modelagem e impressão 3D, e montagem mecânica, resultando em um dispositivo de entretenimento funcional e robusto.

## Materiais

A seguir, a lista de componentes utilizados na montagem do projeto:

- Estrutura e Campo:

  - Madeira MDF para a caixa e o campo de jogo.
  - Rolhas para amortecimento nas laterais.
  - Parafusos diversos para fixação.

- Componentes Mecânicos:

  - 2 Jogadores impressos em 3D.
  - 2 Trilhos de impressora de cartucho para a movimentação dos jogadores.
  - 2 Solenoides de impacto, modelo TAU-0530T.

- Componentes Eletrônicos:
  - 1 Microcontrolador ESP32.
  - 2 Módulos Relé para acionamento dos solenoides.
  - 2 Módulos Ponte-H (Driver de Motor) para controle dos motores dos trilhos.
  - 2 Controles Bluetooth para a interface com o jogador.
  - 4 Botões Chave Microswitch.
  - Jumpers e fios para as conexões.
  - Protoboard para montagem do circuito de controle.

## Processo de construção

A construção do projeto seguiu uma ordem que mesclou a obtenção de materiais com o desenvolvimento eletrônico e mecânico.

1. Aquisição de Componentes e Desmontagem:

  - O ponto de partida foi a procura e obtenção de impressoras usadas na UFES. Essas impressoras foram desmontadas para extrair os trilhos dos cartuchos, que se tornaram a base para a movimentação dos jogadores.

2. Desenvolvimento e Testes Eletrônicos:

  - A montagem eletrônica foi realizada em etapas, começando com testes individuais dos motores das impressoras.
  - Em seguida, foi implementada a conexão dos controles Bluetooth e o controle de movimento pelo usuário.
  - Posteriormente, o acionamento dos solenoides foi integrado ao controle.
  - Por último, implementamos a lógica dos botões de fim de curso para a detecção de gols.

3. Construção da Estrutura e Modelagem 3D:

  - Paralelamente aos testes eletrônicos, seguimos para a construção da caixa e do campo, definindo as medidas e buscando os materiais.
  - Ao mesmo tempo, o modelo 3D dos jogadores foi desenvolvido utilizando o Blender, o que exigiu um aprendizado da ferramenta pela equipe.

4. Montagem Final:
  - Os trilhos foram acoplados à estrutura de madeira.
  - Os modelos 3D dos jogadores foram impressos, ajustados e colados nos carrinhos dos trilhos.
  - Os solenoides foram fixados nas extremidades, alinhados para o chute.
  - Finalmente, todos os fios e componentes eletrônicos foram organizados dentro da caixa para um acabamento seguro e funcional.

## Documentos e Midias

## Conclusão

