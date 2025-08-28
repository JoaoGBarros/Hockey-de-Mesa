#include <Bluepad32.h>

#define motor1a 32
#define motor1b 33
#define motor2a 25
#define motor2b 26
#define solenoide1 27
#define solenoide2 14
#define pwm_module 100


class Player {

  public:

  int motora;
  int motorb;
  int solenoide;
  int index;
  int chute;
  int affectedByStatus;
  unsigned long statusTime;
  bool abilityUsed;
  unsigned long timeUsed;
  
    Player(int motora, int motorb, int solenoide, int index){
      this->motora = motora;
      this->motorb = motorb;
      this->solenoide = solenoide;
      this->index = index;
      this->chute = 0;
      this->affectedByStatus = 0;
      this->statusTime = 0;
      this->abilityUsed = false;
      this->timeUsed = 0;
    }
};

Player* player1 = new Player(32, 33, 27, 0);
Player* player2 = new Player(25, 26, 14, 1);
ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
}


void processGamepad(ControllerPtr ctl, Player* player, Player* enemyPlayer) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...

    int motorValue = ctl->axisX();
    long now = millis();

    if(player->affectedByStatus == 2){
        motorValue = ctl->axisX() * -1;
    }


    if(motorValue> -200 && motorValue < 200){
        //para motor 1
        analogWrite(player->motora, 0);
        analogWrite(player->motorb, 0);
    }
    else if(motorValue > 200){
        //mexe motor 1 um lado
        analogWrite(player->motora, pwm_module);
        analogWrite(player->motorb, 0);
    }
    else if(motorValue < -200){
        //mexe motor 1 outro lado
        analogWrite(player->motora, 0);
        analogWrite(player->motorb, pwm_module);
    }


    //chute
    if(ctl->buttons() == 1 && player->chute == 0 && player->affectedByStatus != 1){
        player->chute = 1;
        digitalWrite(player->solenoide, HIGH);
        delay(50);
        digitalWrite(player->solenoide, LOW);
    }
    else if(ctl->buttons() == 0 && player->chute == 1){
        player->chute = 0;
    }

    //Especial 2
    if (ctl->brake() > 500 && ctl->throttle() > 500 && enemyPlayer->affectedByStatus == 0 && !player->abilityUsed) {
        Serial.printf("Jogador: %d Habilidade 2 utilizada\n", player->index);
        enemyPlayer->affectedByStatus = 2;
        enemyPlayer->statusTime = now;
        player->abilityUsed = true;
        player->timeUsed = now;
    }

    //Especial 1
    if (ctl->buttons()== 2 && enemyPlayer->affectedByStatus == 0 && !player->abilityUsed) {
        Serial.printf("Jogador: %d Habilidade 1 utilizada\n", player->index);
        enemyPlayer->affectedByStatus = 1;
        enemyPlayer->statusTime = now;
        player->abilityUsed = true;
        player->timeUsed = now;
    }
    
    // Cura jogador
    if(player->affectedByStatus == 1 && now - player->statusTime >= 3000){
        Serial.printf("Jogador: %d curado\n", player->index);
        player->affectedByStatus = 0;
        player->statusTime = 0;
        
    }

    if(player->affectedByStatus == 2 && now - player->statusTime >= 5000){
        Serial.printf("Jogador: %d curado\n", player->index);
        player->affectedByStatus = 0;
        player->statusTime = 0;
        
    }

    //Reseta abilidade
    if(player->abilityUsed && now - player->timeUsed >= 30000){
      Serial.printf("Jogador: %d Habilidade resetada\n", player->index);
      player->abilityUsed = false;
      player->timeUsed = 0;
    }

    // Another way to query controller data is by getting the buttons() function.
    // See how the different "dump*" functions dump the Controller info.
    //dumpGamepad(ctl);
}


void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                
                if(myController->index() == player1->index){
                    processGamepad(myController, player1, player2);
                }else if(myController->index() == player2->index){
                    processGamepad(myController, player2, player1);
                }
            }  else {
                Serial.println("Unsupported controller");
            }
        }
    }
}

// Arduino setup function. Runs in CPU 1
void setup() {
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    pinMode(player1->motora, OUTPUT);
    pinMode(player1->motorb, OUTPUT);
    pinMode(player2->motora, OUTPUT);
    pinMode(player2->motorb, OUTPUT);
    pinMode(player1->solenoide, OUTPUT);
    pinMode(player2->solenoide, OUTPUT);


    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    // Calling "forgetBluetoothKeys" in setup() just as an example.
    // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
    // But it might also fix some connection / re-connection issues.
    //BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated)
        processControllers();

    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    //     vTaskDelay(1);
    delay(20);
}
