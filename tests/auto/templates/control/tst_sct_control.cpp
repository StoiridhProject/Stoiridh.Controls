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

#include <StoiridhControlsTemplates/control.hpp>

namespace SCT = StoiridhControlsTemplates;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  TestCase                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestSCTControl : public QObject
{
    Q_OBJECT

private slots:
    void availableWidth_data();
    void availableWidth();

    void availableHeight_data();
    void availableHeight();

    void padding_data();
    void padding();

    void paddings_data();
    void paddings();

    void background();
    void content();

    void geometry_data();
    void geometry();
};
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Tests                                                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSCTControl::availableWidth_data()
{
    QTest::addColumn<QRectF>("padding");
    QTest::addColumn<qreal>("width");

    QTest::addColumn<qreal>("expectedAvailableWidth");

    QTest::newRow("AvailableWidth 01") << QRectF{0.0, 0.0, 0.0, 0.0} << 75.0 << 75.0;
    QTest::newRow("AvailableWidth 02") << QRectF{8.0, 0.0, 8.0, 0.0} << 16.0 <<  0.0;
    QTest::newRow("AvailableWidth 03") << QRectF{2.0, 4.0, 4.0, 2.0} << 32.0 << 26.0;
    QTest::newRow("AvailableWidth 04") << QRectF{4.0, 4.0, 8.0, 8.0} << 75.0 << 63.0;
    QTest::newRow("AvailableWidth 05") << QRectF{4.0, 4.0, 4.0, 4.0} <<  0.0 <<  0.0;
}

void TestSCTControl::availableWidth()
{
    QFETCH(QRectF, padding);
    QFETCH(qreal, width);
    QFETCH(qreal, expectedAvailableWidth);

    SCT::Control control{};
    control.setWidth(width);

    auto *p = control.padding();
    QVERIFY(p);

    p->setPaddings(padding);

    QCOMPARE(control.availableWidth(), expectedAvailableWidth);
}

void TestSCTControl::availableHeight_data()
{
    QTest::addColumn<QRectF>("padding");
    QTest::addColumn<qreal>("height");

    QTest::addColumn<qreal>("expectedAvailableHeight");

    QTest::newRow("AvailableHeight 01") << QRectF{0.0, 0.0, 0.0, 0.0} << 75.0 << 75.0;
    QTest::newRow("AvailableHeight 02") << QRectF{8.0, 0.0, 8.0, 0.0} << 16.0 << 16.0;
    QTest::newRow("AvailableHeight 03") << QRectF{2.0, 4.0, 4.0, 2.0} << 32.0 << 26.0;
    QTest::newRow("AvailableHeight 04") << QRectF{4.0, 4.0, 8.0, 8.0} << 75.0 << 63.0;
    QTest::newRow("AvailableHeight 05") << QRectF{4.0, 4.0, 4.0, 4.0} <<  0.0 <<  0.0;
}

void TestSCTControl::availableHeight()
{
    QFETCH(QRectF, padding);
    QFETCH(qreal, height);
    QFETCH(qreal, expectedAvailableHeight);

    SCT::Control control{};
    control.setHeight(height);

    auto *p = control.padding();
    QVERIFY(p);

    p->setPaddings(padding);

    QCOMPARE(control.availableHeight(), expectedAvailableHeight);
}

void TestSCTControl::padding_data()
{
    QTest::addColumn<QRectF>("padding");
    QTest::addColumn<QRectF>("expected");

    QTest::newRow("Padding 01") << QRectF{ 0.0,  0.0,  0.0,  0.0} << QRectF{ 0.0,  0.0,  0.0,  0.0};
    QTest::newRow("Padding 02") << QRectF{ 8.0,  4.0,  8.0,  4.0} << QRectF{ 8.0,  4.0,  8.0,  4.0};
    QTest::newRow("Padding 03") << QRectF{16.0, 16.0,  8.0,  8.0} << QRectF{16.0, 16.0,  8.0,  8.0};
    QTest::newRow("Padding 04") << QRectF{ 2.0,  2.0,  2.0,  2.0} << QRectF{ 2.0,  2.0,  2.0,  2.0};
    QTest::newRow("Padding 05") << QRectF{ 4.0,  8.0, 16.0, 32.0} << QRectF{ 4.0,  8.0, 16.0, 32.0};
}

