// Semáforo sonoro com botão - Arduino Uno
//
// O semáforo fica no verde. Ao apertar o botão, ele passa por amarelo e
// vermelho, e o buzzer apita enquanto o vermelho está aceso (carros parados).
// Depois volta ao verde.

// Pinos usados
const int vermelho = 10;
const int amarelo = 9;
const int verde = 8;
const int botao = 12;
const int buzzer = 11;

// Tempos (em milissegundos) e frequência do apito (em Hz)
const int tempoAmarelo = 2000;
const int tempoVermelho = 5000;
const int frequenciaBuzzer = 1000;

void setup() {
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // O botão liga o pino ao GND. Com INPUT_PULLUP, o pino lê HIGH solto
  // e LOW apertado, sem precisar de resistor externo.
  pinMode(botao, INPUT_PULLUP);

  // Estado inicial: só o verde aceso
  digitalWrite(verde, HIGH);
  digitalWrite(amarelo, LOW);
  digitalWrite(vermelho, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Botão apertado?
  if (digitalRead(botao) == LOW) {
    delay(50);  // espera 50 ms e confere de novo, para ignorar ruído do botão

    if (digitalRead(botao) == LOW) {
      // Verde -> amarelo
      digitalWrite(verde, LOW);
      digitalWrite(amarelo, HIGH);
      delay(tempoAmarelo);

      // Amarelo -> vermelho, com o buzzer apitando
      digitalWrite(amarelo, LOW);
      digitalWrite(vermelho, HIGH);
      tone(buzzer, frequenciaBuzzer);
      delay(tempoVermelho);
      noTone(buzzer);

      // Vermelho -> amarelo
      digitalWrite(vermelho, LOW);
      digitalWrite(amarelo, HIGH);
      delay(tempoAmarelo);

      // Amarelo -> verde
      digitalWrite(amarelo, LOW);
      digitalWrite(verde, HIGH);

      // Se o botão continuar apertado, espera soltar antes de reiniciar
      while (digitalRead(botao) == LOW) {
        delay(10);
      }
    }
  }
}
