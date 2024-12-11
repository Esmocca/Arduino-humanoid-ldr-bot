#include<Servo.h>

#define block_button 12
#define Atk_button 11
#define run_pin 10
#define heal_pin 8
#define block_pin 9

Servo punggung;
Servo bahukanan;
//Servo tangankanan;
Servo tangankiri;
Servo pinggang;
Servo kakikanan;
Servo kakikiri;

// Character stats:

int damage =0;
//int Atk = 200;
//int Deffense = 800;    //Defense points
int hp = 30;
int deff = 800;
int atk = 300;

// Attack button

int button_press_count = 0;
int button_state = 0;
int prev_button_state = 0;

// Skill button

//int skill_press_count = 0;
//int skill_state = 0;
//int prev_skill_state = 0;

// Block button

int block_press_count = 0;
int block_state = 0;
int prev_block_state = 0;

//Heal button

int heal_press_count=0;
int heal_state =0;
int prev_heal_state =0;

unsigned long lastAtkTime = 0, atkInterval = 500;  // Attack timing
unsigned long lastBlockTime = 0, blockInterval = 3000; // Block timing
unsigned long lastSkillTime = 0, skillInterval = 700; // Skill timing

//int BlockldrPin = A3; // Activated while blocking

int ldrPin = A2;
bool ldr_disabled = false;//ldr disable state

int runValue = 0;
int AttackledPin = 2;

long randnum;

bool isAttacking = false;
bool isBlocking = false;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(ldrPin,INPUT);
  pinMode(heal_pin, INPUT_PULLUP);
  pinMode(block_pin, INPUT_PULLUP);
  pinMode (Atk_button, INPUT_PULLUP); 
//pinMode (skill_pin, INPUT_PULLUP);
  pinMode (block_button,INPUT_PULLUP);
  pinMode (run_pin, INPUT);
//pinMode (BlockldrPin, INPUT);
  pinMode (AttackledPin, OUTPUT);

  punggung.attach(7);
  bahukanan.attach(6);
  //tangankanan.attach(5);
  tangankiri.attach(4);
  pinggang.attach(3);

  setIdlePosition();
  Serial.println("Start...");
}


void setIdlePosition()
{
  bahukanan.write(90);
  //tangankanan.write(120);
  tangankiri.write(80);
  punggung.write(160);
  //tangankanan.write(120);
  tangankiri.write(80);
  pinggang.write(40);
}
void HpState()
{
  Serial.println("Current hp :");
  Serial.println(hp);
  Serial.println(" ");
  // Sensors indicate health point 
  if(ldr_disabled)
  {
    return; // Skip ldr reading when disabled
  }
  // Read ldr value
  int ldrStatus = analogRead(ldrPin);
  Serial.println("ldr Signal : ");
  Serial.println(ldrStatus);
  Serial.println(" ");
  if(ldrStatus >=deff){
    damage+=1;
    hp-=1;
  }
  else{
    
  }
  if(hp <= 0 ){
    digitalWrite(AttackledPin, LOW);
    Serial.print(" You Dead ");
    Serial.println(" Game Over ");
    while (true);  // stop the program
  }
}
void HealState()
{
  heal_state = digitalRead(heal_pin);
  if (heal_state != prev_heal_state)
  {
    if(heal_state == HIGH) {
      //idle 
    }else{
      //button pressed
      hp++;
      Serial.print("Healed! Current HP: ");
      Serial.println(hp);
    }
    delay(100);
  }
  prev_heal_state = heal_state;
}

//void BlockState()// Blocking menggunakan delay
//{
//  block_state = digitalRead(block_pin);
// if (block_state != prev_block_state) {
//    if (block_state == HIGH) {
      
//      ldr_disabled = false; // Enable LDR

//      digitalWrite(AttackledPin,LOW);
//      // Servo blocking idle animation
//      bahukanan.write(90);
//      //tangankanan.write(120);
//      tangankiri.write(80);
//      punggung.write(160);
//     // tangankanan.write(120);
//      tangankiri.write(80);
//      pinggang.write(40);

      
//      Serial.println("Block inactive: LDR enabled");
    
//     } else { // Button press
      
//      ldr_disabled = true;
//      Serial.println("Blocking : LDR disabled");

//       // Servo blocking animation
//      Serial.println("blocking"); 
//      bahukanan.write(150);
      //tangankanan.write(120);
//      tangankiri.write(60);
//      delay(500);
//      bahukanan.write(90);
      //tangankanan.write(120);
//      tangankiri.write(80);
//      punggung.write(160);
      //tangankanan.write(120);
//      tangankiri.write(80);
//      pinggang.write(40);

      
//      ldr_disabled = false; // Enable LDR
//      Serial.println("LDR enabled");
//     }
//     delay(100);
// }
//     prev_block_state = block_state;
     
//}

void BlockState() //Blocking menggunakan millis
{
  block_state = digitalRead(block_pin);
  if (block_state ==  HIGH && !isBlocking) {
    isBlocking = true;
    ldr_disabled = true;  // Disable LDR
    lastBlockTime = millis();
    Serial.println("Blocking started...");
  }

  if (isBlocking) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlockTime < 1000) {
      // Blocking animation
      bahukanan.write(150);
      tangankiri.write(60);
    } else {
      isBlocking = false;
      ldr_disabled = false;  // Re-enable LDR
      setIdlePosition();
      Serial.println("Blocking ended.");
    }
  }
}

