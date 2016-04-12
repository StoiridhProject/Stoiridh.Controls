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

#include <StoiridhControlsTemplates/Internal/style/stylepropertychanges.hpp>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTStylePropertyChanges : public QObject
{
    Q_OBJECT

private slots:
    void target();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTStylePropertyChanges::target()
{
    SCT::StylePropertyChanges changes{};
    QSignalSpy spy{&changes, SIGNAL(targetChanged())}; // pointer-to-member-function doesn't work
                                                       // with this signal

    QVERIFY(spy.isValid());
    QVERIFY(!changes.target());

    QScopedPointer<QQuickItem> target{new QQuickItem{}};

    changes.setTarget(target.data());

    QCOMPARE(changes.target(), target.data());
    QCOMPARE(spy.count(), 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTStylePropertyChanges)
#include "tst_sct_stylepropertychanges.moc"
