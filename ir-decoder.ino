
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\nsetup");

  pinMode(2, INPUT);
}

const int MAX_DURATION = 100 * 1000;
const int MAX_COUNT = 256;

bool signal = true;
unsigned long last_edge = 0;
unsigned long durations[MAX_COUNT];
int count = 0;

void printSequence() {
  Serial.println("-- Begin Sequence --");
  for (int i = 0; i < count; i++) {
    Serial.println(durations[i]);
  }
  Serial.println("-- End Sequence --");
}

void loop() {
  unsigned long duration = micros() - last_edge;
  if (duration > MAX_DURATION * 2) {
    last_edge = micros() - MAX_DURATION;
  }
  if (count > 0 && duration > MAX_DURATION || count == MAX_COUNT) {
    printSequence();
    count = 0;
  }
  if ((GPI & bit(2)) > 0 != signal) {
    signal = !signal;
    last_edge = micros();
    if (duration <= MAX_DURATION) {
      durations[count++] = duration;
    } else if (signal) {
      Serial.println("WARNING: sequence started HIGH");
    }
  }
}
