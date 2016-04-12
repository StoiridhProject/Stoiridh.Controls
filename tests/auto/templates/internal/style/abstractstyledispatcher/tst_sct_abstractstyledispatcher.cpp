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

#include <StoiridhControlsTemplates/Internal/style/abstractstyledispatcher.hpp>
#include <StoiridhControlsTemplates/Internal/style/style.hpp>
#include <StoiridhControlsTemplates/Internal/style/styledispatcher.hpp>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTAbstractStyleDispatcher : public QObject
{
    Q_OBJECT

private slots:
    void style();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTAbstractStyleDispatcher::style()
{
    auto *const style = new SCT::Style{};
    QScopedPointer<SCT::AbstractStyleDispatcher> dispatcher{new SCT::StyleDispatcher{style}};

    QVERIFY(dispatcher->style());
    QCOMPARE(dispatcher->style(), style);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTAbstractStyleDispatcher)
#include "tst_sct_abstractstyledispatcher.moc"
