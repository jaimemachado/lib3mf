/*

Copyright (C) 2019 HP Inc.

All rights reserved.

*/

#include "lib3mf_optimizationiterator.hpp"

// Include custom headers here.
#include "lib3mf_optimization.hpp"

using namespace Lib3MF::Impl;

/*************************************************************************************************************************
Class definition of CSliceStackIterator
**************************************************************************************************************************/
IOptimization * Lib3MF::Impl::COptimizationIterator::GetCurrentOptimization()
{
	return new COptimization(std::dynamic_pointer_cast<NMR::CModelOptimization>(GetCurrentResource()));
}
