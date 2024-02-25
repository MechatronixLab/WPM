# WEARABLE PATIENT MONITOR  
  
This prototype is a proof of concept (POC) for a connected wearable patient monitor capable of measuring oximetry parameters, temperature and track the patient's movement.  
  
It is based on the [Nucleo WL55JC1](https://www.st.com/en/evaluation-tools/nucleo-wl55jc.html) 
([STM32WL55JC](https://www.st.com/en/microcontrollers-microprocessors/stm32wl55jc.html) from ST Microelectronics), 
Maxim (now Analog Devices) [MAX30102](https://www.analog.com/en/products/max30102.html) pulse oximetry sensor, 
Würth Elektronik [WSEN-ISDS](https://www.we-online.com/en/components/products/WSEN-ISDS) 6-DOF IMU, 
an OLED display and a buzzer for simple audio generation.  
  
The device features LoRa connection, allowing it to be used in remote locations where telecommunications infrastructure is not well established.

## Prototype

![Prototype](./IMG/prototype.png)

![Prototype](./IMG/prototype_highlighted.png)

### LoRa Receiver  

A very simple LoRa receiver was assembled using a [LoRa module](https://www.nicerf.com/lora-module/sx1276-lora-module-lora1276.html) from [G-NiceRF](https://www.nicerf.com/), 
which is based on the [SX1276](https://www.semtech.com/products/wireless-rf/lora-connect/sx1276) chip from [Semtech](https://www.semtech.com/), and a BluePill board, which is based on ST Microelectronics STM32F103.    
The software running on the BluePill is a slightly modified version of [arduino-LoRa-STM32](https://github.com/armtronix/arduino-LoRa-STM32) that was deleoped by [ARMtronix Technologies](https://github.com/armtronix).

LoRa module:  

![LoRa Module](./IMG/sx1276_module.png)  
  
More information about how to make this receiver can be found on this [video](https://www.youtube.com/watch?v=A0RhP0SkhkQ&ab_channel=HowToElectronics) 
and [arcticle](https://how2electronics.com/interfacing-lora-sx1276-with-stm32-microcontroller-lr1276-915mhz/) from [How To Electronics](https://how2electronics.com/).

Receiver:  
  
![LoRa Receiver](./IMG/lora_receiver.png)  
  
The software modifications made were necessary to match the radio configuations on the STM32WL55:  
- Frequency: 915 MHz  
- Bandwidth: 500 kHz  
- Spreading Factor: 11  




  

### Software initialization

As the software starts, 3 opening screens are shown:

![Opening screen 1 - Project Title](./IMG/screen_opening_1.png)  
  
![Opening screen 2 - Software Version](./IMG/screen_opening_2.png)  
  
![Opening screen 3 - Elektor/ST Contest information](./IMG/screen_opening_3.png)  

The device also prints data via its serial port:
  
![Serial console](./IMG/serial_console.png)    
  



  
## Acknowledgements  
  
[**Fabio Souza**](https://github.com/FBSeletronica) and [**Halysson Jr**](https://github.com/halyssonjr) @ [Franzininho](https://github.com/Franzininho)  
**William Maia** and **Daniel Botelho** @ [ST Microelectronics](https://github.com/stmicroelectronics) Brazil  
**Fabio Costa** and **Érico Hassegawa** @ [Würth Elektronik](https://github.com/WurthElektronik) Brazil  
**Matt Mielke** @ DigiKey, for writing [this arcticle](https://forum.digikey.com/t/using-the-low-level-sub-ghz-radio-driver-for-the-stm32wl-series/18253) explaining how to use the SubGHz module on the STM32WL55  
[**Elektor Magazine**](https://www.elektormagazine.com/) and [**ST Microelectronics**](https://github.com/stmicroelectronics), for promoting the [STM32 Wireless Innovation Design Contest](https://www.elektormagazine.com/st-contest)  
