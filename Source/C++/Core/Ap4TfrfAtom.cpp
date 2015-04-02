
#include <cstdio>
#include "Ap4TfrfAtom.h"

/*----------------------------------------------------------------------
|   constants
+---------------------------------------------------------------------*/

AP4_UI08 const AP4_UUID_TFRF_ATOM[16] = {
	0xD4, 0x80, 0x7E, 0xF2, 0xCA, 0x39, 0x46, 0x95, 0x8E, 0x54, 0x26, 0xCB, 0x9E, 0x46, 0xA7, 0x9F
};

/*----------------------------------------------------------------------
|   TFRF
+---------------------------------------------------------------------*/

AP4_DEFINE_DYNAMIC_CAST_ANCHOR(AP4_TfrfAtom)

AP4_TfrfAtom*
AP4_TfrfAtom::Create(AP4_Size size, AP4_ByteStream& stream)
{
    AP4_UI08 version = 0;
    AP4_UI32 flags   = 0;
    AP4_Result result = ReadFullHeader(stream, version, flags);
    if (AP4_FAILED(result)) return NULL;
    if (version != 0 && version != 1) return NULL;
    return new AP4_TfrfAtom(size, version, flags, stream);
}

AP4_TfrfAtom::AP4_TfrfAtom():
    AP4_UuidAtom(AP4_FULL_UUID_ATOM_HEADER_SIZE + 4, AP4_UUID_TFRF_ATOM, 1, 0)
{

}

AP4_TfrfAtom::AP4_TfrfAtom(AP4_UI32 size,
	                         AP4_UI32        version,
	                         AP4_UI32        flags,
	                         AP4_ByteStream& stream) :
    AP4_UuidAtom(size, AP4_UUID_TFRF_ATOM, version, flags)
{
	AP4_UI32 m_FragmentCount;

	stream.ReadUI32(m_FragmentCount);

	for(size_t i=0; i<m_FragmentCount; ++i)
	{
		Entry e;
		if(version == 0)
		{
			AP4_UI32 tmp;
			stream.ReadUI32(tmp);
			e.FragmentAbsoluteTime = tmp;

			stream.ReadUI32(tmp);
			e.FragmentDuration = tmp;
		}
		else
		{
			stream.ReadUI64(e.FragmentAbsoluteTime);
			stream.ReadUI64(e.FragmentDuration);
		}

		m_Entries.push_back(e);
	}
}

AP4_Result
AP4_TfrfAtom::InspectFields(AP4_AtomInspector& inspector)
{
    inspector.AddField("FragmentCount", m_Entries.size());
    for(size_t i=0; i<m_Entries.size(); ++i)
    {
    	char buf[100];
    	sprintf(buf, "[absolute_time:%llu duration:%llu]", m_Entries[i].FragmentAbsoluteTime, m_Entries[i].FragmentDuration);
	    inspector.AddField("fragment", buf);
	}

	return AP4_SUCCESS;
}

AP4_Result
AP4_TfrfAtom::WriteFields(AP4_ByteStream& stream)
{
	stream.WriteUI32(m_Entries.size());

	for(size_t i=0; i<m_Entries.size(); ++i)
	{
		Entry & e = m_Entries[i];

		if(m_Version == 0)
		{
			stream.WriteUI32(e.FragmentAbsoluteTime);
			stream.WriteUI32(e.FragmentDuration);
		}
		else
		{
			stream.WriteUI64(e.FragmentAbsoluteTime);
			stream.WriteUI64(e.FragmentDuration);
		}
	}

    return AP4_SUCCESS;
}

void AP4_TfrfAtom::AddEntry(const Entry & e)
{
	m_Entries.push_back(e);
	SetSize(GetSize() + 16);
}
