#ifndef NMR_IOPCPACKAGEREADER
#define NMR_IOPCPACKAGEREADER

#include <memory>
#include <string>
#include "Common/NMR_Types.h"

namespace NMR {
	class COpcPackageRelationship;
	class COpcPackagePart;
	using POpcPackagePart = std::shared_ptr<COpcPackagePart>;

	class IOpcPackageReader {
		virtual _Ret_maybenull_ COpcPackageRelationship * findRootRelation(_In_ std::string sRelationType, _In_ nfBool bMustBeUnique) = 0;
		virtual POpcPackagePart createPart(_In_ std::string sPath) = 0;
		virtual nfUint64 getPartSize(_In_ std::string sPath) = 0;
	};
}
#endif // !NMR_IOPCPACKAGEREADER
