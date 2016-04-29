////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2016 William McKIE                                                    //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QtTest>

#include <QtCore/QSharedPointer>
#include <QtQuick/QQuickItem>

#include <StoiridhControlsTemplates/Control>
#include <StoiridhControlsTemplates/Core/Exception/NullPointerException>

#include <StoiridhControlsTemplates/0.1.0/internal/style/stylestateoperation.hpp>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTStyleStateOperation : public QObject
{
    Q_OBJECT

private:
    using SPEPointer = QSharedPointer<SCT::StylePropertyExpression>;

private slots:
    void constructorCopy();
    void constructorMove();

    void isDefault_data();
    void isDefault();

    void count();

    void name_data();
    void name();

    void addExpression();
    void insertExpressionMapping();
    void expressionAt();

    void apply();

    void opAssignmentCopy();
    void opAssignmentMove();

    void opBinaryComparisonEqual();
    void opBinaryComparisonNotEqual();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTStyleStateOperation::constructorCopy()
{
    SCT::StyleStateOperation operationA{QStringLiteral("Operation")};

    operationA.addExpression(SPEPointer::create());
    operationA.addExpression(SPEPointer::create());

    SCT::StyleStateOperation operationB{operationA};

    QVERIFY(operationA == operationB);
    QCOMPARE(operationA.count(), 2);
    QCOMPARE(operationB.count(), 2);
}

void TestSCTStyleStateOperation::constructorMove()
{
    SCT::StyleStateOperation operationA{QStringLiteral("Operation")};

    operationA.addExpression(SPEPointer::create());
    operationA.addExpression(SPEPointer::create());

    SCT::StyleStateOperation operationB{std::move(operationA)};

    QVERIFY(operationA != operationB);
    QCOMPARE(operationA.count(), 0);
    QCOMPARE(operationB.count(), 2);
}

void TestSCTStyleStateOperation::isDefault_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>("expected");

    QTest::newRow("IsDefault 01") << QString{} << true;
    QTest::newRow("IsDefault 02") << QStringLiteral("OperationName") << false;
}

void TestSCTStyleStateOperation::isDefault()
{
    QFETCH(QString, name);
    QFETCH(bool, expected);

    SCT::StyleStateOperation operation{};
    QVERIFY(operation.isDefault());

    operation.setName(name);

    QCOMPARE(operation.isDefault(), expected);
}

void TestSCTStyleStateOperation::count()
{
    SCT::StyleStateOperation operation{};
    QCOMPARE(operation.count(), 0);

    operation.addExpression(SPEPointer::create());
    QCOMPARE(operation.count(), 1);

    operation.addExpression(SPEPointer::create());
    QCOMPARE(operation.count(), 2);

    operation.addExpression(SPEPointer::create());
    QCOMPARE(operation.count(), 3);
}

void TestSCTStyleStateOperation::name_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Name 01") << QString{} << QString{};
    QTest::newRow("Name 02") << QStringLiteral("Operation") << QStringLiteral("Operation");
}

void TestSCTStyleStateOperation::name()
{
    QFETCH(QString, name);
    QFETCH(QString, expected);

    SCT::StyleStateOperation operation{};
    QVERIFY(operation.name().isEmpty());

    operation.setName(name);

    QCOMPARE(operation.name(), expected);
}

void TestSCTStyleStateOperation::addExpression()
{
    SCT::StyleStateOperation operation{};
    QCOMPARE(operation.count(), 0);

    operation.addExpression(SPEPointer::create());
    QCOMPARE(operation.count(), 1);
}

void TestSCTStyleStateOperation::insertExpressionMapping()
{
    QScopedPointer<SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    auto mapping = qMakePair(control.data(), target.data());

    SCT::StyleStateOperation operation{};
    operation.addExpression(SPEPointer::create());
    operation.addExpression(SPEPointer::create());
    QCOMPARE(operation.count(), 2);

    operation.insertExpressionMapping(1, mapping);

    QCOMPARE(operation.expressionAt(0).lock()->count(), qMakePair(0, 0));
    QCOMPARE(operation.expressionAt(1).lock()->count(), qMakePair(1, 0));
}

void TestSCTStyleStateOperation::expressionAt()
{
    QScopedPointer<SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    auto expression = SPEPointer::create();
    expression->addMapping(control.data(), target.data());

    SCT::StyleStateOperation operation{};
    operation.addExpression(std::move(expression));
    QCOMPARE(operation.count(), 1);

    if (auto expression = operation.expressionAt(0).lock())
    {
        QVERIFY(expression->containsTarget(control.data(), target.data()));
    }
}

void TestSCTStyleStateOperation::apply()
{
    SCT::StyleStateOperation operation{};

    QScopedPointer<SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> background{new QQuickItem{control.data()}};
    QScopedPointer<QQuickItem> content{new QQuickItem{control.data()}};

    control->setBackground(background.data());
    control->setContent(content.data());

    auto expressionA = SPEPointer::create();
    expressionA->addMapping(control.data(), background.data());
    expressionA->addProperty(QStringLiteral("width"), 75.0);
    expressionA->addProperty(QStringLiteral("height"), 25.0);

    auto expressionB = SPEPointer::create();
    expressionB->addMapping(control.data(), content.data());
    expressionB->addProperty(QStringLiteral("width"), 64.0);
    expressionB->addProperty(QStringLiteral("height"), 64.0);

    operation.addExpression(std::move(expressionA));
    operation.addExpression(std::move(expressionB));
    operation.apply(control.data());

    QCOMPARE(control->background()->width(), 75.0);
    QCOMPARE(control->background()->height(), 25.0);

    QCOMPARE(control->content()->width(), 64.0);
    QCOMPARE(control->content()->height(), 64.0);

    // attempt to apply a null pointer in an operation
    QVERIFY_EXCEPTION_THROWN(operation.apply(nullptr), SCT::NullPointerException);
}

void TestSCTStyleStateOperation::opAssignmentCopy()
{
    SCT::StyleStateOperation operationA{QStringLiteral("Operation")};

    operationA.addExpression(SPEPointer::create());
    operationA.addExpression(SPEPointer::create());

    auto operationB = operationA;

    QVERIFY(operationA == operationB);
    QCOMPARE(operationA.count(), 2);
    QCOMPARE(operationB.count(), 2);
}

void TestSCTStyleStateOperation::opAssignmentMove()
{
    SCT::StyleStateOperation operationA{QStringLiteral("Operation")};

    operationA.addExpression(SPEPointer::create());
    operationA.addExpression(SPEPointer::create());

    auto operationB = std::move(operationA);

    QVERIFY(operationA != operationB);
    QCOMPARE(operationA.count(), 0);
    QCOMPARE(operationB.count(), 2);
}

void TestSCTStyleStateOperation::opBinaryComparisonEqual()
{
    SCT::StyleStateOperation operationA{QStringLiteral("Operation")};
    SCT::StyleStateOperation operationB{QStringLiteral("Operation")};

    // an expression must be unique between operations, so it is impossible to add the same
    // expression for two differents operations.

    QVERIFY(operationA == operationB);
}

void TestSCTStyleStateOperation::opBinaryComparisonNotEqual()
{
    SCT::StyleStateOperation operationA{QStringLiteral("OperationA")};
    SCT::StyleStateOperation operationB{QStringLiteral("OperationB")};

    operationA.addExpression(SPEPointer::create());
    operationA.addExpression(SPEPointer::create());

    operationB.addExpression(SPEPointer::create());
    operationB.addExpression(SPEPointer::create());

    QVERIFY(operationA != operationB);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTStyleStateOperation)
#include "tst_sct_stylestateoperation.moc"
