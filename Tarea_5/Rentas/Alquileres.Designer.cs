namespace Rentas
{
    partial class Alquileres
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            checkBox1 = new CheckBox();
            checkBox2 = new CheckBox();
            txtNumero = new TextBox();
            txtFecha = new TextBox();
            button1 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI Black", 9F, FontStyle.Bold, GraphicsUnit.Point, 0);
            label1.Location = new Point(32, 52);
            label1.Name = "label1";
            label1.Size = new Size(176, 25);
            label1.TabIndex = 0;
            label1.Text = "Cuenta a consultar";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(31, 118);
            label2.Name = "label2";
            label2.Size = new Size(166, 25);
            label2.TabIndex = 1;
            label2.Text = "¿Qué vas a realizar?";
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(32, 169);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(349, 29);
            checkBox1.TabIndex = 2;
            checkBox1.Text = "Autoliquidación del Impuesto de Sellos";
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Location = new Point(32, 225);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(469, 29);
            checkBox2.TabIndex = 3;
            checkBox2.Text = "Presentación de Declaración Jurada de Ingresos Brutos";
            checkBox2.UseVisualStyleBackColor = true;
            // 
            // txtNumero
            // 
            txtNumero.ForeColor = Color.Gray;
            txtNumero.Location = new Point(31, 279);
            txtNumero.Name = "txtNumero";
            txtNumero.Size = new Size(301, 31);
            txtNumero.TabIndex = 4;
            txtNumero.Text = "Numero de cuenta inmobiliaria";
            txtNumero.Enter += this.txtNumero_Enter;
            txtNumero.Leave += this.txtNumero_Leave;
            // 
            // txtFecha
            // 
            txtFecha.ForeColor = Color.Gray;
            txtFecha.Location = new Point(387, 279);
            txtFecha.Multiline = true;
            txtFecha.Name = "txtFecha";
            txtFecha.Size = new Size(161, 56);
            txtFecha.TabIndex = 5;
            txtFecha.Text = "Fecha\r\nmm/dd/yyyy\r\n";
            txtFecha.Enter += this.txtFecha_Enter;
            txtFecha.Leave += this.txtFecha_Leave;
            // 
            // button1
            // 
            button1.Location = new Point(590, 282);
            button1.Name = "button1";
            button1.Size = new Size(112, 34);
            button1.TabIndex = 6;
            button1.Text = "Consultar";
            button1.UseVisualStyleBackColor = true;
            button1.Click += this.button1_Click;
            // 
            // Alquileres
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(button1);
            Controls.Add(txtFecha);
            Controls.Add(txtNumero);
            Controls.Add(checkBox2);
            Controls.Add(checkBox1);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Alquileres";
            Size = new Size(821, 502);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private CheckBox checkBox1;
        private CheckBox checkBox2;
        private TextBox txtNumero;
        private TextBox txtFecha;
        private Button button1;
    }
}
