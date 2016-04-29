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

#include <StoiridhControlsTemplates/Core/Exception/NullPointerException>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTNullPointerException : public QObject
{
    Q_OBJECT

private slots:
    void what_data();
    void what();

    void message_data();
    void message();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTNullPointerException::what_data()
{
    QTest::addColumn<QString>("expected");

    QTest::newRow("What 01") << QStringLiteral("StoiridhControlsTemplates::NullPointerException");
}

void TestSCTNullPointerException::what()
{
    QFETCH(QString, expected);

    SCT::NullPointerException exception{};
    QCOMPARE(QString::fromLatin1(exception.what()), expected);
}

void TestSCTNullPointerException::message_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("expected");

    QTest::newRow("Message 01") << QStringLiteral("control")
                                << QStringLiteral("const Control *")
                                << QStringLiteral("control of type 'const Control *' is null");
    QTest::newRow("Message 02") << QStringLiteral("control")
                                << QString{}
                                << QStringLiteral("control is null");
    QTest::newRow("Message 03") << QString{}
                                << QString{}
                                << QString{};
}

void TestSCTNullPointerException::message()
{
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, expected);

    SCT::NullPointerException exception{name, type};
    QCOMPARE(exception.message(), expected);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTNullPointerException)
#include "tst_sct_nullpointerexception.moc"
