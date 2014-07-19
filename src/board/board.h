/*
  ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for ST STM32L-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_STM32L_DISCOVERY
#define BOARD_NAME                  "Elfe"


/*
 * Board oscillators-related settings.
 * NOTE: HSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                0
#endif

#define STM32_HSE_BYPASS

/*
 * MCU type as defined in the ST header file stm32l1xx.h.
 */
#define STM32L1XX_MD

/*
 * IO pins assignments.
 */

#define GPIOA_ADC                   0  // Luminosity sensor
#define GPIOA_PIN1                  1
#define GPIOA_UV_SMALL              2  // LED UV 1 -> TIM2_CH3
#define GPIOA_UV_BIG                3  // LED UV 2 -> TIM2_CH4
#define GPIOA_PIN4                  4
#define GPIOA_PIN5                  5
#define GPIOA_PIN6                  6
#define GPIOA_RGB_BIG_G             7  // LED RGB Big Eye, green -> TIM3_CH2
#define GPIOA_PIN8                  8
#define GPIOA_PIN9                  9
#define GPIOA_PIN10                 10
#define GPIOA_PIN11                 11
#define GPIOA_RF_IRQ                12 // nRF IRQ (entrée)
#define GPIOA_SWDAT                 13
#define GPIOA_SWCLK                 14
#define GPIOA_RGB_SMALL_B           15 // LED RGB Small Eye, blue -> TIM2_CH1_ETR

#define GPIOB_RGB_BIG_B             0  // LED RGB Big Eye, blue -> TIM3_CH3
#define GPIOB_RGB_BIG_R             1  // LED RGB Big Eye, red -> TIM3_CH4
#define GPIOB_BOOT1                 2
#define GPIOB_RGB_SMALL_G           3  // LED RGB Small Eye, green -> TIM2_CH2
#define GPIOB_RGB_SMALL_R           4  // LED RGB Small Eye, red -> TIM3_CH1
#define GPIOB_PIN5                  5
#define GPIOB_DEBUG_TX              6  // Debug -> USART1_TX
#define GPIOB_DEBUG_RX              7  // Debug -> USART1_RX
#define GPIOB_PIN8                  8
#define GPIOB_PIN9                  9
#define GPIOB_PIN10                 10
#define GPIOB_RF_CE                 11 // nRF CE (sortie)
#define GPIOB_RF_NSS                12 // nRF NSS -> SPI2_NSS
#define GPIOB_RF_SCK                13 // nRF clock -> SPI2_SCK
#define GPIOB_RF_MISO               14 // nRF MISO -> SPI2_MISO
#define GPIOB_RF_MOSI               15 // nRF MOSI -> SPI2_MOSI

#define GPIOC_PIN0                  0
#define GPIOC_PIN1                  1
#define GPIOC_PIN2                  2
#define GPIOC_PIN3                  3
#define GPIOC_PIN4                  4
#define GPIOC_PIN5                  5
#define GPIOC_PIN6                  6
#define GPIOC_PIN7                  7
#define GPIOC_PIN8                  8
#define GPIOC_PIN9                  9
#define GPIOC_PIN10                 10
#define GPIOC_PIN11                 11
#define GPIOC_PIN12                 12
#define GPIOC_PROXSENSOR            13 // Proximity Sensor -> WKUP2
#define GPIOC_OSC32_IN              14
#define GPIOC_OSC32_OUT             15

#define GPIOD_PIN0                  0
#define GPIOD_PIN1                  1
#define GPIOD_PIN2                  2
#define GPIOD_PIN3                  3
#define GPIOD_PIN4                  4
#define GPIOD_PIN5                  5
#define GPIOD_PIN6                  6
#define GPIOD_PIN7                  7
#define GPIOD_PIN8                  8
#define GPIOD_PIN9                  9
#define GPIOD_PIN10                 10
#define GPIOD_PIN11                 11
#define GPIOD_PIN12                 12
#define GPIOD_PIN13                 13
#define GPIOD_PIN14                 14
#define GPIOD_PIN15                 15

