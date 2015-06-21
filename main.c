#include <Arduino.h>
#include <irdebug.h>
#define APPLE_REMOTE_MODEL  0xcf
#include <apple-remote.h>
#define SIGNAL_MAX_LENGTH 70

#define PARASOUND_POWER_ON "W 1 1 2\r"
#define PARASOUND_POWER_OFF "W 1 1 1\r"
#define PARASOUND_POWER_TOGGLE "W 1 1 3\r"
#define PARASOUND_VOLUME_UP "W 1 9 1\r"
#define PARASOUND_VOLUME_DOWN "W 1 9 2\r"
#define PARASOUND_MUTE_ON "W 1 10 2\r"
#define PARASOUND_MUTE_OFF "W 1 10 1\r"
#define PARASOUND_MUTE_TOGGLE "W 1 10 3\r"
#define PARASOUND_IN1 "W 1 2 6\r"
#define PARASOUND_IN2 "W 1 2 7\r"
#define PARASOUND_IN3 "W 1 2 8\r"
#define PARASOUND_IN4 "W 1 2 9\r"
#define PARASOUND_IN5 "W 1 2 10\r"
#define PARASOUND_IN6 "W 1 2 11\r"
#define PARASOUND_IN_MP3 "W 1 2 12\r"
#define PARASOUND_IN_BY "W 1 2 13\r"
#define PARASOUND_IN_NEXT "W 1 2 4\r"
#define PARASOUND_IN_PREV "W 1 2 5\r"
#define PARASOUND_TONE_ON "W 1 3 1\r"
#define PARASOUND_TONE_OFF "W 1 3 2\r"
#define PARASOUND_TONE_TOGGLE "W 1 3 3\r"

void setup()
{
  Serial.begin(9600);
  //Serial.println("Point your Apple Controller to your IR sensor.");
}

void loop()
{
  unsigned int signal[SIGNAL_MAX_LENGTH];
  bool captured;
  int code;

  captured = irdebug_capture_signal(signal, SIGNAL_MAX_LENGTH);
  static String command = "";
  if (captured) {
    //irdebug_print_signal(signal);
    code = apple_remote_match(signal);
    bool repeat = false;

    switch (code) {
      case APPLE_REMOTE_MENU:
        command = PARASOUND_TONE_TOGGLE;
        break;
      case APPLE_REMOTE_RIGHT:
        command = PARASOUND_IN_NEXT;
        break;
      case APPLE_REMOTE_LEFT:
        command = PARASOUND_IN_PREV;
        break;
      case APPLE_REMOTE_UP:
        command = PARASOUND_VOLUME_UP;
        repeat = true;
        break;
      case APPLE_REMOTE_DOWN:
        command = PARASOUND_VOLUME_DOWN;
        repeat = true;
        break;
      case APPLE_REMOTE_PLAY:
        command = PARASOUND_MUTE_TOGGLE;
        repeat = true;
        break;
      case APPLE_REMOTE_CENTER:
        command = PARASOUND_POWER_TOGGLE;
        repeat = true;
        break;
      case APPLE_REMOTE_REPEAT:
        repeat = true;
        // Repeats the previous "command"
        break;

    }
    if(command != "") Serial.print(command);
    if(!repeat) command = "";
  }
}