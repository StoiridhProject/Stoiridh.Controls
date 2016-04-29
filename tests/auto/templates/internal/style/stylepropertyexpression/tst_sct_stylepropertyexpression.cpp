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

#include <QtQuick/QQuickItem>

#include <StoiridhControlsTemplates/Control>
#include <StoiridhControlsTemplates/Core/Exception/NullPointerException>

#include <StoiridhControlsTemplates/0.1.0/internal/style/stylepropertyexpression.hpp>

#include <stdexcept>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTStylePropertyExpression : public QObject
{
    Q_OBJECT

private slots:
    void constructorCopy();
    void constructorMove();

    void count();

    void containsControl();
    void containsTarget();

    void addMapping();
    void removeMapping();

    void containsProperty();

    void addProperty();
    void addProperties();
    void removeProperty();

    void apply();

    void opAssignmentCopy();
    void opAssignmentMove();

    void opBinaryComparisonEqual();
    void opBinaryComparisonNotEqual();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTStylePropertyExpression::constructorCopy()
{
    SCT::StylePropertyExpression expressionA{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expressionA.addMapping(control.data(), target.data());
    expressionA.addProperty(propertyA);
    expressionA.addProperty(propertyB);

    SCT::StylePropertyExpression expressionB{expressionA};

    QVERIFY(expressionA == expressionB);
    QCOMPARE(expressionA.count(), qMakePair(1, 2));
    QCOMPARE(expressionB.count(), qMakePair(1, 2));
}

void TestSCTStylePropertyExpression::constructorMove()
{
    SCT::StylePropertyExpression expressionA{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expressionA.addMapping(control.data(), target.data());
    expressionA.addProperty(propertyA);
    expressionA.addProperty(propertyB);

    SCT::StylePropertyExpression expressionB{std::move(expressionA)};

    QVERIFY(expressionA != expressionB);
    QCOMPARE(expressionA.count(), qMakePair(0, 0));
    QCOMPARE(expressionB.count(), qMakePair(1, 2));
}

void TestSCTStylePropertyExpression::count()
{
    SCT::StylePropertyExpression expression{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    QCOMPARE(expression.count(), qMakePair(0, 0));

    expression.addMapping(control.data(), target.data());
    QCOMPARE(expression.count(), qMakePair(1, 0));

    expression.addProperty(propertyA);
    QCOMPARE(expression.count(), qMakePair(1, 1));

    expression.addProperty(propertyB);
    QCOMPARE(expression.count(), qMakePair(1, 2));
}

void TestSCTStylePropertyExpression::containsControl()
{
    SCT::StylePropertyExpression expression{};

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expression.addMapping(control.data(), target.data());

    QVERIFY(expression.containsControl(control.data()));
    QVERIFY(!expression.containsControl(nullptr));
}

void TestSCTStylePropertyExpression::containsTarget()
{
    SCT::StylePropertyExpression expression{};

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expression.addMapping(control.data(), target.data());

    QVERIFY(expression.containsTarget(control.data(), target.data()));
    QVERIFY(!expression.containsTarget(nullptr, nullptr));
    QVERIFY(!expression.containsTarget(control.data(), nullptr));
    QVERIFY(!expression.containsTarget(nullptr, target.data()));
}

void TestSCTStylePropertyExpression::addMapping()
{
    SCT::StylePropertyExpression expression{};

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expression.addMapping(control.data(), target.data());
    QCOMPARE(expression.count(), qMakePair(1, 0));

    // attempt to add a null control to the expression
    QVERIFY_EXCEPTION_THROWN(expression.addMapping(nullptr, target.data()), SCT::NullPointerException);
    QCOMPARE(expression.count(), qMakePair(1, 0));

    // attempt to add a null target to the expression
    QVERIFY_EXCEPTION_THROWN(expression.addMapping(control.data(), nullptr), SCT::NullPointerException);
    QCOMPARE(expression.count(), qMakePair(1, 0));
}

void TestSCTStylePropertyExpression::removeMapping()
{
    SCT::StylePropertyExpression expression{};

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expression.addMapping(control.data(), target.data());
    QCOMPARE(expression.count(), qMakePair(1, 0));

    QVERIFY(expression.removeMapping(control.data()));
    QCOMPARE(expression.count(), qMakePair(0, 0));

    // attempt to remove something that never exists!
    QVERIFY(!expression.removeMapping(nullptr));
}

void TestSCTStylePropertyExpression::containsProperty()
{
    SCT::StylePropertyExpression expression{};

    const auto property = qMakePair(QStringLiteral("color"), QColor{});

    expression.addProperty(property);
    QVERIFY(expression.containsProperty(property.first));
    QVERIFY(!expression.containsProperty({}));
}

void TestSCTStylePropertyExpression::addProperty()
{
    SCT::StylePropertyExpression expression{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    expression.addProperty(propertyA.first, propertyA.second);  // variant 1
    expression.addProperty(propertyB);                          // variant 2

    QVERIFY(expression.containsProperty(propertyA.first));
    QVERIFY(expression.containsProperty(propertyB.first));

    // a property has always a non-empty name
    QVERIFY_EXCEPTION_THROWN(expression.addProperty({}, {}), std::invalid_argument);
}

void TestSCTStylePropertyExpression::addProperties()
{
    SCT::StylePropertyExpression expression{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    expression.addProperties({ propertyA, propertyB });

    QCOMPARE(expression.count(), qMakePair(0, 2));
    QVERIFY(expression.containsProperty(propertyA.first));
    QVERIFY(expression.containsProperty(propertyB.first));
}

void TestSCTStylePropertyExpression::removeProperty()
{
    SCT::StylePropertyExpression expression{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    expression.addProperty(propertyA);
    expression.addProperty(propertyB);

    QCOMPARE(expression.count(), qMakePair(0, 2));

    QVERIFY(expression.removeProperty(propertyA.first));
    QCOMPARE(expression.count(), qMakePair(0, 1));

    // property A already removed from the expression
    QVERIFY(!expression.removeProperty(propertyA.first));
    QCOMPARE(expression.count(), qMakePair(0, 1));

    QVERIFY(expression.removeProperty(propertyB.first));
    QCOMPARE(expression.count(), qMakePair(0, 0));

    // property B already removed from the expression
    QVERIFY(!expression.removeProperty(propertyB.first));
    QCOMPARE(expression.count(), qMakePair(0, 0));
}

void TestSCTStylePropertyExpression::apply()
{
    SCT::StylePropertyExpression expression{};

    QScopedPointer<SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> background{new QQuickItem{control.data()}};
    control->setBackground(background.data());

    QCOMPARE(control->background()->width(), 0.0);
    QCOMPARE(control->background()->height(), 0.0);

    expression.addMapping(control.data(), background.data());
    expression.addProperty(qMakePair(QStringLiteral("width"), 75.0));
    expression.addProperty(qMakePair(QStringLiteral("height"), 25.0));

    QVERIFY(expression.apply(control.data()));

    QCOMPARE(control->background()->width(), 75.0);
    QCOMPARE(control->background()->height(), 25.0);

    // attempt to apply a null pointer in an expression
    QVERIFY_EXCEPTION_THROWN(expression.apply(nullptr), SCT::NullPointerException);
}

void TestSCTStylePropertyExpression::opAssignmentCopy()
{
    SCT::StylePropertyExpression expressionA{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expressionA.addMapping(control.data(), target.data());
    expressionA.addProperty(propertyA);
    expressionA.addProperty(propertyB);

    auto expressionB = expressionA;

    QVERIFY(expressionA == expressionB);
    QCOMPARE(expressionA.count(), qMakePair(1, 2));
    QCOMPARE(expressionB.count(), qMakePair(1, 2));
}

void TestSCTStylePropertyExpression::opAssignmentMove()
{
    SCT::StylePropertyExpression expressionA{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    QScopedPointer<const SCT::Control> control{new SCT::Control{}};
    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    expressionA.addMapping(control.data(), target.data());
    expressionA.addProperty(propertyA);
    expressionA.addProperty(propertyB);

    auto expressionB = std::move(expressionA);

    QVERIFY(expressionA != expressionB);
    QCOMPARE(expressionA.count(), qMakePair(0, 0));
    QCOMPARE(expressionB.count(), qMakePair(1, 2));
}

void TestSCTStylePropertyExpression::opBinaryComparisonEqual()
{
    SCT::StylePropertyExpression expressionA{};
    SCT::StylePropertyExpression expressionB{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    expressionA.addProperty(propertyA);
    expressionA.addProperty(propertyB);

    expressionB.addProperty(propertyA);
    expressionB.addProperty(propertyB);

    QVERIFY(expressionA == expressionB);
}

void TestSCTStylePropertyExpression::opBinaryComparisonNotEqual()
{
    SCT::StylePropertyExpression expressionA{};
    SCT::StylePropertyExpression expressionB{};

    const auto propertyA = qMakePair(QStringLiteral("color"), QColor{});
    const auto propertyB = qMakePair(QStringLiteral("border.width"), 2.0);

    expressionA.addProperty(propertyA);
    expressionB.addProperty(propertyB);

    QVERIFY(expressionA != expressionB);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTStylePropertyExpression)
#include "tst_sct_stylepropertyexpression.moc"
