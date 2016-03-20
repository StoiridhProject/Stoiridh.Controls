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
#ifndef STOIRIDHCONTROLSTEMPLATES_CONTROL_HPP
#define STOIRIDHCONTROLSTEMPLATES_CONTROL_HPP

#include <StoiridhControlsTemplates/Public/global.hpp>
#include <StoiridhControlsTemplates/Padding>

#include <QQuickItem>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class ControlPrivate;

class STOIRIDH_CONTROLS_TEMPLATES_API Control : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal availableWidth READ availableWidth FINAL)
    Q_PROPERTY(qreal availableHeight READ availableHeight FINAL)
    Q_PROPERTY(qreal paddings READ paddings WRITE setPaddings NOTIFY paddingsChanged RESET resetPaddings FINAL)
    Q_PROPERTY(Padding *padding READ padding CONSTANT FINAL)
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QQuickItem *content READ content WRITE setContent NOTIFY contentChanged FINAL)

public:
    explicit Control(QQuickItem *parent = nullptr);
    ~Control() override;

    qreal availableWidth() const;
    qreal availableHeight() const;

    qreal paddings() const;
    void setPaddings(qreal paddings);
    void resetPaddings();

    Padding *padding() const;

    QQuickItem *background() const;
    void setBackground(QQuickItem *background);

    QQuickItem *content() const;
    void setContent(QQuickItem *content);

signals:
    void paddingsChanged();
    void backgroundChanged();
    void contentChanged();

protected:
    Control(ControlPrivate &dd, QQuickItem *parent);

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    Q_DISABLE_COPY(Control)
    Q_DECLARE_PRIVATE(Control)
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
QML_DECLARE_TYPE(StoiridhControlsTemplates::Control)
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDHCONTROLSTEMPLATES_CONTROL_HPP
