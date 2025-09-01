# HockeyComp

Membros do Grupo:

- João Gabriel de Barros Rocha
- Luca Avila
- Tales Viana Ferracioli

## Descrição do trabalho
Este projeto consiste no desenvolvimento e construção de um jogo de hockey de mesa automatizado, inspirado em jogos clássicos como o pebolim e o air hockey. O objetivo foi criar uma experiência onde dois jogadores podem se enfrentar controlando seus respectivos "atletas" em campo através de controles Bluetooth.

Cada jogador é montado sobre um trilho de impressora, permitindo o movimento horizontal ao longo do campo. O "chute" é realizado por um solenoide de impacto, que impulsiona a bola em direção ao gol adversário. O sistema é gerenciado por um microcontrolador ESP32, que recebe os comandos dos controles, aciona os motores de passo para a movimentação e os solenoides para o ataque.

### Comandos

A jogabilidade é controlada através de um controle Bluetooth com os seguintes comandos:

- Joystick Esquerdo: Controla a movimentação horizontal do jogador sobre o trilho.

- Botão X (PlayStation) / A (Xbox): Ativa o solenoide para realizar o "chute".

- Botões L2 + R2 (PlayStation) / LT + RT (Xbox): Aciona um comando especial. (Faz com que o inimigo se movimente na direção contraria de seu input)

## Materiais

A seguir, a lista de componentes utilizados na montagem do projeto:

- Estrutura e Campo:

  - Madeira MDF para a caixa e o campo de jogo.
  - Rolhas para amortecimento.
  - Parafusos diversos para fixação.
  - Adesivos

- Componentes Mecânicos:

  - 2 Jogadores impressos em 3D.
  - 2 Trilhos de impressora de cartucho para a movimentação dos jogadores.
  - 2 Solenoides de impacto, modelo TAU-0530T.

- Componentes Eletrônicos:
  - 1 Microcontrolador ESP32.
  - 2 Módulos Relé para acionamento dos solenoides (Jqc-3ff-s-z).
  - 1 Módulos Ponte-H Dupla (l298n).
  - 2 Controles Bluetooth.
  - Jumpers e fios para as conexões.
  - Protoboard para montagem do circuito de controle.
  - Fonte de 19V

## Processo de construção

A construção do projeto seguiu uma ordem que mesclou a obtenção de materiais com o desenvolvimento eletrônico e mecânico.

1. Aquisição de Componentes e Desmontagem:

  - O ponto de partida foi a procura e obtenção de impressoras usadas na UFES. Essas impressoras foram desmontadas para extrair os trilhos dos cartuchos, que se tornaram a base para a movimentação dos jogadores.

2. Desenvolvimento e Testes Eletrônicos:

  - A montagem eletrônica foi realizada em etapas, começando com testes individuais dos motores das impressoras.
  - Em seguida, foi implementada a conexão dos controles Bluetooth e o controle de movimento pelo usuário. Utilizamos a biblioteca Bluepad32 para conexão dos controles e leituras de input.
  - Posteriormente, forma realizados testes indivusais com os solenoides e logo em seguida a implementação de sua ação no código.

3. Modelagem 3D:

  - O modelo 3D dos jogadores foi desenvolvido utilizando o Blender, o que exigiu um aprendizado da ferramenta pela equipe.
  - Para cada modelo criado, foram realizados testes em relação a tamanho de diametro e altura, chegando ao resultado final após 5 modelo criado.

4. Construção da Estrutura

  - Paralelamente a modelagem 3D, seguimos para a construção da caixa e do campo, definindo as medidas e buscando os materiais.
  - Criamos o croqui da caixa.
  - Com auxilio do Reginaldo, marceneiro do CT, conseguimos construir a estrutura da caixa e do campo.
  - Foram necessarios alguns ajustes, como furar o espaço destinado ao motor do trilho.
  - Por ultimo, foi criado o design dos adesivos utilizando o Canva.

5. Montagem Final:
  - Os trilhos foram acoplados à estrutura de madeira.
  - Os modelos 3D dos jogadores foram impressos, ajustados e colados nos carrinhos dos trilhos.
  - Os solenoides foram fixados nas extremidades, alinhados para o chute.
  - Finalmente, todos os fios e componentes eletrônicos foram organizados dentro da caixa para um acabamento seguro e funcional.

## Documentos e Midias

Todos os arquivos relacionados ao projeto, como o modelo 3D dos jogadores e as dimensões detalhadas da estrutura de madeira, estão disponíveis no repositório oficial do projeto ou em uma pasta compartilhada.

- [Link para o vídeo de inspiração](https://www.youtube.com/shorts/SEkM0ANjcKw)
- [Link para Documentos e Midias do projeto](https://drive.google.com/drive/folders/1O0BGBbFdcr47wDU5BUUsXc0_4UtAozr7?usp=sharing)

O código utilizado para controle do ESP32 pode ser encontrado nesse repositório.

## Melhorias futuras

- Ajustar elevação do campo
- Adicionar LEDs ou outro estimulo visual para indicar gols, especial utilizado, especial em cooldown e "atingido pelo especial"
- Sensor a laser para contar Gols
