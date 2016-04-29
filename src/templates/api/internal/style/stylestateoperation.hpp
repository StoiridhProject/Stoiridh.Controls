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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATEOPERATION_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATEOPERATION_HPP

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
#include "api/internal/style/stylepropertyexpression.hpp"

#include <QtCore/QSharedPointer>
#include <QtCore/QVector>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class Control;

class SCT_INTERNAL_API StyleStateOperation final
{
    using SPEVector = QVector<QSharedPointer<StylePropertyExpression>>;
    using Mapping = QPair<const Control *, QQuickItem *>;

public:
    using iterator = SPEVector::iterator;
    using const_iterator = SPEVector::const_iterator;
    using size_type = SPEVector::size_type;

public:
    explicit StyleStateOperation(const QString &name = {}) noexcept;
    StyleStateOperation(const StyleStateOperation &rhs);
    StyleStateOperation(StyleStateOperation &&rhs) noexcept;

    bool isDefault() const noexcept;
    size_type count() const noexcept;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    QString name() const;
    void setName(const QString &name);

    void addExpression(QSharedPointer<StylePropertyExpression> &&expression) noexcept;
    void insertExpressionMapping(int index, const Mapping &mapping);
    QWeakPointer<StylePropertyExpression> expressionAt(int index) const;

    void apply(const Control *control);

    StyleStateOperation &operator=(const StyleStateOperation &rhs);
    StyleStateOperation &operator=(StyleStateOperation &&rhs) noexcept;

    bool operator==(const StyleStateOperation &rhs) noexcept;
    bool operator!=(const StyleStateOperation &rhs) noexcept;

private:
    QString m_name{};
    QVector<QSharedPointer<StylePropertyExpression>> m_expressions{};
};

//--------------------------------------------------------------------------------------------------

inline bool StyleStateOperation::isDefault() const noexcept
{
    return m_name.isEmpty();
}

inline StyleStateOperation::size_type StyleStateOperation::count() const noexcept
{
    return m_expressions.count();
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATEOPERATION_HPP
