/*
www.DFRobot.com
last updated by Gary on 02/02/2015
wiki doc http://www.dfrobot.com/wiki/index.php/BLE_Wireless_Gamepad_(SKU:DFR0304)
Support Forum: http://www.dfrobot.com/forum/
e-mail: luguanyu.sjtu@gmail.com
Thank Lisper for the basic code.
ibrary version:1.0
*/

#include "BleGamepad.h"

BleGamepad::BleGamepad()
{
}

//get buffer
int BleGamepad::get_buffer()
{
	if(Serial.available())
  {
    for(_i = 0; _i < 15;_i++)
    {
      _databuf[_i]=Serial.read();
      delay(2);
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

//check the buffer
int BleGamepad::check_buffer()
{
  if (get_buffer())
  {
    if(_databuf[0] == 0x55 || _databuf[1] == 0xaa || _databuf[2] == 0x11)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

//get the number of the buttons being pressed
int BleGamepad::button_number()
{
  return _databuf[3];
}

//get the stick state
void BleGamepad::get_stick_state(int *stick_state)
{
  int val;
  for ( _i = 0;_i < 4;_i++)
  {
    val = _databuf[4] >> _i;
    if (val&0x01 == 0x01)
    {
      stick_state[_i] = 1;
    }
    else
    {
      stick_state[_i] = 0;
    }
  }
}

//get the stick position
void BleGamepad::get_stick(int *stick)
{
  get_stick_state(stick_state);
  for(_i = 0;_i < 4;_i++ )
  {
    if (stick_state[_i])
    {
      stick[_i] = _databuf[5+button_number()+_i];
    }
    else
    {
      stick[_i] = 128;
    }
  }
}

//get the name of the buttons
void BleGamepad::get_button(int *button)
{
  for (_i = 0;_i < 3;_i++)
  {
    button[_i] = 0;
  }
  for (_i = 0;_i < button_number();_i++)
  {
    button[_i] = _databuf[5+_i];
  }
}

//get the state of every buttons
void BleGamepad::check_button(int *button_state)
{
  get_button(button);
  for (_i = 0;_i < 14;_i++)
  {
    button_state[_i] = 0;
  }
  for (_i = 0;_i < 14;_i++)
  {
    for (int j = 0;j < button_number();j++)
    {
      if (button_name[_i] == button[j])
      {
        button_state[_i] = 1;
      }
    }
  }
}
