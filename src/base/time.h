/*
** Taiga
** Copyright (C) 2010-2016, Eren Okka
** 
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <ctime>
#include <string>
#include <windows.h>

#include <date/date.h>

#include "comparable.h"

class Date : public base::Comparable<Date> {
public:
  Date();
  explicit Date(const std::wstring& date);
  explicit Date(const SYSTEMTIME& st);
  explicit Date(unsigned short year, unsigned short month, unsigned short day);

  Date& operator=(const Date& date);

  int operator-(const Date& date) const;

  explicit operator bool() const;
  explicit operator SYSTEMTIME() const;
  explicit operator std::wstring() const;
  explicit operator date::year_month_day() const;

  std::wstring to_string() const;

  unsigned short year() const;
  unsigned short month() const;
  unsigned short day() const;

  void set_year(unsigned short year);
  void set_month(unsigned short month);
  void set_day(unsigned short day);

private:
  base::CompareResult Compare(const Date& date) const;

  date::year year_;
  date::month month_;
  date::day day_;
};

class Duration {
public:
  Duration(time_t time);

  enum {
    kToMinutes = 60,
    kToHours   = 60 * 60,
    kToDays    = 60 * 60 * 24,
    kToMonths  = 60 * 60 * 24 * 30,
    kToYears   = 60 * 60 * 24 * 365,
  };

  float seconds() const;
  float minutes() const;
  float hours() const;
  float days() const;
  float months() const;
  float years() const;

private:
  time_t time_;
};

std::wstring GetAbsoluteTimeString(time_t unix_time);
std::wstring GetRelativeTimeString(time_t unix_time, bool append_suffix);

time_t ConvertIso8601(const std::wstring& datetime);
time_t ConvertRfc822(const std::wstring& datetime);
std::wstring ConvertRfc822ToLocal(const std::wstring& datetime);

void GetSystemTime(SYSTEMTIME& st, int utc_offset = 0);

Date GetDate();
Date GetDate(time_t unix_time);
std::wstring GetTime(LPCWSTR format = L"HH':'mm':'ss");

Date GetDateJapan();
std::wstring GetTimeJapan(LPCWSTR format = L"HH':'mm':'ss");

std::wstring ToDateString(time_t seconds);
unsigned int ToDayCount(const Date& date);
std::wstring ToTimeString(int seconds);

const Date& EmptyDate();
