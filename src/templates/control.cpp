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
#include "control.hpp"

#include "api/internal/style/style.hpp"
#include "api/internal/style/styledispatcher.hpp"
#include "api/internal/style/stylefactory.hpp"

#include "api/private/control_p.hpp"
#include "api/private/style/style_p.hpp"

#include <QtQuick/QQuickItem>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class Control control.hpp <StoiridhControlsTemplates/Control>
    \ingroup templates
    \since StoiridhControlsTemplates 1.0

    \brief The Control class provides a base class for all UI controls.
*/


/*!
    Constructs a control with the given \a parent.
*/
Control::Control(QQuickItem *parent)
    : Control{*(new ControlPrivate{}), parent}
{

}

/*! \internal */
Control::Control(ControlPrivate &dd, QQuickItem *parent)
    : QQuickItem{dd, parent}
{
    dd.init(this);
}

/*!
    Destroys this control.
*/
Control::~Control()
{

}

/*! \property StoiridhControlsTemplates::Control::availableWidth
    \readonly

    This property holds the available width for the content item.
*/
qreal Control::availableWidth() const
{
    Q_D(const Control);
    return qMax(0.0, width() - d->padding->left() - d->padding->right());
}

/*! \property StoiridhControlsTemplates::Control::availableHeight
    \readonly

    This property holds the available height for the content item.
*/
qreal Control::availableHeight() const
{
    Q_D(const Control);
    return qMax(0.0, height() - d->padding->top() - d->padding->bottom());
}

/*! \property StoiridhControlsTemplates::Control::paddings

    This property holds the global paddings of the control.

    \sa padding()
*/
qreal Control::paddings() const
{
    Q_D(const Control);
    return d->paddings;
}

void Control::setPaddings(qreal paddings)
{
    Q_D(Control);

    if (!qFuzzyCompare(d->paddings, paddings))
    {
        d->paddings = paddings;

        // adjust the padding of the grouped property
        d->padding->setPaddings(paddings);

        if (isComponentComplete())
            d->calculateContentGeometry();

        emit paddingsChanged();
    }
}

void Control::resetPaddings()
{
    setPaddings(0.0);
}

/*! \property StoiridhControlsTemplates::Control::padding
    \readonly

    This property holds the padding of the control.

    \sa paddings()
*/
StoiridhControlsTemplates::Padding *Control::padding() const
{
    Q_D(const Control);
    return d->padding;
}

/*! \property StoiridhControlsTemplates::Control::background

    This property holds the background of the control.
*/
QQuickItem *Control::background() const
{
    Q_D(const Control);
    return d->background;
}

void Control::setBackground(QQuickItem *background)
{
    Q_D(Control);

    if (d->background != background)
    {
        d->background = background;

        if (d->background)
        {
            d->background->setParentItem(this);
            d->background->setZ(-1.0);

            if (isComponentComplete())
                d->calculateBackgroundGeometry();
        }

        emit backgroundChanged();
    }
}

/*! \property StoiridhControlsTemplates::Control::content

    This property holds the content of the control.
*/
QQuickItem *Control::content() const
{
    Q_D(const Control);
    return d->content;
}

void Control::setContent(QQuickItem *content)
{
    Q_D(Control);

    if (d->content != content)
    {
        d->content = content;

        if (d->content)
        {
            d->content->setParentItem(this);

            if (isComponentComplete())
                d->calculateContentGeometry();
        }

        emit contentChanged();
    }
}

/*! \reimp */
void Control::componentComplete()
{
    Q_D(Control);

    QQuickItem::componentComplete();

    // calculate both background and content geometries in order to avoid a null geometry when the
    // component has completed construction.
    d->calculateBackgroundGeometry();
    d->calculateContentGeometry();

    if (d->style())
    {
        // the StyleFactory can only operate on the style created from the QML engine when the
        // control has completed construction.
        auto *const style = StyleFactory::create<StyleDispatcher>(this);
        d->setStyle(style);
        d->initialiseDefaultStyleState();
    }
}

/*! \reimp */
void Control::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);

    Q_D(Control);
    d->calculateBackgroundGeometry();
    d->calculateContentGeometry();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   PRIVATE API    /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class StoiridhControlsTemplates::ControlPrivate
    \internal
*/

void ControlPrivate::init(QQuickItem *parent)
{
    padding = new Padding{parent};
}

void ControlPrivate::accept(AbstractStyleDispatcher *dispatcher)
{
    Q_Q(Control);
    dispatcher->dispatch(q);
}

/*! \property StoiridhControlsTemplates::Control::style

    This property holds the style of the control.
*/
StoiridhControlsTemplates::Style *ControlPrivate::style() const
{
    return m_style;
}

void ControlPrivate::setStyle(StoiridhControlsTemplates::Style *style)
{
    if (m_style != style)
    {
        Q_Q(Control);
        m_style = style;

        if (q->isComponentComplete())
        {
            updateStyle();
        }

        emit q->styleChanged();
    }
}

void ControlPrivate::updateStyle()
{
    if (auto *const s = style())
    {
        auto *const d_style = StylePrivate::get(s);
        accept(d_style->styleDispatcher());
    }
}

QString ControlPrivate::styleState() const
{
    return m_styleState;
}

void ControlPrivate::initialiseDefaultStyleState()
{
    // a control is an abstract concept so it has not a default style's state.
}

void ControlPrivate::calculateBackgroundGeometry()
{
    Q_Q(Control);

    if (!background)
        return;

    background->setX(0.0);
    background->setY(0.0);

    if (q->widthValid())
    {
        background->setWidth(q->width());
    }
    else
    {
        const auto width = qMax(background->implicitWidth(), q->implicitWidth());
        background->setWidth(width);
        q->setImplicitWidth(width);
    }

    if (q->heightValid())
    {
        background->setHeight(q->height());
    }
    else
    {
        const auto height = qMax(background->implicitHeight(), q->implicitHeight());
        background->setHeight(height);
        q->setImplicitHeight(height);
    }
}

void ControlPrivate::calculateContentGeometry()
{
    Q_Q(Control);

    if (!content)
        return;

    content->setX(padding->left());
    content->setY(padding->top());

    const auto ciw = content->implicitWidth();

    if (q->widthValid() || qFuzzyIsNull(ciw))
    {
        content->setWidth((ciw > 0.0 && ciw < q->availableWidth()) ? ciw : q->availableWidth());
    }
    else
    {
        // adjust the width of the control so as to keep the implicit width of the content item.
        if (ciw >= q->availableWidth())
        {
            const auto width = ciw + padding->left() + padding->right();
            q->setWidth(width);
        }
    }

    // identical to width but for height.
    const auto cih = content->implicitHeight();

    if (q->heightValid() || qFuzzyIsNull(cih))
    {
        content->setHeight((cih > 0.0 && cih < q->availableHeight()) ? cih : q->availableHeight());
    }
    else
    {
        // adjust the height of the control so as to keep the implicit height of the content item.
        if (cih >= q->availableHeight())
        {
            const auto height = cih + padding->top() + padding->bottom();
            q->setHeight(height);
        }
    }
}

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
#include <moc_control.cpp>
