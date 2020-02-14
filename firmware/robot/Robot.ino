#include "RadioWrapperRobot.h"
#include "AudioWrapper.h"
#include "GPSWrapper.h"
#include "ServoWrapper.h"
#include "DisplayWrapper.h"
#include "BatteryWrapper.h"
#include "SensorWrapper.h"
#include "src/MemoryFree/MemoryFree.h"//Serial.println(freeMemory());//see how much free ram is left in bytes. If this becomes zero then bad things happen. 
#include "src/avdweb_SAMDtimer/avdweb_SAMDtimer.h"

RadioWrapperRobot Radio;//radio object enables wireless communication
AudioWrapper Audio;//audio object enables playing audio
GPSWrapper GPS;//GPS object enables position sensing
ServoWrapper Servo;
DisplayWrapper Display;
BatteryWrapper Battery;
SensorWrapper Sensor;

void GPS_ISR(struct tc_module *const module_inst){ //Interrupt service routine is called a thousand times per second to tend to the incomming GPS characters
  GPS.read();//reads in a new char from GPS, if there is one. This needs to be called very often, around 1khz (a thousand times per second)
}

SAMDtimer GPSTimer = SAMDtimer(4, GPS_ISR, 1e3);//create the ISR with the SAMDTimer library that is called every .001 seconds (a thousand times per second) (1e3 microseconds) (1e2 was tested but gave bad data)

void setup(){
  Serial.begin(9600);//serial port to debug to computer
  Radio.initialize();//initialize the radio object
  Audio.initialize();//initialize the Audio object
  GPS.initialize();//initialize the GPS object
}

void loop(){
  String commandFromRadio=Radio.receive();//get response from radio
  if(commandFromRadio!="No Data Received"){//if there is a response,
    parse(commandFromRadio);//parse it and send a response
  }
}

