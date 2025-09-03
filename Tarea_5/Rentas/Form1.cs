namespace Rentas
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void CargarVista(UserControl vistaParaCargar)
        {
            this.panelContenido.Controls.Clear();

            vistaParaCargar.Dock = DockStyle.Fill;

            this.panelContenido.Controls.Add(vistaParaCargar);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            CargarVista(new Impuestos());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            CargarVista(new Domicilio());
        }
        private void button3_Click(object sender, EventArgs e)
        {
            CargarVista(new Debito());
        }
        private void button4_Click(object sender, EventArgs e)
        {
            CargarVista(new Planes());
        }
        private void button5_Click(object sender, EventArgs e)
        {
            CargarVista(new Declaraciones());
        }
        private void button6_Click(object sender, EventArgs e)
        {
            CargarVista(new Usuario());
        }
        private void button7_Click(object sender, EventArgs e)
        {
            CargarVista(new Pagos());
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox1.SelectedIndex)
            {
                case 0:
                    CargarVista(new Alquileres());
                    break;
                case 1:
                    CargarVista(new Compensaciones());
                    break;
                case 2:
                    CargarVista(new Exenciones());
                    break;
                case 3:
                    CargarVista(new Reduccion());
                    break;
                case 4:
                    CargarVista(new Transferencia());
                    break;
                case 5:
                    CargarVista(new Contribuyente());
                    break;

            }
        }
    }
}
