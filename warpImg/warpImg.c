#include "iWarpImg.h"
#include <src/utils_common/include/utils_mem.h>

#include <math.h>

UInt8 *outputPtr = NULL;
UInt8 *streamPtr = NULL;
Int8 *lookupTable = NULL;
long double *warpPtr = NULL;
long double *invWarpPtr = NULL;

Void setWarpMatrix(long double *warpPtr)
{
    // obicna
    *(warpPtr + (0 * 3) + 0) = (9.60022834e-01);
    *(warpPtr + (0 * 3) + 1) = (1.24821787e-01);
    *(warpPtr + (0 * 3) + 2) = (-1.07066767e+02);

    *(warpPtr + (1 * 3) + 0) = (-1.50211998e-01);
    *(warpPtr + (1 * 3) + 1) = (9.52174035e-01);
    *(warpPtr + (1 * 3) + 2) = (6.89422372e+01);

    *(warpPtr + (2 * 3) + 0) = (-1.54474943e-05);
    *(warpPtr + (2 * 3) + 1) = (-3.13154044e-05);
    *(warpPtr + (2 * 3) + 2) = (1.00000000e+00);
}

Void setInvWarpMatrix(long double *invWarpPtr)
{
    // inverzna
    *(invWarpPtr + (0 * 3) + 0) = (1.02317221e+00);
    *(invWarpPtr + (0 * 3) + 1) = (-1.30230909e-01);
    *(invWarpPtr + (0 * 3) + 2) = (1.18526151e+02);

    *(invWarpPtr + (1 * 3) + 0) = (1.59905485e-01);
    *(invWarpPtr + (1 * 3) + 1) = (1.02749927e+00);
    *(invWarpPtr + (1 * 3) + 2) = (-5.37175350e+01);

    *(invWarpPtr + (2 * 3) + 0) = (2.08129519e-05);
    *(invWarpPtr + (2 * 3) + 1) = (3.01648139e-05);
    *(invWarpPtr + (2 * 3) + 2) = (1.00014875e+00);
}

Void warpImg(long double *warpPtr, int *oldCrd, int *newCrd)
{
    *(newCrd + 0) = (int)round((*(warpPtr + (0 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (0 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (0 * 3) + 2) * *(oldCrd + 2)));
    *(newCrd + 1) = (int)round((*(warpPtr + (1 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (1 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (1 * 3) + 2) * *(oldCrd + 2)));
    *(newCrd + 2) = (int)round((*(warpPtr + (2 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (2 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (2 * 3) + 2) * *(oldCrd + 2)));

    if (*(newCrd + 0) < 0)
        *(newCrd + 0) = (int)0;
    else if (*(newCrd + 0) > 2560)
        *(newCrd + 0) = (int)2560;

    if (*(newCrd + 1) < 0)
        *(newCrd + 1) = (int)0;
    else if (*(newCrd + 1) > 720)
        *(newCrd + 1) = (int)720;
}

Void matrixMultiDouble(long double *warpPtr, int *oldCrd, double *newCrd)
{
    *(newCrd + 0) = (*(warpPtr + (0 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (0 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (0 * 3) + 2) * *(oldCrd + 2));
    *(newCrd + 1) = (*(warpPtr + (1 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (1 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (1 * 3) + 2) * *(oldCrd + 2));
    *(newCrd + 2) = (*(warpPtr + (2 * 3) + 0) * *(oldCrd + 0)) + (*(warpPtr + (2 * 3) + 1) * *(oldCrd + 1)) + (*(warpPtr + (2 * 3) + 2) * *(oldCrd + 2));
}

Void nearestNeighbors(int colIdx, int rowIdx, UInt8 *streamPtr, long double *invMatH, UInt8 *pixel)
{
    int oldCrd[3];
    double newCrd[3];
    int xMax = 2560, yMax = 720;
    int tmpCrd[2];
    oldCrd[0] = colIdx;
    oldCrd[1] = rowIdx;
    oldCrd[2] = 1;

    matrixMultiDouble(invMatH, oldCrd, newCrd);

    if (floor(newCrd[0]) == newCrd[0] && floor(newCrd[1]) == newCrd[1])
    {
        tmpCrd[0] = (int)round(newCrd[0]);
        tmpCrd[1] = (int)round(newCrd[1]);

        if (colIdx % 4 == 0)
        {
            while (tmpCrd[0] % 4 != 0)
            {
                tmpCrd[0] -= 1;

                if (tmpCrd[0] < 4)
                {
                    tmpCrd[0] = 0;
                }
            }

            *(pixel + 0) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0]);
            *(pixel + 1) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 1);
            *(pixel + 2) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 3);
        }
        else if (colIdx % 4 == 2)
        {
            while (tmpCrd[0] % 4 != 2)
            {
                tmpCrd[0] -= 1;

                if (tmpCrd[0] < 6)
                {
                    tmpCrd[0] = 2;
                }
            }

            *(pixel + 0) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0]);
            *(pixel + 1) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] - 1);
            *(pixel + 2) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 1);
        }
    }

    if (abs(floor(newCrd[0]) - newCrd[0]) < abs(ceil(newCrd[0]) - newCrd[0]))
    {
        tmpCrd[0] = (int)floor(newCrd[0]);
    }
    else
    {
        tmpCrd[0] = (int)ceil(newCrd[0]);
    }
    
    if (abs(floor(newCrd[1]) - newCrd[1]) < abs(ceil(newCrd[1]) - newCrd[1]))
    {
        tmpCrd[1] = (int)floor(newCrd[1]);
    }
    else
    {
        tmpCrd[1] = (int)ceil(newCrd[1]);
    }

    if (tmpCrd[0] > xMax)
    {
        tmpCrd[0] = xMax;
    }

    if (tmpCrd[1] > yMax)
    {
        tmpCrd[1] = yMax;
    }

    if (colIdx % 4 == 0)
    {
        while (tmpCrd[0] % 4 != 0)
        {
            tmpCrd[0] -= 1;

            if (tmpCrd[0] < 4)
            {
                tmpCrd[0] = 0;
            }
        }

        *(pixel + 0) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0]);
        *(pixel + 1) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 1);
        *(pixel + 2) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 3);
    }
    else if (colIdx % 4 == 2)
    {
        while (tmpCrd[0] % 4 != 2)
        {
            tmpCrd[0] -= 1;

            if (tmpCrd[0] < 6)
            {
                tmpCrd[0] = 2;
            }

        }

        *(pixel + 0) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0]);
        *(pixel + 1) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] - 1);
        *(pixel + 2) = *(streamPtr + (2560 * tmpCrd[1]) + tmpCrd[0] + 1);
    }
}