void TestSCTControl::padding()
{
    QFETCH(QRectF, padding);
    QFETCH(QRectF, expected);

    SCT::Control control{};

    auto *p = control.padding();
    QVERIFY(p);

    QCOMPARE(p->left(), 0.0);
    QCOMPARE(p->top(), 0.0);
    QCOMPARE(p->right(), 0.0);
    QCOMPARE(p->bottom(), 0.0);

    p->setPaddings(padding);

    QCOMPARE(p->left(), expected.x());
    QCOMPARE(p->top(), expected.y());
    QCOMPARE(p->right(), expected.width());
    QCOMPARE(p->bottom(), expected.height());
}

void TestSCTControl::paddings_data()
{
    // data initialisation
    QTest::addColumn<qreal>("paddings");
    QTest::addColumn<QRectF>("paddingRect");

    // the grouped property 'padding' is altered without change of the global 'paddings' property
    QTest::addColumn<bool>("isAltered");
    QTest::addColumn<QRectF>("alteredPaddingRect");

    // the global 'paddings' is altered
    QTest::addColumn<bool>("isPaddingsChanged");
    QTest::addColumn<qreal>("newPaddings");

    // expected results
    QTest::addColumn<qreal>("expectedPaddings");
    QTest::addColumn<QRectF>("expectedPaddingRect");

    //         isAltered: false
    // isPaddingsChanged: false
    QTest::newRow("Paddings 01") << 0.0   << QRectF{0.0, 0.0, 0.0, 0.0}
                                 << false << QRectF{0.0, 0.0, 0.0, 0.0}
                                 << false << 0.0
                                 << 0.0   << QRectF{0.0, 0.0, 0.0, 0.0};

    QTest::newRow("Paddings 02") << 8.0   << QRectF{8.0, 8.0, 8.0, 8.0}
                                 << false << QRectF{0.0, 0.0, 0.0, 0.0}
                                 << false << 0.0
                                 << 8.0   << QRectF{8.0, 8.0, 8.0, 8.0};

    QTest::newRow("Paddings 03") << 16.0  << QRectF{16.0, 16.0, 16.0, 16.0}
                                 << false << QRectF{ 0.0,  0.0,  0.0,  0.0}
                                 << false << 0.0
                                 << 16.0  << QRectF{16.0, 16.0, 16.0, 16.0};

    QTest::newRow("Paddings 04") << 32.0  << QRectF{32.0, 32.0, 32.0, 32.0}
                                 << false << QRectF{ 0.0,  0.0,  0.0,  0.0}
                                 << false << 0.0
                                 << 32.0  << QRectF{32.0, 32.0, 32.0, 32.0};

    QTest::newRow("Paddings 05") << 64.0  << QRectF{64.0, 64.0, 64.0, 64.0}
                                 << false << QRectF{ 0.0,  0.0,  0.0,  0.0}
                                 << false << 0.0
                                 << 64.0  << QRectF{64.0, 64.0, 64.0, 64.0};

    //         isAltered: true
    // isPaddingsChanged: false
    QTest::newRow("Paddings A-01") << 0.0   << QRectF{0.0, 0.0, 0.0, 0.0}
                                   << true  << QRectF{0.0, 4.0, 0.0, 4.0}
                                   << false << 0.0
                                   << 0.0   << QRectF{0.0, 4.0, 0.0, 4.0};

    QTest::newRow("Paddings A-02") << 8.0   << QRectF{ 8.0, 8.0, 8.0, 8.0}
                                   << true  << QRectF{16.0, 8.0, 8.0, 8.0}
                                   << false << 0.0
                                   << 8.0   << QRectF{16.0, 8.0, 8.0, 8.0};

    QTest::newRow("Paddings A-03") << 16.0  << QRectF{16.0, 16.0, 16.0, 16.0}
                                   << true  << QRectF{ 0.0,  0.0,  0.0,  0.0}
                                   << false << 0.0
                                   << 16.0  << QRectF{0.0, 0.0, 0.0, 0.0};

    QTest::newRow("Paddings A-04") << 32.0  << QRectF{32.0, 32.0, 32.0, 32.0}
                                   << true  << QRectF{ 8.0,  8.0,  8.0,  8.0}
                                   << false << 0.0
                                   << 32.0  << QRectF{8.0, 8.0, 8.0, 8.0};

    QTest::newRow("Paddings A-05") << 64.0  << QRectF{64.0, 64.0, 64.0, 64.0}
                                   << true  << QRectF{32.0, 16.0, 32.0, 16.0}
                                   << false << 0.0
                                   << 64.0  << QRectF{32.0, 16.0, 32.0, 16.0};

    //         isAltered: true
    // isPaddingsChanged: true
    QTest::newRow("Paddings AP-01") << 0.0  << QRectF{0.0, 0.0, 0.0, 0.0}
                                    << true << QRectF{4.0, 4.0, 4.0, 4.0}
                                    << true << 64.0
                                    << 64.0 << QRectF{64.0, 64.0, 64.0, 64.0};

    QTest::newRow("Paddings AP-02") << 8.0  << QRectF{8.0, 8.0, 8.0, 8.0}
                                    << true << QRectF{8.0, 0.0, 8.0, 0.0}
                                    << true << 32.0
                                    << 32.0 << QRectF{32.0, 32.0, 32.0, 32.0};

    QTest::newRow("Paddings AP-03") << 16.0 << QRectF{16.0, 16.0, 16.0, 16.0}
                                    << true << QRectF{ 8.0, 16.0,  8.0, 16.0}
                                    << true << 16.0
                                    << 16.0 << QRectF{8.0, 16.0, 8.0, 16.0};

    QTest::newRow("Paddings AP-04") << 32.0 << QRectF{32.0, 32.0, 32.0, 32.0}
                                    << true << QRectF{16.0, 32.0, 32.0, 32.0}
                                    << true << 8.0
                                    << 8.0  << QRectF{8.0, 8.0, 8.0, 8.0};

    QTest::newRow("Paddings AP-05") << 64.0 << QRectF{64.0, 64.0, 64.0, 64.0}
                                    << true << QRectF{ 8.0, 16.0,  8.0, 16.0}
                                    << true << 0.0
                                    << 0.0  << QRectF{0.0, 0.0, 0.0, 0.0};
}

