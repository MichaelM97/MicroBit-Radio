#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 4 // UTC day 1-31
#define YOTTA_BUILD_HOUR 19 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 46 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 56 // UTC second 0-61
#define YOTTA_BUILD_UUID 1115fdb4-9881-485f-aa42-026afd82347d // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 1690fb8eeb290b4bb8d120364cbb8bf4452be35a // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 1690fb8 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
