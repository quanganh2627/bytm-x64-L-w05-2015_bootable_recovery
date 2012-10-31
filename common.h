/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RECOVERY_COMMON_H
#define RECOVERY_COMMON_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "logd.h"


#define LOGE(format, ...) \
    do { \
        fprintf(stderr, "E:" format, ##__VA_ARGS__); \
        __libc_android_log_print(ANDROID_LOG_ERROR, "Recovery", (format), ##__VA_ARGS__ ); \
    } while (0)
#define LOGW(format, ...) \
    __libc_android_log_print(ANDROID_LOG_WARN, "Recovery", (format), ##__VA_ARGS__ )
#define LOGI(format, ...) \
    __libc_android_log_print(ANDROID_LOG_INFO, "Recovery", (format), ##__VA_ARGS__ )

#if 0
#define LOGV(...) fprintf(stdout, "V:" __VA_ARGS__)
#define LOGD(...) fprintf(stdout, "D:" __VA_ARGS__)
#else
#define LOGV(format, ...) \
    __libc_android_log_print(ANDROID_LOG_VERBOSE, "Recovery", (format), ##__VA_ARGS__ )
#define LOGD(format, ...) \
    __libc_android_log_print(ANDROID_LOG_DEBUG, "Recovery", (format), ##__VA_ARGS__ )

#endif

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

typedef struct {
    const char* mount_point;  // eg. "/cache".  must live in the root directory.

    const char* fs_type;      // "yaffs2" or "ext4" or "vfat"

    const char* device;       // MTD partition name if fs_type == "yaffs"
                              // block device if fs_type == "ext4" or "vfat"

    const char* device2;      // alternative device to try if fs_type
                              // == "ext4" or "vfat" and mounting
                              // 'device' fails

    long long length;         // (ext4 partition only) when
                              // formatting, size to use for the
                              // partition.  0 or negative number
                              // means to format all but the last
                              // (that much).
} Volume;

// fopen a file, mounting volumes and making parent dirs as necessary.
FILE* fopen_path(const char *path, const char *mode);

#ifdef __cplusplus
}
#endif

#endif  // RECOVERY_COMMON_H
