/*
 *@Note
 PWM output routine:
 TIM1_CH1(PD2)
 This example demonstrates that the TIM_CH1(PD2) pin outputs PWM in PWM mode 1
 and PWM mode 2.

 */

#include "debug.h"

/* PWM Output Mode Definition */
#define PWM_MODE1   0
#define PWM_MODE2

/* PWM Output Mode Selection */
#define PWM_MODE PWM_MODE1
//#define PWM_MODE PWM_MODE2

const uint16_t tonedata[] = { 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62,
        65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156,
        165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349,
        370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784,
        831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568,
        1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136,
        3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272,
        6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840,
        12544, 13290, 14080, 14917, 15804, 16744, 17740, 18795, 19912, 21096,
        22351, 23680, 25088, 26580, 28160, 29834, 31609, 33488, 35479, 37589,
        39824, 42192, 44701, 47359, 50175 };

const uint8_t notes[] = { 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56,
        0, 55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0,
        60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 58, 0, 58, 0, 58, 0, 58, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0,
        55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0,
        60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0,
        58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 37, 55, 37,
        55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37, 60, 44, 60, 53, 60, 44,
        60, 53, 58, 44, 58, 53, 58, 44, 58, 0, 55, 44, 55, 53, 55, 44, 55, 53,
        56, 44, 56, 53, 56, 44, 56, 53, 60, 41, 60, 41, 60, 41, 60, 41, 58, 41,
        58, 41, 58, 41, 58, 41, 55, 44, 55, 53, 55, 44, 55, 53, 56, 44, 56, 53,
        56, 44, 56, 0, 60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44,
        58, 53, 55, 37, 55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37,
        60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58, 0, 55, 44,
        55, 53, 55, 44, 55, 53, 56, 44, 56, 53, 56, 44, 56, 53, 58, 41, 58, 41,
        58, 41, 58, 41, 60, 41, 60, 41, 60, 41, 60, 41, 61, 44, 61, 53, 61, 44,
        61, 53, 63, 44, 63, 53, 63, 44, 63, 0, 65, 44, 65, 53, 65, 44, 65, 53,
        66, 44, 66, 53, 66, 44, 66, 53, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32,
        70, 32, 70, 32, 70, 32, 70, 44, 70, 54, 70, 44, 70, 54, 68, 44, 68, 54,
        68, 44, 68, 0, 66, 44, 66, 54, 66, 44, 66, 54, 65, 44, 65, 54, 65, 44,
        0, 54, 65, 39, 65, 39, 65, 39, 65, 39, 63, 39, 63, 39, 63, 39, 0, 39,
        63, 44, 63, 54, 63, 44, 63, 54, 62, 44, 62, 54, 62, 44, 62, 0, 63, 44,
        63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 70, 32, 70, 32,
        70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 48, 70, 54, 70, 48,
        70, 54, 68, 48, 68, 54, 68, 48, 68, 0, 66, 48, 66, 54, 66, 48, 66, 54,
        65, 48, 65, 54, 65, 48, 0, 54, 65, 44, 65, 44, 65, 44, 65, 44, 63, 44,
        63, 44, 63, 44, 63, 44, 62, 48, 62, 54, 62, 48, 62, 54, 63, 48, 63, 54,
        63, 48, 63, 0, 65, 48, 65, 54, 65, 48, 65, 54, 58, 48, 58, 54, 58, 48,
        58, 54, 55, 37, 55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37,
        60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58, 0, 55, 44,
        55, 53, 55, 44, 55, 53, 56, 44, 56, 53, 56, 44, 56, 53, 60, 41, 60, 41,
        60, 41, 60, 41, 58, 41, 58, 41, 58, 41, 58, 41, 55, 44, 55, 53, 55, 44,
        55, 53, 56, 44, 56, 53, 56, 44, 56, 0, 60, 44, 60, 53, 60, 44, 60, 53,
        58, 44, 58, 53, 58, 44, 58, 53, 55, 37, 55, 37, 55, 37, 55, 37, 56, 37,
        56, 37, 56, 37, 56, 37, 60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53,
        58, 44, 58, 0, 55, 44, 55, 53, 55, 44, 55, 53, 56, 44, 56, 53, 56, 44,
        56, 53, 58, 41, 58, 41, 58, 41, 58, 41, 60, 41, 60, 41, 60, 41, 60, 41,
        61, 44, 61, 53, 61, 44, 61, 53, 63, 44, 63, 53, 63, 44, 63, 0, 65, 44,
        65, 53, 65, 44, 65, 53, 66, 44, 66, 53, 66, 44, 66, 53, 70, 32, 70, 32,
        70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 44, 70, 54, 70, 44,
        70, 54, 68, 44, 68, 54, 68, 44, 68, 0, 66, 44, 66, 54, 66, 44, 66, 54,
        65, 44, 65, 54, 65, 44, 0, 54, 65, 39, 65, 39, 65, 39, 65, 39, 63, 39,
        63, 39, 63, 39, 0, 39, 63, 44, 63, 54, 63, 44, 63, 54, 62, 44, 62, 54,
        62, 44, 62, 0, 63, 44, 63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 63, 44,
        63, 54, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32,
        70, 44, 70, 54, 70, 44, 70, 54, 68, 44, 68, 54, 68, 44, 68, 0, 66, 44,
        66, 54, 66, 44, 66, 54, 65, 44, 65, 54, 65, 44, 65, 54, 63, 44, 63, 44,
        63, 44, 63, 44, 65, 44, 65, 44, 65, 44, 65, 44, 63, 48, 63, 54, 63, 48,
        63, 54, 62, 48, 62, 54, 62, 48, 62, 54, 63, 32, 63, 32, 63, 32, 63, 32,
        64, 32, 64, 32, 64, 32, 64, 32, 65, 33, 65, 33, 66, 33, 66, 33, 66, 33,
        65, 33, 65, 33, 65, 33, 64, 41, 64, 51, 64, 41, 64, 51, 65, 41, 65, 51,
        65, 41, 65, 0, 68, 41, 68, 51, 68, 41, 68, 51, 66, 41, 66, 51, 66, 41,
        66, 51, 65, 34, 65, 34, 65, 34, 65, 34, 66, 34, 66, 34, 66, 34, 66, 34,
        65, 41, 65, 49, 65, 41, 65, 49, 64, 41, 64, 49, 64, 41, 64, 0, 65, 41,
        65, 49, 65, 41, 65, 49, 70, 41, 70, 49, 70, 41, 70, 49, 68, 36, 68, 36,
        68, 36, 70, 36, 70, 36, 70, 36, 68, 36, 68, 36, 67, 44, 67, 54, 67, 44,
        67, 54, 68, 44, 68, 54, 68, 44, 68, 0, 72, 44, 72, 54, 72, 44, 72, 54,
        70, 44, 70, 54, 70, 44, 70, 54, 68, 37, 68, 37, 68, 37, 68, 37, 70, 37,
        70, 37, 70, 37, 70, 37, 68, 44, 68, 53, 68, 44, 68, 53, 67, 44, 67, 53,
        67, 44, 67, 53, 68, 0, 68, 0, 68, 0, 68, 0, 73, 0, 73, 0, 73, 0, 73, 0,
        72, 42, 72, 42, 72, 42, 72, 42, 70, 42, 70, 42, 70, 42, 70, 44, 68, 46,
        68, 51, 68, 46, 68, 51, 66, 46, 66, 51, 66, 46, 66, 51, 65, 0, 65, 0,
        65, 0, 65, 0, 63, 0, 63, 0, 63, 0, 63, 0, 61, 32, 61, 32, 61, 32, 61,
        32, 60, 32, 60, 32, 60, 32, 60, 32, 58, 41, 58, 49, 58, 41, 58, 49, 56,
        41, 56, 49, 56, 41, 56, 49, 54, 0, 54, 0, 54, 0, 54, 0, 53, 0, 53, 0,
        53, 0, 53, 0, 51, 32, 51, 32, 51, 32, 51, 32, 49, 32, 49, 32, 49, 32,
        49, 32, 48, 42, 48, 44, 48, 42, 48, 44, 51, 42, 51, 44, 51, 42, 51, 0,
        58, 42, 58, 48, 58, 42, 58, 48, 56, 42, 56, 48, 56, 42, 56, 48, 55, 37,
        55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37, 58, 44, 58, 53,
        58, 44, 58, 53, 60, 44, 60, 53, 60, 44, 60, 53, 61, 0, 61, 0, 61, 0, 61,
        0, 63, 0, 63, 0, 63, 0, 63, 0, 65, 44, 65, 44, 65, 44, 66, 44, 66, 44,
        66, 44, 65, 44, 65, 44, 64, 51, 64, 53, 64, 51, 64, 53, 65, 51, 65, 53,
        65, 51, 65, 0, 68, 51, 68, 53, 68, 51, 68, 53, 66, 51, 66, 53, 66, 51,
        66, 53, 65, 46, 65, 46, 65, 46, 65, 46, 66, 46, 66, 46, 66, 46, 66, 46,
        65, 49, 65, 53, 65, 49, 65, 53, 64, 49, 64, 53, 64, 49, 64, 0, 65, 49,
        65, 53, 65, 49, 65, 53, 70, 49, 70, 53, 70, 49, 70, 53, 68, 48, 68, 48,
        68, 48, 70, 48, 70, 48, 70, 48, 68, 48, 68, 48, 67, 54, 67, 56, 67, 54,
        67, 56, 68, 54, 68, 56, 68, 54, 68, 0, 72, 54, 72, 56, 72, 54, 72, 56,
        70, 54, 70, 56, 70, 54, 70, 56, 68, 49, 68, 49, 68, 49, 68, 49, 70, 49,
        70, 49, 70, 49, 70, 49, 68, 53, 68, 56, 68, 53, 68, 56, 67, 53, 67, 56,
        67, 53, 67, 56, 68, 0, 68, 0, 68, 0, 68, 0, 77, 0, 77, 0, 77, 0, 77, 0,
        75, 42, 75, 42, 75, 42, 75, 42, 73, 42, 73, 42, 73, 42, 73, 42, 72, 49,
        72, 58, 72, 49, 72, 58, 70, 49, 70, 58, 70, 49, 70, 58, 68, 0, 68, 0,
        68, 0, 68, 0, 66, 0, 66, 0, 66, 0, 66, 0, 65, 32, 65, 32, 65, 32, 65,
        32, 63, 32, 63, 32, 63, 32, 63, 32, 61, 41, 61, 49, 61, 41, 61, 49, 60,
        41, 60, 49, 60, 41, 60, 49, 58, 0, 58, 0, 58, 0, 58, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 57, 32, 57, 32, 57, 32, 57, 32, 60, 32, 60, 32, 60, 32,
        60, 32, 58, 42, 58, 44, 58, 42, 58, 44, 53, 42, 53, 44, 53, 42, 53, 0,
        54, 42, 54, 44, 54, 42, 54, 44, 48, 42, 48, 44, 48, 42, 48, 44, 49, 37,
        49, 37, 49, 37, 49, 37, 49, 37, 49, 37, 49, 37, 49, 41, 0, 44, 0, 49, 0,
        44, 0, 49, 0, 44, 0, 49, 0, 44, 0, 49, 65, 0, 65, 0, 65, 0, 65, 0, 65,
        0, 65, 0, 65, 0, 65, 0, 65, 33, 65, 33, 66, 33, 66, 33, 66, 33, 65, 33,
        65, 33, 65, 33, 64, 41, 64, 51, 64, 41, 64, 51, 65, 41, 65, 51, 65, 41,
        65, 0, 68, 41, 68, 51, 68, 41, 68, 51, 66, 41, 66, 51, 66, 41, 66, 51,
        65, 34, 65, 34, 65, 34, 65, 34, 66, 34, 66, 34, 66, 34, 66, 34, 65, 41,
        65, 49, 65, 41, 65, 49, 64, 41, 64, 49, 64, 41, 64, 0, 65, 41, 65, 49,
        65, 41, 65, 49, 70, 41, 70, 49, 70, 41, 70, 49, 68, 36, 68, 36, 68, 36,
        70, 36, 70, 36, 70, 36, 68, 36, 68, 36, 67, 44, 67, 54, 67, 44, 67, 54,
        68, 44, 68, 54, 68, 44, 68, 0, 72, 44, 72, 54, 72, 44, 72, 54, 70, 44,
        70, 54, 70, 44, 70, 54, 68, 37, 68, 37, 68, 37, 68, 37, 70, 37, 70, 37,
        70, 37, 70, 37, 68, 44, 68, 53, 68, 44, 68, 53, 67, 44, 67, 53, 67, 44,
        67, 53, 68, 0, 68, 0, 68, 0, 68, 0, 73, 0, 73, 0, 73, 0, 73, 0, 72, 42,
        72, 42, 72, 42, 72, 42, 70, 42, 70, 42, 70, 42, 70, 44, 68, 46, 68, 51,
        68, 46, 68, 51, 66, 46, 66, 51, 66, 46, 66, 51, 65, 0, 65, 0, 65, 0, 65,
        0, 63, 0, 63, 0, 63, 0, 63, 0, 61, 32, 61, 32, 61, 32, 61, 32, 60, 32,
        60, 32, 60, 32, 60, 32, 58, 41, 58, 49, 58, 41, 58, 49, 56, 41, 56, 49,
        56, 41, 56, 49, 54, 0, 54, 0, 54, 0, 54, 0, 53, 0, 53, 0, 53, 0, 53, 0,
        51, 32, 51, 32, 51, 32, 51, 32, 49, 32, 49, 32, 49, 32, 49, 32, 48, 42,
        48, 44, 48, 42, 48, 44, 51, 42, 51, 44, 51, 42, 51, 0, 58, 42, 58, 48,
        58, 42, 58, 48, 56, 42, 56, 48, 56, 42, 56, 48, 55, 37, 55, 37, 55, 37,
        55, 37, 56, 37, 56, 37, 56, 37, 56, 37, 58, 44, 58, 53, 58, 44, 58, 53,
        60, 44, 60, 53, 60, 44, 60, 53, 61, 0, 61, 0, 61, 0, 61, 0, 63, 0, 63,
        0, 63, 0, 63, 0, 65, 44, 65, 44, 65, 44, 66, 44, 66, 44, 66, 44, 65, 44,
        65, 44, 64, 51, 64, 53, 64, 51, 64, 53, 65, 51, 65, 53, 65, 51, 65, 0,
        68, 51, 68, 53, 68, 51, 68, 53, 66, 51, 66, 53, 66, 51, 66, 53, 65, 46,
        65, 46, 65, 46, 65, 46, 66, 46, 66, 46, 66, 46, 66, 46, 65, 49, 65, 53,
        65, 49, 65, 53, 64, 49, 64, 53, 64, 49, 64, 0, 65, 49, 65, 53, 65, 49,
        65, 53, 70, 49, 70, 53, 70, 49, 70, 53, 68, 48, 68, 48, 68, 48, 70, 48,
        70, 48, 70, 48, 68, 48, 68, 48, 67, 54, 67, 56, 67, 54, 67, 56, 68, 54,
        68, 56, 68, 54, 68, 0, 72, 54, 72, 56, 72, 54, 72, 56, 70, 54, 70, 56,
        70, 54, 70, 56, 68, 49, 68, 49, 68, 49, 68, 49, 70, 49, 70, 49, 70, 49,
        70, 49, 68, 53, 68, 56, 68, 53, 68, 56, 67, 53, 67, 56, 67, 53, 67, 56,
        68, 0, 68, 0, 68, 0, 68, 0, 77, 0, 77, 0, 77, 0, 77, 0, 75, 42, 75, 42,
        75, 42, 75, 42, 73, 42, 73, 42, 73, 42, 73, 42, 72, 49, 72, 58, 72, 49,
        72, 58, 70, 49, 70, 58, 70, 49, 70, 58, 68, 0, 68, 0, 68, 0, 68, 0, 66,
        0, 66, 0, 66, 0, 66, 0, 65, 32, 65, 32, 65, 32, 65, 32, 63, 32, 63, 32,
        63, 32, 63, 32, 61, 41, 61, 49, 61, 41, 61, 49, 60, 41, 60, 49, 60, 41,
        60, 49, 58, 0, 58, 0, 58, 0, 58, 0, 56, 0, 56, 0, 56, 0, 56, 0, 57, 32,
        57, 32, 57, 32, 57, 32, 60, 32, 60, 32, 60, 32, 60, 32, 58, 42, 58, 44,
        58, 42, 58, 44, 53, 42, 53, 44, 53, 42, 53, 0, 54, 42, 54, 44, 54, 42,
        54, 44, 48, 42, 48, 44, 48, 42, 48, 44, 49, 37, 49, 37, 49, 37, 49, 37,
        49, 37, 49, 37, 49, 37, 49, 41, 0, 44, 0, 49, 0, 44, 0, 49, 0, 44, 0,
        49, 0, 44, 0, 49, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56,
        0, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56,
        42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 0, 51, 42, 51,
        48, 51, 42, 51, 48, 51, 42, 51, 48, 51, 42, 51, 48, 56, 42, 56, 48, 56,
        42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 0, 56, 42, 56, 48, 56, 42, 56,
        48, 56, 42, 56, 48, 56, 42, 56, 0, 52, 42, 52, 48, 52, 42, 52, 48, 52,
        42, 52, 48, 52, 42, 52, 0, 56, 37, 56, 37, 56, 37, 56, 37, 56, 37, 56,
        37, 56, 37, 56, 37, 56, 44, 56, 49, 56, 44, 56, 49, 56, 44, 56, 49, 56,
        44, 56, 0, 53, 44, 53, 49, 53, 44, 53, 49, 53, 44, 53, 49, 53, 44, 53,
        49, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65,
        44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 0, 0, 65, 44, 65,
        53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 39, 65, 39, 65,
        39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 44, 65, 54, 65, 44, 65,
        54, 65, 44, 65, 54, 65, 44, 65, 0, 58, 44, 58, 54, 58, 44, 58, 54, 58,
        44, 58, 54, 58, 44, 58, 54, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65,
        32, 65, 32, 65, 32, 65, 44, 65, 54, 65, 44, 65, 54, 65, 44, 65, 54, 65,
        44, 65, 0, 60, 44, 60, 54, 60, 44, 60, 54, 60, 44, 60, 54, 60, 44, 60,
        54, 63, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63,
        44, 63, 53, 63, 44, 63, 53, 63, 44, 63, 53, 63, 44, 63, 0, 61, 44, 61,
        53, 61, 44, 61, 53, 61, 44, 61, 53, 61, 44, 61, 53, 60, 41, 60, 41, 60,
        41, 60, 41, 60, 41, 60, 41, 63, 41, 63, 41, 63, 44, 63, 53, 63, 44, 63,
        53, 61, 44, 61, 53, 61, 44, 61, 0, 61, 44, 61, 53, 58, 44, 58, 53, 58,
        44, 58, 53, 58, 44, 58, 53, 56, 39, 56, 39, 56, 39, 56, 39, 56, 39, 56,
        39, 56, 39, 56, 39, 56, 42, 56, 44, 56, 42, 56, 44, 56, 42, 56, 44, 56,
        42, 56, 0, 51, 42, 51, 44, 51, 42, 51, 44, 51, 42, 51, 44, 51, 42, 51,
        44, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56,
        42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 0, 52, 42, 52,
        48, 52, 42, 52, 48, 52, 42, 52, 48, 52, 42, 52, 48, 56, 37, 56, 37, 56,
        37, 56, 37, 56, 37, 56, 37, 56, 37, 56, 37, 56, 44, 56, 49, 56, 44, 56,
        49, 56, 44, 56, 49, 56, 44, 56, 0, 53, 44, 53, 49, 53, 44, 53, 49, 53,
        44, 53, 49, 53, 44, 53, 49, 65, 35, 65, 35, 65, 35, 65, 35, 65, 35, 65,
        35, 65, 35, 65, 35, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65,
        44, 65, 0, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65,
        53, 60, 36, 60, 36, 60, 36, 60, 36, 60, 36, 60, 36, 60, 36, 60, 36, 59,
        44, 59, 53, 59, 44, 59, 53, 59, 44, 59, 53, 59, 44, 59, 0, 60, 44, 60,
        53, 60, 44, 60, 53, 60, 44, 60, 53, 60, 44, 60, 53, 68, 24, 68, 24, 68,
        24, 68, 24, 68, 24, 68, 24, 68, 24, 68, 24, 58, 43, 58, 52, 58, 43, 58,
        52, 58, 43, 58, 52, 58, 43, 58, 0, 67, 43, 67, 52, 67, 43, 67, 52, 67,
        43, 67, 52, 67, 43, 67, 52, 57, 29, 57, 29, 57, 29, 57, 29, 57, 29, 57,
        29, 57, 29, 57, 29, 66, 0, 66, 0, 66, 0, 66, 0, 66, 0, 66, 0, 66, 0, 66,
        0, 56, 41, 56, 48, 56, 41, 56, 48, 56, 41, 56, 48, 56, 41, 56, 48, 65,
        0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 53, 0, 53, 0, 53, 0,
        53, 0, 53, 0, 53, 0, 53, 0, 53, 0, 58, 0, 58, 0, 58, 0, 58, 0, 58, 0,
        58, 0, 58, 0, 58, 0, 56, 36, 56, 36, 56, 36, 56, 36, 56, 36, 56, 36, 56,
        36, 56, 36, 56, 42, 56, 44, 56, 42, 56, 44, 56, 42, 56, 44, 56, 42, 56,
        0, 51, 42, 51, 44, 51, 42, 51, 44, 51, 42, 51, 44, 51, 42, 51, 44, 68,
        32, 65, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 42, 56,
        48, 56, 42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 0, 52, 42, 52, 48, 52,
        42, 52, 48, 52, 42, 52, 48, 52, 42, 52, 48, 56, 37, 56, 37, 56, 37, 56,
        37, 56, 37, 56, 37, 56, 37, 56, 37, 56, 44, 56, 49, 56, 44, 56, 49, 56,
        44, 56, 49, 56, 44, 56, 0, 53, 44, 53, 49, 53, 44, 53, 49, 53, 44, 53,
        49, 53, 44, 53, 49, 68, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65, 32, 65,
        32, 65, 32, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 0,
        0, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 65, 44, 65, 53, 68,
        39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 39, 65, 44, 65,
        54, 65, 44, 65, 54, 65, 44, 65, 54, 65, 44, 65, 0, 60, 44, 60, 54, 60,
        44, 60, 54, 60, 44, 60, 54, 60, 44, 60, 54, 68, 32, 63, 32, 63, 32, 63,
        32, 63, 32, 63, 32, 63, 32, 63, 32, 61, 44, 61, 54, 61, 44, 61, 54, 61,
        44, 61, 54, 61, 44, 61, 0, 60, 44, 60, 54, 60, 44, 60, 54, 60, 44, 60,
        54, 60, 44, 60, 54, 68, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63, 37, 63,
        37, 63, 37, 61, 44, 61, 53, 61, 44, 61, 53, 61, 44, 61, 53, 61, 44, 61,
        0, 61, 44, 61, 53, 61, 44, 61, 53, 58, 44, 58, 53, 58, 44, 58, 53, 68,
        41, 56, 41, 56, 41, 56, 41, 56, 41, 56, 41, 56, 41, 56, 41, 56, 44, 56,
        53, 56, 44, 56, 53, 56, 44, 56, 53, 56, 44, 56, 0, 51, 44, 51, 53, 51,
        44, 51, 53, 51, 44, 51, 53, 51, 44, 51, 53, 68, 36, 56, 36, 56, 36, 56,
        36, 56, 36, 56, 36, 56, 36, 56, 36, 56, 42, 56, 44, 56, 42, 56, 44, 56,
        42, 56, 44, 56, 42, 56, 0, 52, 42, 52, 44, 52, 42, 52, 44, 52, 42, 52,
        44, 52, 42, 52, 44, 68, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56, 32, 56,
        32, 56, 32, 56, 42, 56, 48, 56, 42, 56, 48, 56, 42, 56, 48, 56, 42, 56,
        0, 53, 42, 53, 48, 53, 42, 53, 48, 53, 42, 53, 48, 53, 42, 53, 48, 65,
        35, 65, 35, 65, 35, 65, 35, 65, 35, 65, 35, 65, 35, 65, 35, 65, 41, 65,
        51, 65, 41, 65, 51, 65, 41, 65, 51, 65, 41, 65, 0, 65, 41, 65, 51, 65,
        41, 65, 51, 65, 41, 65, 51, 65, 41, 0, 51, 65, 34, 65, 34, 65, 34, 65,
        34, 65, 34, 65, 34, 65, 34, 65, 34, 65, 41, 65, 50, 65, 41, 65, 50, 65,
        41, 65, 50, 65, 41, 65, 0, 58, 41, 58, 50, 58, 41, 58, 50, 58, 41, 58,
        50, 58, 41, 58, 50, 63, 39, 63, 39, 63, 39, 63, 39, 63, 39, 63, 39, 63,
        39, 63, 39, 63, 49, 63, 55, 63, 49, 63, 55, 63, 49, 63, 55, 63, 49, 63,
        0, 58, 49, 58, 55, 58, 49, 58, 55, 58, 49, 58, 55, 58, 49, 58, 55, 63,
        0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 49, 63, 54, 63,
        49, 63, 54, 63, 49, 63, 54, 63, 49, 63, 0, 58, 49, 58, 54, 58, 49, 58,
        54, 58, 49, 58, 54, 58, 49, 58, 54, 63, 44, 63, 44, 63, 44, 63, 44, 63,
        44, 63, 44, 63, 44, 63, 44, 56, 48, 56, 54, 56, 48, 56, 54, 56, 48, 56,
        54, 56, 48, 56, 54, 62, 0, 62, 0, 62, 0, 62, 0, 62, 0, 62, 0, 62, 0, 62,
        0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 63, 0, 63, 0,
        63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 68, 0, 68, 0, 68, 0, 68, 0,
        68, 0, 68, 0, 68, 0, 68, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0,
        60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0,
        56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0,
        58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0,
        60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 0, 55, 0,
        55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0, 60, 0, 60, 0,
        58, 0, 58, 0, 58, 0, 58, 0, 55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0,
        56, 0, 56, 0, 60, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0,
        55, 0, 55, 0, 55, 0, 55, 0, 56, 0, 56, 0, 56, 0, 56, 0, 60, 0, 60, 0,
        60, 0, 60, 0, 58, 0, 58, 0, 58, 0, 58, 0, 55, 25, 55, 25, 55, 25, 55,
        25, 56, 25, 56, 25, 56, 25, 56, 25, 60, 44, 60, 53, 60, 44, 60, 53, 58,
        44, 58, 53, 58, 44, 58, 0, 55, 44, 55, 53, 55, 44, 55, 53, 56, 44, 56,
        53, 56, 44, 56, 53, 60, 41, 60, 41, 60, 41, 60, 41, 58, 41, 58, 41, 58,
        41, 58, 41, 55, 44, 55, 53, 55, 44, 55, 53, 56, 44, 56, 53, 56, 44, 56,
        0, 60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58, 53, 55,
        37, 55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37, 60, 44, 60,
        53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58, 0, 55, 44, 55, 53, 55,
        44, 55, 53, 56, 44, 56, 53, 56, 44, 56, 53, 58, 41, 58, 41, 58, 41, 58,
        41, 60, 41, 60, 41, 60, 41, 60, 41, 61, 44, 61, 53, 61, 44, 61, 53, 63,
        44, 63, 53, 63, 44, 63, 0, 65, 44, 65, 53, 65, 44, 65, 53, 66, 44, 66,
        53, 66, 44, 66, 53, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70,
        32, 70, 32, 70, 44, 70, 54, 70, 44, 70, 54, 68, 44, 68, 54, 68, 44, 68,
        0, 66, 44, 66, 54, 66, 44, 66, 54, 65, 44, 65, 54, 65, 44, 0, 54, 65,
        39, 65, 39, 65, 39, 65, 39, 63, 39, 63, 39, 63, 39, 0, 39, 63, 44, 63,
        54, 63, 44, 63, 54, 62, 44, 62, 54, 62, 44, 62, 0, 63, 44, 63, 54, 63,
        44, 63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 70, 32, 70, 32, 70, 32, 70,
        32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 48, 70, 54, 70, 48, 70, 54, 68,
        48, 68, 54, 68, 48, 68, 0, 66, 48, 66, 54, 66, 48, 66, 54, 65, 48, 65,
        54, 65, 48, 0, 54, 65, 44, 65, 44, 65, 44, 65, 44, 63, 44, 63, 44, 63,
        44, 63, 44, 62, 48, 62, 54, 62, 48, 62, 54, 63, 48, 63, 54, 63, 48, 63,
        0, 65, 48, 65, 54, 65, 48, 65, 54, 58, 48, 58, 54, 58, 48, 58, 54, 55,
        37, 55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56, 37, 56, 37, 60, 44, 60,
        53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58, 0, 55, 44, 55, 53, 55,
        44, 55, 53, 56, 44, 56, 53, 56, 44, 56, 53, 60, 41, 60, 41, 60, 41, 60,
        41, 58, 41, 58, 41, 58, 41, 58, 41, 55, 44, 55, 53, 55, 44, 55, 53, 56,
        44, 56, 53, 56, 44, 56, 0, 60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58,
        53, 58, 44, 58, 53, 55, 37, 55, 37, 55, 37, 55, 37, 56, 37, 56, 37, 56,
        37, 56, 37, 60, 44, 60, 53, 60, 44, 60, 53, 58, 44, 58, 53, 58, 44, 58,
        0, 55, 44, 55, 53, 55, 44, 55, 53, 56, 44, 56, 53, 56, 44, 56, 53, 58,
        41, 58, 41, 58, 41, 58, 41, 60, 41, 60, 41, 60, 41, 60, 41, 61, 44, 61,
        53, 61, 44, 61, 53, 63, 44, 63, 53, 63, 44, 63, 0, 65, 44, 65, 53, 65,
        44, 65, 53, 66, 44, 66, 53, 66, 44, 66, 53, 70, 32, 70, 32, 70, 32, 70,
        32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 44, 70, 54, 70, 44, 70, 54, 68,
        44, 68, 54, 68, 44, 68, 0, 66, 44, 66, 54, 66, 44, 66, 54, 65, 44, 65,
        54, 65, 44, 0, 54, 65, 39, 65, 39, 65, 39, 65, 39, 63, 39, 63, 39, 63,
        39, 0, 39, 63, 44, 63, 54, 63, 44, 63, 54, 62, 44, 62, 54, 62, 44, 62,
        0, 63, 44, 63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 63, 44, 63, 54, 70,
        32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 32, 70, 44, 70,
        54, 70, 44, 70, 54, 68, 44, 68, 54, 68, 44, 68, 0, 66, 44, 66, 54, 66,
        44, 66, 54, 65, 44, 65, 54, 65, 44, 65, 54, 63, 39, 63, 39, 63, 39, 63,
        39, 65, 39, 65, 39, 65, 39, 65, 39, 63, 44, 63, 54, 63, 44, 63, 54, 62,
        44, 62, 54, 62, 44, 62, 54, 63, 32, 63, 32, 63, 32, 63, 32, 64, 32, 64,
        32, 64, 32, 64, 32, 65, 33, 65, 33, 65, 33, 66, 33, 66, 33, 66, 33, 65,
        33, 65, 33, 64, 41, 64, 47, 64, 41, 64, 47, 65, 41, 65, 47, 65, 41, 65,
        0, 68, 41, 68, 47, 68, 41, 68, 47, 66, 41, 66, 47, 66, 41, 66, 47, 65,
        34, 65, 34, 65, 34, 65, 34, 66, 34, 66, 34, 66, 34, 66, 34, 65, 41, 65,
        49, 65, 41, 65, 49, 64, 41, 64, 49, 64, 41, 64, 0, 65, 41, 65, 49, 65,
        41, 65, 49, 70, 41, 70, 49, 70, 41, 70, 49, 68, 36, 68, 36, 68, 36, 70,
        36, 70, 36, 70, 36, 68, 36, 68, 36, 67, 44, 67, 54, 67, 44, 67, 54, 68,
        44, 68, 54, 68, 44, 68, 0, 72, 44, 72, 54, 72, 44, 72, 54, 70, 44, 70,
        54, 70, 44, 70, 54, 68, 37, 68, 37, 68, 37, 68, 37, 70, 37, 70, 37, 70,
        37, 70, 37, 68, 44, 68, 53, 68, 44, 68, 53, 67, 44, 67, 53, 67, 44, 67,
        53, 68, 0, 68, 0, 68, 0, 68, 0, 73, 0, 73, 0, 73, 0, 73, 0, 72, 42, 72,
        42, 72, 42, 72, 42, 70, 42, 70, 42, 70, 42, 70, 44, 68, 46, 68, 51, 68,
        46, 68, 51, 66, 46, 66, 51, 66, 46, 66, 51, 65, 0, 65, 0, 65, 0, 65, 0,
        63, 0, 63, 0, 63, 0, 63, 0, 61, 32, 61, 32, 61, 32, 61, 32, 60, 32, 60,
        32, 60, 32, 60, 32, 58, 41, 58, 49, 58, 41, 58, 49, 56, 41, 56, 49, 56,
        41, 56, 49, 54, 0, 54, 0, 54, 0, 54, 0, 53, 0, 53, 0, 53, 0, 53, 0, 51,
        32, 51, 32, 51, 32, 51, 32, 49, 32, 49, 32, 49, 32, 49, 32, 48, 42, 48,
        44, 48, 42, 48, 44, 51, 42, 51, 44, 51, 42, 51, 44, 58, 42, 58, 48, 58,
        42, 58, 48, 56, 42, 56, 48, 56, 42, 56, 48, 55, 37, 55, 37, 55, 37, 55,
        37, 56, 37, 56, 37, 56, 37, 56, 37, 58, 44, 58, 53, 58, 44, 58, 53, 60,
        44, 60, 53, 60, 44, 60, 53, 61, 0, 61, 0, 61, 0, 61, 0, 63, 0, 63, 0,
        63, 0, 63, 0, 65, 45, 65, 45, 65, 45, 66, 45, 66, 45, 66, 45, 65, 45,
        65, 45, 64, 51, 64, 53, 64, 51, 64, 53, 65, 51, 65, 53, 65, 51, 65, 0,
        68, 51, 68, 53, 68, 51, 68, 53, 66, 51, 66, 53, 66, 51, 66, 53, 65, 46,
        65, 46, 65, 46, 65, 46, 66, 46, 66, 46, 66, 46, 66, 46, 65, 49, 65, 53,
        65, 49, 65, 53, 64, 49, 64, 53, 64, 49, 64, 0, 65, 49, 65, 53, 65, 49,
        65, 53, 70, 49, 70, 53, 70, 49, 70, 53, 68, 48, 68, 48, 68, 48, 70, 48,
        70, 48, 70, 48, 68, 48, 68, 48, 67, 54, 67, 56, 67, 54, 67, 56, 68, 54,
        68, 56, 68, 54, 68, 0, 72, 54, 72, 56, 72, 54, 72, 56, 70, 54, 70, 56,
        70, 54, 70, 56, 68, 49, 68, 49, 68, 49, 68, 49, 70, 49, 70, 49, 70, 49,
        70, 49, 68, 53, 68, 56, 68, 53, 68, 56, 67, 53, 67, 56, 67, 53, 67, 56,
        68, 0, 68, 0, 68, 0, 68, 0, 77, 0, 77, 0, 77, 0, 77, 0, 75, 42, 75, 42,
        75, 42, 75, 42, 73, 42, 73, 42, 73, 42, 73, 42, 72, 49, 72, 58, 72, 49,
        72, 58, 70, 49, 70, 58, 70, 49, 70, 58, 68, 0, 68, 0, 68, 0, 68, 0, 66,
        0, 66, 0, 66, 0, 66, 0, 65, 32, 65, 32, 65, 32, 65, 32, 63, 32, 63, 32,
        63, 32, 63, 32, 61, 41, 61, 49, 61, 41, 61, 49, 60, 41, 60, 49, 60, 41,
        60, 49, 58, 0, 58, 0, 58, 0, 58, 0, 56, 0, 56, 0, 56, 0, 56, 0, 57, 32,
        57, 32, 57, 32, 57, 32, 60, 32, 60, 32, 60, 32, 60, 32, 58, 42, 58, 44,
        58, 42, 58, 44, 53, 42, 53, 44, 53, 42, 53, 0, 54, 42, 54, 44, 54, 42,
        54, 44, 48, 42, 48, 44, 48, 42, 48, 44, 49, 37, 49, 37, 49, 37, 49, 37,
        49, 37, 49, 37, 49, 37, 49, 37, 0, 44, 0, 53, 0, 44, 0, 53, 0, 44, 0,
        53, 0, 44, 0, 53, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65, 0, 65,
        0, 65, 33, 65, 33, 65, 33, 66, 33, 66, 33, 66, 33, 65, 33, 65, 33, 64,
        41, 64, 51, 64, 41, 64, 51, 65, 41, 65, 51, 65, 41, 65, 0, 68, 41, 68,
        51, 68, 41, 68, 51, 66, 41, 66, 51, 66, 41, 66, 51, 65, 34, 65, 34, 65,
        34, 65, 34, 66, 34, 66, 34, 66, 34, 66, 34, 65, 41, 65, 49, 65, 41, 65,
        49, 64, 41, 64, 49, 64, 41, 64, 0, 65, 41, 65, 49, 65, 41, 65, 49, 70,
        41, 70, 49, 70, 41, 70, 49, 68, 36, 68, 36, 68, 36, 70, 36, 70, 36, 70,
        36, 68, 36, 68, 36, 67, 44, 67, 54, 67, 44, 67, 54, 68, 44, 68, 54, 68,
        44, 68, 0, 72, 44, 72, 54, 72, 44, 72, 54, 70, 44, 70, 54, 70, 44, 70,
        54, 68, 37, 68, 37, 68, 37, 68, 37, 70, 37, 70, 37, 70, 37, 70, 37, 68,
        44, 68, 53, 68, 44, 68, 53, 67, 44, 67, 53, 67, 44, 67, 53, 68, 0, 68,
        0, 68, 0, 68, 0, 73, 0, 73, 0, 73, 0, 73, 0, 72, 42, 72, 42, 72, 42, 72,
        42, 70, 42, 70, 42, 70, 42, 70, 42, 68, 46, 68, 51, 68, 46, 68, 51, 66,
        46, 66, 51, 66, 46, 66, 51, 65, 0, 65, 0, 65, 0, 65, 0, 63, 0, 63, 0,
        63, 0, 63, 0, 61, 32, 61, 32, 61, 32, 61, 32, 60, 32, 60, 32, 60, 32,
        60, 32, 58, 41, 58, 49, 58, 41, 58, 49, 56, 41, 56, 49, 56, 41, 56, 49,
        54, 0, 54, 0, 54, 0, 54, 0, 53, 0, 53, 0, 53, 0, 53, 0, 51, 32, 51, 32,
        51, 32, 51, 32, 49, 32, 49, 32, 49, 32, 49, 32, 48, 42, 48, 44, 48, 42,
        48, 44, 51, 42, 51, 44, 51, 42, 51, 44, 58, 42, 58, 48, 58, 42, 58, 48,
        56, 42, 56, 48, 56, 42, 56, 48, 55, 37, 55, 37, 55, 37, 55, 37, 56, 37,
        56, 37, 56, 37, 56, 37, 58, 44, 58, 53, 58, 44, 58, 53, 60, 44, 60, 53,
        60, 44, 60, 53, 61, 0, 61, 0, 61, 0, 61, 0, 63, 0, 63, 0, 63, 0, 63, 0,
        65, 24, 65, 24, 65, 24, 66, 24, 66, 24, 66, 24, 65, 24, 65, 24, 64, 30,
        64, 32, 64, 30, 64, 32, 65, 30, 65, 32, 65, 30, 65, 0, 68, 30, 68, 32,
        68, 30, 68, 32, 66, 30, 66, 32, 66, 30, 66, 32, 65, 25, 65, 25, 65, 25,
        65, 25, 66, 25, 66, 25, 66, 25, 66, 25, 65, 29, 65, 32, 65, 29, 65, 32,
        64, 29, 64, 32, 64, 29, 64, 0, 65, 29, 65, 32, 65, 29, 65, 32, 70, 29,
        70, 32, 70, 29, 70, 32, 68, 27, 68, 27, 68, 27, 70, 27, 70, 27, 70, 27,
        68, 27, 68, 27, 67, 34, 67, 36, 67, 34, 67, 36, 68, 34, 68, 36, 68, 34,
        68, 0, 72, 34, 72, 36, 72, 34, 72, 36, 70, 34, 70, 36, 70, 34, 70, 36,
        68, 49, 68, 49, 68, 49, 68, 49, 70, 49, 70, 49, 70, 49, 70, 49, 68, 53,
        68, 56, 68, 53, 68, 56, 67, 53, 67, 56, 67, 53, 67, 56, 68, 0, 68, 0,
        68, 0, 68, 0, 77, 0, 77, 0, 77, 0, 77, 0, 75, 30, 75, 30, 75, 30, 73,
        30, 73, 30, 73, 30, 72, 30, 72, 30, 70, 49, 70, 58, 70, 49, 68, 58, 68,
        49, 68, 58, 66, 49, 66, 58, 65, 0, 65, 0, 65, 0, 63, 0, 63, 0, 63, 0,
        73, 0, 73, 0, 72, 0, 72, 0, 72, 0, 70, 0, 70, 0, 70, 0, 68, 0, 68, 0,
        66, 0, 66, 0, 66, 0, 65, 0, 65, 0, 65, 0, 63, 0, 63, 0, 61, 0, 61, 0,
        61, 0, 60, 0, 60, 0, 60, 0, 58, 0, 58, 0, 57, 32, 57, 32, 57, 32, 57,
        32, 60, 32, 60, 32, 60, 32, 60, 32, 58, 42, 58, 44, 58, 42, 58, 44, 53,
        42, 53, 44, 53, 42, 53, 0, 54, 42, 54, 44, 54, 42, 54, 44, 48, 42, 48,
        44, 48, 42, 48, 44, 49, 25, 49, 25, 49, 25, 49, 25, 49, 25, 49, 25, 49,
        25, 49, 25, 49, 41, 49, 53, 49, 41, 49, 53, 49, 41, 49, 53, 49, 41, 49,
        53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/*********************************************************************
 * @fn      TIM1_OutCompare_Init
 *
 * @brief   Initializes TIM1 output compare.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM1_PWMOut_Init(u16 arr, u16 psc, u16 ccp) {
    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

#if (PWM_MODE == PWM_MODE1)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

#elif (PWM_MODE == PWM_MODE2)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

#endif

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init( TIM1, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig( TIM1, ENABLE);
    TIM_Cmd( TIM1, ENABLE);
}

void toneinit(void) {

    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOD, &GPIO_InitStructure);

}

void tone(uint16_t freq) {

    uint16_t duration;

    duration = 1000000 / freq;   // in usec

    TIM1_PWMOut_Init(duration, 47, duration / 2);

}

void notone(void) {

    TIM_Cmd(TIM1, DISABLE);
}

void notone2(void) {

    TIM1_PWMOut_Init(65535, 47, 65535);

}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {

    Delay_Init();

    toneinit();

    while(1) {

        for(int i=0; i<6720; i++) {

            if(notes[i]!=0) {
                tone(tonedata[notes[i]]);
            } else {
                notone2();
            }

            Delay_Ms(11);

        }

        notone();
        Delay_Ms(5000);

    }
}
