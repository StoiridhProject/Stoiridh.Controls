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
#include <QtCore/QVariantList>

#include <StoiridhControlsTemplates/Padding>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTPadding : public QObject
{
    Q_OBJECT

private slots:
    void isNull_data();
    void isNull();

    void top_data();
    void top();

    void left_data();
    void left();

    void bottom_data();
    void bottom();

    void right_data();
    void right();

    void setPaddings_data();
    void setPaddings();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTPadding::isNull_data()
{
    QTest::addColumn<QRectF>("paddings");
    QTest::addColumn<bool>("expected");

    QTest::newRow("IsNull 01") << QRectF{0.0, 0.0, 0.0, 0.0} << true;
    QTest::newRow("IsNull 02") << QRectF{5.0, 0.0, 0.0, 0.0} << false;
    QTest::newRow("IsNull 03") << QRectF{0.0, 5.0, 0.0, 0.0} << false;
    QTest::newRow("IsNull 04") << QRectF{0.0, 0.0, 5.0, 0.0} << false;
    QTest::newRow("IsNull 05") << QRectF{0.0, 0.0, 0.0, 5.0} << false;
}

void TestSCTPadding::isNull()
{
    QFETCH(QRectF, paddings);
    QFETCH(bool, expected);

    SCT::Padding padding{};
    QCOMPARE(padding.isNull(), true);

    padding.setPaddings(paddings);

    QCOMPARE(padding.isNull(), expected);
}

void TestSCTPadding::top_data()
{
    QTest::addColumn<qreal>("top");
    QTest::addColumn<qreal>("expected");

    QTest::newRow("Top 01") <<  0.0 <<  0.0;
    QTest::newRow("Top 02") <<  2.0 <<  2.0;
    QTest::newRow("Top 03") <<  4.0 <<  4.0;
    QTest::newRow("Top 04") <<  8.0 <<  8.0;
    QTest::newRow("Top 05") << 16.0 << 16.0;
}

void TestSCTPadding::top()
{
    QFETCH(qreal, top);
    QFETCH(qreal, expected);

    SCT::Padding padding{};
    QSignalSpy spy{&padding, &SCT::Padding::topChanged};
    QVERIFY(spy.isValid());

    QCOMPARE(padding.top(), 0.0);
    QCOMPARE(spy.count(), 0);

    padding.setTop(top);

    if (top > 0.0)
    {
        QCOMPARE(padding.top(), expected);
        QCOMPARE(spy.count(), 1);

        QVariantList arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toReal(), expected);
    }
}

void TestSCTPadding::left_data()
{
    QTest::addColumn<qreal>("left");
    QTest::addColumn<qreal>("expected");

    QTest::newRow("Left 01") <<  0.0 <<  0.0;
    QTest::newRow("Left 02") <<  2.0 <<  2.0;
    QTest::newRow("Left 03") <<  4.0 <<  4.0;
    QTest::newRow("Left 04") <<  8.0 <<  8.0;
    QTest::newRow("Left 05") << 16.0 << 16.0;
}

void TestSCTPadding::left()
{
    QFETCH(qreal, left);
    QFETCH(qreal, expected);

    SCT::Padding padding{};
    QSignalSpy spy{&padding, &SCT::Padding::leftChanged};
    QVERIFY(spy.isValid());

    QCOMPARE(padding.left(), 0.0);
    QCOMPARE(spy.count(), 0);

    padding.setLeft(left);

    if (left > 0.0)
    {
        QCOMPARE(padding.left(), expected);
        QCOMPARE(spy.count(), 1);

        QVariantList arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toReal(), expected);
    }
}

void TestSCTPadding::bottom_data()
{
    QTest::addColumn<qreal>("bottom");
    QTest::addColumn<qreal>("expected");

    QTest::newRow("Bottom 01") <<  0.0 <<  0.0;
    QTest::newRow("Bottom 02") <<  2.0 <<  2.0;
    QTest::newRow("Bottom 03") <<  4.0 <<  4.0;
    QTest::newRow("Bottom 04") <<  8.0 <<  8.0;
    QTest::newRow("Bottom 05") << 16.0 << 16.0;
}

