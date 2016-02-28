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

#include "api/private/control_p.hpp"

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------


/*! \class StoiridhControlsTemplates::Control
    \inherits QQuickItem
    \inmodule StoiridhControlsTemplates
    \ingroup controls
    \ingroup templates
    \since StoiridhControlsTemplates 1.0

    \brief The Control class provides a base class for UI controls.
*/


/*!
    Constructs a Control with an optional \a parent as parent.
*/
Control::Control(QQuickItem *parent)
    : Control{*(new ControlPrivate{}), parent}
{

}

/*!
    \internal
*/
Control::Control(ControlPrivate &dd, QQuickItem *parent)
    : QQuickItem{dd, parent}
{
    Q_D(Control);
    d->init(this);
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

    \sa {Control::}{padding()}
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

    \sa {Control::}{paddings()}
*/
Padding *Control::padding() const
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

/*!
    \reimp
*/
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

ControlPrivate::ControlPrivate()
{

}

ControlPrivate::~ControlPrivate()
{

}

void ControlPrivate::init(QQuickItem *parent)
{
    padding = new Padding{parent};
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
