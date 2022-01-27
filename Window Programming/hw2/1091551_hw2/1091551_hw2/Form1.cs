using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw2
{
    public partial class Form1 : Form
    {
        Rectangle[] rec;
        int[] check;
        Pen p1, p2, p3;
        Random rd;
        int count;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    e.Graphics.DrawRectangle(p1, 10 + j * 60, 30 + i * 60, 60, 60);
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            Graphics gs = this.CreateGraphics();

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (rec[i * 3 + j].Contains(e.Location) && check[i * 3 + j] == 0)
                    {
                        gs.DrawEllipse(p2, 20 + j * 60, 40 + i * 60, 40, 40);
                        check[i * 3 + j] = 1; //human

                        for (int k = 0; k < 3; k++)
                        {
                            if (check[3 * k] == 1 && check[3 * k + 1] == 1 && check[3 * k + 2] == 1)
                            {
                                label2.Text = "You Win!";
                                gs.DrawLine(p3, 20, 60 + k * 60, 180, 60 + k * 60);
                                for (int l = 0; l < 9; l++)
                                    check[l] = 1;
                                return;
                            }
                            else if (check[k] == 1 && check[k + 3] == 1 && check[k + 6] == 1)
                            {
                                label2.Text = "You Win!";
                                gs.DrawLine(p3, 40 + k * 60, 40, 40 + k * 60, 200);
                                for (int l = 0; l < 9; l++)
                                    check[l] = 1;
                                return;
                            }
                        }
                        if (check[0] == 1 && check[4] == 1 && check[8] == 1)
                        {
                            label2.Text = "You Win!";
                            gs.DrawLine(p3, 20, 40, 180, 200);
                            for (int l = 0; l < 9; l++)
                                check[l] = 1;
                            return;
                        }
                        else if (check[2] == 1 && check[4] == 1 && check[6] == 1)
                        {
                            label2.Text = "You Win!";
                            gs.DrawLine(p3, 180, 40, 20, 200);
                            for (int l = 0; l < 9; l++)
                                check[l] = 1;
                            return;
                        }

                        if (check[4] == 0)
                        {
                            check[4] = 2;
                            gs.DrawLine(p2, 80, 100, 120, 140);
                            gs.DrawLine(p2, 120, 100, 80, 140);
                            count++;
                        }
                        else
                        {
                            while (count < 4)
                            {
                                int a = rd.Next(3);
                                int b = rd.Next(3);
                                if (check[a * 3 + b] == 0)
                                {
                                    gs.DrawLine(p2, 20 + b * 60, 40 + a * 60, 60 + b * 60, 80 + a * 60);
                                    gs.DrawLine(p2, 60 + b * 60, 40 + a * 60, 20 + b * 60, 80 + a * 60);
                                    check[a * 3 + b] = 2; //computer
                                    count++;
                                    break;
                                }
                            }
                        }

                        for (int k = 0; k < 3; k++)
                        {
                            if (check[3 * k] == 2 && check[3 * k + 1] == 2 && check[3 * k + 2] == 2)
                            {
                                label2.Text = "You Lose!";
                                gs.DrawLine(p3, 20, 60 + k * 60, 180, 60 + k * 60);
                                for (int l = 0; l < 9; l++)
                                    check[l] = 2;
                                return;
                            }
                            else if (check[k] == 2 && check[k + 3] == 2 && check[k + 6] == 2)
                            {
                                label2.Text = "You Lose!";
                                gs.DrawLine(p3, 40 + k * 60, 40, 40 + k * 60, 200);
                                for (int l = 0; l < 9; l++)
                                    check[l] = 2;
                                return;
                            }
                        }
                        if (check[0] == 2 && check[4] == 2 && check[8] == 2)
                        {
                            label2.Text = "You Lose!";
                            gs.DrawLine(p3, 20, 40, 180, 200);
                            for (int l = 0; l < 9; l++)
                                check[l] = 2;
                            return;
                        }
                        else if (check[2] == 2 && check[4] == 2 && check[6] == 2)
                        {
                            label2.Text = "You Lose!";
                            gs.DrawLine(p3, 180, 40, 20, 200);
                            for (int l = 0; l < 9; l++)
                                check[l] = 2;
                            return;
                        }
                        return;
                    }
                }
            }
        }


        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            label2.Text = "Draw!";
            Graphics gs = this.CreateGraphics();
            gs.Clear(this.BackColor);

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    gs.DrawRectangle(p1, 10 + j * 60, 30 + i * 60, 60, 60);

            for (int i = 0; i < 9; i++)
                check[i] = 0;
            count = 0;
        }

        public Form1()
        {
            InitializeComponent();
            rec = new Rectangle[9];
            check = new int[9];
            p1 = new Pen(Color.Black, 3);
            p2 = new Pen(Color.Blue, 3);
            p3 = new Pen(Color.Red, 3);
            rd = new Random();
            count = 0;
            label2.Text = "";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    rec[3 * i + j].X = j * 60 + 10;
                    rec[3 * i + j].Y = i * 60 + 30;
                    rec[3 * i + j].Height = 60;
                    rec[3 * i + j].Width = 60;
                    check[3 * i + j] = 0;
                }
            }
        }
    }
}
