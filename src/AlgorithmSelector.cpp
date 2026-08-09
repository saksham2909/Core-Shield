#include "AlgorithmSelector.h"

Algorithm AlgorithmSelector::select(int requestRate, int rejectionRate)
{
    if (rejectionRate > 50)
        return Algorithm::TokenBucket;

    if (requestRate > 1000)
        return Algorithm::FixedWindow;

    return Algorithm::SlidingWindow;
}