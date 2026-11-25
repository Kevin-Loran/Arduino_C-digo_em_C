#define PINO_UMIDADE   A0
#define PINO_LUZ       A1
#define PINO_BOTAO     2
#define PINO_BOMBA     8
#define PINO_ALERTA    9

#define UMIDADE_LIGA     30
#define UMIDADE_DESLIGA  60
#define LUZ_FORTE        700

int bombaLigada = 0;
unsigned long ultimoPisca = 0;
int estadoPisca = 0;

int lerUmidade(void) {
  int leitura = analogRead(PINO_UMIDADE);
  return map(leitura, 0, 1023, 0, 100);
}

int lerLuz(void) {
  return analogRead(PINO_LUZ);
}

int botaoPressionado(void) {
  return digitalRead(PINO_BOTAO) == LOW;
}

void piscarAlerta(void) {
  if (millis() - ultimoPisca >= 300) {
    ultimoPisca = millis();
    estadoPisca = !estadoPisca;
    digitalWrite(PINO_ALERTA, estadoPisca);
  }
}

void setup() {
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_BOMBA, OUTPUT);
  pinMode(PINO_ALERTA, OUTPUT);

  digitalWrite(PINO_BOMBA, LOW);
  digitalWrite(PINO_ALERTA, LOW);

  Serial.begin(9600);
  Serial.println("Sistema de irrigacao iniciado");
}

void loop() {
  int umidade  = lerUmidade();
  int luz      = lerLuz();
  int manual   = botaoPressionado();
  int solSeco  = (umidade < UMIDADE_LIGA);
  int solForte = (luz > LUZ_FORTE);

  if (solSeco && !solForte) {
    bombaLigada = 1;
  } else if (umidade >= UMIDADE_DESLIGA || solForte) {
    bombaLigada = 0;
  }

  if (manual || bombaLigada) {
    digitalWrite(PINO_BOMBA, HIGH);
  } else {
    digitalWrite(PINO_BOMBA, LOW);
  }

  if (solSeco && solForte) {
    piscarAlerta();
  } else if (solSeco) {
    digitalWrite(PINO_ALERTA, HIGH);
  } else {
    digitalWrite(PINO_ALERTA, LOW);
  }

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("% | Luz: ");
  Serial.print(luz);
  Serial.print(" | Manual: ");
  Serial.print(manual ? "SIM" : "NAO");
  Serial.print(" | Bomba: ");
  Serial.println((manual || bombaLigada) ? "LIGADA" : "DESLIGADA");

  delay(200);
}