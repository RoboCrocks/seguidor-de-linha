// Alterar de acordo com os pinos usados para cada motor.
#define MOTOR_L_CW 9
#define MOTOR_L_CCW 8
#define MOTOR_L_PWM 11
#define MOTOR_R_CW 7
#define MOTOR_R_CCW 6
#define MOTOR_R_PWM 10

// Alterar de acordo com os pinos usados para cada sensor.
#define SENSOR_L 13
#define SENSOR_R 12

// Ajustar a velocidade pelo PWM.
#define PWM_DUTY_0 0
#define PWM_DUTY_25 64
#define PWM_DUTY_50 128
#define PWM_DUTY_75 192
#define PWM_DUTY_100 255

// Tempo (ms) de atraso no loop. (Pode ser necessário ajustar)
#define TIME 300

enum direction
{
  FORWARD,
  STOP,
  LEFT,
  RIGHT,
  REVERSE
};

void setup()
{
  pinMode(MOTOR_L_CW, OUTPUT);
  pinMode(MOTOR_L_CCW, OUTPUT);
  pinMode(MOTOR_L_PWM, OUTPUT);

  pinMode(MOTOR_R_CW, OUTPUT);
  pinMode(MOTOR_R_CCW, OUTPUT);
  pinMode(MOTOR_R_PWM, OUTPUT);

  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_R, INPUT);
}

void loop()
{
  switch (getDirection())
  {
  case STOP:
    analogWrite(MOTOR_L_PWM, PWM_DUTY_0);
    analogWrite(MOTOR_R_PWM, PWM_DUTY_0);
    break;

  case FORWARD:
    digitalWrite(MOTOR_L_CW, HIGH);
    digitalWrite(MOTOR_L_CCW, LOW);
    analogWrite(MOTOR_L_PWM, PWM_DUTY_50);
    digitalWrite(MOTOR_R_CW, HIGH);
    digitalWrite(MOTOR_R_CCW, LOW);
    analogWrite(MOTOR_R_PWM, PWM_DUTY_50);
    break;

  case LEFT:
    digitalWrite(MOTOR_L_CW, HIGH);
    digitalWrite(MOTOR_L_CCW, LOW);
    analogWrite(MOTOR_L_PWM, PWM_DUTY_50);
    digitalWrite(MOTOR_R_CW, HIGH);
    digitalWrite(MOTOR_R_CCW, LOW);
    analogWrite(MOTOR_R_PWM, PWM_DUTY_75);
    break;

  case RIGHT:
    digitalWrite(MOTOR_L_CW, HIGH);
    digitalWrite(MOTOR_L_CCW, LOW);
    analogWrite(MOTOR_L_PWM, PWM_DUTY_75);
    digitalWrite(MOTOR_R_CW, HIGH);
    digitalWrite(MOTOR_R_CCW, LOW);
    analogWrite(MOTOR_R_PWM, PWM_DUTY_50);
    break;

  case REVERSE:
    digitalWrite(MOTOR_L_CW, LOW);
    digitalWrite(MOTOR_L_CCW, HIGH);
    analogWrite(MOTOR_L_PWM, PWM_DUTY_50);
    digitalWrite(MOTOR_R_CW, LOW);
    digitalWrite(MOTOR_R_CCW, HIGH);
    analogWrite(MOTOR_R_PWM, PWM_DUTY_50);
    break;
  }

  delay(TIME);
}

direction getDirection()
{
  bool sensor_l, sensor_r;

  sensor_l = digitalRead(SENSOR_L);
  sensor_r = digitalRead(SENSOR_R);

  if (!sensor_l && !sensor_r)
  {
    return FORWARD;
  }

  if (sensor_l && sensor_r)
  {
    return STOP;
  }

  return (!sensor_l && sensor_r) ? LEFT : RIGHT;
}
