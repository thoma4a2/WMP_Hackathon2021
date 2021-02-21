import controlP5.*;
import processing.serial.*;

// declare masks
Serial port;
ControlP5 cp5;
PFont font;
int water_value = 0;
int change = 0;
int temp = 0;


void setup() {
  size(525, 500); //width, height
  background(160, 160, 190); //set background to black
  port = new Serial(this, "COM4", 9600);
  port.bufferUntil(1);


  cp5 = new ControlP5(this);
  font = createFont("Arial", 20);
  cp5.setFont(font);
  CallbackListener listener;

  
 //listener = new CallbackListener() {
 //     public void controlEvent(CallbackEvent event){
 //     if (event.getAction() == ControlP5.ACTION_RELEASE)
 //       if (temp == 0 || temp == water_value){
 //           water_value = 0;
 //       }
 //       else
 //           water_value = change;
 //           temp = water_value;
 //     }
 // };
  
 // cp5.addCallback(listener);
  
  //cp5.addButton("Check")
  //  .setPosition(300, 280)
  //  .setSize(175, 100)
  //  .setColorBackground(color(0, 0, 100))
  //  ;
     
  
  textFont(font);
  text("Water Requirement Level", 40, 50);
  cp5.addButton("Low")
    .setPosition(50, 60)
    .setSize(200, 100)
    .setColorBackground(color(100, 0, 0))
    ;

  cp5.addButton("Moderate")
    .setPosition(50, 170)
    .setSize(200, 100)
    .setColorBackground(color(100, 100, 0))
    .setColorActive(color(100, 100, 0))
    ;

  cp5.addButton("High")
    .setPosition(50, 280)
    .setSize(200, 100)
    .setColorBackground(color(0, 100, 0))
    ;
    
    
    cp5.addButton("Demo")
    .setPosition(400, 400)
    .setSize(70, 50)
    .setColorBackground(color(100, 100, 100))
    ;
}

void draw(){
    //cp5.addTextfield("Days")
    //.setPosition(300, 60)
    //.setSize(175, 80)
    //.setAutoClear(true)
    //.setColorBackground(color(140, 140, 170))
    //.setText("           " + str(water_value))
    //;
//    if (water_value == 0)
//      text("           " + str(water_value))
 //   else
  //    .setText("           " + str(water_value))
    
}

void Low(){
  port.write('0');
}

void Moderate(){
  port.write('1');
}

void High(){
  port.write('2');
}

void Demo(){
  port.write('4');
}


//void Check(){
//  port.write('3');
//  if (port.available() > 1){
//  change = port.read();
//  port.clear();
//  }
//}
