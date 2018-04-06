#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 6 // UTC day 1-31
#define YOTTA_BUILD_HOUR 21 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 22 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 50 // UTC second 0-61
#define YOTTA_BUILD_UUID 6ddc51b5-9423-4219-b9ce-8dc2d42a01f0 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 0e92b41869d35fe6e47a8b85ae5320ea0fd6df79 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 0e92b41 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
