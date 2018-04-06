#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 6 // UTC day 1-31
#define YOTTA_BUILD_HOUR 19 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 38 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 17 // UTC second 0-61
#define YOTTA_BUILD_UUID 0a5ef5a2-5e33-49b6-8133-9a4890c834d0 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 002f3955d284707b8634c200e08a6d52a30d9b48 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 002f395 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
