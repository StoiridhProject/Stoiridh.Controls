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
#include "abstractstyledispatcher.hpp"

#include "core/exception/exceptionhandler.hpp"

#include "api/internal/style/style.hpp"

#include "api/private/style/style_p.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class AbstractStyleDispatcher
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The AbstractStyleDispatcher class is a base class to dispatch a style to a control.

    The class defines the methods shared by all style dispatchers. By inheriting this class, you
    can create custom style dispatcher in order to modify the current style's state of a control.

    AbstractStyleDispatcher provides a pure virtual method used by subclasses to dispatch a control:
    dispatch(). The dispatch() method lets you to change the style's state of a control provided
    that the control has the same style that the AbstractStyleDispatcher.

    \note When a style is given to the AbstractStyleDispatcher class, it becomes responsible for the
    life-cycle of the style.

    \sa StyleDispatcher
*/


/*!
    Constructs an abstract style dispatcher with the given \a style and \a parent.

    \throw NullPointerException if \a style is null.
*/
AbstractStyleDispatcher::AbstractStyleDispatcher(Style *style, QObject *parent)
    : QObject{parent}
    , m_style{style}
{
    ExceptionHandler::checkNullPointer(style, QStringLiteral("style"), QStringLiteral("Style *"));

    m_style->setParent(this);

    auto *const d_style = StylePrivate::get(m_style);
    d_style->setStyleDispatcher(this);
}

/*!
    Returns the style related to the dispatcher.
*/
Style *AbstractStyleDispatcher::style() const noexcept
{
    return m_style;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \fn virtual AbstractStyleDispatcher::~AbstractStyleDispatcher() override = default

    Destroys this abstract style dispatcher.
*/

/*! \fn virtual void AbstractStyleDispatcher::dispatch(const Control *control) = 0

    Dispatches the style to the \a control.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
