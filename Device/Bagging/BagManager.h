/*
 * BagManager.h
 *
 *  Created on: 8 Aug 2016
 *      Author: Zeyi Wen
 *		@brief: 
 */

#ifndef BAGMANAGER_H_
#define BAGMANAGER_H_

#include <helper_cuda.h>
#include <cuda.h>

#include "../../DeviceHost/TreeNode.h"
#include "../../DeviceHost/DefineConst.h"
#include "../../DeviceHost/NodeStat.h"
#include "../../Host/UpdateOps/SplitPoint.h"

class BagManager
{
public:
	static int *m_pInsWeight;
	static int m_numBag;
	static int m_numIns;
	static int m_numFea;
	static long long m_numFeaValue;

	//tree info
	static int m_numTreeEachBag;
	static int m_maxNumNode;
	static int m_maxNumSplittable;

	//device memory
	static cudaStream_t *m_pStream;
	static TreeNode *m_pSNBufferEachBag;
	static int *m_pInsIdToNodeId;
	static int *m_pInsWeight_d;

	static TreeNode *m_pAllTreeEachBag;

	//for gradient and hessian
	static float_point *m_pTargetValueEachBag;
	static float_point *m_pInsGradEachBag, *m_pInsHessEachBag;
	static float_point *m_pGDEachFvalueEachBag, *m_pHessEachFvalueEachBag;
	static float_point *m_pGDPrefixSumEachBag, *m_pHessPrefixSumEachBag;
	static float_point *m_pGainEachFvalueEachBag;
	//for finding the best split
	static float_point *m_pfLocalBestGainEachBag_d;
	static int *m_pnLocalBestGainKeyEachBag_d;
	static float_point *m_pfGlobalBestGainEachBag_d;
	static int *m_pnGlobalBestGainKeyEachBag_d;

	//for pinned memory; for computing indices in multiple level tree
	static int *m_pIndicesEachBag_d;
	static long long *m_pNumFvalueEachNodeEachBag_d;//the number of feature values of each (splittable?) node
	static long long *m_pFvalueStartPosEachNodeEachBag_d;//the start position of each node
	static long long *m_pEachFeaStartPosEachNodeEachBag_d;//the start position of each feature in a node
	static int *m_pEachFeaLenEachNodeEachBag_d;//the number of values of each feature in each node

	//for splittable nodes
	static TreeNode *m_pSplittableNodeEachBag;
	static SplitPoint *m_pBestSplitPointEachBag;
	static nodeStat *m_pSNodeStatEachBag;
	static nodeStat *m_pRChildStatEachBag;
	static nodeStat *m_pLChildStatEachBag;
	//temporary space for splittable nodes
	static nodeStat *m_pTempRChildStatEachBag;
	static float_point *m_pLastValueEachBag;
	static int *m_nSNLockEachBag;//a lock for critical region
	//map splittable node to buffer id
	static int *m_pSNIdToBuffIdEachBag;
	static int *m_pBuffIdVecEachBag;
	static int *m_pNumofBuffIdEachBag;
	static SplitPoint *m_pBestPointEachBagHost;

	//memory for the tree on training
	static TreeNode *m_pNodeTreeOnTrainingEachBag;
	static int *m_pCurNumofNodeTreeOnTrainingEachBag_d;
	static int *m_pNumofNewNodeTreeOnTrainingEachBag;
	//for reseting memory for the next tree
	static TreeNode *m_pNodeTreeOnTrainingEachBagHost;
	//memory for new node statistics
	static nodeStat *m_pNewNodeStatEachBag;
	static TreeNode *m_pNewSplittableNodeEachBag;

	//memory for each individual tree
	static int *m_pNumofNodeEachTreeEachBag;	//the number of nodes of each tree
	static int *m_pStartPosOfEachTreeEachBag;	//the start position of each tree in the memory

	//memory for parent node to children ids
	static int *m_pParentIdEachBag;
	static int *m_pLeftChildIdEachBag, *m_pRightChildIdEachBag;
	//memory for used features in the current splittable nodes
	static int *m_pFeaIdToBuffIdEachBag;
	static int *m_pUniqueFeaIdVecEachBag;
	static int *m_pNumofUniqueFeaIdEachBag;
	static int m_maxNumUsedFeaATree;

	//temp memory
	static float_point *m_pTrueLabel_h;

public:
	static void InitBagManager(int numIns, int numFea, int numTree, int numBag, int maxNumSN,
							   int maxNumNode, long long numFeaValue, int maxNumUsedFeaInATree);

	static void FreeMem();
private:
	static void AllocMem();
};



#endif /* BAGMANAGER_H_ */