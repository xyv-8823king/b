#include "head.h"

#define B1_ON HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET
#define B2_ON HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == GPIO_PIN_RESET
#define B3_ON HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == GPIO_PIN_RESET
#define B4_ON HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET
 double get_vol (ADC_HandleTypeDef *hadc)
 {
    HAL_ADC_Start(hadc);
    uint16_t value = HAL_ADC_GetValue(hadc);
    return (3.3*value)/4096 ;
 
 }
 char text[20];
 double vol_7;
 double vol_8; 
 double low_7;
 double upper_7;
  double low_8;
 double upper_8;
  void lcd_goods(){          
sprintf(text,"       GOODS    ");
LCD_DisplayStringLine(Line2,(uint8_t *)text);
sprintf(text,"     R37:%.2fV      ",vol_7);
LCD_DisplayStringLine(Line4,(uint8_t *)text);
sprintf(text,"     R38:%.2fV      ",vol_8);
LCD_DisplayStringLine(Line5,(uint8_t *)text);
 }
        
void lcd_stand(){
    sprintf(text,"      STANDARD   ");
    LCD_DisplayStringLine(Line2,(uint8_t *)text);
    sprintf(text,"     SR37:%.1f-%.1f  ",low_7,upper_7);
    LCD_DisplayStringLine(Line4,(uint8_t *)text);
    sprintf(text,"     SR38:%.1f-%.1f  ",low_8,upper_8);
    LCD_DisplayStringLine(Line5,(uint8_t *)text);
}
//void lcd_pass(){
//    sprintf(text,"      PASS   ");
//    LCD_DisplayStringLine(Line2,text);
//    sprintf(text,"     SR37:%.1f%%  ",pass_7);
//    LCD_DisplayStringLine(Line4,text);
//    sprintf(text,"     SR38:%.1f%% ",pass_8);
//    LCD_DisplayStringLine(Line5,text);

//}
double low_7 = 1.0; double upper_7 = 2.0;
double low_8 = 2.0; double upper_8 = 3.0;
int page_index = 0;
  uint8_t flg=0;
void Key_scan(){
   if (B1_ON)
    {  while(B1_ON){
        page_index ++;
        page_index %= 3;}
    }
    
}
void show(){  
   switch(page_index){
       case 0:
  vol_7 = get_vol(&hadc2);
    vol_8 = get_vol(&hadc1);
    lcd_goods();  break;
       case 1:
      
        if (B2_ON)
        {
            flg++;
            flg %= 4;
        
        if ((flg==0 )&& (B3_ON) ){
             plus(upper_7);
        }
        if ((flg==1 )&& (B3_ON) ){
             plus(low_7);  
        }
           if ((flg==2)&& (B3_ON) ){
             plus(upper_8);
        }
            if ((flg==3)&& (B3_ON) ){
             plus(low_8);
        }
          
        
        }
          lcd_stand();  break;
        
    
    
    }
}

double plus( double para){
    para +=0.2;
    return para;


}
