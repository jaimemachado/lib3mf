#include "Model/Classes/NMR_ModelOptimization.h"

namespace NMR {

	NMR::CModelOptimization::CModelOptimization(const ModelResourceID sID, CModel * pModel) :
		CModelResource(sID, pModel)
	{
	}

	nfUint32 CModelOptimization::addOptimizationParam(const nfFloat fScalingX, const nfFloat fScalingY, const nfFloat fScalingZ, const nfFloat fOffsetX, const nfFloat fOffsetY, const nfFloat fOffsetZ)
	{
		OPTIMIZATIONPARAM param;
		param.m_scaling[0] = fScalingX;
		param.m_scaling[1] = fScalingY;
		param.m_scaling[2] = fScalingZ;
		param.m_offset[0] = fOffsetX;
		param.m_offset[1] = fOffsetY;
		param.m_offset[2] = fOffsetZ;
		addOpt.lock();
		param.m_index = (nfUint32)m_pOptimizationParams.size();
		m_pOptimizationParams.push_back(param);
		addOpt.unlock();
		return param.m_index;
	}

	OPTIMIZATIONPARAM CModelOptimization::getOptimizationParam(const nfUint32 nIndex)
	{
		if (nIndex >= m_pOptimizationParams.size())
			throw CNMRException(NMR_ERROR_INVALIDINDEX);
		return m_pOptimizationParams[nIndex];
	}

	nfUint32 CModelOptimization::getOptimizationParamCount() {
		return (nfUint32)m_pOptimizationParams.size();
	}


	std::string CModelOptimization::getPath() {
		return m_path;
	}

	void CModelOptimization::setPath(std::string const & path) {
		m_path = path;
	}
}

