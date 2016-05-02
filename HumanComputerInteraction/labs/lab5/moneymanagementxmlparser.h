#ifndef MONEYMANAGEMENTXMLPARSER_H
#define MONEYMANAGEMENTXMLPARSER_H

#include <QXmlDefaultHandler>
#include <QXmlAttributes>
#include <QXmlParseException>
#include <QString>
#include <QTreeWidgetItem>
#include <QTreeWidget>

class MoneyManagementXMLParser : public QXmlDefaultHandler
{
public:
    MoneyManagementXMLParser();
    MoneyManagementXMLParser(QTreeWidget *);
    bool startElement(const QString &,
                      const QString &,
                      const QString &,
                      const QXmlAttributes &);
    bool characters(const QString &);
    bool endElement(const QString &, const QString &, const QString &);
    bool fatalError(const QXmlParseException &);

private:
    QTreeWidget *treeRootItem;
    QTreeWidgetItem *subTreeRootItem;
    QString m_strText;
};

#endif // MONEYMANAGEMENTXMLPARSER_H
