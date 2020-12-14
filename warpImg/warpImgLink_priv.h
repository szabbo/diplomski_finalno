#ifndef _WARPIMG_LINK_PRIV_H_
#define _WARPIMG_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_warpImg.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/utils_common/include/utils_prf.h>
#include "iWarpImg.h"
#include <src/utils_common/include/utils_link_stats_if.h>

#define FRAMECOPY_LINK_MAX_FRAMES (10)
typedef struct
{
    Alg_WarpImg_Obj * algHandle;
    /**< Handle of the algorithm */
    System_LinkOutQueParams outQueParams;
    /**< Output queue information */
    System_LinkInQueParams inQueParams;
    /**< Input queue information */
    System_LinkChInfo inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Input channel information */
    UInt32 numInputChannels;
    /**< Number of input channels */
    Alg_WarpImgCreateParams createParams;
    /**< Create params of the color to gray algorithm */
    Alg_WarpImgControlParams controlParams;
    /**< Control params of the color to gray algorithm */
    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Q */
    System_LinkStatistics *linkStatsInfo;
    /**< Pointer to the Link statistics information,
    used to store below information
    1, min, max and average latency of the link
    2, min, max and average latency from source to this link
    3, links statistics like frames captured, dropped etc
    Pointer is assigned at the link create time from shared
    memory maintained by utils_link_stats layer */
    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
    * to start stats counting
    */
} AlgorithmLink_WarpImgObj;

Int32 AlgorithmLink_WarpImgCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_WarpImgProcess(void * pObj);
Int32 AlgorithmLink_WarpImgControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_WarpImgStop(void * pObj);
Int32 AlgorithmLink_WarpImgDelete(void * pObj);
Int32 AlgorithmLink_WarpImgPrintStatistics(void *pObj, AlgorithmLink_WarpImgObj *pWarpImgObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