#define GPIOE_PIN0                  0
#define GPIOE_PIN1                  1
#define GPIOE_PIN2                  2
#define GPIOE_PIN3                  3
#define GPIOE_PIN4                  4
#define GPIOE_PIN5                  5
#define GPIOE_PIN6                  6
#define GPIOE_PIN7                  7
#define GPIOE_PIN8                  8
#define GPIOE_PIN9                  9
#define GPIOE_PIN10                 10
#define GPIOE_PIN11                 11
#define GPIOE_PIN12                 12
#define GPIOE_PIN13                 13
#define GPIOE_PIN14                 14
#define GPIOE_PIN15                 15

#define GPIOF_PIN0                  0
#define GPIOF_PIN1                  1
#define GPIOF_PIN2                  2
#define GPIOF_PIN3                  3
#define GPIOF_PIN4                  4
#define GPIOF_PIN5                  5
#define GPIOF_PIN6                  6
#define GPIOF_PIN7                  7
#define GPIOF_PIN8                  8
#define GPIOF_PIN9                  9
#define GPIOF_PIN10                 10
#define GPIOF_PIN11                 11
#define GPIOF_PIN12                 12
#define GPIOF_PIN13                 13
#define GPIOF_PIN14                 14
#define GPIOF_PIN15                 15

#define GPIOH_OSC_IN                0
#define GPIOH_OSC_OUT               1
#define GPIOH_PIN2                  2
#define GPIOH_PIN3                  3
#define GPIOH_PIN4                  4
#define GPIOH_PIN5                  5
#define GPIOH_PIN6                  6
#define GPIOH_PIN7                  7
#define GPIOH_PIN8                  8
#define GPIOH_PIN9                  9
#define GPIOH_PIN10                 10
#define GPIOH_PIN11                 11
#define GPIOH_PIN12                 12
#define GPIOH_PIN13                 13
#define GPIOH_PIN14                 14
#define GPIOH_PIN15                 15
/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_400K(n)          (0U << ((n) * 2))
#define PIN_OSPEED_2M(n)            (1U << ((n) * 2))
#define PIN_OSPEED_10M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

