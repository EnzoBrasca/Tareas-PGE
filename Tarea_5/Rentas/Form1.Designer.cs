namespace Rentas
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            button5 = new Button();
            button6 = new Button();
            button7 = new Button();
            comboBox1 = new ComboBox();
            pictureBox1 = new PictureBox();
            Header = new Panel();
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            panelContenido = new Panel();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            Header.SuspendLayout();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(137, 50);
            button1.Name = "button1";
            button1.Size = new Size(112, 34);
            button1.TabIndex = 0;
            button1.Text = "Impuestos";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(491, 50);
            button2.Name = "button2";
            button2.Size = new Size(294, 34);
            button2.TabIndex = 1;
            button2.Text = "Domicilio fiscal electronico";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Location = new Point(809, 48);
            button3.Name = "button3";
            button3.Size = new Size(112, 34);
            button3.TabIndex = 2;
            button3.Text = "Debito";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Location = new Point(953, 48);
            button4.Name = "button4";
            button4.Size = new Size(150, 34);
            button4.TabIndex = 3;
            button4.Text = "Planes de Pago";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // button5
            // 
            button5.Location = new Point(1134, 48);
            button5.Name = "button5";
            button5.Size = new Size(218, 34);
            button5.TabIndex = 4;
            button5.Text = "Declaraciones Juradas";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // button6
            // 
            button6.Location = new Point(1531, 50);
            button6.Name = "button6";
            button6.Size = new Size(112, 34);
            button6.TabIndex = 5;
            button6.Text = "Usuario";
            button6.UseVisualStyleBackColor = true;
            button6.Click += button6_Click;
            // 
            // button7
            // 
            button7.Location = new Point(1391, 50);
            button7.Name = "button7";
            button7.Size = new Size(112, 34);
            button7.TabIndex = 6;
            button7.Text = "Pagos";
            button7.UseVisualStyleBackColor = true;
            button7.Click += button7_Click;
            // 
            // comboBox1
            // 
            comboBox1.FormattingEnabled = true;
            comboBox1.Items.AddRange(new object[] { "Valores de referencia en alquileres", "Compensación", "Exención adultos mayores o vulnerabilidad social", "Reducción de alícuota por saldo a favor", "Transferencia de crédito", "Contribuyente de extraña jurisdicción" });
            comboBox1.Location = new Point(276, 50);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(182, 33);
            comboBox1.TabIndex = 7;
            comboBox1.Text = "Gestiones";
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // pictureBox1
            // 
            pictureBox1.Image = (Image)resources.GetObject("pictureBox1.Image");
            pictureBox1.Location = new Point(0, 30);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(131, 90);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 8;
            pictureBox1.TabStop = false;
            // 
            // Header
            // 
            Header.Controls.Add(button6);
            Header.Controls.Add(pictureBox1);
            Header.Controls.Add(button1);
            Header.Controls.Add(comboBox1);
            Header.Controls.Add(button2);
            Header.Controls.Add(button7);
            Header.Controls.Add(button3);
            Header.Controls.Add(button4);
            Header.Controls.Add(button5);
            Header.Dock = DockStyle.Top;
            Header.Location = new Point(0, 0);
            Header.Name = "Header";
            Header.Size = new Size(1727, 122);
            Header.TabIndex = 9;
            // 
            // panelContenido
            // 
            panelContenido.Dock = DockStyle.Fill;
            panelContenido.Location = new Point(0, 122);
            panelContenido.Name = "panelContenido";
            panelContenido.Size = new Size(1727, 480);
            panelContenido.TabIndex = 10;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1727, 602);
            Controls.Add(panelContenido);
            Controls.Add(Header);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            Header.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private Button button5;
        private Button button6;
        private Button button7;
        private ComboBox comboBox1;
        private PictureBox pictureBox1;
        private Panel Header;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private Panel panelContenido;
    }
}
