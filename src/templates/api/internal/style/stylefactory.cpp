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
#include "stylefactory.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

QHash<QString, AbstractStyleDispatcher *> StyleFactory::m_dispatchers{};


/*! \class StyleFactory
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleFactory class allows to create or reuse a style for a control of the same type.

    \section introduction Introduction

    The StyleFactory class provides a mechanism to avoid style duplication between controls of the
    same type. This mechanism has two distinct roles: creation and reusability.

    The \b creation of a style is the first step, when the control's signature of an control is not
    registered in the factory. This mechanism will create all steps required in order to be used by
    the control. This task is done via the
    \l{StyleFactoryHelper::createStyleStatesOperations(),createStyleStatesOperations()} method.

    The \b reusability of a style is a mechanism that allows to map a Control to an existing style
    via its control's signature. If the mapping is successful, then the control's style will be
    deleted later.

    All process described above is automatically done in the Control::componentComplete() method.
    No further action is required by the programmer to complete this task.

    \subsection control_signature Control's signature

    The StyleFactory class uses the concept of control's signature in order to determine whether a
    style must be created or reused for another control of the same signature.

    The control's signature allows to identify the kind of control. Generally, the control's
    signature is compounded of the module's name and control's name.

    In the example below, we see the simplified template implementation of the Button (Button.qml)
    provided by the Stoiridh.Controls QML module.

    Example:

    \code
    import QtQuick 2.6
    import Stoiridh.Controls.Private 1.0

    Button {
        id: button

        // ...

        style: Style {
            // ...
        }
    }
    \endcode

    The control's signature for the control above will be <tt>Stoiridh.Controls.Private/Button</tt>.

    \subsection memory_handling Memory Handling

    Each time a style is created from the StyleFactory, the style is associated with an
    AbstractStyleDispatcher. The AbstractStyleDispatcher created is handled by the StyleFactory and
    will be automatically destroyed when the user will quit the application.

    \subsection activity_diagram Activity Diagram

    The activity diagram below shows the working process of the style factory when the QML engine
    loads and parses a QML file:

    \image html sct_style_factory_25p.png

    \sa StyleFactoryHelper
*/


/*!
    Destroys all style dispatchers created from the style factory.

    \note Generally, you will never call this method.
*/
void StyleFactory::destroy()
{
    qDeleteAll(m_dispatchers);
    m_dispatchers.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \fn Style *StyleFactory::create(const Control *control)

    Creates a style for a \a control.

    \tparam T must be a base of AbstractStyleDispatcher.

    \pre the \a control must have a non-null style.

    \throw NullPointerException if \a control is null.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
