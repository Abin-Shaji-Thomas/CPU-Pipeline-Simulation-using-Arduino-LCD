#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);  // Use the correct I2C address

const int buttonPin = 2;  // Button pin
int registerA = 0;
int registerB = 0;
int result = 0;

String instructions[10];
int instructionPointer = 0;

// Pin definitions for LEDs
const int redPin = 3;
const int yellowPin = 4;
const int greenPin = 5;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);    // Initialize LCD
  lcd.print("CPU Pipeline");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for instr.");
  
  pinMode(buttonPin, INPUT_PULLUP); // Button setup
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  
  delay(2000);
  
  Serial.println("System Initialized");
  Serial.println("Waiting for instructions...");
}

void loop() {
  if (Serial.available() > 0) {
    String instruction = Serial.readStringUntil('\n');  // Read instruction from Serial
    instruction.trim();
    
    if (instruction == "HLT") {
      Serial.println("HLT received. Execution Stopping.");
      lcd.clear();
      lcd.print("Execution Stopped");
      lcd.setCursor(0, 1);
      lcd.print("Regs: A=" + String(registerA) + " B=" + String(registerB));
      delay(3000);
      while (true); // Stop the program
    } else {
      instructions[instructionPointer] = instruction; // Store instruction
      instructionPointer++;
      Serial.println("Instruction received: " + instruction);
    }
  }

  if (instructionPointer > 0 && digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed, executing instruction...");
    executeInstruction();
    delay(1000); // Debounce button press
  }
}

void executeInstruction() {
  String currentInstruction = instructions[0];
  
  // Stage: Fetch (Red LED)
  lcd.clear();
  lcd.print("Stage: Fetch");
  Serial.println("Stage: Fetch");
  lcd.setCursor(0, 1);
  lcd.print("Instr: " + currentInstruction);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  delay(1000);
  digitalWrite(redPin, LOW);

  // Shift instructions
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
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  delay(1000);
  digitalWrite(greenPin, LOW);

  // Stage: Execute (Yellow LED)
  lcd.clear();
  lcd.print("Stage: Execute");
  Serial.println("Stage: Execute");
  executeDecodedInstruction();
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
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
  Serial.println("Regs after execution: A=" + String(registerA) + " B=" + String(registerB));
}

void decodeInstruction(String instruction) {
  String opCode = instruction.substring(0, instruction.indexOf(' '));
  String operands = instruction.substring(instruction.indexOf(' ') + 1);

  if (opCode == "MOV") {
    Serial.println("Decoded MOV instruction");
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

