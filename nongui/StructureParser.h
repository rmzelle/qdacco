/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2021
 *      Carles Pina i Estany <carles@pina.cat>
 *
 * qdacco is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * qdacco is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef STRUCTUREPARSER_H
#define STRUCTUREPARSER_H

#include <QtCore/QQueue> 
#include <QtCore/QString>
#include <QtXml/QXmlDefaultHandler>

#include "worddata.h"
#include "auxiliar.h"

class QString;

class StructureParser : public QXmlDefaultHandler
{
public:
    bool startDocument();
    bool startElement(const QString& nameSpaceUri, const QString& localName, const QString& qName,
                      const QXmlAttributes& attributes);
    bool endElement(const QString& nameSpaceUri, const QString& localName, const QString& qName);
    bool characters(const QString& chrs);
    void setEntryWanted(const QString& paraula);

    WordData getWordData();

private:
    bool m_isEntry;

    bool m_inTranslation;
    bool m_inExpressions;
    bool m_inExample;
    bool m_inPlural;
    bool m_inNote;
    bool m_inFems;
    bool m_inFemPlural;
    bool m_inCatAcro;
    bool m_inEngAcro;

    bool m_found;

    QString m_entryWanted;

    WordData m_wordData;

    Translation m_translation;
    Expressions m_expressions;

    QString m_type;
};

#endif
