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
#ifndef STOIRIDH_CONTROLS_TEMPLATES_CONTROL_HPP
#define STOIRIDH_CONTROLS_TEMPLATES_CONTROL_HPP

#include <StoiridhControlsTemplates/global.hpp>
#include <StoiridhControlsTemplates/padding.hpp>

#include <QtCore/QPointer>
#include <QtQuick/QQuickItem>

//--------------------------------------------------------------------------------------------------
namespace StoiridhControlsTemplates {
//--------------------------------------------------------------------------------------------------

class STOIRIDH_CONTROLS_TEMPLATES_API Control : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal availableWidth READ availableWidth FINAL)
    Q_PROPERTY(qreal availableHeight READ availableHeight FINAL)
    Q_PROPERTY(qreal paddings READ paddings WRITE setPaddings NOTIFY paddingsChanged RESET resetPaddings FINAL)
    Q_PROPERTY(Padding *padding READ padding CONSTANT FINAL)
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged DESIGNABLE false FINAL)
    Q_PROPERTY(QQuickItem *content READ content WRITE setContent NOTIFY contentChanged DESIGNABLE false FINAL)

public:
    explicit Control(QQuickItem *parent = nullptr);

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
    void paddingsChanged(qreal paddings);
    void backgroundChanged(QQuickItem *background);
    void contentChanged(QQuickItem *content);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

private:
    void calculateBackgroundGeometry();
    void calculateContentGeometry();

private:
    Q_DISABLE_COPY(Control)

    qreal m_paddings{};
    QPointer<Padding> m_padding;
    QPointer<QQuickItem> m_background;
    QPointer<QQuickItem> m_content;
};

//--------------------------------------------------------------------------------------------------
} // namespace StoiridhControlsTemplates
//--------------------------------------------------------------------------------------------------
QML_DECLARE_TYPE(StoiridhControlsTemplates::Control)
//--------------------------------------------------------------------------------------------------

#endif // STOIRIDH_CONTROLS_TEMPLATES_CONTROL_HPP
