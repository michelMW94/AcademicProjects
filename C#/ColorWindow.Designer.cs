namespace BoolPgia
{
    public partial class ColorWindow
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonWhite = new System.Windows.Forms.Button();
            this.buttonMaroon = new System.Windows.Forms.Button();
            this.buttonYellow = new System.Windows.Forms.Button();
            this.buttonBlue = new System.Windows.Forms.Button();
            this.buttonAqua = new System.Windows.Forms.Button();
            this.buttonLime = new System.Windows.Forms.Button();
            this.buttonRed = new System.Windows.Forms.Button();
            this.buttonFuchsia = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonWhite
            // 
            this.buttonWhite.BackColor = System.Drawing.Color.White;
            this.buttonWhite.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonWhite.Location = new System.Drawing.Point(491, 173);
            this.buttonWhite.Name = "buttonWhite";
            this.buttonWhite.Size = new System.Drawing.Size(120, 120);
            this.buttonWhite.TabIndex = 15;
            this.buttonWhite.UseVisualStyleBackColor = false;
            this.buttonWhite.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonMaroon
            // 
            this.buttonMaroon.BackColor = System.Drawing.Color.Maroon;
            this.buttonMaroon.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonMaroon.Location = new System.Drawing.Point(330, 173);
            this.buttonMaroon.Name = "buttonMaroon";
            this.buttonMaroon.Size = new System.Drawing.Size(120, 120);
            this.buttonMaroon.TabIndex = 14;
            this.buttonMaroon.UseVisualStyleBackColor = false;
            this.buttonMaroon.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonYellow
            // 
            this.buttonYellow.BackColor = System.Drawing.Color.Yellow;
            this.buttonYellow.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonYellow.Location = new System.Drawing.Point(174, 173);
            this.buttonYellow.Name = "buttonYellow";
            this.buttonYellow.Size = new System.Drawing.Size(120, 120);
            this.buttonYellow.TabIndex = 13;
            this.buttonYellow.UseVisualStyleBackColor = false;
            this.buttonYellow.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonBlue
            // 
            this.buttonBlue.BackColor = System.Drawing.Color.Blue;
            this.buttonBlue.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonBlue.Location = new System.Drawing.Point(24, 173);
            this.buttonBlue.Name = "buttonBlue";
            this.buttonBlue.Size = new System.Drawing.Size(120, 120);
            this.buttonBlue.TabIndex = 12;
            this.buttonBlue.UseVisualStyleBackColor = false;
            this.buttonBlue.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonAqua
            // 
            this.buttonAqua.BackColor = System.Drawing.Color.Aqua;
            this.buttonAqua.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonAqua.Location = new System.Drawing.Point(491, 22);
            this.buttonAqua.Name = "buttonAqua";
            this.buttonAqua.Size = new System.Drawing.Size(120, 120);
            this.buttonAqua.TabIndex = 11;
            this.buttonAqua.UseVisualStyleBackColor = false;
            this.buttonAqua.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonLime
            // 
            this.buttonLime.BackColor = System.Drawing.Color.Lime;
            this.buttonLime.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonLime.Location = new System.Drawing.Point(330, 22);
            this.buttonLime.Name = "buttonLime";
            this.buttonLime.Size = new System.Drawing.Size(120, 120);
            this.buttonLime.TabIndex = 10;
            this.buttonLime.UseVisualStyleBackColor = false;
            this.buttonLime.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonRed
            // 
            this.buttonRed.BackColor = System.Drawing.Color.Red;
            this.buttonRed.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonRed.Location = new System.Drawing.Point(174, 22);
            this.buttonRed.Name = "buttonRed";
            this.buttonRed.Size = new System.Drawing.Size(120, 120);
            this.buttonRed.TabIndex = 9;
            this.buttonRed.UseVisualStyleBackColor = false;
            this.buttonRed.Click += new System.EventHandler(this.button_Click);
            // 
            // buttonFuchsia
            // 
            this.buttonFuchsia.BackColor = System.Drawing.Color.Fuchsia;
            this.buttonFuchsia.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonFuchsia.Location = new System.Drawing.Point(24, 22);
            this.buttonFuchsia.Name = "buttonFuchsia";
            this.buttonFuchsia.Size = new System.Drawing.Size(120, 120);
            this.buttonFuchsia.TabIndex = 8;
            this.buttonFuchsia.UseVisualStyleBackColor = false;
            this.buttonFuchsia.Click += new System.EventHandler(this.button_Click);
            // 
            // ColorWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(660, 323);
            this.Controls.Add(this.buttonWhite);
            this.Controls.Add(this.buttonMaroon);
            this.Controls.Add(this.buttonYellow);
            this.Controls.Add(this.buttonBlue);
            this.Controls.Add(this.buttonAqua);
            this.Controls.Add(this.buttonLime);
            this.Controls.Add(this.buttonRed);
            this.Controls.Add(this.buttonFuchsia);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Location = new System.Drawing.Point(220, 150);
            this.Name = "ColorWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Pick A Color:";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonWhite;
        private System.Windows.Forms.Button buttonMaroon;
        private System.Windows.Forms.Button buttonYellow;
        private System.Windows.Forms.Button buttonBlue;
        private System.Windows.Forms.Button buttonAqua;
        private System.Windows.Forms.Button buttonLime;
        private System.Windows.Forms.Button buttonRed;
        private System.Windows.Forms.Button buttonFuchsia;
    }
}