#ifndef TIME_H_
#define TIME_H_


class Time
{

  public:

      /// one 60th of a second 
      int sec_1_60th;

      int seconds;

      int minutes;

      int hours;

      Time():
          sec_1_60th(0),
          seconds(0),
          minutes(0),
          hours(0)

      {

      }

      ~Time()	{}

      //  Tick the time every second
      Time operator++(int x)
      {

          if(sec_1_60th >= 59)
          {

              sec_1_60th = 0;

              if(seconds >= 59)
              {

                  seconds = 0;
                  if(minutes >= 59)
                  {

                      minutes = 0;
                      hours++;

                  }

                  else
                  {

                      minutes++;

                  }
              }

              else
              {

                  seconds++;

              }

          }
          else
          {

              sec_1_60th++;

          }

      }
};
#endif /*TIME_H_*/
