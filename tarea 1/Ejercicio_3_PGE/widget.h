#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTimer;
class Vibora;
class Comida;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void updateGame();

private:
    void initGame();
    void spawnFood();
    void checkCollisions();
    void drawGrid(QPainter* painter);
    void drawGameOver(QPainter* painter);
    void drawScore(QPainter* painter);

    enum class GameState { Playing, Paused, GameOver };


    static const int BOARD_WIDTH = 30;
    static const int BOARD_HEIGHT = 25;
    static const int GAME_SPEED_MS = 120;

    QTimer* m_timer;
    Vibora* m_snake;
    Comida* m_food;
    GameState m_gameState;
    int m_score;
};

#endif // WIDGET_H
