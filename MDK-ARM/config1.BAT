SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\Parallels\Parallels Tools\Applications;C:\Program Files (x86)\STMicroelectronics\st_toolset\asm;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\
SET CPU_TYPE=STM32L071RBTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=config1
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\system_stm32l0xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_rcc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_rtc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_wwdg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_dma.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_adc_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_cortex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_flash_ramfunc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_rtc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_i2c_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_pwr.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_uart_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_spi.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_tim_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_pwr_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_flash_ex.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "config1\startup_stm32l071xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_hal_msp.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\stm32l0xx_it.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\spiflash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\delay.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\pwm_tim2.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\key.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\gpio_i2c.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\battery.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\ads1115.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\elec_sw.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\cat9555.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\usart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\e_ink.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "config1\test_seq.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "config1\config1.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "config1\config1.axf" --i32combined --output "config1\config1.hex"
