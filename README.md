# strptime function for Windows (and Linux)

Published under MIT License  
  
[Repository](https://github.com/OlafSimon/strptime-for-Windows-Linux) documentation under docs/docs.chm or (after download) docs/html/index.html.

## Intention
 
To my surprise the function 'strptime' to convert date and time from a string representation to a numerical calendrical representation available on Linux is not available on Window for C/C++ programming.  Further more even time zone Information cannot be processed, even under Linux.  
  
My surprise was even larger not to  find solutions on open source publications without having tremendous disadvantages. See section 'Inquiry' for more Information.  
  
As a result I took the time to implement strptime and strftime having the following features:

* Integration of time zone Information
* Option for parsing calendrical strings without the need of a format string 
* Portable code using ANSI C
* Language support (so far English and German, extensions easily possible)
* Thread safety
* Format string and function parameters compatible to standard C 'strftime' definition  
 (as far as possible)

In order to avoid Name conflicts with the Standard C libraries the functions are called:

* LibOb_strftime()
* LibOb_strptime()

Additional functions for time operations and general string parsing are provided also.  
  
In case you are programming using C++ you may be interested in the [cTime class](https://github.com/OlafSimon/cTime) providing even more simple usage.

## Usage of LibOb\_strptime and LibOb\_strftime

The following code snippet demonstrates the usage of the implemented functions. The function LibOb\_strftime needed two additional parameters to support time zone and language. Both parameters may be set to 'zero' if not needed.

    #include "LibCpp/Time/cTime.h"

    using namespace LibCpp;
    using namespace std;

    int main()
    {
        printf("------- Usage of strptime / strftime ---------\n");
        char timeStr[64];
        struct tm tp;

        time_t now = time(0);
        localtime_s(&tp,&now);
        stTimeZone localZone = LibOb_localTimeZone(0);

        LibOb_strftime(timeStr, 64, 0, &tp, &localZone, 0);

        printf("Current time is: %s\n", timeStr);
        LibOb_strftime(timeStr, 64, "%A %Y-%m-%d %H:%M:%S %Z", &tp, &localZone, 0);
        printf("or formatted: %s\n", timeStr);

        //string dateString = "2022-9-15";
        //string dateString = "15:32:10";
        //string dateString = "15:32:10DST";
        //string dateString = "15:32:10 DST";
        //string dateString = "15:32:10 DST +02:00";
        //string dateString = "2007-08-31T16:47+01:45";
        //string dateString = "2007-08-31#16:47:36#UTC#+01:00";
        //string dateString = "03/15/2023";
        //string dateString = "1.2.2024";
        //string dateString = "8:23 Uhr am 1. 2. 2024 CEST";
        //string dateString = "1. Februar 2024 um 10:11Uhr";
        //string dateString = "May 15th 2019";

        const char* dateString = "May 15, 2019";
        printf("Test input: %s\n", dateString);

        LibOb_strptime(dateString, 0, &tp, &localZone);

        printf("Numerical calendar data: year %d, month %d, day %d\n", (int)tp.tm_year+1900, (int)tp.tm_mon+1, (int)tp.tm_mday);
        fflush(stdout);
    }

## Installation

The following files need to be included to your C/C++ project: 

* src/LibOb_strptime.h
* src/LibOb_strptime.cpp
 
## Further documentation

This repository and documentation is a part of the larger [cTime class](https://github.com/OlafSimon/cTime) library on github.

## Inquiry

An intense discussion on the issue of having 'strptime' available on Windows can be found on stack-overflow under [strptime-equivalent-on-windows]( https://stackoverflow.com/questions/321849/strptime-equivalent-on-windows).  
  
Several proposals are listed but all of them have some kind of disadvantages.

* Usage of 'sscanf'

This solution is more a work around but does not support the comfortable use of 'strptime'.

* Usage of 'std::get_time()'

The resulting data is delivered through the struct tm, which has no entry for time zone data.
Thus time zone is not sufficiently supported.

* NetBSD publication by Klaus Klein and David Laight

The 'strptime' implementation can be found on [NetBsd](http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/time/strptime.c?rev=HEAD
) and does have support for time zone data which is the mayor feature to be provided. This implementation has a dependence of 'tzfile.h', which seems to be part of the [iana time zone database](ttp://www.iana.org/time-zones). The 'struct tm' seems to be enlarged by the TM_ZONE  entry. Named time zones seem to be limited to US zones. At least Installation is a bit complicated and I expect name conflicts with the C/C++ standard libraries. 

* 'boost' library

You get a dependence of a large library, which probably not desired for just the implementation of two functions. I didn't check what actually can be done or can't be done for that reason. "swick" and "amwinter" also raised that issue.

 * CStringA::FormatV

is a Microsoft specific implementation and not portable. Same applies to the class CTime.

* Implementation of P. J. Miller

The [implementation](https://github.com/p-j-miller/date-time) from P. J. Miller is the (by far) best approach addressing time zone support and many other of the desired features. The main reason for not just adding language support and automated parsing is the chosen concept of passing the time zone Information through a global variable and thus loosing the abaility of thread safety. Alltogether I decided not to develop a solution on top of that implementation.


----
# Note from the packager

The three goals of this fork — https://github.com/treeswift/strptime — are to provide [build files](meson.build), release tagging and a ready-to-use POSIX interface
for seamlessly integrating `LibOb_strptime` into large *nix-oriented codebases without mixing licenses. Two of those goals could be accomplished with a simple patch,
but tagging required its own forty acres and a mule. Absent any versioning in the originally published code, we have arbitrarily assigned it version 1.0.0.

The naming of the methods suggests that `LibOb_strptime` may be a part of a larger project and there is more to come; in anticipation of that, our plan is to expose
single-purpose, "Unix way" components as static libraries and the umbrella `libob` as a single shared library. Feel free to change that.

