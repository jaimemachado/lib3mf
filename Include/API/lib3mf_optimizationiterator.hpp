/*

Copyright (C) 2019 HP Inc.

All rights reserved.

*/


#ifndef __LIB3MF_OPTIMIZATIONITERATOR
#define __LIB3MF_OPTIMIZATIONITERATOR

#include "lib3mf_interfaces.hpp"

// Parent classes
#include "lib3mf_resourceiterator.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.


namespace Lib3MF {
	namespace Impl {


		/*************************************************************************************************************************
		Class declaration of CSliceStackIterator
		**************************************************************************************************************************/

		class COptimizationIterator : public virtual IOptimizationIterator, public virtual CResourceIterator {
		private:

			/**
			* Put private members here.
			*/

		protected:

			/**
			* Put protected members here.
			*/

		public:

			/**
			* Put additional public members here. They will not be visible in the external API.
			*/


			/**
			* Public member functions to implement.
			*/





			// Inherited via IOptimizationIterator
			virtual IOptimization * GetCurrentOptimization() override;

		};

	} // namespace Impl
} // namespace Lib3MF

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif 
