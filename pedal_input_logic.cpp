//Pedal input pin
#define PEDAL_PIN 2

//Left motor driver
#define PWM_L_A 3
#define PWM_R_A 5   
#define ENABLE_L_A 6  
#define ENABLE_R_A 7

//Right motor driver
#define PWM_L_B 9   
#define PWM_R_B 10  
#define ENABLE_L_B 11  
#define ENABLE_R_B 12  

//PWM variables
int pwm_value = 0;  
const int pwm_max = 255;  
const int pwm_step = 5;  
const int pwm_delay = 50;

void setup() {
    pinMode(PEDAL_PIN, INPUT_PULLUP); 

    //Set left motor driver pins
    pinMode(PWM_L_A, OUTPUT);
    pinMode(PWM_R_A, OUTPUT);
    pinMode(ENABLE_L_A, OUTPUT);
    pinMode(ENABLE_R_A, OUTPUT);

    //Set right motor driver pins
    pinMode(PWM_L_B, OUTPUT);
    pinMode(PWM_R_B, OUTPUT);
    pinMode(ENABLE_L_B, OUTPUT);
    pinMode(ENABLE_R_B, OUTPUT);

    //Enable motor drivers
    digitalWrite(ENABLE_L_A, HIGH);
    digitalWrite(ENABLE_R_A, HIGH);
    digitalWrite(ENABLE_L_B, HIGH);
    digitalWrite(ENABLE_R_B, HIGH);

    //Start with motors off
    analogWrite(PWM_L_A, 0);
    analogWrite(PWM_R_A, 0);
    analogWrite(PWM_L_B, 0);
    analogWrite(PWM_R_B, 0);
}

void loop() {
    if (digitalRead(PEDAL_PIN) == LOW) { //Pedal pressed & soft start
        while (pwm_value < pwm_max) { 
            pwm_value += pwm_step;  
            if (pwm_value > pwm_max) pwm_value = pwm_max;

            //Write PWM to left and right motor for speed up
            analogWrite(PWM_L_A, pwm_value);
            analogWrite(PWM_R_A, pwm_value);
            analogWrite(PWM_L_B, pwm_value);
            analogWrite(PWM_R_B, pwm_value);
            
            //Delay for ~ 3 second ramp up
            delay(pwm_delay);
        }
    } else { //Pedal released & soft stop
        while (pwm_value > 0) { 
            pwm_value -= pwm_step;  
            if (pwm_value < 0) pwm_value = 0;

            //Write PWM to left and right motor for speed down
            analogWrite(PWM_L_A, pwm_value);
            analogWrite(PWM_R_A, pwm_value);
            analogWrite(PWM_L_B, pwm_value);
            analogWrite(PWM_R_B, pwm_value);

            //Delay for ~ 3 second ramp down
            delay(pwm_delay);
        }
    }
}