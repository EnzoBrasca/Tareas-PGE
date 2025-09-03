namespace Rentas
{
    partial class Debito
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
            SlideDown = new ComboBox();
            button1 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(34, 58);
            label1.Name = "label1";
            label1.Size = new Size(199, 25);
            label1.TabIndex = 0;
            label1.Text = "Para nuevas adheciones";
            // 
            // SlideDown
            // 
            SlideDown.DropDownStyle = ComboBoxStyle.DropDownList;
            SlideDown.FormattingEnabled = true;
            SlideDown.Items.AddRange(new object[] { "Impuestos no adheridos", "Automotor", "Inmueble", "Bienes personales" });
            SlideDown.Location = new Point(32, 122);
            SlideDown.Name = "SlideDown";
            SlideDown.Size = new Size(354, 33);
            SlideDown.TabIndex = 1;
            // 
            // button1
            // 
            button1.Location = new Point(32, 218);
            button1.Name = "button1";
            button1.Size = new Size(112, 34);
            button1.TabIndex = 2;
            button1.Text = "Adherir";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // Debito
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(button1);
            Controls.Add(SlideDown);
            Controls.Add(label1);
            Name = "Debito";
            Size = new Size(578, 638);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private ComboBox SlideDown;
        private Button button1;
    }
}
