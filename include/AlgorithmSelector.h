#pragma once

#include "Algorithm.h"

class AlgorithmSelector
{
public:
    static Algorithm select(int requestRate, int rejectionRate);
};