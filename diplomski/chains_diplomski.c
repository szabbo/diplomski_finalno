#include "diplomski_priv.h"
#include <examples/tda2xx/include/chains_common.h>
#include <examples/tda2xx/include/chains_common_amv.h>

#include "examples/tda2xx/include/chains_common_osal.h"

#define CAPTURE_SENSOR_WIDTH (1280)
#define CAPTURE_SENSOR_HEIGHT (720)

/**
*******************************************************************************
*
* \brief Use-case object
*
* This structure contains all the LinksId's and create Params.
* The same is passed to all create, start, stop functions.
*
*******************************************************************************
*/
typedef struct 
{
	diplomskiObj ucObj;
	
	UInt32 captureOutWidth;
	UInt32 captureOutHeight;
	UInt32 displayWidth;
	UInt32 displayHeight;
	UInt32 displayActiveChId;
	/**< CH ID which is shown on display, by default 2x2 SW Mosaic
	* is shown on display
	*/
	UInt32 numLvdsCh;
	/**< Number of channels of LVDS to enable */
	Chains_Ctrl *chainsCfg;
	//netProcID za snimanje video signala sa kamere
	UInt32 netProcId;
} Chains_diplomskiAppObj;
/**
*******************************************************************************
*
* \brief Two Cameras with Algs and Display usecase function for SC TDA2xx
*
* This functions executes the create, start functions
*
* Further in a while loop displays run time menu and waits
* for user inputs to print the statistics or to end the demo.
*
* Once the user inputs end of demo stop and delete
* functions are executed.
*
* \param chainsCfg [IN] Chains_Ctrl
*
*******************************************************************************
*/

/**
*******************************************************************************
*
* \brief Set Select Create Parameters
*
* Assign the CH to the Q
*
* \param pPrm [OUT] SelectLink_CreateParams
*
*******************************************************************************
*/
static Void diplomski_SetSelectPrms(SelectLink_CreateParams *pPrm)
{
	pPrm->numOutQue = 2;
	pPrm->outQueChInfo[0].outQueId = 0;
	pPrm->outQueChInfo[0].numOutCh = 1;
	pPrm->outQueChInfo[0].inChNum[0] = 0;
	pPrm->outQueChInfo[1].outQueId = 1;
	pPrm->outQueChInfo[1].numOutCh = 1;
	pPrm->outQueChInfo[1].inChNum[0] = 1;
}
/**
*******************************************************************************
*
* \brief Set VPE Create Parameters
*
* This function is used to set the VPE params.
* It is called in Create function. It is advisable to have
* chains_diplomski_ResetLinkPrm prior to set params
* so all the default params get set.
* Scaling parameters and dataFormat are set.
*
*
* \param pPrm [OUT] VpeLink_CreateParams
*
*******************************************************************************
*/
static Void diplomski_SetVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 displayWidth,
                    UInt32 displayHeight,
                    System_VideoDataFormat dataFormat
)

{
    UInt32 widthFactor, heightFactor;
    VpeLink_ChannelParams *chPrms;

    pPrm->enableOut[0] = TRUE;
    widthFactor = 1;
    heightFactor = 1;

    pPrm->chParams[0].outParams[0].width = SystemUtils_floor(displayWidth/widthFactor, 16);
    pPrm->chParams[0].outParams[0].height = displayHeight/heightFactor;
    pPrm->chParams[0].outParams[0].dataFormat = dataFormat;
    pPrm->chParams[0].outParams[0].numBufsPerCh = 4;

    chPrms = &pPrm->chParams[0];

    chPrms->scCfg.bypass = FALSE;
    chPrms->scCfg.nonLinear = FALSE;
    chPrms->scCfg.stripSize = 0;

    chPrms->scCropCfg.cropStartX = 0;
    chPrms->scCropCfg.cropStartY = 0;
    chPrms->scCropCfg.cropWidth = CAPTURE_SENSOR_WIDTH;
    chPrms->scCropCfg.cropHeight = CAPTURE_SENSOR_HEIGHT;
}

/**
*******************************************************************************
* \brief Set create parameters for NullSrc
*******************************************************************************
*/
Void diplomski_SetNullPrms(Chains_diplomskiAppObj *pObj, NullLink_CreateParams *pPrm)
{
	pPrm->networkServerPort = NETWORK_TX_SERVER_PORT;
	/* Select network mode for null link */
	ChainsCommon_networkTxSetMode(pPrm);
}

