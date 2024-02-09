
#include "Model/Reader/PartOptimization050/NMR_ModelReader_PartOptimization050_Optimization.h"
#include "Model/Reader/PartOptimization050/NMR_ModelReader_PartOptimization050_OptimizationParam.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_ModelConstantsPartOptimization.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"
#include "Common/NMR_StringUtils.h"
NMR::CModelReaderNode_PartOptimization050_Optimization::CModelReaderNode_PartOptimization050_Optimization(CModel * pModel, PModelReaderWarnings pWarnings, PProgressMonitor pProgressMonitor):
	CModelReaderNode(pWarnings, pProgressMonitor), m_pModel(pModel) {
}

void NMR::CModelReaderNode_PartOptimization050_Optimization::parseXML(CXmlReader * pXMLReader) {
	
	parseName(pXMLReader);

	parseAttributes(pXMLReader);

	m_pOptimizationResource = std::make_shared<CModelOptimization>(m_Id, m_pModel);

	parseContent(pXMLReader);

	m_pOptimizationResource->setPath(m_sPath);
	m_pModel->addResource(m_pOptimizationResource);
}

void NMR::CModelReaderNode_PartOptimization050_Optimization::OnAttribute(const nfChar * pAttributeName, const nfChar * pAttributeValue) {
	if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONID) == 0) {
		m_Id = fnStringToUint32(pAttributeValue);
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPATH) == 0) {
		m_sPath = pAttributeValue;
	} else {
		m_pWarnings->addException(CNMRException(NMR_ERROR_PARTOPTIMIZATION_INVALIDATTRIBUTE), mrwFatal);
	}
}

void NMR::CModelReaderNode_PartOptimization050_Optimization::OnNSChildElement(const nfChar * pChildName, const nfChar * pNameSpace, CXmlReader * pXMLReader) {
	if (strcmp(pChildName, XML_3MF_ELEMENT_PARTOPTIMIZATIONPARAMS) == 0) {
		PModelReaderNode_PartOptimization050_OptimizationParam pXMLNode = nullptr;
		pXMLNode = std::make_shared<CModelReaderNode_PartOptimization050_OptimizationParam>(m_pOptimizationResource.get(), m_pWarnings, m_pProgressMonitor);
		pXMLNode->parseXML(pXMLReader);
	} else {
		m_pWarnings->addException(CNMRException(NMR_ERROR_PARTOPTIMIZATION_INVALIDELEMENT), mrwFatal);
	}
}

