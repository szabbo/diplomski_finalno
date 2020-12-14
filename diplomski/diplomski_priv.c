/*
*******************************************************************************
*
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
*
*******************************************************************************
*/

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/
#include "diplomski_priv.h"
Void diplomski_SetLinkId(diplomskiObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->SplitLinkID                    = IPU1_0_LINK (SYSTEM_LINK_ID_SPLIT_0);
       pObj->SelectLinkID                   = IPU1_0_LINK (SYSTEM_LINK_ID_SELECT_0);
       pObj->VPE_2LinkID                    = SYSTEM_LINK_ID_VPE_0;
       pObj->IPCOut_IPU1_0_A15_0_1LinkID    = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_1);
       pObj->IPCIn_A15_0_IPU1_0_0LinkID     = A15_0_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->NullLinkID                     = A15_0_LINK (SYSTEM_LINK_ID_NULL_0);
       pObj->VPE_1LinkID                    = SYSTEM_LINK_ID_VPE_1;
       pObj->IPCOut_IPU1_0_DSP1_0LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_DSP1_IPU1_0_0LinkID      = DSP1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_WarpImgLinkID              = DSP1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->IPCOut_DSP1_IPU1_0_0LinkID     = DSP1_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_IPU1_0_DSP1_0LinkID      = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Display_CFLinkID               = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void diplomski_ResetLinkPrms(diplomskiObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       SplitLink_CreateParams_Init(&pObj->SplitPrm);
       SelectLink_CreateParams_Init(&pObj->SelectPrm);
       VpeLink_CreateParams_Init(&pObj->VPE_2Prm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_A15_0_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_A15_0_IPU1_0_0Prm);
       NullLink_CreateParams_Init (&pObj->NullPrm);
       VpeLink_CreateParams_Init(&pObj->VPE_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_DSP1_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_DSP1_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_DSP1_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_IPU1_0_DSP1_0Prm);
       DisplayLink_CreateParams_Init(&pObj->Display_CFPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void diplomski_SetPrms(diplomskiObj *pObj){
       (pObj->Alg_WarpImgPrm).baseClassCreate.size  = sizeof(AlgorithmLink_WarpImgCreateParams);
       (pObj->Alg_WarpImgPrm).baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_WARPIMG;
       (pObj->SelectPrm).numOutQue = 2;
       (pObj->NullPrm).numInQue = 1;
}

Void diplomski_ConnectLinks(diplomskiObj *pObj){

       //Capture -> Split
       pObj->CapturePrm.outQueParams.nextLink = pObj->SplitLinkID;
       pObj->SplitPrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->SplitPrm.inQueParams.prevLinkQueId = 0;

       //Split -> Select
       pObj->SplitPrm.outQueParams.nextLink = pObj->SelectLinkID;
       pObj->SelectPrm.inQueParams.prevLinkId = pObj->SplitLinkID;
       pObj->SelectPrm.inQueParams.prevLinkQueId = 0;

       //Select -> VPE_1
       pObj->SelectPrm.outQueParams[0].nextLink = pObj->VPE_1LinkID;
       pObj->VPE_1Prm.inQueParams.prevLinkId = pObj->SelectLinkID;
       pObj->VPE_1Prm.inQueParams.prevLinkQueId = 0;

       //Select -> VPE_2
       pObj->SelectPrm.outQueParams[1].nextLink = pObj->VPE_2LinkID;
       pObj->VPE_2Prm.inQueParams.prevLinkId = pObj->SelectLinkID;
       pObj->VPE_2Prm.inQueParams.prevLinkQueId = 1;

       //VPE_2 -> IPCOut_IPU1_0_A15_0_1
       pObj->VPE_2Prm.outQueParams[0].nextLink = pObj->IPCOut_IPU1_0_A15_0_1LinkID;
       pObj->IPCOut_IPU1_0_A15_0_1Prm.inQueParams.prevLinkId = pObj->VPE_2LinkID;
       pObj->IPCOut_IPU1_0_A15_0_1Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_IPU1_0_A15_0_1 -> IPCIn_A15_0_IPU1_0_0
       pObj->IPCOut_IPU1_0_A15_0_1Prm.outQueParams.nextLink = pObj->IPCIn_A15_0_IPU1_0_0LinkID;
       pObj->IPCIn_A15_0_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_A15_0_1LinkID;
       pObj->IPCIn_A15_0_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_A15_0_IPU1_0_0 -> Null
       pObj->IPCIn_A15_0_IPU1_0_0Prm.outQueParams.nextLink = pObj->NullLinkID;
       pObj->NullPrm.inQueParams[0].prevLinkId = pObj->IPCIn_A15_0_IPU1_0_0LinkID;
       pObj->NullPrm.inQueParams[0].prevLinkQueId = 0;

       //VPE_1 -> IPCOut_IPU1_0_DSP1_0
       pObj->VPE_1Prm.outQueParams[0].nextLink = pObj->IPCOut_IPU1_0_DSP1_0LinkID;
       pObj->IPCOut_IPU1_0_DSP1_0Prm.inQueParams.prevLinkId = pObj->VPE_1LinkID;
       pObj->IPCOut_IPU1_0_DSP1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_IPU1_0_DSP1_0 -> IPCIn_DSP1_IPU1_0_0
       pObj->IPCOut_IPU1_0_DSP1_0Prm.outQueParams.nextLink = pObj->IPCIn_DSP1_IPU1_0_0LinkID;
       pObj->IPCIn_DSP1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_DSP1_0LinkID;
       pObj->IPCIn_DSP1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_DSP1_IPU1_0_0 -> Alg_WarpImg
       pObj->IPCIn_DSP1_IPU1_0_0Prm.outQueParams.nextLink = pObj->Alg_WarpImgLinkID;
       pObj->Alg_WarpImgPrm.inQueParams.prevLinkId = pObj->IPCIn_DSP1_IPU1_0_0LinkID;
       pObj->Alg_WarpImgPrm.inQueParams.prevLinkQueId = 0;

       //Alg_WarpImg -> IPCOut_DSP1_IPU1_0_0
       pObj->Alg_WarpImgPrm.outQueParams.nextLink = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->Alg_WarpImgLinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_DSP1_IPU1_0_0 -> IPCIn_IPU1_0_DSP1_0
       pObj->IPCOut_DSP1_IPU1_0_0Prm.outQueParams.nextLink = pObj->IPCIn_IPU1_0_DSP1_0LinkID;
       pObj->IPCIn_IPU1_0_DSP1_0Prm.inQueParams.prevLinkId = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCIn_IPU1_0_DSP1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_IPU1_0_DSP1_0 -> Display_CF
       pObj->IPCIn_IPU1_0_DSP1_0Prm.outQueParams.nextLink = pObj->Display_CFLinkID;
       pObj->Display_CFPrm.inQueParams.prevLinkId = pObj->IPCIn_IPU1_0_DSP1_0LinkID;
       pObj->Display_CFPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 diplomski_Create(diplomskiObj *pObj, Void *appObj){

       Int32 status;

       diplomski_SetLinkId(pObj);
       diplomski_ResetLinkPrms(pObj);

       diplomski_SetPrms(pObj);
       diplomski_SetAppPrms(pObj, appObj);

       diplomski_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->SplitLinkID, &pObj->SplitPrm, sizeof(pObj->SplitPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->SelectLinkID, &pObj->SelectPrm, sizeof(pObj->SelectPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPE_2LinkID, &pObj->VPE_2Prm, sizeof(pObj->VPE_2Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_A15_0_1LinkID, &pObj->IPCOut_IPU1_0_A15_0_1Prm, sizeof(pObj->IPCOut_IPU1_0_A15_0_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_A15_0_IPU1_0_0LinkID, &pObj->IPCIn_A15_0_IPU1_0_0Prm, sizeof(pObj->IPCIn_A15_0_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->NullLinkID, &pObj->NullPrm, sizeof(pObj->NullPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPE_1LinkID, &pObj->VPE_1Prm, sizeof(pObj->VPE_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_DSP1_0LinkID, &pObj->IPCOut_IPU1_0_DSP1_0Prm, sizeof(pObj->IPCOut_IPU1_0_DSP1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_DSP1_IPU1_0_0LinkID, &pObj->IPCIn_DSP1_IPU1_0_0Prm, sizeof(pObj->IPCIn_DSP1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_WarpImgLinkID, &pObj->Alg_WarpImgPrm, sizeof(pObj->Alg_WarpImgPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_DSP1_IPU1_0_0LinkID, &pObj->IPCOut_DSP1_IPU1_0_0Prm, sizeof(pObj->IPCOut_DSP1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_IPU1_0_DSP1_0LinkID, &pObj->IPCIn_IPU1_0_DSP1_0Prm, sizeof(pObj->IPCIn_IPU1_0_DSP1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_CFLinkID, &pObj->Display_CFPrm, sizeof(pObj->Display_CFPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 diplomski_Start(diplomskiObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_CFLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_WarpImgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPE_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_A15_0_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_A15_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPE_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->SelectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->SplitLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 diplomski_Stop(diplomskiObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_CFLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_WarpImgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPE_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_A15_0_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_A15_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPE_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->SelectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->SplitLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 diplomski_Delete(diplomskiObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_CFLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_WarpImgLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPE_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_A15_0_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_A15_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPE_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->SelectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->SplitLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void diplomski_printBufferStatistics(diplomskiObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->SplitLinkID);
       System_linkPrintBufferStatistics(pObj->SelectLinkID);
       System_linkPrintBufferStatistics(pObj->VPE_2LinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_A15_0_1LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_A15_0_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->NullLinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->VPE_1LinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_WarpImgLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       System_linkPrintBufferStatistics(pObj->Display_CFLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void diplomski_printStatistics(diplomskiObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->SplitLinkID);
       System_linkPrintStatistics(pObj->SelectLinkID);
       System_linkPrintStatistics(pObj->VPE_2LinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_A15_0_1LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_A15_0_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->NullLinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->VPE_1LinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->Alg_WarpImgLinkID);
       System_linkPrintStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_IPU1_0_DSP1_0LinkID);
       System_linkPrintStatistics(pObj->Display_CFLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}
