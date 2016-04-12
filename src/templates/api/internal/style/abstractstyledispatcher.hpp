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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_ABSTRACTSTYLEDISPATCHER_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_ABSTRACTSTYLEDISPATCHER_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This internal header file is not part of StoiridhControlsTemplates API. It exists purely as   //
//  an internal use and must not be used in external project(s).                                  //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "api/internal/global.hpp"

#include <QtCore/QObject>
#include <QtCore/QPointer>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class Control;
class Style;

class SCT_INTERNAL_API AbstractStyleDispatcher : public QObject
{
    Q_OBJECT

public:
    explicit AbstractStyleDispatcher(Style *style, QObject *parent = nullptr);
    virtual ~AbstractStyleDispatcher() override = default;

    Style *style() const noexcept;

    virtual void dispatch(const Control *control) = 0;

private:
    Q_DISABLE_COPY(AbstractStyleDispatcher)

    QPointer<Style> m_style{};
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_ABSTRACTSTYLEDISPATCHER_HPP