Void fixMissingPixels(UInt8 *outputPtr, UInt8 *streamPtr, Int8 *lookupTable)
{
    int colIdx;
    int rowIdx;
    UInt8 pixel[3];

    // Y
    for (rowIdx = 0; rowIdx < 720; rowIdx++)
    {
        // X
        for (colIdx = 2; colIdx < 2560; colIdx += 2)
        {
            if (colIdx % 4 == 0)
            {
                if (*(lookupTable + (2560 * rowIdx) + colIdx) != -1 && (*(lookupTable + (2560 * rowIdx) + colIdx - 2) == -1 || *(lookupTable + (2560 * rowIdx) + colIdx + 2) == -1))
                {
                    nearestNeighbors(colIdx, rowIdx, streamPtr, invWarpPtr, pixel);

                    *(outputPtr + (2560 * rowIdx) + colIdx) = *(pixel + 0);
                    *(outputPtr + (2560 * rowIdx) + colIdx + 2) = *(pixel + 1);
                    *(outputPtr + (2560 * rowIdx) + colIdx + 3) = *(pixel + 2);
                }
            }
            else if (colIdx % 4 == 2)
            {
                if (*(lookupTable + (2560 * rowIdx) + colIdx) != -1 && (*(lookupTable + (2560 * rowIdx) + colIdx - 2) == -1 || *(lookupTable + (2560 * rowIdx) + colIdx + 2) == -1))
                {
                    nearestNeighbors(colIdx, rowIdx, streamPtr, invWarpPtr, pixel);

                    *(outputPtr + (2560 * rowIdx) + colIdx) = *(pixel + 0);
                    *(outputPtr + (2560 * rowIdx) + colIdx - 2) = *(pixel + 1);
                    *(outputPtr + (2560 * rowIdx) + colIdx + 2) = *(pixel + 2);
                }
            }
        }
    }
}

Void setToZero(Int8 *lookupTable)
{
    int colIdx, rowIdx;
    // Y
    for (rowIdx = 0; rowIdx < 720; rowIdx++)
        // X
        for (colIdx = 0; colIdx < 2560; colIdx++)
            *(lookupTable + (2560 * rowIdx) + colIdx) = 0;
}

Alg_WarpImg_Obj * Alg_WarpImgCreate(Alg_WarpImgCreateParams *pCreateParams)
{
    Alg_WarpImg_Obj * pAlgHandle;

    pAlgHandle = (Alg_WarpImg_Obj *) malloc(sizeof(Alg_WarpImg_Obj));
    UTILS_assert(pAlgHandle != NULL);

    warpPtr = Utils_memAlloc(UTILS_HEAPID_DDR_NON_CACHED_SR0, 9, sizeof(long double));
    UTILS_assert(warpPtr != NULL);

    setWarpMatrix(warpPtr);

    invWarpPtr = Utils_memAlloc(UTILS_HEAPID_DDR_NON_CACHED_SR0, 9, sizeof(long double));
    UTILS_assert(invWarpPtr != NULL);

    setInvWarpMatrix(invWarpPtr);
  
    outputPtr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, 2560 * 720, sizeof(UInt8));
    UTILS_assert(outputPtr != NULL);

    streamPtr = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, 2560 * 720, sizeof(UInt8));
    UTILS_assert(streamPtr != NULL);

    lookupTable = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, 2560 * 720, sizeof(UInt8));
    UTILS_assert(lookupTable != NULL);

    return pAlgHandle;
}