//void handleAtkState()//...( Random Atkanimation )
//{
 // button_state = digitalRead(Atk_button);
 // if (button_state != prev_button_state) {
  //  if (button_state == HIGH) {
   //   digitalWrite(AttackledPin,LOW);
      //Servo atatack idle animation
    //  bahukanan.write(90);
    //  tangankanan.write(120);
    //  tangankiri.write(80);
    //  punggung.write(160);
    //  tangankanan.write(120);
    //  tangankiri.write(80);
    //  pinggang.write(40);
   
   // } else { //button press
      
     // randnum  = random(0, 2);
      
     // Serial.println("Attacking...");
    //  Serial.println(randnum);

     // if(randnum == 0){
     // delay(200);
    //  digitalWrite(AttackledPin, HIGH);
      // Servo animation 1
      
    //  pinggang.write(100);
    //  punggung.write(100);
    //  bahukanan.write(120);
    //  tangankanan.write(30);
    //  delay(500);
    //  tangankanan.write(120);
    //  pinggang.write(40);
    //  punggung.write(160);
    //  digitalWrite(AttackledPin, LOW);
    //  }
    //  if(randnum == 1){
    //  delay(200);
    //  digitalWrite(AttackledPin, HIGH);
       // Servo animation 2

     //  pinggang.write(100);
     //  punggung.write(100);
      // bahukanan.write(120);
      // tangankanan.write(30);
     //  delay(500);
     //  tangankanan.write(120);
     //  pinggang.write(40);
     //  punggung.write(160);
     // digitalWrite(AttackledPin, LOW);
     // }  
      
   // }
  //  delay(100);
 // }
//  prev_button_state = button_state;
//}

void handleAtkState() {
  static int animationIndex = 0;  // Indeks untuk memilih animasi
  button_state = digitalRead(Atk_button);

  if (button_state == HIGH && !isAttacking) {
    isAttacking = true;
    lastAtkTime = millis();
    digitalWrite(AttackledPin, HIGH); // Lampu menyala saat serangan dimulai
    Serial.println("Attack started...");
  }

  if (isAttacking) {
    unsigned long currentTime = millis();

    switch (animationIndex) {
      case 0:  // Animasi serangan 1
        if (currentTime - lastAtkTime < 200) {
          pinggang.write(100);
          punggung.write(100);
          bahukanan.write(120);
        } else if (currentTime - lastAtkTime < 400) {
          pinggang.write(40);
          punggung.write(160);
        } else {
          isAttacking = false;
          animationIndex = (animationIndex + 1) % 3;  // Pindah ke animasi berikutnya
          digitalWrite(AttackledPin, LOW); // Lampu mati
          setIdlePosition();
          Serial.println("Attack 1 ended.");
        }
        break;

      case 1:  // Animasi serangan 2
        if (currentTime - lastAtkTime < 300) {
          bahukanan.write(150);
          tangankiri.write(60);
          pinggang.write(90);
        } else if (currentTime - lastAtkTime < 500) {
          tangankiri.write(80);
          pinggang.write(40);
        } else {
          isAttacking = false;
          animationIndex = (animationIndex + 1) % 3;  // Pindah ke animasi berikutnya
          digitalWrite(AttackledPin, LOW); // Lampu mati
          setIdlePosition();
          Serial.println("Attack 2 ended.");
        }
        break;

      case 2:  // Animasi serangan 3
        if (currentTime - lastAtkTime < 250) {
          tangankiri.write(140);
          pinggang.write(90);
        } else if (currentTime - lastAtkTime < 450) {
          pinggang.write(20);
          tangankiri.write(60);
        } else {
          isAttacking = false;
          animationIndex = (animationIndex + 1) % 3;  // Pindah ke animasi berikutnya
          digitalWrite(AttackledPin, LOW); // Lampu mati
          setIdlePosition();
          Serial.println("Attack 3 ended.");
        }
        break;
    }
  }
  else if (button_state == HIGH) {
    // Pastikan lampu mati jika tombol tidak ditekan
    digitalWrite(AttackledPin, LOW);
  }
  prev_button_state = button_state;
}


void handleSkillState()
{
  //skill_state = digitalRead(skill_pin);
 //if (skill_state != prev_skill_state) {
  //  if (skill_state == HIGH) {
  //    digitalWrite(ledPin,LOW);
  //    servo1.write(170);
  //    servo2.write(50);
  //    servo3.write(90);
  //    servo6.write(180);
      
      
      
   // } else { //button press
   
   //   digitalWrite(ledPin, HIGH);

   //   servo2.write(180);
   //   servo1.write(140);
   //   servo3.write(160);
   //   delay(300);
   //   servo1.write(140);
   //   servo2.write(30);
   //   servo3.write(60);
   //   delay(Atkspeed);
   //   delay(50);
      //

   //   servo1.write(140);
   //   servo2.write(30);
   //   servo3.write(60);
   //   delay(Atkspeed);
   //   servo1.write(140);
   //   servo2.write(160);
   //   servo3.write(160);
   //   delay(Atkspeed); 
   //   delay(50);
      
      //    
      
   //    servo6.write(60);
   //   servo2.write(180);
   //   servo1.write(140);
   //   servo3.write(160);

    //  delay(300);
    //  servo6.write(180);
    //  servo1.write(140);
    //  servo2.write(30);
    //  servo3.write(60);

    //  delay(Atkspeed);
    //  delay(50);
    //  digitalWrite(ledPin, LOW);  
    //     servo1.write(170);
    //  servo2.write(50);
    //  servo3.write(90);
    //  servo6.write(180);
      
     // delay(2000);
   // }
   // delay(50);
  //}
  //prev_skill_state = skill_state;
}

void loop() {
  HpState();
  HealState();
  BlockState();
  handleAtkState();
  handleSkillState();
}