/* By default, the setup will be "input pulldown" in order to save power and to avoid short  */
/*
 * GPIOA setup:
 *
 * PA0  - ADC IN0                   (anolog input)
 * PA1  -
 * PA2  - UV_SMAL                   (alternate 1 -> Timer ; pushpull).
 * PA3  - UV_BIG                    (alternate 1 -> Timer ; pushpull).
 * PA4  -
 * PA5  -
 * PA6  -
 * PA7  - RGB_BIG_G                  (alternate 1 -> Timer ; pushpull).
 * PA8  -
 * PA9  -
 * PA10 -
 * PA11 -
 * PA12 - RF_IRQ                     (input pullup high).
 * PA13 - SWDAT                      (IO pull-up).
 * PA14 - SWDCLK                     (input pulldown).
 * PA15 - RGB_SMALL_B                (alternate 1 -> Timer ; pushpull).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_ADC) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_UV_SMALL) | \
                                     PIN_MODE_ALTERNATE(GPIOA_UV_BIG)   | \
                                     PIN_MODE_INPUT(GPIOA_PIN4) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN5) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN6) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_RGB_BIG_G) | \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN9) |       \
                                     PIN_MODE_INPUT(GPIOA_PIN10) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN11) |      \
                                     PIN_MODE_INPUT(GPIOA_RF_IRQ) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDAT) | \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) | \
                                     PIN_MODE_ALTERNATE(GPIOA_RGB_SMALL_B))

#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_ADC) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UV_SMALL) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UV_BIG) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RGB_BIG_G) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RF_IRQ) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDAT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RGB_SMALL_B))

#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_400K(GPIOA_ADC) |       \
                                     PIN_OSPEED_400K(GPIOA_PIN1) |      \
                                     PIN_OSPEED_40M(GPIOA_UV_SMALL) |  \
                                     PIN_OSPEED_40M(GPIOA_UV_BIG) |    \
                                     PIN_OSPEED_400K(GPIOA_PIN4) |      \
                                     PIN_OSPEED_400K(GPIOA_PIN5) |      \
                                     PIN_OSPEED_400K(GPIOA_PIN6) |      \
                                     PIN_OSPEED_40M(GPIOA_RGB_BIG_G) | \
                                     PIN_OSPEED_400K(GPIOA_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOA_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOA_PIN10) |     \
                                     PIN_OSPEED_400K(GPIOA_PIN11) |     \
                                     PIN_OSPEED_400K(GPIOA_RF_IRQ) |    \
                                     PIN_OSPEED_40M(GPIOA_SWDAT) |      \
                                     PIN_OSPEED_40M(GPIOA_SWCLK) |      \
                                     PIN_OSPEED_40M(GPIOA_RGB_SMALL_B))

#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOA_ADC) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN1) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_UV_SMALL) | \
                                     PIN_PUPDR_PULLDOWN(GPIOA_UV_BIG) | \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN4) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN6) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_RGB_BIG_G) | \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN11) |  \
                                     PIN_PUPDR_PULLUP(GPIOA_RF_IRQ) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDAT) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_RGB_SMALL_B))

#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_ADC) |          \
                                     PIN_ODR_HIGH(GPIOA_PIN1) |         \
                                     PIN_ODR_HIGH(GPIOA_UV_SMALL) |     \
                                     PIN_ODR_HIGH(GPIOA_UV_BIG) |       \
                                     PIN_ODR_HIGH(GPIOA_PIN4) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN6) |         \
                                     PIN_ODR_HIGH(GPIOA_RGB_BIG_G) |    \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOA_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOA_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOA_RF_IRQ) |       \
                                     PIN_ODR_HIGH(GPIOA_SWDAT) |     \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |     \
                                     PIN_ODR_HIGH(GPIOA_RGB_SMALL_B))

#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_UV_SMALL, 1) |   \
                                     PIN_AFIO_AF(GPIOA_UV_BIG, 1) |     \
                                     PIN_AFIO_AF(GPIOA_RGB_BIG_G, 2))

#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_SWDAT, 0) |   \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |   \
                                     PIN_AFIO_AF(GPIOA_RGB_SMALL_B, 1))

/*
 * GPIOB setup:
 *
 * PB0  - RGB_BIG_B                  (alternate 2 -> Timer 3; pushpull).
 * PB1  - RGB_BIG_R                  (alternate 2 -> Timer 3; pushpull).
 * PB2  -
 * PB3  - RGB_SMALL_G                (alternate 1 -> Timer 2; pushpull).
 * PB4  - RGB_SMALL_R                (alternate 2 -> Timer 3; pushpull).
 * PB5  -
 * PB5  -
 * PB6  - DEBUG_TX                   (alternate 7 -> USART ; pushpull).
 * PB7  - DEBUG_RX                   (alternate 7 -> USART ; input).
 * PB8  -
 * PB9  -
 * PB10 -
 * PB11 - RF_CE                      (output pushpull pullup)
 * PB12 - RF_NSS                     (ouput pushpull pullup).
 * PB13 - RF_SCK                     (alternate 5 -> SPI ; pushpull).
 * PB14 - RF_MISO                    (alternate 5 -> SPI ; input).
 * PB15 - RF_MOSI                    (alternate 5 -> SPI ; pushpull).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_RGB_BIG_B) | \
                                     PIN_MODE_ALTERNATE(GPIOB_RGB_BIG_R) | \
                                     PIN_MODE_INPUT(GPIOB_BOOT1) |      \
                                     PIN_MODE_ALTERNATE(GPIOB_RGB_SMALL_G) | \
                                     PIN_MODE_ALTERNATE(GPIOB_RGB_SMALL_R) | \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_DEBUG_TX) | \
                                     PIN_MODE_INPUT(GPIOB_DEBUG_RX) |   \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |       \
                                     PIN_MODE_INPUT(GPIOB_PIN9) |       \
                                     PIN_MODE_INPUT(GPIOB_PIN10) |      \
                                     PIN_MODE_OUTPUT(GPIOB_RF_CE) |     \
                                     PIN_MODE_OUTPUT(GPIOB_RF_NSS) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_RF_SCK) | \
                                     PIN_MODE_ALTERNATE(GPIOB_RF_MISO) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_RF_MOSI))

#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_RGB_BIG_B) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RGB_BIG_R) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BOOT1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RGB_SMALL_G) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RGB_SMALL_R) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_DEBUG_TX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_DEBUG_RX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RF_CE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RF_NSS) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RF_SCK) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RF_MISO) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_RF_MOSI))

#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_40M(GPIOB_RGB_BIG_B) | \
                                     PIN_OSPEED_40M(GPIOB_RGB_BIG_R) | \
                                     PIN_OSPEED_400K(GPIOB_BOOT1) |     \
                                     PIN_OSPEED_40M(GPIOB_RGB_SMALL_G) | \
                                     PIN_OSPEED_40M(GPIOB_RGB_SMALL_R) | \
                                     PIN_OSPEED_400K(GPIOB_PIN5) |      \
                                     PIN_OSPEED_2M(GPIOB_DEBUG_TX) |  \
                                     PIN_OSPEED_2M(GPIOB_DEBUG_RX) |  \
                                     PIN_OSPEED_400K(GPIOB_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOB_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOB_PIN10) |     \
                                     PIN_OSPEED_10M(GPIOB_RF_CE) |     \
                                     PIN_OSPEED_10M(GPIOB_RF_NSS) |    \
                                     PIN_OSPEED_10M(GPIOB_RF_SCK) |    \
                                     PIN_OSPEED_10M(GPIOB_RF_MISO) |   \
                                     PIN_OSPEED_10M(GPIOB_RF_MOSI))

#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_RGB_BIG_B) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_RGB_BIG_R) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_BOOT1) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOB_RGB_SMALL_G) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_RGB_SMALL_R) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOB_DEBUG_TX) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_DEBUG_RX) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN10) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_RF_CE) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_RF_NSS) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_RF_SCK) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_RF_MISO) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_RF_MOSI))

#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_RGB_BIG_B) |    \
                                     PIN_ODR_HIGH(GPIOB_RGB_BIG_R) |    \
                                     PIN_ODR_HIGH(GPIOB_BOOT1) |        \
                                     PIN_ODR_HIGH(GPIOB_RGB_SMALL_G) |  \
                                     PIN_ODR_HIGH(GPIOB_RGB_SMALL_R) |  \
                                     PIN_ODR_HIGH(GPIOB_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOB_DEBUG_TX) |     \
                                     PIN_ODR_HIGH(GPIOB_DEBUG_RX) |     \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOB_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOB_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOB_RF_CE) |        \
                                     PIN_ODR_HIGH(GPIOB_RF_NSS) |       \
                                     PIN_ODR_HIGH(GPIOB_RF_SCK) |       \
                                     PIN_ODR_HIGH(GPIOB_RF_MISO) |      \
                                     PIN_ODR_HIGH(GPIOB_RF_MOSI))

#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_RGB_BIG_B, 2) |  \
                                     PIN_AFIO_AF(GPIOB_RGB_BIG_R, 2) |  \
                                     PIN_AFIO_AF(GPIOB_RGB_SMALL_G, 1) | \
                                     PIN_AFIO_AF(GPIOB_RGB_SMALL_R, 2) | \
                                     PIN_AFIO_AF(GPIOB_DEBUG_TX, 7) |   \
                                     PIN_AFIO_AF(GPIOB_DEBUG_RX, 7))

#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_RF_SCK, 5) |     \
                                     PIN_AFIO_AF(GPIOB_RF_MISO, 5) |    \
                                     PIN_AFIO_AF(GPIOB_RF_MOSI, 5))

/*
 * GPIOC setup:
 *
 * PC0  -
 * PC1  -
 * PC2  -
 * PC3  -
 * PC4  -
 * PC5  -
 * PC6  -
 * PC7  -
 * PC8  -
 * PC9  -
 * PC10 -
 * PC11 -
 * PC12 -
 * PC13 - PROXSENSOR                (alternate 0 -> WAKE UP ; pulldown).
 * PC14 -
 * PC15 -
 */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_PIN0) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN1) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN3) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN7) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN10) |      \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |      \
                                     PIN_MODE_INPUT(GPIOC_PIN12) |      \
                                     PIN_MODE_INPUT(GPIOC_PROXSENSOR) | \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |   \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))

