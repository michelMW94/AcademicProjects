using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace BoolPgia
{
    public class GameStartWindow : Form
    {
        //// const members
        public const int k_MaximalNumberOfChances = 10;
        public const int k_MinimalNumberOfChances = 4;
        //// regular members
        private int m_NumerOfChances;
        private Button GameStartButton;
        private Button ChoosingNumberChancesButton;

        public GameStartWindow() // c'tor
        {
            m_NumerOfChances = k_MinimalNumberOfChances;
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.ChoosingNumberChancesButton = new System.Windows.Forms.Button();
            this.GameStartButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            //// ChoosingNumberChancesButton
            this.ChoosingNumberChancesButton.BackColor = System.Drawing.SystemColors.Control;
            this.ChoosingNumberChancesButton.Location = new System.Drawing.Point(10, 32);
            this.ChoosingNumberChancesButton.Name = "ChoosingNumberChancesButton";
            this.ChoosingNumberChancesButton.Size = new System.Drawing.Size(480, 43);
            this.ChoosingNumberChancesButton.TabIndex = 0;
            this.ChoosingNumberChancesButton.Text = "Number Of Chances: 4";
            this.ChoosingNumberChancesButton.UseVisualStyleBackColor = false;
            this.ChoosingNumberChancesButton.Click += new System.EventHandler(this.numberChancesButton_Click);
            //// GameStartButton
            this.GameStartButton.BackColor = System.Drawing.SystemColors.Control;
            this.GameStartButton.Location = new System.Drawing.Point(334, 175);
            this.GameStartButton.Name = "GameStartButton";
            this.GameStartButton.Size = new System.Drawing.Size(138, 35);
            this.GameStartButton.TabIndex = 1;
            this.GameStartButton.Text = "Start";
            this.GameStartButton.UseVisualStyleBackColor = false;
            this.GameStartButton.Click += new System.EventHandler(this.gameStartButton_Click);
            //// GameStartWindow
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(497, 222);
            this.Controls.Add(this.GameStartButton);
            this.Controls.Add(this.ChoosingNumberChancesButton);
            this.Name = "GameStartWindow";
            this.Text = "Bool Pgia";
            this.ResumeLayout(false);
            this.CenterToScreen();
        }

        private void numberChancesButton_Click(object sender, EventArgs e) // increasing number of chances button click method
        {
            int ButtonTextLenght = ChoosingNumberChancesButton.Text.Length;
            if (m_NumerOfChances == k_MaximalNumberOfChances)
            {
                m_NumerOfChances = k_MinimalNumberOfChances;
                ChoosingNumberChancesButton.Text = ChoosingNumberChancesButton.Text.Remove(ButtonTextLenght - 2);
            }
            else
            {
                ChoosingNumberChancesButton.Text = ChoosingNumberChancesButton.Text.Remove(ButtonTextLenght - 1);
                m_NumerOfChances++;
            }

            ChoosingNumberChancesButton.Text += m_NumerOfChances.ToString();
        }

        private void gameStartButton_Click(object sender, EventArgs e) // Game start burron click method
        {
            TheGame newGameWindow = new TheGame(m_NumerOfChances);
            newGameWindow.ShowDialog();
        }
    }
}
