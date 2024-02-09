/*

Copyright (C) 2019 HP Inc.

All rights reserved.

*/
#ifndef __LIB3MF_OPTIMIZATION
#define __LIB3MF_OPTIMIZATION


#include "lib3mf_interfaces.hpp"
#include "lib3mf_resource.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

#include "Model/Classes/NMR_ModelOptimization.h"


namespace Lib3MF {
	namespace Impl {


		/*************************************************************************************************************************
		Class declaration of COptimization
		**************************************************************************************************************************/

		class COptimization : public virtual IOptimization, public virtual CResource {
		private:
			/**
			* Put private members here.
			*/

		protected:
			/**
			* Put protected members here.
			*/

			NMR::PModelOptimization optimization();

		public:

			COptimization(NMR::PModelOptimization pOptimization);

			// Inherited via IOptimization
			virtual Lib3MF_uint32 AddOptimizationParam(const Lib3MF::sOptimizationParam Param) override;

			virtual Lib3MF::sOptimizationParam GetOptimizationParam(const Lib3MF_uint32 nResourceIndex) override;

			virtual void RemoveOptimizationParam(const Lib3MF_uint32 nOptimizationParamIndex) override;

			virtual void SetPath(const std::string &sPath) override;

			virtual std::string GetPath() override;



			/**
			* Put additional public members here. They will not be visible in the external API.
			*/
		};

	}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif


#endif
