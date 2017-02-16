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

#ifndef _CBTEK_COMMON_UTILITY_RANDOM_H_
#define _CBTEK_COMMON_UTILITY_RANDOM_H_

#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>

#include "UtilityCommon.hpp"

namespace cbtek {
namespace common {
namespace utility {

class CBTEK_UTILS_DLL Random
{
public:
    /**
     * @brief Random
     * @param seed
     */
    Random(long seed=0xABCDEF);

    /**
     * @brief reseed
     * @param seed
     */
    void reseed(long seed);


    /**
     * @brief random
     * @return
     */
    double random();

    /**
     * @brief next
     * @param min
     * @param max
     * @return
     */
    int next(int  min, int max);

    /**
     * @brief next
     * @param max
     * @return
     */
    int next(int  max);

private:
    long m_ix,m_iy,m_iz;
    double m_mx,m_my,m_mz;
};

}}}//namespace
#endif // _CBTEK_COMMON_UTILITY_RANDOM_H_
