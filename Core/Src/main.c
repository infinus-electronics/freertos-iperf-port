/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_IP_Private.h"
#include "NetworkBufferManagement.h"

#include "UDPLoggingPrintf.h"
#include "iperf_task.h"
#include "eventLogging.h"
#include "hr_gettime.h"
#include "tcp_mem_stats.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x30000000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x30000080
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x30000000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x30000080))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __GNUC__ ) /* GNU Compiler */

//ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
//ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
#endif

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

//TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
static TaskHandle_t xServerWorkTaskHandle = NULL;

static void vHeapInit( void );
static void vStartRandomGenerator( void );

#define mainTCP_SERVER_STACK_SIZE	640

static void MPU_Config( void );
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
//static void MX_ETH_Init(void);
//static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
const uint8_t ucMACAddress[ 6 ] = { configMAC_ADDR0, configMAC_ADDR1, configMAC_ADDR2, configMAC_ADDR3, configMAC_ADDR4, configMAC_ADDR5 };

static BaseType_t xTasksAlreadyCreated = pdFALSE;

//RNG_HandleTypeDef hrng;
static uint32_t ulSeed;

int verboseLevel = 0;

static BaseType_t xDoCreateSockets;

static void prvServerWorkTask( void *pvParameters );

static BaseType_t run_command_line( void );
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* Make the AXI memory non-cacheable */
      MPU_Config();
  /* USER CODE END 1 */

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  vHeapInit();
  vStartHighResolutionTimer();


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
//  MX_ETH_Init();
//  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  const uint8_t ucIPAddress[ 4 ] = { configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 };
  const uint8_t ucNetMask[ 4 ] = { configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3 };
  const uint8_t ucGatewayAddress[ 4 ] = { configGATEWAY_ADDR0, configGATEWAY_ADDR1, configGATEWAY_ADDR2, configGATEWAY_ADDR3 };
  const uint8_t ucDNSServerAddress[ 4 ] = { configDNS_SERVER_ADDR0, configDNS_SERVER_ADDR1, configDNS_SERVER_ADDR2, configDNS_SERVER_ADDR3 };

  FreeRTOS_printf( ( "Calling FreeRTOS_IPInit\n" ) );

  FreeRTOS_IPInit( ucIPAddress, ucNetMask, ucGatewayAddress, ucDNSServerAddress, ucMACAddress );

  xTaskCreate( prvServerWorkTask, "SvrWork", mainTCP_SERVER_STACK_SIZE, NULL, 1, &xServerWorkTaskHandle );
  /* Start the RTOS scheduler. */
  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
