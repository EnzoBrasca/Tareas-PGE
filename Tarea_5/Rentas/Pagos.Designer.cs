namespace Rentas
{
    partial class Pagos
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
            panel1 = new Panel();
            linkLabel1 = new LinkLabel();
            label2 = new Label();
            panel1.SuspendLayout();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(17, 55);
            label1.Name = "label1";
            label1.Size = new Size(238, 25);
            label1.TabIndex = 0;
            label1.Text = "Sus comprobantes de pago ";
            // 
            // panel1
            // 
            panel1.Controls.Add(label2);
            panel1.Controls.Add(linkLabel1);
            panel1.Location = new Point(22, 120);
            panel1.Name = "panel1";
            panel1.Size = new Size(521, 50);
            panel1.TabIndex = 1;
            // 
            // linkLabel1
            // 
            linkLabel1.AutoSize = true;
            linkLabel1.Location = new Point(413, 13);
            linkLabel1.Name = "linkLabel1";
            linkLabel1.Size = new Size(91, 25);
            linkLabel1.TabIndex = 0;
            linkLabel1.TabStop = true;
            linkLabel1.Text = "Descargar";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(20, 13);
            label2.Name = "label2";
            label2.Size = new Size(353, 25);
            label2.TabIndex = 1;
            label2.Text = "Pago impuesto automotor Diciembre 2024";
            // 
            // Pagos
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(panel1);
            Controls.Add(label1);
            Name = "Pagos";
            Size = new Size(782, 559);
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Panel panel1;
        private Label label2;
        private LinkLabel linkLabel1;
    }
}
