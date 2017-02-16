/**
MIT License

Copyright (c) 2016 cbtek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef _CBTEK_COMMON_UTILITY_FILEUTILS_HPP_
#define _CBTEK_COMMON_UTILITY_FILEUTILS_HPP_

#include <string>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include "Random.h"
#include "StringUtils.hpp"
#include "Exception.hpp"
#include "TimeUtils.hpp"

#ifdef _WIN32
#   include <windows.h>
#   include <shlobj.h>
#   include <Lmcons.h>
#else
#   include <fts.h>
#   include <dirent.h>
#   include <unistd.h>
#   include <sys/types.h>
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <pwd.h>
#endif

namespace cbtek {
namespace common {
namespace utility {
namespace FileUtils {

#ifdef _WIN32
    extern "C" WINBASEAPI DWORD WINAPI GetLongPathNameA(LPCSTR,LPSTR,DWORD);
#endif
#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

/**
 * @brief Prepares a directory for searching. This is really
 * only required for windows. On non windows systems dirPath
 * is returned.
 * @param dirPath Path to file or directory
 * @return Formated version of dirPath that is ready
 * for directory searching
 */

inline std::string getSearchPath(const std::string & dirPath)
{
#ifdef _WIN32
    std::string path(dirPath);
    if(path[path.size()-1] != '*')
    {
        if(path[path.size()-1] != '/' && path[path.size()-1] != '\\')
        {
            path += '/';
        }

        path += '*';
    }
    return path;
#else
    return dirPath;

#endif
}


/**
 * @brief Determines if given filePath is a directory
 * @param filePath Path to file or directory
 * @return true if filePath is directory, false otherwise
 */
inline bool isDirectory(const std::string &filePath)
{
#ifdef _WIN32
    DWORD attr;

    if(filePath.size() && (attr = GetFileAttributesA(filePath.c_str())) != INVALID_FILE_ATTRIBUTES)
    {
        if(attr & FILE_ATTRIBUTE_DIRECTORY)
        {
            return true;
        }
    }

#else
    struct stat si;

    if(filePath.size() && (stat(filePath.c_str(), &si)) == 0)
    {
        if(S_ISDIR(si.st_mode))
        {
            return true;
        }
    }
#endif

    return false;
}


