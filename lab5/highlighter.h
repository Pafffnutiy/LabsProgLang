#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	Highlighter(QString language, QColor keywordColor = Qt::darkBlue, 
		QColor singleCommentColor = Qt::red, 
		QColor multiCommentColor = Qt::red,
		QColor quotationColor = Qt::darkGreen,
		QColor functionColor = Qt::blue, 
		QTextDocument* parent = 0);

protected:
	void highlightBlock(const QString& text);

private:
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	QTextCharFormat keywordFormat;
	QTextCharFormat classFormat;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotationFormat;
	QTextCharFormat functionFormat;
};

#endif