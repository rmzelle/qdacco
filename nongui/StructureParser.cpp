/*
 * This file is part of qdacco
 * qdacco: offline Dacco Catalan <-> English dictionary
 *
 * Copyright (c) 2005, 2006, 2007, 2015, 2021
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

#include "StructureParser.h"
#include <QDebug>

static QStringList exampleElements = {"example", "catexamp", "engexamp"};
static QStringList noteElements = {"catnote", "engnote"};

bool StructureParser::startDocument()
{
    return true;
}

bool StructureParser::startElement(const QString& nameSpaceUri, const QString& localName,
                                   const QString& qName,
                                   const QXmlAttributes& attributes)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    m_isEntry = (qName == "Entry");

    if (m_isEntry) {
        return true;
    }

    if (wordTypesList.contains(qName)) {
        m_type = qName;
    }

    if (qName == "translation") {
        m_inTranslation = true;
        m_translation = Translation();

        m_translation.gender = attributes.value("gender");

        m_translation.picture = attributes.value("picture");

        if (m_translation.picture.isEmpty()) {
            // It uses attributes.value("picture") if available, else tries with flickr
            m_translation.picture = attributes.value("flickr");
        }
    } else if (qName == "mistakes") {
        m_inMistakes = true;
    } else if (qName == "catacro") {
        m_inCatAcro = true;
    } else if (qName == "engacro") {
        m_inEngAcro = true;
    } else if (qName == "expressions") {
        m_inExpressions = true;
        m_expressions = Expressions();
    } else if (qName == "plural") {
        m_inPlural = true;
    } else if (qName == "fems") {
        m_inFems = true;
    } else if (qName == "femplural") {
        m_inFemPlural = true;
    } else if (qName == "synonyms") {
        m_inSynonyms = true;
    } else if (exampleElements.contains(qName)) {
        m_inExample = true;
    } else if (noteElements.contains(qName)) {
        m_inNote = true;
    }

    return true;
}

bool StructureParser::characters(const QString& chrs)
{
    QString ch = chrs.trimmed();

    if (m_isEntry && !m_inSearchedWord) {
        if (ch == m_entryWanted) {
            m_inSearchedWord = true;
            m_inExpressions = false;
            m_inTranslation = false;
            m_inExample = false;
            m_inPlural = false;
            m_inNote = false;
            m_inFems = false;
            m_inFemPlural = false;
            m_inCatAcro = false;
            m_inEngAcro = false;
            m_inMistakes = false;
            m_inSynonyms = false;

            m_type = QString();
        }
        else {
            m_inSearchedWord = false;
        }
    }

    if (!m_inSearchedWord) {
        return true;
    }

    if (m_inTranslation && m_inPlural) {
        m_translation.plural = ch;
    }
    else if (m_inTranslation && m_inSynonyms) {
        m_translation.synonyms = ch;
    }
    else if (m_inTranslation && m_inCatAcro) {
        m_translation.catalanAcronym = ch;
    }
    else if (m_inTranslation && m_inEngAcro) {
        m_translation.englishAcronym = ch;
    }
    else if (m_inCatAcro) {
        m_wordData.setCatalanAcronym(ch);
    }
    else if (m_inEngAcro) {
        m_wordData.setEnglishAcronym(ch);
    }
    else if (m_inTranslation && m_inExample) {
        m_translation.examples.append(ch);
    }
    else if (m_inTranslation && m_inNote) {
        m_translation.notes.append(ch);
    }
    else if (m_inFems) {
        m_translation.female = ch;
    }
    else if (m_inFemPlural) {
        m_translation.femalePlural = ch;
    }
    else if (m_inTranslation) {
        m_translation.translation = ch;
    }
    else if (m_inExpressions) {
        m_expressions.expression = ch;
    }
    else if (m_inMistakes) {
        m_mistakes = ch;
    }

    return true;
}

bool StructureParser::endElement(const QString& nameSpaceUri, const QString& localName, const QString& qName)
{
    Q_UNUSED(nameSpaceUri);
    Q_UNUSED(localName);

    if (!m_inSearchedWord) {
        return true;
    }

    if (m_inPlural && qName == "plural") {
        m_inPlural = false;
    }
    else if (m_inCatAcro && qName == "catacro") {
        m_inCatAcro = false;
    }
    else if (m_inEngAcro && qName == "engacro") {
        m_inEngAcro = false;
    }
    else if (m_inFems && qName == "fems") {
        m_inFems = false;
    }
    else if (m_inFemPlural && qName == "femplural") {
        m_inFemPlural = false;
    }
    else if (m_inExpressions && qName == "translation") {
        m_expressions.translations.append(m_translation);
        m_translation = Translation();
        m_inTranslation = false;
    }
    else if (qName == "translation") {
        m_wordData.addTranslation(m_translation, m_type);
        m_translation = Translation();
        m_inTranslation = false;
    }
    else if (qName == "mistakes") {
        m_wordData.setMistakes(m_mistakes);
        m_mistakes = QString();
    }
    else if (qName == "synonyms") {
        m_inSynonyms = false;
    }

    if (exampleElements.contains(qName)) {
        m_inExample = false;
    }

    if (noteElements.contains(qName)) {
        m_inNote = false;
    }

    if (qName == "expressions") {
        m_wordData.addExpressions(m_expressions);
        m_expressions = Expressions();
        m_inExpressions = false;
    }

    if (wordTypesList.contains(qName)) {
        m_type = QString();
    }

    if (qName=="Entry") {	// leaving word, if we were in the matched
                            // not anymore. If we weren't it doesn't matter:
                            // we are not anymore either
        m_inSearchedWord=false;
    }

    return true;
}

void StructureParser::setEntryWanted(const QString& paraula)
{
    m_entryWanted = paraula;
}

WordData StructureParser::getWordData()
{
    return m_wordData;
}
