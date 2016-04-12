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
#include "stylestate.hpp"

#include "api/internal/style/stylepropertychanges.hpp"

#include "api/private/style/stylestate_p.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StyleState
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleState class represents a state for a Style.
*/


/*!
    Construts a style's state with the given \a parent.
*/
StyleState::StyleState(QObject *parent)
    : StyleState{*(new StyleStatePrivate{}), parent}
{

}

/*! \internal */
StyleState::StyleState(StyleStatePrivate &dd, QObject *parent)
    : QObject{dd, parent}
{

}

/*! \property StyleState::changes()

    This default property holds the StylePropertyChanges of the style's state.

    \access

    <table>
      <tr>
        <td>QQmlListProperty<StoiridhControlsTemplates::StylePropertyChanges></td>
        <td><b>changes()</b></td>
      </tr>
    </table>
*/
QQmlListProperty<StylePropertyChanges> StyleState::changes()
{
    Q_D(StyleState);
    return {this, &d->changes,
                &StyleStatePrivate::changes_append,
                &StyleStatePrivate::changes_count,
                &StyleStatePrivate::changes_at,
                &StyleStatePrivate::changes_clear};
}

/*! \property QString StyleState::name

    This property holds the name of the style's state.

    \warning \a name must not be an empty string.

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
QString StyleState::name() const
{
    Q_D(const StyleState);
    return d->name;
}

void StyleState::setName(const QString &name)
{
    Q_D(StyleState);
    if (d->name != name)
    {
        d->name = name;
        emit nameChanged();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   PRIVATE API    /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class StoiridhControlsTemplates::StyleStatePrivate
    \internal
*/

void StyleStatePrivate::changes_append(SPCListProperty *property, StylePropertyChanges *value)
{
    auto *const changes = static_cast<QList<StylePropertyChanges *>*>(property->data);
    changes->append(value);
}

StylePropertyChanges *StyleStatePrivate::changes_at(SPCListProperty *property, int index)
{
    const auto *const changes = static_cast<QList<StylePropertyChanges *>*>(property->data);
    return changes->at(index);
}

void StyleStatePrivate::changes_clear(SPCListProperty *property)
{
    auto *const changes = static_cast<QList<StylePropertyChanges *>*>(property->data);
    changes->clear();
}

int StyleStatePrivate::changes_count(SPCListProperty *property)
{
    const auto *const changes = static_cast<QList<StylePropertyChanges *>*>(property->data);
    return changes->count();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
