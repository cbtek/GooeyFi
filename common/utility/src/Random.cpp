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

#include "Random.h"

namespace cbtek {
namespace common {
namespace utility {

Random::Random(long seed) : m_ix(9123),m_iy(8844),m_iz(20846)
{
    reseed(seed);
    m_mx=1/30269.0;m_my=1/30307.0;m_mz=1/30323.0;
}

void Random::reseed(long seed)
{
    srand(seed);
    m_ix=rand();
    m_iy=rand();
    m_iz=rand();
}

double Random::random()
{
    m_ix = fmod(171*m_ix,30269);
    m_iy = fmod(172*m_iy,20207);
    m_iz = fmod(170*m_iz,30323);
    double modValue=(((double)m_ix)*m_mx+((double)m_iy)*m_my+((double)m_iz)*m_mz);
    double value = fmod(modValue,1.);
    if (value < 0)
    {
        value*=-1;
    }
    return value;
}

int Random::next(int mn, int mx)
{
	if (mn==mx)return mn;
    int max=mx;
    int min=mn;
    max++;
    if (min < 0)
    {
        min*=-1;
        max = max + min;
        double rng=random();
        int value = (int)((rng*(max)));
        return (value-min);
    }

    double rng=random();
    return (int)(rng*(max-min))+min;
}

int Random::next(int max)
{
    return next(0,max);
}

}}}//namespace
