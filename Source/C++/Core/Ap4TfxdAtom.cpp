
#include <cstdio>
#include "Ap4TfxdAtom.h"

/*----------------------------------------------------------------------
|   constants
+---------------------------------------------------------------------*/
AP4_UI08 const AP4_UUID_TFXD_ATOM[16] = {
    0x6D, 0x1D, 0x9B, 0x05, 0x42, 0xD5, 0x44, 0xE6, 0x80, 0xE2, 0x14, 0x1D, 0xAF, 0xF7, 0x57, 0xB2
};

AP4_DEFINE_DYNAMIC_CAST_ANCHOR(AP4_TfxdAtom)

AP4_TfxdAtom*
AP4_TfxdAtom::Create(AP4_Size size, AP4_ByteStream& stream)
{
    AP4_UI08 version = 0;
    AP4_UI32 flags   = 0;
    AP4_Result result = ReadFullHeader(stream, version, flags);
    if (AP4_FAILED(result)) return NULL;
    if (version != 0 && version != 1) return NULL;
    return new AP4_TfxdAtom(size, version, flags, stream);
}

AP4_TfxdAtom::AP4_TfxdAtom(AP4_UI64 abstime, AP4_UI64 duration):
    AP4_UuidAtom(AP4_FULL_UUID_ATOM_HEADER_SIZE + 16, AP4_UUID_TFXD_ATOM, 1, 0)
{
	m_FragmentAbsoluteTime = abstime;
	m_FragmentDuration = duration;
}

AP4_TfxdAtom::AP4_TfxdAtom(AP4_UI32 size,
	                         AP4_UI32        version,
	                         AP4_UI32        flags,
	                         AP4_ByteStream& stream) :
    AP4_UuidAtom(size, AP4_UUID_TFXD_ATOM, version, flags)
{
	if(version == 0)
	{
		AP4_UI32 tmp;
		stream.ReadUI32(tmp);

		m_FragmentAbsoluteTime = tmp;
		stream.ReadUI32(tmp);
		m_FragmentDuration = tmp;
	}
	else
	{
		stream.ReadUI64(m_FragmentAbsoluteTime);
		stream.ReadUI64(m_FragmentDuration);
	}
}

AP4_Result
AP4_TfxdAtom::InspectFields(AP4_AtomInspector& inspector)
{
    inspector.AddField("FragmentAbsoluteTime", m_FragmentAbsoluteTime);
    inspector.AddField("FragmentDuration", m_FragmentDuration);

	return AP4_SUCCESS;
}

AP4_Result
AP4_TfxdAtom::WriteFields(AP4_ByteStream& stream)
{
	if(m_Version == 0)
	{
		stream.WriteUI32(m_FragmentAbsoluteTime);
		stream.WriteUI32(m_FragmentDuration);
	}
	else
	{
		stream.WriteUI64(m_FragmentAbsoluteTime);
		stream.WriteUI64(m_FragmentDuration);
	}

    return AP4_SUCCESS;
}
