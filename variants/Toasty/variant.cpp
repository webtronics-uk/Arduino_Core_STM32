#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
// Match Table 20. NUCLEO-H743ZI pin assignments
// from UM1974 STM32 Nucleo-144 board
const PinName digitalPin[] = {
  PA_1,  //D0 - USART_A_RX
  PA_2, //D1 - USART_A_TX
  PA_3, //D2
  PA_4, //D3 - TIMER_A_PWM3
  PA_5, //D4
  PA_6, //D5 - TIMER_A_PWM2
  PA_7,  //D6 - TIMER_A_PWM1
  PA_8, //D7
  PB_0, //D8
  PB_1, //D9  - TIMER_B_PWM2
  PB_2, //D10 - SPI_A_CS/ TIM_B_PWM3
  PB_5,  //D11 - SPI_A_MOSI/If JP6 ON used also for Ethernet PHY as RMII_DV
  PB_6,  //D12 - SPI_A_MISO
  PB_7,  //D13 - SPI_A_SCK
  PB_8,  //D14 - I2C_A_SDA
  PB_9,  //D15 - I2C_A_SCL
  PB_10,  //D16 - I2S_A_MCK
  PB_11, //D17 - I2S_A_SD
  PB_12, //D18 - I2S_A_CK/If JP7 ON used also for Ethernet PHY as RMII_TXD1
  PB_13, //D19 - I2S_A_WS
  PB_14, //D20 - I2S_B_WS
  PB_15,  //D21 - I2S_B_MCK
  PC_0,  //D22 - I2S_B_SD/SPI_B_MOSI
  PC_1,  //D23 - I2S_B_CK/SPI_B_SCK - SWO
  PC_2,  //D24 - SPI_B_NSS
  PC_3,  //D25 - SPI_B_MISO
  PC_4,  //D26 - QSPI_CS
  PC_5,  //D27 - QSPI_CLK
  PC_6, //D28 - QSPI_BK1_IO3
  PC_7, //D29 - QSPI_BK1_IO1
  PC_13, //D30 - QSPI_BK1_IO0
  PD_0,  //D31 - SAI_A_MCLK/QSPI_BK1_IO2
  PD_1,  //D32 - TIMER_C_PWM1
  PD_3,  //D33 - TIMER_D_PWM1 - LD1 LED_GREEN
  PD_4,  //D34 - TIMER_B_ETR
  PD_5, //D35 - TIMER_C_PWM3
  PD_6, //D36 - TIMER_C_PWM2
  PD_7, //D37 - TIMER_A_BKIN1
  PD_8, //D38
  PD_9, //D39 - TIMER_A_PWM3N
  PD_10, //D40 - TIMER_A_PWM2N
  PD_11,  //D41 - TIMER_A_ETR
  PD_12,  //D42 - TIMER_A_PWM1N
  PD_13,  //D43 - SDMMC1_D0
  PE_2,  //D44 - SDMMC1_D1/I2S_A_CKIN
  PE_3, //D45 - SDMMC1_D2
  PE_4, //D46 - SDMMC1_D3
  PE_5, //D47 - SDMMC1_CK
  PE_6,  //D48 - SDMMC1_CMD
  PE_7,  //D49
  PE_8,  //D50
  PE_9,  //D51 - USART_B_SCLK
  PE_10,  //D52 - USART_B_RX
  PE_11,  //D53 - USART_B_TX
  PE_12,  //D54 - USART_B_RTS
  PE_13,  //D55 - USART_B_CTS
  PE_14,  //D56 - SAI_A_MCLK/QSPI_BK1_IO2 - D31
  PE_15,  //D57 - SAI_A_FS
  PE_1,  //D58 - SAI_A_SCK
  PE_0  //D59 - SAI_A_SD,
  // Additional pins for LEDs
  PD_14,
  PD_15
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  /* Supply configuration update enable */
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

  /* Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) {
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Initializes the CPU, AHB and APB buses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(SystemCoreClock/1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
