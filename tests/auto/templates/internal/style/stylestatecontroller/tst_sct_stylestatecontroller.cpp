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

#include <StoiridhControlsTemplates/Internal/style/style.hpp>
#include <StoiridhControlsTemplates/Internal/style/stylestatecontroller.hpp>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTStyleStateController : public QObject
{
    Q_OBJECT

private:
    using SSOPointer = QSharedPointer<SCT::StyleStateOperation>;
    using SPEPointer = QSharedPointer<SCT::StylePropertyExpression>;

private:
    static SSOPointer make_operation(SCT::Control *control);

private slots:
    void constructor();

    void isEmpty();
    void count();

    void style();

    void addStateOperation();

    void findStateOperation_data();
    void findStateOperation();

    void defaultStateOperation_data();
    void defaultStateOperation();

    void apply();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Helpers                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////
TestSCTStyleStateController::SSOPointer
TestSCTStyleStateController::make_operation(SCT::Control *control)
{
    Q_ASSERT(control);

    auto operation = SSOPointer::create();

    control->setBackground(new QQuickItem{control});
    control->setContent(new QQuickItem{control});

    auto expressionA = SPEPointer::create();
    expressionA->addMapping(control, control->background());
    expressionA->addProperty(QStringLiteral("width"), 75.0);
    expressionA->addProperty(QStringLiteral("height"), 25.0);

    auto expressionB = SPEPointer::create();
    expressionB->addMapping(control, control->content());
    expressionB->addProperty(QStringLiteral("width"), 64.0);
    expressionB->addProperty(QStringLiteral("height"), 64.0);

    operation->addExpression(std::move(expressionA));
    operation->addExpression(std::move(expressionB));

    return operation;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTStyleStateController::constructor()
{
    QScopedPointer<SCT::Style> style{};
    QVERIFY_EXCEPTION_THROWN(SCT::StyleStateController{style.data()}, SCT::NullPointerException);
}

void TestSCTStyleStateController::isEmpty()
{
    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};
    QVERIFY(controller.isEmpty());

    controller.addStateOperation(SSOPointer::create());
    QVERIFY(!controller.isEmpty());
}

void TestSCTStyleStateController::count()
{
    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};
    QCOMPARE(controller.count(), 0);

    controller.addStateOperation(SSOPointer::create());
    QCOMPARE(controller.count(), 1);
    controller.addStateOperation(SSOPointer::create(QStringLiteral("operation a")));
    QCOMPARE(controller.count(), 2);
    controller.addStateOperation(SSOPointer::create(QStringLiteral("operation b")));
    QCOMPARE(controller.count(), 3);
}

void TestSCTStyleStateController::style()
{
    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};

    QCOMPARE(controller.style(), style.data());
}

void TestSCTStyleStateController::addStateOperation()
{
    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};

    auto operationName = QString::fromUtf8("Operation");
    auto operation = SSOPointer::create(operationName);

    controller.addStateOperation(std::move(operation));

    QCOMPARE(controller.count(), 1);
    QVERIFY(!controller.findStateOperation(operationName).isNull());
}

void TestSCTStyleStateController::findStateOperation_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("operationName");
    QTest::addColumn<bool>("found");

    QTest::newRow("FindStateOperation 01") << QStringLiteral("operation")
                                           << QStringLiteral("operation")
                                           << true;
    QTest::newRow("FindStateOperation 02") << QStringLiteral("operation")
                                           << QStringLiteral("other_operation")
                                           << false;
    QTest::newRow("FindStateOperation 03") << QStringLiteral("other_operation")
                                           << QStringLiteral("operation")
                                           << false;
    QTest::newRow("FindStateOperation 04") << QString{}
                                           << QStringLiteral("operation")
                                           << false;
    QTest::newRow("FindStateOperation 05") << QStringLiteral("operation")
                                           << QString{}
                                           << false;
}

void TestSCTStyleStateController::findStateOperation()
{
    QFETCH(QString, name);
    QFETCH(QString, operationName);
    QFETCH(bool, found);

    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};

    auto operation = SSOPointer::create(name);

    controller.addStateOperation(std::move(operation));

    QCOMPARE(controller.count(), 1);
    QCOMPARE(!controller.findStateOperation(operationName).isNull(), found);
}

void TestSCTStyleStateController::defaultStateOperation_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>("found");

    QTest::newRow("DefaultStateOperation 01") << QString{}
                                              << true;
    QTest::newRow("DefaultStateOperation 02") << QStringLiteral("operation")
                                              << false;
}

void TestSCTStyleStateController::defaultStateOperation()
{
    QFETCH(QString, name);
    QFETCH(bool, found);

    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};

    auto operation = SSOPointer::create(name);

    controller.addStateOperation(std::move(operation));

    QCOMPARE(controller.count(), 1);
    QCOMPARE(!controller.defaultStateOperation().isNull(), found);
}

void TestSCTStyleStateController::apply()
{
    QScopedPointer<SCT::Style> style{new SCT::Style{}};
    SCT::StyleStateController controller{style.data()};

    QScopedPointer<SCT::Control> control{new SCT::Control{}};

    auto operation = TestSCTStyleStateController::make_operation(control.data());

    controller.addStateOperation(std::move(operation));
    controller.apply(control.data());

    QCOMPARE(control->background()->width(), 75.0);
    QCOMPARE(control->background()->height(), 25.0);

    QCOMPARE(control->content()->width(), 64.0);
    QCOMPARE(control->content()->height(), 64.0);

    // attempt to apply a null pointer to a controller
    QVERIFY_EXCEPTION_THROWN(controller.apply(nullptr), SCT::NullPointerException);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTStyleStateController)
#include "tst_sct_stylestatecontroller.moc"
