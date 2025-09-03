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
    public partial class Debito : UserControl
    {
        public Debito()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
           if(SlideDown.SelectedIndex != -1)
            {
                SlideDown.SelectedIndex = 0;
            }
                
        }
    }
}
