#include "playercontrols.h"
#include "player.h"

#include <QKeyEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

PlayerControls::PlayerControls(QScrollBar*s , QObject *parent) :
    QGraphicsScene(0,0,8000,720, parent)
  , m_velocity(7)
  , m_skippedMoving(0)
  , m_groundLevel(0)
  , m_minX(0)
  , m_maxX(0)
  , m_jumpHeight(200)
  , m_fieldWidth(8000) //width of the virtual world
  , m_player()
  , m_platform()
  , scroll(s)

{
    initPlayField();

    //Timer to check if player is moving
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &PlayerControls::movePlayer);

    //Timer to control player fall speed
    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &PlayerControls::fallPlayer);
    connect(this, &PlayerControls::jumpFactorChanged, this, &PlayerControls::jumpPlayer);
}

//Player movement
void PlayerControls::keyPressEvent(QKeyEvent *event)
{

    if (event->isAutoRepeat())
            return;

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(-1);
        checkTimer();
        break;
    case Qt::Key_Space:
        qDebug() << "space pressed";

        break;
    default:
        break;
    }
}

void PlayerControls::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(-1);
        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(1);
        checkTimer();
        break;

    default:
        break;
    }
}
