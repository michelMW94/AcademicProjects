using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace BoolPgia
{
    public partial class ColorWindow : Form
    {
        //// decleration of member of the class
        private Color m_CurrentChosenColor;
        private Color m_ColorToEnable;

        public ColorWindow() // c'tor
        {
            InitializeComponent();
            ColorToEnable = Color.Black; // default color           
        }

        public Color CurrentChosenColor // setter and getter of current color that was chosen in the game
        {
            get { return m_CurrentChosenColor; }
            set { m_CurrentChosenColor = value; }
        }

        public Color ColorToEnable // setter and getter of color to enable if the game user chooses another color
        {
            get { return m_ColorToEnable; }
            set { m_ColorToEnable = value; }
        }

        private void enableButten() // enable disabled colored Method
        {
           if(m_ColorToEnable == Color.Fuchsia)
            {
                buttonFuchsia.Enabled = true;
            }
           else if(m_ColorToEnable == Color.Red)
            {
                buttonRed.Enabled = true;
            }
           else if (m_ColorToEnable == Color.Lime)
            {
                buttonLime.Enabled = true;
            }
            else if (m_ColorToEnable == Color.Aqua)
            {
                buttonAqua.Enabled = true;
            }
            else if (m_ColorToEnable == Color.Blue)
            {
                buttonBlue.Enabled = true;
            }
            else if (m_ColorToEnable == Color.Yellow)
            {
                buttonYellow.Enabled = true;
            }
            else if (m_ColorToEnable == Color.Maroon)
            {
                buttonMaroon.Enabled = true;
            }
            else
            {
                buttonWhite.Enabled = true;
            }
        }

        private void button_Click(object sender, EventArgs e) // color buttons click  event method
        {
            if(m_ColorToEnable != Color.Black)
            {
                enableButten();
            }

            Button currentColor = sender as Button;
            m_CurrentChosenColor = currentColor.BackColor;
            currentColor.Enabled = false;
        }
    }
}
