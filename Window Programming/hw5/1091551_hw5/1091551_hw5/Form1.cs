using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw5
{
    public partial class Form1 : Form
    {
        int time = 0;
        Image fruit = Properties.Resources._8_0;
        Image[] fruits = new Image[16];
        Random rd = new Random();
        int p1x = -1, p1y = -1, p1f = -1;
        bool[] open = new bool[16];
        bool stop = false;
        Image[] p = new Image[8];

        private void timer1_Tick(object sender, EventArgs e)
        {
            label1.Text = "" + ++time +" Seconds";

            int i = 0;
            for (; i < 16; ++i) if (open[i] == false) break;

            if (i == 16) timer1.Stop();
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            Graphics gs = this.CreateGraphics();

            for (int i = 0; i < 4; ++i)
                for (int j = 1; j <= 4; ++j)
                {
                    if (open[(j - 1) + i * 4] == false)
                    {
                        gs.DrawImage(fruit, i * 60, j * 60, 60, 60);
                        gs.DrawRectangle(Pens.Black, i * 60, j * 60, 60, 60);
                    }
                }

            stop = false;
            timer2.Stop();
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Start();
            time = -1;
            p1x = p1y = p1f = -1;

            bool[] check = new bool[16];
            int tmp;

            for (int i = 0; i < 16; ++i)
            {
                check[i] = false;
                open[i] = false;
            }

            for (int j = 0; j < 2; ++j)
            {
                for (int i = 0; i < 8; ++i)
                {
                    tmp = rd.Next(16);
                    while (check[tmp] == true) tmp = rd.Next(16);
                    fruits[tmp] = p[i];
                    check[tmp] = true;
                }
            }

            Graphics gs = this.CreateGraphics();
            for (int i = 0; i < 4; ++i)
                for (int j = 1; j <= 4; ++j)
                {
                    gs.DrawImage(fruit, i * 60, j * 60, 60, 60);
                    gs.DrawRectangle(Pens.Black, i * 60, j * 60, 60, 60);
                }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            p[0] = Properties.Resources._8_1;
            p[1] = Properties.Resources._8_2;
            p[2] = Properties.Resources._8_3;
            p[3] = Properties.Resources._8_4;
            p[4] = Properties.Resources._8_5;
            p[5] = Properties.Resources._8_6;
            p[6] = Properties.Resources._8_7;
            p[7] = Properties.Resources._8_8;
            bool[] check = new bool[16];
            int tmp;

            for (int i = 0; i < 16; ++i)
            {
                check[i] = false;
                open[i] = false;
            }

            for (int j = 0; j < 2; ++j)
            {
                for (int i = 0; i < 8; ++i)
                {
                    tmp = rd.Next(16);
                    while (check[tmp] == true) tmp = rd.Next(16);
                    fruits[tmp] = p[i];
                    check[tmp] = true;
                }
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            Graphics gs = this.CreateGraphics();

            for (int i = 0; i < 4; ++i)
            {
                for (int j = 1; j <= 4; ++j)
                {
                    if (e.X > i * 60 && e.Y > j * 60 && e.X < (i + 1) * 60 && e.Y < (j + 1) * 60 && open[(j - 1) + i * 4] != true && !stop)
                    {
                        gs.DrawImage(fruits[(j - 1) + i * 4], i * 60, j * 60, 60, 60);
                        gs.DrawRectangle(Pens.Black, i * 60, j * 60, 60, 60);

                        if (p1x == -1)
                        {
                            p1x = i * 60;
                            p1y = j * 60;
                            p1f = (j - 1) + i * 4;
                        }
                        else
                        {
                            if (fruits[p1f] == fruits[(j - 1) + i * 4])
                            {
                                open[p1f] = true;
                                open[(j - 1) + i * 4] = true;
                            }
                            else
                            {
                                stop = true;
                                timer2.Start();
                            }

                            p1x = p1y = p1f = -1;
                        }

                        i = 4;
                        break;
                    }
                }
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < 4; ++i)
                for (int j = 1; j <= 4; ++j)
                {
                    e.Graphics.DrawImage(fruit, i * 60, j * 60, 60, 60);
                    e.Graphics.DrawRectangle(Pens.Black, i * 60, j * 60, 60, 60);
                }
        }

        
        public Form1()
        {
            InitializeComponent();
        }
    }
}
