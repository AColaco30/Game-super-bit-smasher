// Trabalho realizado por: André Filipe Costa Colaço.
// UC: 2020220301.

int target, inicial, operacoes;   // Números que vão ser gerados aleatoriamente.
int numero;                       // Número convertido para inteiro.
unsigned long intervalo = 60000;  // Tempo do jogo.
unsigned long tempo;              // Variável onde esta guardada a função millis().
String valor;                     // Número que escrevemos no Serial Monitor.
bool start = true;                // Começa ou recomeça o jogo (inicializada a true para o jogo começar).
bool botoes, ler_numero;          // Variáveis que determinam onde o vai jogo.

void setup() {

  for (int p = 8; p < 12; p++) pinMode(p, OUTPUT);    // Inicializa os quatro leds.
  for (int b = 2; b < 5 ; b++) pinMode(b, INPUT_PULLUP);    // Inicializa os três botões.
  randomSeed(analogRead(0));    // Faz com que os números sejam gerados aleatoriamente.
  Serial.begin(9600);

}

void loop() {

  // Quando start for true, o jogo começa ou recomeça.
  if (start == true) {
    for (int i = 8; i < 12; i++) digitalWrite(i, HIGH);   // Liga todos os leds.
    gerar_numeros();
    tempo = millis();   // É resetado o tempo.
    start = false;      // Para o jogo não estar constantemente a recomeçar.
  }
  ler();
  buttons();
  // Quando o valor base for igual ao target.
  if (inicial == target) {
    Serial.println("Parabéns! Acertaste!");
    // O jogo recomeça.
    start = true;
  }

}

// Função que gera aleatoriamente o valor de onde partimos(inicial), o valor onde queremos chegar(target)
// e um valor para obter as operações permitidas(operacoes).
void gerar_numeros() {

  target = random(1, 256);    // Gera o target(onde queremos chegar).
  inicial = random(1, 256);   // Gera o base(onde partimos).
  operacoes = random(1, 4);   // Gera o operacoes(para as operações permitidas).

  // São apresentadas as operações permitidas e os valores inicial e target, em binário.
  Serial.print("Operações permitidas: ");
  if (operacoes == 1) Serial.println("OR-vermelho , XOR-amarelo");
  if (operacoes == 2) Serial.println("AND-branco , OR-vermelho");
  if (operacoes == 3) Serial.println("AND-branco , OR-vermelho , XOR-amarelo");
  Serial.println("Valor target: " + String(target, BIN));
  Serial.println("Valor base: " + String(inicial, BIN));

}

// Função que lê o que é escrito no serial monitor e passa-o para inteiro.
void ler() {

  // Para entrar no while.
  ler_numero = true;
  // Caso o jogo não seja para recomeçar, é impressa esta mensagem.
  if (start == false) Serial.println("Introduza um valor: ");
  // Entra no while(se não for para recomeçar o jogo) e espera que seja escrito alguma coisa.
  while (ler_numero == true && start == false) {
    leds();
    // Se existirem dados na porta serie para receber.
    if (Serial.available() > 0) {
      // Lê os dados recebidos na porta serie.
      valor = Serial.readStringUntil("\n");
      // Converte o número para inteiro.
      numero = valor.toInt();
      // É apresentado o número, em binário.
      Serial.println("Valor lido: " + String(numero, BIN));
      // Para sair deste while.
      ler_numero = false;
    }
  }

}

// Função que espera que seja premido algum dos botões disponíveis.
void buttons() {

  // Para entrar no while.
  botoes = true;
  // Caso o jogo não seja para recomeçar, é impressa esta mensagem.
  if (start == false) Serial.println("Prima um operador");
  // Entra no while(se não for para recomeçar o jogo) e espera que seja premido algum botão.
  while (botoes == true && start == false) {
    leds();
    // Se o botão AND for premido e estiver disponível.
    if ((operacoes == 2 || operacoes == 3) && !digitalRead(4) == true) {
      // Faz a operação e este valor é guardado na mesma variável.
      inicial = inicial & numero;
      // Imprime o valor da operação, em binário.
      Serial.println("Valor calculado: " + String(inicial, BIN));
      // Para sair deste while.
      botoes = false;
    }
    // Se o botão OR for premido.
    if (!digitalRead(3) == true) {
      // Faz a operação e este valor é guardado na mesma variável.
      inicial = inicial | numero;
      // Imprime o valor da operação, em binário.
      Serial.println("Valor calculado: " + String(inicial, BIN));
      // Para sair deste while.
      botoes = false;
    }
    // Se o botão XOR for premido e estiver disponível.
    if ((operacoes == 1 || operacoes == 3) && !digitalRead(2) == true) {
      // Faz a operação e este valor é guardado na mesma variável.
      inicial = inicial ^ numero;
      // Imprime o valor da operação, em binário.
      Serial.println("Valor calculado: " + String(inicial, BIN));
      // Para sair deste while.
      botoes = false;
    }
  }

}

// Função que, à medida que o tempo passa, vai apagando os leds, até o jogo recomeçar.
void leds() {

  // Quando passar 1/4 do tempo, o primeiro led apagasse.
  if ((millis() - tempo) >= (0.25 * intervalo)) digitalWrite(8, LOW);
  // Quando passar 2/4 do tempo,, o segundo led apagasse.
  if ((millis() - tempo) >= (0.50 * intervalo)) digitalWrite(9, LOW);
  // Quando passar 3/4 do tempo, o terceito led apagasse.
  if ((millis() - tempo) >= (0.75 * intervalo)) digitalWrite(10, LOW);
  // Quando passar tempo todo, o último led apagasse e o jogo recomeça.
  if ((millis() - tempo) >= intervalo) {
    digitalWrite(11, LOW);
    Serial.println("O tempo acabou! Tenta outra vez!");
    delay(500);
    start = true;
  }

} 
