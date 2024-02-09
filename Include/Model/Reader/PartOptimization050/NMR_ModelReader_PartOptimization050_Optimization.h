#ifndef __NMR_MODELREADER_PARTOPTIMIZATION
#define __NMR_MODELREADER_PARTOPTIMIZATION

#include "Model/Reader/NMR_ModelReaderNode.h"
#include "Model/Classes/NMR_ModelOptimization.h"

namespace NMR {
	class CModelReaderNode_PartOptimization050_Optimization : public CModelReaderNode {
	private:
		CModel * m_pModel;
		nfUint32 m_Id;
		std::string m_sPath;
		PModelOptimization m_pOptimizationResource;
	protected:
		virtual void OnAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue);
		virtual void OnNSChildElement(_In_z_ const nfChar * pChildName, _In_z_ const nfChar * pNameSpace, _In_ CXmlReader * pXMLReader);
	public:
		CModelReaderNode_PartOptimization050_Optimization() = delete;
		CModelReaderNode_PartOptimization050_Optimization(_In_ CModel *pModel, _In_ PModelReaderWarnings pWarnings, _In_ PProgressMonitor pProgressMonitor);
		// Inherited via CModelReaderNode
		virtual void parseXML(CXmlReader * pXMLReader) override;
	};
	typedef std::shared_ptr<CModelReaderNode_PartOptimization050_Optimization> PModelReaderNode_PartOptimization050_Optimization;
}
#endif