//static void MX_ETH_Init(void)
//{
//
//  /* USER CODE BEGIN ETH_Init 0 */
////
//  /* USER CODE END ETH_Init 0 */
//
//   static uint8_t MACAddr[6];
//
//  /* USER CODE BEGIN ETH_Init 1 */
////
//  /* USER CODE END ETH_Init 1 */
//  heth.Instance = ETH;
//  MACAddr[0] = 0x00;
//  MACAddr[1] = 0x80;
//  MACAddr[2] = 0xE1;
//  MACAddr[3] = 0x00;
//  MACAddr[4] = 0x00;
//  MACAddr[5] = 0x00;
//  heth.Init.MACAddr = &MACAddr[0];
//  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
//  heth.Init.TxDesc = DMATxDscrTab;
//  heth.Init.RxDesc = DMARxDscrTab;
//  heth.Init.RxBuffLen = 1524;
//
//  /* USER CODE BEGIN MACADDRESS */
////
//  /* USER CODE END MACADDRESS */
//
//  if (HAL_ETH_Init(&heth) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
//  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
//  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
//  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
//  /* USER CODE BEGIN ETH_Init 2 */
////
//  /* USER CODE END ETH_Init 2 */
//
//}
//
///**
//  * @brief TIM2 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_TIM2_Init(void)
//{
//
//  /* USER CODE BEGIN TIM2_Init 0 */
////
//  /* USER CODE END TIM2_Init 0 */
//
//  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//  TIM_MasterConfigTypeDef sMasterConfig = {0};
//
//  /* USER CODE BEGIN TIM2_Init 1 */
////
//  /* USER CODE END TIM2_Init 1 */
//  htim2.Instance = TIM2;
//  htim2.Init.Prescaler = 0;
//  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim2.Init.Period = 4294967295;
//  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN TIM2_Init 2 */
////
//  /* USER CODE END TIM2_Init 2 */
//
//}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_OTG_FS_PWR_EN_GPIO_Port, USB_OTG_FS_PWR_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_PWR_EN_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_PWR_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_OTG_FS_PWR_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OTG_FS_OVCR_Pin */
  GPIO_InitStruct.Pin = USB_OTG_FS_OVCR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OTG_FS_OVCR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
 * RAM area	H747	H743	H742	Location
 * ------------------------------------------------
 * DTCM		128k	128k	128k	0x20000000
 * AXI-SRAM	511k	511k	384k	0x24000000
 *
 * SRAM1	128k	128k	32k		0x30000000
 * SRAM2	128k	128k	16k		0x30020000
 * SRAM3	32k		32k	 	-		0x30040000
 * SRAM4	64k		64k		64k		0x38000000
 * Backup   SRAM	4k		4k	4k	0x38800000
 */

static uint8_t ucRAM_1 [384 * 1024] __attribute__( ( section( ".ethernet_data" ) ) );
//static uint8_t ucRAM_2 [128 * 1024] __attribute__( ( section( ".ram2_data" ) ) );
static uint8_t ucRAM_3 [ 64 * 1024] __attribute__( ( section( ".ram3_data" ) ) );

#define mainMEM_REGION( REGION )   REGION, sizeof( REGION )

static void vHeapInit( )
{
	/* Note: the memories must be sorted on their physical address. */
	HeapRegion_t xHeapRegions[] = {
		{ mainMEM_REGION( ucRAM_1 ) },
//		{ mainMEM_REGION( ucRAM_2 ) },
		{ mainMEM_REGION( ucRAM_3 ) },
		{ NULL, 0 }
		};

	vPortDefineHeapRegions( xHeapRegions );
}
/*-----------------------------------------------------------*/

//static void vStartRandomGenerator( void )
//{
//	/* Enable the clock for the RNG. */
//	__HAL_RCC_RNG_CLK_ENABLE();
//	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
//	RNG->CR |= RNG_CR_RNGEN;
//
//	hrng.Instance = RNG;
//	hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
//	if (HAL_RNG_Init(&hrng) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/* Get random numbers. */
//	HAL_RNG_GenerateRandomNumber( &hrng, &ulSeed );
//}
/*-----------------------------------------------------------*/

uint32_t ulGetRunTimeCounterValue()
{
	return 0U;
}

void vAssertCalled( const char *pcFile, uint32_t ulLine )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	taskENTER_CRITICAL();
	{
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			__NOP();
		}
	}
	taskEXIT_CRITICAL();
}

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

	/* Force an assert. */
	configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

//int lUDPLoggingPrintf( const char *pcFormatString, ... )
//{
//	( void ) pcFormatString;
//	return 0;
//

uint32_t ulApplicationGetNextSequenceNumber(
    uint32_t ulSourceAddress,
    uint16_t usSourcePort,
    uint32_t ulDestinationAddress,
    uint16_t usDestinationPort )
{
	uint32_t ulReturn;
	( void ) ulSourceAddress;
	( void ) usSourcePort;
	( void ) ulDestinationAddress;
	( void ) usDestinationPort;
	xApplicationGetRandomNumber( &ulReturn );

	return ulReturn;
}

