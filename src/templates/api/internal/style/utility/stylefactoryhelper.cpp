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
#include "stylefactoryhelper.hpp"

#include "control.hpp"
#include "core/exception/exceptionhandler.hpp"

#include "api/internal/style/abstractstyledispatcher.hpp"
#include "api/internal/style/style.hpp"
#include "api/internal/style/stylepropertychanges.hpp"
#include "api/internal/style/stylestate.hpp"

#include "api/private/control_p.hpp"
#include "api/private/style/style_p.hpp"
#include "api/private/style/stylepropertychanges_p.hpp"
#include "api/private/style/stylestate_p.hpp"

#include <QtQml/QQmlInfo>

#include <QtQml/private/qqmlmetatype_p.h>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StyleFactoryHelper
    \since StoiridhControlsTemplates 1.0
    \ingroup style

    \brief The StyleFactoryHelper class is a helper class for the StyleFactory.

    \section introduction Introduction

    The StyleFactoryHelper class manages all stages for the \e creation and the \e reusability of a
    style for a given Control.

    The creation of the style state operations are achieved by the bias of the
    createStyleStatesOperations() method. This method will create different style state operations
    for the style \e owner.

    When a control has already its signature registered within the StyleFactory via its controlId(),
    we enter in the \b reusability stage where a mapping() is performed from the style
    \e target to the style \e owner.

    If an error occurred during the mapping(), the style \e target will not be deleted.

    \subsection style_owner_and_target Style Owner and Style Target

    During the \b creation stage, the style \e owner is associated with the control's style, whereas
    the style \e target is not used.

    During the \b reusability stage, the style \e owner is associated with the style dispatcher,
    whereas the style \e target is associated with the control's style.

    \sa StyleFactory
*/


/*!
    Constructs a style factory helper with the given \a control.

    \throw NullPointerException if either \a control or the \a control's style is null.
*/
StyleFactoryHelper::StyleFactoryHelper(const Control *control)
    : m_control{control}
{
    ExceptionHandler::checkNullPointer(control,
                                       QStringLiteral("control"),
                                       QStringLiteral("const Control *"));

    // assign the style owner to the control's style
    auto *const d_control = ControlPrivate::get(control);
    m_styleOwner = d_control->style();

    ExceptionHandler::checkNullPointer(m_styleOwner,
                                       QStringLiteral("control's style"),
                                       QStringLiteral("Style *"));
}

/*!
    Destroys this style factory helper.
*/
StyleFactoryHelper::~StyleFactoryHelper()
{
    // when a style target is assigned and successfully mapped to the style owner, then we can
    // safely delete the style target because the control's style will be bound to the style owner.
    if (m_styleTarget && !m_hasErrors)
    {
        m_styleTarget->deleteLater();
    }
}

/*!
    Returns either the control's style during the \b creation stage or the style dispatcher during
    the \b reusability stage.
*/
Style *StyleFactoryHelper::style() const
{
    return m_styleOwner;
}

/*!
    Sets the style's \a dispatcher to perform the mapping between the control and the style held by
    the style's dispatcher.

    \throw NullPointerException if \a dispatcher is null.

    \sa mapping()
*/
void StyleFactoryHelper::setStyleDispatcher(const AbstractStyleDispatcher *dispatcher)
{
    ExceptionHandler::checkNullPointer(dispatcher,
                                       QStringLiteral("dispatcher"),
                                       QStringLiteral("const AbstractStyleDispatcher *"));

    // style owner (control's style) becomes the style target
    m_styleTarget = m_styleOwner;
    m_styleOwner = dispatcher->style();
}

/*!
    Returns the control identifier. Generally, it is the result of the concatenation of the QML
    module's name and the control's name.
*/
const QString &StyleFactoryHelper::controlId() const
{
    return QQmlMetaType::qmlType(m_control->metaObject())->qmlTypeName();
}

/*!
    Creates the different style state operations for the \e owner style state controller.

    \throw NullPointerException if the style \e owner (control's style) is null.
*/
void StyleFactoryHelper::createStyleStatesOperations()
{
    ExceptionHandler::checkNullPointer(m_styleOwner, QStringLiteral("style owner"));

    auto *d_style_owner = StylePrivate::get(m_styleOwner);

    if (auto controller = d_style_owner->stateController().lock())
    {
        auto defaultOperation = createDefaultStyleStateOperation();
        controller->addStateOperation(std::move(defaultOperation));

        for (auto *state : d_style_owner->states)
        {
            if (state->name().isEmpty())
            {
                QtQml::qmlInfo(state) << QObject::tr("the name property can't be empty");
            }
            else
            {
                auto operation = createStyleStateOperation(state);
                controller->addStateOperation(std::move(operation));
            }
        }
    }
}

