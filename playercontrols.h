#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>
#include <QScrollBar>

class Player;

class PlayerControls : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
    PlayerControls();
    explicit PlayerControls(QScrollBar* s, QObject *parent = 0);
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

signals:
    void jumpFactorChanged(qreal);

private:
    void initPlayField();

    int m_velocity;
    int m_skippedMoving;
    qreal m_groundLevel;
    qreal m_minX;
    qreal m_maxX;
    QTimer m_timer;
    QTimer mFallTimer;
    qreal m_jumpFactor;
    int m_jumpHeight;
    int m_fieldWidth;
    qreal m_realPos; //The actual position of character

    Player* m_player;

    QGraphicsItem *m_platform;
    QScrollBar *scroll;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void checkTimer();
    void checkCollidingCoin();
    bool handleCollisionWithPlatform();

    QGraphicsItem* collidingPlatforms();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

#endif // PLAYERCONTROLS_H
