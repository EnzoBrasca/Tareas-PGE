#include "widget.h"
#include "vibora.h"
#include "comida.h"

#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QFont>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    m_timer(new QTimer(this)),
    m_snake(nullptr),
    m_food(nullptr),
    m_gameState(GameState::Playing),
    m_score(0)
{

    setFixedSize(BOARD_WIDTH * TILE_SIZE, BOARD_HEIGHT * TILE_SIZE);

    setFocusPolicy(Qt::StrongFocus);

    connect(m_timer, &QTimer::timeout, this, &Widget::updateGame);

    initGame();
}

Widget::~Widget()
{
    delete m_snake;
    delete m_food;
}

void Widget::initGame()
{
    m_score = 0;


    delete m_snake;
    delete m_food;


    m_snake = new Vibora(QPointF(BOARD_WIDTH / 2, BOARD_HEIGHT / 2));
    spawnFood();

    m_gameState = GameState::Playing;
    m_timer->start(GAME_SPEED_MS);
}

void Widget::updateGame()
{
    if (m_gameState == GameState::Playing) {
        m_snake->move();
        checkCollisions();

        update();
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    drawGrid(&painter);


    if (m_snake) m_snake->paint(&painter);
    if (m_food) m_food->paint(&painter);


    drawScore(&painter);
    if (m_gameState == GameState::GameOver) {
        drawGameOver(&painter);
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (m_gameState == GameState::Playing) {
        switch(event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            m_snake->setDirection(Direction::Up);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            m_snake->setDirection(Direction::Down);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            m_snake->setDirection(Direction::Left);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            m_snake->setDirection(Direction::Right);
            break;
        case Qt::Key_P: // Pausa
            m_gameState = GameState::Paused;
            m_timer->stop();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    } else if (m_gameState == GameState::Paused) {
        if (event->key() == Qt::Key_P) {
            m_gameState = GameState::Playing;
            m_timer->start(GAME_SPEED_MS);
        }
    } else if (m_gameState == GameState::GameOver) {

        if (event->key() == Qt::Key_R) {
            initGame();
        }
    }
}


void Widget::spawnFood()
{

    delete m_food;
    m_food = nullptr;

    QPointF newPos;

    do {
        int x = QRandomGenerator::global()->bounded(0, BOARD_WIDTH);
        int y = QRandomGenerator::global()->bounded(0, BOARD_HEIGHT);
        newPos = QPointF(x, y);
    } while (m_snake->occupies(newPos));

    m_food = new Comida(newPos);
}

void Widget::checkCollisions()
{
    const QPointF headPos = m_snake->headPosition();

    if (headPos.x() < 0 || headPos.x() >= BOARD_WIDTH ||
        headPos.y() < 0 || headPos.y() >= BOARD_HEIGHT) {
        m_gameState = GameState::GameOver;
        m_timer->stop();
        return;
    }


    if (m_snake->checkSelfCollision()) {
        m_gameState = GameState::GameOver;
        m_timer->stop();
        return;
    }


    if (m_food && headPos == m_food->position()) {
        m_snake->grow();
        m_score += 10;
        spawnFood();
    }
}

void Widget::drawGrid(QPainter* painter)
{
    painter->save();
    QRectF board(0, 0, width(), height());
    painter->fillRect(board, QColor(20, 20, 40)); // Fondo azul oscuro
    painter->setPen(QColor(30, 30, 50));
    for (int x = TILE_SIZE; x < width(); x += TILE_SIZE) {
        painter->drawLine(x, 0, x, height());
    }
    for (int y = TILE_SIZE; y < height(); y += TILE_SIZE) {
        painter->drawLine(0, y, width(), y);
    }
    painter->restore();
}

void Widget::drawGameOver(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::white);
    QFont font("Arial", 30, QFont::Bold);
    painter->setFont(font);

    // Sombra para el texto
    painter->setPen(Qt::black);
    painter->drawText(rect().translated(2, 2), Qt::AlignCenter, "GAME OVER");
    // Texto principal
    painter->setPen(Qt::red);
    painter->drawText(rect(), Qt::AlignCenter, "GAME OVER");

    // Texto de reinicio
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::white);
    QRectF restartRect = rect().adjusted(0, 80, 0, 0);
    painter->drawText(restartRect, Qt::AlignCenter, "Presiona 'R' para reiniciar");
    painter->restore();
}

void Widget::drawScore(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 12));
    painter->drawText(5, 20, QString("Puntaje: %1").arg(m_score));
    painter->restore();
}
