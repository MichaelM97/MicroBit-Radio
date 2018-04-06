#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 6 // UTC day 1-31
#define YOTTA_BUILD_HOUR 17 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 8 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 33 // UTC second 0-61
#define YOTTA_BUILD_UUID 5f5b0383-8ef8-45c7-9201-66b6a6361251 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 2663ee9797f6e36f7a2cd9d2dad02e4a1036b90d // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 2663ee9 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
