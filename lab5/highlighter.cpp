#include <QtGui>

#include "highlighter.h"

Highlighter::Highlighter(QString language, QColor keywordColor,
	QColor singleCommentColor,
	QColor multiCommentColor, 
	QColor quotationColor, 
	QColor functionColor,
	QTextDocument* parent)
	: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	keywordFormat.setForeground(keywordColor);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;

	if (language == "C++14") //From official doc N4140 2014-10-07
		keywordPatterns << "\\balignas\\b" << "\\bclass\\b" << "\\bconst\\b"
		<< "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
		<< "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
		<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
		<< "\\bshort\\b" << "\\bsigned\\b" << "\\bcontinue\\b"
		<< "\\bstatic\\b" << "\\bstruct\\b" << "\\bregister\\b"
		<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
		<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
		<< "\\bvoid\\b" << "\\bvolatile\\b" << "\\btrue\\b"
		<< "\\balignof\\b" << "\\bdecltype\\b" << "\\bgoto\\b"
		<< "\\breinterpret_cast\\b" << "\\btry\\b" << "\\basm\\b"
		<< "\\bdefault\\b" << "\\bif\\b" << "\\breturn\\b"
		<< "\\bauto\\b" << "\\bdelete\\b" << "\\btypeid\\b"
		<< "\\bbool\\b" << "\\bdo\\b" << "\\bbreak\\b"
		<< "\\bsizeof\\b" << "\\bcase\\b" << "\\bdynamic_cast\\b"
		<< "\\bmutable\\b" << "\\bcatch\\b" << "\\belse\\b"
		<< "\\bstatic_assert\\b" << "\\busing\\b" << "\\bchar\\b"
		<< "\\bnew\\b" << "\\bstatic_cast\\b" << "\\bchar16_t\\b"
		<< "\\bnoexcept\\b" << "\\bchar32_t\\b" << "\\bexport\\b"
		<< "\\bnullptr\\b" << "\\bswitch\\b" << "\\bextern\\b"
		<< "\\bwchar_t\\b" << "\\bfalse\\b" << "\\bthis\\b"
		<< "\\bwhile\\b" << "\\bconstexpr\\b" << "\\bfloat\\b"
		<< "\\bthread_local\\b" << "\\bconst_cast\\b" << "\\bfor\\b"
		<< "\\bthrow\\b";
	else if (language == "C11") 
		//From official doc N1570, Committee Draft — April 12, 2011
		keywordPatterns << "\\auto\\b" << "\\bbreak\\b" << "\\bcase\\b"
		<< "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
		<< "\\bdefault\\b" << "\\bdo\\b" << "\\bdouble\\b"
		<< "\\belse\\b" << "\\benum\\b" << "\\bextern\\b"
		<< "\\bfloat\\b" << "\\bfor\\b" << "\\bgoto\\b"
		<< "\\bif\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bregister\\b" << "\\brestrict\\b"
		<< "\\breturn\\b" << "\\bshort\\b" << "\\bsigned\\b"
		<< "\\bsizeof\\b" << "\\bstatic\\b" << "\\bstruct\\b"
		<< "\\bswitch\\b" << "\\btypedef\\b" << "\\bunion\\b"
		<< "\\bunsigned\\b" << "\\bvoid\\b" << "\\bvolatile\\b"
		<< "\\bwhile\\b" << "\\b_Alignas\\b" << "\\b_Alignof\\b"
		<< "\\b_Atomic\\b" << "\\b_Bool\\b" << "\\b_Complex\\b"
		<< "\\b_Generic\\b" << "\\b_Imaginary\\b" << "\\b_Noreturn\\b"
		<< "\\b_Static_assert\\b" << "\\_Thread_local\\b";
	else if (language == "C18") //From doc N2176
		keywordPatterns << "\\auto\\b" << "\\bbreak\\b" << "\\bcase\\b"
		<< "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
		<< "\\bdefault\\b" << "\\bdo\\b" << "\\bdouble\\b"
		<< "\\belse\\b" << "\\benum\\b" << "\\bextern\\b"
		<< "\\bfloat\\b" << "\\bfor\\b" << "\\bgoto\\b"
		<< "\\bif\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bregister\\b" << "\\brestrict\\b"
		<< "\\breturn\\b" << "\\bshort\\b" << "\\bsigned\\b"
		<< "\\bsizeof\\b" << "\\bstatic\\b" << "\\bstruct\\b"
		<< "\\bswitch\\b" << "\\btypedef\\b" << "\\bunion\\b"
		<< "\\bunsigned\\b" << "\\bvoid\\b" << "\\bvolatile\\b"
		<< "\\bwhile\\b" << "\\b_Alignas\\b" << "\\b_Alignof\\b"
		<< "\\b_Atomic\\b" << "\\b_Bool\\b" << "\\b_Complex\\b"
		<< "\\b_Generic\\b" << "\\b_Imaginary\\b" << "\\b_Noreturn\\b"
		<< "\\b_Static_assert\\b" << "\\_Thread_local\\b";
	else if (language == "C++17") //From doc N4659 2017-03-21
		keywordPatterns << "\\balignas\\b" << "\\bclass\\b" << "\\bconst\\b"
		<< "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
		<< "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
		<< "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
		<< "\\bshort\\b" << "\\bsigned\\b" << "\\bcontinue\\b"
		<< "\\bstatic\\b" << "\\bstruct\\b" << "\\bregister\\b"
		<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
		<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
		<< "\\bvoid\\b" << "\\bvolatile\\b" << "\\btrue\\b"
		<< "\\balignof\\b" << "\\bdecltype\\b" << "\\bgoto\\b"
		<< "\\breinterpret_cast\\b" << "\\btry\\b" << "\\basm\\b"
		<< "\\bdefault\\b" << "\\bif\\b" << "\\breturn\\b"
		<< "\\bauto\\b" << "\\bdelete\\b" << "\\btypeid\\b"
		<< "\\bbool\\b" << "\\bdo\\b" << "\\bbreak\\b"
		<< "\\bsizeof\\b" << "\\bcase\\b" << "\\bdynamic_cast\\b"
		<< "\\bmutable\\b" << "\\bcatch\\b" << "\\belse\\b"
		<< "\\bstatic_assert\\b" << "\\busing\\b" << "\\bchar\\b"
		<< "\\bnew\\b" << "\\bstatic_cast\\b" << "\\bchar16_t\\b"
		<< "\\bnoexcept\\b" << "\\bchar32_t\\b" << "\\bexport\\b"
		<< "\\bnullptr\\b" << "\\bswitch\\b" << "\\bextern\\b"
		<< "\\bwchar_t\\b" << "\\bfalse\\b" << "\\bthis\\b"
		<< "\\bwhile\\b" << "\\bconstexpr\\b" << "\\bfloat\\b"
		<< "\\bthread_local\\b" << "\\bconst_cast\\b" << "\\bfor\\b"
		<< "\\bthrow\\b";
	else if (language == "C++20") //From doc NN4892 2021-06-18
		keywordPatterns << "\\balignas\\b" << "\\balignof\\b" << "\\basm\\b"
		<< "\\bauto\\b" << "\\bbool\\b" << "\\bbreak\\b"
		<< "\\bcase\\b" << "\\bcatch\\b" << "\\bchar\\b"
		<< "\\bchar8_t\\b" << "\\bchar16_t\\b" << "\\bchar32_t\\b"
		<< "\\bclass\\b" << "\\bconcept\\b" << "\\bconst\\b"
		<< "\\bconsteval\\b" << "\\bconstexpr\\b" << "\\bconstinit\\b"
		<< "\\bconst_cast\\b" << "\\bcontinue\\b" << "\\bco_await\\b"
		<< "\\bco_return\\b" << "\\bco_yield\\b" << "\\bdecltype\\b"
		<< "\\bdefault\\b" << "\\bdelete\\b" << "\\bdo\\b"
		<< "\\bdouble\\b" << "\\bdynamic_cast\\b" << "\\belse\\b"
		<< "\\benum\\b" << "\\bexplicit\\b" << "\\bexport\\b"
		<< "\\bextern\\b" << "\\bfalse\\b" << "\\bfloat\\b"
		<< "\\bfor\\b" << "\\bfriend\\b" << "\\bgoto\\b"
		<< "\\bif\\b" << "\\binline\\b" << "\\bint\\b"
		<< "\\blong\\b" << "\\bmutable\\b" << "\\bnamespace\\b"
		<< "\\bnew\\b" << "\\bnoexcept\\b" << "\\bnullptr\\b"
		<< "\\boperator\\b" << "\\bprivate\\b" << "\\bprotected\\b"
		<< "\\bpublic\\b" << "\\bregister\\b" << "\\breinterpret_cast\\b"
		<< "\\brequires\\b" << "\\breturn\\b" << "\\bshort\\b"
		<< "\\bsigned\\b" << "\\bsizeof\\b" << "\\bstatic\\b"
		<< "\\bstatic_assert\\b" << "\\bstatic_cast\\b" << "\\bstruct\\b"
		<< "\\bswitch\\b" << "\\btemplate\\b" << "\\bthis\\b"
		<< "\\bthread_local\\b" << "\\bthrow\\b" << "\\btrue\\b"
		<< "\\btry\\b" << "\\btypedef\\b" << "\\btypeid\\b"
		<< "\\btypename\\b" << "\\bunion\\b" << "\\bunsigned\\b"
		<< "\\busing\\b" << "\\bvirtual\\b" << "\\bvoid\\b"
		<< "\\bvolatile\\b" << "\\bwchar_t\\b" << "\\bwhile\\b";

	for (const QString& pattern : keywordPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	classFormat.setFontWeight(QFont::Bold);
	classFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
	rule.format = classFormat;
	highlightingRules.append(rule);

	singleLineCommentFormat.setForeground(singleCommentColor);
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);

	multiLineCommentFormat.setForeground(multiCommentColor);
	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");

	quotationFormat.setForeground(quotationColor);
	rule.pattern = QRegExp("\".*\"");
	rule.format = quotationFormat;
	highlightingRules.append(rule);

	functionFormat.setFontItalic(true);
	functionFormat.setForeground(functionColor);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat;
	highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString& text)
{
	for (const HighlightingRule& rule : highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}
	setCurrentBlockState(0); //0 - outside comm, 1 - inside comm

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else {
			commentLength = endIndex - startIndex
				+ commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(
			text, startIndex + commentLength);
	}
}