#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 6 // UTC day 1-31
#define YOTTA_BUILD_HOUR 16 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 57 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 26 // UTC second 0-61
#define YOTTA_BUILD_UUID a37b41ca-fffc-4340-b79d-86ed1c76ed19 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 680f6397f5ef3afef58d2d51ede4d06047f2765d // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 680f639 // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