/*!
    Creates a new style state operation from the given \a state.

    \throw NullPointerException if \a state is null.
*/
QSharedPointer<StyleStateOperation>
StyleFactoryHelper::createStyleStateOperation(const StyleState *state)
{
    ExceptionHandler::checkNullPointer(state,
                                       QStringLiteral("state"),
                                       QStringLiteral("const StyleState *"));

    auto *const d_state = StyleStatePrivate::get(state);
    auto operation = QSharedPointer<StyleStateOperation>::create(state->name());

    for (auto *changes : d_state->changes)
    {
        auto expression = createStylePropertyExpression(changes);
        operation->addExpression(std::move(expression));
    }

    return operation;
}

/*!
    Merges the style \a state within the style state \a operation.

    \return true when the style \a state is successfully merged in the style state \a operation,
            otherwise, false.

    \throw NullPointerException if either \a operation or \a state is null.
*/
bool
StyleFactoryHelper::mergeStyleStateOperation(const QSharedPointer<StyleStateOperation> &operation,
                                             const StyleState *state)
{
    ExceptionHandler::checkNullPointer(operation,
                                       QStringLiteral("operation"),
                                       QStringLiteral("const "
                                                      "QSharedPointer<StyleStateOperation> &"));
    ExceptionHandler::checkNullPointer(state,
                                       QStringLiteral("state"),
                                       QStringLiteral("const StyleState *"));

    const auto *const d_state = StyleStatePrivate::get(state);
    const auto operationName = operation->name();
    const auto styleStateName = state->name();

    if (operationName != styleStateName)
    {
        pushMappingError(QObject::tr("the style state operation '%1' is not the same as the "
                                     "given style's state '%2'.")
                         .arg(operationName)
                         .arg(styleStateName));
        return false;
    }

    if (operation->count() != d_state->changes.count())
    {
        pushMappingError(QObject::tr("the style state operation '%1' from the owner style are "
                                     "not equal to the style property changes of the style's "
                                     "state '%2' of the target style.")
                         .arg(operationName)
                         .arg(styleStateName));
        return false;
    }

    // we need only to map the (control, target)-pair because the properties are symmetric between
    // the style state operation and the style's state.
    for (auto i = 0; i < operation->count(); ++i)
    {
        auto *const changes = d_state->changes.at(i);
        operation->insertExpressionMapping(i, qMakePair(m_control, changes->target()));
    }

    return true;
}

/*!
    Creates a new style property expression from the given \a changes.

    \throw NullPointerException if \a changes is null.
*/
QSharedPointer<StylePropertyExpression>
StyleFactoryHelper::createStylePropertyExpression(StylePropertyChanges *changes,
                                                  bool useDefaultProperties)
{
    ExceptionHandler::checkNullPointer(changes,
                                       QStringLiteral("changes"),
                                       QStringLiteral("StylePropertyChanges *"));

    auto *const d_changes = StylePropertyChangesPrivate::get(changes);
    auto expression = QSharedPointer<StylePropertyExpression>::create();

    if (!d_changes->decoded)
    {
        d_changes->decode();
    }

    expression->addMapping(m_control, changes->target());
    expression->addProperties(useDefaultProperties ? d_changes->defaultProperties
                                                   : d_changes->properties);

    return expression;
}

/*!
    Maps the style's states from \e target to the style state operations of \e owner.

    \return true when the mapping is successfully applied to the style \e owner, otherwise, false.

    \throw NullPointerException if either style \e owner (style dispatcher) or style \e target
                                (control's style) is null.

    \sa setStyleDispatcher()
*/
bool StyleFactoryHelper::mapping()
{
    ExceptionHandler::checkNullPointer(m_styleOwner, QStringLiteral("style owner"));
    ExceptionHandler::checkNullPointer(m_styleTarget, QStringLiteral("style target"));

    // clear the previous recorded errors
    if (m_hasErrors)
    {
        clearMappingErrors();
    }

    if (m_styleOwner == m_styleTarget)
    {
        pushMappingError(QObject::tr("style owner and style target are same."));
        return false;
    }

    auto *const d_style_owner = StylePrivate::get(m_styleOwner);
    auto *const d_style_target = StylePrivate::get(m_styleTarget);

    if (d_style_owner->states.count() != d_style_target->states.count())
    {
        pushMappingError(QObject::tr("the style's states number from the style owner are not "
                                     "equal to the style's states number of the style target."));
        return false;
    }

    if (auto controller = d_style_owner->stateController().lock())
    {
        for (const auto *state : d_style_target->states)
        {
            if (auto operation = controller->findStateOperation(state->name()).lock())
            {
                if (!mergeStyleStateOperation(operation, state))
                {
                    pushMappingError(QObject::tr("impossible to merge the style's state from the "
                                                 "style target to the style state operation from "
                                                 "the style owner."));
                    return false;
                }
            }

            if (auto defaultOperation = controller->defaultStateOperation().lock())
            {
                mergeDefaultStyleStateOperation(defaultOperation, state);
            }
        }
    }

    return true;
}