void TestSCTControl::paddings()
{
    QFETCH(qreal, paddings);
    QFETCH(QRectF, paddingRect);

    QFETCH(bool, isAltered);
    QFETCH(QRectF, alteredPaddingRect);

    QFETCH(bool, isPaddingsChanged);
    QFETCH(qreal, newPaddings);

    QFETCH(qreal, expectedPaddings);
    QFETCH(QRectF, expectedPaddingRect);

    SCT::Control control{};
    QSignalSpy spy{&control, &SCT::Control::paddingsChanged};
    int spyCount{};

    QVERIFY(spy.isValid());
    QCOMPARE(control.paddings(), 0.0);
    QVERIFY(spy.isEmpty());

    if (control.paddings() != paddings)
        spyCount++;

    control.setPaddings(paddings);

    QCOMPARE(control.paddings(), paddings);
    QCOMPARE(spy.count(), spyCount);

    auto *p = control.padding();
    QVERIFY(p);

    QCOMPARE(p->left(), paddingRect.x());
    QCOMPARE(p->top(), paddingRect.y());
    QCOMPARE(p->right(), paddingRect.width());
    QCOMPARE(p->bottom(), paddingRect.height());

    if (isAltered)
    {
        p->setLeft(alteredPaddingRect.x());
        p->setTop(alteredPaddingRect.y());
        p->setRight(alteredPaddingRect.width());
        p->setBottom(alteredPaddingRect.height());
    }

    if (isPaddingsChanged)
    {
        if (control.paddings() != newPaddings)
            spyCount++;

        control.setPaddings(newPaddings);
    }

    QCOMPARE(control.paddings(), expectedPaddings);
    QCOMPARE(spy.count(), spyCount);

    QCOMPARE(p->left(), expectedPaddingRect.x());
    QCOMPARE(p->top(), expectedPaddingRect.y());
    QCOMPARE(p->right(), expectedPaddingRect.width());
    QCOMPARE(p->bottom(), expectedPaddingRect.height());
}

void TestSCTControl::background()
{
    SCT::Control control{};
    QSignalSpy spy{&control, &SCT::Control::backgroundChanged};

    QVERIFY(spy.isValid());
    QVERIFY(spy.isEmpty());
    QVERIFY(!control.background());

    QScopedPointer<QQuickItem> backgroundItem{new QQuickItem{}};
    QVERIFY(!backgroundItem.isNull());

    control.setBackground(backgroundItem.data());

    QVERIFY(control.background());
    QCOMPARE(control.background()->z(), -1.0);

    QCOMPARE(control.background()->parentItem(), &control);
    QCOMPARE(spy.count(), 1);
}

