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
/// -------------------------------------------------------------------------------------------- ///
/// /!\                                      WARNING                                         /!\ ///
/// -------------------------------------------------------------------------------------------- ///
///                                                                                              ///
/// This private header file is not part of StoiridhControlsTemplates API. It exists purely as   ///
/// an implementation detail for the class, Control.                                             ///
///                                                                                              ///
/// The content of this file may change from version to version without notice, or even be       ///
/// removed.                                                                                     ///
///                                                                                              ///
/// You are forewarned!                                                                          ///
///                                                                                              ///
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QtQuick/private/qquickitem_p.h>

#include <QPointer>
#include <QQuickItem>

#include "control.hpp"
#include "padding.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class ControlPrivate : public QQuickItemPrivate
{
    Q_DECLARE_PUBLIC(Control)

public:
    ControlPrivate();
    ~ControlPrivate() override;

    void init(QQuickItem *parent);

    void calculateBackgroundGeometry();
    void calculateContentGeometry();

    // members
    qreal paddings{};
    QPointer<Padding> padding;
    QPointer<QQuickItem> background;
    QPointer<QQuickItem> content;
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_CONTROL_P_HPP
