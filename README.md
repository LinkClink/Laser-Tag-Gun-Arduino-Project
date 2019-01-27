# Arduino-Project-Pistol-Laser-Tag

Realizacja projectu
~ Kiedy zaczynałem robić tę projekt to chciałem zrobić broń podobną do automata AK-47 w wyniku wuszło coś bardzo podobne:
Arduino ma swój język bardzo podobny do wiadomych języków takich jak (Java, C++ C ) , na podstawie tego napisałew sterownik jaki zarządza arduino i innymi sterownikami.
~ Sam kod jest za duży żeby pokazywac wszyski kod dlatego pokazuje kawałki:
Funkcja pszeladowania:
Zmienne:
magazine: magazynek AK-47 (standartowo 30 nab.)
life: życie graca  (standartowo 100)
flag_err: flag jaki broni wykorzystanie danej funkcji
all_mag: ilość dostępnych nabojów
st_rel: przerywania możliwości stszelania 

if( magazine<30 && life>0 && flag_err == 0 && all_mag>0 ) 
{
rec_mag=30-magazine;
if( all_mag-rec_mag >= 0 )
{
all_mag-=rec_mag;
magazine=30;
st_rel=1; //test stop shot but reload
}
if(magazine+all_mag<=30)
{
magazine+=all_mag;
all_mag=0;
st_rel=1;
}
rec_mag=30; //test stop shot but reload
}
}




Funkcja pszelączenia typa strzelania:
Zmienne:
flag_err: flag jaki broni wykorzystanie danej funkcji
type_st: drugi flag jaki nie daje powtarzać naciskania pszycisku 
life: życie graca  (standartowo 100)
type: typ stszelania ( 0 – automat 1 – semi-automat)

        void fun_type()                                              
          {                                                          
            if( type_st==0 && life>0 && flag_err==0 )                  
            {                                                                                           
             if(type==0)                                            
              {                                                      
               type_st=1;                                            
               type=1;                                              
              }                                                     
              else                                                   
              {                                                      
               type_st=1;                                            
               type=0;                                               
              }                                                      
            }                                                        
         }                                                           

Funkcja strzelania:
Zmienne:
buttonState: znajduje się na 5 pinie sprawdza naciśnienia przycisku
st_rel: flag jaki blokuje powtarzanie nacziśnienia pszycisku (pszeladowania)
flag_err: zastęp ot blędów
type_st: flag jaki blokuje powtarzanie naciskania pszycisku (pszelączenia typa strzelania)
magazine: magazynek AK-47 (standartowo 30 nab.)
flag_type: flag jaki pomaga pszy zmianie typa stszelania
   int fun_shot()                                                                 
     {                                                                           
      int buttonState = digitalRead(button_shot);                                 
      if(st_rel==1) // funkcja testowa naprawia (powtarzania naciskania pszyczisków)          
      {                                                                           
        flag_err=1;                                                               
        delay(200);                                                               
        tmrpcm.play( "reload.wav" ); //play rel voice                            
        delay (3800);                                                             
        st_rel=0;                                                                 
        flag_err=0;                                                               
       }                                                                          
      if(type_st==1) // funkcja testowa naprawia (powtarzania naciskania pszyczisków)          .                
      {                                                                           
       flag_err=1;                                                                
       delay (200);                                                               
       tmrpcm.play( "type.wav" ); //play type voice                              
       delay (350);                                                               
       type_st=0;                                                                 
       flag_err=0;                                                                
      }                                                                           
      if(buttonState==HIGH && life>0 && flag_type==0 && flag_err==0)              
        {                                                                         
          flag_err=1;                                                             
          if(type==1)                                                             
           {                                                                      
            flag_type=1;                                                          
           }                                                                      
         if(magazine<=0 && em_fl==0) // magazynek pusty
          { em_fl=1;                                                              
            tmrpcm.play( "empty.wav" ); //play empty voice                        
            delay(400);                                                           
          }                                                                       
          if(magazine>0)                                                          
           {                                                                      
            magazine-=1;                                                          
            irsendstd.sendNECstd(0xFF28D7, 32);  //  
            Serial.print("Shot"); // test
            tmrpcm.play( "shot.wav" ); //play shot voice                
            }                                                                     
            delay(135); //520                                                     
           }                                                                      
           flag_err=0;                                                            
     }                                                                            

Odstęp:
Sam kod ma około 300 linii z nich dużo deklaracji zmiennych bibliotek i innych zeczy , pszedstałiłem tu kilka funkcji z całego programu.




Schemat projektu

Sam projekt obchodzi się okolo 23$ z baterią i 14$ bez , za elektronike.

Do niej wchodzi:

1.Linza + 6,47 / 10 = 0,64 USD
2. Arduino uno / nano + 2,53 USD
3. Przyciski + 1 $
4. Transfery + 1,50 USD
5. Czytnik SD + 0,61 $
6. Glosnik + 2,74 USD
7. Czujniki IR + 0,57 $
8. Nadajnik IR + 1,43 / 10 = 0,14 $
9. Komora baterii + 1,87 $
10. Ladowarka +
11. Konwerter + 
12. Karta SD + 2,84 USD
13. Wejście lan + 2,12 / 5 = 0,42 wejściowe 3,5 mm = 1,53 / 4 = 0,38 USD
14. Bateria + +/- 9000MA 8,25 USD
15. Przewód 3.55 USD // rj-11/12

Oczywiście jeście do tego mamy dołączyć cene samej broni , będzie ona zrobiona pszez was albo kupiona to mamy na wybór dwa sposoby 
drogi i tani 
~ pierwszy to maket “ Air soft ” repliki jaki kosztuje od 200+ złotych 
są twoszone sztuczne z dobrego plastyku czasem z metalu są ciężkie i dobre wyglądają
~ drugi jest więć tańszy damo nazwy zabawki dla dzieci podobne do broni, czasami są nie zle kosztują ok 30+ złotych.





Sam schemat:
![alt text](https://pp.userapi.com/c851420/v851420223/a135f/7i_2P8dpkdo.jpg)
Opis shematu:
W schemacie wykorzystujemi ze tszy przyciski 
- do strzelania 
- do pszelączenia typa strzelania (auto , semi-auto)
- do przeładowania
Wykoszystujemi glośnik dla podania różnych dzwięków , same rekordy bierzemy z karty SD pszez odczytywać.
Mamy również nadajnik i czujnik IR dla strzelania i odbierania sygnalów.
Dla zasilania arduino wykorzystujemi baterie Lipo i konwerter dla zwiększenia moćy ladujemy pszez port micro-usb. 

