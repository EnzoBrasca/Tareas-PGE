#include "inventario.h"
#include "producto.h"
#include "ui_inventario.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QString>
Inventario::Inventario(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Inventario),
    m_indiceEnEdicion(-1)
{
    ui->setupUi(this);

    connect(ui->pbIngresar, SIGNAL(clicked()), this, SLOT(agregarProducto()));


    ui->tbInventario->installEventFilter(this);
}

Inventario::~Inventario()
{
    delete ui;
}

bool Inventario::eventFilter(QObject *watched, QEvent *event)
{
    // Primero, nos aseguramos que el evento viene del widget que nos interesa
    if (watched == ui->tbInventario) {
        // Segundo, verificamos si el evento es una pulsación de tecla
        if (event->type() == QEvent::KeyPress) {
            // Convertimos el evento genérico a un evento de teclado
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            // Verificamos qué tecla se presionó
            if (keyEvent->key() == Qt::Key_Delete) {
                eliminarProductoSeleccionado();
                return true; // Evento manejado, no procesar más.
            }
            if (keyEvent->key() == Qt::Key_M) {
                iniciarModificacionProducto();
                return true; // Evento manejado.
            }
        }
    }

    // Para todos los demás eventos, los dejamos pasar a su procesamiento normal.
    return QWidget::eventFilter(watched, event);
}

void Inventario::agregarProducto(){
    QString nombre = ui->leNombre->text();
    int cantidad = ui->leCantidad->text().toInt();
    double precio = ui->lePrecio->text().toDouble();


    // --- LÓGICA INTELIGENTE ---
    // Si m_indiceEnEdicion NO es -1, significa que estamos modificando.
    if (m_indiceEnEdicion != -1) {
        // Modificamos directamente el producto en la lista de datos

        productos[m_indiceEnEdicion].Nombre = nombre;
        productos[m_indiceEnEdicion].cantidad = cantidad;
        productos[m_indiceEnEdicion].precio = precio;
    } else {
        // Si no, estamos en modo "agregar", creamos un producto nuevo.
        Producto nuevoProducto;
        nuevoProducto.Nombre = nombre;
        nuevoProducto.cantidad = cantidad;
        nuevoProducto.precio = precio;
        productos.append(nuevoProducto);
    }

    // Finalmente, reseteamos el estado del formulario y actualizamos la lista
    resetearFormulario();
    actualizarTabla();
 }

void Inventario::eliminarProductoSeleccionado()
{
    // Obtenemos el índice de la fila actualmente seleccionada
    int indice = ui->tbInventario->currentRow();

    // Verificamos que haya una selección válida
    if (indice < 0) {
        return; // No hay nada seleccionado
    }

    // Eliminamos el producto de nuestra lista de datos en ese índice
    productos.removeAt(indice);

    // Actualizamos la interfaz gráfica
    actualizarTabla();
}

void Inventario::iniciarModificacionProducto()
{
    int indice = ui->tbInventario->currentRow();
    if (indice < 0) {
        return; // No hay nada seleccionado
    }

    // Guardamos el índice del producto que estamos editando
    m_indiceEnEdicion = indice;

    // Obtenemos una referencia al producto en nuestra lista de datos
    const Producto &producto = productos.at(indice);

    // Llenamos los campos con los datos del producto
    ui->leNombre->setText(producto.Nombre);
    ui->leCantidad->setText(QString::number(producto.cantidad));
    ui->lePrecio->setText(QString::number(producto.precio, 'f', 2));

    // Cambiamos el texto del botón para que sea más claro
    ui->pbCambios->setText("Guardar Cambios");
}

// Resetea el formulario a su estado original
void Inventario::resetearFormulario()
{
    ui->leNombre->clear();
    ui->leCantidad->clear();
    ui->lePrecio->clear();

    ui->pbIngresar->setText("Agregar Producto");
    m_indiceEnEdicion = -1; // Muy importante: volvemos al modo "agregar"
}

void Inventario::actualizarTabla(){
     ui->tbInventario->clear();

    for (const Producto &producto : productos) {
        // 3. Creamos un string formateado con todos los datos del producto.
        // El método arg() es una forma segura y moderna de construir strings.
        QString itemText = QString("%1 (Cant: %2, Precio: $%3)                   Presione M para modificar")
                               .arg(producto.Nombre)
                               .arg(producto.cantidad)
                               .arg(QString::number(producto.precio, 'f', 2)); // Formato con 2 decimales

        // 4. Añadimos el string como un nuevo elemento al listWidget.
        ui->tbInventario->addItem(itemText);
    }
}
