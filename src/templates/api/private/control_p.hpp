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
#ifndef STOIRIDHCONTROLSTEMPLATES_CONTROL_P_HPP
#define STOIRIDHCONTROLSTEMPLATES_CONTROL_P_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This private header file is not part of StoiridhControlsTemplates API. It exists purely as    //
//  an implementation detail for the class, Control.                                              //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "control.hpp"
#include "padding.hpp"

#include "api/internal/abstractcontrol.hpp"

#include <QtCore/QPointer>

#include <QtQuick/private/qquickitem_p.h>

#include <type_traits>

QT_BEGIN_NAMESPACE
class QQuickItem;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class Style;

class ControlPrivate : public QQuickItemPrivate, public AbstractControl
{
    Q_DECLARE_PUBLIC(Control)

public:
    ControlPrivate() = default;
    virtual ~ControlPrivate() override = default;

    static ControlPrivate *get(Control *control);
    static const ControlPrivate *get(const Control *control);

    void init(QQuickItem *parent);
    void accept(AbstractStyleDispatcher *dispatcher) override final;

    StoiridhControlsTemplates::Style *style() const;
    void setStyle(StoiridhControlsTemplates::Style *style);
    void updateStyle();

    QString styleState() const;

    template<typename T>
    void updateStyleState(T currentState);

    virtual void initialiseDefaultStyleState();

    void calculateBackgroundGeometry();
    void calculateContentGeometry();

    // members
    qreal paddings{};
    QPointer<Padding> padding{};
    QPointer<QQuickItem> background{};
    QPointer<QQuickItem> content{};

private:
    QPointer<Style> m_style{};
    QString m_styleState{};
};

//--------------------------------------------------------------------------------------------------

/*! \internal */
inline ControlPrivate *ControlPrivate::get(Control *control)
{
    return control->d_func();
}

/*! \internal */
inline const ControlPrivate *ControlPrivate::get(const Control *control)
{
    return control->d_func();
}

template<typename T>
void ControlPrivate::updateStyleState(T currentState)
{
    static_assert(std::is_enum<T>::value, "T is not an enumeration type.");

    auto metaEnum = QMetaEnum::fromType<T>();
    m_styleState = QString::fromUtf8(metaEnum.key(static_cast<int>(currentState)));
    updateStyle();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_CONTROL_P_HPP
