/*****************************************************************
|
|    AP4 - TFXD support
|
|    Copyright 2002-2009 Axiomatic Systems, LLC
|
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
****************************************************************/

#ifndef _AP4_TFXD_H_
#define _AP4_TFXD_H_

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Ap4Types.h"
#include "Ap4Atom.h"
#include "Ap4AtomFactory.h"
#include "Ap4UuidAtom.h"

/*----------------------------------------------------------------------
|   class references
+---------------------------------------------------------------------*/
class AP4_TfxdAtom;

/*----------------------------------------------------------------------
|   constants
+---------------------------------------------------------------------*/

extern AP4_UI08 const AP4_UUID_TFXD_ATOM[16];

class AP4_TfxdAtom : public AP4_UuidAtom
{
public:
    AP4_IMPLEMENT_DYNAMIC_CAST_D(AP4_TfxdAtom, AP4_UuidAtom)

    // class methods
    static AP4_TfxdAtom* Create(AP4_Size size,
                                AP4_ByteStream& stream);

    AP4_TfxdAtom(AP4_UI64 abstime, AP4_UI64 duration);

    // methods
    virtual AP4_Result InspectFields(AP4_AtomInspector& inspector);
    virtual AP4_Result WriteFields(AP4_ByteStream& stream);

private:
    // methods
    AP4_TfxdAtom(AP4_UI32        size,
                                 AP4_UI32        version,
                                 AP4_UI32        flags,
                                 AP4_ByteStream& stream);

    AP4_UI64 m_FragmentAbsoluteTime;
    AP4_UI64 m_FragmentDuration;
};


#endif // _AP4_TFXD_H_
