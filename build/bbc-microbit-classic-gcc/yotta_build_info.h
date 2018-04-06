#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 4 // UTC month 1-12
#define YOTTA_BUILD_DAY 6 // UTC day 1-31
#define YOTTA_BUILD_HOUR 21 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 59 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 29 // UTC second 0-61
#define YOTTA_BUILD_UUID 4f3d7ff5-5fe2-40b8-aba1-aed778353c21 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID bc4b9cedc4729b7c77a216b4a290365ad84bcee1 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION bc4b9ce // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
