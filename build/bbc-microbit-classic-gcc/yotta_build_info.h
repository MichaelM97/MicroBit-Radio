#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 4 // UTC day 1-31
#define YOTTA_BUILD_HOUR 20 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 3 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 23 // UTC second 0-61
#define YOTTA_BUILD_UUID d3d3a8f7-d4cf-45a4-8a87-b18cfbb044a7 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 4e200444f4f17ee297a1db958a97292dac6b5133 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 4e20044 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
