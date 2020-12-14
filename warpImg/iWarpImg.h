#ifndef _IWARPIMG_H_
#define _IWARPIMG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <include/link_api/system.h>
#include <math.h>

typedef struct
{
    UInt32 xxx;
} Alg_WarpImg_Obj;
typedef struct
{
    UInt32 xxxx;
} Alg_WarpImgCreateParams;
typedef struct
{
    UInt32 xxx;
    /**< Any parameters which can be used to alter the algorithm behavior */
} Alg_WarpImgControlParams;

Alg_WarpImg_Obj * Alg_WarpImgCreate(Alg_WarpImgCreateParams *pCreateParams);
Int32 Alg_WarpImgProcess(Alg_WarpImg_Obj *algHandle, UInt8 *inPtr[], UInt32 width, UInt32 height, UInt32 inPitch[], UInt32 dataFormat);
Int32 Alg_WarpImgControl(Alg_WarpImg_Obj *pAlgHandle, Alg_WarpImgControlParams *pControlParams);
Int32 Alg_WarpImgDelete(Alg_WarpImg_Obj *pAlgHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
