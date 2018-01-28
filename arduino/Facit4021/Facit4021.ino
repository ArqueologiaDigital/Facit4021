/* (c) 2018 Felipe Correa da Silva Sanches
 * Released under the terms of the GNU General Public License v3 (or later).
 *
 * FACIT 4021 Paper Tape Reader
 */
#define StepDir A0
#define ReadInstruction A1
#define FeedHole A2
#define DataAvailable A3
#define ReaderReady A4
// Max. reading speed is 300 chars/s
#define CHARS_PER_SECOND 300
#define PER_CHAR_DELAY (1000 / CHARS_PER_SECOND)
int DataPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  pinMode(StepDir, OUTPUT);
  digitalWrite(StepDir, LOW);
  
  pinMode(ReadInstruction, OUTPUT);
  digitalWrite(ReadInstruction, LOW);
  
  pinMode(FeedHole, INPUT);
  pinMode(DataAvailable, INPUT);
  pinMode(ReaderReady, INPUT);
  
  for (int i=0; i<8; i++){
    pinMode(DataPin[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(ReaderReady) == HIGH){
    delay(PER_CHAR_DELAY);
    digitalWrite(ReadInstruction, HIGH);
    while (digitalRead(DataAvailable) == LOW){ };
    int data = 0;
    for (int i=0; i<8; i++){
      if (digitalRead(DataPin[i]) == HIGH){
        data |= (1 << i);
      }
    }
    Serial.write(data & 0x7F);
    digitalWrite(ReadInstruction, LOW);
  }
}
