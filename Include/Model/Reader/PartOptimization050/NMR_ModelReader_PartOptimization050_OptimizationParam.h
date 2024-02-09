#ifndef __NMR_MODELREADER_PARTOPTIMIZATIONPARAM
#define __NMR_MODELREADER_PARTOPTIMIZATIONPARAM
#include "Model/Reader/NMR_ModelReaderNode.h"
#include "Model/Classes/NMR_ModelOptimization.h"
namespace NMR {
	class CModelReaderNode_PartOptimization050_OptimizationParam : public CModelReaderNode {
	private:
		CModelOptimization * m_pOptimization;
		nfFloat m_nfOffsetX,
				m_nfOffsetY,
				m_nfOffsetZ,
				m_nfScaleX,
				m_nfScaleY,
				m_nfScaleZ;
		nfUint32 m_nfParamCount;

	public:
		CModelReaderNode_PartOptimization050_OptimizationParam() = delete;
		CModelReaderNode_PartOptimization050_OptimizationParam(_In_ CModelOptimization *pOptimization, _In_ PModelReaderWarnings pWarnings, _In_ PProgressMonitor pProgressMonitor);
		// Inherited via CModelReaderNode
		virtual void parseXML(CXmlReader * pXMLReader) override;
	protected:
		virtual void OnAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue);
	};

	typedef std::shared_ptr<CModelReaderNode_PartOptimization050_OptimizationParam> PModelReaderNode_PartOptimization050_OptimizationParam;
}
#endif