///
/// @brief Checks if a file exists
/// @param filePath Full path to the file
/// @return true or false for if the file exists or does not exist
///
inline bool fileExists(const std::string & filePath)
{
    if (FILE *file = fopen(filePath.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
///
/// @brief This function returns all lines from the file as a vector
///        of strings.
/// @param filePath Full path to the location to read the file
/// @param[out] fileLines Reference to an output vector that will contain all
///             line strings from the file
/// @return Return true if file read was successful
///
inline bool getFileLines(const std::string &filePath,
                         std::vector<std::string> &fileLinesOut)
{
    if (!fileExists(filePath))
    {
        return false;
    }
    std::fstream in(filePath.c_str());
    std::string line;
    bool hasData=false;
    while(in)
    {
        std::getline(in,line);
        if (!in)
        {
            break;
        }
        hasData=true;
        fileLinesOut.push_back(line);
    }
    in.close();

    return hasData;
}

///
/// @brief This function returns all lines from the file as a vector
///        of strings
/// @param filePath Full path to the file to open
/// @return vector of strings where each element is a line from the file
///
inline std::vector<std::string> getFileLines(const std::string &filePath)
{
    std::vector<std::string> lines;
    getFileLines(filePath,lines);
    return lines;
}

///
/// @brief This function returns all characters from a file as a string
/// @param filePath Full path to the file to open
/// @param[out] data std::string of all data from filePath
///
inline void getFileContents(const std::string &filePath, std::string &data)
{
    std::fstream in(filePath.c_str());

    while(in)
    {
        char c=(static_cast<char>(in.get()));
        if (!in)
        {
            break;
        }
        data.push_back(c);
    }
    in.close();
}



///
/// @brief This function returns all characters from a file as a string
/// @param filePath Full path to the file to open
/// @return std::string containing all data from the given file
///
inline std::string getFileContents(const std::string &filePath)
{
    std::string data;
    getFileContents(filePath,data);
    return data;
}

/**
 * @brief getRawFileContents
 * @param filePath
 * @param dataOut
 */
inline void getRawFileContents(const std::string &filePath, std::vector<char> &dataOut)
{
    size_t length;
    FILE * rawFilePtr = fopen (filePath.c_str(), "rb");
    if (rawFilePtr)
    {
        fseek (rawFilePtr, 0, SEEK_END);
        length = ftell (rawFilePtr);
        fseek (rawFilePtr, 0, SEEK_SET);
        dataOut.resize(length);
        fread (&dataOut[0], 1, length, rawFilePtr);
        fclose (rawFilePtr);
    }
}


///
/// @brief Writes the contents of data to a file at filePath
/// @param filePath Location on disk to write the data
/// @param data The data to be written
/// @return Return true upon successful writing, false otherwise
///
inline bool writeFileContents(const std::string &filePath,
                                  const std::string &data)
{
    std::ofstream out(filePath.c_str());
    bool success=false;
    if (out)
    {
        out << data;
        success=true;
    }
    out.close();
    return success;
}


////
/// @brief appendToFile
/// @param filePath
/// @param dataToAppend
/// @return
///
inline bool appendToFile(const std::string & filePath,
                         const std::string & dataToAppend)
{

    std::ofstream out(filePath.c_str(),std::ios::app);
    if (out.is_open())
    {
        out << dataToAppend;
        out.close();
        return true;
    }
    return false;
}

/**
 * @brief This function opens output stream to a binary file
 * @param filePath The path to the filePath to write
 * @param[out] out The reference to the output stream
 * @return Returns true if the file was opened, false otherwise
 */
inline bool openBinaryFileForWrite(const std::string &filePath,
                                       std::ofstream &out)
{
    out.open(filePath.c_str(),std::ios::binary);
    return(out.is_open());
}

/**
 * @brief This function opens input stream to a binary file
 * @param filePath The filePath to read
 * @param[out] in The reference to the input stream
 * @return Returns true if the file was opened, false otherwise
 */
inline bool openBinaryFileForRead(const std::string &filePath,
                                      std::ifstream &in)
{
    in.open(filePath.c_str(),std::ios::binary);
    return(in.is_open());
}

/**
 * @brief This function opens input stream to a text file
 * @param filePath The filePath to read
 * @param[out] in The reference to the input stream
 * @return Returns true if the file was opened, false otherwise
 */
inline bool openTextFileForRead(const std::string &filePath,
                                std::ifstream &in)
{
    in.open(filePath.c_str());
    return(in.is_open());
}

/**
 * @brief This function opens an output stream to a text file
 * @param filePath The path to the filePath to write
 * @param[out] out The reference to the output stream
 * @return Returns true if the file was opened, false otherwise
 */
inline bool openTextFileForWrite(const std::string &filePath,
                                     std::ofstream &out)
{
    out.open(filePath.c_str());
    return(out.is_open());
}

/**
 * @brief Constructs a full file path from a directory
 * path and filename.
 * @param dirPath A directory path (eg. C:\windows, /usr/lib/,etc)
 * @param fileName A file name (eg. test.xml,  run.bat, /exits/exit.bat,etc)
 * @return Constructed file path with system path seperators
 */
inline std::string buildFilePath(const std::string &dirPath, const std::string &fileName)
{
    std::string pathSep,file,dir;

    if (StringUtils::trimmed(dirPath).size()==0)
    {
        return fileName;
    }

#   ifdef __WIN32
    pathSep = "\\";
    dir = StringUtils::replace(dirPath,"/",pathSep);
    file= StringUtils::replace(fileName,"/",pathSep);
#   else
    pathSep = "/";
    dir = StringUtils::replace(dirPath,"\\",pathSep);
    file= StringUtils::replace(fileName,"\\",pathSep);
#   endif

    size_t pathHasSep=
            StringUtils::endsWith(StringUtils::trimmed(dir),pathSep);

    size_t fileHasSep=
            StringUtils::startsWith(StringUtils::trimmed(fileName),pathSep);


    if (pathHasSep || fileHasSep)
    {
       if (pathHasSep && fileHasSep)
       {
           int dirSize = static_cast<int>(dir.size());
           for(int a1 = dirSize-1;a1 >= 0;--a1)
           {
               if (dir[a1]==' ')
               {
                   continue;
               }
               else if (dir[a1]==pathSep[0])
               {
                   dir.erase(dir.begin()+a1);
                   break;
               }
           }
       }
        return dir+fileName;
    }
    else
    {
       return dir+pathSep+fileName;
    }
}

/**
 * @brief Get list of files from directory
 * @param dirPath Path to directory
 * @param recursive Enables recursive search of files in dirPath
 * @param keepFullPath Appends the dirPath to the file entry
 * @param filteredExtensions List of extensions to search for. Example:
 * txt, mp3, doc, etc
 * @param[out] entryListOut List of files from dirPath.
 * This excludes the .. and . path symbols.*
 */
inline void getFileEntries(const std::string &dirPath,
                           bool keepFullPath,
                           const std::vector<std::string> & filteredExtensions,
                           std::vector<std::string> & entryListOut)
{

        std::string     path = getSearchPath(dirPath);
        #ifdef _WIN32
        {
            HANDLE h;
            WIN32_FIND_DATAA fdat;

            h = FindFirstFileA(path.c_str(), &fdat);

            if(INVALID_HANDLE_VALUE == h)
            {
                return;
            }

            do
            {
                std::string fileOrFolder(fdat.cFileName);
                if (!filteredExtensions.empty() && !StringUtils::endsWithMultiple(fileOrFolder,filteredExtensions,false))
                {
                    continue;
                }

                entryListOut.push_back( fdat.cFileName);
                if (keepFullPath)
                {
                    entryListOut[entryListOut.size()-1] =
                            buildFilePath(dirPath,entryListOut.back());
                }
            } while (FindNextFileA(h, &fdat) != 0);

            FindClose(h);
            StringUtils::removeAllThatEndWith(entryListOut,"\\.");
            StringUtils::removeAllThatEndWith(entryListOut,"\\..");
        }
        #else
        {
            DIR*   dir = opendir(path.c_str());
            struct dirent* dp;

            if(NULL == dir)
            {
                return;
            }

            while((dp = readdir(dir)) != NULL)
            {
                std::string fileOrFolder(dp->d_name);
                if (!filteredExtensions.empty() && !StringUtils::endsWithMultiple(fileOrFolder,filteredExtensions,false))
                {
                    continue;
                }

                entryListOut.push_back(dp->d_name);
                if (keepFullPath)
                {
                    entryListOut[entryListOut.size()-1] =
                    buildFilePath(dirPath,entryListOut.back());
                }

            }
            closedir(dir);
            StringUtils::removeAllThatEndWith(entryListOut,"/.");
            StringUtils::removeAllThatEndWith(entryListOut,"/..");
        }
        #endif

}
inline void getRecursiveFolders(const std::string & dirPath,
                                std::set<std::string> & folders)
{
    std::vector<std::string> entryListOut;
    getFileEntries(dirPath,true,std::vector<std::string>(),entryListOut);

    for (const std::string & folder : entryListOut)
    {
        if (isDirectory(folder))
        {
            folders.insert(folder);
            getRecursiveFolders(folder,folders);
        }
    }
}

/**
 * @brief getRecursiveFileEntries
 * @param dirPath
 * @param extensionFilters
 * @param entryListOut
 */
inline void getRecursiveFileEntries(const std::string &dirPath,
                                    const std::vector<std::string> & extensionFilters,
                                    std::vector<std::string> & entryListOut)
{
    std::set<std::string> folders;
    getRecursiveFolders(dirPath,folders);
    for(const std::string & folder : folders)
    {
        getFileEntries(folder,true,extensionFilters,entryListOut);
    }
}




/**
 * @brief Returns the directory portion of a filePath
 * @param filePath The full path to a file
 * @return directory of filePath
 */
inline std::string getDirPath(const std::string &filePath)
{
    std::string universalFilePath = StringUtils::replace(filePath,"\\","/");
    size_t index = 0;

    if((index = universalFilePath.find_last_of('/')) != std::string::npos)
    {
        return universalFilePath.substr(0, index+1);
    }
    return "";
}

/**
 * @brief Returns the filename portion of full file path
 * @param filePath The full path to a file
 * @return Returns the filename portion of filePath
 */
inline std::string getFileName(const std::string &filePath)
{
    std::string universalFilePath = StringUtils::replace(filePath,"\\","/");
    size_t index=0;

    if((index = universalFilePath.find_last_of('/')) != std::string::npos)
    {
       return universalFilePath.substr(index+1);
    }
    return "";
}

/**
 * @brief Computes the total size (in bytes) of the file
 * at filePath
 * @param filePath Full path to the file
 * @return Returns the size of filePath in bytes
 */

inline std::uint64_t getFileSize(const std::string &filePath)
{
    std::ifstream in(filePath.c_str(),
                     std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

/**
 * @brief getCurrentPath
 * @return
 */
inline std::string getCurrentPath()
{
    char dir[MAX_PATH];
    #ifdef _WIN32
        GetCurrentDirectoryA(MAX_PATH, dir);
    #else
        getcwd(dir, MAX_PATH);
    #endif
        return std::string(dir);
}





/**
 * @brief This function copies a file from a source to its destination
 * @param sourceFile The location of the source file
 * @param destinationFile The location of the destination file
 * @throws FileNotFoundException if either the source or destination file
 * location is invalid
 */
inline void copyFile(const std::string & sourceFile, const std::string & destinationFile)
{
    std::ifstream  src(sourceFile.c_str(),        std::ios::binary);
    std::ofstream  dst(destinationFile.c_str(),   std::ios::binary);
    if (!src.is_open())
    {
        std::string msg = EXCEPTION_TAG+"Could not open source file at \""+sourceFile+"\"";
        throw FileNotFoundException(msg);
    }
    if (!dst.is_open())
    {
        std::string msg = EXCEPTION_TAG+"Could not open destination file at \""+destinationFile+"\"";
        throw FileNotFoundException(msg);
    }
    dst << src.rdbuf();

}

/**
 * @brief remove
 * @param sourceFile
 */
inline void deleteFile(const std::string & sourceFile)
{
    if (FileUtils::fileExists(sourceFile))
    {
        if( remove(sourceFile.c_str()) != 0 )
        {
            std::string msg = EXCEPTION_TAG+"Could not remove file at \""+sourceFile+"\"";
            throw FileAccessException(msg);
        }
    }
}

inline void createDirectory(const std::string &dirPath)
{
    int nError=0;
    #if defined(_WIN32)
        CreateDirectory(dirPath.c_str(), NULL);
        nError = GetLastError();
    #else
        nError = mkdir(dirPath.c_str(),0733);
    #endif
}

inline void writeRawContentsToFile(const std::string & filePath,const char * buffer, size_t bufferSize)
{
    std::ofstream out(filePath.c_str(),std::ios::out | std::ios::binary);
    if (out.is_open())
    {
        out.close();
        throw FileAccessException(EXCEPTION_TAG+"Could not open file for write at \""+filePath+"\"");
    }
    out.write(buffer,bufferSize);
    out.close();
}

inline void renameFile(const std::string &oldFilePath, const std::string &newFilePath)
{
    std::rename(oldFilePath.c_str(),newFilePath.c_str());
}

inline std::string getRandomFolderName(int length)
{
    Random rnd;
    rnd.reseed((std::uint64_t)TimeUtils::getMillisecondsNow() + TimeUtils::getSecondsNow());
    std::string file;
    for (size_t a1 = 0;a1<length;++a1)
    {
        if (rnd.next(100) > 75)
        {
            file.push_back(rnd.next('a','z'));
        }
        else if (rnd.next(100) > 50)
        {
            file.push_back(rnd.next('A','Z'));
        }
        else if (rnd.next(100) > 25)
        {
            file.push_back(rnd.next('0','9'));
        }
        else
        {
            file.push_back(rnd.next('A','F'));
        }
    }
    return file;
}

inline std::string getRandomFileName(int length, int extensionLength)
{
    Random rnd;
    rnd.reseed((std::uint64_t)TimeUtils::getMillisecondsNow() + TimeUtils::getSecondsNow());

    std::string file = getRandomFolderName(length);
    file.push_back('.');
    for (size_t a1 = 0;a1<extensionLength;++a1)
    {
        if (rnd.next(100) > 75)
        {
            file.push_back(rnd.next('a','z'));
        }
        else if (rnd.next(100) > 50)
        {
            file.push_back(rnd.next('A','Z'));
        }
        else if (rnd.next(100) > 25)
        {
            file.push_back(rnd.next('0','9'));
        }
        else
        {
            file.push_back(rnd.next('F','Z'));
        }
    }
    return file;
}

inline std::string getFileExtension(const std::string & filePath)
{
    std::string ext;
    for (int a1 = filePath.size()-1;a1>=0;--a1)
    {
        if(filePath[a1]=='.')
        {
            break;
        }
        ext.push_back(filePath[a1]);
    }
    return ext;
}

inline int deleteFolder(const std::string &dirPath)
{

#ifdef __WIN32
    std::string refcstrRootDirectory = StringUtils::replace(dirPath,"/","\\");
    bool bDeleteSubdirectories = true;

    bool            bSubdirectory = false;       // Flag, indicating whether
                                               // subdirectories have been found
    HANDLE          hFile;                       // Handle to directory
    std::string     strFilePath;                 // Filepath
    std::string     strPattern;                  // Pattern
    WIN32_FIND_DATA FileInformation;             // File information


    strPattern = refcstrRootDirectory + "\\*.*";
    hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
    if(hFile != INVALID_HANDLE_VALUE)
    {
    do
    {
      if(FileInformation.cFileName[0] != '.')
      {
        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

        if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          if(bDeleteSubdirectories)
          {
            // Delete subdirectory
            int iRC = deleteFolder(strFilePath);
            if(iRC)
              return iRC;
          }
          else
            bSubdirectory = true;
        }
        else
        {
          // Set file attributes
          if(::SetFileAttributes(strFilePath.c_str(),
                                 FILE_ATTRIBUTE_NORMAL) == FALSE)
            return ::GetLastError();

          // Delete file
          if(::DeleteFile(strFilePath.c_str()) == FALSE)
            return ::GetLastError();
        }
      }
    } while(::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if(dwError != ERROR_NO_MORE_FILES)
      return dwError;
    else
    {
      if(!bSubdirectory)
      {
        // Set directory attributes
        if(::SetFileAttributes(refcstrRootDirectory.c_str(),FILE_ATTRIBUTE_NORMAL) == FALSE)
        {
            return ::GetLastError();
        }

        // Delete directory
        if(::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
        {
           return ::GetLastError();
        }

      }
    }
   }

  return 0;
#else
    const char *dir = dirPath.c_str();
        int ret = 0;
        FTS *ftsp = NULL;
        FTSENT *curr;

        // Cast needed (in C) because fts_open() takes a "char * const *", instead
        // of a "const char * const *", which is only allowed in C++. fts_open()
        // does not modify the argument.
        char *files[] = { (char *) dir, NULL };

        // FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
        //                in multithreaded programs
        // FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
        //                of the specified directory
        // FTS_XDEV     - Don't cross filesystem boundaries
        ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
        if (!ftsp) {
            fprintf(stderr, "%s: fts_open failed: %s\n", dir, strerror(errno));
            ret = -1;
            goto finish;
        }

        while ((curr = fts_read(ftsp))) {
            switch (curr->fts_info) {
            case FTS_NS:
            case FTS_DNR:
            case FTS_ERR:
                fprintf(stderr, "%s: fts_read error: %s\n",
                        curr->fts_accpath, strerror(curr->fts_errno));
                break;

            case FTS_DC:
            case FTS_DOT:
            case FTS_NSOK:
                // Not reached unless FTS_LOGICAL, FTS_SEEDOT, or FTS_NOSTAT were
                // passed to fts_open()
                break;

            case FTS_D:
                // Do nothing. Need depth-first search, so directories are deleted
                // in FTS_DP
                break;

            case FTS_DP:
            case FTS_F:
            case FTS_SL:
            case FTS_SLNONE:
            case FTS_DEFAULT:
                if (remove(curr->fts_accpath) < 0) {
                    fprintf(stderr, "%s: Failed to remove: %s\n",
                            curr->fts_path, strerror(errno));
                    ret = -1;
                }
                break;
            }
        }

    finish:
        if (ftsp) {
            fts_close(ftsp);
        }

        return ret;

#endif

}
}}}}
#endif // _CBTEK_COMMON_UTILITY_FILEUTILS_HPP_
