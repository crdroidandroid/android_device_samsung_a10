/*
 * Copyright 2021 Soo Hwan Na "Royna"
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

#define KMSG_PATH "/proc/kmsg"
#define CHECK_KMSG "/data/debug/kmsg"
#define WRITE_KMSG "/data/debug/logs/kmsg.txt"
#define LOG_TAG "DebugKmsgDaemon"

#include <log/log.h>
#include <fstream>

bool check_data() {
    std::ifstream datafile(CHECK_KMSG);
    if (datafile.good()) {
        datafile.close();
        ALOGI("Found %s, logging...", CHECK_KMSG);
        return true;
    } else {
        ALOGW("Couldn't find %s, not logging...", CHECK_KMSG);
        return false;
    }
}

void copy_kmsg() {
    if (check_data()) {
        std::ifstream readfile(KMSG_PATH);
        std::ofstream writefile(WRITE_KMSG);
        writefile << readfile.rdbuf();
    }
}