/**
*******************************************************************************
*
* \brief Set link Parameters
*
* It is called in Create function of the auto generated use-case file.
*
* \param pUcObj [IN] Auto-generated usecase object
* \param appObj [IN] Application specific object
*
*******************************************************************************
*/
Void diplomski_SetAppPrms(diplomskiObj *pUcObj, Void *appObj)
{
	Chains_diplomskiAppObj *pObj = (Chains_diplomskiAppObj*)appObj;

	//dodano
	pUcObj->IPCIn_A15_0_IPU1_0_0LinkID = SYSTEM_MAKE_LINK_ID(pObj->netProcId, pUcObj->IPCIn_A15_0_IPU1_0_0LinkID);
	pUcObj->NullLinkID = SYSTEM_MAKE_LINK_ID(pObj->netProcId, pUcObj->NullLinkID);

	UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];

	pObj->displayActiveChId = 0;
	pObj->numLvdsCh = 2;
	pObj->captureOutWidth = CAPTURE_SENSOR_WIDTH;
	pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

	ChainsCommon_GetDisplayWidthHeight(pObj->chainsCfg->displayType, &pObj->displayWidth, &pObj->displayHeight);

	portId[0] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;

	ChainsCommon_MultiCam_SetCapturePrms(&pUcObj->CapturePrm, CAPTURE_SENSOR_WIDTH * 2, CAPTURE_SENSOR_HEIGHT, portId, pObj->numLvdsCh / 2);
	ChainsCommon_Amv_StartCMSDevices();
	diplomski_SetSelectPrms(&pUcObj->SelectPrm);

	//dodano
	diplomski_SetNullPrms(pObj, &pUcObj->NullPrm);

	ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm, pObj->displayWidth, pObj->displayHeight);
	ChainsCommon_SetDisplayPrms(&pUcObj->Display_CFPrm, &pUcObj->Display_GrpxPrm, pObj->chainsCfg->displayType, pObj->displayWidth, pObj->displayHeight);
	
	pUcObj->Display_CFPrm.rtParams.posX = (float)0;
	pUcObj->Display_CFPrm.rtParams.posY = (float)0;
	pUcObj->Display_CFPrm.rtParams.tarWidth = (float) pObj->displayWidth; // CAPTURE_SENSOR_WIDTH;
	pUcObj->Display_CFPrm.rtParams.tarHeight = (float) pObj->displayHeight; // (CAPTURE_SENSOR_HEIGHT);
	pUcObj->Display_CFPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

	diplomski_SetVpePrm(&pUcObj->VPE_1Prm, CAPTURE_SENSOR_WIDTH, CAPTURE_SENSOR_HEIGHT, SYSTEM_DF_YUV420P); // / 2 height, SYSTEM_DF_YUV422I_YUYV
	diplomski_SetVpePrm(&pUcObj->VPE_2Prm, CAPTURE_SENSOR_WIDTH, CAPTURE_SENSOR_HEIGHT, SYSTEM_DF_YUV422I_YUYV);//SYSTEM_DF_YUV420SP_UV

	ChainsCommon_StartDisplayCtrl(pObj->chainsCfg->displayType, CAPTURE_SENSOR_WIDTH, CAPTURE_SENSOR_HEIGHT);
}

/**
*******************************************************************************
*
* \brief Start the capture display Links
*
* Function sends a control command to capture and display link to
* to Start all the required links . Links are started in reverce
* order as information of next link is required to connect.
* System_linkStart is called with LinkId to start the links.
*
* \param pObj [IN] Chains_twoCam_RotateAndColorToGrayObj
*
* \return SYSTEM_LINK_STATUS_SOK on success
*
*******************************************************************************
*/
static Void diplomski_StartApp(Chains_diplomskiAppObj *pObj)
{
	#ifdef TDA2EX_BUILD
	ChainsCommon_tda2exSelectPHY(pObj->chainsCfg->captureSrc);
	#endif

	Chains_memPrintHeapStatus();
	ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
	diplomski_Start(&pObj->ucObj);
	Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}
/**
*******************************************************************************
*
* \brief Delete the capture display Links
*
* Function sends a control command to capture and display link to
* to delete all the prior created links
* System_linkDelete is called with LinkId to delete the links.
*
* \param pObj [IN] Chains_twoCam_RotateAndColorToGrayObj
*
*******************************************************************************
*/
static Void diplomski_StopAndDeleteApp(Chains_diplomskiAppObj *pObj)
{
	diplomski_Stop(&pObj->ucObj);
	diplomski_Delete(&pObj->ucObj);
	ChainsCommon_StopDisplayCtrl();
	ChainsCommon_Amv_StopCMSDevices();
	ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);
	/* Print the HWI, SWI and all tasks load */
	/* Reset the accumulated timer ticks */
	Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

Void Chains_diplomski(Chains_Ctrl *chainsCfg)
{
	char ch;
	UInt32 done = FALSE;
	Chains_diplomskiAppObj chainsObj;
	chainsObj.numLvdsCh = 0; /* KW error fix */
	chainsObj.displayActiveChId = 0; /* KW error fix */

	//dodano
	chainsObj.netProcId = Utils_netGetProcId();
	if(chainsObj.netProcId==System_getSelfProcId())
	{
		Vps_printf(" \n");
		Vps_printf(" CHAINS: ERROR: Networking/NDK MUST be run on different CPU"
		" than IPU1-0.\n");
		Vps_printf(" CHAINS: ERROR: If you need to run this use-case with NDK"
		" on IPU1-0 then regenerate the use-case with NullSrc/Null"
		" links on IPU1-0.\n"
		);
		Vps_printf(" \n");
		return;
	}


	chainsObj.chainsCfg = chainsCfg;
	diplomski_Create(&chainsObj.ucObj, &chainsObj);
	diplomski_StartApp(&chainsObj);

	while(!done)
	{
		ch = Chains_menuRunTime();
		switch(ch)
		{
			case '0':
				done = TRUE;
				break;
			case 'p':
			case 'P':
				ChainsCommon_PrintStatistics();
				diplomski_printStatistics(&chainsObj.ucObj);
				break;
			default:
				Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
				break;
		}
	}
	diplomski_StopAndDeleteApp(&chainsObj);
}
