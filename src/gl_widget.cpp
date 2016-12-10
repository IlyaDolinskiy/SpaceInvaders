#include "gl_widget.hpp"

#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QGuiApplication>
#include <cmath>

#include <iostream>

#include "main_window.hpp"

namespace
{

int constexpr kLeftDirection = 0;
int constexpr kRightDirection = 1;

} // namespace

GLWidget::GLWidget(MainWindow * mw, QColor const & background)
  : m_mainWindow(mw)
  , m_background(background)
{
  setMinimumSize(m_width, m_height);
  setMaximumSize(m_width, m_height);
  setFocusPolicy(Qt::StrongFocus);
}

GLWidget::~GLWidget()
{
  makeCurrent();
  delete m_textureAlien;
  delete m_textureGun;
  delete m_textureObstacle;
  delete m_textureBullet;
  delete m_texturedRect;
  doneCurrent();
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);

  m_textureAlien = new QOpenGLTexture(QImage("data/alien.png"));
  m_textureGun = new QOpenGLTexture(QImage("data/gun.png"));
  m_textureObstacle = new QOpenGLTexture(QImage("data/obstacle.png"));
  m_textureBullet = new QOpenGLTexture(QImage("data/bullet.png"));

  m_time.start();
  m_timeShot.start();
  m_timeMove.start();
}

