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
#include "style.hpp"

#include "api/internal/style/abstractstyledispatcher.hpp"
#include "api/internal/style/stylestate.hpp"

#include "api/private/style/style_p.hpp"

#include <QtCore/QPointer>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class Style
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The Style class allows to customise the appearance of the control.

    The class describes the appearance of the control. It may contain several StyleState defined
    from QML allowing to change the appearance of the control for a state at a given moment.

    Example:

    \code
    Button {
        id: button

        // ...

        style: Style {
            name: "Button"
        }
    }
    \endcode

    A name may be set to a style in order to apply a custom style name for a control. If there is
    not name defined for the style, then the style's name will be the name of the QML module
    concatenated with the QML type name of the control.

    \sa StyleState
*/


/*!
    Constructs a style with the given \a parent.
*/
Style::Style(QObject *parent)
    : Style{*(new StylePrivate{}), parent}
{

}

/*! \internal */
Style::Style(StylePrivate &dd, QObject *parent)
    : QObject{dd, parent}
{
    dd.init();
}

/*! \property QQmlListProperty<StoiridhControlsTemplates::StyleState> Style::states

    This default property holds the StyleState of the style.

    \access

    <table>
      <tr>
        <td>QQmlListProperty<StoiridhControlsTemplates::StyleState></td>
        <td><b>states()</b></td>
      </tr>
    </table>
*/
QQmlListProperty<StoiridhControlsTemplates::StyleState> Style::states()
{
    Q_D(Style);
    return {this, &d->states,
                &StylePrivate::style_state_append,
                &StylePrivate::style_state_count,
                &StylePrivate::style_state_at,
                &StylePrivate::style_state_clear};
}

/*! \property QString Style::name

    This optional property holds the name of the style.

    \access

    <table>
      <tr>
        <td>QString</td>
        <td><b>name() const</b></td>
      </tr>
      <tr>
        <td>void</td>
        <td><b>setName(const QString &name)</b></td>
      </tr>
    </table>

    \notifier_signal

    <table>
      <tr>
        <td>void</td>
        <td>nameChanged()</td>
      </tr>
    </table>
*/
QString Style::name() const
{
    Q_D(const Style);
    return d->name;
}

void Style::setName(const QString &name)
{
    Q_D(Style);

    if (d->name != name)
    {
        d->name = name;
        emit nameChanged();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   PRIVATE API    /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class StoiridhControlsTemplates::StylePrivate
    \internal
*/

/*!
    Initialises the data members.
*/
void StylePrivate::init()
{
    Q_Q(Style);
    m_stateController = QSharedPointer<StyleStateController>::create(q);
}

/*!
    Returns the style dispatcher attached to this style.

    \sa setStyleDispatcher()
*/
AbstractStyleDispatcher *StylePrivate::styleDispatcher() const
{
    return m_dispatcher;
}

/*!
    Sets a \a dispatcher for the style.

    \note Generally, it is set by the dispatcher itself when a style is attached.
    \sa styleDispatcher()
*/
void StylePrivate::setStyleDispatcher(AbstractStyleDispatcher *dispatcher)
{
    if (m_dispatcher != dispatcher)
    {
        m_dispatcher = dispatcher;
    }
}

/*!
    Returns the style state controller.

    \note This method will always return a valid StyleStateController object.
    \sa StyleStateController
*/
QWeakPointer<StyleStateController> StylePrivate::stateController() const
{
    return m_stateController.toWeakRef();
}

void StylePrivate::style_state_append(StyleStateListProperty *property, StyleState *value)
{
    auto *const states = static_cast<QList<StyleState *>*>(property->data);

    if (value)
    {
        states->append(value);
    }
}

StyleState *StylePrivate::style_state_at(StyleStateListProperty *property, int index)
{
    const auto *const states = static_cast<QList<StyleState *>*>(property->data);
    return states->at(index);
}

void StylePrivate::style_state_clear(StyleStateListProperty *property)
{
    auto *const states = static_cast<QList<StyleState *>*>(property->data);
    states->clear();
}

int StylePrivate::style_state_count(StyleStateListProperty *property)
{
    const auto *const states = static_cast<QList<StyleState *>*>(property->data);
    return states->count();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////   DOCUMENTATION    ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \signal void Style::nameChanged()

    This signal is emmitted when the style's name changes.
*/

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
