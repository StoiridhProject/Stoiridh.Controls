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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYEXPRESSION_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYEXPRESSION_HPP

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

#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVector>

QT_BEGIN_NAMESPACE
class QQuickItem;
QT_END_NAMESPACE

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class Control;

class SCT_INTERNAL_API StylePropertyExpression final
{
public:
    explicit StylePropertyExpression() = default;
    StylePropertyExpression(const StylePropertyExpression &rhs);
    StylePropertyExpression(StylePropertyExpression &&rhs) noexcept;
    ~StylePropertyExpression() = default;

    QPair<int, int> count() const noexcept;

    bool containsControl(const Control *control) const noexcept;
    bool containsTarget(const Control *control, const QQuickItem *target) const noexcept;
    void addMapping(const Control *control, QQuickItem *target);
    bool removeMapping(const Control *control) noexcept;

    bool containsProperty(const QString &name) const noexcept;
    void addProperty(const QString &name, const QVariant &value);
    void addProperty(const QPair<QString, QVariant> &property);
    void addProperties(const QVector<QPair<QString, QVariant>> &properties) noexcept;
    bool removeProperty(const QString &name) noexcept;

    bool apply(const Control *control);

    StylePropertyExpression &operator=(const StylePropertyExpression &rhs);
    StylePropertyExpression &operator=(StylePropertyExpression &&rhs) noexcept;

    bool operator==(const StylePropertyExpression &rhs) const;
    bool operator!=(const StylePropertyExpression &rhs) const;

private:
    QMap<const Control *, QQuickItem *> m_mappings{};
    QHash<QString, QVariant> m_properties{};
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLEPROPERTYEXPRESSION_HPP
