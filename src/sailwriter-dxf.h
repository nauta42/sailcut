/*
 * Copyright (C) 1993-2015 Robert & Jeremy Laine
 * See AUTHORS file for a full list of contributors.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef SAILWRITER_DXF_H
#define SAILWRITER_DXF_H

#include "filewriter.h"
#include "sailcpp/panelgroup.h"
#include <iostream>
#include <fstream>

/** An abstract class containing the methods needed for DXF writing.
 */
class CSailDxfWriter : public CFileWriter<CPanelGroup>
{
public:
    /** The constructor.
     */
    CSailDxfWriter() : CFileWriter<CPanelGroup>(".dxf", "DXF files")
    {}
    ;

    void writeBegin(ofstream &out, const QString &filename) const;
    void writeEnd(ofstream &out) const;

    void writeAtom(ofstream &out, int code, const QString& content) const;
    void writeFace(ofstream &out, CPoint3d p0, CPoint3d p1, CPoint3d p2, unsigned int layer) const;
    void writeLayer(ofstream &out, unsigned int layer, const QString &color) const;
    void writePolyline(ofstream &out, unsigned int layer, const QString &color) const;
    void writeVertex(ofstream &out, CPoint3d p0, unsigned int layer) const;
};


/** A class used to write a CPanelGroup to a 2D DXF file.
 *
 * @ingroup FileIo
 */
class CSailDxfWriter2d : public CSailDxfWriter
{
public:
    enum Dxf2dType {
        NORMAL,
        BLOCKS,
        SPLIT,
    };

    CSailDxfWriter2d(enum Dxf2dType format) : type(format) {};
    void write(const CPanelGroup &sail, const QString &filename) const;

protected:
    void writePanel(ofstream &out, const CPanel &panel, unsigned int layer) const;

    void writeNormal(const CPanelGroup &sail, const QString &filename) const;
    void writeBlocks(const CPanelGroup &sail, const QString &filename) const;
    void writeSplit(const CPanelGroup &sail, const QString &filename) const;

    Dxf2dType type;
};


/** A class used to write a CPanelGroup to a 3D DXF file.
 *
 * @ingroup FileIo
 */
class CSailDxfWriter3d : public CSailDxfWriter
{
public:
    enum Dxf3dType {
        NORMAL,
        SPLIT,
    };

    CSailDxfWriter3d(enum Dxf3dType format) : type(format) {};
    void write(const CPanelGroup &sail, const QString &filename) const;

protected:
    void writePanel(ofstream &out, const CPanel &panel, unsigned int layer) const;

    void writeNormal(const CPanelGroup &sail, const QString &filename) const;
    void writeSplit(const CPanelGroup &sail, const QString &filename) const;

    Dxf3dType type;
};


#endif