void TestSCTPadding::bottom()
{
    QFETCH(qreal, bottom);
    QFETCH(qreal, expected);

    SCT::Padding padding{};
    QSignalSpy spy{&padding, &SCT::Padding::bottomChanged};
    QVERIFY(spy.isValid());

    QCOMPARE(padding.bottom(), 0.0);
    QCOMPARE(spy.count(), 0);

    padding.setBottom(bottom);

    if (bottom > 0.0)
    {
        QCOMPARE(padding.bottom(), expected);
        QCOMPARE(spy.count(), 1);

        QVariantList arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toReal(), expected);
    }
}

void TestSCTPadding::right_data()
{
    QTest::addColumn<qreal>("right");
    QTest::addColumn<qreal>("expected");

    QTest::newRow("Right 01") <<  0.0 <<  0.0;
    QTest::newRow("Right 02") <<  2.0 <<  2.0;
    QTest::newRow("Right 03") <<  4.0 <<  4.0;
    QTest::newRow("Right 04") <<  8.0 <<  8.0;
    QTest::newRow("Right 05") << 16.0 << 16.0;
}

void TestSCTPadding::right()
{
    QFETCH(qreal, right);
    QFETCH(qreal, expected);

    SCT::Padding padding{};
    QSignalSpy spy{&padding, &SCT::Padding::rightChanged};
    QVERIFY(spy.isValid());

    QCOMPARE(padding.right(), 0.0);
    QCOMPARE(spy.count(), 0);

    padding.setRight(right);

    if (right > 0.0)
    {
        QCOMPARE(padding.right(), expected);
        QCOMPARE(spy.count(), 1);

        QVariantList arguments = spy.takeFirst();
        QCOMPARE(arguments.at(0).toReal(), expected);
    }
}

void TestSCTPadding::setPaddings_data()
{
    QTest::addColumn<bool>("usePaddings");
    QTest::addColumn<bool>("useQMarginFPaddings");
    QTest::addColumn<bool>("useQRectFPaddings");
    QTest::addColumn<QRectF>("paddings");

    QTest::addColumn<QRectF>("expectedPaddings");

    // [LEGEND]
    //       P: plain padding
    //       M: QMarginF variant
    //       R: QRectF variant

    QTest::newRow("Paddings 01") << false << false << false
                                 << QRectF{0.0, 0.0, 0.0, 0.0}
                                 << QRectF{0.0, 0.0, 0.0, 0.0};

    QTest::newRow("Paddings P-01") << true << false << false
                                   << QRectF{2.0, 4.0, 2.0, 4.0}
                                   << QRectF{2.0, 4.0, 2.0, 4.0};

    QTest::newRow("Paddings M-01") << false << true << false
                                   << QRectF{3.0, 8.0, 3.0, 8.0}
                                   << QRectF{3.0, 8.0, 3.0, 8.0};

    QTest::newRow("Paddings R-01") << false << false << true
                                   << QRectF{5.0, 5.0, 5.0, 5.0}
                                   << QRectF{5.0, 5.0, 5.0, 5.0};
}

void TestSCTPadding::setPaddings()
{
    QFETCH(bool, usePaddings);
    QFETCH(bool, useQMarginFPaddings);
    QFETCH(bool, useQRectFPaddings);
    QFETCH(QRectF, paddings);

    QFETCH(QRectF, expectedPaddings);

    SCT::Padding padding{};

    if (usePaddings)
    {
        padding.setPaddings(paddings.x(), paddings.y(), paddings.width(), paddings.height());
    }
    else if (useQMarginFPaddings)
    {
        QMarginsF margins{paddings.x(), paddings.y(), paddings.width(), paddings.height()};
        padding.setPaddings(margins);
    }
    else if (useQRectFPaddings)
    {
        padding.setPaddings(paddings);
    }

    QCOMPARE(padding.left(), expectedPaddings.x());
    QCOMPARE(padding.top(), expectedPaddings.y());
    QCOMPARE(padding.right(), expectedPaddings.width());
    QCOMPARE(padding.bottom(), expectedPaddings.height());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTPadding)
#include "tst_sct_padding.moc"
