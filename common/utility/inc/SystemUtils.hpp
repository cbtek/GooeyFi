///
/// CBTek LLC ("COMPANY") CONFIDENTIAL
/// Copyright (c) 2016 CBTek, All Rights Reserved.
///
/// NOTICE:  All information contained herein is, and remains the property of COMPANY. The intellectual and technical concepts contained
/// herein are proprietary to COMPANY and may be covered by U.S. and Foreign Patents, patents in process, and are protected by trade secret or copyright law.
/// Dissemination of this information or reproduction of this material is strictly forbidden unless prior written permission is obtained
/// from COMPANY.  Access to the source code contained herein is hereby forbidden to anyone except current COMPANY employees, managers or contractors who have executed
/// Confidentiality and Non-disclosure agreements explicitly covering such access.
///
/// The copyright notice above does not evidence any actual or intended publication or disclosure  of  this source code, which includes
/// information that is confidential and/or proprietary, and is a trade secret, of  COMPANY.   ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC  PERFORMANCE,
/// OR PUBLIC DISPLAY OF OR THROUGH USE  OF THIS  SOURCE CODE  WITHOUT  THE EXPRESS WRITTEN CONSENT OF COMPANY IS STRICTLY PROHIBITED, AND IN VIOLATION OF APPLICABLE
/// LAWS AND INTERNATIONAL TREATIES.  THE RECEIPT OR POSSESSION OF  THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
/// TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT  MAY DESCRIBE, IN WHOLE OR IN PART.
///


#include "utility/inc/StringUtils.hpp"
#include "utility/inc/FileUtils.hpp"
#include "utility/inc/Exception.hpp"

#include <chrono>

#ifdef _WIN32
#   include <windows.h>
#   include <shlobj.h>
#   include <Lmcons.h>
#else
#   include <dirent.h>
#   include <unistd.h>
#   include <libgen.h>
#   include <sys/types.h>
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <pwd.h>
#   include <dlfcn.h>
#endif
#ifndef c_MAX_PATH
#define c_MAX_PATH 1024
#endif

namespace cbtek {
namespace common {
namespace utility {
namespace SystemUtils {

static inline std::uint64_t getCurrentMilliseconds()
{
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}



static inline std::string getUserHomeDirectory()
{
#ifdef _WIN32
    char dir[c_MAX_PATH];

    SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, dir);

    std::string dirStr(dir);
    StringUtils::replaceInPlace(dirStr,"\\","/");
    return dirStr;
#else
    return std::string(getenv("HOME"));
#endif
}

static inline std::string getUserAppDirectory()
{
#ifdef _WIN32
    char dir[c_MAX_PATH];

    SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, dir);

    std::string dirStr(dir);
    StringUtils::replaceInPlace(dirStr,"\\","/");
    return dirStr;
#else
    return getUserHomeDirectory() + "/.local/share"; // TODO: Reconsider this
#endif
}

static inline std::string getUserTempDirectory()
{
#ifdef _WIN32
    char dir[c_MAX_PATH];

    GetTempPathA(c_MAX_PATH, dir);
    GetLongPathNameA(dir, dir, c_MAX_PATH);

    std::string dirStr(dir);
    StringUtils::replaceInPlace(dirStr,"\\","/");
    return dirStr;
#else
    return std::string("/tmp");
#endif
}

static inline std::string getUserName()
{
#ifdef _WIN32
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserNameA(username, &username_len);
    return std::string(username);
#else
    struct passwd *passwd;
    passwd =getpwuid ( getuid());
    return std::string(passwd->pw_name);
#endif
}

static inline int execute(const std::string &command)
{
    int retCode = system(command.c_str());  //one day this will do more
    return retCode;
}

static inline std::string getCurrentDirectory()
{
    char dir[c_MAX_PATH];
    #ifdef _WIN32
        GetCurrentDirectoryA(MAX_PATH, dir);
    #else
        char * ret = getcwd(dir, c_MAX_PATH);
        if (ret)
        {
            delete ret;
        }
    #endif
    return std::string(dir);
}

static inline std::string getApplicationDirectory()
{
    std::string appPath;
    char buffer[PATH_MAX];
    #ifdef _WIN32
        GetModuleFileNameA(NULL,buffer,256);
        appPath = std::string(buffer);
        appPath = FileUtils::getDirPath(appPath);

    #else  
        ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
        if (len != -1)
        {
          buffer[len] = '\0';
          appPath = std::string(buffer);
        }
        //Fix to remove exe name
        appPath = FileUtils::getDirPath(appPath);
    #endif
    return appPath;
}
}}}}//end namespace

