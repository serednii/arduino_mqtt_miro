

class GetDate {
  public:
    //Week Days
    String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    //Month names
    String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    time_t epochTime;
    String formattedTime;
    int currentHour;
    int currentMinute;
    int currentSecond;
    int weekDayNumber;
    String weekDay;
    int monthDay;
    int currentMonth;
    String currentMonthName;
    int currentYear;
    String currentDate;
};

GetDate getDate;
