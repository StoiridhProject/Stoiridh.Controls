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
#include "styledispatcher.hpp"

#include "control.hpp"
#include "core/exception/exceptionhandler.hpp"

#include "api/internal/style/stylestatecontroller.hpp"

#include "api/private/style/style_p.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StyleDispatcher
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleDispatcher class dispatches a control.

    The class dispatches a control by modifying the style's state of the control.

    \sa Control
*/


/*!
    Applies a new style's state to the \a control.

    \throw NullPointerException if \a control is null.
*/
void StyleDispatcher::dispatch(const Control *control)
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    auto *const d_style = StylePrivate::get(style());

    if (auto controller = d_style->stateController().lock())
    {
        controller->apply(control);
    }
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
