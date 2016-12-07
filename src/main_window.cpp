#include "main_window.hpp"

#include <QApplication>
#include "gl_widget.hpp"
#include <iostream>

typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{
  setMaximumSize(1024, 768);
  setMinimumSize(1024, 768);
  m_glWidget = new GLWidget(this, qRgb(20, 20, 50));
//  setMaximumSize(GLWidget.GetWidth(), GLWidget.GetHeight());
//  setMinimumSize(GLWidget.GetWidth(), GLWidget.GetHeight());
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();

  setFocusPolicy(Qt::StrongFocus);
}
