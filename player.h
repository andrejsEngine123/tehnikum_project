#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>

class Player : public QGraphicsItem
{
public:
    Player(QGraphicsItem *parent = 0);
    ~Player();
   int direction() const;
   void nextFrame();
   void addDirection(int direction);
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool isTouchingPlatform(QGraphicsItem *item);

    void stand();
    void jump();
    void walk();
    void fall();

    bool isFalling();

private:
    enum State {
         Standing = 0,
         Walking,
         Jumping,
         Falling
    };

    int m_direction;
    int mCurrentFrame;
    State mState;
    QPixmap mNormalPixmap;
    QPixmap mDiedPixmap;
};

#endif // PLAYER_H
