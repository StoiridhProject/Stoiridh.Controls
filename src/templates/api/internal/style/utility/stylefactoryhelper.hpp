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
#ifndef STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_UTILITY_STYLEFACTORYHELPER_HPP
#define STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_UTILITY_STYLEFACTORYHELPER_HPP

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
#include "api/internal/style/stylestateoperation.hpp"

#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>

#include <queue>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class AbstractStyleDispatcher;
class Control;
class Style;
class StylePropertyChanges;
class StyleState;

class SCT_INTERNAL_API StyleFactoryHelper final
{
public:
    explicit StyleFactoryHelper(const Control *control);
    StyleFactoryHelper(const StyleFactoryHelper &rhs) = delete;
    StyleFactoryHelper(StyleFactoryHelper &&rhs) = delete;
    ~StyleFactoryHelper();

    Style *style() const;
    void setStyleDispatcher(const AbstractStyleDispatcher *dispatcher);

    const QString &controlId() const;

    void createStyleStatesOperations();

    QSharedPointer<StyleStateOperation>
    createStyleStateOperation(const StyleState *state);

    bool mergeStyleStateOperation(const QSharedPointer<StyleStateOperation> &operation,
                                  const StyleState *state);

    QSharedPointer<StylePropertyExpression>
    createStylePropertyExpression(StylePropertyChanges *changes, bool useDefaultProperties = false);

    bool mapping();

    bool hasErrors() const noexcept;
    QString mappingErrors() const noexcept;

    StyleFactoryHelper &operator=(const StyleFactoryHelper &rhs) = delete;
    StyleFactoryHelper &operator=(StyleFactoryHelper &&rhs) = delete;

private:
    QSharedPointer<StyleStateOperation> createDefaultStyleStateOperation();
    void mergeDefaultStyleStateOperation(const QSharedPointer<StyleStateOperation> &operation,
                                         const StyleState *state);

    void pushMappingError(QString &&error) noexcept;
    void clearMappingErrors() noexcept;

private:
    QPointer<const Control> m_control{};
    QPointer<Style> m_styleOwner{};
    QPointer<Style> m_styleTarget{};
    mutable std::queue<QString> m_errors{};
    bool m_hasErrors{false};
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_INTERNAL_STYLE_UTILITY_STYLEFACTORYHELPER_HPP
