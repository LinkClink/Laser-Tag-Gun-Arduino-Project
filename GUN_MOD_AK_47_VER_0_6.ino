/// GUn AK-47 ////// by LibkClink - + - ver 0.3
///
#include <IRremote.h>   // IR sensor library (pin: 8)
#include <IRstD.h>     // IR transmitter library (pin: 8)
#include <Thread.h>   // time translation library (300)
#include <TMRpcm.h>  // sound playback library
#include <SPI.h>    // speaker library
#include <SD.h>    // SD Picture Library
///
#define CHIP_SELECT_PIN 4  // Pin SD Picture (CS)
#define SPEAKER_PIN 10    // Speaker pin (10)
TMRpcm tmrpcm;           // Variable sound reproduction
Thread rec = Thread (); // Flow (cycle) IR pr.
///
IRsendstd irsendstd;         // Pin of the transmitter (-9-)
decode_resultsstd res_std;  // Decode pin transmitter
const byte ir_rec = 8;     // IR Successor Variable
IRrecv irrecv (ir_rec);   // Pin successor (-9-)
decode_results results;  // Decoding pin successor
///
// Weapons /////////////
byte but_type = 0, rec_type = 1, flag_type = 0, type = 0; // Pin button type shooting (-3-)
byte magazine = 30, rec_mag = 30;                        // Change weapon shop
const byte button_shot = 5;                             // Pin buttons are whistled
const byte but_reload = 1;                             // Pin reload button (-2-)
int all_mag = 0;                                      // Change weapon shop
// Weapons /////////////
///
//Character//////////
int damage_to_me_1, damage_to_me_2, damade_turn; // Damage on the character and on commands
byte life = 100, life_fl = 0;                   // Character's life and life flag
//Character//////////
///
// Commands /////////////
const int red_team_dam_me_1, red_team_dam_me_2, red_team_dam_turn;          // Damage on the character and on commands
const int blue_team_dam_me_1, blue_team_dam_me_2, blue_team_dam_turn;      // Damage on the character and on commands
const int green_team_dam_me_1, green_team_dam_me_2, green_team_dam_turn;  // Damage on the character and on commands
const int every_team_dam_me_1, every_team_dam_me_2, every_team_dam_turn; // Damage on the character and on commands
// Commands /////////////
///
// Additional functions ////////////
byte flag_err = 0; // The function of the prohibition of pressing the button
byte functions,   // Variable of functions
st_rel = 0,      // Bounce of reload button (corrected)
type_st = 0,    // Button type bounce (corrected)
dam_st = 0;    // Pre-Damage Damage
int i;
byte em_fl = 0;
// Additional functions ////////////
///
  void setup ()
  {
   Serial.begin (9600);                 // Console work
   tmrpcm.speakerPin = SPEAKER_PIN;    // Declaration of the SD speaker pin
  // if (! SD.begin (CHIP_SELECT_PIN)) {return;} else tmrpcm.play ("start.wav"); // Check SD Card
   irrecv.enableIRIn (); // Turn on IR sensor
   ////
   attachInterrupt (but_reload, fun_reload, CHANGE);  // Preloading for recharge
   attachInterrupt (but_type, fun_type, CHANGE);     // Predivanie to switch shooting mode
   ////
   rec.onRun (fun_check_ir_rec);  // Stream prerivaniye
   rec.setInterval (300);        // Interval prerivaniya (300)
   ////
   irrecv.blink13 (true);
  }
  
///// Recharge function /////////////////////////////////////
    void fun_reload () 
   {
   if (magazine <30 && life> 0 && flag_err == 0 && all_mag> 0) 
    {
      rec_mag = 30-magazine; 
     if (all_mag-rec_mag> = 0) 
     {
       all_mag- = rec_mag; 
       magazine = 30; 
       st_rel = 1; // test stop shot but reload 
     } 
     if (magazine + all_mag <= 30) 
     {
       magazine + = all_mag; 
       all_mag = 0; 
       st_rel = 1; 
     } 
     rec_mag = 30; // test stop shot but reload //
    } 
   } 
////////// end /////////////////////////////////////// /////////


/////Shot AK-47//////////////////////////////////////////////////////////////////
   int fun_shot()                                                                 //      
     {                                                                            //
      int buttonState = digitalRead(button_shot);                                 //
      if(st_rel==1) // test funct. (bounce contacts)  //4000                      //
      {                                                                           //
        flag_err=1;                                                               //
        delay(200);                                                               //
        tmrpcm.play( "reload.wav" ); //play rel voice                             //
        delay (3800);                                                             //
        st_rel=0;                                                                 //
        flag_err=0;                                                               //
       }                                                                          //
      if(type_st==1) // test funct. ((bounce contacts)) испр.                     //
      {                                                                           //
       flag_err=1;                                                                //
       delay (200);                                                               //
       tmrpcm.play( "type.wav" ); //play type voice                               //
       delay (350);                                                               //
       type_st=0;                                                                 //
       flag_err=0;                                                                //
      }                                                                           //
      if(buttonState==HIGH && life>0 && flag_type==0 && flag_err==0)              //
        {                                                                         //
          flag_err=1;                                                             //
          if(type==1)                                                             //
           {                                                                      //
            flag_type=1;                                                          //
           }                                                                      //
         if(magazine<=0 && em_fl==0) // magazine is empty                         //
          { em_fl=1;                                                              //
            tmrpcm.play( "empty.wav" ); //play empty voice                        //
            delay(400);                                                           //
          }                                                                       //
          if(magazine>0)                                                          //
           {                                                                      //
            magazine-=1;                                                          //
            irsendstd.sendNECstd(0xFF28D7, 32);  // test    
            Serial.print("Shot");
            tmrpcm.play( "shot.wav" ); //play shot voice //i//                    //
            }                                                                     //
            delay(135); //520                                                     //
           }                                                                      //
           flag_err=0;                                                            //
     }                                                                            //
