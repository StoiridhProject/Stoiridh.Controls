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
#ifndef STOIRIDHCONTROLSTEMPLATES_PADDING_HPP
#define STOIRIDHCONTROLSTEMPLATES_PADDING_HPP

#include <StoiridhControlsTemplates/global.hpp>

#include <QObject>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE
class QMarginsF;
class QRectF;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class STOIRIDH_CONTROLS_TEMPLATES_API Padding : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal left READ left WRITE setLeft NOTIFY leftChanged RESET resetLeft FINAL)
    Q_PROPERTY(qreal top READ top WRITE setTop NOTIFY topChanged RESET resetTop FINAL)
    Q_PROPERTY(qreal right READ right WRITE setRight NOTIFY rightChanged RESET resetRight FINAL)
    Q_PROPERTY(qreal bottom READ bottom WRITE setBottom NOTIFY bottomChanged RESET resetBottom FINAL)

public:
    explicit Padding(QObject *parent = nullptr);

    bool isNull() const;

    qreal left() const;
    void setLeft(qreal left);
    void resetLeft();

    qreal top() const;
    void setTop(qreal top);
    void resetTop();

    qreal right() const;
    void setRight(qreal right);
    void resetRight();

    qreal bottom() const;
    void setBottom(qreal bottom);
    void resetBottom();

    void setPaddings(qreal paddings);
    void setPaddings(qreal left, qreal top, qreal right, qreal bottom);
    void setPaddings(const QMarginsF &paddings);
    void setPaddings(const QRectF &paddings);

signals:
    void leftChanged(qreal left);
    void topChanged(qreal top);
    void rightChanged(qreal right);
    void bottomChanged(qreal bottom);

private:
    Q_DISABLE_COPY(Padding)

    qreal m_left{};
    qreal m_top{};
    qreal m_right{};
    qreal m_bottom{};
};

//--------------------------------------------------------------------------------------------------

#ifndef QT_NO_DEBUG_STREAM
STOIRIDH_CONTROLS_TEMPLATES_API QDebug operator<<(QDebug debug, const Padding &padding);
STOIRIDH_CONTROLS_TEMPLATES_API QDebug operator<<(QDebug debug, const Padding *padding);
#endif

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
QML_DECLARE_TYPE(StoiridhControlsTemplates::Padding)
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_PADDING_HPP
