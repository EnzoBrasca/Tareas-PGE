#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QWidget>
#include "producto.h"
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui {
class Inventario;
}
QT_END_NAMESPACE

class Inventario : public QWidget
{
    Q_OBJECT

public:
    Inventario(QWidget *parent = nullptr);
    ~Inventario();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void actualizarTabla();

    void eliminarProductoSeleccionado();
    void iniciarModificacionProducto();
    void resetearFormulario();

    Ui::Inventario *ui;

    QList<Producto> productos;

    int m_indiceEnEdicion;
private slots:
    void agregarProducto();
};
#endif // INVENTARIO_H
