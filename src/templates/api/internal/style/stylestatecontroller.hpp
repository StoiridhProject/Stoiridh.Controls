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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATECONTROLLER_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATECONTROLLER_HPP

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
#include "api/internal/style/stylestateoperation.hpp"

#include <QtCore/QHash>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class Control;
class Style;

class SCT_INTERNAL_API StyleStateController final
{
    using SSOHash = QHash<QString, QSharedPointer<StyleStateOperation>>;

public:
    using size_type = SSOHash::size_type;

public:
    explicit StyleStateController(Style *style);
    StyleStateController(const StyleStateController &rhs) = delete;
    StyleStateController(StyleStateController &&rhs) = delete;
    ~StyleStateController() = default;

    bool isEmpty() const noexcept;
    size_type count() const noexcept;

    Style *style() const;

    void addStateOperation(QSharedPointer<StyleStateOperation> &&operation) noexcept;
    QWeakPointer<StyleStateOperation> findStateOperation(const QString &name) const noexcept;
    QWeakPointer<StyleStateOperation> defaultStateOperation() const noexcept;

    void apply(const Control *control);

    StyleStateController &operator=(const StyleStateController &rhs) = delete;
    StyleStateController &operator=(StyleStateController &&rhs) = delete;

private:
    QPointer<Style> m_style{};
    QHash<QString, QSharedPointer<StyleStateOperation>> m_operations{};
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_STYLESTATECONTROLLER_HPP