#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PROXSENSOR) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_400K(GPIOC_PIN0) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN1) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN2) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN3) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN4) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN5) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN6) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN7) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOC_PIN10) |     \
                                     PIN_OSPEED_400K(GPIOC_PIN11) |     \
                                     PIN_OSPEED_400K(GPIOC_PIN12) |     \
                                     PIN_OSPEED_400K(GPIOC_PROXSENSOR) | \
                                     PIN_OSPEED_400K(GPIOC_OSC32_IN) |  \
                                     PIN_OSPEED_400K(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOC_PIN0) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN1) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN2) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN3) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN4) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN6) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN7) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN11) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN12) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PROXSENSOR) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_OSC32_IN) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOC_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOC_PIN12) |        \
                                     PIN_ODR_HIGH(GPIOC_PROXSENSOR) |   \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |     \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0) |   \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0))
#define VAL_GPIOC_AFRH              (0)

/*
 * GPIOD setup:
 *
 * PD0  - PIN0
 * PD1  - PIN1
 * PD2  - PIN2
 * PD3  - PIN3
 * PD4  - PIN4
 * PD5  - PIN5
 * PD6  - PIN6
 * PD7  - PIN7
 * PD8  - PIN8
 * PD9  - PIN9
 * PD10 - PIN10
 * PD11 - PIN11
 * PD12 - PIN12
 * PD13 - PIN13
 * PD14 - PIN14
 * PD15 - PIN15
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |  \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_400K(GPIOD_PIN0) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN1) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN2) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN3) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN4) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN5) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN6) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN7) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOD_PIN10) |     \
                                     PIN_OSPEED_400K(GPIOD_PIN11) |     \
                                     PIN_OSPEED_400K(GPIOD_PIN12) |     \
                                     PIN_OSPEED_400K(GPIOD_PIN13) |     \
                                     PIN_OSPEED_400K(GPIOD_PIN14) |     \
                                     PIN_OSPEED_400K(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOD_PIN0) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN1) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN2) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN3) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN4) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN6) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN7) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN11) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN12) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN13) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN14) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |  \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |  \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0) |  \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0) |  \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0) |  \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - PIN2                      (input pullup).
 * PE3  - PIN3                      (input pullup).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - PIN7                      (input pullup).
 * PE8  - PIN8                      (input pullup).
 * PE9  - PIN9                      (input pullup).
 * PE10 - PIN10                     (input pullup).
 * PE11 - PIN11                     (input pullup).
 * PE12 - PIN12                     (input pullup).
 * PE13 - PIN13                     (input pullup).
 * PE14 - PIN14                     (input pullup).
 * PE15 - PIN15                     (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN3) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |   \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |  \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_400K(GPIOE_PIN0) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN1) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN2) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN3) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN4) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN5) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN6) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN7) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOE_PIN10) |     \
                                     PIN_OSPEED_400K(GPIOE_PIN11) |     \
                                     PIN_OSPEED_400K(GPIOE_PIN12) |     \
                                     PIN_OSPEED_400K(GPIOE_PIN13) |     \
                                     PIN_OSPEED_400K(GPIOE_PIN14) |     \
                                     PIN_OSPEED_400K(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOE_PIN0) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN1) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN2) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN3) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN4) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN6) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN7) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN11) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN12) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN13) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN14) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |        \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0) |   \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0) |  \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |     \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |    \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |       \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |      \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |      \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |      \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |      \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |      \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_400K(GPIOH_OSC_IN) |    \
                                     PIN_OSPEED_400K(GPIOH_OSC_OUT) |   \
                                     PIN_OSPEED_400K(GPIOH_PIN2) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN3) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN4) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN5) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN6) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN7) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN8) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN9) |      \
                                     PIN_OSPEED_400K(GPIOH_PIN10) |     \
                                     PIN_OSPEED_400K(GPIOH_PIN11) |     \
                                     PIN_OSPEED_400K(GPIOH_PIN12) |     \
                                     PIN_OSPEED_400K(GPIOH_PIN13) |     \
                                     PIN_OSPEED_400K(GPIOH_PIN14) |     \
                                     PIN_OSPEED_400K(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) | \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) | \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN2) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN3) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN4) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN5) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN6) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN7) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN8) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN9) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN10) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN11) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN12) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN13) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN14) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |       \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |      \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |         \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |        \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |        \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |        \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |        \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |        \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0) |     \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0) |    \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0) |       \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0) |       \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0) |       \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0) |       \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0) |       \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0) |   \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0) |   \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0) |  \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0) |  \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0) |  \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0) |  \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0) |  \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
