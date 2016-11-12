using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Marine.Battle
{
    public partial class MBForm : Form
    { 
        private const int MapSize = 10;
        
        private int UserY;

        private int UserX;

        private bool PcTurn;

        private bool UserTurn;

        private Timer MoveTimer;

        private Timer CounterOnButtonTimer;

        private int CounterOnButton;
        
        public MBForm()
        {
            InitializeComponent();
            this.DataGridMap.RowCount = MapSize;
            for (int i = 0; i < MapSize; i++)
                this.DataGridMap.Rows[i].HeaderCell.Value = Convert.ToString(i+1);
            this.MessageStrip.Text = "Для початку гри згенеруйте карту кораблів.";
            this.PcTurn = false;
            this.UserTurn = false;
            this.UserY = this.UserX = -1;
            this.CounterOnButtonTimer = new Timer();
            this.CounterOnButtonTimer.Interval = 1000;
            this.CounterOnButtonTimer.Tick += new EventHandler(CounterOnButtonHandler);
            this.MoveTimer = new Timer();
            this.MoveTimer.Interval = 4000;
            this.MoveTimer.Tick += new EventHandler(AutoMoveHandler);
            this.ButtonNext.EnabledChanged += new EventHandler(ButtonNextStateHandler);
        }

        public delegate void RequestGenerateMapDelegate(String Whose);

        public event RequestGenerateMapDelegate RequestGenerateMap;

        public delegate void RequestMapDelegate(String Whose, String What);

        public event RequestMapDelegate RequestMap;

        public delegate void SendUserMoveDelegate (int Y, int X);

        public event SendUserMoveDelegate SendUserMove;

        public delegate void SendPCMoveDelegate();

        public event SendPCMoveDelegate SendPCMove;

        private void згенеруватиКартуToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.новаГраToolStripMenuItem.Enabled = true;
            this.RequestGenerateMap("User");
            this.RequestMap("User", "Ships");
            this.MessageStrip.Text = "Карту згенеровано. Перегенерувати / Розпочати.";
        }

        private void розпочатиПершимToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.DataGridMap.Enabled = true;
            this.RequestGenerateMap("PC");
            this.RequestMap("User", "Attack");
            this.згенеруватиКартуToolStripMenuItem.Enabled = false;
            this.новаГраToolStripMenuItem.Enabled = false;
            this.MessageStrip.Text = "Ваш хід.";
        }

        private void розпочатиДругимToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.RequestGenerateMap("PC");
            this.RequestMap("PC", "Attack");
            this.згенеруватиКартуToolStripMenuItem.Enabled = false;
            this.новаГраToolStripMenuItem.Enabled = false;
            this.ButtonNext.Enabled = true;
            this.ButtonNext_Click(sender, e);
            this.MessageStrip.Text = "Хід супротивника.";
        }

        private void DataGridMap_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            this.ButtonFire.Enabled = true;
            this.UserY = e.RowIndex + 1;
            this.UserX = e.ColumnIndex + 1;
            this.MessageStrip.Text = String.Format("Постріл по координатах: {0} {1}", this.TransLiterator(UserX), UserY);
        }

        private void ButtonFire_Click(object sender, EventArgs e)
        {
            this.ButtonFire.Enabled = false;
            this.DataGridMap.Enabled = false;
            this.SendUserMove(UserY, UserX);
        }

        private void ButtonNext_Click(object sender, EventArgs e)
        {
            this.MoveTimer.Stop();
            this.CounterOnButtonTimer.Stop();
            this.ButtonNext.Text = "ДАЛІ...";
            if (this.UserTurn == true)
            {
                this.RequestMap("User", "Attack");
                this.MessageStrip.Text = "Ваша черга здійснювати постріл.";
                this.UserTurn = false;
                this.ButtonNext.Enabled = false;
                this.DataGridMap.Enabled = true;
            }
            else if (this.PcTurn == false)
            {
                this.RequestMap("PC", "Attack");
                this.MessageStrip.Text = "Черга супротивника здійснювати простріл.";
                this.PcTurn = true;
                this.ButtonNext.Enabled = false;
                this.ButtonNext.Enabled = true;
            }
            else
            { // використати при першому ході компютера;            
                this.ButtonNext.Enabled = false;
                this.PcTurn = false;
                this.SendPCMove();
            }
        }

        public void AcceptMapHandler(char[,] Map, String Whose, String What)
        {
            for (int i = 0; i < MapSize; i++)
                for (int j = 0; j < MapSize; j++)
                {
                    this.DataGridMap.Rows[i].Cells[j].Value = Convert.ToString(Map[i, j]);
                    if (What == "Ships")
                    {

                        if (Map[i, j] == ' ')
                        {
                            this.DataGridMap.Rows[i].Cells[j].Style.BackColor = Color.LightBlue;
                            this.DataGridMap.Rows[i].Cells[j].Style.SelectionBackColor = Color.LightBlue;
                        }
                        else if (Map[i, j] == 'X')
                        {
                            this.DataGridMap.Rows[i].Cells[j].Style.BackColor = Color.Firebrick;
                            this.DataGridMap.Rows[i].Cells[j].Style.SelectionBackColor = Color.Firebrick;
                        }
                    }
                    else
                    {
                        if (Map[i, j] == ' ')
                        {
                            this.DataGridMap.Rows[i].Cells[j].Style.BackColor = Color.RoyalBlue;
                            this.DataGridMap.Rows[i].Cells[j].Style.SelectionBackColor = Color.Blue;
                        }
                        else if (Map[i, j] == 'X')
                        {
                            this.DataGridMap.Rows[i].Cells[j].Style.BackColor = Color.Firebrick;
                            this.DataGridMap.Rows[i].Cells[j].Style.SelectionBackColor = Color.Firebrick;
                        }
                        else
                        {
                            this.DataGridMap.Rows[i].Cells[j].Style.BackColor = Color.LightBlue;
                            this.DataGridMap.Rows[i].Cells[j].Style.SelectionBackColor = Color.LightBlue;
                        }
                    }
                }
        }

        public void AcceptResultHandler(String Whose, String Result)
        {
            if (Whose == "User")
            {
                this.RequestMap("User", "Attack");
                if (Result == "Miss")
                {
                    this.ButtonNext.Enabled = true;
                    this.MessageStrip.Text = "Постріл здійснено мимо, перхід ходу.";
                }
                else if (Result == "Already")
                {
                    this.DataGridMap.Enabled = true;
                    this.MessageStrip.Text = "По цих координатах Ви вже стріляли, Ваш хід.";
                }
                else if (Result == "Wound")
                {
                    this.DataGridMap.Enabled = true;
                    this.MessageStrip.Text = "Корабель поранено, Ваш хід.";
                }
                else if (Result == "Kill")
                {
                    this.DataGridMap.Enabled = true;
                    this.MessageStrip.Text = "Корабель вбито, Ваш хід.";
                }
                else
                {
                    this.згенеруватиКартуToolStripMenuItem.Enabled = true;
                    this.MessageStrip.Text = "Для початку гри згенеруйте карту кораблів.";
                    MessageBox.Show("Ви перемогли!", "Кінець гри", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            else
            {
                this.RequestMap("PC", "Attack");
                if (Result == "Miss")
                {
                    this.UserTurn = true;
                    this.ButtonNext.Enabled = true;
                    this.MessageStrip.Text = "Постріл здійснено мимо, перехід ходу.";
                }
                else if (Result == "Wound")
                {
                    this.ButtonNext.Enabled = true;
                    this.MessageStrip.Text = "Корабель поранено, хід супротивника.";
                }
                else if (Result == "Kill")
                {
                    this.ButtonNext.Enabled = true;
                    this.MessageStrip.Text = "Корабель вбито, хід супротивника.";
                }
                else
                {
                    this.згенеруватиКартуToolStripMenuItem.Enabled = true;
                    this.MessageStrip.Text = "Для початку гри згенеруйте карту кораблів.";
                    MessageBox.Show("Супротивник переміг!", "Кінець гри", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }         
            }
        }

        private void ButtonNextStateHandler(object sender, EventArgs e)
        {
            if (this.ButtonNext.Enabled == true)
            {
                this.CounterOnButton = 2;
                this.MoveTimer.Start();
                this.CounterOnButtonTimer.Start();
            }
        }

        private void CounterOnButtonHandler(object sender, EventArgs e)
        {
            this.ButtonNext.Text = String.Format("ДАЛІ... ({0})", this.CounterOnButton);
            this.CounterOnButton--;
        }

        private void AutoMoveHandler(object sender, EventArgs e)
        {
            this.ButtonNext_Click(sender, e);
        }

        private char TransLiterator(int Value)
        {
            char Letter = '0';
            switch (Value)
            {
                case 1: Letter = 'A'; break;
                case 2: Letter = 'Б'; break;
                case 3: Letter = 'В'; break;
                case 4: Letter = 'Г'; break;
                case 5: Letter = 'Д'; break;
                case 6: Letter = 'Е'; break;
                case 7: Letter = 'Ж'; break;
                case 8: Letter = 'З'; break;
                case 9: Letter = 'К'; break;
                case 10: Letter = 'Л'; break;
                default: break;
            }
            return Letter;
        }

        private void випадковийВибірToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Random Rand = new Random();
            if (Rand.Next(0, 10) % 2 == 0)
                this.розпочатиПершимToolStripMenuItem_Click(sender, e);
            else
                this.розпочатиДругимToolStripMenuItem_Click(sender, e);
        }

        private void версіяToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Версія 0.9b", "Інформація", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void правилаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("\n\n\tПеред початком гри необхідно згенерувати карту власних кораблів. Генерувати карту можна декілька раз.\n\n\tДля здійснення пострілу необхідно обрати необхідну клітинку та натиснути кнопку \"ВОГОНЬ!\". Для перегляду ходу супротивника необхідно натиснути кнопку \"ДАЛІ...\".\n\n\tПеремагає той, хто перший знищить усі кораблі супровтивника. \n\n\tУспіхів =)... ", "Правила гри", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void вихідToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
