#include <kaulab.h>
#include <stdbool.h>
// Majd Mansour & Hagar Alyasaki (DVGB15, ht 25)

// KONSTANTER 
#define BASE_SPEED    80
#define M_LEFT        2
#define M_RIGHT       1
#define SAFE_DIST     18

// TILLSTÅND
int phase = 0;
bool lineMode = true;
bool obstacleMode = false;
int ticks = 0;
int lastSeen = 0;   // 1 = vänster, 2 = höger

// MOTORHJÄLP 
void drive(int left, int right) {
  zRobotSetMotorSpeed(M_LEFT, left);
  zRobotSetMotorSpeed(M_RIGHT, right);
}

// HINDERLOGIK 
void obstacleTask() {
  if (!obstacleMode) return;
  lineMode = false;

  if (lastSeen == 1) {
    // === LINJE VÄNSTER: nuvarande logik ===
    switch (phase) {
      case 0: 
        drive(-BASE_SPEED, -BASE_SPEED);
        if (ticks > 7) { phase = 1; ticks = 0; }
        break;

      case 1: // Sväng vänster (inåt)
        drive(BASE_SPEED, -(BASE_SPEED / 2));
        if (zRobotGetLineSensor() == 0) { phase = 2; ticks = 0; }
        break;

      case 2: // Sväng höger tillbaka
        drive(0, -BASE_SPEED);
        if (ticks > 4) {
          phase = 0; ticks = 0;
          obstacleMode = false;
          lineMode = true;
        }
        break;
    }
  } 
  else if (lastSeen == 2) {
        switch (phase) {
          case 0: 
            drive(BASE_SPEED, BASE_SPEED);
            if (ticks > 7) { phase = 1; ticks = 0; }
            break;

          case 1:
            drive((BASE_SPEED / 2), -BASE_SPEED);
            if (zRobotGetLineSensor() == 0) {
              phase = 2; ticks = 0;
            }
            break;

          case 2: // Sväng vänster tillbaka till linjen
            drive(BASE_SPEED, 0);
            if (ticks > 4) {
              phase = 0; ticks = 0;
              obstacleMode = false;
              lineMode = true;
            }
            break;
        }
      }
  ticks++;
}


// LINJEFÖLJNING
void lineTask() {
  if (!lineMode) return;

  // Hinderkoll
  if (zRobotGetUltraSensor() < SAFE_DIST) {
    obstacleMode = true;
    lineMode = false;
    phase = 0;
    ticks = 0;
    return;
  }

  // Linjesensor
  int sensor = zRobotGetLineSensor();
  switch (sensor) {
    case 1: drive(0, -BASE_SPEED); lastSeen = 1; break;  // vänster ser svart
    case 2: drive(BASE_SPEED, 0); lastSeen = 2; break;   // höger ser svart
    case 0: drive(BASE_SPEED, -BASE_SPEED); break;       // båda ser linjen
    default: break;
  }
}

// SETUP 
void setup() {
  zInitialize();
  zScheduleTask(lineTask, 2, 5);
  zScheduleTask(obstacleTask, 5, 10);
  zStart();
}

void loop() {}