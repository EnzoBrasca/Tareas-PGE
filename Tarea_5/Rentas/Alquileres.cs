using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rentas
{
    public partial class Alquileres : UserControl
    {
        public Alquileres()
        {
            InitializeComponent();
        }

        private void txtNumero_Enter(object sender, EventArgs e)
        {
            if(txtNumero.ForeColor == Color.Gray)
            {
                txtNumero.Text = "";
                txtNumero.ForeColor = Color.Black;
            }
        }

        private void txtNumero_Leave(object sender, EventArgs e)
        {
            if (txtNumero.Text == "")
            {
                txtNumero.Text = "Numero de cuenta inmobiliaria";
                txtNumero.ForeColor = Color.Gray;
            }
        }

        private void txtFecha_Enter(object sender, EventArgs e)
        {
            if (txtNumero.ForeColor == Color.Gray)
            {
                txtFecha.Text = "";
                txtFecha.ForeColor = Color.Black;
            }
        }

        private void txtFecha_Leave(object sender, EventArgs e)
        {

            if (txtFecha.Text == "")
            {
                txtFecha.Text = "Fecha\r\nmm/dd/yyyy\r\n";
                txtFecha.ForeColor = Color.Gray;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
           txtNumero.Text = "Numero de cuenta inmobiliaria";
           txtFecha.Text = "Fecha\r\nmm/dd/yyyy\r\n";
        }
    }
}
