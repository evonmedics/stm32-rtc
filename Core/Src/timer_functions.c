/*
 * timer_functions.c
 *
 *  Created on: May 21, 2024
 *      Author: ngp
 */
#include "rtc.h"
#include <stdio.h>
#include "timer_functions.h"
#include <stm32l4xx_hal_rtc.h>

//init rtc and calender

struct time{
	char HH;
	char MM;
	char SS;
};

/*
 * uint8_t hrs : uint8_t min : uint8_t sec : unin8_t date : uint8_t weekday : uint8_t month : uint8_t year
 *
 *  uint8_t weekday = RTC_WEEKDAY_TUESDAY, uint8_t month = RTC_MONTH_MAY, uint8_t year = 24,  unin8_t date = 22
 */

void set_time (char hrs, char min, char sec,  char date, uint8_t weekday, uint8_t month, char year)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	/** Initialize RTC and set the Time and Date
	 */
	sTime.Hours = hrs;
	sTime.Minutes = min;
	sTime.Seconds = sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}

	sDate.WeekDay = weekday;
	sDate.Month = month;
	sDate.Date = date;
	sDate.Year = year;

	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2); // backup register
}

void get_time(char Time[], char Date[])
{
	RTC_DateTypeDef gDate = {0};
	RTC_TimeTypeDef gTime = {0};

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	/* Display time Format: hh:mm:ss */
	sprintf((char*)Time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
	/* Display date Format: dd-mm-yy */
	sprintf((char*)Date,"%02d-%02d-%2d",gDate.Date, gDate.Month, 2000 + gDate.Year);
}


void get_timestamp(char timestamp[])
{
	RTC_DateTypeDef gDate = {0};
	RTC_TimeTypeDef gTime = {0};

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	/* Display timestamp Format: hh:mm:ss dd-mm-yy */
	sprintf((char*)timestamp,"%02d:%02d:%02d %02d-%02d-%2d",gTime.Hours, gTime.Minutes, gTime.Seconds ,gDate.Date, gDate.Month, 2000 + gDate.Year);
}



