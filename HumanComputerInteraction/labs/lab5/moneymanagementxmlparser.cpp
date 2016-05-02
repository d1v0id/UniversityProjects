#include "moneymanagementxmlparser.h"
#include <QtDebug>

MoneyManagementXMLParser::MoneyManagementXMLParser()
{
    treeRootItem = new QTreeWidget();
}

MoneyManagementXMLParser::MoneyManagementXMLParser(QTreeWidget *rootItem)
{
    treeRootItem = rootItem;
}

bool MoneyManagementXMLParser::startElement(const QString &,
                                            const QString &,
                                            const QString &,
                                            const QXmlAttributes &attrs)
{
    for (int i = 0; i < attrs.count(); i++) {
        if (attrs.localName(i).compare("id") == 0) {
            subTreeRootItem = new QTreeWidgetItem(treeRootItem);
            subTreeRootItem->setText(0, "Person ID");
            subTreeRootItem->setText(1, attrs.value(i));
            qDebug() << "Person ID: " << attrs.value(i);
        }
    }

    return true;
}

bool MoneyManagementXMLParser::characters(const QString &strText)
{
    m_strText = strText;

    return true;
}

bool MoneyManagementXMLParser::endElement(const QString &,
                                          const QString &,
                                          const QString &str)
{
    if (str != "person" && str != "money_management") {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem();
        treeItem->setText(0, str);
        treeItem->setText(1, m_strText);
        subTreeRootItem->addChild(treeItem);
        qDebug() << "TagName: " << str << "\tText: " << m_strText;
    }

    return true;
}

bool MoneyManagementXMLParser::fatalError(const QXmlParseException &exception)
{
    qDebug() << "Line: " << exception.lineNumber() <<
                ", Column: " << exception.columnNumber() <<
                ", Message: " << exception.message();

    return false;
}
