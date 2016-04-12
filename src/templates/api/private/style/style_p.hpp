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
#ifndef STOIRIDHCONTROLSTEMPLATES_STYLE_STYLE_P_HPP
#define STOIRIDHCONTROLSTEMPLATES_STYLE_STYLE_P_HPP

////////////////////////////////////////////////////////////////////////////////////////////////////
//  --------------------------------------------------------------------------------------------  //
//  /!\                                     W A R N I N G                                    /!\  //
//  --------------------------------------------------------------------------------------------  //
//                                                                                                //
//  This private header file is not part of StoiridhControlsTemplates API. It exists purely as    //
//  an implementation detail for the internal class, Style.                                       //
//                                                                                                //
//  The content of this file may change from version to version without notice, or even be        //
//  removed.                                                                                      //
//                                                                                                //
//  You are forewarned!                                                                           //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "api/internal/style/style.hpp"
#include "api/internal/style/stylestatecontroller.hpp"

#include <QtCore/QList>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtQml/qqml.h>

#include <QtCore/private/qobject_p.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class AbstractStyleDispatcher;
class StyleState;

class StylePrivate final : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(Style)
    using StyleStateListProperty = QQmlListProperty<StyleState>;

public:
    StylePrivate() = default;
    ~StylePrivate() override = default;

    static StylePrivate *get(Style *style);
    static const StylePrivate *get(const Style *style);

    void init();

    AbstractStyleDispatcher *styleDispatcher() const;
    void setStyleDispatcher(AbstractStyleDispatcher *dispatcher);

    QWeakPointer<StyleStateController> stateController() const;

    // members
    QList<StyleState *> states{};
    QString name{};

private:
    static void style_state_append(StyleStateListProperty *property, StyleState *value);
    static StyleState *style_state_at(StyleStateListProperty *property, int index);
    static void style_state_clear(StyleStateListProperty *property);
    static int style_state_count(StyleStateListProperty *property);

private:
    QPointer<AbstractStyleDispatcher> m_dispatcher{};
    QSharedPointer<StyleStateController> m_stateController{};
};

//--------------------------------------------------------------------------------------------------

/*! \internal */
inline StylePrivate *StylePrivate::get(Style *style)
{
    return style->d_func();
}

/*! \internal */
inline const StylePrivate *StylePrivate::get(const Style *style)
{
    return style->d_func();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_STYLE_STYLE_P_HPP
