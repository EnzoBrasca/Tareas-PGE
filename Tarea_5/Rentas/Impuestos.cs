using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rentas
{
    public partial class Impuestos : UserControl
    {
        public Impuestos()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            label1 = new Label();
            panel1 = new Panel();
            checkedListBox1 = new CheckedListBox();
            button1 = new Button();
            panel1.SuspendLayout();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(49, 45);
            label1.Name = "label1";
            label1.Size = new Size(128, 25);
            label1.TabIndex = 0;
            label1.Text = "Tus Impuestos";
            // 
            // panel1
            // 
            panel1.Controls.Add(button1);
            panel1.Controls.Add(checkedListBox1);
            panel1.Location = new Point(55, 111);
            panel1.Name = "panel1";
            panel1.Size = new Size(320, 339);
            panel1.TabIndex = 1;
            // 
            // checkedListBox1
            // 
            checkedListBox1.FormattingEnabled = true;
            checkedListBox1.Items.AddRange(new object[] { "Enero 2025", "Febrero 2025", "Marzo 2025", "Abril 2025", "Mayo 2025", "Junio 2025", "Julio 2025", "Agosto 2025", "Septiembre 2025", "Octubre 2025", "Noviembre 2025", "Diciembre 2025" });
            checkedListBox1.Location = new Point(3, 3);
            checkedListBox1.Name = "checkedListBox1";
            checkedListBox1.Size = new Size(320, 284);
            checkedListBox1.TabIndex = 0;
            // 
            // button1
            // 
            button1.Location = new Point(3, 302);
            button1.Name = "button1";
            button1.Size = new Size(317, 34);
            button1.TabIndex = 1;
            button1.Text = "Pagar";
            button1.UseVisualStyleBackColor = true;
            // 
            // Ventana
            // 
            Controls.Add(panel1);
            Controls.Add(label1);
            Name = "Ventana";
            Size = new Size(594, 554);
            panel1.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        private Panel panel1;
        private CheckedListBox checkedListBox1;
        private Button button1;
        private Label label1;

    }
}