//////////end///////////////////////////////////////////////////////////////////////
     
/////IR successor check function(300с)////////////////////////////////////////////
   int fun_check_ir_rec()                                                       //
      {                                                                         //
        if(irrecv.decode(&results))                                             //
          {  Serial.println(results.value, HEX);                                //
                  ////blue_team//// 11 button in the rem. contr.                //
              if (results.value == 0xFF926D ) //test                            //
                 {                                                              //
                   life=100;     //test                                         //
                   magazine=30; //test                                          //
                   all_mag=150;                                                 //
                   type=0;                                                      //
                   damage_to_me_1=red_team_dam_turn;                            //
                   damage_to_me_2=green_team_dam_turn;                          //
                   damade_turn=blue_team_dam_turn;                              //
                   life_fl=0;                                                   //
                   tmrpcm.play( "blue.wav" ); //play team voice                 //
                   delay(1200);                                                 //
                 }                                                              //
                  ////red_team//// 9 button in the rem. contr.                  //
              if (results.value == 0xFF2AD5)// test                             //
                 {                                                              //
                   life=100;     //test                                         //
                   magazine=30; //test                                          //
                   all_mag=150;                                                 //
                   type=0;                                                      //
                   damage_to_me_1=blue_team_dam_turn;                           //
                   damage_to_me_2=green_team_dam_turn;                          //
                   damade_turn=red_team_dam_turn;                               //
                   life_fl=0;                                                   //
                   tmrpcm.play( "red.wav" ); //play team voice                  //
                   delay(1200);                                                 //
                 }                                                              //
                  ////green_team//// 10 button in the rem. contr.               //
              if (results.value == 0xFFAA55) //test                             //
                 {                                                              //
                   life=100;     //test                                         //
                   magazine=30; //test                                          //
                   all_mag=150;                                                 //
                   type=0;                                                      //
                   damage_to_me_1=every_team_dam_me_1;;                         //
                   damage_to_me_2=0;                                            //
                   damade_turn=green_team_dam_turn;                             //
                   life_fl=0;                                                   //
                   tmrpcm.play( "green.wav" ); //play team voice                //
                   delay(1200);                                                 //
                 }                                                              //
                 ////evey_team//// 12 button in the rem. contr.                 //
                 if (results.value == 0xFF12ED) //test                          //
                 {                                                              //
                   life=160;     //test                                         //
                   magazine=30; //test                                          //
                   all_mag=300;                                                 //
                   type=0;                                                      //
                   damage_to_me_1=blue_team_dam_turn;                           //
                   damage_to_me_2=red_team_dam_turn;                            //
                   damade_turn=every_team_dam_turn;                             //
                   life_fl=0;                                                   //
                   tmrpcm.play( "every.wav" ); //play team voice                //
                   delay(1200);                                                 //
                 }                                                              //
                 ////off_mode/// 12 button in the rem. contr.                   //
                 if (results.value == 0xFF02FD) //test                          //
                 {                                                              //
                   life=0;     //test                                           //
                   magazine=0; //test                                           //
                   all_mag=0;                                                   //
                   type=0;                                                      //
                   damage_to_me_1=0;                                            //
                   damage_to_me_2=0;                                            //
                   damade_turn=0;                                               //
                   life_fl=0; // test                                           //
                   tmrpcm.play( "off.wav" ); //play team voice                  //
                   delay(1000);                                                 //
                 }                                                              //
                  ////damage//// damage                                          //
                  if(life_fl<=5 && life>0) // test                              //
                  {                                                             //
                   if (results.value == 0xFF3AC5 || results.value == 0xFFBA45 ) //
                   {                                                            //
                    life_fl++;                                                  //
                    life-=20;   // test                                         //
                    dam_st=1;  // flag                                          //
                   }                                                            //
                  }                                                             //                                                                     
                  irrecv.resume(); //take the next signal                       //
         }                                                                      //
     }                                                                          //
//////////end/////////////////////////////////////////////////////////////////////

///// Switching of the page. AK-47 //// (automatic semi-automat) //////
        void fun_type()                                              //
          {                                                          //
            if(type_st==0 && life>0 && flag_err==0)                  //
            {                                                        //                                        
             if(type==0)                                             //
              {                                                      //
               type_st=1;                                            //
               type=1;                                               //
              }                                                      //
              else                                                   //
              {                                                      //
               type_st=1;                                            //
               type=0;                                               //
              }                                                      //
            }                                                        //
         }                                                           //
//////////end//////////////////////////////////////////////////////////
      

