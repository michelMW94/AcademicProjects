using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace BoolPgia
{
    public class TheGame : Form
    {
        //// const members decleration
        protected const int k_SizeOfSequence = 4;
        protected const int k_MinimalRangeValue = 0;
        protected const int k_MaximalRangeValue = 7;
        protected const int k_NumberOfButtonsInAlevel = 9;
        protected const int k_ArrowButtonIndex = 4;
        protected const int k_FirstScoreButtonIndex = 5;
        protected static int s_NumberOfColoredButtons = 0;
        //// readonly member decleration 
        protected readonly List<Color> r_ColorArrey;
        //// regular members decleration
        private List<Color> m_ColorSequence;
        private Button SequenceButton1;
        private Button SequenceButton2;
        private Button SequenceButton3;
        private Button SequenceButton4;
        private List<List<Button>> m_ButtonList;
        private int m_GameSize;
        private ColorWindow m_CurrentLevelColorWindow;
        private int m_Currentlevel;
        //// sctruct of the game score after each step
        public struct Score
        {
            // decleration of member of the struct
            public int MatchesWithPosition;
            public int MatchesWithoutPosition;

            public Score(int i_MatchesWithoutPosition, int i_MatchesWithPosition)
            {
                MatchesWithPosition = i_MatchesWithPosition;
                MatchesWithoutPosition = i_MatchesWithoutPosition;
            }
        }

        public TheGame(int i_GameSize) // c'tor
        {
            m_GameSize = i_GameSize;
            r_ColorArrey = new List<Color>() { Color.Fuchsia, Color.Red, Color.Lime, Color.Aqua, Color.Blue, Color.Yellow, Color.Maroon, Color.White };
            m_ColorSequence = CreateARandomColorSequence();
            m_ButtonList = new List<List<Button>>(i_GameSize);
            m_Currentlevel = 0;
              m_CurrentLevelColorWindow = new ColorWindow();
            InitializeComponent();    
        }

        private void createtheGameBoard() // creating the game's board method
        {
            System.Drawing.Point currentPoint = new Point(10, 75);
            for (int i = 0; i < m_GameSize; i++)
            {
                m_ButtonList.Add(new List<Button>(k_NumberOfButtonsInAlevel));
                for (int j = 0; j < k_NumberOfButtonsInAlevel; j++)
                {
                    m_ButtonList[i].Add(new Button());
                    if (j < k_SizeOfSequence)
                    {
                        createGameSequenceGuessButoon(i, j, ref currentPoint); // creating guess buttons
                    }
                    else if (j == k_ArrowButtonIndex)
                    {
                        createArrowButoon(i, ref currentPoint);
                    }
                    else
                    {
                        createResultButton(i, j, ref currentPoint);
                    }

                    determaningButtonEnableStatus(i, j);
                    this.m_ButtonList[i][j].TabIndex = 1;
                    this.Controls.Add(m_ButtonList[i][j]);
                }
            }
        }

        private void determaningButtonEnableStatus(int i_IndexOfRow, int i_IndexOfNumberInRow) // determamnig button enable status method
        {
            if (i_IndexOfRow == 0 && i_IndexOfNumberInRow < k_SizeOfSequence)
            {
                m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Enabled = true;
            }
            else
            {
                m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Enabled = false;
            }
        }

        private void InitializeComponent()
        {
            this.SequenceButton1 = new System.Windows.Forms.Button();
            this.SequenceButton2 = new System.Windows.Forms.Button();
            this.SequenceButton3 = new System.Windows.Forms.Button();
            this.SequenceButton4 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            //// SequenceButton1
            this.SequenceButton1.BackColor = System.Drawing.Color.Black;
            this.SequenceButton1.Enabled = false;
            this.SequenceButton1.Location = new System.Drawing.Point(10, 10);
            this.SequenceButton1.Name = "SequenceButton1";
            this.SequenceButton1.Size = new System.Drawing.Size(45, 45);
            this.SequenceButton1.TabIndex = 0;
            this.SequenceButton1.UseVisualStyleBackColor = false;
            //// SequenceButton2
            this.SequenceButton2.BackColor = System.Drawing.Color.Black;
            this.SequenceButton2.Enabled = false;
            this.SequenceButton2.Location = new System.Drawing.Point(65, 10);
            this.SequenceButton2.Name = "SequenceButton2";
            this.SequenceButton2.Size = new System.Drawing.Size(45, 45);
            this.SequenceButton2.TabIndex = 1;
            this.SequenceButton2.UseVisualStyleBackColor = false;
            //// SequenceButton3
            this.SequenceButton3.BackColor = System.Drawing.Color.Black;
            this.SequenceButton3.Enabled = false;
            this.SequenceButton3.Location = new System.Drawing.Point(120, 10);
            this.SequenceButton3.Name = "SequenceButton3";
            this.SequenceButton3.Size = new System.Drawing.Size(45, 45);
            this.SequenceButton3.TabIndex = 2;
            this.SequenceButton3.UseVisualStyleBackColor = false;
            //// SequenceButton4
            this.SequenceButton4.BackColor = System.Drawing.Color.Black;
            this.SequenceButton4.Enabled = false;
            this.SequenceButton4.Location = new System.Drawing.Point(175, 10);
            this.SequenceButton4.Name = "SequenceButton4";
            this.SequenceButton4.Size = new System.Drawing.Size(45, 45);
            this.SequenceButton4.TabIndex = 3;
            this.SequenceButton4.UseVisualStyleBackColor = false;
            //// TheGame

            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(350, 400);
            this.Controls.Add(this.SequenceButton4);
            this.Controls.Add(this.SequenceButton3);
            this.Controls.Add(this.SequenceButton2);
            this.Controls.Add(this.SequenceButton1);
            createtheGameBoard();
            this.Name = "TheGame";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Bool Pgia";
            this.ResumeLayout(false);
            currentLevelGameProcess();
            this.CenterToParent();
            this.Height -= 100;
        }

        private void currentLevelGameProcess() // curremt game level method
        {
            for (int i = 0; i < m_GameSize; i++)
            {   
                for (int j = 0; j < k_SizeOfSequence + 1; j++)
                {  
                    if (j < k_SizeOfSequence)
                    {
                        m_ButtonList[i][j].Click += new EventHandler(this.guessButton_Click);
                    }
                   else
                    {
                        m_ButtonList[i][j].Click += new EventHandler(this.arrowButton_Click);
                    }
                }
            }
        }
        
        private void arrowButton_Click(object sender, EventArgs e) // arrow button click method that detemanes the score and moves to next level
        {
            Button ArrowButton = sender as Button;
            ArrowButton.Enabled = false;
            Score currentLevelScore = calculatingUserGuessScore();
            int NumberOfBul = currentLevelScore.MatchesWithPosition;
            for(int j = k_FirstScoreButtonIndex; j < k_NumberOfButtonsInAlevel; j++)
            {
                if(currentLevelScore.MatchesWithPosition > 0)
                {
                    m_ButtonList[m_Currentlevel][j].BackColor = Color.Black;
                    currentLevelScore.MatchesWithPosition--;
                }
                else if(currentLevelScore.MatchesWithoutPosition > 0)
                {
                    m_ButtonList[m_Currentlevel][j].BackColor = Color.Yellow;
                    currentLevelScore.MatchesWithoutPosition--;
                }
            }

            m_Currentlevel++;
            if(NumberOfBul == k_SizeOfSequence || m_Currentlevel == m_GameSize)
            {
                SequenceButton1.BackColor = m_ColorSequence[0];
                SequenceButton2.BackColor = m_ColorSequence[1];
                SequenceButton3.BackColor = m_ColorSequence[2];
                SequenceButton4.BackColor = m_ColorSequence[3];
            }
            else
            {
                for(int i = 0; i < k_SizeOfSequence; i++)
                {
                    m_ButtonList[m_Currentlevel][i].Enabled = true;
                }

                m_CurrentLevelColorWindow = new ColorWindow(); 
            }

            s_NumberOfColoredButtons = 0;
        }

        private Score calculatingUserGuessScore() // calculeting level score method
        {
            Score score = new Score(0, 0);
            for (int j = 0; j < k_SizeOfSequence; j++)
            {
                m_ButtonList[m_Currentlevel][j].Enabled = false;
                if (m_ButtonList[m_Currentlevel][j].BackColor == m_ColorSequence[j])
                {
                    score.MatchesWithPosition++;
                }
                else
                {
                    for (int k = 0; k < k_SizeOfSequence; k++)
                    {
                        if (m_ButtonList[m_Currentlevel][j].BackColor == m_ColorSequence[k])
                        {
                            score.MatchesWithoutPosition++;
                            break;
                        }
                    }
                }
            }

            return score;
        }

        private void guessButton_Click(object sender, EventArgs e) // guess button click methd for choosing a color
        {
            Button ClickedButton = sender as Button;
            if (ClickedButton.BackColor != Color.WhiteSmoke)
            {
                m_CurrentLevelColorWindow.ColorToEnable = ClickedButton.BackColor;
                s_NumberOfColoredButtons--;
            }

            if (m_CurrentLevelColorWindow.ShowDialog() == DialogResult.OK)
            {
                ClickedButton.BackColor = m_CurrentLevelColorWindow.CurrentChosenColor;
                s_NumberOfColoredButtons++;
                if(s_NumberOfColoredButtons >= k_SizeOfSequence)
                {
                    m_ButtonList[m_Currentlevel][k_ArrowButtonIndex].Enabled = true;
                }
            }    
        }
        
        private void createResultButton(int i_IndexOfRow, int i_IndexOfNumberInRow, ref Point io_CurrentPoint) // creating result button method
        {
            if (i_IndexOfNumberInRow == k_FirstScoreButtonIndex + 2)
            {
                io_CurrentPoint = m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 2].Location;
                io_CurrentPoint.Offset(0, m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 2].Height + 5);
            }
            else
            {
                io_CurrentPoint = m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 1].Location;
                if (i_IndexOfNumberInRow == k_FirstScoreButtonIndex)
                {
                    io_CurrentPoint.Offset(m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 1].Width + 5, -15);
                }
                else
                {
                    io_CurrentPoint.Offset(m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 1].Width + 5, 0);
                }
            }

            m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Location = io_CurrentPoint;
            m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Size = new System.Drawing.Size(20, 20);
        }
        
        private void createArrowButoon(int i_IndexOfRow, ref Point io_CurrentPoint) // creating arrow button method
        {
            io_CurrentPoint = m_ButtonList[i_IndexOfRow][k_ArrowButtonIndex - 1].Location;
            io_CurrentPoint.Offset(m_ButtonList[i_IndexOfRow][k_ArrowButtonIndex - 1].Width + 10, 15);
            m_ButtonList[i_IndexOfRow][k_ArrowButtonIndex].Location = io_CurrentPoint;
            m_ButtonList[i_IndexOfRow][k_ArrowButtonIndex].Size = new System.Drawing.Size(50, 20);
            m_ButtonList[i_IndexOfRow][k_ArrowButtonIndex].Text = "-->>";
        }
        
        private void createGameSequenceGuessButoon(int i_IndexOfRow, int i_IndexOfNumberInRow, ref Point io_CurrentPoint) // creating computer sequence
        {
            if (i_IndexOfNumberInRow == 0)
            {
                if (i_IndexOfRow != 0)
                {
                    io_CurrentPoint = m_ButtonList[i_IndexOfRow - 1][i_IndexOfNumberInRow].Location;
                    io_CurrentPoint.Offset(0, m_ButtonList[i_IndexOfRow - 1][i_IndexOfNumberInRow].Height + 10);
                }
            }
            else
            {
                io_CurrentPoint = m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 1].Location;
                io_CurrentPoint.Offset(m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow - 1].Width + 10, 0);
            }

            m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].BackColor = Color.WhiteSmoke;
            m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Location = io_CurrentPoint;
            m_ButtonList[i_IndexOfRow][i_IndexOfNumberInRow].Size = new System.Drawing.Size(45, 45);
        }
        //// creating  a random sequence of letters method
        private List<Color> CreateARandomColorSequence()
        {
            List<Color> randomColorSequence = new List<Color>();
            bool isEveryColorOneTime = false;
            int theRandomNumer;
            Random rand = new Random();
            for (int i = 0; i < k_SizeOfSequence; i++)
            {
                theRandomNumer = rand.Next(k_MinimalRangeValue, k_MaximalRangeValue);
                if (i != 0)
                {
                    isEveryColorOneTime = checkForMultipulationOfColorsInRandomSequence(r_ColorArrey[theRandomNumer], randomColorSequence);
                    while (isEveryColorOneTime != true)
                    {
                        theRandomNumer = rand.Next(k_MinimalRangeValue, k_MaximalRangeValue);
                        isEveryColorOneTime = checkForMultipulationOfColorsInRandomSequence(r_ColorArrey[theRandomNumer], randomColorSequence);
                    }
                }

                randomColorSequence.Add(r_ColorArrey[theRandomNumer]);
            }

            return randomColorSequence;
        }

         //// checking for multipole letters in the random sequence by the computer
        private bool checkForMultipulationOfColorsInRandomSequence(Color io_CheckedColor, List<Color> io_SequenceOfColors)
        {
            bool result = true;
            for (int i = 0; i < io_SequenceOfColors.Count; i++)
            {
                if (io_SequenceOfColors[i] == io_CheckedColor)
                {
                    result = false;
                    break;
                }
            }

            return result;
        }     
    }
}