void parse(String command) {
	switch (firstWord(command)) {
	case "Radio":					command.remove(0, String("Radio ").length());  // if the first word of command is "Radio" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Radio.clearErrors());		return;
		case "getLastError":		Radio.send(Radio.getLastError());		return;
		case "getErrorCount":		Radio.send(Radio.getErrorCount());		return;
		case "getSignalStrength":	Radio.send(Radio.getSignalStrength());	return;
		case "getTemperature":		Radio.send(Radio.getTemperature());		return;
		}
	case "Audio":					command.remove(0, String("Audio ").length());  // if the first word of command is "Audio" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Audio.clearErrors());		return;
		case "getLastError":		Radio.send(Audio.getLastError());		return;
		case "getErrorCount":		Radio.send(Audio.getErrorCount());		return;
		case "beep":				Radio.send(Audio.beep());				return;
		case "setVolume":			command.remove(0, String("setVolume ").length());
			Radio.send(Audio.setVolume(command));	return;
		case "getVolume":			Radio.send(Audio.getVolume());			return;
		case "play":				command.remove(0, String("play ").length());
			Radio.send(Audio.play(command));		return;
		case "isPlaying":			Radio.send(Audio.isPlaying());			return;
		case "pause":				Radio.send(Audio.pause());				return;
		case "resume":				Radio.send(Audio.resume());				return;
		case "isPaused":			Radio.send(Audio.isPaused());			return;
		case "stop":				Radio.send(Audio.stop());				return;
		case "isStopped":			Radio.send(Audio.isStopped());			return;
		case "getLastFileName":		Radio.send(Audio.getLastFileName());	return;
		}
	case "GPS":						command.remove(0, String("GPS ").length());  // if the first word of command is "GPS" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(GPS.clearErrors());			return;
		case "getLastError":		Radio.send(GPS.getLastError());			return;
		case "getErrorCount":		Radio.send(GPS.getErrorCount());		return;
		case "getLocation":			Radio.send(GPS.getLocation());			return;
		case "getAltitude":			Radio.send(GPS.getAltitude());			return;
		case "getTime":				Radio.send(GPS.getTime());				return;
		case "getDate":				Radio.send(GPS.getDate());				return;
		case "getFix":				Radio.send(GPS.getFix());				return;
		case "getSatelliteCount":	Radio.send(GPS.getSatelliteCount());	return;
		}
	case "Servo":					command.remove(0, String("Servo ").length());  // if the first word of command is "Servo" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Servo.clearErrors());		return;
		case "getLastError":		Radio.send(Servo.getLastError());		return;
		case "getErrorCount":		Radio.send(Servo.getErrorCount());		return;
		case "getVoltage":			Radio.send(Servo.getVoltage());			return;
		case "0":					command.remove(0, String("0 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(0));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(0, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(0));			return;
			}
		case "1":					command.remove(0, String("1 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(1));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(1, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(1));			return;
			}
		case "2":					command.remove(0, String("2 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(2));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(2, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(2));			return;
			}
		case "3":					command.remove(0, String("3 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(3));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(3, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(3));			return;
			}
		case "4":					command.remove(0, String("4 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(4));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(4, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(4));			return;
			}
		case "5":					command.remove(0, String("5 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(5));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(5, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(5));			return;
			}
		case "6":					command.remove(0, String("6 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(6));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(6, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(6));			return;
			}
		case "7":					command.remove(0, String("7 ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "getAngle":		Radio.send(Servo.getAngle(7));			return;
			case "setAngle":		command.remove(0, String("setAngle ").length());
									Radio.send(Servo.setAngle(7, command));	return;
			case "goLimp":			Radio.send(Servo.goLimp(7));			return;
			}

		}
	case "Display":					command.remove(0, String("Display ").length());  // if the first word of command is "Display" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Display.clearErrors());		return;
		case "getLastError":		Radio.send(Display.getLastError());		return;
		case "getErrorCount":		Radio.send(Display.getErrorCount());	return;
		case"getUpdateCount":		Radio.send(Display.getUpdateCount());	return;
		case "show":				command.remove(0, String("show ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "all":				Radio.send(Display.showAll());			return;
			case "title":			Radio.send(Display.showTitle());		return;
			case "loopCount":		Radio.send(Display.showLoopCount());	return;
			case "commandCount":	Radio.send(Display.showCommandCount());	return;
			case "totalErrorCount":	Radio.send(Display.showTotalErrorCount()); return;
			case "line0":			Radio.send(Display.showLine0());		return;
			case "line1":			Radio.send(Display.showLine1());		return;
			case "line2":			Radio.send(Display.showLine2());		return;
			case "line3":			Radio.send(Display.showLine3());		return;
			case "signal":			Radio.send(Display.showSignal());		return;
			case "battery":			Radio.send(Display.showBattery());		return;
			case "volume":			Radio.send(Display.showVolume());		return;
			case "timeout":			Radio.send(Display.showAll());			return;
			}
		case "hide":				command.remove(0, String("hide ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "all":				Radio.send(Display.hideAll());			return;
			case "title":			Radio.send(Display.hideTitle());		return;
			case "loopCount":		Radio.send(Display.hideLoopCount());	return;
			case "commandCount":	Radio.send(Display.hideCommandCount());	return;
			case "totalErrorCount": Radio.send(Display.hideTotalErrorCount()); return;
			case "line0":			Radio.send(Display.hideLine0());		return;
			case "line1":			Radio.send(Display.hideLine1());		return;
			case "line2":			Radio.send(Display.hideLine2());		return;
			case "line3":			Radio.send(Display.hideLine3());		return;
			case "signal":			Radio.send(Display.hideSignal());		return;
			case "battery":			Radio.send(Display.hideBattery());		return;
			case "volume":			Radio.send(Display.hideVolume());		return;
			case "timeout":			Radio.send(Display.hideTimeout());		return;
			}
		case "isShowing":			command.remove(0, String("isShowing ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "title":			Radio.send(Display.isShowingTitle());	return;
			case "loopCount":		Radio.send(Display.isShowingLoopCount()); return;
			case "commandCount":	Radio.send(Display.isShowingCommandCount()); return;
			case "totalErrorCount":	Radio.send(Display.isShowingTotalErrorCount()); return;
			case "line0":			Radio.send(Display.isShowingLine0());	return;
			case "line1":			Radio.send(Display.isShowingLine1());	return;
			case "line2":			Radio.send(Display.isShowingLine2());	return;
			case "line3":			Radio.send(Display.isShowingLine3());	return;
			case "signal":			Radio.send(Display.isShowingSignal());	return;
			case "battery":			Radio.send(Display.isShowingBattery());	return;
			case "volume":			Radio.send(Display.isShowingVolume());	return;
			case "timeout":			Radio.send(Display.isShowingTimeout());	return;
			}
		case "setText":				command.remove(0, String("setText ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "line0":			command.remove(0, String("line0 ").length());
									Radio.send(Display.setTextLine0(command)); return;
			case "line1":			command.remove(0, String("line1 ").length());
									Radio.send(Display.setTextLine1(command)); return;
			case "line2":			command.remove(0, String("line2 ").length());
									Radio.send(Display.setTextLine2(command)); return;
			case "line3":			command.remove(0, String("line3 ").length());
									Radio.send(Display.setTextLine3(command)); return;
			}
		case "getText":				command.remove(0, String("getText ").length());  // remove the first word of the command
			switch (firstWord(command)) {
			case "line0":			Radio.send(Display.getTextLine0());		return;
			case "line1":			Radio.send(Display.getTextLine1());		return;
			case "line2":			Radio.send(Display.getTextLine2());		return;
			case "line3":			Radio.send(Display.getTextLine3());		return;
			}
		}
	case "Battery":					command.remove(0, String("Battery ").length());  // if the first word of command is "Battery" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Battery.clearErrors());		return;
		case "getLastError":		Radio.send(Battery.getLastError());		return;
		case "getErrorCount":		Radio.send(Battery.getErrorCount());	return;
		case "getVoltage":			Radio.send(Battery.getVoltage());		return;
		case "getCharge":			Radio.send(Battery.getCharge());		return;
		case "getHealth":			Radio.send(Battery.getHealth());		return;
		case "getCurrent":			Radio.send(Battery.getCurrent());		return;
		case "getPower":			Radio.send(Battery.getPower());			return;
		case "getCapacity":			Radio.send(Battery.getCapacity());		return;
		case "getMinimum":			Radio.send(Battery.getMinimum());		return;
		case "isCharging":			Radio.send(Battery.isCharging());		return;
		case "setMaxCapacity":		command.remove(0, String("setMaxCapacity ").length());
									Radio.send(Battery.setMaxCapacity(command)); return;
		case "setMinimum":			command.remove(0, String("setMinimum ").length());
									Radio.send(Battery.setMinimum(command)); return;
		}
	case "Sensor":					command.remove(0, String("Sensor ").length());  // if the first word of command is "Sensor" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Sensor.clearErrors());		return;
		case "getLastError":		Radio.send(Sensor.getLastError());		return;
		case "getErrorCount":		Radio.send(Sensor.getErrorCount());		return;
		case "getTemperature":		Radio.send(Sensor.getTemperature());	return;
		case "getPressure":			Radio.send(Sensor.getPressure());		return;
		case "getHumidity":			Radio.send(Sensor.getHumidity());		return;
		}
	case "FRAM":					command.remove(0, String("FRAM ").length());  // if the first word of command is "FRAM" and remove the first word of the command
		switch (firstWord(command)) {
		case "clearErrors":			Radio.send(Fram.clearErrors());			return;
		case "getLastError":		Radio.send(Fram.getLastError());		return;
		case "getErrorCount":		Radio.send(Fram.getErrorCount());		return;
		case "getData":				command.remove(0, String("getData ").length());
									Radio.send(Fram.getData(command));		return;
		case "clearData":			Radio.send(Fram.clearData());			return;
		}
	case "System":					command.remove(0, String("System ").length());  // if the first word of command is "System" and remove the first word of the command
		switch (firstWord(command)) {
		case "wakeUp":				Radio.send(wakeUp());					return;
		case "goToSleep":			Radio.send(goToSleep());				return;
		case "restart":				Radio.send(restart());					return;
		case "getAvailableMemory":	Radio.send(String(freeMemory()) + " bytes"); return;
		case "getVersion":			Radio.send(VERSION);					return;
		case "ping":				Radio.send("pong");						return;
		case "forceCrash":			Radio.send(forceCrash());				return;
		case "shutDown":			Radio.send(shutDown());					return;
		case "getTimeLeft":			Radio.send(getTimeLeft());				return;
		}
	default:						Radio.send("EpicError: " + command);	return;
	}
}

bool firstWordOf(String command, String key){//is key the first word in command? If so return true; if not return false.
  if(firstWord(command).equals(key)){return true;} //note that this is case sensitive
  else{return false;}
}

String firstWord(String command){//returns the first word of a string, denoted by a space, not including the space.
  int index=command.indexOf(" ");
  if(index==-1){index=command.length();}
  return command.substring(0,index);
}

String wakeUp(){return "Not implemented yet";}
String goToSleep(){return "Not implemented yet";}
String restart(){return "Not implemented yet";}