/*!
    Returns true if errors has occurred during the mapping, otherwise, false.
*/
bool StyleFactoryHelper::hasErrors() const noexcept
{
    return m_hasErrors;
}

/*!
    Returns the errors generated during the mapping of the styles.
 */
QString StyleFactoryHelper::mappingErrors() const noexcept
{
    auto errors = QString::fromUtf8("Control: %1\n").arg(controlId());
    int count{1};
    auto totalErrors = m_errors.size();

    while (!m_errors.empty())
    {
        auto message = QString::fromUtf8("%1 on %2: %3\n").arg(count)
                                                          .arg(totalErrors)
                                                          .arg(m_errors.front());
        errors.append(message);
        m_errors.pop();
        ++count;
    }

    return errors;
}

/*!
    Creates the default style state operation for the control.

    \pre the control's style must not be null.
*/
QSharedPointer<StyleStateOperation> StyleFactoryHelper::createDefaultStyleStateOperation()
{
    Q_ASSERT_X(m_styleOwner, "createDefaultStyleStateOperation", "style owner is null");

    auto *d_style_owner = StylePrivate::get(m_styleOwner);
    auto defaultOperation = QSharedPointer<StyleStateOperation>::create();

    // check if a default style state operation contains a (control, target)-pair. If it exists,
    // then it returns an iterator of this expression.
    auto findExpressionByTarget = [&defaultOperation](const Control *control,
                                                      const QQuickItem *target)
    {
        auto predicate = [&control, &target](const auto &expressionIterator) -> bool
        {
            return (*expressionIterator).containsTarget(control, target);
        };

        return std::find_if(std::begin(*defaultOperation), std::end(*defaultOperation), predicate);
    };

    for (auto *state : d_style_owner->states)
    {
        if (state->name().isEmpty())
        {
            QtQml::qmlInfo(state) << QObject::tr("the name property can't be empty");
        }
        else
        {
            auto *const d_state = StyleStatePrivate::get(state);

            for (auto *changes : d_state->changes)
            {
                auto expressionIterator = findExpressionByTarget(m_control, changes->target());

                if (expressionIterator != defaultOperation->end())
                {
                    // add the default properties contained in the style property changes of the
                    // current style's state to the expression found.
                    auto d_changes = StylePropertyChangesPrivate::get(changes);
                    (*expressionIterator)->addProperties(d_changes->defaultProperties);
                }
                else
                {
                    // create a new style property expression and append the default properties to
                    // it.
                    auto expression = createStylePropertyExpression(changes, true);
                    defaultOperation->addExpression(std::move(expression));
                }
            }
        }
    }

    return defaultOperation;
}

/*!
    Merges the \a state to the default style state \a operation.

    \pre \a operation must not be null.
    \pre \a state must not be null.
*/
void
StyleFactoryHelper::mergeDefaultStyleStateOperation(const QSharedPointer<StyleStateOperation> &operation,
                                                    const StyleState *state)
{
    Q_ASSERT_X(operation, "mergeDefaultStyleStateOperation", "operation is null");
    Q_ASSERT_X(state, "mergeDefaultStyleStateOperation", "state is null");

    auto *const d_state = StyleStatePrivate::get(state);

    for (auto i = 0; i < d_state->changes.count(); ++i)
    {
        const auto *const changes = d_state->changes.at(i);
        operation->insertExpressionMapping(i, qMakePair(m_control, changes->target()));
    }
}

/*!
    Pushes a new error to the errors' queue.

    \sa mapping(), hasErrors(), clearMappingErrors()
*/
void StyleFactoryHelper::pushMappingError(QString &&error) noexcept
{
    m_errors.push(std::move(error));

    if (!m_hasErrors)
    {
        m_hasErrors = true;
    }
}

/*!
    Clears the mapping errors previously recorded during the last mapping.
    \sa mapping()
*/
void StyleFactoryHelper::clearMappingErrors() noexcept
{
    std::queue<QString> errors{};
    m_errors.swap(errors);
    m_hasErrors = false;
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
