/*

Copyright (C) 2019 HP Inc.

All rights reserved.

*/

#include "lib3mf_interfaceexception.hpp"
#include "lib3mf_optimization.hpp"

using namespace Lib3MF::Impl;

/*************************************************************************************************************************
Class definition of COptimization
**************************************************************************************************************************/

Lib3MF::Impl::COptimization::COptimization(NMR::PModelOptimization pOptimization):
	CResource(pOptimization)
{
}

NMR::PModelOptimization Lib3MF::Impl::COptimization::optimization()
{
	return std::dynamic_pointer_cast<NMR::CModelOptimization>(resource());
}


Lib3MF_uint32 Lib3MF::Impl::COptimization::AddOptimizationParam(const Lib3MF::sOptimizationParam Param) {
	return optimization()->addOptimizationParam(Param.m_ScalingX, Param.m_ScalingY, Param.m_ScalingZ, Param.m_OffsetX, Param.m_OffsetY, Param.m_OffsetZ);
}

Lib3MF::sOptimizationParam Lib3MF::Impl::COptimization::GetOptimizationParam(const Lib3MF_uint32 nResourceIndex) {
	NMR::OPTIMIZATIONPARAM param = optimization()->getOptimizationParam(nResourceIndex);
	sOptimizationParam result;
	result.m_ScalingX = param.m_scaling[0];
	result.m_ScalingY = param.m_scaling[1];
	result.m_ScalingZ = param.m_scaling[2];
	result.m_OffsetX = param.m_offset[0];
	result.m_OffsetY = param.m_offset[1];
	result.m_OffsetZ = param.m_offset[2];
	return result;
}

void Lib3MF::Impl::COptimization::RemoveOptimizationParam(Lib3MF_uint32 nOptimizationParamIndex)
{
	throw ELib3MFInterfaceException(LIB3MF_ERROR_NOTIMPLEMENTED);
}

void Lib3MF::Impl::COptimization::SetPath(const std::string &sPath)
{
	optimization()->setPath(sPath);
}

std::string Lib3MF::Impl::COptimization::GetPath()
{
	return optimization()->getPath();
}
