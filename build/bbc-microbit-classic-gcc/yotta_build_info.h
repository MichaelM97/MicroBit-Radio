#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 4 // UTC day 1-31
#define YOTTA_BUILD_HOUR 20 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 10 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 19 // UTC second 0-61
#define YOTTA_BUILD_UUID 055b62bb-4fc3-425d-8965-f375678aa29a // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID f46c72d6757b49cf2120ffee46aae73ce3678aa0 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION f46c72d // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
