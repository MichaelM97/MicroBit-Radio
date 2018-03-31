#ifndef __YOTTA_BUILD_INFO_H__
#define __YOTTA_BUILD_INFO_H__
// yotta build info, #include YOTTA_BUILD_INFO_HEADER to access
#define YOTTA_BUILD_YEAR 2018 // UTC year
#define YOTTA_BUILD_MONTH 3 // UTC month 1-12
#define YOTTA_BUILD_DAY 9 // UTC day 1-31
#define YOTTA_BUILD_HOUR 4 // UTC hour 0-24
#define YOTTA_BUILD_MINUTE 36 // UTC minute 0-59
#define YOTTA_BUILD_SECOND 13 // UTC second 0-61
#define YOTTA_BUILD_UUID cfcbb530-49c1-428d-9f33-99b3df756a39 // unique random UUID for each build
#define YOTTA_BUILD_VCS_ID 5fbae5df32c1e346f8da7ec3d201b5f2101b96b2 // git or mercurial hash
#define YOTTA_BUILD_VCS_CLEAN 0 // evaluates true if the version control system was clean, otherwise false
#define YOTTA_BUILD_VCS_DESCRIPTION 5fbae5d // git describe or mercurial equivalent
#endif // ndef __YOTTA_BUILD_INFO_H__