void GLWidget::paintGL()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.beginNativePainting();

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);

  painter.endNativePainting();

  if (elapsed != 0)
  {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(20, 20, framesPerSecond + " fps");
    painter.drawText(20, 40,  "health: " + QString::number(m_gun->GetHealth()));
    painter.drawText(20, 50,  "ammo: " + QString::number(m_gun->GetAmmo()));
    for (const auto & alien : m_alien)
    {
      painter.drawText(alien->GetPosition().x() - alien->GetSize().width() / 4,
                       m_height - (alien->GetPosition().y() + alien->GetSize().height() / 2),
                       "health: " + QString::number(alien->GetHealth()));
    }
    for (const auto & obstacle : m_obstacle)
    {
      painter.drawText(obstacle->GetPosition().x() - obstacle->GetSize().width() / 4,
                       m_height - (obstacle->GetPosition().y() + obstacle->GetSize().height()/2),
                       "health: " + QString::number(obstacle->GetHealth()));
    }
    if (!m_gameIsActive)
    {
      switch(m_status)
      {
        case Status::Lose:
          painter.drawText(m_width / 2, m_height / 2, "Game Over!");
          painter.drawText(m_width / 2, m_height / 2 + 20, "You Lose!");
          break;
        case Status::Win:
          painter.drawText(m_width / 2, m_height / 2, "Game Over!");
          painter.drawText(m_width / 2, m_height / 2 + 20, "You Win!");
          break;
      }
    }
  }
  painter.end();

  if (!(m_frames % 100))
  {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;
  update();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GLWidget::Update(float elapsedSeconds)
{
  if (!(!m_gun->GetIsActive() || m_gun->GetAmmo() == 0 || m_alien.size() == 0))
  {
    if (m_shot)
    {
      m_bullet.push_back(std::move(m_gun->Shot(QVector2D(m_gun->GetPosition()),
                                               QVector2D(m_gun->GetShotDirection()),
                                               Shooter::Gun)));
      m_shot = false;
    }

    if (m_timeShot.elapsed() > 500)
    {
      int number = Random::Int(0,  m_alien.size()-1);
      m_bullet.push_back(std::move(m_alien.at(number)->Shot(QVector2D(m_alien.at(number)->GetPosition()),
                                                            QVector2D(m_alien.at(number)->GetShotDirection()),
                                                            Shooter::Alien)));
      m_timeShot.restart();
    }

    if (m_alien.at(0)->GetPosition().y() > m_height / 2)
    {
      for (const auto & alien : m_alien)
      {
        alien->Move(elapsedSeconds);
      }
      m_timeMove.restart();
    }


    for (const auto & bullet : m_bullet)
    {
      bullet->Update(elapsedSeconds);
      if (bullet->GetPosition().x() < 0 || bullet->GetPosition().y() < 0 || bullet->GetPosition().x() > m_width || bullet->GetPosition().y() > m_height)
        bullet->SetIsActive(false);

      if (bullet->GetIsActive())
      {
        if (bullet->Intersection(*(m_gun.get())) && (bullet->GetShooter() == Shooter::Alien))
        {
          bullet->SetIsActive(false);
          m_gun->Damage();
          Log << LOG_DAMAGE << LOG_GUN;
        }

        for (const auto & alien : m_alien)
        {
          if (bullet->Intersection(*(alien.get())) && (bullet->GetShooter() == Shooter::Gun))
          {
            bullet->SetIsActive(false);
            alien->Damage();
            Log << LOG_DAMAGE << LOG_ALIEN;
          }
        }

        for (const auto & obstacle : m_obstacle)
        {
          if (bullet->Intersection(*(obstacle.get())))
          {
            bullet->SetIsActive(false);
            obstacle->Damage();
            Log << LOG_DAMAGE << LOG_OBSTACLE;
          }
        }
      }
    }

    for (const auto & alien : m_alien)
    {
      if (!alien->GetIsActive())
      Log << LOG_DESTRUCTION << LOG_ALIEN;
    }

    for (const auto & obstacle : m_obstacle)
      if (!obstacle->GetIsActive())
        Log << LOG_DESTRUCTION << LOG_OBSTACLE;

    m_bullet.erase(std::remove_if(m_bullet.begin(), m_bullet.end(),
                                  [](std::shared_ptr<Bullet> element) -> bool { return !element->GetIsActive(); }
                   ), m_bullet.end()
        );

    m_alien.erase(std::remove_if(m_alien.begin(), m_alien.end(),
                                  [](std::shared_ptr<Alien> element) -> bool { return !element->GetIsActive(); }
                   ), m_alien.end()
        );

    m_obstacle.erase(std::remove_if(m_obstacle.begin(), m_obstacle.end(),
                                  [](std::shared_ptr<Obstacle> element) -> bool { return !element->GetIsActive(); }
                   ), m_obstacle.end()
        );

    if (m_directions[kLeftDirection] && (m_gun->GetPosition().x() - m_gun->GetSpeed() * elapsedSeconds > (m_gun->GetSize().width() / 2.0f + 1)))
      m_gun->SetPosition(QVector2D(m_gun->GetPosition().x() - m_gun->GetSpeed() * elapsedSeconds, m_gun->GetPosition().y()));
    if (m_directions[kRightDirection] && (m_gun->GetPosition().x() + m_gun->GetSpeed() * elapsedSeconds < (m_width - m_gun->GetSize().width() / 2.0f - 1)))
      m_gun->SetPosition(QVector2D(m_gun->GetPosition().x() + m_gun->GetSpeed() * elapsedSeconds, m_gun->GetPosition().y()));
  }

  else
  {
    m_gameIsActive = false;
    if (!m_gun->GetIsActive() || m_gun->GetAmmo() == 0)
    {
      Log << LOG_DESTRUCTION << LOG_GUN;
      Log << std::string("GameOver\n");
      m_status = Status::Lose;
    }
    else
    {
      Log << std::string("You Win\n");
      Log << std::string("GameOver\n");
      m_status = Status::Win;
    }
  }
}

void GLWidget::Render()
{
  for (const auto & it : m_obstacle)
    m_texturedRect->Render(m_textureObstacle, it->GetPosition(), it->GetSize(), m_screenSize);
  for (const auto & it : m_bullet)
    m_texturedRect->Render(m_textureBullet, it->GetPosition(), it->GetSize(), m_screenSize);
  for (const auto & it : m_alien)
    m_texturedRect->Render(m_textureAlien, it->GetPosition(), it->GetSize(), m_screenSize);
  m_texturedRect->Render(m_textureGun, m_gun->GetPosition(), m_gun->GetSize(), m_screenSize);

}

void GLWidget::keyPressEvent(QKeyEvent * e)
{  
  if (e->key() == Qt::Key_Space)
    m_shot = true;

  if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = true;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = true;
}

void GLWidget::keyReleaseEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Space)
    m_shot = false;

  if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = false;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = false;
}
