
/*++

Copyright (C) 2019 3MF Consortium

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_ModelReaderNode_KeyStoreCipherValue.h defines the Model Reader Node class that is related to <xenc:CipherValue>.

--*/

#include "Model/Reader/SecureContent085/NMR_ModelReaderNode_KeyStoreBase64Value.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_KeyStoreResourceData.h"
#include "Model/Classes/NMR_KeyStoreAccessRight.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"
#include "Common/NMR_StringUtils.h"

#include "Libraries/cpp-base64/base64.h"
#include "..\..\..\Include\Model\Reader\NMR_ModelReader_KeyStoreBase64Value.h"

namespace NMR {

	CModelReaderNode_KeyStoreBase64Value::CModelReaderNode_KeyStoreBase64Value(CKeyStore * pKeyStore, PModelReaderWarnings pWarnings)
		: CModelReaderNode_KeyStoreBase(pKeyStore, pWarnings)
	{
		m_sCodedValue = "";
	}

	std::vector<nfByte> CModelReaderNode_KeyStoreBase64Value::getValue()
	{
		return m_decodedValue;
	}

	void CModelReaderNode_KeyStoreBase64Value::parseXML(_In_ CXmlReader * pXMLReader)
	{
		// Parse name
		parseName(pXMLReader);

		// Parse attribute
		parseAttributes(pXMLReader);

		// Parse Content
		parseContent(pXMLReader);

		m_decodedValue = base64_decode(m_sCodedValue);
	}

	void CModelReaderNode_KeyStoreBase64Value::OnText(_In_z_ const nfChar * pText, _In_ CXmlReader * pXMLReader)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);

		m_sCodedValue += std::string(pText);
	}

}
