#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);  // Initialize LCD with I2C address

const int buttonPin = 2;  // Button for executing instructions
int registerA = 0;
int registerB = 0;
int result = 0;

String instructions[10];  // Instruction queue
int instructionPointer = 0;

// LED Pin Definitions
const int redPin = 3;    // Fetch stage
const int yellowPin = 4; // Execute stage
const int greenPin = 5;  // Decode stage

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("CPU Pipeline");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for instr.");

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);

  delay(2000);
  Serial.println("System Ready - Waiting for Instructions...");
}

void loop() {
  if (Serial.available() > 0) {
    String instruction = Serial.readStringUntil('\n');  // Read incoming instruction
    instruction.trim();

    if (instruction == "HLT") {
      Serial.println("HLT received. Stopping Execution.");
      lcd.clear();
      lcd.print("Execution Stopped");
      lcd.setCursor(0, 1);
      lcd.print("Regs: A=" + String(registerA) + " B=" + String(registerB));
      delay(3000);
      while (true); // Halt execution
    } else {
      instructions[instructionPointer] = instruction;
      instructionPointer++;
      Serial.println("Instruction Stored: " + instruction);
    }
  }

  if (instructionPointer > 0 && digitalRead(buttonPin) == LOW) {
    Serial.println("Button Pressed, Executing...");
    executeInstruction();
    delay(1000); // Debounce delay
  }
}

void executeInstruction() {
  String currentInstruction = instructions[0];

  // Stage: Fetch (Red LED)
  lcd.clear();
  lcd.print("Stage: Fetch");
  Serial.println("Stage: Fetch - " + currentInstruction);
  lcd.setCursor(0, 1);
  lcd.print(currentInstruction);
  digitalWrite(redPin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);

  // Shift instruction queue
  for (int i = 0; i < instructionPointer - 1; i++) {
    instructions[i] = instructions[i + 1];
  }
  instructionPointer--;

  // Stage: Decode (Green LED)
  lcd.clear();
  lcd.print("Stage: Decode");
  Serial.println("Stage: Decode");
  decodeInstruction(currentInstruction);
  digitalWrite(greenPin, HIGH);
  delay(1000);
  digitalWrite(greenPin, LOW);

  // Stage: Execute (Yellow LED)
  lcd.clear();
  lcd.print("Stage: Execute");
  Serial.println("Stage: Execute");
  executeDecodedInstruction();
  digitalWrite(yellowPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, LOW);

  // Stage: Memory (All LEDs)
  lcd.clear();
  lcd.print("Stage: Memory");
  Serial.println("Stage: Memory");
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);

  lcd.clear();
  lcd.print("Regs: A=" + String(registerA) + " B=" + String(registerB));
  Serial.println("Registers: A=" + String(registerA) + ", B=" + String(registerB));
}

void decodeInstruction(String instruction) {
  String opCode = instruction.substring(0, instruction.indexOf(' '));
  String operands = instruction.substring(instruction.indexOf(' ') + 1);

  if (opCode == "MOV") {
    Serial.println("Decoding MOV instruction...");
    if (operands.startsWith("A,")) {
      registerA = operands.substring(2).toInt();
      Serial.println("MOV: Register A = " + String(registerA));
    } else if (operands.startsWith("B,")) {
      registerB = operands.substring(2).toInt();
      Serial.println("MOV: Register B = " + String(registerB));
    }
  } 
}

void executeDecodedInstruction() {
  String opCode = instructions[0].substring(0, instructions[0].indexOf(' '));

  if (opCode == "ADD") {
    result = registerA + registerB;
    Serial.println("Executed ADD: Result = " + String(result));
    registerA = result;
  } else if (opCode == "SUB") {
    result = registerA - registerB;
    Serial.println("Executed SUB: Result = " + String(result));
    registerA = result;
  } 
}