Int32 Alg_WarpImgProcess(Alg_WarpImg_Obj *algHandle, UInt8 *inPtr[], UInt32 width, UInt32 height, UInt32 inPitch[], UInt32 dataFormat)
{
    UInt8 *inputPtr;
    Int32 rowIdx;
    Int32 colIdx;
    int oldCrd[3];
    int newCrd[3];
    inputPtr = inPtr[0];
    int offset = inPitch[0];

    memcpy(&streamPtr, &inPtr[0], sizeof(streamPtr));
    setToZero(lookupTable);
    // Y
    for (rowIdx = 0; rowIdx < height; rowIdx++)
    {        
        // X
        for (colIdx = 0; colIdx < inPitch[0]; colIdx += 2)
        {
            if (colIdx % 4 == 0)
            {
                oldCrd[0] = colIdx;
                oldCrd[1] = rowIdx;
                oldCrd[2] = 1;

                warpImg(warpPtr, oldCrd, newCrd);

                if (newCrd[0] < inPitch[0] && newCrd[1] < height)
                {

                    while (newCrd[0] % 4 != 0)
                    {
                        newCrd[0] += 1;

                        if (newCrd[0] < 4)
                        {
                            newCrd[0] = 0;
                        }                    
                    }
                    
                    *(outputPtr + (newCrd[1] * offset) + newCrd[0]) = *(inputPtr + colIdx);
                    *(outputPtr + (newCrd[1] * offset) + newCrd[0] + 1) = *(inputPtr + colIdx + 1);
                    *(outputPtr + (newCrd[1] * offset) + newCrd[0] + 3) = *(inputPtr + colIdx + 3);
                    
                    *(lookupTable + (newCrd[1] * offset) + newCrd[0]) = -1;
                    *(lookupTable + (newCrd[1] * offset) + newCrd[0] + 1) = -1;
                    *(lookupTable + (newCrd[1] * offset) + newCrd[0] + 3) = -1;
                }
            }

            else if (colIdx % 4 == 2)
            {
                oldCrd[0] = colIdx;
                oldCrd[1] = rowIdx;
                oldCrd[2] = 1;

                warpImg(warpPtr, oldCrd, newCrd);

                if (newCrd[0] < (inPitch[0] - 1) && newCrd[1] < (height - 1))
                {
                    newCrd[0] += 1;
                    while (newCrd[0] % 4 != 2)
                    {
                        newCrd[0] += 1;

                        if (newCrd[0] < 6)
                        {
                            newCrd[0] = 2;
                        }
                    }

                    *(outputPtr + (newCrd[1] * offset) + newCrd[0]) = *(inputPtr + colIdx);
                    *(outputPtr + (newCrd[1] * offset) + newCrd[0] - 1) = *(inputPtr + colIdx - 1);
                    *(outputPtr + (newCrd[1] * offset) + newCrd[0] + 1) = *(inputPtr + colIdx + 1);

                    *(lookupTable + (newCrd[1] * offset) + newCrd[0]) = -1;
                    *(lookupTable + (newCrd[1] * offset) + newCrd[0] - 1) = -1;
                    *(lookupTable + (newCrd[1] * offset) + newCrd[0] + 1) = -1;
                }
            }
        }
        inputPtr += (inPitch[0]);
    }

    fixMissingPixels(outputPtr, inPtr, streamPtr, lookupTable);
    memcpy(&inPtr[0], &outputPtr, sizeof(outputPtr));

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Alg_WarpImgControl(Alg_WarpImg_Obj *pAlgHandle, Alg_WarpImgControlParams *pControlParams)
{
    /*
    * Any alteration of algorithm behavior
    */
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Alg_WarpImgStop(Alg_WarpImg_Obj *algHandle)
{
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Alg_WarpImgDelete(Alg_WarpImg_Obj *algHandle)
{
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, outputPtr, 2560 * 720);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, streamPtr, 2560 * 720);
    Utils_memFree(UTILS_HEAPID_DDR_NON_CACHED_SR0, warpPtr, 9);
    Utils_memFree(UTILS_HEAPID_DDR_NON_CACHED_SR0, invWarpPtr, 9);
    
    free(algHandle);
    return SYSTEM_LINK_STATUS_SOK;
}
