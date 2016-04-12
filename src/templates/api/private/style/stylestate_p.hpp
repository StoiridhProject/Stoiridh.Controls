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
#ifndef STOIRIDHCONTROLSTEMPLATES_STYLE_STYLESTATE_P_HPP
#define STOIRIDHCONTROLSTEMPLATES_STYLE_STYLESTATE_P_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This private header file is not part of StoiridhControlsTemplates API. It exists purely as    //
//  an implementation detail for the internal class, StyleState.                                  //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "api/internal/style/stylestate.hpp"

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtQml/qqml.h>

#include <QtCore/private/qobject_p.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class StylePropertyChanges;

class StyleStatePrivate final : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(StyleState)
    using SPCListProperty = QQmlListProperty<StylePropertyChanges>;

public:
    StyleStatePrivate() = default;
    ~StyleStatePrivate() override = default;

    static StyleStatePrivate *get(StyleState *state);
    static const StyleStatePrivate *get(const StyleState *state);

    // members
    QList<StylePropertyChanges *> changes{};
    QString name{};

private:
    static void changes_append(SPCListProperty *property, StylePropertyChanges *value);
    static StylePropertyChanges *changes_at(SPCListProperty *property, int index);
    static void changes_clear(SPCListProperty *property);
    static int changes_count(SPCListProperty *property);
};

//--------------------------------------------------------------------------------------------------

/*! \internal */
inline StyleStatePrivate *StyleStatePrivate::get(StyleState *state)
{
    return state->d_func();
}

/*! \internal */
inline const StyleStatePrivate *StyleStatePrivate::get(const StyleState *state)
{
    return state->d_func();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_STYLE_STYLESTATE_P_HPP