void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
	/* If the network has just come up...*/
	if( eNetworkEvent == eNetworkUp )
	{
	uint32_t ulIPAddress, ulNetMask, ulGatewayAddress, ulDNSServerAddress;
	char cBuffer[ 16 ];

		/* Create the tasks that use the IP stack if they have not already been
		created. */
		if( xTasksAlreadyCreated == pdFALSE )
		{
			xTasksAlreadyCreated = pdTRUE;
			/* Sockets, and tasks that use the TCP/IP stack can be created here. */
			xDoCreateSockets = pdTRUE;
		}
		/* Print out the network configuration, which may have come from a DHCP
		server. */
		FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
		FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );
		FreeRTOS_printf( ( "IP Address: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulNetMask, cBuffer );
		FreeRTOS_printf( ( "Subnet Mask: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulGatewayAddress, cBuffer );
		FreeRTOS_printf( ( "Gateway Address: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulDNSServerAddress, cBuffer );
		FreeRTOS_printf( ( "DNS Server Address: %s\n", cBuffer ) );
	}
}
/*-----------------------------------------------------------*/

BaseType_t xApplicationDNSQueryHook( const char *pcName )
{
	BaseType_t xReturn = pdFAIL;

	/* Determine if a name lookup is for this node.  Two names are given
	to this node: that returned by pcApplicationHostnameHook() and that set
	by mainDEVICE_NICK_NAME. */
	if( strcasecmp( pcName, pcApplicationHostnameHook() ) == 0 )
	{
		xReturn = pdPASS;
	}
	return xReturn;
}
/*-----------------------------------------------------------*/

const char *pcApplicationHostnameHook( void )
{
	/* Assign the name "STM32H7" to this network node.  This function will be
	called during the DHCP: the machine will be registered with an IP address
	plus this name. */
	return "STM32H7";
}
/*-----------------------------------------------------------*/

BaseType_t xApplicationGetRandomNumber( uint32_t *pulNumber ){
	*pulNumber = rand();
	return pdTRUE;
}
/*-----------------------------------------------------------*/

struct xREGISTER_STACK {
	uint32_t spare0[ 8 ];
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r12;
	uint32_t lr; /* Link register. */
	uint32_t pc; /* Program counter. */
	uint32_t psr;/* Program status register. */
	uint32_t spare1[ 8 ];
};

volatile struct xREGISTER_STACK *pxRegisterStack = NULL;

void prvGetRegistersFromStack( uint32_t * pulFaultStackAddress )
{
	/* When the debuggger stops here, you can inspect the registeers of the
	application by looking at *pxRegisterStack. */
	pxRegisterStack = ( volatile struct xREGISTER_STACK * )
		( pulFaultStackAddress - ARRAY_SIZE( pxRegisterStack->spare0 ) );

	/* When the following line is hit, the variables contain the register values. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void HardFault_Handler(void)
{
	__asm volatile
	(
		" tst lr, #4                                                \n"
		" ite eq                                                    \n"
		" mrseq r0, msp                                             \n"
		" mrsne r0, psp                                             \n"
		" ldr r1, [r0, #24]                                         \n"
		" bl prvGetRegistersFromStack                               \n"
	);
}
/*-----------------------------------------------------------*/

#define CONTINUOUS_PING	0

static void prvServerWorkTask( void *pvParameters )
{
#if( CONTINUOUS_PING != 0 )
	/* CONTINUOUS_PING can be used while testing the network driver. */
	uint32_t ulIPAddress = FreeRTOS_inet_addr_quick( 192, 168, 2, 5 );
	size_t uxNumberOfBytesToSend = 16;
	TickType_t uxBlockTimeTicks = ipMS_TO_MIN_TICKS( 100U );
#endif	/* ( CONTINUOUS_PING != 0 ) */

	for( ;; )
	{
		vTaskDelay( 10U );
		if( xDoCreateSockets != pdFALSE )
		{
			xDoCreateSockets = pdFALSE;
			/* Start a new task to fetch logging lines and send them out.
			See FreeRTOSConfig.h for the configuration of UDP logging. */
			vUDPLoggingTaskCreate();
			vIPerfInstall();
			#if( USE_LOG_EVENT != 0 )
			{
				iEventLogInit();
			}
			#endif
		}

		#if( CONTINUOUS_PING != 0 )
		{
			if( xTasksAlreadyCreated != pdFALSE )
			{
				FreeRTOS_SendPingRequest( ulIPAddress, uxNumberOfBytesToSend, uxBlockTimeTicks );
			}
		}
		#endif

		run_command_line();
	}
}

#define USE_ZERO_COPY  1

#include "hr_gettime.h"

static BaseType_t run_command_line()
{
char  pcBuffer[ 92 ];
BaseType_t xCount;
struct freertos_sockaddr xSourceAddress;
socklen_t xSourceAddressLength = sizeof( xSourceAddress );
xSocket_t xSocket = xLoggingGetSocket();
static NetworkBufferDescriptor_t *pxDescriptor = NULL;

	if( xSocket == NULL )
	{
		return 0;
	}

	#if( USE_ZERO_COPY )
	{
		if( pxDescriptor != NULL )
		{
			vReleaseNetworkBufferAndDescriptor( pxDescriptor );
			pxDescriptor = NULL;
		}
		char  *ppcBuffer;
		xCount = FreeRTOS_recvfrom( xSocket, ( void * )&ppcBuffer, sizeof( pcBuffer ) - 1, FREERTOS_MSG_DONTWAIT | FREERTOS_ZERO_COPY, &xSourceAddress, &xSourceAddressLength );
		if( xCount > 0 )
		{
			if( ( ( size_t ) xCount ) > ( sizeof pcBuffer - 1 ) )
			{
				xCount = ( BaseType_t ) ( sizeof pcBuffer - 1 );
			}
			memcpy( pcBuffer, ppcBuffer, xCount );
			pcBuffer[ xCount ] = '\0';
			pxDescriptor = pxUDPPayloadBuffer_to_NetworkBuffer( ( const void * ) ppcBuffer );
		}
	}
	#else
	{
		xCount = FreeRTOS_recvfrom( xSocket, ( void * ) pcBuffer, sizeof( pcBuffer ) - 1, FREERTOS_MSG_DONTWAIT,
			&xSourceAddress, &xSourceAddressLength );
	}
	#endif
	if( xCount <= 0 )
	{
		return 0;
	}
	pcBuffer[ xCount ] = 0;
	if( strncmp( pcBuffer, "ver", 4 ) == 0 )
	{
		lUDPLoggingPrintf( "Verbose level %d\n", verboseLevel );
		lUDPLoggingPrintf( "CPU sped %lu\n", configCPU_CLOCK_HZ );
	}
	else if( strncmp( pcBuffer, "hrtime", 6 ) == 0 )
	{
		static uint64_t lastTime = 0ULL;
		uint64_t curTime = ullGetHighResolutionTime();
		uint32_t difTime = ( uint32_t ) ( ( curTime - lastTime ) / 1000U );

		static TickType_t ulLastTime = 0U;
		TickType_t ulCurTime = xTaskGetTickCount();
		TickType_t ulDifTime = ulCurTime - ulLastTime;

		lUDPLoggingPrintf( "hr_time %lu  FreeRTOS %u\n",
			( uint32_t ) difTime,
			( uint32_t ) ulDifTime );
		lastTime = curTime;
		ulLastTime = ulCurTime;
	}
	else if( memcmp( pcBuffer, "random", 6 ) == 0 )
	{
	uint32_t ulFrequencies[ 32 ];
	uint32_t ulCount;
	uint32_t ulIndex;
	uint32_t ulValue;

		memset( ulFrequencies, 0, sizeof ulFrequencies );
		for( ulCount = 0U; ulCount < 20000; ulCount++ )
		{
			ulValue = rand();
			for( ulIndex = 0; ulIndex < ARRAY_SIZE( ulFrequencies ); ulIndex++ )
			{
				if( ( ulValue & 0x80000000U ) != 0 )
				{
					ulFrequencies[ ulIndex ]++;
				}
				ulValue <<= 1;
			}
		}
		for( ulIndex = 0; ulIndex < ARRAY_SIZE( ulFrequencies ); ulIndex += 8 )
		{
				/* Expected: +/- 10000  10000  10000  10000  10000  10000  */
			FreeRTOS_printf( ( "%2d - %2d : %6u %6u %6u %6u %6u %6u %6u %6u\n",
				ulIndex, ulIndex+7,
				ulFrequencies[ ulIndex + 0 ],
				ulFrequencies[ ulIndex + 1 ],
				ulFrequencies[ ulIndex + 2 ],
				ulFrequencies[ ulIndex + 3 ],
				ulFrequencies[ ulIndex + 4 ],
				ulFrequencies[ ulIndex + 5 ],
				ulFrequencies[ ulIndex + 6 ],
				ulFrequencies[ ulIndex + 7 ] ) );
		}
		FreeRTOS_printf( ( "\n" ) );
	}
#if ( USE_IPERF != 0 )
    else if( strncmp( pcBuffer, "iperf", 5 ) == 0 )
    {
        FreeRTOS_printf( ( "iperf is already installed.\n" ) );
    }
#endif /* ( USE_IPERF != 0 ) */
	else if( memcmp( pcBuffer, "mem", 3 ) == 0 )
	{
		uint32_t now = xPortGetFreeHeapSize( );
		uint32_t total = 0;//xPortGetOrigHeapSize( );
		uint32_t perc = total ? ( ( 100 * now ) / total ) : 100;
		lUDPLoggingPrintf("mem Low %u, Current %lu / %lu (%lu perc free)\n",
			xPortGetMinimumEverFreeHeapSize( ),
			now, total, perc );
	}
#if( USE_LOG_EVENT != 0 )
	else if( strncmp( pcBuffer, "event", 4 ) == 0 )
	{
		if(pcBuffer[ 5 ] == 'c')
		{
			int rc = iEventLogClear();
			lUDPLoggingPrintf( "cleared %d events\n", rc );
		}
		else
		{
			eventLogDump();
		}
	}
#endif /* USE_LOG_EVENT */
	else
	{
		FreeRTOS_printf( ( "Don't know: %s\n", pcBuffer ) );
	}
	return xCount;
}

#if ( ipconfigSUPPORT_OUTGOING_PINGS == 1 )
	void vApplicationPingReplyHook( ePingReplyStatus_t eStatus, uint16_t usIdentifier )
	{
		FreeRTOS_printf( ( "Received ping ID %04X\n", usIdentifier ) );
	}
#endif
/*-----------------------------------------------------------*/

static void MPU_Config( void )
{
    MPU_Region_InitTypeDef MPU_InitStruct;

    /*  Prohibit MPU */
    HAL_MPU_Disable();

    /*  Configure the MPU attributes of AXI SRAM as Write back, Read allocate, Write allocate */
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0x24000000;               // AXI memory where ETH descriptors and buffers are stored
    MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE; // MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;	 // MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_SHAREABLE; // MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /*Enable MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  Retargets the C library printf function to the USART.
  *   None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

//Example vApplicationIPNetworkEventHook() definition

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer,
		uint32_t *pulIdleTaskStackSize )
{
	/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
    state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task’s stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*———————————————————–*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
		StackType_t **ppxTimerTaskStackBuffer,
		uint32_t *pulTimerTaskStackSize )
{
	/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
    task’s state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task’s stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

//Examples of the callback functions that must be provided by the application to
//
//supply the RAM used by the Idle and Timer Service tasks if configSUPPORT_STATIC_ALLOCATION
//
//is set to 1.

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
