/* Main tools used in animation such as 
   - The eyes light up slowly in a color C
   - The heart's beat speed up

*/

#include "ch.h"
#include "hal.h"
#include "test.h"

static int CYCLIC_RATIO = 200; /* Number of states in PWM*/
/* A FAIRE : CHOISIR LE TYPE. INT INNEFICACE (TROP DE BITS INUTILISES) */


static void clear_all_tim2 (PWMDriver *pwmd)
{
  palSetPad(GPIOA, GPIOA_UV1); 
  palSetPad(GPIOA, GPIOA_UV2);
  palSetPad(GPIOA, GPIOA_RGBsmall_B);
  palSetPad(GPIOB, GPIOB_RGBsmall_G);
}

static void clear_all_tim3 (PWMDriver *pwmd)
{
  palSetPad(GPIOB, GPIOB_RGBsmall_R); 
  palSetPad(GPIOA, GPIOA_RGBbig_G);
  palSetPad(GPIOB, GPIOB_RGBbig_B);
  palSetPad(GPIOB, GPIOB_RGBbig_R);
}


static PWMConfig pwmcfg_tim2 = {
  20000,
  CYCLIC_RATIO,
  clear_all_tim2,
  {
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Small Eye, blue */
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Small Eye, green */
    {PWM_OUTPUT_DISABLED, NULL}, /* LED UV 1 : Head*/
    {PWM_OUTPUT_DISABLED, NULL},/* LED UV 2 : Heart*/
  
  },
  0,
  0
};

static PWMConfig pwmcfg_tim3 = {
  20000,
  CYCLIC_RATIO,
  clear_all_tim3,
  {
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Small Eye, red */
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Big Eye, green*/
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Big Eye, blue */
    {PWM_OUTPUT_DISABLED, NULL}, /* LED RGB Big Eye, red */
  
  },
  0,
  0
};




/* Eyes light up/ light down slowly :
   Eye -> "2" if both eyes, "b" if only the big one, "s" if only the small one
   blue, red, green -> color (between 0 and 255)
   intensity -> between 0 (off) and 10 (full on)
   Time -> duration of the lightening
*/
static void eyes_lightening (char eye, int8 blue, int8 red, int8 green ,int8 initial_intensity, int8 final_intensity,int time ) = {
  int t = time/CYCLIC_RATIO; 
  int sens = initial_intensity<final_intensity ? 1 : -1;

    for(int i=1+(initial_intensity*CYCLIC_RATIO/10); i<CYCLIC_RATIO*final_intensity/10; i+=sens) {

      int c_bigblue = (eye = "2" | eye = "b") ? (i*blue)/256 : 0;
      int c_bigred = (eye = "2" | eye = "b") ? (i*red)/256 : 0;
      int c_biggreen = (eye = "2" | eye = "b") ? (i*green)/256 : 0;
      int c_smallblue = (eye = "2" | eye = "s") ? (i*blue)/256 : 0;
      int c_smallred = (eye = "2" | eye = "s") ? (i*red)/256 : 0;
      int c_smallgreen = (eye = "2" | eye = "s") ? (i*green)/256 : 0;

      pwmEnableChannel(&PWMD3, 2, c_biggreen); 
      pwmEnableChannel(&PWMD3, 3,c_bigblue);
      pwmEnableChannel(&PWMD3, 4, c_bigred);

      pwmEnableChannel(&PWMD2, 2, c_smallgreen);
      pwmEnableChannel(&PWMD2, 1,c_smallblue);
      pwmEnableChannel(&PWMD3, 1, c_smallred);	

      chThdSleepMilliseconds(t);  
    }
};

static void set_heart_beat (int speed) = { 
  
  pwmEnableChannel(&PWMD2, 4,CYCLIC_RATIO/2 );     /* big beat */ 
  chThdSleepMilliseconds(speed/8);
  pwmEnableChannel(&PWMD2, 4, 0 );                /*turn off */
  chThdSleepMilliseconds(speed/16);  
  pwmEnableChannel(&PWMD2, 4,CYCLIC_RATIO/2 );    /* small beat */ 
  chThdSleepMilliseconds(speed/16);  
  pwmEnableChannel(&PWMD2, 4,0 );                 /* turn off*/
  chThdSleepMilliseconds(speed*3/4);    
    

}

