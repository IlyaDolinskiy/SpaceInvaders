#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"

#include "space.hpp"
#include "gun.hpp"

#include <array>

class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions, public Space
{
  Q_OBJECT
public:
  GLWidget(MainWindow * mw, QColor const & background);
  ~GLWidget();

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void Render();

  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  int L2D(int px) const { return px * devicePixelRatio(); }

  MainWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;

  QOpenGLTexture * m_textureAlien = nullptr;
  QOpenGLTexture * m_textureGun = nullptr;
  QOpenGLTexture * m_textureObstacle = nullptr;
  QOpenGLTexture * m_textureBullet = nullptr;
  TexturedRect * m_texturedRect = nullptr;

  QVector2D m_position = QVector2D(200, 200);
  std::array<bool, 2> m_directions = { {false, false} };
  bool m_fire = false;
};
