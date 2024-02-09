
#ifndef __NMR_MODELOPTIMIZATION
#define __NMR_MODELOPTIMIZATION

#include <memory>
#include <vector>
#include <string>
#include <mutex>
#include "Model/Classes/NMR_Model.h"
#include "Model/Classes/NMR_ModelResource.h"
namespace NMR {

	typedef struct {
		nfInt32 m_index;
		nfFloat m_scaling[3];
		nfFloat m_offset[3];
	} OPTIMIZATIONPARAM;

	class CModelOptimization: public CModelResource {
	private:

		std::vector<OPTIMIZATIONPARAM> m_pOptimizationParams;
		std::string m_path;
		std::mutex addOpt;
	public:
		CModelOptimization() = delete;
		CModelOptimization(_In_ const ModelResourceID sID, _In_ CModel * pModel);

		nfUint32 addOptimizationParam(const nfFloat fScalingX, const nfFloat fScalingY, const nfFloat fScalingZ, const nfFloat fOffsetX, const nfFloat fOffsetY, const nfFloat fOffsetZ);
		OPTIMIZATIONPARAM getOptimizationParam(const nfUint32 fIndex);
		nfUint32 getOptimizationParamCount();

		std::string getPath();
		void setPath(std::string const & path);
	};

	typedef std::shared_ptr <CModelOptimization> PModelOptimization;
}
#endif
