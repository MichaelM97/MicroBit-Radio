#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 5 // UTC day 1-31
#define YOTTA_BUILD_HOUR 19 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 40 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 23 // UTC second 0-61
#define YOTTA_BUILD_UUID bc0ac527-c14e-4eb3-bf42-2cc63e5b84ab // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID fe23f51fc689b9b57c6ca07fdb11b218136dd2a1 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION fe23f51 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