void TestSCTControl::content()
{
    SCT::Control control{};
    QSignalSpy spy{&control, &SCT::Control::contentChanged};

    QVERIFY(spy.isValid());
    QVERIFY(spy.isEmpty());
    QVERIFY(!control.content());

    QScopedPointer<QQuickItem> contentItem{new QQuickItem{}};
    QVERIFY(!contentItem.isNull());

    control.setContent(contentItem.data());

    QVERIFY(control.content());

    QCOMPARE(control.content()->parentItem(), &control);
    QCOMPARE(spy.count(), 1);
}

void TestSCTControl::geometry_data()
{
    // control's padding
    QTest::addColumn<bool>("useGlobalPaddings");
    QTest::addColumn<qreal>("globalPaddings");
    QTest::addColumn<QRectF>("padding");

    // control's geometry
    QTest::addColumn<bool>("useControlImplicitSize");
    QTest::addColumn<QRectF>("controlGeometry");
    QTest::addColumn<QSizeF>("controlImplicitSize");

    // background control's geometry
    QTest::addColumn<bool>("useBackgroundImplicitSize");
    QTest::addColumn<QRectF>("backgroundGeometry");
    QTest::addColumn<QSizeF>("backgroundImplicitSize");

    // content control's geometry
    QTest::addColumn<bool>("useContentImplicitSize");
    QTest::addColumn<QRectF>("contentGeometry");
    QTest::addColumn<QSizeF>("contentImplicitSize");

    // expected results
    QTest::addColumn<QRectF>("expectedControlGeometry");
    QTest::addColumn<QRectF>("expectedBackgroundGeometry");
    QTest::addColumn<QRectF>("expectedContentGeometry");

    // [LEGEND]
    //      GP: Global Padding
    //       C: Control
    //       B: Background
    //      Ct: Content

    // without using global padding
    QTest::newRow("Geometry 01")
            << false                          << 0.0                            << QRectF{0.0, 0.0,  0.0,  0.0}
            << false                          << QRectF{48.0, 48.0, 75.0, 25.0} << QSizeF{0.0, 0.0}
            << false                          << QRectF{ 0.0,  0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << false                          << QRectF{ 0.0,  0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << QRectF{48.0, 48.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0};
    QTest::newRow("Geometry 02")
            << false                          << 0.0                            << QRectF{2.0, 4.0,  2.0,  4.0}
            << false                          << QRectF{48.0, 48.0, 75.0, 25.0} << QSizeF{0.0, 0.0}
            << false                          << QRectF{ 0.0,  0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << false                          << QRectF{ 0.0,  0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << QRectF{48.0, 48.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0} << QRectF{2.0, 4.0, 71.0, 17.0};

    QTest::newRow("Geometry Ct-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{ 0.0,  0.0, 64.0, 64.0};
    QTest::newRow("Geometry Ct-02")
            << false                        << 0.0                          << QRectF{ 2.0,  4.0, 2.0,  4.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << QRectF{0.0, 0.0, 68.0, 72.0} << QRectF{0.0, 0.0, 68.0, 72.0} << QRectF{ 2.0,  4.0, 64.0, 64.0};

    QTest::newRow("Geometry B-01")
            << false                         << 0.0                           << QRectF{  0.0,  0.0,   0.0,  0.0}
            << false                         << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{  0.0,  0.0}
            << true                          << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{120.0, 80.0}
            << false                         << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{  0.0,  0.0}
            << QRectF{0.0, 0.0, 120.0, 80.0} << QRectF{0.0, 0.0, 120.0, 80.0} << QRectF{  0.0,  0.0, 120.0, 80.0};
    QTest::newRow("Geometry B-02")
            << false                         << 0.0                           << QRectF{  8.0,  8.0,   8.0,  8.0}
            << false                         << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{  0.0,  0.0}
            << true                          << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{120.0, 80.0}
            << false                         << QRectF{0.0, 0.0,   0.0,  0.0} << QSizeF{  0.0,  0.0}
            << QRectF{0.0, 0.0, 120.0, 80.0} << QRectF{0.0, 0.0, 120.0, 80.0} << QRectF{  8.0,  8.0, 104.0, 64.0};

    QTest::newRow("Geometry BCt-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 25.0, 25.0};
    QTest::newRow("Geometry BCt-02")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{15.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << QRectF{0.0, 0.0, 25.0, 25.0} << QRectF{0.0, 0.0, 25.0, 25.0} << QRectF{ 0.0,  0.0, 25.0, 25.0};
    QTest::newRow("Geometry BCt-03")
            << false                        << 0.0                          << QRectF{ 4.0,  4.0, 4.0, 4.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << QRectF{0.0, 0.0, 75.0, 33.0} << QRectF{0.0, 0.0, 75.0, 33.0} << QRectF{ 4.0,  4.0, 25.0, 25.0};
    QTest::newRow("Geometry BCt-04")
            << false                        << 0.0                          << QRectF{ 2.0,  4.0, 2.0, 4.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{15.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << QRectF{0.0, 0.0, 29.0, 33.0} << QRectF{0.0, 0.0, 29.0, 33.0} << QRectF{ 2.0,  4.0, 25.0, 25.0};

    QTest::newRow("Geometry C-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0};
    QTest::newRow("Geometry C-02")
            << false                        << 0.0                          << QRectF{ 4.0,  4.0, 4.0, 4.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 4.0,  4.0, 67.0, 17.0};

    QTest::newRow("Geometry CCt-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{69.0, 69.0}
            << QRectF{0.0, 0.0, 75.0, 69.0} << QRectF{0.0, 0.0, 75.0, 69.0} << QRectF{ 0.0,  0.0, 69.0, 69.0};
    QTest::newRow("Geometry CCt-02")
            << false                        << 0.0                          << QRectF{ 4.0,  4.0,  4.0,  4.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{69.0, 69.0}
            << QRectF{0.0, 0.0, 77.0, 77.0} << QRectF{0.0, 0.0, 77.0, 77.0} << QRectF{ 4.0,  4.0, 69.0, 69.0};

    QTest::newRow("Geometry CB-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0};
    QTest::newRow("Geometry CB-02")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0};
    QTest::newRow("Geometry CB-03")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{85.0, 30.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 85.0, 30.0} << QRectF{0.0, 0.0, 85.0, 30.0} << QRectF{ 0.0,  0.0, 85.0, 30.0};
    QTest::newRow("Geometry CB-04")
            << false                        << 0.0                          << QRectF{ 4.0,  4.0,  2.0,  2.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{85.0, 30.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 85.0, 30.0} << QRectF{0.0, 0.0, 85.0, 30.0} << QRectF{ 4.0,  4.0, 79.0, 24.0};

    QTest::newRow("Geometry CBCt-01")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 0.0,  0.0, 75.0, 25.0};
    QTest::newRow("Geometry CBCt-02")
            << false                        << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{30.0, 60.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << QRectF{0.0, 0.0, 75.0, 64.0} << QRectF{0.0, 0.0, 75.0, 64.0} << QRectF{ 0.0,  0.0, 64.0, 64.0};
    QTest::newRow("Geometry CBCt-03")
            << false                        << 0.0                          << QRectF{ 4.0,  8.0,  4.0,  8.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{30.0, 60.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << QRectF{0.0, 0.0, 75.0, 80.0} << QRectF{0.0, 0.0, 75.0, 80.0} << QRectF{ 4.0,  8.0, 64.0, 64.0};


    // using global padding
    QTest::newRow("Geometry GP-01")
            << true                       << 16.0                       << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << false                      << QRectF{0.0, 0.0, 0.0, 0.0} << QSizeF{ 0.0,  0.0}
            << false                      << QRectF{0.0, 0.0, 0.0, 0.0} << QSizeF{ 0.0,  0.0}
            << false                      << QRectF{0.0, 0.0, 0.0, 0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 0.0, 0.0} << QRectF{0.0, 0.0, 0.0, 0.0} << QRectF{16.0, 16.0, 0.0, 0.0};
    QTest::newRow("Geometry GP-02")
            << true                         << 16.0                         << QRectF{ 0.0,  0.0,  0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 75.0, 25.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{16.0, 16.0, 43.0, 0.0};
    QTest::newRow("Geometry GP-03")
            << true                         << 8.0                          << QRectF{0.0, 0.0,  0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 75.0, 25.0} << QSizeF{0.0, 0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{0.0, 0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{8.0, 8.0, 59.0, 9.0};

    QTest::newRow("Geometry GPCt-01")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{ 4.0,  4.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCt-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 16.0, 16.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 16.0, 16.0} << QRectF{0.0, 0.0, 16.0, 16.0} << QRectF{ 4.0,  4.0, 8.0, 8.0};
    QTest::newRow("Geometry GPCt-03")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 48.0, 48.0} << QRectF{0.0, 0.0, 48.0, 48.0} << QRectF{ 8.0,  8.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCt-04")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0, 0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 16.0, 16.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 16.0, 16.0} << QRectF{0.0, 0.0, 16.0, 16.0} << QRectF{ 8.0,  8.0, 0.0, 0.0};

    QTest::newRow("Geometry GPB-01")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 4.0,  4.0, 67.0, 17.0};
    QTest::newRow("Geometry GPB-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 50.0, 15.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 50.0, 15.0} << QRectF{0.0, 0.0, 50.0, 15.0} << QRectF{ 4.0,  4.0, 42.0, 7.0};
    QTest::newRow("Geometry GPB-03")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0,  0.0, 0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{0.0, 0.0, 75.0, 25.0} << QRectF{ 8.0,  8.0, 59.0, 9.0};
    QTest::newRow("Geometry GPB-04")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0,  0.0, 0.0}
            << false                        << QRectF{0.0, 0.0, 50.0, 15.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 50.0, 15.0} << QRectF{0.0, 0.0, 50.0, 15.0} << QRectF{ 8.0,  8.0, 34.0, 0.0};

    QTest::newRow("Geometry GPBCt-01")
            << true                         << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{ 0.0,  0.0, 32.0, 32.0};
    QTest::newRow("Geometry GPBCt-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0, 32.0, 32.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{ 4.0,  4.0, 24.0, 24.0};
    QTest::newRow("Geometry GPBCt-03")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{75.0, 25.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 75.0, 48.0} << QRectF{0.0, 0.0, 75.0, 48.0} << QRectF{ 8.0,  8.0, 32.0, 32.0};
    QTest::newRow("Geometry GPBCt-04")
            << true                         << 8.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << false                        << QRectF{0.0, 0.0, 64.0, 32.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 64.0, 32.0} << QRectF{0.0, 0.0, 64.0, 32.0} << QRectF{ 8.0,  8.0, 32.0, 16.0};

    QTest::newRow("Geometry GPC-01")
            << true                         << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{ 0.0,  0.0, 32.0, 32.0};
    QTest::newRow("Geometry GPC-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{ 4.0,  4.0, 24.0, 24.0};

    QTest::newRow("Geometry GPCCt-01")
            << true                         << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{ 0.0,  0.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCCt-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{25.0, 25.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{ 4.0,  4.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCCt-03")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{64.0, 64.0}
            << false                        << QRectF{0.0, 0.0, 75.0, 25.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{0.0, 0.0, 64.0, 64.0} << QRectF{ 4.0,  4.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCCt-04")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 64.0}
            << false                        << QRectF{0.0, 0.0, 75.0, 25.0} << QSizeF{ 0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 40.0, 64.0} << QRectF{0.0, 0.0, 40.0, 64.0} << QRectF{ 4.0,  4.0, 32.0, 32.0};

    QTest::newRow("Geometry GPCB-01")
            << true                         << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << false                        << QRectF{0.0, 0.0, 32.0, 32.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 24.0, 24.0} << QRectF{0.0, 0.0, 24.0, 24.0} << QRectF{ 0.0,  0.0, 24.0, 24.0};
    QTest::newRow("Geometry GPCB-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << false                        << QRectF{0.0, 0.0, 32.0, 32.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 24.0, 24.0} << QRectF{0.0, 0.0, 24.0, 24.0} << QRectF{ 4.0,  4.0, 16.0, 16.0};
    QTest::newRow("Geometry GPCB-03")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << false                        << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{ 0.0,  0.0}
            << QRectF{0.0, 0.0, 32.0, 24.0} << QRectF{0.0, 0.0, 32.0, 24.0} << QRectF{ 4.0,  4.0, 24.0, 16.0};

    QTest::newRow("Geometry GPCBCt-01")
            << true                         << 0.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{0.0, 0.0, 32.0, 32.0} << QRectF{ 0.0,  0.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCBCt-02")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{32.0, 32.0}
            << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{0.0, 0.0, 40.0, 40.0} << QRectF{ 4.0,  4.0, 32.0, 32.0};
    QTest::newRow("Geometry GPCBCt-03")
            << true                         << 4.0                          << QRectF{ 0.0,  0.0,  0.0,  0.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 16.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{24.0, 24.0}
            << true                         << QRectF{0.0, 0.0,  0.0,  0.0} << QSizeF{16.0, 32.0}
            << QRectF{0.0, 0.0, 24.0, 40.0} << QRectF{0.0, 0.0, 24.0, 40.0} << QRectF{ 4.0,  4.0, 16.0, 32.0};
}

void TestSCTControl::geometry()
{
    QFETCH(bool, useGlobalPaddings);
    QFETCH(qreal, globalPaddings);
    QFETCH(QRectF, padding);

    QFETCH(bool, useControlImplicitSize);
    QFETCH(QRectF, controlGeometry);
    QFETCH(QSizeF, controlImplicitSize);

    QFETCH(bool, useBackgroundImplicitSize);
    QFETCH(QRectF, backgroundGeometry);
    QFETCH(QSizeF, backgroundImplicitSize);

    QFETCH(bool, useContentImplicitSize);
    QFETCH(QRectF, contentGeometry);
    QFETCH(QSizeF, contentImplicitSize);

    QFETCH(QRectF, expectedControlGeometry);
    QFETCH(QRectF, expectedBackgroundGeometry);
    QFETCH(QRectF, expectedContentGeometry);

    SCT::Control control{};
    control.setPosition(controlGeometry.topLeft());

    if (useControlImplicitSize)
    {
        control.setImplicitWidth(controlImplicitSize.width());
        control.setImplicitHeight(controlImplicitSize.height());
    }
    else
    {
        if (!controlGeometry.isNull())
            control.setSize(controlGeometry.size());
    }

    if (useGlobalPaddings)
    {
        control.setPaddings(globalPaddings);
    }
    else
    {
        auto *p = control.padding();
        QVERIFY(p);

        p->setPaddings(padding);
    }

    QVERIFY(!control.background());
    QVERIFY(!control.content());

    QScopedPointer<QQuickItem> backgroundItem{new QQuickItem{}};
    QVERIFY(!backgroundItem.isNull());

    backgroundItem->setPosition(backgroundGeometry.topLeft());

    if (useBackgroundImplicitSize)
    {
        backgroundItem->setImplicitWidth(backgroundImplicitSize.width());
        backgroundItem->setImplicitHeight(backgroundImplicitSize.height());
    }
    else
    {
        if (!backgroundGeometry.isNull())
            backgroundItem->setSize(backgroundGeometry.size());
    }

    QScopedPointer<QQuickItem> contentItem{new QQuickItem{}};
    QVERIFY(!contentItem.isNull());

    contentItem->setPosition(contentGeometry.topLeft());

    if (useContentImplicitSize)
    {
        contentItem->setImplicitWidth(contentImplicitSize.width());
        contentItem->setImplicitHeight(contentImplicitSize.height());
    }
    else
    {
        if (!contentGeometry.isNull())
            contentItem->setSize(contentGeometry.size());
    }

    control.setBackground(backgroundItem.data());
    control.setContent(contentItem.data());

    QVERIFY(control.background());
    QVERIFY(control.content());

    QCOMPARE(control.x(), expectedControlGeometry.x());
    QCOMPARE(control.y(), expectedControlGeometry.y());
    QCOMPARE(control.width(), expectedControlGeometry.width());
    QCOMPARE(control.height(), expectedControlGeometry.height());

    const auto *background = control.background();
    QCOMPARE(background->x(), expectedBackgroundGeometry.x());
    QCOMPARE(background->y(), expectedBackgroundGeometry.y());
    QCOMPARE(background->width(), expectedBackgroundGeometry.width());
    QCOMPARE(background->height(), expectedBackgroundGeometry.height());

    const auto *content = control.content();
    QCOMPARE(content->x(), expectedContentGeometry.x());
    QCOMPARE(content->y(), expectedContentGeometry.y());
    QCOMPARE(content->width(), expectedContentGeometry.width());
    QCOMPARE(content->height(), expectedContentGeometry.height());
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//  Run                                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
QTEST_APPLESS_MAIN(TestSCTControl)
#include "tst_sct_control.moc"
