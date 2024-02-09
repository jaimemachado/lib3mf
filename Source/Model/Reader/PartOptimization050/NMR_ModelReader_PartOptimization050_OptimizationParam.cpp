
#include "Model/Reader/PartOptimization050/NMR_ModelReader_PartOptimization050_OptimizationParam.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_ModelConstantsPartOptimization.h"
#include "Model/Classes/NMR_ModelOptimization.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"
#include "Common/NMR_StringUtils.h"

NMR::CModelReaderNode_PartOptimization050_OptimizationParam::CModelReaderNode_PartOptimization050_OptimizationParam(CModelOptimization * pOptimization, PModelReaderWarnings pWarnings, PProgressMonitor pProgressMonitor)
	: CModelReaderNode(pWarnings, pProgressMonitor)
{
	m_pOptimization = pOptimization;
	m_nfOffsetX = m_nfOffsetY = m_nfOffsetZ = 0;
	m_nfScaleX = m_nfScaleY = m_nfScaleZ = 1.0;
	m_nfParamCount = 0;
}

void NMR::CModelReaderNode_PartOptimization050_OptimizationParam::parseXML(CXmlReader * pXMLReader) 
{
	parseName(pXMLReader);

	parseAttributes(pXMLReader);
	if (m_nfParamCount == 6)
		m_pOptimization->addOptimizationParam(m_nfScaleX, m_nfScaleY, m_nfScaleZ, m_nfOffsetX, m_nfOffsetY, m_nfOffsetZ);
	else
		m_pWarnings->addException(CNMRException(NMR_ERROR_PARTOPTIMIZATION_INVALIDELEMENT), mrwMissingMandatoryValue);
}


void NMR::CModelReaderNode_PartOptimization050_OptimizationParam::OnAttribute(const nfChar * pAttributeName, const nfChar * pAttributeValue) 
{
	if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMSCALINGX) == 0) {
		m_nfScaleX = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMSCALINGY) == 0) {
		m_nfScaleY = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMSCALINGZ) == 0) {
		m_nfScaleZ = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMOFFSETX) == 0) {
		m_nfOffsetX = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMOFFSETY) == 0) {
		m_nfOffsetY = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_PARTOPTIMIZATIONPARAMOFFSETZ) == 0) {
		m_nfOffsetZ = fnStringToFloat(pAttributeValue);
		m_nfParamCount++;
	} else {
		throw CNMRException(NMR_ERROR_PARTOPTIMIZATION_INVALIDATTRIBUTE);
	}
}
