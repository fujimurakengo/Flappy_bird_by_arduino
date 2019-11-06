#include <TVout.h>
#include <fontALL.h>


#define terrain_width 5
#define through_hight 40
///#define terrain_between_width 20
float terrain_heights[]={0.2 ,0.2 ,0.5, 0.4  ,0.1,0.4,0.1};
int       terrain_pos[]={0   ,50, 100 ,150 ,200 ,250, 300};
void Product_terrain(int start_x,int hight);
TVout TV;


int Bird_y_poss;
//int terrain_pos=TV.hres();
bool Is_player_jumped(){
  //ここに加速度センサーからの値をぶち込んで

   return( digitalRead(13));
}

void update_terrain(){
  for (int i=0;i<7;i++){
   terrain_pos[i]--;   
   if(terrain_pos[i]>0&&terrain_pos[i]<TV.hres()){
      Product_terrain(terrain_pos[i],TV.vres()*terrain_heights[i]);
   }
  }
}


void setup() {
  pinMode(13,INPUT);
   digitalWrite(13,HIGH);
  TV.begin(PAL,120,96);
  Bird_y_poss=40;
  TV.draw_circle(TV.hres()/2,Bird_y_poss,5,WHITE);  

  
    Bird_y_poss=40;
  
  
 for(int  Bird_y_speed=0;  Bird_y_poss <TV.vres() ; Bird_y_speed=Bird_y_speed+1){
    TV.clear_screen();
    TV.draw_circle(TV.hres()/4,Bird_y_poss,5,WHITE);  
    if( digitalRead(13)&& Bird_y_speed>0){
      Bird_y_speed = -5;
    }
       Bird_y_poss = Bird_y_poss + Bird_y_speed;
     update_terrain();
    if( Bird_y_poss <0)
     Bird_y_poss = 0; 
     
     TV.delay(100);
  }

  
}

void loop() {
 TV.select_font(font8x8);
 if(terrain_pos[6]<0){
  TV.println("You Win");
  }
   
 else{
   TV.println("You Lose!!!");
  }
  
  
  while(1){};

}


void Product_terrain(int start_x,int hight){

  //下の地形
  
  TV.draw_line( start_x, 
                TV.vres(),
                start_x,
                TV.vres()-hight,
                WHITE);
  TV.draw_line( start_x, 
                TV.vres()-hight,   
                start_x+ terrain_width,
                TV.vres()-hight,
                WHITE);
  TV.draw_line( start_x+terrain_width ,
                TV.vres()-hight,
                start_x+terrain_width ,
                TV.vres(),WHITE);


  //上の地形through_width
  TV.draw_line( start_x, 
                0,  
                start_x,
                TV.vres()-hight-through_hight,
                WHITE);
  TV.draw_line( start_x,
                TV.vres()-hight-through_hight, 
                start_x+terrain_width, 
                TV.vres()-hight-through_hight,
                WHITE);
  TV.draw_line( start_x+terrain_width ,
                TV.vres()-hight-through_hight ,
                start_x+terrain_width ,
                0,WHITE);
  
}
/* Draw a line from one point to another
 *
 * Arguments:
 *  x0:
 *    The x coordinate of point 0.
 *  y0:
 *    The y coordinate of point 0.
 *  x1:
 *    The x coordinate of point 1.
 *  y1:
 *    The y coordinate of point 1.
 *  c:
 *    The color of the line.
 *    (see color note at the top of this file)
 *    void TVout::draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c) {
 */

